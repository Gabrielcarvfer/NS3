// MAH: start
// Similar to the Learning-Switch.{c,h}, this defines a representation for
// an MPLS-enabled OpenFlow switch used by the controller
#ifndef MPLS_SWITCH_H
#define MPLS_SWITCH_H 1

#include <stdbool.h>
#include "freelist.h"

struct ofpbuf;
struct rconn;
struct mpls_fib;
struct mpls_switch_operations;

struct mpls_switch {
    /* If nonnegative, the switch sets up flows that expire after the given
     * number of seconds (or never expire, if the value is OFP_FLOW_PERMANENT).
     * Otherwise, the switch processes every packet. */
    int max_idle;

    freeListPtr vports;

    // the switches MPLS forwarding information
    mplsFibPtr mplsFibTable;

    // which option should be used for each MPLS operation
	struct mpls_switch_operations mplsSwitchOps;

    unsigned long long int datapath_id;
    uint32_t capabilities;
    uint32_t flow_actions;
    uint32_t vport_actions;
    time_t last_features_request;

    /* Number of outgoing queued packets on the rconn. */
    int n_queued;

    uint32_t query_xid;         /* XID used for query. */
    int n_flows, n_no_recv, n_no_send;
};

static inline uint32_t alloc_vport(freeListPtr list) {
	return OFPP_VP_START + alloc_entry(list);
}

static inline void free_vport(freeListPtr list, uint32_t vport)
{
	free_entry(list, vport + OFPP_VP_START);
}

void queue_tx(struct mpls_switch *, struct rconn *, struct ofpbuf *);

struct mpls_switch *mpls_switch_create(struct rconn *);
void mpls_switch_run(struct mpls_switch *, struct rconn *);
void mpls_switch_wait(struct mpls_switch *);
void mpls_switch_destroy(struct mpls_switch *);
void mpls_switch_process_packet(struct mpls_switch *, struct rconn *,
								const struct ofpbuf *);

#endif

// MAH: end
