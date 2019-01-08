// MAH: start
// Virtual port table actions
#ifndef PT_ACT_H
#define PT_ACT_H 1

#include "dp_act.h"
#include "datapath.h"

void pop_mpls_act(struct datapath *dp, struct ofpbuf *buffer,
				  const struct sw_flow_key *key, const struct action_pop_mpls *apm);

void push_mpls_act(struct datapath *dp, struct ofpbuf *buffer,
				   const struct sw_flow_key *key, const struct action_push_mpls *apm);



uint16_t pt_validate_act(struct datapath *dp,
		const struct ofp_action_header *ah, uint16_t len);

void pt_execute_act(struct datapath *dp, struct ofpbuf *buffer,
		const struct ofp_action_header *ah);

uint16_t validate_vport_actions(struct datapath *dp, const struct ofp_action_header *actions,
							   size_t actions_len);

void execute_vport_actions(struct datapath *dp, struct ofpbuf *buffer,
						  struct sw_flow_key *key,
						  const struct ofp_action_header *actions, size_t actions_len);

#endif /* pt_act.h */


// MAH: end
