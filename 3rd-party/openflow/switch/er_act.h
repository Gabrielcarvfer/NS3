// MAH: start
// Ericsson defined actions for supporting MPLS
#ifndef ER_ACT_H
#define ER_ACT_H 1

#include "switch-flow.h"
#include "datapath.h"

uint16_t er_validate_act(struct datapath *dp, const struct sw_flow_key *key,
		const struct ofp_action_vendor_header *avh, uint16_t len);

void er_execute_act(struct datapath *dp, struct ofpbuf *buffer,
		const struct sw_flow_key *key,
		const struct ofp_action_vendor_header *avh);

#endif /* er_act.h */


// MAH: end
