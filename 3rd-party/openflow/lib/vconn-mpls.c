// MAH: start
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <arpa/inet.h>
#include "packets.h"
#include "openflow/openflow.h"
#include "openflow/ericsson-ext.h"
#include "flow.h"
#include "ofpbuf.h"
#include "vconn-mpls.h"



struct ofpbuf *
make_add_mpls_flow(const struct ofp_match *match, uint32_t buffer_id,
              uint16_t idle_timeout, size_t actions_len)
{
	// generate the OpenFlow message to install a flow for MPLS
    struct ofp_flow_mod *ofm;
    size_t size = sizeof *ofm + actions_len;
    struct ofpbuf *out = ofpbuf_new(size);
    ofm = ofpbuf_put_zeros(out, size);
    ofm->header.version = OFP_VERSION;
    ofm->header.type = OFPT_FLOW_MOD;
    ofm->header.length = htons(size);
    ofm->match.in_port = match->in_port;
    memcpy(ofm->match.dl_src, match->dl_src, sizeof ofm->match.dl_src);
    memcpy(ofm->match.dl_dst, match->dl_dst, sizeof ofm->match.dl_dst);
    ofm->match.dl_vlan = match->dl_vlan;
    ofm->match.dl_type = match->dl_type;
    ofm->match.nw_src = match->nw_src;
    ofm->match.nw_dst = match->nw_dst;
    ofm->match.nw_proto = match->nw_proto;
    ofm->match.tp_src = match->tp_src;
    ofm->match.tp_dst = match->tp_dst;
    ofm->match.mpls_label1 = match->mpls_label1;
    ofm->match.mpls_label2 = match->mpls_label2;
    ofm->match.wildcards = match->wildcards;
    ofm->command = htons(OFPFC_ADD);
    ofm->idle_timeout = htons(idle_timeout);
    ofm->hard_timeout = htons(OFP_FLOW_PERMANENT);
    ofm->buffer_id = htonl(buffer_id);

    return out;
}


struct ofpbuf *
add_mpls_flow_entry(const struct ofp_match *match, uint32_t buffer_id,
				  uint16_t idle_timeout, void *actions, uint32_t actions_len)
{
	struct ofp_flow_mod *ofm;
	struct ofpbuf *buffer;

	buffer = make_add_mpls_flow(match, buffer_id, idle_timeout, actions_len);
	ofm = buffer->data;
    memcpy(ofm->actions, actions, actions_len);

    return buffer;
}


struct ofpbuf *
add_mpls_vport_entry(uint32_t vport, uint32_t parent_port,
					 void *actions, uint32_t actions_len)
{
	struct ofp_vport_mod *ovpm;
    struct ofpbuf *buffer;
    size_t size;

    size = sizeof *ovpm + actions_len;
    buffer = ofpbuf_new(size);
    ovpm = ofpbuf_put_zeros(buffer, size);
    ovpm->header.version = OFP_VERSION;
    ovpm->header.type = OFPT_VPORT_MOD;
    ovpm->header.length = htons(size);
    ovpm->vport = htonl(vport);
    ovpm->parent_port = htonl(parent_port);
	ovpm->command = htons(OFPVP_ADD);
	memcpy(ovpm->actions, actions, actions_len);

    return buffer;
}

struct ofpbuf *
rem_flow_entry(const struct ofp_match *match)
{
	struct ofp_flow_mod *ofm;
	struct ofpbuf *buffer;

    buffer = make_add_mpls_flow(match, 0, 0, 0);

    // first pop action;
    ofm = buffer->data;
    ofm->command = htons(OFPFC_DELETE);
	ofm->buffer_id = 0; // not meaningful for delete
    ofm->out_port = htons(OFPP_NONE);

    return buffer;
}

struct ofpbuf *
rem_vport_entry(uint32_t vport)
{
	struct ofp_vport_mod *ovpm;
    struct ofpbuf *buffer;
    size_t size;

    size = sizeof *ovpm;
    buffer = ofpbuf_new(size);
    ovpm = ofpbuf_put_zeros(buffer, size);
    ovpm->header.version = OFP_VERSION;
    ovpm->header.type = OFPT_VPORT_MOD;
    ovpm->header.length = htons(size);
    ovpm->vport = htonl(vport);
    ovpm->parent_port = htonl(0); // not needed
	ovpm->command = htons(OFPVP_DELETE);

	return buffer;
}


struct ofpbuf *
get_flow_stats(const struct ofp_match *match)
{
    struct ofp_stats_request *osr;
    struct ofp_flow_stats_request *ofsr;
    struct ofpbuf *buffer;
    size_t size;

    size = sizeof *osr + sizeof *ofsr;
    buffer = ofpbuf_new(size);
    osr = ofpbuf_put_zeros(buffer, size);

    osr->header.version = OFP_VERSION;
    osr->header.type = OFPT_STATS_REQUEST;
    osr->header.length = htons(size);
    osr->type = htons(OFPST_FLOW);
    osr->flags = htons(0);

    ofsr = (struct ofp_flow_stats_request *) osr->body;

    ofsr->match.wildcards = match->wildcards;
    ofsr->match.in_port = match->in_port;
    memcpy(ofsr->match.dl_src, match->dl_src, sizeof ofsr->match.dl_src);
    memcpy(ofsr->match.dl_dst, match->dl_dst, sizeof ofsr->match.dl_dst);
    ofsr->match.dl_vlan = match->dl_vlan;
    ofsr->match.dl_type = match->dl_type;
    ofsr->match.nw_src = match->nw_src;
    ofsr->match.nw_dst = match->nw_dst;
    ofsr->match.nw_proto = match->nw_proto;
    ofsr->match.tp_src = match->tp_src;
    ofsr->match.tp_dst = match->tp_dst;
    ofsr->match.mpls_label1 = match->mpls_label1;
    ofsr->match.mpls_label2 = match->mpls_label2;
    ofsr->table_id = 0xff;
    ofsr->out_port = htons(OFPP_NONE); // don't filter command on out_port

    osr = (struct ofp_stats_request *)buffer->base	;
    ofsr = (struct ofp_flow_stats_request *)osr->body;

    return buffer;
}


struct ofpbuf *
get_vport_stats(uint32_t *ports, uint32_t num_ports)
{
    struct ofp_stats_request *osr;
    struct ofpbuf *buffer;
    size_t size;

    printf("test_vport_stats with %u ports\n", num_ports);

    size = sizeof *osr + sizeof(uint32_t)*num_ports;
    buffer = ofpbuf_new(size);
    osr = ofpbuf_put_zeros(buffer, size);

    osr->header.version = OFP_VERSION;
    osr->header.type = OFPT_STATS_REQUEST;
    osr->header.length = htons(size);
    osr->type = htons(OFPST_PORT);
    osr->flags = htons(0);
    memcpy(osr->body, ports, sizeof(uint32_t)*num_ports);

    return buffer;
}

struct ofpbuf *
get_vport_table_stats()
{
    struct ofp_stats_request *osr;
    struct ofpbuf *buffer;
    size_t size;


    size = sizeof *osr;
    buffer = ofpbuf_new(size);
    osr = ofpbuf_put_zeros(buffer, size);

    osr->header.version = OFP_VERSION;
    osr->header.type = OFPT_STATS_REQUEST;
    osr->header.length = htons(size);

    osr->type = htons(OFPST_PORT_TABLE);
    osr->flags = htons(0);

    return buffer;
}


// FLOW TABLE ACTIONS
void
make_flow_output_action(struct ofp_action_output *op, uint32_t out_port)
{
    op->type = htons(OFPAT_OUTPUT);
    op->len = htons(sizeof *op);
    op->port = htonl(out_port);
}

void
make_flow_set_dl_addr_action(struct ofp_action_dl_addr *op,
								 uint8_t *dl_addr, uint16_t type)
{
    op->type = htons(type);
    op->len = htons(sizeof *op);
    memcpy(op->dl_addr, dl_addr, OFP_ETH_ALEN);
}

void
make_flow_set_mpls_label_action(struct ofp_action_mpls_label *op,
								uint32_t mpls_label)
{
    op->type = htons(OFPAT_SET_MPLS_LABEL);
    op->len = htons(sizeof *op);
    op->label_out = htonl(mpls_label);
}

void
make_flow_set_mpls_exp_action(struct ofp_action_mpls_exp *op,
							  uint8_t exp_bits)
{
    op->type = htons(OFPAT_SET_MPLS_EXP);
    op->len = htons(sizeof *op);
    op->exp = exp_bits;
}

// ericsson extensions
void
make_flow_pop_mpls_action(struct er_action_pop_mpls *op,
						  uint16_t eth_type, uint8_t flags)
{
    op->erah.type = htons(OFPAT_VENDOR);
    op->erah.len = htons(sizeof *op);
    op->erah.vendor = htonl(ER_VENDOR_ID);
    op->erah.subtype = htons(ERXT_POP_MPLS);
    op->apm.flags = flags;
    op->apm.eth_type = htons(eth_type);
}

void
make_flow_push_mpls_action(struct er_action_push_mpls *op, uint32_t label_out,
						   uint8_t exp, uint8_t ttl, uint8_t flags)
{
    op->erah.type = htons(OFPAT_VENDOR);
    op->erah.len = htons(sizeof *op);
    op->erah.vendor = htonl(ER_VENDOR_ID);
    op->erah.subtype = htons(ERXT_POP_MPLS);
    op->apm.label_out = htonl(label_out);
    op->apm.exp = exp;
    op->apm.ttl = ttl;
    op->apm.flags = flags;
}


// PORT TABLE ACTIONS
void
make_vport_pop_mpls_action(struct ofp_vport_action_pop_mpls *op,
						   uint16_t eth_type, uint8_t flags)
{
	op->type = htons(OFPPAT_POP_MPLS);
	op->len = htons(sizeof *op);
	op->apm.eth_type = htons(eth_type);
	op->apm.flags = flags;
}

void
make_vport_push_mpls_action(struct ofp_vport_action_push_mpls *op,
					        uint32_t label_out, uint8_t exp,
							uint8_t ttl, uint8_t flags)
{
	op->type = htons(OFPPAT_PUSH_MPLS);
	op->len = htons(sizeof *op);
    op->apm.exp = exp;
    op->apm.ttl = ttl;
    op->apm.flags = flags;
    op->apm.label_out = htonl(label_out);
}

void
make_vport_set_mpls_label_action(struct ofp_action_mpls_label *op,
								 uint32_t mpls_label)
{
    op->type = htons(OFPPAT_SET_MPLS_LABEL);
    op->len = htons(sizeof *op);
    op->label_out = htonl(mpls_label);
}

void
make_vport_set_mpls_exp_action(struct ofp_action_mpls_exp *op,
							   uint8_t exp_bits)
{
    op->type = htons(OFPPAT_SET_MPLS_EXP);
    op->len = htons(sizeof *op);
    op->exp = exp_bits;
}


// MAH: end
