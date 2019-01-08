#ifndef DP_ACT_H
#define DP_ACT_H 1

#include "datapath.h"

#define ACT_VALIDATION_OK ((uint16_t)-1)

// MAH: start
struct sk_buff *set_mpls_label_act(struct sk_buff *skb,
						struct sw_flow_key *key,
						const uint32_t label_out);
struct sk_buff *set_mpls_exp_act(struct sk_buff *skb,
					  struct sw_flow_key *key,
					  const uint8_t exp);
// Make this publicly available
int do_output(struct datapath *dp, struct sk_buff *skb, size_t max_len,
			  int out_port, int ignore_no_fwd);
void update_csum(__sum16 *sum, struct sk_buff *skb,
			__be32 from, __be32 to, int pseudohdr);
// MAH: end

uint16_t validate_actions(struct datapath *, const struct sw_flow_key *,
		const struct ofp_action_header *, size_t);
void execute_actions(struct datapath *, struct sk_buff *,
		struct sw_flow_key *, const struct ofp_action_header *,
		size_t action_len, int ignore_no_fwd);
int make_writable(struct sk_buff **pskb);

#endif /* dp_act.h */
