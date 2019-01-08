/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford
 * Junior University
 *
 * We are making the OpenFlow specification and associated documentation
 * (Software) available for public use and benefit with the expectation
 * that others will use, modify and enhance the Software and contribute
 * those enhancements back to the community. However, since we would
 * like to make the Software available for broadest use, with as few
 * restrictions as possible permission is hereby granted, free of
 * charge, to any person obtaining a copy of this Software to deal in
 * the Software under the copyrights without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * The name and trademarks of copyright holder(s) may NOT be used in
 * advertising or publicity pertaining to the Software or any
 * derivatives without specific, written prior permission.
 */

#include <config.h>
#include "ofp-print.h"
#include "xtoxll.h"

#include <errno.h>
#include <inttypes.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>

#include "compiler.h"
#include "dynamic-string.h"
#include "flow.h"
#include "ofpbuf.h"
#include "openflow/openflow.h"
#include "openflow/nicira-ext.h"
#include "packets.h"
#include "util.h"

static void ofp_print_port_name(struct ds *string, uint16_t port);
static void ofp_print_match(struct ds *, const struct ofp_match *,
                            int verbosity);

/* Returns a string that represents the contents of the Ethernet frame in the
 * 'len' bytes starting at 'data' to 'stream' as output by tcpdump.
 * 'total_len' specifies the full length of the Ethernet frame (of which 'len'
 * bytes were captured).
 *
 * The caller must free the returned string.
 *
 * This starts and kills a tcpdump subprocess so it's quite expensive. */
char *
ofp_packet_to_string(const void *data, size_t len, size_t total_len)
{
    struct pcap_hdr {
        uint32_t magic_number;   /* magic number */
        uint16_t version_major;  /* major version number */
        uint16_t version_minor;  /* minor version number */
        int32_t thiszone;        /* GMT to local correction */
        uint32_t sigfigs;        /* accuracy of timestamps */
        uint32_t snaplen;        /* max length of captured packets */
        uint32_t network;        /* data link type */
    } PACKED;

    struct pcaprec_hdr {
        uint32_t ts_sec;         /* timestamp seconds */
        uint32_t ts_usec;        /* timestamp microseconds */
        uint32_t incl_len;       /* number of octets of packet saved in file */
        uint32_t orig_len;       /* actual length of packet */
    } PACKED;

    struct pcap_hdr ph;
    struct pcaprec_hdr prh;

    struct ds ds = DS_EMPTY_INITIALIZER;

    char command[128];
    FILE *pcap;
    FILE *tcpdump;
    int status;
    int c;

    pcap = tmpfile();
    if (!pcap) {
        ofp_error(errno, "tmpfile");
        return xstrdup("<error>");
    }

    /* The pcap reader is responsible for figuring out endianness based on the
     * magic number, so the lack of htonX calls here is intentional. */
    ph.magic_number = 0xa1b2c3d4;
    ph.version_major = 2;
    ph.version_minor = 4;
    ph.thiszone = 0;
    ph.sigfigs = 0;
    ph.snaplen = 1518;
    ph.network = 1;             /* Ethernet */

    prh.ts_sec = 0;
    prh.ts_usec = 0;
    prh.incl_len = len;
    prh.orig_len = total_len;

    fwrite(&ph, 1, sizeof ph, pcap);
    fwrite(&prh, 1, sizeof prh, pcap);
    fwrite(data, 1, len, pcap);

    fflush(pcap);
    if (ferror(pcap)) {
        ofp_error(errno, "error writing temporary file");
    }
    rewind(pcap);

    snprintf(command, sizeof command, "/usr/sbin/tcpdump -e -n -r /dev/fd/%d 2>/dev/null",
             fileno(pcap));
    tcpdump = popen(command, "r");
    fclose(pcap);
    if (!tcpdump) {
        ofp_error(errno, "exec(\"%s\")", command);
        return xstrdup("<error>");
    }

    while ((c = getc(tcpdump)) != EOF) {
        ds_put_char(&ds, c);
    }

    status = pclose(tcpdump);
    if (WIFEXITED(status)) {
        if (WEXITSTATUS(status))
            ofp_error(0, "tcpdump exited with status %d", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        ofp_error(0, "tcpdump exited with signal %d", WTERMSIG(status));
    }
    return ds_cstr(&ds);
}

/* Pretty-print the OFPT_PACKET_IN packet of 'len' bytes at 'oh' to 'stream'
 * at the given 'verbosity' level. */
static void
ofp_packet_in(struct ds *string, const void *oh, size_t len, int verbosity)
{
    const struct ofp_packet_in *op = oh;
    size_t data_len;

    ds_put_format(string, " total_len=%"PRIu16" in_port=",
                  ntohs(op->total_len));
    ofp_print_port_name(string, ntohs(op->in_port));

    if (op->reason == OFPR_ACTION)
        ds_put_cstr(string, " (via action)");
    else if (op->reason != OFPR_NO_MATCH)
        ds_put_format(string, " (***reason %"PRIu8"***)", op->reason);

    data_len = len - offsetof(struct ofp_packet_in, data);
    ds_put_format(string, " data_len=%zu", data_len);
    if (htonl(op->buffer_id) == UINT32_MAX) {
        ds_put_format(string, " (unbuffered)");
        if (ntohs(op->total_len) != data_len)
            ds_put_format(string, " (***total_len != data_len***)");
    } else {
        ds_put_format(string, " buffer=0x%08"PRIx32, ntohl(op->buffer_id));
        if (ntohs(op->total_len) < data_len)
            ds_put_format(string, " (***total_len < data_len***)");
    }
    ds_put_char(string, '\n');

    if (verbosity > 0) {
        struct flow flow;
        struct ofpbuf packet;
        struct ofp_match match;
        packet.data = (void *) op->data;
        packet.size = data_len;
        flow_extract(&packet, ntohs(op->in_port), &flow);
        match.wildcards = 0;
        match.in_port = flow.in_port;
        memcpy(match.dl_src, flow.dl_src, ETH_ADDR_LEN);
        memcpy(match.dl_dst, flow.dl_dst, ETH_ADDR_LEN);
        match.dl_vlan = flow.dl_vlan;
        match.dl_type = flow.dl_type;
        match.nw_proto = flow.nw_proto;
        match.pad = 0;
        match.nw_src = flow.nw_src;
        match.nw_dst = flow.nw_dst;
        match.tp_src = flow.tp_src;
        match.tp_dst = flow.tp_dst;
        ofp_print_match(string, &match, verbosity);
        ds_put_char(string, '\n');
    }
    if (verbosity > 1) {
        char *packet = ofp_packet_to_string(op->data, data_len,
                                            ntohs(op->total_len));
        ds_put_cstr(string, packet);
        free(packet);
    }
}

static void ofp_print_port_name(struct ds *string, uint16_t port)
{
    const char *name;
    switch (port) {
    case OFPP_IN_PORT:
        name = "IN_PORT";
        break;
    case OFPP_TABLE:
        name = "TABLE";
        break;
    case OFPP_NORMAL:
        name = "NORMAL";
        break;
    case OFPP_FLOOD:
        name = "FLOOD";
        break;
    case OFPP_ALL:
        name = "ALL";
        break;
    case OFPP_CONTROLLER:
        name = "CONTROLLER";
        break;
    case OFPP_LOCAL:
        name = "LOCAL";
        break;
    case OFPP_NONE:
        name = "NONE";
        break;
    default:
        ds_put_format(string, "%"PRIu16, port);
        return;
    }
    ds_put_cstr(string, name);
}

static void
ofp_print_nx_action(struct ds *string, const struct nx_action_header *nah)
{

    if (nah->subtype == htonl(NXAST_SNAT)) {
        const struct nx_action_snat *nas = (struct nx_action_snat *)nah;
        uint16_t port = ntohs(nas->port);

        if (port < OFPP_MAX) {
            ds_put_format(string, "nat:%"PRIu16, port);
        } else {
            ds_put_format(string, "nat:%"PRIu16" (invalid port)", port);
        }
    } else {
        ds_put_format(string, "***unknown Nicira action:%d***\n",
                ntohl(nah->subtype));
    }
}

static int
ofp_print_action(struct ds *string, const struct ofp_action_header *ah,
        size_t actions_len)
{
    uint16_t type;
    size_t len;

    struct openflow_action {
        size_t min_size;
        size_t max_size;
    };

    const struct openflow_action of_actions[] = {
        [OFPAT_OUTPUT] = {
            sizeof(struct ofp_action_output),
            sizeof(struct ofp_action_output),
        },
        [OFPAT_SET_VLAN_VID] = {
            sizeof(struct ofp_action_vlan_vid),
            sizeof(struct ofp_action_vlan_vid),
        },
        [OFPAT_SET_VLAN_PCP] = {
            sizeof(struct ofp_action_vlan_pcp),
            sizeof(struct ofp_action_vlan_pcp),
        },
        [OFPAT_STRIP_VLAN] = {
            sizeof(struct ofp_action_header),
            sizeof(struct ofp_action_header),
        },
        [OFPAT_SET_DL_SRC] = {
            sizeof(struct ofp_action_dl_addr),
            sizeof(struct ofp_action_dl_addr),
        },
        [OFPAT_SET_DL_DST] = {
            sizeof(struct ofp_action_dl_addr),
            sizeof(struct ofp_action_dl_addr),
        },
        [OFPAT_SET_NW_SRC] = {
            sizeof(struct ofp_action_nw_addr),
            sizeof(struct ofp_action_nw_addr),
        },
        [OFPAT_SET_NW_DST] = {
            sizeof(struct ofp_action_nw_addr),
            sizeof(struct ofp_action_nw_addr),
        },
        [OFPAT_SET_TP_SRC] = {
            sizeof(struct ofp_action_tp_port),
            sizeof(struct ofp_action_tp_port),
        },
        [OFPAT_SET_TP_DST] = {
            sizeof(struct ofp_action_tp_port),
            sizeof(struct ofp_action_tp_port),
        }
        /* OFPAT_VENDOR is not here, since it would blow up the array size. */
    };

    if (actions_len < sizeof *ah) {
        ds_put_format(string, "***action array too short for next action***\n");
        return -1;
    }

    type = ntohs(ah->type);
    len = ntohs(ah->len);
    if (actions_len < len) {
        ds_put_format(string, "***truncated action %"PRIu16"***\n", type);
        return -1;
    }

    if ((len % 8) != 0) {
        ds_put_format(string,
                "***action %"PRIu16" length not a multiple of 8***\n",
                type);
        return -1;
    }

    if (type < ARRAY_SIZE(of_actions)) {
        const struct openflow_action *act = &of_actions[type];
        if ((len < act->min_size) || (len > act->max_size)) {
            ds_put_format(string,
                    "***action %"PRIu16" wrong length: %zu***\n", type, len);
            return -1;
        }
    }

    switch (type) {
    case OFPAT_OUTPUT: {
        struct ofp_action_output *oa = (struct ofp_action_output *)ah;
        // MAH: now 32-bits
        uint32_t port = ntohl(oa->port);
        //uint16_t port = ntohs(oa->port);
        // MAH: end
        if (port < OFPP_MAX) {
            ds_put_format(string, "output:%"PRIu16, port);
        } else {
            ofp_print_port_name(string, port);
            if (port == OFPP_CONTROLLER) {
                if (oa->max_len) {
                    ds_put_format(string, ":%"PRIu16, ntohs(oa->max_len));
                } else {
                    ds_put_cstr(string, ":all");
                }
            }
        }
        break;
    }

    case OFPAT_SET_VLAN_VID: {
        struct ofp_action_vlan_vid *va = (struct ofp_action_vlan_vid *)ah;
        ds_put_format(string, "mod_vlan_vid:%"PRIu16, ntohs(va->vlan_vid));
        break;
    }

    case OFPAT_SET_VLAN_PCP: {
        struct ofp_action_vlan_pcp *va = (struct ofp_action_vlan_pcp *)ah;
        ds_put_format(string, "mod_vlan_pcp:%"PRIu8, va->vlan_pcp);
        break;
    }

    case OFPAT_STRIP_VLAN:
        ds_put_cstr(string, "strip_vlan");
        break;

    case OFPAT_SET_DL_SRC: {
        struct ofp_action_dl_addr *da = (struct ofp_action_dl_addr *)ah;
        ds_put_format(string, "mod_dl_src:"ETH_ADDR_FMT,
                ETH_ADDR_ARGS(da->dl_addr));
        break;
    }

    case OFPAT_SET_DL_DST: {
        struct ofp_action_dl_addr *da = (struct ofp_action_dl_addr *)ah;
        ds_put_format(string, "mod_dl_dst:"ETH_ADDR_FMT,
                ETH_ADDR_ARGS(da->dl_addr));
        break;
    }

    case OFPAT_SET_NW_SRC: {
        struct ofp_action_nw_addr *na = (struct ofp_action_nw_addr *)ah;
        ds_put_format(string, "mod_nw_src:"IP_FMT, IP_ARGS(&na->nw_addr));
        break;
    }

    case OFPAT_SET_NW_DST: {
        struct ofp_action_nw_addr *na = (struct ofp_action_nw_addr *)ah;
        ds_put_format(string, "mod_nw_dst:"IP_FMT, IP_ARGS(&na->nw_addr));
        break;
    }

    case OFPAT_SET_TP_SRC: {
        struct ofp_action_tp_port *ta = (struct ofp_action_tp_port *)ah;
        ds_put_format(string, "mod_tp_src:%d", ntohs(ta->tp_port));
        break;
    }

    case OFPAT_SET_TP_DST: {
        struct ofp_action_tp_port *ta = (struct ofp_action_tp_port *)ah;
        ds_put_format(string, "mod_tp_dst:%d", ntohs(ta->tp_port));
        break;
    }

    case OFPAT_VENDOR: {
        struct ofp_action_vendor_header *avh
                = (struct ofp_action_vendor_header *)ah;
        if (len < sizeof *avh) {
            ds_put_format(string, "***ofpat_vendor truncated***\n");
            return -1;
        }
        if (avh->vendor == htonl(NX_VENDOR_ID)) {
            ofp_print_nx_action(string, (struct nx_action_header *)avh);
        } else {
            ds_put_format(string, "vendor action:0x%x", ntohl(avh->vendor));
        }
        break;
    }

    default:
        ds_put_format(string, "(decoder %"PRIu16" not implemented)", type);
        break;
    }

    return len;
}

static void
ofp_print_actions(struct ds *string, const struct ofp_action_header *action,
                  size_t actions_len)
{
    uint8_t *p = (uint8_t *)action;
    size_t len = 0;

    ds_put_cstr(string, "actions=");
    while (actions_len > 0) {
        if (len) {
            ds_put_cstr(string, ",");
        }
        len = ofp_print_action(string, (struct ofp_action_header *)p,
                actions_len);
        if (len < 0) {
            return;
        }
        p += len;
        actions_len -= len;
    }
}

/* Pretty-print the OFPT_PACKET_OUT packet of 'len' bytes at 'oh' to 'string'
 * at the given 'verbosity' level. */
static void ofp_packet_out(struct ds *string, const void *oh, size_t len,
                           int verbosity)
{
    const struct ofp_packet_out *opo = oh;
    size_t actions_len = ntohs(opo->actions_len);

    ds_put_cstr(string, " in_port=");
    ofp_print_port_name(string, ntohs(opo->in_port));

    ds_put_format(string, " actions_len=%zu ", actions_len);
    if (actions_len > (ntohs(opo->header.length) - sizeof *opo)) {
        ds_put_format(string, "***packet too short for action length***\n");
        return;
    }
    ofp_print_actions(string, opo->actions, actions_len);

    if (ntohl(opo->buffer_id) == UINT32_MAX) {
        int data_len = len - sizeof *opo - actions_len;
        ds_put_format(string, " data_len=%d", data_len);
        if (verbosity > 0 && len > sizeof *opo) {
            char *packet = ofp_packet_to_string(
                    (uint8_t *)opo->actions + actions_len, data_len, data_len);
            ds_put_char(string, '\n');
            ds_put_cstr(string, packet);
            free(packet);
        }
    } else {
        ds_put_format(string, " buffer=0x%08"PRIx32, ntohl(opo->buffer_id));
    }
    ds_put_char(string, '\n');
}

/* qsort comparison function. */
static int
compare_ports(const void *a_, const void *b_)
{
    const struct ofp_phy_port *a = a_;
    const struct ofp_phy_port *b = b_;
    uint16_t ap = ntohs(a->port_no);
    uint16_t bp = ntohs(b->port_no);

    return ap < bp ? -1 : ap > bp;
}

static void ofp_print_port_features(struct ds *string, uint32_t features)
{
    if (features == 0) {
        ds_put_cstr(string, "Unsupported\n");
        return;
    }
    if (features & OFPPF_10MB_HD) {
        ds_put_cstr(string, "10MB-HD ");
    }
    if (features & OFPPF_10MB_FD) {
        ds_put_cstr(string, "10MB-FD ");
    }
    if (features & OFPPF_100MB_HD) {
        ds_put_cstr(string, "100MB-HD ");
    }
    if (features & OFPPF_100MB_FD) {
        ds_put_cstr(string, "100MB-FD ");
    }
    if (features & OFPPF_1GB_HD) {
        ds_put_cstr(string, "1GB-HD ");
    }
    if (features & OFPPF_1GB_FD) {
        ds_put_cstr(string, "1GB-FD ");
    }
    if (features & OFPPF_10GB_FD) {
        ds_put_cstr(string, "10GB-FD ");
    }
    if (features & OFPPF_COPPER) {
        ds_put_cstr(string, "COPPER ");
    }
    if (features & OFPPF_FIBER) {
        ds_put_cstr(string, "FIBER ");
    }
    if (features & OFPPF_AUTONEG) {
        ds_put_cstr(string, "AUTO_NEG ");
    }
    if (features & OFPPF_PAUSE) {
        ds_put_cstr(string, "AUTO_PAUSE ");
    }
    if (features & OFPPF_PAUSE_ASYM) {
        ds_put_cstr(string, "AUTO_PAUSE_ASYM ");
    }
    ds_put_char(string, '\n');
}

static void
ofp_print_phy_port(struct ds *string, const struct ofp_phy_port *port)
{
    uint8_t name[OFP_MAX_PORT_NAME_LEN];
    int j;

    memcpy(name, port->name, sizeof name);
    for (j = 0; j < sizeof name - 1; j++) {
        if (!isprint(name[j])) {
            break;
        }
    }
    name[j] = '\0';

    ds_put_char(string, ' ');
    ofp_print_port_name(string, ntohs(port->port_no));
    ds_put_format(string, "(%s): addr:"ETH_ADDR_FMT", config: %#x, state:%#x\n",
            name, ETH_ADDR_ARGS(port->hw_addr), ntohl(port->config),
            ntohl(port->state));
    if (port->curr) {
        ds_put_format(string, "     current:    ");
        ofp_print_port_features(string, ntohl(port->curr));
    }
    if (port->advertised) {
        ds_put_format(string, "     advertised: ");
        ofp_print_port_features(string, ntohl(port->advertised));
    }
    if (port->supported) {
        ds_put_format(string, "     supported:  ");
        ofp_print_port_features(string, ntohl(port->supported));
    }
    if (port->peer) {
        ds_put_format(string, "     peer:       ");
        ofp_print_port_features(string, ntohl(port->peer));
    }
}

/* Pretty-print the struct ofp_switch_features of 'len' bytes at 'oh' to
 * 'string' at the given 'verbosity' level. */
static void
ofp_print_switch_features(struct ds *string, const void *oh, size_t len,
                          int verbosity)
{
    const struct ofp_switch_features *osf = oh;
    struct ofp_phy_port *port_list;
    int n_ports;
    int i;

    ds_put_format(string, " ver:0x%x, dpid:%"PRIx64"\n",
            osf->header.version, ntohll(osf->datapath_id));
    ds_put_format(string, "n_tables:%d, n_buffers:%d\n", osf->n_tables,
            ntohl(osf->n_buffers));
    ds_put_format(string, "features: capabilities:%#x, actions:%#x\n",
           ntohl(osf->capabilities), ntohl(osf->actions));

    if (ntohs(osf->header.length) >= sizeof *osf) {
        len = MIN(len, ntohs(osf->header.length));
    }
    n_ports = (len - sizeof *osf) / sizeof *osf->ports;

    port_list = xmemdup(osf->ports, len - sizeof *osf);
    qsort(port_list, n_ports, sizeof *port_list, compare_ports);
    for (i = 0; i < n_ports; i++) {
        ofp_print_phy_port(string, &port_list[i]);
    }
    free(port_list);
}

// MAH: start
static void ofp_print_vport_table_features(struct ds *string, const void *oh,
										   size_t len, int verbosity)
{
    const struct ofp_vport_table_features *ovpf = oh;
	ds_put_format(string, "actions:%#x\n", ntohl(ovpf->actions));
}
// MAH: end

/* Pretty-print the struct ofp_switch_config of 'len' bytes at 'oh' to 'string'
 * at the given 'verbosity' level. */
static void
ofp_print_switch_config(struct ds *string, const void *oh, size_t len,
                        int verbosity)
{
    const struct ofp_switch_config *osc = oh;
    uint16_t flags;

    flags = ntohs(osc->flags);
    if (flags & OFPC_SEND_FLOW_EXP) {
        flags &= ~OFPC_SEND_FLOW_EXP;
        ds_put_format(string, " (sending flow expirations)");
    }
    if (flags) {
        ds_put_format(string, " ***unknown flags 0x%04"PRIx16"***", flags);
    }

    ds_put_format(string, " miss_send_len=%"PRIu16"\n", ntohs(osc->miss_send_len));
}

static void print_wild(struct ds *string, const char *leader, int is_wild,
            int verbosity, const char *format, ...)
            __attribute__((format(printf, 5, 6)));

static void print_wild(struct ds *string, const char *leader, int is_wild,
                       int verbosity, const char *format, ...)
{
    if (is_wild && verbosity < 2) {
        return;
    }
    ds_put_cstr(string, leader);
    if (!is_wild) {
        va_list args;

        va_start(args, format);
        ds_put_format_valist(string, format, args);
        va_end(args);
    } else {
        ds_put_char(string, '*');
    }
    ds_put_char(string, ',');
}

static void
print_ip_netmask(struct ds *string, const char *leader, uint32_t ip,
                 uint32_t wild_bits, int verbosity)
{
    if (wild_bits >= 32 && verbosity < 2) {
        return;
    }
    ds_put_cstr(string, leader);
    if (wild_bits < 32) {
        ds_put_format(string, IP_FMT, IP_ARGS(&ip));
        if (wild_bits) {
            ds_put_format(string, "/%d", 32 - wild_bits);
        }
    } else {
        ds_put_char(string, '*');
    }
    ds_put_char(string, ',');
}

/* Pretty-print the ofp_match structure */
static void ofp_print_match(struct ds *f, const struct ofp_match *om,
        int verbosity)
{
    uint32_t w = ntohl(om->wildcards);
    bool skip_type = false;
    bool skip_proto = false;

    if (!(w & OFPFW_DL_TYPE)) {
        skip_type = true;
        if (om->dl_type == htons(ETH_TYPE_IP)) {
            if (!(w & OFPFW_NW_PROTO)) {
                skip_proto = true;
                if (om->nw_proto == IP_TYPE_ICMP) {
                    ds_put_cstr(f, "icmp,");
                } else if (om->nw_proto == IP_TYPE_TCP) {
                    ds_put_cstr(f, "tcp,");
                } else if (om->nw_proto == IP_TYPE_UDP) {
                    ds_put_cstr(f, "udp,");
                } else {
                    ds_put_cstr(f, "ip,");
                    skip_proto = false;
                }
            } else {
                ds_put_cstr(f, "ip,");
            }
        } else if (om->dl_type == htons(ETH_TYPE_ARP)) {
            ds_put_cstr(f, "arp,");
        } else {
            skip_type = false;
        }
    }
    print_wild(f, "in_port=", w & OFPFW_IN_PORT, verbosity,
               "%d", ntohs(om->in_port));
    print_wild(f, "dl_vlan=", w & OFPFW_DL_VLAN, verbosity,
               "0x%04x", ntohs(om->dl_vlan));
    print_wild(f, "dl_src=", w & OFPFW_DL_SRC, verbosity,
               ETH_ADDR_FMT, ETH_ADDR_ARGS(om->dl_src));
    print_wild(f, "dl_dst=", w & OFPFW_DL_DST, verbosity,
               ETH_ADDR_FMT, ETH_ADDR_ARGS(om->dl_dst));
    if (!skip_type) {
        print_wild(f, "dl_type=", w & OFPFW_DL_TYPE, verbosity,
                   "0x%04x", ntohs(om->dl_type));
    }
    print_ip_netmask(f, "nw_src=", om->nw_src,
                     (w & OFPFW_NW_SRC_MASK) >> OFPFW_NW_SRC_SHIFT, verbosity);
    print_ip_netmask(f, "nw_dst=", om->nw_dst,
                     (w & OFPFW_NW_DST_MASK) >> OFPFW_NW_DST_SHIFT, verbosity);
    if (!skip_proto) {
        print_wild(f, "nw_proto=", w & OFPFW_NW_PROTO, verbosity,
                   "%u", om->nw_proto);
    }
    if (om->nw_proto == IP_TYPE_ICMP) {
        print_wild(f, "icmp_type=", w & OFPFW_ICMP_TYPE, verbosity,
                   "%d", ntohs(om->icmp_type));
        print_wild(f, "icmp_code=", w & OFPFW_ICMP_CODE, verbosity,
                   "%d", ntohs(om->icmp_code));
    } else {
        print_wild(f, "tp_src=", w & OFPFW_TP_SRC, verbosity,
                   "%d", ntohs(om->tp_src));
        print_wild(f, "tp_dst=", w & OFPFW_TP_DST, verbosity,
                   "%d", ntohs(om->tp_dst));
    }
}

/* Pretty-print the OFPT_FLOW_MOD packet of 'len' bytes at 'oh' to 'string'
 * at the given 'verbosity' level. */
static void
ofp_print_flow_mod(struct ds *string, const void *oh, size_t len,
                   int verbosity)
{
    const struct ofp_flow_mod *ofm = oh;

    ofp_print_match(string, &ofm->match, verbosity);
    switch (ntohs(ofm->command)) {
    case OFPFC_ADD:
        ds_put_cstr(string, " ADD: ");
        break;
    case OFPFC_MODIFY:
        ds_put_cstr(string, " MOD: ");
        break;
    case OFPFC_MODIFY_STRICT:
        ds_put_cstr(string, " MOD_STRICT: ");
        break;
    case OFPFC_DELETE:
        ds_put_cstr(string, " DEL: ");
        break;
    case OFPFC_DELETE_STRICT:
        ds_put_cstr(string, " DEL_STRICT: ");
        break;
    default:
        ds_put_format(string, " cmd:%d ", ntohs(ofm->command));
    }
    ds_put_format(string, "idle:%d hard:%d pri:%d buf:%#x",
            ntohs(ofm->idle_timeout), ntohs(ofm->hard_timeout),
            ofm->match.wildcards ? ntohs(ofm->priority) : (uint16_t)-1,
            ntohl(ofm->buffer_id));
    ofp_print_actions(string, ofm->actions,
                      len - offsetof(struct ofp_flow_mod, actions));
    ds_put_char(string, '\n');
}

/* Pretty-print the OFPT_FLOW_EXPIRED packet of 'len' bytes at 'oh' to 'string'
 * at the given 'verbosity' level. */
static void
ofp_print_flow_expired(struct ds *string, const void *oh, size_t len,
                       int verbosity)
{
    const struct ofp_flow_expired *ofe = oh;

    ofp_print_match(string, &ofe->match, verbosity);
    ds_put_cstr(string, " reason=");
    switch (ofe->reason) {
    case OFPER_IDLE_TIMEOUT:
        ds_put_cstr(string, "idle");
        break;
    case OFPER_HARD_TIMEOUT:
        ds_put_cstr(string, "hard");
        break;
    default:
        ds_put_format(string, "**%"PRIu8"**", ofe->reason);
        break;
    }
    ds_put_format(string,
         " pri%"PRIu16" secs%"PRIu32" pkts%"PRIu64" bytes%"PRIu64"\n",
         ofe->match.wildcards ? ntohs(ofe->priority) : (uint16_t)-1,
         ntohl(ofe->duration), ntohll(ofe->packet_count),
         ntohll(ofe->byte_count));
}

static void
ofp_print_port_mod(struct ds *string, const void *oh, size_t len,
                   int verbosity)
{
    const struct ofp_port_mod *opm = oh;

    ds_put_format(string, "port: %d: addr:"ETH_ADDR_FMT", config: %#x, mask:%#x\n",
            ntohs(opm->port_no), ETH_ADDR_ARGS(opm->hw_addr),
            ntohl(opm->config), ntohl(opm->mask));
    ds_put_format(string, "     advertise: ");
    if (opm->advertise) {
        ofp_print_port_features(string, ntohl(opm->advertise));
    } else {
        ds_put_format(string, "UNCHANGED\n");
    }
}

// MAH: start
static void
ofp_print_vport_mod(struct ds *string, const void *oh, size_t len,
                   int verbosity)
{
    const struct ofp_vport_mod *ovpm = oh;

    ds_put_format(string, "vport: %u: command: %u\n",
            ntohl(ovpm->vport), ntohl(ovpm->command));
}
// MAH: end

struct error_type {
    int type;
    int code;
    const char *name;
};

static const struct error_type error_types[] = {
#define ERROR_TYPE(TYPE) {TYPE, -1, #TYPE}
#define ERROR_CODE(TYPE, CODE) {TYPE, CODE, #CODE}
    ERROR_TYPE(OFPET_HELLO_FAILED),
    ERROR_CODE(OFPET_HELLO_FAILED, OFPHFC_INCOMPATIBLE),

    ERROR_TYPE(OFPET_BAD_REQUEST),
    ERROR_CODE(OFPET_BAD_REQUEST, OFPBRC_BAD_VERSION),
    ERROR_CODE(OFPET_BAD_REQUEST, OFPBRC_BAD_TYPE),
    ERROR_CODE(OFPET_BAD_REQUEST, OFPBRC_BAD_STAT),
    ERROR_CODE(OFPET_BAD_REQUEST, OFPBRC_BAD_VERSION),

    ERROR_TYPE(OFPET_BAD_ACTION),
    ERROR_CODE(OFPET_BAD_ACTION, OFPBAC_BAD_TYPE),
    ERROR_CODE(OFPET_BAD_ACTION, OFPBAC_BAD_LEN),
    ERROR_CODE(OFPET_BAD_ACTION, OFPBAC_BAD_VENDOR),
    ERROR_CODE(OFPET_BAD_ACTION, OFPBAC_BAD_VENDOR_TYPE),
    ERROR_CODE(OFPET_BAD_ACTION, OFPBAC_BAD_OUT_PORT),

    ERROR_TYPE(OFPET_FLOW_MOD_FAILED),
    ERROR_CODE(OFPET_FLOW_MOD_FAILED, OFPFMFC_ALL_TABLES_FULL)
    // MAH: start
    ,ERROR_TYPE(OFPET_VPORT_MOD_FAILED)
    // MAH: end
};
#define N_ERROR_TYPES ARRAY_SIZE(error_types)

static const char *
lookup_error_type(int type)
{
    const struct error_type *t;

    for (t = error_types; t < &error_types[N_ERROR_TYPES]; t++) {
        if (t->type == type && t->code == -1) {
            return t->name;
        }
    }
    return "?";
}

static const char *
lookup_error_code(int type, int code)
{
    const struct error_type *t;

    for (t = error_types; t < &error_types[N_ERROR_TYPES]; t++) {
        if (t->type == type && t->code == code) {
            return t->name;
        }
    }
    return "?";
}

/* Pretty-print the OFPT_ERROR packet of 'len' bytes at 'oh' to 'string'
 * at the given 'verbosity' level. */
static void
ofp_print_error_msg(struct ds *string, const void *oh, size_t len,
                       int verbosity)
{
    const struct ofp_error_msg *oem = oh;
    int type = ntohs(oem->type);
    int code = ntohs(oem->code);
    char *s;

    ds_put_format(string, " type%d(%s) code%d(%s) payload:\n",
                  type, lookup_error_type(type),
                  code, lookup_error_code(type, code));

    switch (type) {
    case OFPET_HELLO_FAILED:
        ds_put_printable(string, (char *) oem->data, len - sizeof *oem);
        break;

    case OFPET_BAD_REQUEST:
        s = ofp_to_string(oem->data, len - sizeof *oem, 1);
        ds_put_cstr(string, s);
        free(s);
        break;

    default:
        ds_put_hex_dump(string, oem->data, len - sizeof *oem, 0, true);
        break;
    }
}

/* Pretty-print the OFPT_PORT_STATUS packet of 'len' bytes at 'oh' to 'string'
 * at the given 'verbosity' level. */
static void
ofp_print_port_status(struct ds *string, const void *oh, size_t len,
                      int verbosity)
{
    const struct ofp_port_status *ops = oh;

    if (ops->reason == OFPPR_ADD) {
        ds_put_format(string, " ADD:");
    } else if (ops->reason == OFPPR_DELETE) {
        ds_put_format(string, " DEL:");
    } else if (ops->reason == OFPPR_MODIFY) {
        ds_put_format(string, " MOD:");
    }

    ofp_print_phy_port(string, &ops->desc);
}

static void
ofp_desc_stats_reply(struct ds *string, const void *body, size_t len,
                     int verbosity)
{
    const struct ofp_desc_stats *ods = body;

    ds_put_format(string, "Manufacturer: %s\n", ods->mfr_desc);
    ds_put_format(string, "Hardware: %s\n", ods->hw_desc);
    ds_put_format(string, "Software: %s\n", ods->sw_desc);
    ds_put_format(string, "Serial Num: %s\n", ods->serial_num);
}

static void
ofp_flow_stats_request(struct ds *string, const void *oh, size_t len,
                      int verbosity)
{
    const struct ofp_flow_stats_request *fsr = oh;

    if (fsr->table_id == 0xff) {
        ds_put_format(string, " table_id=any, ");
    } else {
        ds_put_format(string, " table_id=%"PRIu8", ", fsr->table_id);
    }

    ofp_print_match(string, &fsr->match, verbosity);
}

static void
ofp_flow_stats_reply(struct ds *string, const void *body_, size_t len,
                     int verbosity)
{
    const char *body = body_;
    const char *pos = body;
    for (;;) {
        const struct ofp_flow_stats *fs;
        ptrdiff_t bytes_left = body + len - pos;
        size_t length;

        if (bytes_left < sizeof *fs) {
            if (bytes_left != 0) {
                ds_put_format(string, " ***%td leftover bytes at end***",
                              bytes_left);
            }
            break;
        }

        fs = (const void *) pos;
        length = ntohs(fs->length);
        if (length < sizeof *fs) {
            ds_put_format(string, " ***length=%zu shorter than minimum %zu***",
                          length, sizeof *fs);
            break;
        } else if (length > bytes_left) {
            ds_put_format(string,
                          " ***length=%zu but only %td bytes left***",
                          length, bytes_left);
            break;
        } else if ((length - sizeof *fs) % sizeof fs->actions[0]) {
            ds_put_format(string,
                          " ***length=%zu has %zu bytes leftover in "
                          "final action***",
                          length,
                          (length - sizeof *fs) % sizeof fs->actions[0]);
            break;
        }

        ds_put_format(string, "  duration=%"PRIu32"s, ", ntohl(fs->duration));
        ds_put_format(string, "table_id=%"PRIu8", ", fs->table_id);
        ds_put_format(string, "priority=%"PRIu16", ",
                    fs->match.wildcards ? ntohs(fs->priority) : (uint16_t)-1);
        ds_put_format(string, "n_packets=%"PRIu64", ",
                    ntohll(fs->packet_count));
        ds_put_format(string, "n_bytes=%"PRIu64", ", ntohll(fs->byte_count));
        ds_put_format(string, "idle_timeout=%"PRIu16",",
                      ntohs(fs->idle_timeout));
        ds_put_format(string, "hard_timeout=%"PRIu16",",
                      ntohs(fs->hard_timeout));
        ofp_print_match(string, &fs->match, verbosity);
        ofp_print_actions(string, fs->actions, length - sizeof *fs);
        ds_put_char(string, '\n');

        pos += length;
     }
}

static void
ofp_aggregate_stats_request(struct ds *string, const void *oh, size_t len,
                            int verbosity)
{
    const struct ofp_aggregate_stats_request *asr = oh;

    if (asr->table_id == 0xff) {
        ds_put_format(string, " table_id=any, ");
    } else {
        ds_put_format(string, " table_id=%"PRIu8", ", asr->table_id);
    }

    ofp_print_match(string, &asr->match, verbosity);
}

static void
ofp_aggregate_stats_reply(struct ds *string, const void *body_, size_t len,
                          int verbosity)
{
    const struct ofp_aggregate_stats_reply *asr = body_;

    ds_put_format(string, " packet_count=%"PRIu64, ntohll(asr->packet_count));
    ds_put_format(string, " byte_count=%"PRIu64, ntohll(asr->byte_count));
    ds_put_format(string, " flow_count=%"PRIu32, ntohl(asr->flow_count));
}

static void print_port_stat(struct ds *string, const char *leader,
                            uint64_t stat, int more)
{
    ds_put_cstr(string, leader);
    if (stat != -1) {
        ds_put_format(string, "%"PRIu64, stat);
    } else {
        ds_put_char(string, '?');
    }
    if (more) {
        ds_put_cstr(string, ", ");
    } else {
        ds_put_cstr(string, "\n");
    }
}

static void
ofp_port_stats_reply(struct ds *string, const void *body, size_t len,
                     int verbosity)
{
    const struct ofp_port_stats *ps = body;
    size_t n = len / sizeof *ps;
    ds_put_format(string, " %zu ports\n", n);
    if (verbosity < 1) {
        return;
    }

    for (; n--; ps++) {
    	// MAH: start
        //ds_put_format(string, "  port %2"PRIu16": ", ntohs(ps->port_no));
    	ds_put_format(string, "  port %4"PRIu32": ", ntohl(ps->port_no));
        // MAH: end

        ds_put_cstr(string, "rx ");
        print_port_stat(string, "pkts=", ntohll(ps->rx_packets), 1);
        print_port_stat(string, "bytes=", ntohll(ps->rx_bytes), 1);
        print_port_stat(string, "drop=", ntohll(ps->rx_dropped), 1);
        print_port_stat(string, "errs=", ntohll(ps->rx_errors), 1);
        print_port_stat(string, "frame=", ntohll(ps->rx_frame_err), 1);
        print_port_stat(string, "over=", ntohll(ps->rx_over_err), 1);
        print_port_stat(string, "crc=", ntohll(ps->rx_crc_err), 0);

        ds_put_cstr(string, "           tx ");
        print_port_stat(string, "pkts=", ntohll(ps->tx_packets), 1);
        print_port_stat(string, "bytes=", ntohll(ps->tx_bytes), 1);
        print_port_stat(string, "drop=", ntohll(ps->tx_dropped), 1);
        print_port_stat(string, "errs=", ntohll(ps->tx_errors), 1);
        print_port_stat(string, "coll=", ntohll(ps->collisions), 1);
        // MAH: start
        print_port_stat(string, "mpls_ttl0_drop=", ntohll(ps->mpls_ttl0_dropped), 0);
        // MAH: end
    }
}

static void
ofp_table_stats_reply(struct ds *string, const void *body, size_t len,
                     int verbosity)
{
    const struct ofp_table_stats *ts = body;
    size_t n = len / sizeof *ts;
    ds_put_format(string, " %zu tables\n", n);
    if (verbosity < 1) {
        return;
    }

    for (; n--; ts++) {
        char name[OFP_MAX_TABLE_NAME_LEN + 1];
        strncpy(name, ts->name, sizeof name);
        name[OFP_MAX_TABLE_NAME_LEN] = '\0';

        ds_put_format(string, "  %d: %-8s: ", ts->table_id, name);
        ds_put_format(string, "wild=0x%05"PRIx32", ", ntohl(ts->wildcards));
        ds_put_format(string, "max=%6"PRIu32", ", ntohl(ts->max_entries));
        ds_put_format(string, "active=%"PRIu32"\n", ntohl(ts->active_count));
        ds_put_cstr(string, "               ");
        ds_put_format(string, "lookup=%"PRIu64", ",
                    ntohll(ts->lookup_count));
        ds_put_format(string, "matched=%"PRIu64"\n",
                    ntohll(ts->matched_count));
     }
}

// MAH: start
static void
ofp_port_table_stats_reply(struct ds *string, const void *body, size_t len,
                     int verbosity)
{
    const struct ofp_vport_table_stats *pts = body;
    ds_put_format(string, " port table statistics\n");
    if (verbosity < 1) {
        return;
    }

	ds_put_format(string, "max=%6"PRIu32", ", ntohl(pts->max_vports));
	ds_put_format(string, "active=%"PRIu32"\n", ntohl(pts->active_vports));
	ds_put_cstr(string, "               ");
	ds_put_format(string, "lookup=%"PRIu64", ",
				ntohll(pts->lookup_count));
	ds_put_format(string, "port_matches=%"PRIu64", ",
				ntohll(pts->port_match_count));
	ds_put_format(string, "chain_matches=%"PRIu64"\n",
				ntohll(pts->chain_match_count));
}
// MAH: end

static void
vendor_stat(struct ds *string, const void *body, size_t len,
            int verbosity UNUSED)
{
    ds_put_format(string, " vendor=%08"PRIx32, ntohl(*(uint32_t *) body));
    ds_put_format(string, " %zu bytes additional data",
                  len - sizeof(uint32_t));
}

enum stats_direction {
    REQUEST,
    REPLY
};

static void
print_stats(struct ds *string, int type, const void *body, size_t body_len,
            int verbosity, enum stats_direction direction)
{
    struct stats_msg {
        size_t min_body, max_body;
        void (*printer)(struct ds *, const void *, size_t len, int verbosity);
    };

    struct stats_type {
        int type;
        const char *name;
        struct stats_msg request;
        struct stats_msg reply;
    };

    static const struct stats_type stats_types[] = {
        {
            OFPST_DESC,
            "description",
            { 0, 0, NULL },
            { 0, SIZE_MAX, ofp_desc_stats_reply },
        },
        {
            OFPST_FLOW,
            "flow",
            { sizeof(struct ofp_flow_stats_request),
              sizeof(struct ofp_flow_stats_request),
              ofp_flow_stats_request },
            { 0, SIZE_MAX, ofp_flow_stats_reply },
        },
        {
            OFPST_AGGREGATE,
            "aggregate",
            { sizeof(struct ofp_aggregate_stats_request),
              sizeof(struct ofp_aggregate_stats_request),
              ofp_aggregate_stats_request },
            { sizeof(struct ofp_aggregate_stats_reply),
              sizeof(struct ofp_aggregate_stats_reply),
              ofp_aggregate_stats_reply },
        },
        {
            OFPST_TABLE,
            "table",
            { 0, 0, NULL },
            { 0, SIZE_MAX, ofp_table_stats_reply },
        },
        {
            OFPST_PORT,
            "port",
            // MAH: start
            //{ 0, 0, NULL, },
            { 0, SIZE_MAX, NULL, }, // body now supports a list of port numbers
            // MAH: end
            { 0, SIZE_MAX, ofp_port_stats_reply },
        },
        // MAH: start
        {
			OFPST_PORT_TABLE,
			"port_table",
			// MAH: start
			//{ 0, 0, NULL, },
			{ 0, sizeof(struct ofp_vport_table_stats), NULL, }, // body now supports a list of port numbers
			// MAH: end
			{ 0, sizeof(struct ofp_vport_table_stats), ofp_port_table_stats_reply },
		},
        // MAH: end
        {
            OFPST_VENDOR,
            "vendor-specific",
            { sizeof(uint32_t), SIZE_MAX, vendor_stat },
            { sizeof(uint32_t), SIZE_MAX, vendor_stat },
        },
        {
            -1,
            "unknown",
            { 0, 0, NULL, },
            { 0, 0, NULL, },
        },
    };

    const struct stats_type *s;
    const struct stats_msg *m;

    if (type >= ARRAY_SIZE(stats_types) || !stats_types[type].name) {
        ds_put_format(string, " ***unknown type %d***", type);
        return;
    }
    for (s = stats_types; s->type >= 0; s++) {
        if (s->type == type) {
            break;
        }
    }
    ds_put_format(string, " type=%d(%s)\n", type, s->name);

    m = direction == REQUEST ? &s->request : &s->reply;
    if (body_len < m->min_body || body_len > m->max_body) {
        ds_put_format(string, " ***body_len=%zu not in %zu...%zu***",
                      body_len, m->min_body, m->max_body);
        return;
    }
    if (m->printer) {
        m->printer(string, body, body_len, verbosity);
    }
}

static void
ofp_stats_request(struct ds *string, const void *oh, size_t len, int verbosity)
{
    const struct ofp_stats_request *srq = oh;

    if (srq->flags) {
        ds_put_format(string, " ***unknown flags 0x%04"PRIx16"***",
                      ntohs(srq->flags));
    }

    print_stats(string, ntohs(srq->type), srq->body,
                len - offsetof(struct ofp_stats_request, body),
                verbosity, REQUEST);
}

static void
ofp_stats_reply(struct ds *string, const void *oh, size_t len, int verbosity)
{
    const struct ofp_stats_reply *srp = oh;

    ds_put_cstr(string, " flags=");
    if (!srp->flags) {
        ds_put_cstr(string, "none");
    } else {
        uint16_t flags = ntohs(srp->flags);
        if (flags & OFPSF_REPLY_MORE) {
            ds_put_cstr(string, "[more]");
            flags &= ~OFPSF_REPLY_MORE;
        }
        if (flags) {
            ds_put_format(string, "[***unknown flags 0x%04"PRIx16"***]", flags);
        }
    }

    print_stats(string, ntohs(srp->type), srp->body,
                len - offsetof(struct ofp_stats_reply, body),
                verbosity, REPLY);
}

static void
ofp_echo(struct ds *string, const void *oh, size_t len, int verbosity)
{
    const struct ofp_header *hdr = oh;

    ds_put_format(string, " %zu bytes of payload\n", len - sizeof *hdr);
    if (verbosity > 1) {
        ds_put_hex_dump(string, hdr, len - sizeof *hdr, 0, true);
    }
}

struct openflow_packet {
    uint8_t type;
    const char *name;
    size_t min_size;
    void (*printer)(struct ds *, const void *, size_t len, int verbosity);
};

static const struct openflow_packet packets[] = {
    {
        OFPT_HELLO,
        "hello",
        sizeof (struct ofp_header),
        NULL,
    },
    {
        OFPT_FEATURES_REQUEST,
        "features_request",
        sizeof (struct ofp_header),
        NULL,
    },
    {
        OFPT_FEATURES_REPLY,
        "features_reply",
        sizeof (struct ofp_switch_features),
        ofp_print_switch_features,
    },
    // MAH: start
    {
    	OFPT_VPORT_TABLE_FEATURES_REQUEST,
    	"vport_table_features_request",
    	sizeof (struct ofp_header),
    	NULL,
    },
    {
    	OFPT_VPORT_TABLE_FEATURES_REPLY,
		"vport_table_features_reply",
		sizeof (struct ofp_vport_table_features),
		ofp_print_vport_table_features,
	},
    // MAH: end
    {
        OFPT_GET_CONFIG_REQUEST,
        "get_config_request",
        sizeof (struct ofp_header),
        NULL,
    },
    {
        OFPT_GET_CONFIG_REPLY,
        "get_config_reply",
        sizeof (struct ofp_switch_config),
        ofp_print_switch_config,
    },
    {
        OFPT_SET_CONFIG,
        "set_config",
        sizeof (struct ofp_switch_config),
        ofp_print_switch_config,
    },
    {
        OFPT_PACKET_IN,
        "packet_in",
        offsetof(struct ofp_packet_in, data),
        ofp_packet_in,
    },
    {
        OFPT_PACKET_OUT,
        "packet_out",
        sizeof (struct ofp_packet_out),
        ofp_packet_out,
    },
    {
        OFPT_FLOW_MOD,
        "flow_mod",
        sizeof (struct ofp_flow_mod),
        ofp_print_flow_mod,
    },
    {
        OFPT_FLOW_EXPIRED,
        "flow_expired",
        sizeof (struct ofp_flow_expired),
        ofp_print_flow_expired,
    },
    {
        OFPT_PORT_MOD,
        "port_mod",
        sizeof (struct ofp_port_mod),
        ofp_print_port_mod,
    },
    // MAH: start
    // add vport_mod
    {
        OFPT_VPORT_MOD,
        "vport_mod",
        sizeof (struct ofp_vport_mod),
        ofp_print_vport_mod,
    },
    // MAH: end
    {
        OFPT_PORT_STATUS,
        "port_status",
        sizeof (struct ofp_port_status),
        ofp_print_port_status
    },
    {
        OFPT_ERROR,
        "error_msg",
        sizeof (struct ofp_error_msg),
        ofp_print_error_msg,
    },
    {
        OFPT_STATS_REQUEST,
        "stats_request",
        sizeof (struct ofp_stats_request),
        ofp_stats_request,
    },
    {
        OFPT_STATS_REPLY,
        "stats_reply",
        sizeof (struct ofp_stats_reply),
        ofp_stats_reply,
    },
    {
        OFPT_ECHO_REQUEST,
        "echo_request",
        sizeof (struct ofp_header),
        ofp_echo,
    },
    {
        OFPT_ECHO_REPLY,
        "echo_reply",
        sizeof (struct ofp_header),
        ofp_echo,
    },
};

/* Composes and returns a string representing the OpenFlow packet of 'len'
 * bytes at 'oh' at the given 'verbosity' level.  0 is a minimal amount of
 * verbosity and higher numbers increase verbosity.  The caller is responsible
 * for freeing the string. */
char *
ofp_to_string(const void *oh_, size_t len, int verbosity)
{
    struct ds string = DS_EMPTY_INITIALIZER;
    const struct ofp_header *oh = oh_;
    const struct openflow_packet *pkt;

    if (len < sizeof(struct ofp_header)) {
        ds_put_cstr(&string, "OpenFlow packet too short:\n");
        ds_put_hex_dump(&string, oh, len, 0, true);
        return ds_cstr(&string);
    } else if (oh->version != OFP_VERSION) {
        ds_put_format(&string, "Bad OpenFlow version %"PRIu8":\n", oh->version);
        ds_put_hex_dump(&string, oh, len, 0, true);
        return ds_cstr(&string);
    }

    for (pkt = packets; ; pkt++) {
        if (pkt >= &packets[ARRAY_SIZE(packets)]) {
            ds_put_format(&string, "Unknown OpenFlow packet type %"PRIu8":\n",
                          oh->type);
            ds_put_hex_dump(&string, oh, len, 0, true);
            return ds_cstr(&string);
        } else if (oh->type == pkt->type) {
            break;
        }
    }

    ds_put_format(&string, "%s (xid=0x%"PRIx32"):", pkt->name, oh->xid);

    if (ntohs(oh->length) > len)
        ds_put_format(&string, " (***truncated to %zu bytes from %"PRIu16"***)",
                len, ntohs(oh->length));
    else if (ntohs(oh->length) < len) {
        ds_put_format(&string, " (***only uses %"PRIu16" bytes out of %zu***)\n",
                ntohs(oh->length), len);
        len = ntohs(oh->length);
    }

    if (len < pkt->min_size) {
        ds_put_format(&string, " (***length=%zu < min_size=%zu***)\n",
                len, pkt->min_size);
    } else if (!pkt->printer) {
        if (len > sizeof *oh) {
            ds_put_format(&string, " length=%"PRIu16" (decoder not implemented)\n",
                          ntohs(oh->length));
        }
    } else {
        pkt->printer(&string, oh, len, verbosity);
    }
    if (verbosity >= 3) {
        ds_put_hex_dump(&string, oh, len, 0, true);
    }
    if (string.string[string.length - 1] != '\n') {
        ds_put_char(&string, '\n');
    }
    return ds_cstr(&string);
}

static void
print_and_free(FILE *stream, char *string)
{
    fputs(string, stream);
    free(string);
}

/* Pretty-print the OpenFlow packet of 'len' bytes at 'oh' to 'stream' at the
 * given 'verbosity' level.  0 is a minimal amount of verbosity and higher
 * numbers increase verbosity. */
void
ofp_print(FILE *stream, const void *oh, size_t len, int verbosity)
{
    print_and_free(stream, ofp_to_string(oh, len, verbosity));
}

/* Dumps the contents of the Ethernet frame in the 'len' bytes starting at
 * 'data' to 'stream' using tcpdump.  'total_len' specifies the full length of
 * the Ethernet frame (of which 'len' bytes were captured).
 *
 * This starts and kills a tcpdump subprocess so it's quite expensive. */
void
ofp_print_packet(FILE *stream, const void *data, size_t len, size_t total_len)
{
    print_and_free(stream, ofp_packet_to_string(data, len, total_len));
}
