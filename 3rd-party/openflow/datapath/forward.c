/*
 * Distributed under the terms of the GNU GPL version 2.
 * Copyright (c) 2007, 2008 The Board of Trustees of The Leland
 * Stanford Junior University
 */

#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/if_ether.h>
#include <linux/if_vlan.h>
#include <asm/uaccess.h>
#include <linux/types.h>
#include "forward.h"
#include "datapath.h"
#include "openflow/nicira-ext.h"
#include "dp_act.h"
#include "nx_msg.h"
#include "chain.h"
#include "flow.h"
// MAH: start
#include "pt_act.h"
// MAH: end

/* FIXME: do we need to use GFP_ATOMIC everywhere here? */


static struct sk_buff *retrieve_skb(uint32_t id);
static void discard_skb(uint32_t id);

// MAH: start
int run_through_vport_table(struct sw_chain *chain, struct sk_buff *skb,
							struct net_bridge_port *p, uint32_t vport)
{
	struct vport_table_entry *vpe;
    struct sw_flow_key key;

	// extract the flow again since we need it
	// and the layer pointers may changed
    key.wildcards = 0;
    if (flow_extract(skb, p ? p->port_no : OFPP_NONE, &key)
        && (chain->dp->flags & OFPC_FRAG_MASK) == OFPC_FRAG_DROP) {
        /* Drop fragment. */
    	kfree_skb(skb);
        return 0;
    }

    // run through the chain of port table entries
    vpe = vport_table_lookup(&chain->dp->vport_table, vport);
    chain->dp->vport_table.lookup_count++;
    if (vpe) chain->dp->vport_table.port_match_count++;
    while (vpe != NULL) {
		execute_vport_actions(chain->dp, skb, &key, vpe->port_acts->actions,
							  vpe->port_acts->actions_len);
		vport_used(vpe, skb); // update counters for virtual port
		if (vpe->parent_port_ptr == NULL) {
			// if a port table's parent_port_ptr is NULL then
			// the parent_port should be a physical port
			if (vpe->parent_port <= OFPP_VP_START) {
				// done traversing port chain, send packet to output port
				dp_output_port(chain->dp, skb, vpe->parent_port, false);
			} else {
				kfree_skb(skb);
			}
		} else {
			// increment the number of port entries accessed by chaining
			chain->dp->vport_table.chain_match_count++;
		}
		// move to the parent port entry
		vpe = vpe->parent_port_ptr;
	}

	return 0;
}
// MAH: end

/* 'skb' was received on port 'p', which may be a physical switch port, the
 * local port, or a null pointer.  Process it according to 'chain'.  Returns 0
 * if successful, in which case 'skb' is destroyed, or -ESRCH if there is no
 * matching flow, in which case 'skb' still belongs to the caller. */
int run_flow_through_tables(struct sw_chain *chain, struct sk_buff *skb,
			    struct net_bridge_port *p)
{
	/* Ethernet address used as the destination for STP frames. */
	static const uint8_t stp_eth_addr[ETH_ALEN]
		= { 0x01, 0x80, 0xC2, 0x00, 0x00, 0x01 };
	struct sw_flow_key key;
	struct sw_flow *flow;

	if (flow_extract(skb, p ? p->port_no : OFPP_NONE, &key)
	    && (chain->dp->flags & OFPC_FRAG_MASK) == OFPC_FRAG_DROP) {
		/* Drop fragment. */
		kfree_skb(skb);
		return 0;
	}

    // MAH: start
    // drop MPLS packets with TTL 1
    if (key.mpls_label1 != MPLS_INVALID_LABEL) {
    	mpls_header mpls_h;
    	mpls_h.value = ntohl(*((uint32_t*)mpls_hdr(skb)));
    	if (mpls_h.ttl == 1) {
    		// delete packet buffer
    		kfree_skb(skb);
    		// increment mpls drop counter
    		p->mpls_ttl0_dropped++;
    		return 0;
    	}
    }
    // MAH: end


	if (p && p->config & (OFPPC_NO_RECV | OFPPC_NO_RECV_STP) &&
	    p->config & (compare_ether_addr(key.dl_dst, stp_eth_addr)
			? OFPPC_NO_RECV : OFPPC_NO_RECV_STP)) {
		kfree_skb(skb);
		return 0;
	}

	flow = chain_lookup(chain, &key);
	if (likely(flow != NULL)) {
		struct sw_flow_actions *sf_acts = rcu_dereference(flow->sf_acts);
		//printk("flow matched!\n");
		flow_used(flow, skb);
		execute_actions(chain->dp, skb, &key,
				sf_acts->actions, sf_acts->actions_len, 0);
		return 0;
	} else {
		//printk("flow not matched!\n");
		return -ESRCH;
	}
}

/* 'skb' was received on port 'p', which may be a physical switch port, the
 * local port, or a null pointer.  Process it according to 'chain', sending it
 * up to the controller if no flow matches.  Takes ownership of 'skb'. */
void fwd_port_input(struct sw_chain *chain, struct sk_buff *skb,
		    struct net_bridge_port *p)
{
	WARN_ON_ONCE(skb_shared(skb));
	WARN_ON_ONCE(skb->destructor);
	if (run_flow_through_tables(chain, skb, p)) {
		dp_output_control(chain->dp, skb, fwd_save_skb(skb),
				  chain->dp->miss_send_len,
				  OFPR_NO_MATCH);
	}
}

static int
recv_hello(struct sw_chain *chain, const struct sender *sender,
	   const void *msg)
{
	return dp_send_hello(chain->dp, sender, msg);
}

static int
recv_features_request(struct sw_chain *chain, const struct sender *sender,
		      const void *msg)
{
	return dp_send_features_reply(chain->dp, sender);
}

static int
recv_get_config_request(struct sw_chain *chain, const struct sender *sender,
			const void *msg)
{
	return dp_send_config_reply(chain->dp, sender);
}

static int
recv_set_config(struct sw_chain *chain, const struct sender *sender,
		const void *msg)
{
	const struct ofp_switch_config *osc = msg;
	int flags;

	flags = ntohs(osc->flags) & (OFPC_SEND_FLOW_EXP | OFPC_FRAG_MASK);
	if ((flags & OFPC_FRAG_MASK) != OFPC_FRAG_NORMAL
	    && (flags & OFPC_FRAG_MASK) != OFPC_FRAG_DROP) {
		flags = (flags & ~OFPC_FRAG_MASK) | OFPC_FRAG_DROP;
	}
	chain->dp->flags = flags;

	chain->dp->miss_send_len = ntohs(osc->miss_send_len);

	return 0;
}

static int
recv_packet_out(struct sw_chain *chain, const struct sender *sender,
		const void *msg)
{
	const struct ofp_packet_out *opo = msg;
	struct sk_buff *skb;
	uint16_t v_code;
	struct sw_flow_key key;
	size_t actions_len = ntohs(opo->actions_len);

	if (actions_len > (ntohs(opo->header.length) - sizeof *opo)) {
		if (net_ratelimit())
			printk("message too short for number of actions\n");
		return -EINVAL;
	}

	if (ntohl(opo->buffer_id) == (uint32_t) -1) {
		int data_len = ntohs(opo->header.length) - sizeof *opo - actions_len;

		/* FIXME: there is likely a way to reuse the data in msg. */
		skb = alloc_skb(data_len, GFP_ATOMIC);
		if (!skb)
			return -ENOMEM;

		/* FIXME?  We don't reserve NET_IP_ALIGN or NET_SKB_PAD since
		 * we're just transmitting this raw without examining anything
		 * at those layers. */
		skb_put(skb, data_len);
		skb_copy_to_linear_data(skb,
					(uint8_t *)opo->actions + actions_len,
					data_len);
		skb_reset_mac_header(skb);
	} else {
		skb = retrieve_skb(ntohl(opo->buffer_id));
		if (!skb)
			return -ESRCH;
	}

	dp_set_origin(chain->dp, ntohs(opo->in_port), skb);

	flow_extract(skb, ntohs(opo->in_port), &key);

	v_code = validate_actions(chain->dp, &key, opo->actions, actions_len);
	if (v_code != ACT_VALIDATION_OK) {
		dp_send_error_msg(chain->dp, sender, OFPET_BAD_ACTION, v_code,
				  msg, ntohs(opo->header.length));
		goto error;
	}

	execute_actions(chain->dp, skb, &key, opo->actions, actions_len, 1);

	return 0;

error:
	kfree_skb(skb);
	return -EINVAL;
}

static int
recv_port_mod(struct sw_chain *chain, const struct sender *sender,
	      const void *msg)
{
	const struct ofp_port_mod *opm = msg;

	dp_update_port_flags(chain->dp, opm);

	return 0;
}

static int
recv_echo_request(struct sw_chain *chain, const struct sender *sender,
		  const void *msg)
{
	return dp_send_echo_reply(chain->dp, sender, msg);
}

static int
recv_echo_reply(struct sw_chain *chain, const struct sender *sender,
		  const void *msg)
{
	return 0;
}

static int
add_flow(struct sw_chain *chain, const struct sender *sender,
		const struct ofp_flow_mod *ofm)
{
	int error = -ENOMEM;
	uint16_t v_code;
	struct sw_flow *flow;
	size_t actions_len = ntohs(ofm->header.length) - sizeof *ofm;

	/* Allocate memory. */
	flow = flow_alloc(actions_len, GFP_ATOMIC);
	if (flow == NULL)
		goto error;

	flow_extract_match(&flow->key, &ofm->match);

	v_code = validate_actions(chain->dp, &flow->key, ofm->actions, actions_len);
	if (v_code != ACT_VALIDATION_OK) {
		dp_send_error_msg(chain->dp, sender, OFPET_BAD_ACTION, v_code,
				  ofm, ntohs(ofm->header.length));
		goto error_free_flow;
	}

	/* Fill out flow. */
	flow->priority = flow->key.wildcards ? ntohs(ofm->priority) : -1;
	flow->idle_timeout = ntohs(ofm->idle_timeout);
	flow->hard_timeout = ntohs(ofm->hard_timeout);
	flow->used = jiffies;
	flow->init_time = jiffies;
	flow->byte_count = 0;
	flow->packet_count = 0;
	spin_lock_init(&flow->lock);
	memcpy(flow->sf_acts->actions, ofm->actions, actions_len);

	/* Act. */
	error = chain_insert(chain, flow);
	if (error == -ENOBUFS) {
		dp_send_error_msg(chain->dp, sender, OFPET_FLOW_MOD_FAILED,
				OFPFMFC_ALL_TABLES_FULL, ofm, ntohs(ofm->header.length));
		goto error_free_flow;
	} else if (error)
		goto error_free_flow;
	error = 0;
	if (ntohl(ofm->buffer_id) != (uint32_t) -1) {
		struct sk_buff *skb = retrieve_skb(ntohl(ofm->buffer_id));
		if (skb) {
			struct sw_flow_key key;
			flow_used(flow, skb);
			dp_set_origin(chain->dp, ntohs(ofm->match.in_port), skb);
			flow_extract(skb, ntohs(ofm->match.in_port), &key);
			execute_actions(chain->dp, skb, &key, ofm->actions, actions_len, 0);
		}
		else
			error = -ESRCH;
	}
	return error;

error_free_flow:
	flow_free(flow);
error:
	if (ntohl(ofm->buffer_id) != (uint32_t) -1)
		discard_skb(ntohl(ofm->buffer_id));
	return error;
}

// MAH: start
/* Add a virtual port table entry. */
int
add_vport(struct sw_chain *chain, const struct sender *sender,
		  const struct ofp_vport_mod *ovpm)
{
	int error = 0;
	uint16_t v_code;
	unsigned int vport, parent_port;
	struct vport_table_entry *vpe;
	size_t actions_len;

	actions_len = ntohs(ovpm->header.length) - sizeof *ovpm;
	vport = ntohl(ovpm->vport);
	parent_port = ntohl(ovpm->parent_port);

	// check whether port table entry exists for specified port number
	vpe = vport_table_lookup(&(chain->dp->vport_table), vport);
	if (vpe != NULL) {
		printk("vport %u already exists!\n", vport);
		dp_send_error_msg(chain->dp, sender, OFPET_BAD_ACTION, OFPET_VPORT_MOD_FAILED,
		                  ovpm, ntohs(ovpm->header.length));
		return EINVAL;
	}
	// check whether actions are valid
    v_code = validate_vport_actions(chain->dp, ovpm->actions, actions_len);
    if (v_code != ACT_VALIDATION_OK) {
        dp_send_error_msg(chain->dp, sender, OFPET_BAD_ACTION, v_code,
						  ovpm, ntohs(ovpm->header.length));
        return EINVAL;
    }

	vpe = vport_table_entry_alloc(actions_len);

	vpe->vport = vport;
	vpe->parent_port = parent_port;
	if (!(vport >= OFPP_VP_START && vport <= OFPP_VP_END)) {
		printk("port %u is not in the virtual port range (%u-%u)", vport, OFPP_VP_START, OFPP_VP_END);
		dp_send_error_msg(chain->dp, sender, OFPET_BAD_ACTION, OFPET_VPORT_MOD_FAILED,
		                  ovpm, ntohs(ovpm->header.length));
		free_vport_table_entry(vpe); // free allocated entry
		return EINVAL;
	}

	vpe->port_acts->actions_len = actions_len;
	memcpy(vpe->port_acts->actions, ovpm->actions, actions_len);

	error = insert_vport_table_entry(&chain->dp->vport_table, vpe);
	if (error) {
		printk("could not insert port table entry for port %u\n", vport);
	}

    return error;

}
// MAH: end

static int
mod_flow(struct sw_chain *chain, const struct sender *sender,
		const struct ofp_flow_mod *ofm)
{
	int error = -ENOMEM;
	uint16_t v_code;
	size_t actions_len;
	struct sw_flow_key key;
	uint16_t priority;
	int strict;

	flow_extract_match(&key, &ofm->match);

	actions_len = ntohs(ofm->header.length) - sizeof *ofm;

	v_code = validate_actions(chain->dp, &key, ofm->actions, actions_len);
	if (v_code != ACT_VALIDATION_OK) {
		dp_send_error_msg(chain->dp, sender, OFPET_BAD_ACTION, v_code,
				  ofm, ntohs(ofm->header.length));
		goto error;
	}

	priority = key.wildcards ? ntohs(ofm->priority) : -1;
	strict = (ofm->command == htons(OFPFC_MODIFY_STRICT)) ? 1 : 0;
	chain_modify(chain, &key, priority, strict, ofm->actions, actions_len);

	if (ntohl(ofm->buffer_id) != (uint32_t) -1) {
		struct sk_buff *skb = retrieve_skb(ntohl(ofm->buffer_id));
		if (skb) {
			struct sw_flow_key skb_key;
			flow_extract(skb, ntohs(ofm->match.in_port), &skb_key);
			execute_actions(chain->dp, skb, &skb_key,
					ofm->actions, actions_len, 0);
		}
		else
			error = -ESRCH;
	}
	return error;

error:
	if (ntohl(ofm->buffer_id) != (uint32_t) -1)
		discard_skb(ntohl(ofm->buffer_id));
	return error;
}

static int
recv_flow(struct sw_chain *chain, const struct sender *sender, const void *msg)
{
	const struct ofp_flow_mod *ofm = msg;
	uint16_t command = ntohs(ofm->command);

	if (command == OFPFC_ADD) {
		return add_flow(chain, sender, ofm);
	} else if ((command == OFPFC_MODIFY) || (command == OFPFC_MODIFY_STRICT)) {
		return mod_flow(chain, sender, ofm);
	}  else if (command == OFPFC_DELETE) {
		struct sw_flow_key key;
		flow_extract_match(&key, &ofm->match);
		return chain_delete(chain, &key, ofm->out_port, 0, 0) ? 0 : -ESRCH;
	} else if (command == OFPFC_DELETE_STRICT) {
		struct sw_flow_key key;
		uint16_t priority;
		flow_extract_match(&key, &ofm->match);
		priority = key.wildcards ? ntohs(ofm->priority) : -1;
		return chain_delete(chain, &key, ofm->out_port,
				priority, 1) ? 0 : -ESRCH;
	} else {
		return -ENOTSUPP;
	}
}

// MAH: start
/* add or remove a virtual port table entry */
static int
recv_vport_mod(struct sw_chain *chain, const struct sender *sender, const void *msg)
{
    const struct ofp_vport_mod *ovpm = msg;
    uint16_t command = ntohs(ovpm->command);

    if (command == OFPVP_ADD) {
        return add_vport(chain, sender, ovpm);
    } else if (command == OFPVP_DELETE) {
    	if (remove_vport_table_entry(&chain->dp->vport_table, ntohl(ovpm->vport))) {
			printk("could not remove_vport_table_entry %u\n", ntohl(ovpm->vport));
			return -EINVAL;
		}
    }

    return 0;
}
// MAH: end

// MAH: start
static int
recv_vport_table_features_request(struct sw_chain *chain, const struct sender *sender,
								  const void *msg)
{
	dp_send_vport_table_features(chain->dp, sender);
	return 0;
}
// MAH: end

static int
recv_vendor(struct sw_chain *chain, const struct sender *sender,
		const void *msg)
{
	const struct ofp_vendor_header *ovh = msg;

	switch(ntohl(ovh->vendor))
	{
	case NX_VENDOR_ID:
		return nx_recv_msg(chain, sender, msg);
	default:
		if (net_ratelimit())
			printk("Uknown vendor: %#x\n", ntohl(ovh->vendor));
		dp_send_error_msg(chain->dp, sender, OFPET_BAD_REQUEST,
				  OFPBRC_BAD_VENDOR, msg, ntohs(ovh->header.length));
		return -EINVAL;
	}
}

/* 'msg', which is 'length' bytes long, was received across Netlink from
 * 'sender'.  Apply it to 'chain'. */
int
fwd_control_input(struct sw_chain *chain, const struct sender *sender,
		  const void *msg, size_t length)
{

	struct openflow_packet {
		size_t min_size;
		int (*handler)(struct sw_chain *, const struct sender *,
			       const void *);
	};

	static const struct openflow_packet packets[] = {
		[OFPT_HELLO] = {
			sizeof (struct ofp_header),
			recv_hello,
		},
		[OFPT_ECHO_REQUEST] = {
			sizeof (struct ofp_header),
			recv_echo_request,
		},
		[OFPT_ECHO_REPLY] = {
			sizeof (struct ofp_header),
			recv_echo_reply,
		},
		[OFPT_VENDOR] = {
			sizeof (struct ofp_vendor_header),
			recv_vendor,
		},
		[OFPT_FEATURES_REQUEST] = {
			sizeof (struct ofp_header),
			recv_features_request,
		},
		[OFPT_GET_CONFIG_REQUEST] = {
			sizeof (struct ofp_header),
			recv_get_config_request,
		},
		[OFPT_SET_CONFIG] = {
			sizeof (struct ofp_switch_config),
			recv_set_config,
		},
		[OFPT_PACKET_OUT] = {
			sizeof (struct ofp_packet_out),
			recv_packet_out,
		},
		[OFPT_FLOW_MOD] = {
			sizeof (struct ofp_flow_mod),
			recv_flow,
		},
		[OFPT_PORT_MOD] = {
			sizeof (struct ofp_port_mod),
			recv_port_mod,
		},
		// MAH: start
		[OFPT_VPORT_MOD] = {
			sizeof(struct ofp_vport_mod),
			recv_vport_mod,
		},
		[OFPT_VPORT_TABLE_FEATURES_REQUEST] = {
			 sizeof(struct ofp_header),
			 recv_vport_table_features_request,
		}
    	// MAH: end
	};

	struct ofp_header *oh;

	oh = (struct ofp_header *) msg;
	if (oh->version != OFP_VERSION
	    && oh->type != OFPT_HELLO
	    && oh->type != OFPT_ERROR
	    && oh->type != OFPT_ECHO_REQUEST
	    && oh->type != OFPT_ECHO_REPLY
	    && oh->type != OFPT_VENDOR)
	{
		dp_send_error_msg(chain->dp, sender, OFPET_BAD_REQUEST,
				  OFPBRC_BAD_VERSION, msg, length);
		return -EINVAL;
	}
	if (ntohs(oh->length) != length) {
		if (net_ratelimit())
			printk("received message length wrong: %d/%d\n",
				ntohs(oh->length), length);
		return -EINVAL;
	}

	if (oh->type < ARRAY_SIZE(packets)) {
		const struct openflow_packet *pkt = &packets[oh->type];
		if (pkt->handler) {
			if (length < pkt->min_size)
				return -EFAULT;
			return pkt->handler(chain, sender, msg);
		}
	}
	dp_send_error_msg(chain->dp, sender, OFPET_BAD_REQUEST,
			  OFPBRC_BAD_TYPE, msg, length);
	return -EINVAL;
}

/* Packet buffering. */

#define OVERWRITE_SECS	1
#define OVERWRITE_JIFFIES (OVERWRITE_SECS * HZ)

struct packet_buffer {
	struct sk_buff *skb;
	uint32_t cookie;
	unsigned long exp_jiffies;
};

static struct packet_buffer buffers[N_PKT_BUFFERS];
static unsigned int buffer_idx;
static DEFINE_SPINLOCK(buffer_lock);

uint32_t fwd_save_skb(struct sk_buff *skb)
{
	struct sk_buff *old_skb = NULL;
	struct packet_buffer *p;
	unsigned long int flags;
	uint32_t id;

	/* FIXME: Probably just need a skb_clone() here. */
	skb = skb_copy(skb, GFP_ATOMIC);
	if (!skb)
		return -1;

	spin_lock_irqsave(&buffer_lock, flags);
	buffer_idx = (buffer_idx + 1) & PKT_BUFFER_MASK;
	p = &buffers[buffer_idx];
	if (p->skb) {
		/* Don't buffer packet if existing entry is less than
		 * OVERWRITE_SECS old. */
		if (time_before(jiffies, p->exp_jiffies)) {
			spin_unlock_irqrestore(&buffer_lock, flags);
			kfree_skb(skb);
			return -1;
		} else {
			/* Defer kfree_skb() until interrupts re-enabled.
			 * FIXME: we only need to do that if it has a
			 * destructor, but it never should since we orphan
			 * sk_buffs on entry. */
			old_skb = p->skb;
		}
	}
	/* Don't use maximum cookie value since the all-bits-1 id is
	 * special. */
	if (++p->cookie >= (1u << PKT_COOKIE_BITS) - 1)
		p->cookie = 0;
	p->skb = skb;
	p->exp_jiffies = jiffies + OVERWRITE_JIFFIES;
	id = buffer_idx | (p->cookie << PKT_BUFFER_BITS);
	spin_unlock_irqrestore(&buffer_lock, flags);

	if (old_skb)
		kfree_skb(old_skb);

	return id;
}

static struct sk_buff *retrieve_skb(uint32_t id)
{
	unsigned long int flags;
	struct sk_buff *skb = NULL;
	struct packet_buffer *p;

	spin_lock_irqsave(&buffer_lock, flags);
	p = &buffers[id & PKT_BUFFER_MASK];
	if (p->cookie == id >> PKT_BUFFER_BITS) {
		skb = p->skb;
		p->skb = NULL;
	} else {
		printk("cookie mismatch: %x != %x\n",
				id >> PKT_BUFFER_BITS, p->cookie);
	}
	spin_unlock_irqrestore(&buffer_lock, flags);

	return skb;
}

void fwd_discard_all(void)
{
	int i;

	for (i = 0; i < N_PKT_BUFFERS; i++) {
		struct sk_buff *skb;
		unsigned long int flags;

		/* Defer kfree_skb() until interrupts re-enabled. */
		spin_lock_irqsave(&buffer_lock, flags);
		skb = buffers[i].skb;
		buffers[i].skb = NULL;
		spin_unlock_irqrestore(&buffer_lock, flags);

		kfree_skb(skb);
	}
}

static void discard_skb(uint32_t id)
{
	struct sk_buff *old_skb = NULL;
	unsigned long int flags;
	struct packet_buffer *p;

	spin_lock_irqsave(&buffer_lock, flags);
	p = &buffers[id & PKT_BUFFER_MASK];
	if (p->cookie == id >> PKT_BUFFER_BITS) {
		/* Defer kfree_skb() until interrupts re-enabled. */
		old_skb = p->skb;
		p->skb = NULL;
	}
	spin_unlock_irqrestore(&buffer_lock, flags);

	if (old_skb)
		kfree_skb(old_skb);
}

void fwd_exit(void)
{
	fwd_discard_all();
}
