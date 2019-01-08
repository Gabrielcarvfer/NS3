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
#include "switch-flow.h"
#include <arpa/inet.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "ofpbuf.h"
#include "openflow/openflow.h"
#include "packets.h"
#include "timeval.h"

/* Internal function used to compare fields in flow. */
static inline int
flow_fields_match(const struct flow *a, const struct flow *b, uint16_t w,
                  uint32_t src_mask, uint32_t dst_mask)
{
//	print_flow_(a, w);
	//print_flow_(b, w);
    return ((w & OFPFW_IN_PORT || a->in_port == b->in_port)
            && (w & OFPFW_DL_VLAN || a->dl_vlan == b->dl_vlan)
            && (w & OFPFW_DL_SRC || eth_addr_equals(a->dl_src, b->dl_src))
            && (w & OFPFW_DL_DST || eth_addr_equals(a->dl_dst, b->dl_dst))
            && (w & OFPFW_DL_TYPE || a->dl_type == b->dl_type)
            && !((a->nw_src ^ b->nw_src) & src_mask)
            && !((a->nw_dst ^ b->nw_dst) & dst_mask)
            && (w & OFPFW_NW_PROTO || a->nw_proto == b->nw_proto)
            && (w & OFPFW_TP_SRC || a->tp_src == b->tp_src)
            && (w & OFPFW_TP_DST || a->tp_dst == b->tp_dst)
    // MAH: start
    // match on the 2 MPLS labels as well
    // use a wildcard for label 2 when there is only one MPLS label
            ///);
            && (w & OFPFW_MPLS_L1 || a->mpls_label1 == b->mpls_label1)
            && (w & OFPFW_MPLS_L2 || a->mpls_label2 == b->mpls_label2));
    // MAH: end

}

static uint32_t make_nw_mask(int n_wild_bits)
{
    n_wild_bits &= (1u << OFPFW_NW_SRC_BITS) - 1;
    return n_wild_bits < 32 ? htonl(~((1u << n_wild_bits) - 1)) : 0;
}

/* Returns nonzero if 'a' and 'b' match, that is, if their fields are equal
 * modulo wildcards in 'b', zero otherwise. */
inline int
flow_matches_1wild(const struct sw_flow_key *a, const struct sw_flow_key *b)
{
    return flow_fields_match(&a->flow, &b->flow, b->wildcards,
                             b->nw_src_mask, b->nw_dst_mask);
}

/* Returns nonzero if 'a' and 'b' match, that is, if their fields are equal
 * modulo wildcards in 'a' or 'b', zero otherwise. */
inline int
flow_matches_2wild(const struct sw_flow_key *a, const struct sw_flow_key *b)
{
    return flow_fields_match(&a->flow, &b->flow, a->wildcards | b->wildcards,
                             a->nw_src_mask & b->nw_src_mask,
                             a->nw_dst_mask & b->nw_dst_mask);
}

/* Returns nonzero if 't' (the table entry's key) and 'd' (the key
 * describing the match) match, that is, if their fields are
 * equal modulo wildcards, zero otherwise.  If 'strict' is nonzero, the
 * wildcards must match in both 't_key' and 'd_key'.  Note that the
 * table's wildcards are ignored unless 'strict' is set. */
int
flow_matches_desc(const struct sw_flow_key *t, const struct sw_flow_key *d,
        int strict)
{
    if (strict && d->wildcards != t->wildcards) {
        return 0;
    }
    return flow_matches_1wild(t, d);
}

void
flow_extract_match(struct sw_flow_key* to, const struct ofp_match* from)
{
    to->wildcards = ntohl(from->wildcards) & OFPFW_ALL;
    // MAH: start
    // by default wild card the MPLS fields and only set them to
    // 0 when we have valid MPLS labels
    to->wildcards |= OFPFW_MPLS_L1 | OFPFW_MPLS_L2;
    // MAH: end
    to->flow.reserved = 0;
    to->flow.in_port = from->in_port;
    to->flow.dl_vlan = from->dl_vlan;
    memcpy(to->flow.dl_src, from->dl_src, ETH_ADDR_LEN);
    memcpy(to->flow.dl_dst, from->dl_dst, ETH_ADDR_LEN);
    to->flow.dl_type = from->dl_type;

    // MAH: start
    to->flow.mpls_label1 = from->mpls_label1;
    to->flow.mpls_label2 = from->mpls_label2;
    // MAH: end

    to->flow.nw_src = to->flow.nw_dst = to->flow.nw_proto = 0;
    to->flow.tp_src = to->flow.tp_dst = 0;



#define OFPFW_TP (OFPFW_TP_SRC | OFPFW_TP_DST)
#define OFPFW_NW (OFPFW_NW_SRC_MASK | OFPFW_NW_DST_MASK | OFPFW_NW_PROTO)
    if (to->wildcards & OFPFW_DL_TYPE) {
        /* Can't sensibly match on network or transport headers if the
         * data link type is unknown. */
        to->wildcards |= OFPFW_NW | OFPFW_TP;
    } else if (from->dl_type == htons(ETH_TYPE_IP)) {
        to->flow.nw_src   = from->nw_src;
        to->flow.nw_dst   = from->nw_dst;
        to->flow.nw_proto = from->nw_proto;

        if (to->wildcards & OFPFW_NW_PROTO) {
            /* Can't sensibly match on transport headers if the network
             * protocol is unknown. */
            to->wildcards |= OFPFW_TP;
        } else if (from->nw_proto == IPPROTO_TCP
                || from->nw_proto == IPPROTO_UDP
                || from->nw_proto == IPPROTO_ICMP) {
            to->flow.tp_src = from->tp_src;
            to->flow.tp_dst = from->tp_dst;
        } else {
            /* Transport layer fields are undefined.  Mark them as
             * exact-match to allow such flows to reside in table-hash,
             * instead of falling into table-linear. */
            to->wildcards &= ~OFPFW_TP;
        }

    // MAH: start
    // If packet is MPLS, we include up to the fist 2 labels
    // from the label stack
    } else if (from->dl_type == htons(ETH_TYPE_MPLS_UNICAST)) {

    	// just assume that there is a second label
    	// the second will be wildcarded if we match on only one
    	to->wildcards &= ~OFPFW_MPLS_L1;
    	if (ntohl(to->flow.mpls_label1) >= 0x00100000) {
    		printf("Invalid first MPLS label %x\n", to->flow.mpls_label1);
    	}
    	// a value > 2^20 means mpls_label2 is not valid
    	// so set the mask bit
    	if (ntohl(to->flow.mpls_label2) < 0x00100000) {
    		to->wildcards &= ~OFPFW_MPLS_L2;
    	}
    	// wildcard remaining headers
    	to->wildcards |= OFPFW_NW | OFPFW_TP;
    // MAH: end

    } else {
        /* Network and transport layer fields are undefined.  Mark them
         * as exact-match to allow such flows to reside in table-hash,
         * instead of falling into table-linear. */
        to->wildcards &= ~(OFPFW_NW | OFPFW_TP);
    }

	/* We set these late because code above adjusts to->wildcards. */
	to->nw_src_mask = make_nw_mask(to->wildcards >> OFPFW_NW_SRC_SHIFT);
	to->nw_dst_mask = make_nw_mask(to->wildcards >> OFPFW_NW_DST_SHIFT);
}

void
flow_fill_match(struct ofp_match* to, const struct sw_flow_key* from)
{
    to->wildcards = htonl(from->wildcards);
    to->in_port   = from->flow.in_port;
    to->dl_vlan   = from->flow.dl_vlan;
    memcpy(to->dl_src, from->flow.dl_src, ETH_ADDR_LEN);
    memcpy(to->dl_dst, from->flow.dl_dst, ETH_ADDR_LEN);
    to->dl_type   = from->flow.dl_type;
    to->nw_src        = from->flow.nw_src;
    to->nw_dst        = from->flow.nw_dst;
    // MAH: start
    to->mpls_label1	  = from->flow.mpls_label1;
    to->mpls_label2   = from->flow.mpls_label2;
    // MAH: end
    to->nw_proto  = from->flow.nw_proto;
    to->tp_src        = from->flow.tp_src;
    to->tp_dst        = from->flow.tp_dst;
    to->pad           = 0;
}

/* Allocates and returns a new flow with room for 'actions_len' actions.
 * Returns the new flow or a null pointer on failure. */
struct sw_flow *
flow_alloc(size_t actions_len)
{
    struct sw_flow_actions *sfa;
    size_t size = sizeof *sfa + actions_len;
    struct sw_flow *flow = malloc(sizeof *flow);
    if (!flow)
        return NULL;

    sfa = malloc(size);
    if (!sfa) {
        free(flow);
        return NULL;
    }
    sfa->actions_len = actions_len;
    flow->sf_acts = sfa;
    return flow;
}

/* Frees 'flow' immediately. */
void
flow_free(struct sw_flow *flow)
{
    if (!flow) {
        return;
    }
    free(flow->sf_acts);
    free(flow);
}

/* Copies 'actions' into a newly allocated structure for use by 'flow'
 * and frees the structure that defined the previous actions. */
void flow_replace_acts(struct sw_flow *flow,
        const struct ofp_action_header *actions, size_t actions_len)
{
    struct sw_flow_actions *sfa;
    int size = sizeof *sfa + actions_len;

    sfa = malloc(size);
    if (unlikely(!sfa))
        return;

    sfa->actions_len = actions_len;
    memcpy(sfa->actions, actions, actions_len);

    free(flow->sf_acts);
    flow->sf_acts = sfa;

    return;
}

// MAH: start
/*
print_flow(const struct flow *f)
{
    const struct flow *f = &key->flow;
    printf("wild%08x port%04x:vlan%04x mac%02x:%02x:%02x:%02x:%02x:%02x"
           "->%02x:%02x:%02x:%02x:%02x:%02x"
           "proto%04x ip%u.%u.%u.%u->%u.%u.%u.%u port%d->%d\n",
           key->wildcards, ntohs(f->in_port), ntohs(f->dl_vlan),
           f->dl_src[0], f->dl_src[1], f->dl_src[2],
           f->dl_src[3], f->dl_src[4], f->dl_src[5],
           f->dl_dst[0], f->dl_dst[1], f->dl_dst[2],
           f->dl_dst[3], f->dl_dst[4], f->dl_dst[5],
           ntohs(f->dl_type),
           ((unsigned char *)&f->nw_src)[0],
           ((unsigned char *)&f->nw_src)[1],
           ((unsigned char *)&f->nw_src)[2],
           ((unsigned char *)&f->nw_src)[3],
           ((unsigned char *)&f->nw_dst)[0],
           ((unsigned char *)&f->nw_dst)[1],
           ((unsigned char *)&f->nw_dst)[2],
           ((unsigned char *)&f->nw_dst)[3],
           ntohs(f->tp_src), ntohs(f->tp_dst));
}
*/

/* Prints a representation of 'key' to the kernel log. */
void print_flow(const struct sw_flow_key *key)
{
	const struct flow *f = &key->flow;
	print_flow_(f, key->wildcards);
}

void
print_flow_(const struct flow *f, uint32_t wildcards)
{
	    printf("wild%08x port%04x:vlan%04x mac%02x:%02x:%02x:%02x:%02x:%02x"
	           "->%02x:%02x:%02x:%02x:%02x:%02x mpls_l1:%05x mpls_l2:%05x "
	           "proto%04x ip%u.%u.%u.%u->%u.%u.%u.%u port%d->%d\n",
	           wildcards, ntohs(f->in_port), ntohs(f->dl_vlan),
	           f->dl_src[0], f->dl_src[1], f->dl_src[2],
	           f->dl_src[3], f->dl_src[4], f->dl_src[5],
	           f->dl_dst[0], f->dl_dst[1], f->dl_dst[2],
	           f->dl_dst[3], f->dl_dst[4], f->dl_dst[5],
	           ntohl(f->mpls_label1), ntohl(f->mpls_label2),
	           ntohs(f->dl_type),
	           ((unsigned char *)&f->nw_src)[0],
	           ((unsigned char *)&f->nw_src)[1],
	           ((unsigned char *)&f->nw_src)[2],
	           ((unsigned char *)&f->nw_src)[3],
	           ((unsigned char *)&f->nw_dst)[0],
	           ((unsigned char *)&f->nw_dst)[1],
	           ((unsigned char *)&f->nw_dst)[2],
	           ((unsigned char *)&f->nw_dst)[3],
	           ntohs(f->tp_src), ntohs(f->tp_dst));
}
// MAH: end

bool flow_timeout(struct sw_flow *flow)
{
    time_t now = time_now();
    if (flow->idle_timeout != OFP_FLOW_PERMANENT
        && now > flow->used + flow->idle_timeout) {
        flow->reason = OFPER_IDLE_TIMEOUT;
        return true;
    } else if (flow->hard_timeout != OFP_FLOW_PERMANENT
               && now > flow->created + flow->hard_timeout) {
        flow->reason = OFPER_HARD_TIMEOUT;
        return true;
    } else {
        return false;
    }
}

/* Returns nonzero if 'flow' contains an output action to 'out_port' or
 * has the value OFPP_NONE. 'out_port' is in network-byte order. */
int flow_has_out_port(struct sw_flow *flow, uint16_t out_port)
{
    struct sw_flow_actions *sf_acts = flow->sf_acts;
    size_t actions_len = sf_acts->actions_len;
    uint8_t *p = (uint8_t *)sf_acts->actions;

    if (out_port == htons(OFPP_NONE))
        return 1;

    while (actions_len > 0) {
        struct ofp_action_header *ah = (struct ofp_action_header *)p;
        size_t len = ntohs(ah->len);

        if (ah->type == htons(OFPAT_OUTPUT)) {
            struct ofp_action_output *oa = (struct ofp_action_output *)p;
            if (oa->port == out_port) {
                return 1;
            }
        }
        p += len;
        actions_len -= len;
    }

    return 0;
}

void flow_used(struct sw_flow *flow, struct ofpbuf *buffer)
{
    flow->used = time_now();
    flow->packet_count++;
    flow->byte_count += buffer->size;
}
