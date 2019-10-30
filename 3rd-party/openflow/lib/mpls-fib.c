// MAH: start
#include <stdlib.h>
#include "ofpbuf.h"
#include "openflow/openflow.h"
#include "openflow/ericsson-ext.h"
#include "packets.h"
#include "vconn.h"
#include "rconn.h"
#include <arpa/inet.h>
#include "mpls-fib.h"
#include "mpls-switch.h"
#include "vconn-mpls.h"



struct rconn;

void destroy_nhlfes(nhlfePtr n) {
	nhlfePtr nn;
	while (n != NULL) {
		nn = n->next_entry;
		free(n->actions);
		free(n);
		n = nn;
	}
}

void destroy_mpls_fib(mplsFibPtr fib) {
	ftnPtr f, fn;
	ilmPtr i, in;

	// free ftnTable
	f = fib->ftnTable;
	while (f != NULL) {
		fn = f->next_entry;
		destroy_nhlfes(f->nhlfe);
		free(f);
		f = fn;
	}
	// free ilmTable
	i = fib->ilmTable;
	while (i != NULL) {
		in = i->next_entry;
		destroy_nhlfes(i->nhlfe);
		free(i);
		i = in;
	}
}

struct ofp_mpls_op_header*
make_pop_action(struct mpls_switch *sw, struct pop_params *pop, struct ofp_match *match) {
	struct ofp_mpls_pop_op1 *pop1;

	switch (sw->mplsSwitchOps.pop_option)
	{
	case OFP_MPLS_POP_OP1:
		pop1 = (struct ofp_mpls_pop_op1*)malloc(sizeof(struct ofp_mpls_pop_op1));
		pop1->type = OFP_MPLS_POP_OP1;
		pop1->len = sizeof(struct ofp_mpls_pop_op1);
		pop1->vport = alloc_vport(sw->vports);
		pop1->parent_port = pop->out_port;
		// flags for this pop: decrement the ttl and copy the TTL and EXP bits to
		// the next MPLS label or to the IP header if the label stack becomes empty
		pop1->flags = MPLS_POP_DECREMENT_TTL | MPLS_POP_COPY_TTL | MPLS_POP_COPY_EXP;
		memcpy(&pop1->src_mac, &pop->src_mac, ETH_ADDR_LEN);
		memcpy(&pop1->dst_mac, &pop->dst_mac, ETH_ADDR_LEN);
		memcpy(&pop1->match, match, sizeof(struct ofp_match));
		return (struct ofp_mpls_op_header*)pop1;
		break;
	case OFP_MPLS_POP_OP2:
		// implement option 2 for NetFPGA switch if needed
		printf("pop option 2 not implemented!\n");
		break;
	default:
		printf("invalid pop option!\n");
	}

	return NULL;
}

struct ofp_mpls_op_header*
make_push_action(struct mpls_switch *sw, struct push_params *push, struct ofp_match *match) {
	struct ofp_mpls_push_op1 *push1;

	switch (sw->mplsSwitchOps.push_option)
	{
	case OFP_MPLS_PUSH_OP1:
		push1 = (struct ofp_mpls_push_op1*)malloc(sizeof(struct ofp_mpls_push_op1));
		push1->type = OFP_MPLS_PUSH_OP1;
		push1->len = sizeof(struct ofp_mpls_push_op1);
		push1->vport = alloc_vport(sw->vports);
		push1->parent_port = push->out_port;
		// flags for this push:
		push1->flags = MPLS_PUSH_DECREMENT_TTL | MPLS_PUSH_TTL_NEXT | MPLS_PUSH_EXP_NEXT;
		memcpy(&push1->src_mac, &push->src_mac, ETH_ADDR_LEN);
		memcpy(&push1->dst_mac, &push->dst_mac, ETH_ADDR_LEN);
		memcpy(&push1->match, match, sizeof(struct ofp_match));
		push1->mpls_label = push->mpls_label;
		return (struct ofp_mpls_op_header*)push1;
		break;
	case OFP_MPLS_PUSH_OP2:
		// implement option 2 for NetFPGA switch if needed
		printf("push option 2 not implemented!\n");
		break;
	default:
		printf("invalid push option!\n");
	}

	return NULL;
}

struct ofp_mpls_op_header*
make_swap_action(struct mpls_switch *sw, struct swap_params *swap, struct ofp_match *match) {
	struct ofp_mpls_swap_op1 *swap1;
	struct ofp_mpls_swap_op2 *swap2;

	switch (sw->mplsSwitchOps.swap_option)
	{
	case OFP_MPLS_SWAP_OP1:
		swap1 = (struct ofp_mpls_swap_op1*)malloc(sizeof(struct ofp_mpls_swap_op1));
		swap1->type = OFP_MPLS_SWAP_OP1;
		swap1->len = sizeof(struct ofp_mpls_swap_op1);
		swap1->pop_vport = alloc_vport(sw->vports);
		swap1->push_vport = alloc_vport(sw->vports);
		swap1->push_parent_port = swap->out_port;
		swap1->mpls_label = swap->mpls_label;
		swap1->pop_flags = MPLS_POP_COPY_TTL | MPLS_POP_COPY_EXP;
		swap1->push_flags = MPLS_PUSH_DECREMENT_TTL | MPLS_PUSH_TTL_PREV | MPLS_PUSH_EXP_PREV;
		memcpy(&swap1->src_mac, &swap->src_mac, ETH_ADDR_LEN);
		memcpy(&swap1->dst_mac, &swap->dst_mac, ETH_ADDR_LEN);
		memcpy(&swap1->match, match, sizeof(struct ofp_match));
		return (struct ofp_mpls_op_header*)swap1;
		break;
	case OFP_MPLS_SWAP_OP2:
		swap2 = (struct ofp_mpls_swap_op2*)malloc(sizeof(struct ofp_mpls_swap_op2));
		swap2->type = OFP_MPLS_SWAP_OP2;
		swap2->len = sizeof(struct ofp_mpls_swap_op2);
		swap2->pop_vport = alloc_vport(sw->vports);
		swap2->pop_parent_port = swap->out_port;
		swap2->mpls_label = swap->mpls_label;
		swap2->pop_flags = MPLS_POP_DONT_POP | MPLS_POP_DECREMENT_TTL;
		memcpy(&swap2->src_mac, &swap->src_mac, ETH_ADDR_LEN);
		memcpy(&swap2->dst_mac, &swap->dst_mac, ETH_ADDR_LEN);
		memcpy(&swap2->match, match, sizeof(struct ofp_match));
		return (struct ofp_mpls_op_header*)swap2;
		break;
	default:
		printf("invalid swap option!\n");
	}

	return NULL;
}



int
ofp_mpls_pop_op1_install(struct mpls_switch *sw, struct rconn *rconn, void *ofp_mpls_op)
{
	struct ofp_mpls_pop_op1 *op = (struct ofp_mpls_pop_op1 *)ofp_mpls_op;
	// flow actions
	struct ofp_action_dl_addr rewrite_dl_src;
	struct ofp_action_dl_addr rewrite_dl_dst;
	struct ofp_action_output out;
	void *flow_actions, *p;
	uint32_t flow_actions_len;
	// vport actions
	struct ofp_vport_action_pop_mpls pop;

	// flow table actions
	flow_actions_len = sizeof rewrite_dl_src + sizeof rewrite_dl_dst + sizeof out;
	flow_actions = (void*)malloc(flow_actions_len);
	// copy actions
	p = flow_actions;
	make_flow_set_dl_addr_action(&rewrite_dl_src, op->src_mac, OFPAT_SET_DL_SRC);
	memcpy(p, &rewrite_dl_src, sizeof rewrite_dl_src);
	p  = (uint8_t*)p + sizeof rewrite_dl_src;
	make_flow_set_dl_addr_action(&rewrite_dl_dst, op->dst_mac, OFPAT_SET_DL_DST);
	memcpy(p, &rewrite_dl_dst, sizeof rewrite_dl_dst);
	p  = (uint8_t*)p + sizeof rewrite_dl_dst;
	make_flow_output_action(&out, op->vport);
	memcpy(p, &out, sizeof out);

	// vport table actions
	make_vport_pop_mpls_action(&pop, ETH_TYPE_IP, op->flags);

	// add vport to perform MPLS pop action
	queue_tx(sw, rconn, add_mpls_vport_entry(op->vport, op->parent_port,
											 (void*)&pop, sizeof pop));
		// install flow table entry to direct flow to vport
	queue_tx(sw, rconn, add_mpls_flow_entry(&op->match, -1, OFP_FLOW_PERMANENT,
											flow_actions, flow_actions_len));
	free(flow_actions);

	// XXX TODO trap and return errors

	return 0;
}

int
ofp_mpls_pop_op1_remove(struct mpls_switch *sw, struct rconn *rconn, void *ofp_mpls_op)
{
	struct ofp_mpls_pop_op1 *op = (struct ofp_mpls_pop_op1 *)ofp_mpls_op;

	// remove vport entry for pop action
	queue_tx(sw, rconn, rem_vport_entry(op->vport));

	// remove flow entry that sends traffic to vport
	queue_tx(sw, rconn, rem_flow_entry(&op->match));

	// XXX TODO trap and return errors

	return 0;
}



int
ofp_mpls_pop_op1_stats(struct mpls_switch *sw, struct rconn *rconn, void *ofp_mpls_op)
{
	uint32_t ports;
	struct ofp_mpls_pop_op1 *op = (struct ofp_mpls_pop_op1 *)ofp_mpls_op;
	ports = op->vport;

	queue_tx(sw, rconn, get_vport_stats(&ports, 1));

	queue_tx(sw, rconn, get_flow_stats(&op->match));

	return 0;
}


int
ofp_mpls_push_op1_install(struct mpls_switch *sw, struct rconn *rconn, void *ofp_mpls_op)
{
	struct ofp_mpls_push_op1 *op = (struct ofp_mpls_push_op1 *)ofp_mpls_op;
	// flow actions
	struct ofp_action_dl_addr rewrite_dl_src;
	struct ofp_action_dl_addr rewrite_dl_dst;
	struct ofp_action_output out;
	void *flow_actions, *p;
	uint32_t flow_actions_len;
	// vport actions
	struct ofp_vport_action_push_mpls push;

	// flow table actions
	flow_actions_len = sizeof rewrite_dl_src + sizeof rewrite_dl_dst + sizeof out;
	flow_actions = (void*)malloc(flow_actions_len);
	p = flow_actions;
	flow_actions_len = sizeof rewrite_dl_src + sizeof rewrite_dl_dst + sizeof out;
	// set source MAC address
	make_flow_set_dl_addr_action(&rewrite_dl_src, op->src_mac, OFPAT_SET_DL_SRC);
	memcpy(p, &rewrite_dl_src, sizeof rewrite_dl_src);
	p  = (uint8_t*)p + sizeof rewrite_dl_src;
	// set destination MAC address
	make_flow_set_dl_addr_action(&rewrite_dl_dst, op->dst_mac, OFPAT_SET_DL_DST);
	memcpy(p, &rewrite_dl_dst, sizeof rewrite_dl_dst);
	p  = (uint8_t*)p + sizeof rewrite_dl_dst;
	// forward to virtual port
	make_flow_output_action(&out, op->vport);
	memcpy(p, &out, sizeof out);


	// vport table actions
	make_vport_push_mpls_action(&push, op->mpls_label, 0, 0, op->flags);

	// add vport to perform MPLS pop action
	queue_tx(sw, rconn, add_mpls_vport_entry(op->vport, op->parent_port,
											 (void*)&push, sizeof push));
		// install flow table entry to direct flow to vport
	queue_tx(sw, rconn, add_mpls_flow_entry(&op->match, -1, OFP_FLOW_PERMANENT,
											flow_actions, flow_actions_len));
	free(flow_actions);

	// XXX TODO trap and return errors

	return 0;
}

int
ofp_mpls_push_op1_remove(struct mpls_switch *sw, struct rconn *rconn, void *ofp_mpls_op)
{
	struct ofp_mpls_push_op1 *op = (struct ofp_mpls_push_op1 *)ofp_mpls_op;

	// remove vport entry for pop action
	queue_tx(sw, rconn, rem_vport_entry(op->vport));

	// remove flow entry that sends traffic to vport
	queue_tx(sw, rconn, rem_flow_entry(&op->match));

	// XXX TODO trap and return errors

	return 0;
}

int
ofp_mpls_push_op1_stats(struct mpls_switch *sw, struct rconn *rconn, void *ofp_mpls_op)
{
	uint32_t ports;
	struct ofp_mpls_push_op1 *op = (struct ofp_mpls_push_op1 *)ofp_mpls_op;
	ports = op->vport;

	queue_tx(sw, rconn, get_vport_stats(&ports, 1));

	queue_tx(sw, rconn, get_flow_stats(&op->match));

	return 0;
}


int
ofp_mpls_swap_op1_install(struct mpls_switch *sw, struct rconn *rconn, void *ofp_mpls_op)
{
	struct ofp_mpls_swap_op1 *op = (struct ofp_mpls_swap_op1 *)ofp_mpls_op;
	// flow actions
	struct ofp_action_dl_addr rewrite_dl_src;
	struct ofp_action_dl_addr rewrite_dl_dst;
	struct ofp_action_output out;
	void *flow_actions, *p;
	uint32_t flow_actions_len;
	// vport actions
	struct ofp_vport_action_pop_mpls pop;
	struct ofp_vport_action_push_mpls push;

	// flow table actions
	flow_actions_len = sizeof rewrite_dl_src + sizeof rewrite_dl_dst + sizeof out;
	flow_actions = (void*)malloc(flow_actions_len);
	p = flow_actions;
	flow_actions_len = sizeof rewrite_dl_src + sizeof rewrite_dl_dst + sizeof out;
	// set source MAC address
	make_flow_set_dl_addr_action(&rewrite_dl_src, op->src_mac, OFPAT_SET_DL_SRC);
	memcpy(p, &rewrite_dl_src, sizeof rewrite_dl_src);
	p  = (uint8_t*)p + sizeof rewrite_dl_src;
	// set destination MAC address
	make_flow_set_dl_addr_action(&rewrite_dl_dst, op->dst_mac, OFPAT_SET_DL_DST);
	memcpy(p, &rewrite_dl_dst, sizeof rewrite_dl_dst);
	p  = (uint8_t*)p + sizeof rewrite_dl_dst;
	// forward to virtual port
	make_flow_output_action(&out, op->pop_vport);
	memcpy(p, &out, sizeof out);


	// vport table action for pop
	make_vport_pop_mpls_action(&pop, ETH_TYPE_IP, op->pop_flags);

	// vport table action for push
	make_vport_push_mpls_action(&push, op->mpls_label, 0, 0, op->push_flags);;

	// add vport to perform MPLS push action
	queue_tx(sw, rconn, add_mpls_vport_entry(op->push_vport, op->push_parent_port,
											(void*)&push, sizeof push));

	// add vport to perform MPLS pop action
	queue_tx(sw, rconn, add_mpls_vport_entry(op->pop_vport, op->push_vport,
											 (void*)&pop, sizeof pop));

	// install flow table entry to direct flow to vport
	queue_tx(sw, rconn, add_mpls_flow_entry(&op->match, -1, OFP_FLOW_PERMANENT,
											flow_actions, flow_actions_len));
	free(flow_actions);
	return 0;
}

int
ofp_mpls_swap_op1_remove(struct mpls_switch *sw, struct rconn *rconn, void *ofp_mpls_op)
{
	struct ofp_mpls_swap_op1 *op = (struct ofp_mpls_swap_op1 *)ofp_mpls_op;

	// remove vport entry for pop action
	queue_tx(sw, rconn, rem_vport_entry(op->pop_vport));

	// remove vport entry for push action
	queue_tx(sw, rconn, rem_vport_entry(op->push_vport));

	// remove flow entry that sends traffic to vport
	queue_tx(sw, rconn, rem_flow_entry(&op->match));

	// XXX TODO trap and return errors

	return 0;
}

int
ofp_mpls_swap_op1_stats(struct mpls_switch *sw, struct rconn *rconn, void *ofp_mpls_op)
{
	uint32_t ports[2];
	struct ofp_mpls_swap_op1 *op = (struct ofp_mpls_swap_op1 *)ofp_mpls_op;
	ports[0] = op->pop_vport;
	ports[1] = op->push_vport;

	// get stats for both vports
	queue_tx(sw, rconn, get_vport_stats(ports, 2));

	queue_tx(sw, rconn, get_flow_stats(&op->match));

	return 0;
}

int
ofp_mpls_swap_op2_install(struct mpls_switch *sw, struct rconn *rconn, void *ofp_mpls_op)
{
	struct ofp_mpls_swap_op2 *op = (struct ofp_mpls_swap_op2 *)ofp_mpls_op;
	// flow actions
	struct ofp_action_dl_addr rewrite_dl_src;
	struct ofp_action_dl_addr rewrite_dl_dst;
	struct ofp_action_mpls_label set_label;
	struct ofp_action_output out;
	void *flow_actions, *p;
	uint32_t flow_actions_len;
	// vport actions
	struct ofp_vport_action_pop_mpls pop;

	// flow table actions
	flow_actions_len = sizeof rewrite_dl_src + sizeof rewrite_dl_dst +
					   sizeof set_label + sizeof out;
	flow_actions = (void*)malloc(flow_actions_len);
	p = flow_actions;
	// set source MAC address
	make_flow_set_dl_addr_action(&rewrite_dl_src, op->src_mac, OFPAT_SET_DL_SRC);
	memcpy(p, &rewrite_dl_src, sizeof rewrite_dl_src);
	p  = (uint8_t*)p + sizeof rewrite_dl_src;
	// set destination MAC address
	make_flow_set_dl_addr_action(&rewrite_dl_dst, op->dst_mac, OFPAT_SET_DL_DST);
	memcpy(p, &rewrite_dl_dst, sizeof rewrite_dl_dst);
	p  = (uint8_t*)p + sizeof rewrite_dl_dst;
	// set MPLS label
	make_flow_set_mpls_label_action(&set_label, op->mpls_label);
	memcpy(p, &set_label, sizeof set_label);
	p  = (uint8_t*)p + sizeof set_label;
	// forward to virtual port
	make_flow_output_action(&out, op->pop_vport);
	memcpy(p, &out, sizeof out);


	// vport table action for pop
	make_vport_pop_mpls_action(&pop, ETH_TYPE_IP, op->pop_flags);

	// add vport to perform MPLS pop action
	queue_tx(sw, rconn, add_mpls_vport_entry(op->pop_vport, op->pop_parent_port,
											 (void*)&pop, sizeof pop));

	// install flow table entry to direct flow to vport
	queue_tx(sw, rconn, add_mpls_flow_entry(&op->match, -1, OFP_FLOW_PERMANENT,
											flow_actions, flow_actions_len));
	free(flow_actions);

	return 0;
}

int
ofp_mpls_swap_op2_remove(struct mpls_switch *sw, struct rconn *rconn, void *ofp_mpls_op)
{
	struct ofp_mpls_swap_op1 *op = (struct ofp_mpls_swap_op1 *)ofp_mpls_op;

	// remove vport entry for pop action
	queue_tx(sw, rconn, rem_vport_entry(op->pop_vport));


	// remove flow entry that sends traffic to vport
	queue_tx(sw, rconn, rem_flow_entry(&op->match));

	// XXX TODO trap and return errors

	return 0;
}

int
ofp_mpls_swap_op2_stats(struct mpls_switch *sw, struct rconn *rconn, void *ofp_mpls_op)
{
	uint32_t ports[1];
	struct ofp_mpls_swap_op2 *op = (struct ofp_mpls_swap_op2 *)ofp_mpls_op;
	ports[0] = op->pop_vport;

	// get stats for both vports
	queue_tx(sw, rconn, get_vport_stats(ports, 1));

	queue_tx(sw, rconn, get_flow_stats(&op->match));

	return 0;
}

struct ofp_mpls_operation {
    int (*install)(struct mpls_switch *sw, struct rconn *rconn, void *ofp_mpls_op);
    int (*remove)(struct mpls_switch *sw, struct rconn *rconn,  void *ofp_mpls_op);
    int (*get_stats)(struct mpls_switch *sw, struct rconn *rconn, void *ofp_mpls_op);
};

static const struct ofp_mpls_operation ofp_mpls_operations[] = {
	   [OFP_MPLS_POP_OP1] = {
			ofp_mpls_pop_op1_install,
			ofp_mpls_pop_op1_remove,
			ofp_mpls_pop_op1_stats
		},
		[OFP_MPLS_PUSH_OP1] = {
			ofp_mpls_push_op1_install,
			ofp_mpls_push_op1_remove,
			ofp_mpls_push_op1_stats
		},
		[OFP_MPLS_SWAP_OP1] = {
			ofp_mpls_swap_op1_install,
			ofp_mpls_swap_op1_remove,
			ofp_mpls_swap_op1_stats
		},
	    [OFP_MPLS_SWAP_OP2] = {
			ofp_mpls_swap_op2_install,
			ofp_mpls_swap_op2_remove,
			ofp_mpls_swap_op2_stats
		}
};


void install_nhlfe_actions(struct mpls_switch *sw, struct rconn *rconn, struct mpls_nhlfe *nhlfe)
{
	uint16_t actions_len, len;
	const struct ofp_mpls_operation *omo;
	actions_len = nhlfe->actions_len;

	while (actions_len > 0)
	{
		struct ofp_mpls_op_header *oph = (struct ofp_mpls_op_header*)nhlfe->actions;
		len = oph->len;
		omo = &ofp_mpls_operations[oph->type];
		if (omo->install) {
			omo->install(sw, rconn, oph);
		}
		actions_len -= len;
	}
}

void remove_nhlfe_actions(struct mpls_switch *sw, struct rconn *rconn, struct mpls_nhlfe *nhlfe)
{
	uint16_t actions_len, len;
	const struct ofp_mpls_operation *omo;
	actions_len = nhlfe->actions_len;

	while (actions_len > 0)
	{
		struct ofp_mpls_op_header *oph = (struct ofp_mpls_op_header*)nhlfe->actions;
		len = oph->len;
		omo = &ofp_mpls_operations[oph->type];
		if (omo->remove) {
			omo->remove(sw, rconn, oph);
		}
		actions_len -= len;
	}
}


// MAH: end
