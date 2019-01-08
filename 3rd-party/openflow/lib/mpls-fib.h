// MAH: start
// This file defines our representation for the Forwarding Information Base
// (FIB) for an MPLS-enabled OpenFlow switch. An MPLS switch has 2 types of
// forwarding tables, an Incoming Label Map (ILM) and an FEC To NHLFE (FTN)
// table. An entry in either of these tables maps to one or more Next Hop
// Label Forwarding Entries (NHFLE) which contain a list of MPLS actions
// to perform (i.e. push, pop, swap). These actions can be performed
// in different ways using the MPLS extensions to OpenFlow. As a result the
// NHLFE action entries can take different forms depending on the capabilities
// of the switch.
#ifndef MPLS_FIB_H
#define MPLS_FIB_H 1

struct mpls_switch;

// Parameters needed to define an MPLS pop action in OpenFlow
struct pop_params {
	uint32_t out_port;
	uint8_t src_mac[ETH_ADDR_LEN];
	uint8_t dst_mac[ETH_ADDR_LEN];
};

// Parameters needed to define an MPLS push action in OpenFLow
struct push_params {
        uint32_t out_port;
        uint8_t src_mac[ETH_ADDR_LEN];
        uint8_t dst_mac[ETH_ADDR_LEN];
        uint32_t mpls_label;
};

// Parameters needed to define an MPLS swap action in OpenFlow
struct swap_params {
        uint32_t out_port;
        uint8_t src_mac[ETH_ADDR_LEN];
        uint8_t dst_mac[ETH_ADDR_LEN];
        uint32_t mpls_label;
};

// The header of the data structure for an action in an NHLFE entry
struct ofp_mpls_op_header {
	uint16_t type;
	uint16_t len;
};

// Next Hop Label Forwarding Entry, implemented as a link-list
typedef struct mpls_nhlfe {
	struct mpls_nhlfe *next_entry;

	// the length in bytes of the list of actions below
	uint32_t actions_len;
	// actions is a list of push, pop, and swap options defined above
	void *actions;
} nhlfe, *nhlfePtr;

// Incoming Label Map, implemented as a link-list
typedef struct mpls_ilm {
	// ILM maps an incoming label to a
	// set of Next Hop Label Forwarding Entries

	struct mpls_ilm *next_entry;

	// ingress port for packet
	uint32_t in_port;

	// packet's label
	uint32_t mpls_label;

	// List of Next Hop Label Forwarding Entries
	struct mpls_nhlfe *nhlfe;
} ilm, *ilmPtr;

// FEC-TO-NHLFE, implemented as a link-list
typedef struct mpls_ftn {
	// FTN maps a Forward Equivalence Class (FEC)
	// to a set of Next Hop Label Forwarding Entries

	struct mpls_ftn *next_entry;

	// Use OpenFlow's flow struct to define the FEC
	// note these values will be in host byte order
	struct ofp_match FEC;

	// Next Hop Label Forwarding Entry
	struct mpls_nhlfe *nhlfe;
} ftn, *ftnPtr;

// FIB for an MPLS switch consists of a FTN table and an ILM table
typedef struct mpls_fib {
	ftnPtr ftnTable;
	ilmPtr ilmTable;
} mplsFib, *mplsFibPtr;

// destroy FIB table
void destroy_mpls_fib(mplsFibPtr fib);

// Iterate through the list of actions in the NHLFE entry and send the relevant
// OF messages to the switch to install the action
void install_nhlfe_actions(struct mpls_switch *sw, struct rconn *rconn, struct mpls_nhlfe *nhlfe);

// Iterate through the list of actions in the NHFLE entry and send the relevant
// OF message to remove the previously installed action from the switch
void remove_nhlfe_actions(struct mpls_switch *sw, struct rconn *rconn, struct mpls_nhlfe *nhlfe);

// XXX TODO support statistics
// void stats_nhfle_actions(...)

// The MPLS operations push, pop, and swap can be implemented in different
// ways using the MPLS extensions to OpenFlow (e.g. swap can be done via
// a pop_mpls followed by a push_mpls or by a set_mpls_label)
// The following lists the different supported possibilities
enum {
	OFP_MPLS_UNSUPPORTED, // Indicates the switch doesn't support the operation

	OFP_MPLS_POP_OP1,	// rewrite MAC addresses at flow table and send to
						// vport where the OpenFlow MPLS pop is performed

	OFP_MPLS_POP_OP2,	// XXX NOT IMPLEMENTED XXX

	OFP_MPLS_PUSH_OP1,	// rewrite MAC addresses at flow table and send to
						// vport where the OpenFlow MPLS push is performed

	OFP_MPLS_PUSH_OP2,	// XXX NOT IMPLEMENTED XXX

	OFP_MPLS_SWAP_OP1,	// rewrite MAC addresses at flow table and send to
						// a vport to perform the OpenFlow pop action
						// the vport's parent is another vport which performs
						// the OpenFlow push action

	OFP_MPLS_SWAP_OP2	// XXX NOT IMPLEMENTED XXX
};

// The controller must chose which of the above options it should
// use to implement the MPLS operations in OpenFlow for a given switch.
// The data structure below stores those options
typedef struct mpls_switch_operations {
	int pop_option;
	int push_option;
	int swap_option;
} mplsOps, *mplsOpsPtr;


// Build an OpenFlow NHLFE action for pop
// based on the pop option chosen (OFP_MPLS_POP_OP*)
struct ofp_mpls_op_header* make_pop_action(struct mpls_switch *sw,
										   struct pop_params *pop,
										   struct ofp_match *match);

// Build an OpenFlow NHLFE action for push
// based on the push option chosen (OFP_MPLS_PUSH_OP*)
struct ofp_mpls_op_header* make_push_action(struct mpls_switch *sw,
											struct push_params *push,
											struct ofp_match *match);

// Build an OpenFlow NHLFE action for swap
// based on the swap option chosen (OFP_MPLS_SWAP_OP*)
struct ofp_mpls_op_header* make_swap_action(struct mpls_switch *sw,
											struct swap_params *swap,
											struct ofp_match *match);


// Option 1 to perform a pop action in OpenFlow:
// rewrite src/dst MAC addresses at flow table and send to a virtual port
// perform the mpls_pop action at the virtual port and send the packet
// to the parent physical port
struct ofp_mpls_pop_op1 {
	uint16_t type;			// = OFP_MPLS_POP_OP1
	uint16_t len;			// = sizeof(struct ofp_mpls_pop_op1)
	uint32_t parent_port;	// XXX rename
	uint32_t vport; 		// vport for pop action
	struct ofp_match match;	// 12-tuple of flow
	uint8_t src_mac[ETH_ADDR_LEN]; // src address for outgoing packet
	uint8_t dst_mac[ETH_ADDR_LEN]; // dst address for outgoing packet
	uint8_t flags;			// flags for the OpenFlow pop action
};

// Option 1 to perform a push action in OpenFlow;
// rewrite src/dst MAC addresses at flow table and send to a virtual port
// perform the mpls_push action at the virtual port and send the packet
// to the parent physical port
struct ofp_mpls_push_op1 {
	uint16_t type;	// = OFP_MPLS_PUSH_OP1
	uint16_t len;
	uint32_t parent_port;
	uint32_t vport; 	// vport for pop action
	struct  ofp_match match;	// 12-tuple of flow
	uint8_t src_mac[ETH_ADDR_LEN];
	uint8_t dst_mac[ETH_ADDR_LEN];

	uint32_t mpls_label; // label to push
	uint8_t flags;
};

// Option 1 to perform a swap is to perform a pop and a push at the port table
// this requires two virtual ports where the first virtual port performs a pop
// and the parent virtual port performs a push
struct ofp_mpls_swap_op1 {
	uint16_t type;	// = OFP_MPLS_SWAP_OP1
	uint16_t len;
	uint32_t pop_vport; 	// vport for pop action
	uint32_t push_vport; 	// vport for push action
	// parent port for push, the parent port for pop = vport for push
	uint32_t push_parent_port;
	struct ofp_match match;	// 12-tuple of flow
	uint8_t src_mac[ETH_ADDR_LEN];
	uint8_t dst_mac[ETH_ADDR_LEN];

	uint32_t mpls_label; // label to push
	uint8_t pop_flags;
	uint8_t push_flags;
};

// Option 2 to perform a swap is to perform a pop and a push at the port table
// this requires two virtual ports where the first virtual port performs a pop
// and the parent virtual port performs a push
struct ofp_mpls_swap_op2 {
	uint16_t type;				// = OFP_MPLS_SWAP_OP2
	uint16_t len;
	uint32_t pop_vport; 		// vport for pop action
	uint32_t pop_parent_port;	// egress port
	struct ofp_match match;		// 12-tuple of flow
	uint8_t src_mac[ETH_ADDR_LEN];
	uint8_t dst_mac[ETH_ADDR_LEN];
	uint32_t mpls_label; 		// label to push
	uint8_t pop_flags;
};

#endif

// MAH: end
