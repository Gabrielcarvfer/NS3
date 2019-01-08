// MAH: start
// Much like switch-flow contains the flow-table functionality,
// this switch-port contains the virtual port table functionality.
#ifndef SWITCH_PORT_H
#define SWITCH_PORT_H 1

#include "openflow/openflow.h"
#include "kred-black-tree.h"
#include <linux/skbuff.h>

// Maximum number of allowed port table entries:
// let software switch can support the whole virtual port space.
#define MAX_VPORT_TABLE_SIZE	(OFPP_VP_END-OFPP_VP_START)

struct vport_table_t
{
    // We need an efficient data structure to store the virtual ports
    // since we obviously can't preallocate all 2^32 possible entries
    // Currently use a red-black tree... offers lookup speed near that
    // of a balanced binary-tree with an insert/remove that's on average
	// much less expensive
    rb_red_blk_tree* table;

    uint32_t max_vports;    	/* Max number of entries supported. 				*/
    uint32_t active_vports;   	/* Number of active entries. 						*/
    uint64_t lookup_count;   	/* Number of port entries looked up in port table.	*/
    uint64_t port_match_count;  /* Number of entries looked up in port table. 		*/
    uint64_t chain_match_count; /* Number of entries accessed by chaining. 			*/
};

struct sw_vport_actions {
    size_t actions_len;
    struct ofp_action_header actions[0];
};

struct vport_table_entry
{
  unsigned int vport;		/* virtual port number. */

  rb_red_blk_node *node;	/* pointer to this entry's node in the red-black tree. */

  uint32_t parent_port;  	/* the port number of the parent port. */

  struct vport_table_entry *parent_port_ptr;	/* pointer to parent port entry for convenience. */

  uint64_t packet_count;    /* Number of packets in flow. */
  uint64_t byte_count;      /* Number of bytes in flow. */

  struct sw_vport_actions *port_acts; /* port table entry's actions. */
};


void vport_table_init(struct vport_table_t *vport_table);
struct vport_table_entry *vport_table_entry_alloc(size_t actions_len);
void free_vport_table_entry(struct vport_table_entry *vpe);
struct vport_table_entry *vport_table_lookup(struct vport_table_t *vport_table, unsigned int vport);
int insert_vport_table_entry(struct vport_table_t *vport_table, struct vport_table_entry *vpe);
int remove_vport_table_entry(struct vport_table_t *vport_table, unsigned int vport);
void vport_used(struct vport_table_entry *vpe, struct sk_buff *skb);

#endif

// MAH: end

