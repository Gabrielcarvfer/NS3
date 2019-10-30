// MAH: start

#include <config.h>
#include <errno.h>
#include <inttypes.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <time.h>

#include "flow.h"
#include "mac-learning.h"
#include "ofpbuf.h"
#include "ofp-print.h"
#include "openflow/openflow.h"
#include "poll-loop.h"
#include "queue.h"
#include "rconn.h"
#include "stp.h"
#include "timeval.h"
#include "vconn.h"
#include "xtoxll.h"

#include "openflow/ericsson-ext.h"
struct rconn;

#include "mpls-fib.h"
#include "mpls-switch.h"
#include "read-mpls-fib.h"
#define THIS_MODULE VLM_mpls_switch
#include "vlog.h"

// MAH: start
// XXX TEMPORARY
#include "vconn-mpls.h"
// MAH: end

/* The log messages here could actually be useful in debugging, so keep the
 * rate limit relatively high. */
static struct vlog_rate_limit rl = VLOG_RATE_LIMIT_INIT(30, 300);

static void send_features_request(struct mpls_switch *sw, struct rconn *rconn);
void queue_tx(struct mpls_switch *, struct rconn *, struct ofpbuf *);


static void send_features_request(struct mpls_switch *, struct rconn *);
static void schedule_query(struct mpls_switch *, long long int delay);

typedef void packet_handler_func(struct mpls_switch *, struct rconn *, void *);
static packet_handler_func process_switch_features;
static packet_handler_func process_packet_in;
static packet_handler_func process_echo_request;
static packet_handler_func process_port_status;
static packet_handler_func process_phy_port;
static packet_handler_func process_stats_reply;
static packet_handler_func process_vport_table_features_reply;
void configure_mpls_switch_state(struct mpls_switch *sw, struct rconn *rconn);


/* Creates and returns a new mpls-enabled switch.
 * 'rconn' is used to send out an OpenFlow features request. */
struct mpls_switch *
mpls_switch_create(struct rconn *rconn)
{
    struct mpls_switch *sw;
    sw = xcalloc(1, sizeof *sw);
    sw->max_idle = OFP_FLOW_PERMANENT; // permanent flow
    sw->datapath_id = 0;
    sw->last_features_request = time_now() - 1;
    send_features_request(sw, rconn);
    return sw;
}

/* Destroys 'sw'. */
void
mpls_switch_destroy(struct mpls_switch *sw)
{
	destroy_freelist(sw->vports);
	destroy_mpls_fib(sw->mplsFibTable);
    if (sw) free(sw);
}

/* Takes care of necessary 'sw' activity, except for receiving packets (which
 * the caller must do). */
void
mpls_switch_run(struct mpls_switch *sw, struct rconn *rconn)
{
	// start the configuration process
    //send_features_request(sw, rconn);
}

void
mpls_switch_wait(struct mpls_switch *sw)
{
	// does nothing right now
}

/* Processes 'msg', which should be an OpenFlow received on 'rconn', according
 * to the learning switch state in 'sw'.  The most likely result of processing
 * is that flow-setup and packet-out OpenFlow messages will be sent out on
 * 'rconn'.  */
void
mpls_switch_process_packet(struct mpls_switch *sw, struct rconn *rconn,
						   const struct ofpbuf *msg)
{
    struct processor {
        uint8_t type;
        size_t min_size;
        packet_handler_func *handler;
    };
    static const struct processor processors[] = {
        {
            OFPT_ECHO_REQUEST,
            sizeof(struct ofp_header),
            process_echo_request
        },
        {
            OFPT_FEATURES_REPLY,
            sizeof(struct ofp_switch_features),
            process_switch_features
        },
        {
            OFPT_PACKET_IN,
            offsetof(struct ofp_packet_in, data),
            process_packet_in
        },
        {
            OFPT_PORT_STATUS,
            sizeof(struct ofp_port_status),
            process_port_status
        },
        {
            OFPT_STATS_REPLY,
            offsetof(struct ofp_stats_reply, body),
            process_stats_reply
        },
        {
            OFPT_FLOW_EXPIRED,
            sizeof(struct ofp_flow_expired),
            NULL
        },
        // vport table features reply message
        {
        	OFPT_VPORT_TABLE_FEATURES_REPLY,
        	sizeof(struct ofp_vport_table_features),
        	process_vport_table_features_reply
        },
    };
    const size_t n_processors = ARRAY_SIZE(processors);
    const struct processor *p;
    struct ofp_header *oh;

    oh = msg->data;
    if (sw->datapath_id == 0
        && oh->type != OFPT_ECHO_REQUEST
        && oh->type != OFPT_FEATURES_REPLY) {
        send_features_request(sw, rconn);
        return;
    }

    for (p = processors; p < &processors[n_processors]; p++) {
        if (oh->type == p->type) {
            if (msg->size < p->min_size) {
                VLOG_WARN_RL(&rl, "%012llx: %s: too short (%zu bytes) for "
                             "type %"PRIu8" (min %zu)", sw->datapath_id,
                             rconn_get_name(rconn), msg->size, oh->type,
                             p->min_size);
                return;
            }
            if (p->handler) {
                (p->handler)(sw, rconn, msg->data);
            }
            return;
        }
    }
    if (VLOG_IS_DBG_ENABLED()) {
        char *p = ofp_to_string(msg->data, msg->size, 2);
        VLOG_DBG_RL(&rl, "%012llx: OpenFlow packet ignored: %s",
                    sw->datapath_id, p);
        free(p);
    }
}

static void
send_features_request(struct mpls_switch *sw, struct rconn *rconn)
{
    time_t now = time_now();
    if (now >= sw->last_features_request + 1) {
        struct ofpbuf *b;
        struct ofp_switch_config *osc;

        /* Send OFPT_FEATURES_REQUEST. */
        make_openflow(sizeof(struct ofp_header), OFPT_FEATURES_REQUEST, &b);
        queue_tx(sw, rconn, b);

        /* Send OFPT_SET_CONFIG. */
        osc = make_openflow(sizeof *osc, OFPT_SET_CONFIG, &b);
        osc->flags = htons(OFPC_SEND_FLOW_EXP);
        osc->miss_send_len = htons(OFP_DEFAULT_MISS_SEND_LEN);
        queue_tx(sw, rconn, b);

        sw->last_features_request = now;
    }
}

static void
send_vport_table_features_request(struct mpls_switch *sw, struct rconn *rconn)
{
	struct ofpbuf *b;
	make_openflow(sizeof(struct ofp_header), OFPT_VPORT_TABLE_FEATURES_REQUEST, &b);
	queue_tx(sw, rconn, b);
}

void
queue_tx(struct mpls_switch *sw, struct rconn *rconn, struct ofpbuf *b)
{
    int retval = rconn_send_with_limit(rconn, b, &sw->n_queued, 10);
    if (retval && retval != ENOTCONN) {
        if (retval == EAGAIN) {
            VLOG_WARN_RL(&rl, "%012llx: %s: tx queue overflow",
                         sw->datapath_id, rconn_get_name(rconn));
        } else {
            VLOG_WARN_RL(&rl, "%012llx: %s: send: %s",
                         sw->datapath_id, rconn_get_name(rconn),
                         strerror(retval));
        }
    }
}

#include<sys/stat.h>

int file_exists (char * fileName)
{
   struct stat buf;
   int i = stat ( fileName, &buf );
     /* File found */
     if ( i == 0 )
     {
       return 1;
     }
     return 0;

}


void configure_mpls_switch_state(struct mpls_switch *sw, struct rconn *rconn)
{
	struct mpls_ftn *ftn_entry;
	struct mpls_ilm *ilm_entry;
	struct mpls_nhlfe *nhlfe_entry;
	// hardcode in values for now
	char mpls_fib_file[1024];

	// MAH: start
	// example of how to query port stats
	//uint32_t ports[] = {0, 65539}; // one physical port, one virtual
	// MAH: end

	while (!file_exists(mpls_fib_file)) {
		printf("Enter path of FIB file (e.g. ./switch_fib.xml): ");
		if (scanf("%s", mpls_fib_file)) {}
	}

	sw->mplsFibTable = read_mpls_fib(mpls_fib_file, sw);

	// iterate through FTN table
	// install all the OF actions for the NHLFE entries
	ftn_entry = sw->mplsFibTable->ftnTable;
	while (ftn_entry != NULL) {
		nhlfe_entry = ftn_entry->nhlfe;
		while (nhlfe_entry != NULL) {
			install_nhlfe_actions(sw, rconn, nhlfe_entry);
			nhlfe_entry = nhlfe_entry->next_entry;
		}
		ftn_entry = ftn_entry->next_entry;
	}


	// loop over ILM table
	ilm_entry = sw->mplsFibTable->ilmTable;
	while (ilm_entry != NULL) {
		nhlfe_entry = ilm_entry->nhlfe;
		while (nhlfe_entry != NULL) {
			install_nhlfe_actions(sw, rconn, nhlfe_entry);
			nhlfe_entry = nhlfe_entry->next_entry;
		}
		ilm_entry = ilm_entry->next_entry;
	}

	// MAH: start
	// example of how to use port_stats
	//queue_tx(sw, rconn, get_vport_table_stats());
	//ports[0] = htonl(ports[0]);
	//ports[1] = htonl(ports[1]);
	//queue_tx(sw, rconn, get_vport_stats(ports,2));
	// MAH: end

}

static void
schedule_query(struct mpls_switch *sw, long long int delay)
{
	(void)sw;
	(void)delay;
	// does nothing
}

static void
process_switch_features(struct mpls_switch *sw, struct rconn *rconn, void *osf_)
{
    struct ofp_switch_features *osf = osf_;
    size_t n_ports = ((ntohs(osf->header.length)
                       - offsetof(struct ofp_switch_features, ports))
                      / sizeof *osf->ports);
    size_t i;

    sw->datapath_id = ntohll(osf->datapath_id);
    sw->capabilities = ntohl(osf->capabilities);
    sw->flow_actions = ntohl(osf->actions);
    for (i = 0; i < n_ports; i++) {
        process_phy_port(sw, rconn, &osf->ports[i]);
    }
    if (sw->capabilities & OFPC_STP) {
        schedule_query(sw, 1000);
    }

	printf("process_switch_features\n");
	// check for support of virtual port table
    if (sw->capabilities & OFPC_VPORT_TABLE) {
    	// switch supports virtual port table
    	// request virtual port table features
    	printf("send vport table features request\n");
    	send_vport_table_features_request(sw, rconn);
    } else {
    	// without virtual port table support, MPLS is not supported
    	sw->mplsSwitchOps.pop_option  = OFP_MPLS_UNSUPPORTED;
    	sw->mplsSwitchOps.push_option = OFP_MPLS_UNSUPPORTED;
    	sw->mplsSwitchOps.swap_option = OFP_MPLS_UNSUPPORTED;
    }

}

static void
process_vport_table_features_reply(struct mpls_switch *sw, struct rconn *rconn, void *ovpf_)
{
	struct ofp_vport_table_features *ovpf = ovpf_;
	// The actions the switch supports at the virtual port table
	sw->vport_actions = ntohl(ovpf->actions);

	printf("process_vport_table_features_reply\n");

	// The switch supports max_vports virtual port entries
	// create a free list to manage this port space
	sw->vports = create_freelist(ntohl(ovpf->max_vports));
	if (sw->vports == NULL) {
		printf("could not allocate vports freelist\n");
		exit(0);
	}

	// Determine how the switch should support the pop action
	if (sw->vport_actions & OFPPAT_POP_MPLS) {
		sw->mplsSwitchOps.pop_option = OFP_MPLS_POP_OP1;
		printf("pop op1\n");
	} else {
		sw->mplsSwitchOps.pop_option = OFP_MPLS_UNSUPPORTED;
		printf("pop unsupported\n");
	}

	// Determine how the switch should perform the push action
	if (sw->vport_actions & OFPPAT_PUSH_MPLS) {
		sw->mplsSwitchOps.push_option = OFP_MPLS_PUSH_OP1;
		printf("push op1\n");
	} else {
		sw->mplsSwitchOps.push_option = OFP_MPLS_UNSUPPORTED;
		printf("push unsupported\n");
	}

	// Determine how the switch should perform the swap action
	if (ovpf->mixed_chaining && (sw->vport_actions & OFPPAT_PUSH_MPLS)
		&& (sw->vport_actions & OFPPAT_POP_MPLS)) {
		// switch can support a pop virtual port followed by a push virtual port
		sw->mplsSwitchOps.swap_option = OFP_MPLS_SWAP_OP1;
		printf("swap op1\n");
	} else if ((sw->flow_actions & OFPAT_SET_MPLS_LABEL)
			   && (sw->vport_actions & OFPPAT_POP_MPLS)) {
		// switch cannot mix pop & push virtual ports
		// but can rewrite at the flow tabl eand
		sw->mplsSwitchOps.swap_option = OFP_MPLS_SWAP_OP2;
		printf("swap op2\n");
	} else {
		// determine how to support MPLS swap
		sw->mplsSwitchOps.swap_option = OFP_MPLS_UNSUPPORTED;
		printf("swap unsupported\n");
	}



	// Read the FIB for a switch from a file
    configure_mpls_switch_state(sw, rconn);
}

static void
process_packet_in(struct mpls_switch *sw, struct rconn *rconn, void *opi_)
{
	// Set up flows to drop any packets that dont match the
	// pre-defined MPLS flows
    struct ofp_packet_in *opi = opi_;
    uint16_t in_port = ntohs(opi->in_port);

    size_t pkt_ofs, pkt_len;
    struct ofpbuf pkt;
    struct flow flow;

    /* Extract flow data from 'opi' into 'flow'. */
    pkt_ofs = offsetof(struct ofp_packet_in, data);
    pkt_len = ntohs(opi->header.length) - pkt_ofs;
    pkt.data = opi->data;
    pkt.size = pkt_len;
    flow_extract(&pkt, in_port, &flow);


    /* Set up a flow to drop packets, or just drop the packet if we don't set
     * up flows at all. */
    if (sw->max_idle >= 0) {
        queue_tx(sw, rconn, make_add_flow(&flow, ntohl(opi->buffer_id),
                                          sw->max_idle, 0));
    }
    return;
}

static void
process_echo_request(struct mpls_switch *sw, struct rconn *rconn, void *rq_)
{
    struct ofp_header *rq = rq_;
    queue_tx(sw, rconn, make_echo_reply(rq));
}

static void
process_port_status(struct mpls_switch *sw, struct rconn *rconn, void *ops_)
{
    struct ofp_port_status *ops = ops_;
    process_phy_port(sw, rconn, &ops->desc);
}

static void
process_phy_port(struct mpls_switch *sw, struct rconn *rconn, void *opp_)
{
	(void)sw;
	(void)rconn;
	(void)opp_;
}

static void
process_flow_stats(struct mpls_switch *sw, struct rconn *rconn,
                   const struct ofp_flow_stats *ofs)
{
	(void)sw;
	(void)rconn;
	(void)ofs;
}

static void
process_stats_reply(struct mpls_switch *sw, struct rconn *rconn, void *osr_)
{
    struct ofp_stats_reply *osr = osr_;
    const uint8_t *body = osr->body;
    const uint8_t *pos = body;
    size_t body_len;


    body_len = (ntohs(osr->header.length)
                - offsetof(struct ofp_stats_reply, body));
    for (;;) {
        const struct ofp_flow_stats *fs;
        ptrdiff_t bytes_left = body + body_len - pos;
        size_t length;

        if (bytes_left < sizeof *fs) {
            if (bytes_left != 0) {
                VLOG_WARN_RL(&rl, "%012llx: %td leftover bytes in flow "
                             "stats reply", sw->datapath_id, bytes_left);
            }
            break;
        }

        fs = (const void *) pos;
        length = ntohs(fs->length);
        if (length < sizeof *fs) {
            VLOG_WARN_RL(&rl, "%012llx: flow stats length %zu is shorter than "
                         "min %zu", sw->datapath_id, length, sizeof *fs);
            break;
        } else if (length > bytes_left) {
            VLOG_WARN_RL(&rl, "%012llx: flow stats length %zu but only %td "
                         "bytes left", sw->datapath_id, length, bytes_left);
            break;
        } else if ((length - sizeof *fs) % sizeof fs->actions[0]) {
            VLOG_WARN_RL(&rl, "%012llx: flow stats length %zu has %zu bytes "
                         "left over in final action", sw->datapath_id, length,
                         (length - sizeof *fs) % sizeof fs->actions[0]);
            break;
        }

        sw->n_flows++;
        process_flow_stats(sw, rconn, fs);

        pos += length;
     }
    if (!(osr->flags & htons(OFPSF_REPLY_MORE))) {
        VLOG_DBG("%012llx: Deleted %d of %d received flows to "
                 "implement STP, %d because of no-recv, %d because of "
                 "no-send", sw->datapath_id,
                 sw->n_no_recv + sw->n_no_send, sw->n_flows,
                 sw->n_no_recv, sw->n_no_send);
    } else {
    }
}

// MAH: end
