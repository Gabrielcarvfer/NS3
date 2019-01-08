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

/* Interface exported by OpenFlow module. */

#ifndef DATAPATH_H
#define DATAPATH_H 1

#include <stdbool.h>
#include <stdint.h>
#include "ofpbuf.h"
// MAH: start
#include "switch-port.h"
// MAH: end

struct datapath;
struct rconn;
struct pvconn;

// MAH: start
// moved all of the following from datapath.c
#include "flow.h"
#include "list.h"
#include "openflow/openflow.h"
#include "packets.h"
#include "timeval.h"

/* Capabilities supported by this implementation. */
// MAH: start
// switch supports a virtual port table
/*#define OFP_SUPPORTED_CAPABILITIES ( OFPC_FLOW_STATS \
        | OFPC_TABLE_STATS \
        | OFPC_PORT_STATS \
        | OFPC_MULTI_PHY_TX )
*/
#define OFP_SUPPORTED_CAPABILITIES ( OFPC_FLOW_STATS \
        | OFPC_TABLE_STATS \
        | OFPC_PORT_STATS \
        | OFPC_MULTI_PHY_TX \
        | OFPC_VPORT_TABLE)
// MAH: end

/* Actions supported by this implementation. */
#define OFP_SUPPORTED_ACTIONS ( (1 << OFPAT_OUTPUT)         \
                                | (1 << OFPAT_SET_VLAN_VID) \
                                | (1 << OFPAT_SET_VLAN_PCP) \
                                | (1 << OFPAT_STRIP_VLAN)   \
                                | (1 << OFPAT_SET_DL_SRC)   \
                                | (1 << OFPAT_SET_DL_DST)   \
                                | (1 << OFPAT_SET_NW_SRC)   \
                                | (1 << OFPAT_SET_NW_DST)   \
                                | (1 << OFPAT_SET_TP_SRC)   \
                                | (1 << OFPAT_SET_TP_DST) 	\
								| (1 << OFPAT_SET_MPLS_LABEL) \
								| (1 << OFPAT_SET_MPLS_EXP) )
// MAH: start
// added OFPAT_SET_MPLS_LABEL & OFPAT_SET_MPLS_EXP above
// MAH: end
// MAH: start
#define OFP_SUPPORTED_VPORT_TABLE_ACTIONS ( (1 << OFPPAT_OUTPUT) \
								| (1 << OFPPAT_POP_MPLS) \
								| (1 << OFPPAT_PUSH_MPLS) \
								| (1 << OFPPAT_SET_MPLS_LABEL) \
								| (1 << OFPPAT_SET_MPLS_EXP) ) \
// MAH: end

struct sw_port {
    uint32_t config;            /* Some subset of OFPPC_* flags. */
    uint32_t state;             /* Some subset of OFPPS_* flags. */
    struct datapath *dp;
    struct netdev *netdev;
    struct list node; /* Element in datapath.ports. */
    unsigned long long int rx_packets, tx_packets;
    unsigned long long int rx_bytes, tx_bytes;
    unsigned long long int tx_dropped;
    // MAH: start
    unsigned long long int mpls_ttl0_dropped;
    // MAH: end
};

/* The origin of a received OpenFlow message, to enable sending a reply. */
struct sender {
    struct remote *remote;      /* The device that sent the message. */
    uint32_t xid;               /* The OpenFlow transaction ID. */
};

/* A connection to a controller or a management device. */
struct remote {
    struct list node;
    struct rconn *rconn;
#define TXQ_LIMIT 128           /* Max number of packets to queue for tx. */
    int n_txq;                  /* Number of packets queued for tx on rconn. */

    /* Support for reliable, multi-message replies to requests.
     *
     * If an incoming request needs to have a reliable reply that might
     * require multiple messages, it can use remote_start_dump() to set up
     * a callback that will be called as buffer space for replies. */
    int (*cb_dump)(struct datapath *, void *aux);
    void (*cb_done)(void *aux);
    void *cb_aux;
};

#define DP_MAX_PORTS 255
BUILD_ASSERT_DECL(DP_MAX_PORTS <= OFPP_MAX);

struct datapath {
    /* Remote connections. */
    struct remote *controller;  /* Connection to controller. */
    struct list remotes;        /* All connections (including controller). */
    struct pvconn *listen_pvconn;

    time_t last_timeout;

    /* Unique identifier for this datapath */
    uint64_t  id;

    struct sw_chain *chain;  /* Forwarding rules. */

    /* Configuration set from controller. */
    uint16_t flags;
    uint16_t miss_send_len;

    /* Switch ports. */
    struct sw_port ports[DP_MAX_PORTS];
    struct list port_list; /* List of ports, for flooding. */

    // MAH: start
    /* Virtual ports. */
    struct vport_table_t vport_table;
    // MAH: end

};
// MAH: end


int dp_new(struct datapath **, uint64_t dpid, struct rconn *);
int dp_add_port(struct datapath *, const char *netdev);
void dp_add_listen_pvconn(struct datapath *, struct pvconn *);
void dp_run(struct datapath *);
void dp_wait(struct datapath *);
void dp_output_port(struct datapath *, struct ofpbuf *, int in_port,
        int out_port, bool ignore_no_fwd);
void dp_output_control(struct datapath *, struct ofpbuf *, int in_port,
        size_t max_len, int reason);

#endif /* datapath.h */
