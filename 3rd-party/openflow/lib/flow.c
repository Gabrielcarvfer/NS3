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
#include <sys/types.h>
#include "flow.h"
#include <inttypes.h>
#include <netinet/in.h>
#include <string.h>
#include "hash.h"
#include "ofpbuf.h"
#include "openflow/openflow.h"
#include "packets.h"

#include "vlog.h"
#define THIS_MODULE VLM_flow

// MAH: start
// function below grabs the MPLS label(s)
static mpls_header *
pull_mpls(struct ofpbuf *packet)
{
	return ofpbuf_try_pull(packet, MPLS_HEADER_LEN);
}
// MAH: end

static struct ip_header *
pull_ip(struct ofpbuf *packet)
{
    if (packet->size >= IP_HEADER_LEN) {
        struct ip_header *ip = packet->data;
        int ip_len = IP_IHL(ip->ip_ihl_ver) * 4;
        if (ip_len >= IP_HEADER_LEN && packet->size >= ip_len) {
            return ofpbuf_pull(packet, ip_len);
        }
    }
    return NULL;
}

static struct tcp_header *
pull_tcp(struct ofpbuf *packet)
{
    if (packet->size >= TCP_HEADER_LEN) {
        struct tcp_header *tcp = packet->data;
        int tcp_len = TCP_OFFSET(tcp->tcp_ctl) * 4;
        if (tcp_len >= TCP_HEADER_LEN && packet->size >= tcp_len) {
            return ofpbuf_pull(packet, tcp_len);
        }
    }
    return NULL;
}

static struct udp_header *
pull_udp(struct ofpbuf *packet)
{
    return ofpbuf_try_pull(packet, UDP_HEADER_LEN);
}

static struct icmp_header *
pull_icmp(struct ofpbuf *packet)
{
    return ofpbuf_try_pull(packet, ICMP_HEADER_LEN);
}

static struct eth_header *
pull_eth(struct ofpbuf *packet)
{
    return ofpbuf_try_pull(packet, ETH_HEADER_LEN);
}

static struct vlan_header *
pull_vlan(struct ofpbuf *packet)
{
    return ofpbuf_try_pull(packet, VLAN_HEADER_LEN);
}

/* Returns 1 if 'packet' is an IP fragment, 0 otherwise. */
int
flow_extract(struct ofpbuf *packet, uint16_t in_port, struct flow *flow)
{
    struct ofpbuf b = *packet;
    struct eth_header *eth;
    int retval = 0;
    // MAH: start
    mpls_header mpls_h;
    // MAH: end

    if (b.size < ETH_TOTAL_MIN) {
        /* This message is not too useful since there are various ways that we
         * can end up with runt frames, e.g. frames that only ever passed
         * through virtual network devices and never touched a physical
         * Ethernet. */
        static struct vlog_rate_limit rl = VLOG_RATE_LIMIT_INIT(5, 60);
        VLOG_DBG_RL(&rl, "packet length %zu less than minimum size %d",
                    b.size, ETH_TOTAL_MIN);
    }

    memset(flow, 0, sizeof *flow);
    flow->dl_vlan = htons(OFP_VLAN_NONE);
    flow->in_port = htons(in_port);

    packet->l2 = b.data;
    packet->l3 = NULL;
    packet->l4 = NULL;
    packet->l7 = NULL;

    eth = pull_eth(&b);
    if (eth) {
        if (ntohs(eth->eth_type) >= OFP_DL_TYPE_ETH2_CUTOFF) {
            /* This is an Ethernet II frame */
            flow->dl_type = eth->eth_type;
        } else {
            /* This is an 802.2 frame */
            struct llc_snap_header *h = ofpbuf_at(&b, 0, sizeof *h);
            if (h == NULL) {
                return 0;
            }
            if (h->llc.llc_dsap == LLC_DSAP_SNAP
                && h->llc.llc_ssap == LLC_SSAP_SNAP
                && h->llc.llc_cntl == LLC_CNTL_SNAP
                && !memcmp(h->snap.snap_org, SNAP_ORG_ETHERNET,
                           sizeof h->snap.snap_org)) {
                flow->dl_type = h->snap.snap_type;
                ofpbuf_pull(&b, sizeof *h);
            } else {
                flow->dl_type = htons(OFP_DL_TYPE_NOT_ETH_TYPE);
                ofpbuf_pull(&b, sizeof(struct llc_header));
            }
        }

        /* Check for a VLAN tag */
        if (flow->dl_type == htons(ETH_TYPE_VLAN)) {
            struct vlan_header *vh = pull_vlan(&b);
            if (vh) {
                flow->dl_type = vh->vlan_next_type;
                flow->dl_vlan = vh->vlan_tci & htons(VLAN_VID_MASK);
            }
        }
        memcpy(flow->dl_src, eth->eth_src, ETH_ADDR_LEN);
        memcpy(flow->dl_dst, eth->eth_dst, ETH_ADDR_LEN);

        // MAH: start
        // If the packet is MPLS, the flow can include up to the first 2 MPLS labels in the
        // packet's label stack
        // Note that out of convenience we keep the MPLS labels in host byte order
        packet->l2_5 = b.data; // if no MPLS header l2.5 will = l3
        flow->mpls_label1 = htonl(MPLS_INVALID_LABEL);
        flow->mpls_label2 = htonl(MPLS_INVALID_LABEL);
        if (flow->dl_type == htons(ETH_TYPE_MPLS_UNICAST)) {
           mpls_h.value = ntohl(pull_mpls(&b)->value);
           flow->mpls_label1 = htonl(mpls_h.label);
           if (!(mpls_h.s)) {// another label exists
        	   mpls_h.value = ntohl(pull_mpls(&b)->value);
        	   flow->mpls_label2 = htonl(mpls_h.label);
           }
           // move past the remaining labels to get to l3
           while(!mpls_h.s) {
        	   mpls_h.value = ntohl(pull_mpls(&b)->value);
           }
        }
        packet->l3 = b.data;
        // MAH: end
        // MAH: start
        // Since the ethertype is MPLS we don't know whether layer 3 is IP or not
        // assume it is and fill out the rest of the key accordingly and if it's not IP
        // the fields will be garbage so the controller will need to wildcard the fields
        //if (flow->dl_type == htons(ETH_TYPE_IP)) {
        if (flow->dl_type == htons(ETH_TYPE_IP) ||
			flow->dl_type == htons(ETH_TYPE_MPLS_UNICAST)) {
        // MAH: end
            const struct ip_header *nh = pull_ip(&b);
            if (nh) {
                flow->nw_src = nh->ip_src;
                flow->nw_dst = nh->ip_dst;
                flow->nw_proto = nh->ip_proto;
                packet->l4 = b.data;
                if (!IP_IS_FRAGMENT(nh->ip_frag_off)) {
                    if (flow->nw_proto == IP_TYPE_TCP) {
                        const struct tcp_header *tcp = pull_tcp(&b);
                        if (tcp) {
                            flow->tp_src = tcp->tcp_src;
                            flow->tp_dst = tcp->tcp_dst;
                            packet->l7 = b.data;
                        } else {
                            /* Avoid tricking other code into thinking that
                             * this packet has an L4 header. */
                            flow->nw_proto = 0;
                        }
                    } else if (flow->nw_proto == IP_TYPE_UDP) {
                        const struct udp_header *udp = pull_udp(&b);
                        if (udp) {
                            flow->tp_src = udp->udp_src;
                            flow->tp_dst = udp->udp_dst;
                            packet->l7 = b.data;
                        } else {
                            /* Avoid tricking other code into thinking that
                             * this packet has an L4 header. */
                            flow->nw_proto = 0;
                        }
                    } else if (flow->nw_proto == IP_TYPE_ICMP) {
                        const struct icmp_header *icmp = pull_icmp(&b);
                        if (icmp) {
                            flow->icmp_type = htons(icmp->icmp_type);
                            flow->icmp_code = htons(icmp->icmp_code);
                            packet->l7 = b.data;
                        } else {
                            /* Avoid tricking other code into thinking that
                             * this packet has an L4 header. */
                            flow->nw_proto = 0;
                        }
                    }
                } else {
                    retval = 1;
                }
            }
        }
    }
    return retval;
}

void
flow_print(FILE *stream, const struct flow *flow)
{
    fprintf(stream,
            "port%04x:vlan%04x mac"ETH_ADDR_FMT"->"ETH_ADDR_FMT" "
            "proto%04x ip"IP_FMT"->"IP_FMT" port%d->%d",
            ntohs(flow->in_port), ntohs(flow->dl_vlan),
            ETH_ADDR_ARGS(flow->dl_src), ETH_ADDR_ARGS(flow->dl_dst),
            ntohs(flow->dl_type),
            IP_ARGS(&flow->nw_src), IP_ARGS(&flow->nw_dst),
            ntohs(flow->tp_src), ntohs(flow->tp_dst));
    // MAH: start
    // Note that MPLS labels are kept in host byte order
    // print MPLS labels.
    if (flow->mpls_label2 >= 0x100000){
    	// No valid second mpls label
    	fprintf(stream, " mpls_l1 %u mpls_l2 NONE ", flow->mpls_label1);
    } else {
    	fprintf(stream, " mpls_l1 %u mpls_l2 %u ", flow->mpls_label1, flow->mpls_label2);
    }
    // MAH: end
}

int
flow_compare(const struct flow *a, const struct flow *b)
{
    return memcmp(a, b, sizeof *a);
}

unsigned long int
flow_hash(const struct flow *flow, uint32_t basis)
{
    return hash_fnv(flow, sizeof *flow, basis);
}
