// MAH: start
// This file contains the functions to add or remove flow table and virtual port table entries.
// It also includes functions to populate action structures needed for MPLS operations.

#ifndef VCONN_MPLS_H
#define VCONN_MPLS_H 1

// add a flow entry to match on the provided match structure and perform
// the specified actions
struct ofpbuf * add_mpls_flow_entry(const struct ofp_match *match,
									uint32_t buffer_id,
								    uint16_t idle_timeout,
								    void *actions, uint32_t actions_len);

// add a virtual port entry with the specified actions that is linked
// to the specified parent port
struct ofpbuf * add_mpls_vport_entry(uint32_t vport, uint32_t parent_port,
									 void *actions, uint32_t actions_len);

// remove a flow table entry
struct ofpbuf * rem_flow_entry(const struct ofp_match *match);

// remove a virtual port table entry
struct ofpbuf * rem_vport_entry(uint32_t vport);

// get statistics for a flow table entry
struct ofpbuf * get_flow_stats(const struct ofp_match *match);

// get statistics for a virtual port table entry
struct ofpbuf * get_vport_stats(uint32_t *ports, uint32_t vports);

// get statistics for virtual port table
struct ofpbuf * get_vport_table_stats(void);

// fill in action structures
void make_flow_output_action(struct ofp_action_output *op, uint32_t out_port);

void make_flow_set_dl_addr_action(struct ofp_action_dl_addr *op,
									  uint8_t *dl_addr, uint16_t type);

void make_flow_set_mpls_label_action(struct ofp_action_mpls_label *op,
								     uint32_t mpls_label);

void make_flow_set_mpls_exp_action(struct ofp_action_mpls_exp *op,
								   uint8_t exp_bits);

void make_flow_pop_mpls_action(struct er_action_pop_mpls *op,
							   uint16_t eth_type, uint8_t flags);

void make_flow_push_mpls_action(struct er_action_push_mpls *op, uint32_t label_out,
							    uint8_t exp, uint8_t ttl, uint8_t flags);

void make_vport_pop_mpls_action(struct ofp_vport_action_pop_mpls *op,
								uint16_t eth_type, uint8_t flags);

void make_vport_push_mpls_action(struct ofp_vport_action_push_mpls *op,
								 uint32_t label_out, uint8_t exp,
								 uint8_t ttl, uint8_t flags);

void make_vport_set_mpls_label_action(struct ofp_action_mpls_label *op,
									  uint32_t mpls_label);

void make_vport_set_mpls_exp_action(struct ofp_action_mpls_exp *op,
								    uint8_t exp_bits);

#endif
// MAH: end
