// MAH: start
/* Functions for Ericsson-extended actions. */
#include <arpa/inet.h>
#include "openflow/ericsson-ext.h"
#include "er_act.h"
#include "dp_act.h"
#include "pt_act.h"
#include "csum.h"
#include "packets.h"

static void
er_pop_mpls_act(struct datapath *dp, struct ofpbuf *buffer, const struct sw_flow_key *key,
				const struct er_action_header *ah)
{
	struct er_action_pop_mpls *erapm = (struct er_action_pop_mpls *)ah;
	pop_mpls_act(dp, buffer, key, &erapm->apm);
}

static void
er_push_mpls_act(struct datapath *dp, struct ofpbuf *buffer, const struct sw_flow_key *key,
				 const struct er_action_header *ah)
{
	struct er_action_push_mpls *erapm = (struct er_action_push_mpls *)ah;
	push_mpls_act(dp, buffer, key, &erapm->apm);
}


struct er_action {
    size_t min_size;
    size_t max_size;
    uint16_t (*validate)(struct datapath *dp,
            const struct sw_flow_key *key,
            const struct er_action_header *ah);
    void (*execute)(struct datapath *dp, struct ofpbuf *buffer,
            const struct sw_flow_key *key,
            const struct er_action_header *ah);
};

static const struct er_action er_of_actions[] = {
    [ERXT_POP_MPLS] = {
        sizeof(struct er_action_pop_mpls),
        sizeof(struct er_action_pop_mpls),
        NULL,	/* XXX add a proper validate function if appropriate */
        er_pop_mpls_act
    },
    [ERXT_PUSH_MPLS] = {
        sizeof(struct er_action_push_mpls),
        sizeof(struct er_action_push_mpls),
        NULL,	/* XXX add a proper validate function if appropriate */
        er_push_mpls_act
    }
};

/* Validate Ericsson OpenFlow actions.  Either returns ACT_VALIDATION_OK
 * or an OFPET_BAD_ACTION error code. */
uint16_t
er_validate_act(struct datapath *dp, const struct sw_flow_key *key,
		const struct ofp_action_vendor_header *avh, uint16_t len)
{
	const struct er_action_header *erah = (const struct er_action_header *)avh;
	int ret = ACT_VALIDATION_OK;
	const struct er_action *act = &er_of_actions[ntohs(erah->subtype)];

	// XXX printf("er_validate_act called len = %u min size = %u max size = %u\n", len, act->min_size, act->max_size);
	if ((len < act->min_size) || (len > act->max_size)) {
		return OFPBAC_BAD_LEN;
	}

	if (act->validate) {
		ret = act->validate(dp, key, erah);
	}

	return ret;
}




void
er_execute_act(struct datapath *dp, struct ofpbuf *buffer, const struct sw_flow_key *key,
		const struct ofp_action_vendor_header *avh)
{
	const struct er_action_header *erah = (const struct er_action_header *)avh;
	const struct er_action *act = &er_of_actions[ntohs(erah->subtype)];

    if (act->execute) {
        act->execute(dp, buffer, key, erah);
    }
}

// MAH: end
