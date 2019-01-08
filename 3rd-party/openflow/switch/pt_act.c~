// MAH: start
/* Port table actions. */
#include <arpa/inet.h>
#include "pt_act.h"
#include "dp_act.h"
#include "csum.h"
#include "packets.h"

static void inline
update_checksums(struct ofpbuf *buffer, const struct sw_flow_key *key,
				 uint32_t old_word, uint32_t new_word) {
    struct ip_header *nh = buffer->l3;
	if (key->flow.nw_proto == IP_TYPE_TCP) {
		struct tcp_header *th = buffer->l4;
		th->tcp_csum = recalc_csum32(th->tcp_csum, old_word, new_word);
	} else if (key->flow.nw_proto == IP_TYPE_UDP) {
		struct udp_header *th = buffer->l4;
        if (th->udp_csum) {
            th->udp_csum = recalc_csum32(th->udp_csum, old_word, new_word);
            if (!th->udp_csum) {
                th->udp_csum = 0xffff;
            }
        }
	}
    nh->ip_csum = recalc_csum32(nh->ip_csum, old_word, new_word);
}


static void
pt_pop_mpls_act(struct datapath *dp, struct ofpbuf *buffer, const struct sw_flow_key *key,
        const struct ofp_action_header *ah)
{
	struct ofp_vport_action_pop_mpls *opapm = (struct ofp_vport_action_pop_mpls *)ah;
	pop_mpls_act(dp, buffer, key, &opapm->apm);
}

static void
pt_push_mpls_act(struct datapath *dp, struct ofpbuf *buffer, const struct sw_flow_key *key,
        const struct ofp_action_header *ah)
{
	struct ofp_vport_action_push_mpls *opapm = (struct ofp_vport_action_push_mpls *)ah;
	push_mpls_act(dp, buffer, key, &opapm->apm);
}


static void
pt_set_mpls_label_act(struct datapath *dp, struct ofpbuf *buffer, const struct sw_flow_key *key,
				      const struct ofp_action_header *ah)
{
	struct ofp_vport_action_set_mpls_label *oparml = (struct ofp_vport_action_set_mpls_label *)ah;
	set_mpls_label_act(buffer, key, oparml->label_out);
}

static void
pt_set_mpls_exp_act(struct datapath *dp, struct ofpbuf *buffer, const struct sw_flow_key *key,
				    const struct ofp_action_header *ah)
{
	struct ofp_vport_action_set_mpls_exp *oparme = (struct ofp_vport_action_set_mpls_exp *)ah;
	set_mpls_exp_act(buffer, key, oparme->exp);
}


/* pop the top MPLS label from the label stack. */
void pop_mpls_act(struct datapath *dp, struct ofpbuf *buffer,
				  const struct sw_flow_key *key,
				  const struct action_pop_mpls *apm)
{
	struct eth_header *eth_h;
	struct ip_header *ip_h;
	mpls_header mpls_h, mpls_h2;
	uint32_t old_word, new_word;
	void *word_addr;

	uint16_t eth_proto = ntohs(key->flow.dl_type);

	// XXX TODO handle multicast MPLS
    if (eth_proto == ETH_TYPE_MPLS_UNICAST) {
    	// grab the MLPS label at the top of the stack
    	mpls_h.value =  htonl(*(uint32_t*)buffer->l2_5);
    	if (apm->flags & MPLS_POP_DECREMENT_TTL) {
    		// decrement the ttl and write the updated value back to the packet
    		mpls_h.ttl--;
    		*((uint32_t *)buffer->l2_5) = htonl(mpls_h.value);
    	}

    	// remember the label at the top of the stack
    	// this is needed when we implement swap using a pop followed by a push
        buffer->last_mpls_h = *(uint32_t*)buffer->l2_5;

        // pop the top label in the label stack
        if (!(apm->flags & MPLS_POP_DONT_POP)) {
        	ofpbuf_pop(buffer, (size_t)buffer->l2_5 - (size_t)buffer->l2, sizeof(uint32_t));
        } else {
        	return; // do nothing else
        }

        if (mpls_h.s) {
        	// Set the Ethertype in the Ethernet header back to whatever it was
        	eth_h = (struct eth_header *) buffer->l2;
        	eth_h->eth_type = apm->eth_type;
        }

        // If this is the last label on the stack
        if (mpls_h.s) {
    		ip_h = (struct ip_header *) buffer->l3;

			// if the COPY_TTL flag is set then copy the MPLS ttl bits
    		// back to the IP header
        	if (apm->flags & MPLS_POP_COPY_TTL) {
        		// copy the TTL from the popped label into the IP header
        		word_addr = (void*)&ip_h->ip_frag_off;
        		old_word = *((uint32_t*)word_addr);
        		ip_h->ip_ttl = ((uint8_t)mpls_h.ttl);
        		new_word = *((uint32_t*)word_addr);

        		// recalculate checksums
        		update_checksums(buffer, key, old_word, new_word);
        	}
        	// if the COPY_EXP flaq is set then replace the type of service bits in the IP
        	// header with the exp bits from the MPLS header
        	if (apm->flags & MPLS_POP_COPY_EXP) {
        		// copy the TTL from the popped label into the IP header
        		word_addr = (void*)&ip_h->ip_ihl_ver;
        		old_word = *((uint32_t*)word_addr);
        		ip_h->ip_tos = mpls_h.exp;
        		new_word = *((uint32_t*)word_addr);

        		// recalculate checksums
        		update_checksums(buffer, key, old_word, new_word);
        	}
        } else {
        	// if this is not the last label on the stack
        	// get the next label
        	mpls_h2.value =  htonl(*(uint32_t*)buffer->l2_5);

        	if (apm->flags & MPLS_POP_COPY_TTL) {
        		mpls_h2.ttl = mpls_h.ttl;
        	}
        	if (apm->flags & MPLS_POP_COPY_EXP) {
        		mpls_h2.exp = mpls_h.exp;
        	}

        	// copy the updated copy of the second label back
        	// to the packet
        	*((uint32_t *)buffer->l2_5) = htonl(mpls_h2.value);
        }
    }
}


/* push an MPLS label onto the label stack. */
void push_mpls_act(struct datapath *dp, struct ofpbuf *buffer,
				   const struct sw_flow_key *key,
				   const struct action_push_mpls *apm)
{
	struct eth_header *eth_h;
	struct ip_header *ip_h;
	mpls_header mpls_h, last_mpls_h;
	uint32_t value_to_push;
	uint16_t eth_proto;
	size_t offset;

	if (buffer->l2_5) {
		offset = (size_t)buffer->l2_5 - (size_t)buffer->l2;
	} else {
		offset = (size_t)buffer->l3 - (size_t)buffer->l2;
	}

	eth_h = (struct eth_header *) buffer->l2;
	eth_proto = ntohs(eth_h->eth_type);
	mpls_h.label = ntohl(apm->label_out);
	last_mpls_h.value = ntohl(buffer->last_mpls_h);
	ip_h = (struct ip_header *) buffer->l3;


	// first check whether there is another label on the stack
	if (eth_proto == ETH_TYPE_MPLS_UNICAST) {
		mpls_h.s = 0; // must be 0
	} else if (eth_proto == ETH_TYPE_IP) {
    	mpls_h.s = 1; // bottom of stack
		// also change the Ethertype to MPLS
		eth_h->eth_type = htons(ETH_TYPE_MPLS_UNICAST);
    }

	// next determine where to get the ttl and exp bits
	if (apm->flags & MPLS_PUSH_TTL_PREV) {
		// use the IP from the previous label
		mpls_h.ttl = last_mpls_h.ttl - (apm->flags & MPLS_PUSH_DECREMENT_TTL);
	} else if (apm->flags & MPLS_PUSH_TTL_NEXT) {
		// use the IP TTL
		mpls_h.ttl = ip_h->ip_ttl - (apm->flags & MPLS_PUSH_DECREMENT_TTL);
	} else {
		// use the ttl specified by controller
		// do not decrement in that case
		mpls_h.ttl = apm->ttl;
	}
	if (apm->flags & MPLS_PUSH_EXP_PREV) {
		// use the IP from the previous label
		mpls_h.exp = last_mpls_h.exp;
	} else if (apm->flags & MPLS_PUSH_EXP_NEXT) {
		// use the IP type of service bits
		mpls_h.exp = ip_h->ip_tos; // XXX TODO IP diff serv is 8-bits, MPLS has 3 exp bits, what do we do?
	} else {
		// use the exp bits specified by the controller
		mpls_h.exp = apm->exp;
	}

	// push on the new label
	value_to_push = htonl(mpls_h.value);
    ofpbuf_push_at(buffer, offset, &value_to_push, sizeof(uint32_t));
}



struct openflow_vport_action {
    size_t min_size;
    size_t max_size;
    uint16_t (*validate)(struct datapath *dp,
            const struct ofp_action_header *ah);
    void (*execute)(struct datapath *dp,
    		struct ofpbuf *buffer,
    		const struct sw_flow_key *key,
            const struct ofp_action_header *ah);
};

static const struct openflow_vport_action port_actions[] = {
    [OFPPAT_POP_MPLS] = {
        sizeof(struct ofp_vport_action_pop_mpls),
        sizeof(struct ofp_vport_action_pop_mpls),
        NULL,
        pt_pop_mpls_act
    },
    [OFPPAT_PUSH_MPLS] = {
        sizeof(struct ofp_vport_action_push_mpls),
        sizeof(struct ofp_vport_action_push_mpls),
        NULL,
        pt_push_mpls_act
    },
    [OFPPAT_SET_MPLS_LABEL] = {
        sizeof(struct ofp_vport_action_set_mpls_label),
        sizeof(struct ofp_vport_action_set_mpls_label),
        NULL,
        pt_set_mpls_label_act
    },
    [OFPPAT_SET_MPLS_EXP] = {
		sizeof(struct ofp_vport_action_set_mpls_exp),
		sizeof(struct ofp_vport_action_set_mpls_exp),
		NULL,
		pt_set_mpls_exp_act
    }
};


/* Validate "built-in" OpenFlow port table actions.
 * Either returns ACT_VALIDATION_OK
 * or an OFPET_BAD_ACTION error code. */
static uint16_t
validate_ofppat(struct datapath *dp, const struct ofp_action_header *ah,
				uint16_t type, uint16_t len)
{
    int ret = ACT_VALIDATION_OK;
    const struct openflow_vport_action *act = &port_actions[type];
    if ((len < act->min_size) || (len > act->max_size)) {
        return OFPBAC_BAD_LEN;
    }

    if (act->validate) {
        ret = act->validate(dp, ah);
    }

    return ret;
}


/* Validates a list of port table entry actions in the same spirit as
 * for the flow table. If a problem is found, a code for the
 * OFPET_BAD_ACTION error type is returned.  If the action list validates,
 * ACT_VALIDATION_OK is returned. */
uint16_t
validate_vport_actions(struct datapath *dp, const struct ofp_action_header *actions,
					   size_t actions_len)
{
    uint8_t *p = (uint8_t *)actions;
    int err;

    while (actions_len >= sizeof(struct ofp_action_header)) {
        struct ofp_action_header *ah = (struct ofp_action_header *)p;
        size_t len = ntohs(ah->len);
        uint16_t type;

        /* Make there's enough remaining data for the specified length
         * and that the action length is a multiple of 64 bits. */
        if ((actions_len < len) || (len % 8) != 0) {
            return OFPBAC_BAD_LEN;
        }

        type = ntohs(ah->type);
        if (type < ARRAY_SIZE(port_actions)) {
            err = validate_ofppat(dp, ah, type, len);
            if (err != ACT_VALIDATION_OK) {
                return err;
            }
        } else {
            return OFPBAC_BAD_TYPE;
        }

        p += len;
        actions_len -= len;
    }

    /* Check if there's any trailing garbage. */
    if (actions_len != 0) {
        return OFPBAC_BAD_LEN;
    }

    return ACT_VALIDATION_OK;
}

/* Executes alist of port table entry actions in the same spirit as
 * for the flow table. */
void execute_vport_actions(struct datapath *dp, struct ofpbuf *buffer,
						  struct sw_flow_key *key,
						  const struct ofp_action_header *actions, size_t actions_len)
{
	/* Every output action needs a separate clone of 'buffer', but the common
     * case is just a single output action, so that doing a clone and then
     * freeing the original buffer is wasteful.  So the following code is
     * slightly obscure just to avoid that. */
    unsigned int prev_port;
    size_t max_len=0;     /* Initialze to make compiler happy */
    uint16_t in_port = ntohs(key->flow.in_port);
    uint8_t *p = (uint8_t *)actions;
    uint16_t type;
    const struct openflow_vport_action *act;
    struct ofp_action_output *oa;

    prev_port = -1;
    /* The action list was already validated, so we can be a bit looser
     * in our sanity-checking. */
    while (actions_len > 0) {
		struct ofp_action_header *ah = (struct ofp_action_header *)p;
		size_t len = htons(ah->len);
		if (prev_port != -1) {
			 do_output(dp, ofpbuf_clone(buffer), in_port, max_len,
					   prev_port, false);
			 prev_port = -1;
		}
		if (ah->type == htons(OFPAT_OUTPUT)) {
			 oa = (struct ofp_action_output *)p;
			 prev_port = ntohl(oa->port);
			 max_len = ntohs(oa->max_len);
		} else {
			 type = ntohs(ah->type);
			 if (type < ARRAY_SIZE(port_actions)) {
				 act = &port_actions[type];
				 if (act->execute) {
					 act->execute(dp, buffer, key, ah);
				 }
			 }
		}

        p += len;
		actions_len -= len;
	 }
	 if (prev_port != -1) {
		 do_output(dp, buffer, in_port, max_len, prev_port, false);
	 }
}


// MAH: end
