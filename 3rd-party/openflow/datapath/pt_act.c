// MAH: start
/* Port table actions. */

#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include "compat.h"
#include <linux/if_ether.h>
#include <linux/if_vlan.h>
#include <net/llc_pdu.h>
#include <linux/ip.h>
#include <linux/jiffies.h>
#include <linux/kernel.h>
#include <linux/llc.h>
#include <linux/module.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/icmp.h>
#include <linux/in.h>
#include <linux/rcupdate.h>
#include <net/ip.h>

#include <linux/skbuff.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/in6.h>
#include <linux/if_vlan.h>
#include <net/checksum.h>
#include "pt_act.h"
#include "dp_act.h"

void sk_buff_pop_mpls(struct sk_buff *skb, mpls_header *mpls_h);
void sk_buff_push_mpls(struct sk_buff *skb, mpls_header *mpls_h);


static inline void set_last_mpls_hdr(struct sk_buff *skb, mpls_header* mpls_h)
{
	char *last_word = (char*)skb->end - sizeof(mpls_h);
	// remember the label at the top of the stack
	// this is needed when we implement swap using a pop followed by a push
	// store it in the last 4 bytes of skb which should be free
	if ((char*)skb->end - (char*)skb->tail < sizeof(mpls_header)) {
		printk("could not save last popped label to buffer\n");
		return;
	}
	// stored in host byte order
    memcpy(last_word, mpls_h, sizeof(mpls_header));
}


static inline mpls_header *get_last_mpls_hdr(struct sk_buff *skb)
{
	char *last_word = (char*)skb->end - sizeof(mpls_header);
	// returned in host byte order
	return (mpls_header *)last_word;
}


static void
pt_pop_mpls_act(struct datapath *dp, struct sk_buff *skb, struct sw_flow_key *key,
        const struct ofp_action_header *ah)
{
	struct ofp_vport_action_pop_mpls *opapm = (struct ofp_vport_action_pop_mpls *)ah;
	//printk("pt_pop_mpls_act invoked\n");
	pop_mpls_act(dp, skb, key, &opapm->apm);
}

static void
pt_push_mpls_act(struct datapath *dp, struct sk_buff *skb, struct sw_flow_key *key,
        const struct ofp_action_header *ah)
{
	struct ofp_vport_action_push_mpls *opapm = (struct ofp_vport_action_push_mpls *)ah;
	//printk("pt_push_mpls_act invoked\n");
	push_mpls_act(dp, skb, key, &opapm->apm);
}


static void
pt_set_mpls_label_act(struct datapath *dp, struct sk_buff *skb, struct sw_flow_key *key,
				      const struct ofp_action_header *ah)
{
	struct ofp_vport_action_set_mpls_label *oparml = (struct ofp_vport_action_set_mpls_label *)ah;
	//printk("pt_set_mpls_label_act invoked\n");
	set_mpls_label_act(skb, key, oparml->label_out);
}

static void
pt_set_mpls_exp_act(struct datapath *dp, struct sk_buff *skb, struct sw_flow_key *key,
				    const struct ofp_action_header *ah)
{
	struct ofp_vport_action_set_mpls_exp *oparme = (struct ofp_vport_action_set_mpls_exp *)ah;
	//printk("pt_set_mpls_exp_act invoked\n");
	set_mpls_exp_act(skb, key, oparme->exp);
}


static void inline
update_checksums(struct sk_buff *skb, const struct sw_flow_key *key,
				 uint32_t old_word, uint32_t new_word) {
	struct iphdr *nh;
	if (key->nw_proto == IPPROTO_TCP) {
		struct tcphdr *th = tcp_hdr(skb);
		update_csum(&th->check, skb, old_word, new_word, 1);
	} else if (key->nw_proto == IPPROTO_UDP) {
		struct udphdr *th = udp_hdr(skb);
		update_csum(&th->check, skb, old_word, new_word, 1);
	}
	nh = ip_hdr(skb);
	update_csum(&nh->check, skb, old_word, new_word, 0);
}

/* pop the top MPLS label from the label stack. */
void pop_mpls_act(struct datapath *dp, struct sk_buff *skb,
				  struct sw_flow_key *key,
				  const struct action_pop_mpls *apm)
{
	struct ethhdr *eth;
	struct iphdr *nh;
	mpls_header mpls_h, mpls_h2;
	uint32_t old_word, new_word;
	char *mpls_header;
	void *word_addr;


	uint16_t eth_proto = ntohs(key->dl_type);
	//printk("pop_mpls_act invoked\n");

	// XXX TODO handle multicast MPLS
	eth = eth_hdr(skb);
    if (eth_proto == ETH_TYPE_MPLS_UNICAST) {
    	// grab the MLPS label at the top of the stack

		mpls_header = mpls_hdr(skb);
    	mpls_h.value = htonl(*(uint32_t*)mpls_header);

    	if (apm->flags & MPLS_POP_DECREMENT_TTL) {
    		// decrement the ttl and write the updated value back to the packet
    		mpls_h.ttl--;
    		*((uint32_t *)mpls_header) = htonl(mpls_h.value);
    	}
    	// remember the label at the top of the stack
    	set_last_mpls_hdr(skb, &mpls_h);

    	if (!(apm->flags & MPLS_POP_DONT_POP)) {
			sk_buff_pop_mpls(skb, &mpls_h);
    	} else {
        	return; // do nothing else
		}

        if (mpls_h.s) {
        	set_ethertype(skb, apm->eth_type);
        	key->dl_type = apm->eth_type;
        }

        // If this is the last label on the stack
        if (mpls_h.s) {
    		nh = ip_hdr(skb);

			// if the COPY_TTL flag is set then copy the MPLS ttl bits
    		// back to the IP header
        	if (apm->flags & MPLS_POP_COPY_TTL) {
        		// copy the TTL from the popped label into the IP header
        		word_addr = (void*)((uint32_t*)nh + 2);
        		old_word = *((uint32_t*)word_addr);
        		nh->ttl = ((uint8_t)mpls_h.ttl);
        		new_word = *((uint32_t*)word_addr);

        		update_checksums(skb, key, old_word, new_word);
        	}
        	// if the COPY_EXP flaq is set then replace the type of service bits in the IP
        	// header with the exp bits from the MPLS header
        	if (apm->flags & MPLS_POP_COPY_EXP) {
        		// copy the TTL from the popped label into the IP header
        		word_addr = (void*)nh;
        		old_word = *((uint32_t*)word_addr);
        		nh->tos = mpls_h.exp;
        		new_word = *((uint32_t*)word_addr);

        		update_checksums(skb, key, old_word, new_word);
        	}
        } else {
        	// if this is not the last label on the stack
        	// get the next label
        	mpls_h2.value =  htonl(*(uint32_t*)mpls_header);

        	if (apm->flags & MPLS_POP_COPY_TTL) {
        		mpls_h2.ttl = mpls_h.ttl;
        	}
        	if (apm->flags & MPLS_POP_COPY_EXP) {
        		mpls_h2.exp = mpls_h.exp;
        	}

        	// copy the updated copy of the second label back
        	// to the packet
        	*((uint32_t *)mpls_header) = htonl(mpls_h2.value);
        }
    }

}


/* push an MPLS label onto the label stack. */
void push_mpls_act(struct datapath *dp, struct sk_buff *skb,
				   struct sw_flow_key *key,
				   const struct action_push_mpls *apm)
{
	struct iphdr *nh;
	mpls_header mpls_h;
	mpls_header last_mpls_h;
	uint16_t eth_proto;
	size_t offset;
	//printk("push_mpls_act invoked remaining headroom = %d\n", (char *)skb->data - (char*)skb->head);


	offset = (char*)mpls_hdr(skb) - (char*)skb->data;

	eth_proto = ntohs(key->dl_type);
	mpls_h.label = ntohl(apm->label_out);
	last_mpls_h.value = get_last_mpls_hdr(skb)->value;
	nh = ip_hdr(skb);


	// first check whether there is another label on the stack
	if (eth_proto == ETH_TYPE_MPLS_UNICAST) {
		mpls_h.s = 0; // must be 0
	} else if (eth_proto == ETH_P_IP) {
    	mpls_h.s = 1; // bottom of stack
		// also change the Ethertype to MPLS
		set_ethertype(skb, htons(ETH_TYPE_MPLS_UNICAST));
    }

	// next determine where to get the ttl and exp bits
	if (apm->flags & MPLS_PUSH_TTL_PREV) {
		// use the IP from the previous label
		mpls_h.ttl = last_mpls_h.ttl - (apm->flags & MPLS_PUSH_DECREMENT_TTL);
	} else if (apm->flags & MPLS_PUSH_TTL_NEXT) {
		// use the IP TTL
		mpls_h.ttl = nh->ttl - (apm->flags & MPLS_PUSH_DECREMENT_TTL);
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
		mpls_h.exp = nh->tos; // XXX TODO IP diff serv is 8-bits, MPLS has 3 exp bits, what do we do?
	} else {
		// use the exp bits specified by the controller
		mpls_h.exp = apm->exp;
	}

	// push on the new label
    sk_buff_push_mpls(skb, &mpls_h);
}



struct openflow_vport_action {
    size_t min_size;
    size_t max_size;
    uint16_t (*validate)(struct datapath *dp,
            const struct ofp_action_header *ah);
    void (*execute)(struct datapath *dp,
    		struct sk_buff *skb,
    		struct sw_flow_key *key,
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
void execute_vport_actions(struct datapath *dp, struct sk_buff *skb,
						  struct sw_flow_key *key,
						  const struct ofp_action_header *actions, size_t actions_len)
{
	/* Every output action needs a separate clone of 'skb', but the common
     * case is just a single output action, so that doing a clone and then
     * freeing the original skb is wasteful.  So the following code is
     * slightly obscure just to avoid that. */
    unsigned int prev_port;
    size_t max_len=0;     /* Initialize to make compiler happy */
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
			 do_output(dp, skb_clone(skb, GFP_ATOMIC), max_len,
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
					 act->execute(dp, skb, key, ah);
				 }
			 }
		}

        p += len;
		actions_len -= len;
	 }
	 if (prev_port != -1) {
		 do_output(dp, skb, max_len, prev_port, false);
	 }
}


// remove the top label in the MPLS label stack
void sk_buff_pop_mpls(struct sk_buff *skb, mpls_header *mpls_h)
{
	uint32_t offset = (char*)mpls_hdr(skb) - (char*)skb->data;

	// move everything up to L2.5 up 4 bytes
	memcpy((char*)skb->data + sizeof(mpls_header), skb->data, offset);

	// pull offset + size
	skb_pull(skb, sizeof(mpls_header));

	// reset poniter to L2
	skb_reset_mac_header(skb);
}



// add an MPLS label to the top off the label stack
void sk_buff_push_mpls(struct sk_buff *skb, mpls_header *mpls_h)
{
	// bytes before L2.5
	uint32_t offset = (char*)mpls_hdr(skb) - (char*)skb->data;

	// make sure there's room
	if ( (char*)skb->head - (char*)skb->data < sizeof(mpls_header) ) {
		printk("insufficient room in skb to push label %u\n", mpls_h->label);
		return;
	}

	// make room for new label by adding 4 bytes
	skb_push(skb, sizeof(mpls_header));

	// reset pointer to L2
	skb_reset_mac_header(skb);

	//  move L2 header to make room for new label
	memcpy(skb->data, (char*)skb->data+sizeof(mpls_header), offset);

	*((uint32_t*)mpls_hdr(skb)) = htonl(mpls_h->value);
}


// MAH: end
