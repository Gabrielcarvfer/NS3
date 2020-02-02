/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford
 * Junior University
 *
 * We are making the OpenFlow specification and associated documentation
 * (Software) available for public use and benefit with the expectation
 * that others will use, modify and enhance the Software and contribute
 * those enhancements back to the community. However, since we would
 * like to make the Software available for broadest use, with as few
 * restrictions as possible permission is hereby granted, free of
 * charge, to any person obtaining a copy of this Software to deal in
 * the Software under the copyrights without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * The name and trademarks of copyright holder(s) may NOT be used in
 * advertising or publicity pertaining to the Software or any
 * derivatives without specific, written prior permission.
 */

/* OpenFlow: protocol between controller and datapath. */

#ifndef OPENFLOW_OPENFLOW_H
#define OPENFLOW_OPENFLOW_H 1

#ifdef __KERNEL__
#include <linux/types.h>
#else
#include <stdint.h>
#endif

#ifdef SWIG
#define OFP_ASSERT(EXPR)        /* SWIG can't handle OFP_ASSERT. */
#elif !defined(__cplusplus)
/* Build-time assertion for use in a declaration context. */
#define OFP_ASSERT(EXPR)                                                \
        extern int (*build_assert(void))[ sizeof(struct {               \
                    unsigned int build_assert_failed : (EXPR) ? 1 : -1; })]
#else /* __cplusplus */
#include <boost/static_assert.hpp>
#define OFP_ASSERT BOOST_STATIC_ASSERT
#endif /* __cplusplus */

#ifndef SWIG
#define OFP_PACKED __attribute__((packed))
#else
#define OFP_PACKED              /* SWIG doesn't understand __attribute. */
#endif

/* The most significant bit being set in the version field indicates an
 * experimental OpenFlow version.
 */
#define OFP_VERSION   0x97

#define OFP_MAX_TABLE_NAME_LEN 32
#define OFP_MAX_PORT_NAME_LEN  16

#define OFP_TCP_PORT  6633
#define OFP_SSL_PORT  6633

#define OFP_ETH_ALEN 6          /* Bytes in an Ethernet address. */

/* Port numbering.  Physical ports are numbered starting from 0. */
enum ofp_port {
    /* Maximum number of physical switch ports. */
    OFPP_MAX = 0xff00,

    /* Fake output "ports". */
    OFPP_IN_PORT    = 0xfff8,  /* Send the packet out the input port.  This
                                  virtual port must be explicitly used
                                  in order to send back out of the input
                                  port. */
    OFPP_TABLE      = 0xfff9,  /* Perform actions in flow table.
                                  NB: This can only be the destination
                                  port for packet-out messages. */
    OFPP_NORMAL     = 0xfffa,  /* Process with normal L2/L3 switching. */
    OFPP_FLOOD      = 0xfffb,  /* All physical ports except input port and
                                  those disabled by STP. */
    OFPP_ALL        = 0xfffc,  /* All physical ports except input port. */
    OFPP_CONTROLLER = 0xfffd,  /* Send to controller. */
    OFPP_LOCAL      = 0xfffe,  /* Local openflow "port". */
    OFPP_NONE       = 0xffff,   /* Not associated with a physical port. */
    // MAH: start
    OFPP_VP_START	= 0x10000,	  /* start of virtual ports. */
    OFPP_VP_END		= 0x40000000 /* end of virtual ports.   */
    //OFPP_VPL_START	= 0x40000001, /* start of virtual port lists. */
    //OFPP_VPL_START	= 0xffffffff  /* end of virtual port lists. */

    // MAH: end
};

enum ofp_type {
    /* Immutable messages. */
    OFPT_HELLO,               /* Symmetric message */
    OFPT_ERROR,               /* Symmetric message */
    OFPT_ECHO_REQUEST,        /* Symmetric message */
    OFPT_ECHO_REPLY,          /* Symmetric message */
    OFPT_VENDOR,              /* Symmetric message */

    /* Switch configuration messages. */
    OFPT_FEATURES_REQUEST,    /* Controller/switch message */
    OFPT_FEATURES_REPLY,      /* Controller/switch message */
    // MAH: start
    OFPT_VPORT_TABLE_FEATURES_REQUEST, /* Controller/switch message */
    OFPT_VPORT_TABLE_FEATURES_REPLY,   /* Controller/switch message */
    // MAH: end
    OFPT_GET_CONFIG_REQUEST,  /* Controller/switch message */
    OFPT_GET_CONFIG_REPLY,    /* Controller/switch message */
    OFPT_SET_CONFIG,          /* Controller/switch message */


    /* Asynchronous messages. */
    OFPT_PACKET_IN,           /* Async message */
    OFPT_FLOW_EXPIRED,        /* Async message */
    OFPT_PORT_STATUS,         /* Async message */

    /* Controller command messages. */
    OFPT_PACKET_OUT,          /* Controller/switch message */
    OFPT_FLOW_MOD,            /* Controller/switch message */
    OFPT_PORT_MOD,            /* Controller/switch message */
    // MAH: start
    // modify virtual port
    OFPT_VPORT_MOD,			  /* Controller/switch message */
	// MAH: end

    /* Statistics messages. */
    OFPT_STATS_REQUEST,       /* Controller/switch message */
    OFPT_STATS_REPLY          /* Controller/switch message */
};

/* Header on all OpenFlow packets. */
struct ofp_header {
    uint8_t version;    /* OFP_VERSION. */
    uint8_t type;       /* One of the OFPT_ constants. */
    uint16_t length;    /* Length including this ofp_header. */
    uint32_t xid;       /* Transaction id associated with this packet.
                           Replies use the same id as was in the request
                           to facilitate pairing. */
};
OFP_ASSERT(sizeof(struct ofp_header) == 8);

/* OFPT_HELLO.  This message has an empty body, but implementations must
 * ignore any data included in the body, to allow for future extensions. */
struct ofp_hello {
    struct ofp_header header;
};

#define OFP_DEFAULT_MISS_SEND_LEN   128

enum ofp_config_flags {
    /* Tells datapath to notify the controller of expired flow entries. */
    OFPC_SEND_FLOW_EXP = 1 << 0,

    /* Handling of IP fragments. */
    OFPC_FRAG_NORMAL   = 0 << 1,  /* No special handling for fragments. */
    OFPC_FRAG_DROP     = 1 << 1,    /* Drop fragments. */
    OFPC_FRAG_REASM    = 2 << 1,   /* Reassemble (only if OFPC_IP_REASM set). */
    OFPC_FRAG_MASK     = 3 << 1
};

/* Switch configuration. */
struct ofp_switch_config {
    struct ofp_header header;
    uint16_t flags;             /* OFPC_* flags. */
    uint16_t miss_send_len;     /* Max bytes of new flow that datapath should
                                   send to the controller. */
};
OFP_ASSERT(sizeof(struct ofp_switch_config) == 12);

/* Capabilities supported by the datapath. */
enum ofp_capabilities {
    OFPC_FLOW_STATS     = 1 << 0,  /* Flow statistics. */
    OFPC_TABLE_STATS    = 1 << 1,  /* Table statistics. */
    OFPC_PORT_STATS     = 1 << 2,  /* Port statistics. */
    OFPC_STP            = 1 << 3,  /* 802.1d spanning tree. */
    OFPC_MULTI_PHY_TX   = 1 << 4,  /* Supports transmitting through multiple
                                      physical interfaces */
    OFPC_IP_REASM       = 1 << 5,   /* Can reassemble IP fragments. */
    // MAH: start
    OFPC_VPORT_TABLE	= 1 << 6	/* Supports a virtual port table
									   rest of virtual port table attributes
									   specified in ofp_vport_table_features */
    // MAH: end
};

/* Flags to indicate behavior of the physical port.  These flags are
 * used in ofp_phy_port to describe the current configuration.  They are
 * used in the ofp_port_mod message to configure the port's behavior.
 */
enum ofp_port_config {
    OFPPC_PORT_DOWN    = 1 << 0,  /* Port is administratively down. */

    OFPPC_NO_STP       = 1 << 1,  /* Disable 802.1D spanning tree on port. */
    OFPPC_NO_RECV      = 1 << 2,  /* Drop all packets except 802.1D spanning
                                     tree packets. */
    OFPPC_NO_RECV_STP  = 1 << 3,  /* Drop received 802.1D STP packets. */
    OFPPC_NO_FLOOD     = 1 << 4,  /* Do not include this port when flooding. */
    OFPPC_NO_FWD       = 1 << 5,  /* Drop packets forwarded to port. */
    OFPPC_NO_PACKET_IN = 1 << 6   /* Do not send packet-in msgs for port. */
};

/* Current state of the physical port.  These are not configurable from
 * the controller.
 */
enum ofp_port_state {
    OFPPS_LINK_DOWN   = 1 << 0, /* No physical link present. */

    /* The OFPPS_STP_* bits have no effect on switch operation.  The
     * controller must adjust OFPPC_NO_RECV, OFPPC_NO_FWD, and
     * OFPPC_NO_PACKET_IN appropriately to fully implement an 802.1D spanning
     * tree. */
    OFPPS_STP_LISTEN  = 0 << 8, /* Not learning or relaying frames. */
    OFPPS_STP_LEARN   = 1 << 8, /* Learning but not relaying frames. */
    OFPPS_STP_FORWARD = 2 << 8, /* Learning and relaying frames. */
    OFPPS_STP_BLOCK   = 3 << 8, /* Not part of spanning tree. */
    OFPPS_STP_MASK    = 3 << 8  /* Bit mask for OFPPS_STP_* values. */
};

/* Features of physical ports available in a datapath. */
enum ofp_port_features {
    OFPPF_10MB_HD    = 1 << 0,  /* 10 Mb half-duplex rate support. */
    OFPPF_10MB_FD    = 1 << 1,  /* 10 Mb full-duplex rate support. */
    OFPPF_100MB_HD   = 1 << 2,  /* 100 Mb half-duplex rate support. */
    OFPPF_100MB_FD   = 1 << 3,  /* 100 Mb full-duplex rate support. */
    OFPPF_1GB_HD     = 1 << 4,  /* 1 Gb half-duplex rate support. */
    OFPPF_1GB_FD     = 1 << 5,  /* 1 Gb full-duplex rate support. */
    OFPPF_10GB_FD    = 1 << 6,  /* 10 Gb full-duplex rate support. */
    OFPPF_COPPER     = 1 << 7,  /* Copper medium */
    OFPPF_FIBER      = 1 << 8,  /* Fiber medium */
    OFPPF_AUTONEG    = 1 << 9,  /* Auto-negotiation */
    OFPPF_PAUSE      = 1 << 10, /* Pause */
    OFPPF_PAUSE_ASYM = 1 << 11  /* Asymmetric pause */
};

/* Description of a physical port */
struct ofp_phy_port {
    uint16_t port_no;
    uint8_t hw_addr[OFP_ETH_ALEN];
    uint8_t name[OFP_MAX_PORT_NAME_LEN]; /* Null-terminated */

    uint32_t config;        /* Bitmap of OFPPC_* flags. */
    uint32_t state;         /* Bitmap of OFPPS_* flags. */

    /* Bitmaps of OFPPF_* that describe features.  All bits zeroed if
     * unsupported or unavailable. */
    uint32_t curr;          /* Current features. */
    uint32_t advertised;    /* Features being advertised by the port. */
    uint32_t supported;     /* Features supported by the port. */
    uint32_t peer;          /* Features advertised by peer. */
};
OFP_ASSERT(sizeof(struct ofp_phy_port) == 48);

/* Switch features. */
struct ofp_switch_features {
    struct ofp_header header;
    uint64_t datapath_id;   /* Datapath unique ID.  Only the lower 48-bits
                               are meaningful. */

    uint32_t n_buffers;     /* Max packets buffered at once. */

    uint8_t n_tables;       /* Number of tables supported by datapath. */
    uint8_t pad[3];         /* Align to 64-bits. */

    /* Features. */
    uint32_t capabilities;  /* Bitmap of support "ofp_capabilities". */
    uint32_t actions;       /* Bitmap of supported "ofp_action_type"s. */

    /* Port info.*/
    struct ofp_phy_port ports[0];  /* Port definitions.  The number of ports
                                      is inferred from the length field in
                                      the header. */
};
OFP_ASSERT(sizeof(struct ofp_switch_features) == 32);

// MAH: start
/* virtual port table features.
 * If the switch supports virtual port table,
 * then use this message to query for the
 * port table attributes and the actions
 * supported at the port table. */
struct ofp_vport_table_features {
    struct ofp_header header;
    // Note: max_vports also found in ofp_vport_table_stats
    uint32_t max_vports;    /* Max number of entries supported */
    uint32_t actions;		/* Bitmap of supported port table actions */
	uint16_t max_chain_depth;	/* maximum depth of virtual port chain */
    // XXX mixed_chaining is a non-permanent field
    // It is used to indicate a virtual port cannot have a parent virtual
    // port that performs a different action
    // This is the case with the NetFPGA MPLS-switch as it cannot chain
    // pop and push virtual ports
    uint8_t mixed_chaining; /* 0 = false, 1 = true */
    uint8_t pad[5];			/* align to 64-bits */
};
OFP_ASSERT(sizeof(struct ofp_vport_table_features) == 24);
// MAH: end

/* What changed about the physical port */
enum ofp_port_reason {
    OFPPR_ADD,              /* The port was added */
    OFPPR_DELETE,           /* The port was removed */
    OFPPR_MODIFY            /* Some attribute of the port has changed */
};

/* A physical port has changed in the datapath */
struct ofp_port_status {
    struct ofp_header header;
    uint8_t reason;          /* One of OFPPR_* */
    uint8_t pad[7];          /*
 to 64-bits */
    struct ofp_phy_port desc;
};
OFP_ASSERT(sizeof(struct ofp_port_status) == 64);

/* Modify behavior of the physical port */
struct ofp_port_mod {
    struct ofp_header header;
    uint16_t port_no;
    uint8_t hw_addr[OFP_ETH_ALEN]; /* The hardware address is not
                                      configurable.  This is used to
                                      sanity-check the request, so it must
                                      be the same as returned in an
                                      ofp_phy_port struct. */

    uint32_t config;        /* Bitmap of OFPPC_* flags. */
    uint32_t mask;          /* Bitmap of OFPPC_* flags to be changed. */

    uint32_t advertise;     /* Bitmap of "ofp_port_features"s.  Zero all
                               bits to prevent any action taking place. */
    uint8_t pad[4];         /* Pad to 64-bits. */
};
OFP_ASSERT(sizeof(struct ofp_port_mod) == 32);

// MAH: start
/* flag values for mpls_pop action. */
enum {
	MPLS_POP_DONT_POP		= 1 << 0, 	/* Don't pop. */
	MPLS_POP_DECREMENT_TTL	= 1 << 1,	/* Decrement the ttl. */
	MPLS_POP_COPY_TTL		= 1 << 2,	/* Copy the ttl bits to the next header. */
	MPLS_POP_COPY_EXP		= 1 << 3	/* Copy the exp bits to the next header. */
};

/* flag values for mpls_push action. */
enum {
	MPLS_PUSH_DECREMENT_TTL	= 1 << 0,	/* Decrement the ttl. */
	MPLS_PUSH_TTL_NEXT		= 1 << 1,	/* Copy the ttl bits from the next header. */
	MPLS_PUSH_EXP_NEXT		= 1 << 2,	/* Copy the exp bits from the next header. */
	MPLS_PUSH_TTL_PREV		= 1 << 3,	/* Copy the ttl bits from the previous label. */
	MPLS_PUSH_EXP_PREV		= 1 << 4	/* Copy the exp bits from the previous label. */
};


struct action_pop_mpls {
	uint16_t eth_type;	/* eth_type of packet 	*/
    uint8_t flags;  	/* MPLS_POP_* flags		*/
    uint8_t pad[5]; 	/* align to 64-bits		*/
};
OFP_ASSERT(sizeof(struct action_pop_mpls) == 8);

struct action_push_mpls {
    uint32_t label_out; /* outgoing mpls label.	*/
    uint8_t	exp;		/* exp/cos bits. 		*/
    uint8_t	ttl;		/* time to live. 		*/
    uint8_t flags;		/* MPLS_PUSH_* flags	*/
    uint8_t pad[1];		/* align to 64-bits 	*/
};
OFP_ASSERT(sizeof(struct action_push_mpls) == 8);

struct ofp_action_mpls_label {
    uint16_t type;                  /* OFPPAT_SET_MPLS_LABEL. */
    uint16_t len;                   /* Length is 8. */
    uint32_t label_out; 			/* outgoing mpls label. */
};

struct ofp_action_mpls_exp {
    uint16_t type;                  /* OFPPAT_SET_MPLS_EXP. */
    uint16_t len;                   /* Length is 8. */
	uint8_t	exp;					/* experimental/class of service bits */
	uint8_t pad[3];
};

struct ofp_vport_action_pop_mpls
{
    uint16_t type;                  /* OFPPAT_POP_MPLS. */
    uint16_t len;                   /* Length is 8. */
    struct action_pop_mpls apm;
    uint8_t pad[4];
};
OFP_ASSERT(sizeof(struct ofp_vport_action_pop_mpls) == 16);

struct ofp_vport_action_push_mpls
{
    uint16_t type;                  /* OFPPAT_PUSH_MPLS. */
    uint16_t len;                   /* Length is 8. */
    struct action_push_mpls apm;
    uint8_t pad[4];
};
OFP_ASSERT(sizeof(struct ofp_vport_action_push_mpls) == 16);

struct ofp_vport_action_set_mpls_label
{
    uint16_t type;                  /* OFPPAT_SET_MPLS_LABEL. */
    uint16_t len;                   /* Length is 8. */
    uint32_t label_out; 			/* outgoing mpls label. */
};
OFP_ASSERT(sizeof(struct ofp_vport_action_set_mpls_label) == 8);

struct ofp_vport_action_set_mpls_exp
{
    uint16_t type;                  /* OFPPAT_SET_MPLS_EXP. */
    uint16_t len;                   /* Length is 8. */
    uint8_t	exp;					/* experimental/class of service bits */
    uint8_t pad[3];
};
OFP_ASSERT(sizeof(struct ofp_vport_action_set_mpls_exp) == 8);
// MAH: end

/* Why is this packet being sent to the controller? */
enum ofp_packet_in_reason {
    OFPR_NO_MATCH,          /* No matching flow. */
    OFPR_ACTION             /* Action explicitly output to controller. */
};

/* Packet received on port (datapath -> controller). */
struct ofp_packet_in {
    struct ofp_header header;
    uint32_t buffer_id;     /* ID assigned by datapath. */
    uint16_t total_len;     /* Full length of frame. */
    uint16_t in_port;       /* Port on which frame was received. */
    uint8_t reason;         /* Reason packet is being sent (one of OFPR_*) */
    uint8_t pad;
    uint8_t data[0];        /* Ethernet frame, halfway through 32-bit word,
                               so the IP header is 32-bit aligned.  The
                               amount of data is inferred from the length
                               field in the header.  Because of padding,
                               offsetof(struct ofp_packet_in, data) ==
                               sizeof(struct ofp_packet_in) - 2. */
};
OFP_ASSERT(sizeof(struct ofp_packet_in) == 20);

enum ofp_action_type {
    OFPAT_OUTPUT,           /* Output to switch port. */
    OFPAT_SET_VLAN_VID,     /* Set the 802.1q VLAN id. */
    OFPAT_SET_VLAN_PCP,     /* Set the 802.1q priority. */
    OFPAT_STRIP_VLAN,       /* Strip the 802.1q header. */
    OFPAT_SET_DL_SRC,       /* Ethernet source address. */
    OFPAT_SET_DL_DST,       /* Ethernet destination address. */
    OFPAT_SET_NW_SRC,       /* IP source address. */
    OFPAT_SET_NW_DST,       /* IP destination address. */
    OFPAT_SET_TP_SRC,       /* TCP/UDP source port. */
    OFPAT_SET_TP_DST,       /* TCP/UDP destination port. */
    // MAH: start
    OFPAT_SET_MPLS_LABEL,	/* Set the MPLS label. */
    OFPAT_SET_MPLS_EXP,		/* Set the MPLS EXP bits. */
    // MAH: end
    OFPAT_VENDOR = 0xffff
};

// MAH: start
// port table actions
enum ofp_vport_action_type {
	OFPPAT_OUTPUT,		   		/* Output to switch port .	*/
	OFPPAT_POP_MPLS,       		/* Pop MLPS label. 			*/
    OFPPAT_PUSH_MPLS,      		/* Push MPLS label. 		*/
    OFPPAT_SET_MPLS_LABEL,		/* Set MPLS label.	 		*/
    OFPPAT_SET_MPLS_EXP			/* Set MPLS exp bits.		*/
};
// MAH: end

/* Action structure for OFPAT_OUTPUT, which sends packets out 'port'.
 * When the 'port' is the OFPP_CONTROLLER, 'max_len' indicates the max
 * number of bytes to send.  A 'max_len' of zero means the entire packet
 * should be sent. */
struct ofp_action_output {
    uint16_t type;                  /* OFPAT_OUTPUT. */
    uint16_t len;                   /* Length is 8. */
    // MAH: start
    // port space is now 32-bits to accomodate virtual ports
    // first 16-bits have same meaning as before
    uint32_t port;					/* Output port. */
    //uint16_t port;                  /* Output port. */
    // MAH: end
    uint16_t max_len;               /* Max length to send to controller. */
    uint8_t  pad[6];				/* Padding. */
};
// MAH: start
OFP_ASSERT(sizeof(struct ofp_action_output) == 16);
//OFP_ASSERT(sizeof(struct ofp_action_output) == 8);
// MAH: end

/* The VLAN id is 12 bits, so we can use the entire 16 bits to indicate
 * special conditions.  All ones is used to match that no VLAN id was
 * set. */
#define OFP_VLAN_NONE      0xffff

/* Action structure for OFPAT_SET_VLAN_VID. */
struct ofp_action_vlan_vid {
    uint16_t type;                  /* OFPAT_SET_VLAN_VID. */
    uint16_t len;                   /* Length is 8. */
    uint16_t vlan_vid;              /* VLAN id. */
    uint8_t pad[2];
};
OFP_ASSERT(sizeof(struct ofp_action_vlan_vid) == 8);

/* Action structure for OFPAT_SET_VLAN_PCP. */
struct ofp_action_vlan_pcp {
    uint16_t type;                  /* OFPAT_SET_VLAN_PCP. */
    uint16_t len;                   /* Length is 8. */
    uint8_t vlan_pcp;               /* VLAN priority. */
    uint8_t pad[3];
};
// MAH: start
// bug fix
//OFP_ASSERT(sizeof(struct ofp_action_vlan_vid) == 8);
OFP_ASSERT(sizeof(struct ofp_action_vlan_pcp) == 8);
// MAH: end

/* Action structure for OFPAT_SET_DL_SRC/DST. */
struct ofp_action_dl_addr {
    uint16_t type;                  /* OFPAT_SET_DL_SRC/DST. */
    uint16_t len;                   /* Length is 16. */
    uint8_t dl_addr[OFP_ETH_ALEN];  /* Ethernet address. */
    uint8_t pad[6];
};
OFP_ASSERT(sizeof(struct ofp_action_dl_addr) == 16);

/* Action structure for OFPAT_SET_NW_SRC/DST. */
struct ofp_action_nw_addr {
    uint16_t type;                  /* OFPAT_SET_TW_SRC/DST. */
    uint16_t len;                   /* Length is 8. */
    uint32_t nw_addr;               /* IP address. */
};
OFP_ASSERT(sizeof(struct ofp_action_nw_addr) == 8);

/* Action structure for OFPAT_SET_TP_SRC/DST. */
struct ofp_action_tp_port {
    uint16_t type;                  /* OFPAT_SET_TP_SRC/DST. */
    uint16_t len;                   /* Length is 8. */
    uint16_t tp_port;               /* TCP/UDP port. */
    uint8_t pad[2];
};
OFP_ASSERT(sizeof(struct ofp_action_tp_port) == 8);

/* Action header for OFPAT_VENDOR. The rest of the body is vendor-defined. */
struct ofp_action_vendor_header {
    uint16_t type;                  /* OFPAT_VENDOR. */
    uint16_t len;                   /* Length is 8. */
    uint32_t vendor;                /* Vendor ID, which takes the same form
                                       as in "struct ofp_vendor". */
};
OFP_ASSERT(sizeof(struct ofp_action_vendor_header) == 8);

/* Action header that is common to all actions.  The length includes the
 * header and any padding used to make the action 64-bit aligned.
 * NB: The length of an action *must* always be a multiple of eight. */
struct ofp_action_header {
    uint16_t type;                  /* One of OFPAT_*. */
    uint16_t len;                   /* Length of action, including this
                                       header.  This is the length of action,
                                       including any padding to make it
                                       64-bit aligned. */
    uint8_t pad[4];
};
OFP_ASSERT(sizeof(struct ofp_action_header) == 8);

/* Send packet (controller -> datapath). */
struct ofp_packet_out {
    struct ofp_header header;
    uint32_t buffer_id;           /* ID assigned by datapath (-1 if none). */
    uint16_t in_port;             /* Packet's input port (OFPP_NONE if none). */
    uint16_t actions_len;          /* Size of action array in bytes. */
    struct ofp_action_header actions[0]; /* Actions. */
    /* uint8_t data[0]; */        /* Packet data.  The length is inferred
                                     from the length field in the header.
                                     (Only meaningful if buffer_id == -1.) */
};
OFP_ASSERT(sizeof(struct ofp_packet_out) == 16);

enum ofp_flow_mod_command {
    OFPFC_ADD,              /* New flow. */
    OFPFC_MODIFY,           /* Modify all matching flows. */
    OFPFC_MODIFY_STRICT,    /* Modify entry strictly matching wildcards */
    OFPFC_DELETE,           /* Delete all matching flows. */
    OFPFC_DELETE_STRICT     /* Strictly match wildcards and priority. */
};

/* Flow wildcards. */
enum ofp_flow_wildcards {
    OFPFW_IN_PORT  = 1 << 0,  /* Switch input port. */
    OFPFW_DL_VLAN  = 1 << 1,  /* VLAN. */
    OFPFW_DL_SRC   = 1 << 2,  /* Ethernet source address. */
    OFPFW_DL_DST   = 1 << 3,  /* Ethernet destination address. */
    OFPFW_DL_TYPE  = 1 << 4,  /* Ethernet frame type. */
    OFPFW_NW_PROTO = 1 << 5,  /* IP protocol. */
    OFPFW_TP_SRC   = 1 << 6,  /* TCP/UDP source port. */
    OFPFW_TP_DST   = 1 << 7,  /* TCP/UDP destination port. */


    /* IP source address wildcard bit count.  0 is exact match, 1 ignores the
     * LSB, 2 ignores the 2 least-significant bits, ..., 32 and higher wildcard
     * the entire field.  This is the *opposite* of the usual convention where
     * e.g. /24 indicates that 8 bits (not 24 bits) are wildcarded. */
    OFPFW_NW_SRC_SHIFT = 8,
    OFPFW_NW_SRC_BITS = 6,
    OFPFW_NW_SRC_MASK = ((1 << OFPFW_NW_SRC_BITS) - 1) << OFPFW_NW_SRC_SHIFT,
    OFPFW_NW_SRC_ALL = 32 << OFPFW_NW_SRC_SHIFT,

    /* IP destination address wildcard bit count.  Same format as source. */
    OFPFW_NW_DST_SHIFT = 14,
    OFPFW_NW_DST_BITS = 6,
    OFPFW_NW_DST_MASK = ((1 << OFPFW_NW_DST_BITS) - 1) << OFPFW_NW_DST_SHIFT,
    OFPFW_NW_DST_ALL = 32 << OFPFW_NW_DST_SHIFT,

    // MAH: start
    // add support for two MPLS labels
    OFPFW_MPLS_L1	= 1 << 20, /* MPLS Label 1. */
    OFPFW_MPLS_L2	= 1 << 21, /* MPLS label 2. */
    // MAH: end

    /* Wildcard all fields. */
    // MAH: start
    // now have 22 bits after adding MPLS
    //OFPFW_ALL = ((1 << 20) - 1)
    OFPFW_ALL = ((1 << 22) - 1)
    // MAH: end
};

/* The wildcards for ICMP type and code fields use the transport source
 * and destination port fields, respectively. */
#define OFPFW_ICMP_TYPE OFPFW_TP_SRC
#define OFPFW_ICMP_CODE OFPFW_TP_DST

/* Values below this cutoff are 802.3 packets and the two bytes
 * following MAC addresses are used as a frame length.  Otherwise, the
 * two bytes are used as the Ethernet type.
 */
#define OFP_DL_TYPE_ETH2_CUTOFF   0x0600

/* Value of dl_type to indicate that the frame does not include an
 * Ethernet type.
 */
#define OFP_DL_TYPE_NOT_ETH_TYPE  0x05ff

/* The VLAN id is 12-bits, so we can use the entire 16 bits to indicate
 * special conditions.  All ones indicates that no VLAN id was set.
 */
#define OFP_VLAN_NONE      0xffff

/* Fields to match against flows */
struct ofp_match {
    uint32_t wildcards;        /* Wildcard fields. */
    uint16_t in_port;          /* Input switch port. */
    uint8_t dl_src[OFP_ETH_ALEN]; /* Ethernet source address. */
    uint8_t dl_dst[OFP_ETH_ALEN]; /* Ethernet destination address. */
    uint16_t dl_vlan;          /* Input VLAN. */
    uint16_t dl_type;          /* Ethernet frame type. */
    uint8_t nw_proto;          /* IP protocol. */
    uint8_t pad;               /* Align to 32-bits. */
    uint32_t nw_src;           /* IP source address. */
    uint32_t nw_dst;           /* IP destination address. */
    uint16_t tp_src;           /* TCP/UDP source port. */
    uint16_t tp_dst;           /* TCP/UDP destination port. */
    // MAH: start
    // Add support for two MPLS labels to the flow table.
    // note: leave the pad field to preserve 32-bit alignment
    uint32_t mpls_label1;		/* Top of label stack */
    uint32_t mpls_label2;		/* Second label (if available)*/
    // MAH: end
};
// MAH: start
// MPLS adds 8 more bytes to the size
//OFP_ASSERT(sizeof(struct ofp_match) == 36);
OFP_ASSERT(sizeof(struct ofp_match) == 44);
// MAH: end

/* The match fields for ICMP type and code use the transport source and
 * destination port fields, respectively. */
#define icmp_type tp_src
#define icmp_code tp_dst

/* Value used in "idle_timeout" and "hard_timeout" to indicate that the entry
 * is permanent. */
#define OFP_FLOW_PERMANENT 0

/* By default, choose a priority in the middle */
#define OFP_DEFAULT_PRIORITY 0x8000

/* Flow setup and teardown (controller -> datapath). */
struct ofp_flow_mod {
    struct ofp_header header;
    struct ofp_match match;      /* Fields to match */

    /* Flow actions. */
    uint16_t command;             /* One of OFPFC_*. */
    uint16_t idle_timeout;        /* Idle time before discarding (seconds). */
    uint16_t hard_timeout;        /* Max time before discarding (seconds). */
    uint16_t priority;            /* Priority level of flow entry. */
    uint32_t buffer_id;           /* Buffered packet to apply to (or -1).
                                     Not meaningful for OFPFC_DELETE*. */
    uint16_t out_port;            /* For OFPFC_DELETE* commands, require
                                     matching entries to include this as an
                                     output port.  A value of OFPP_NONE
                                     indicates no restriction. */
    uint8_t pad[2];               /* Align to 32-bits. */
    uint32_t reserved;            /* Reserved for future use. */
    struct ofp_action_header actions[0]; /* The action length is inferred
                                            from the length field in the
                                            header. */
};
// MAH: start
// add 8 more bytes since the ofp_match struct is now 8 bytes bigger
//OFP_ASSERT(sizeof(struct ofp_flow_mod) == 64);
OFP_ASSERT(sizeof(struct ofp_flow_mod) == 72);
// MAH: end


// MAH: start
// Add or remove a virtual port
struct ofp_vport_mod {
    struct ofp_header header;
    uint32_t vport;      	/* virtual port number. */
    uint32_t parent_port; 	/* parent port number */


    /* Flow actions. */
    uint16_t command;             /* One of OFPFC_*. */

    uint8_t pad[6];               /* Align to 32-bits. */
    //uint32_t reserved;          /* Reserved for future use. */
    struct ofp_action_header actions[0]; /* Uses the same action header as the flow-table
										 The action length is inferred
										 from the length field in the
										 header. */
};
OFP_ASSERT(sizeof(struct ofp_vport_mod) == 24);

enum ofp_vport_mod_command {
    OFPVP_ADD,			/* New virtual port. */
    OFPVP_DELETE		/* Delete virtual port. */
};
// MAH: end


/* Why did this flow expire? */
enum ofp_flow_expired_reason {
    OFPER_IDLE_TIMEOUT,         /* Flow idle time exceeded idle_timeout. */
    OFPER_HARD_TIMEOUT          /* Time exceeded hard_timeout. */
};

/* Flow expiration (datapath -> controller). */
struct ofp_flow_expired {
    struct ofp_header header;
    struct ofp_match match;   /* Description of fields */

    uint16_t priority;        /* Priority level of flow entry. */
    uint8_t reason;           /* One of OFPER_*. */
    uint8_t pad[1];           /* Align to 32-bits. */

    uint32_t duration;        /* Time flow was alive in seconds. */
    uint8_t pad2[4];          /* Align to 64-bits. */
    uint64_t packet_count;
    uint64_t byte_count;
};
// MAH: start
// add 8 more bytes since the ofp_match struct is now 8 bytes bigger
//OFP_ASSERT(sizeof(struct ofp_flow_expired) == 72);
OFP_ASSERT(sizeof(struct ofp_flow_expired) == 80);
// MAH: end

/* Values for 'type' in ofp_error_message.  These values are immutable: they
 * will not change in future versions of the protocol (although new values may
 * be added). */
enum ofp_error_type {
    OFPET_HELLO_FAILED,         /* Hello protocol failed. */
    OFPET_BAD_REQUEST,          /* Request was not understood. */
    OFPET_BAD_ACTION,           /* Error in action description. */
    OFPET_FLOW_MOD_FAILED,       /* Problem modifying flow entry. */
    // MAH: start
    OFPET_VPORT_MOD_FAILED		/* Problem modifying port table entry. */
    // MAH: end
};

/* ofp_error_msg 'code' values for OFPET_HELLO_FAILED.  'data' contains an
 * ASCII text string that may give failure details. */
enum ofp_hello_failed_code {
    OFPHFC_INCOMPATIBLE         /* No compatible version. */
};

/* ofp_error_msg 'code' values for OFPET_BAD_REQUEST.  'data' contains at least
 * the first 64 bytes of the failed request. */
enum ofp_bad_request_code {
    OFPBRC_BAD_VERSION,         /* ofp_header.version not supported. */
    OFPBRC_BAD_TYPE,            /* ofp_header.type not supported. */
    OFPBRC_BAD_STAT,            /* ofp_stats_request.type not supported. */
    OFPBRC_BAD_VENDOR,          /* Vendor not supported (in ofp_vendor or
                                 * ofp_stats_request or ofp_stats_reply). */
    OFPBRC_BAD_SUBTYPE          /* Vendor subtype not supported. */
};

/* ofp_error_msg 'code' values for OFPET_BAD_ACTION.  'data' contains at least
 * the first 64 bytes of the failed request. */
enum ofp_bad_action_code {
    OFPBAC_BAD_TYPE,           /* Unknown action type. */
    OFPBAC_BAD_LEN,            /* Length problem in actions. */
    OFPBAC_BAD_VENDOR,         /* Unknown vendor id specified. */
    OFPBAC_BAD_VENDOR_TYPE,    /* Unknown action type for vendor id. */
    OFPBAC_BAD_OUT_PORT,       /* Problem validating output action. */
    OFPBAC_BAD_ARGUMENT        /* Bad action argument. */
};

/* ofp_error_msg 'code' values for OFPET_FLOW_MOD_FAILED.  'data' contains
 * at least the first 64 bytes of the failed request. */
enum ofp_flow_mod_failed_code {
    OFPFMFC_ALL_TABLES_FULL    /* Flow not added because of full tables. */
};

/* OFPT_ERROR: Error message (datapath -> controller). */
struct ofp_error_msg {
    struct ofp_header header;

    uint16_t type;
    uint16_t code;
    uint8_t data[0];          /* Variable-length data.  Interpreted based
                                 on the type and code. */
};
OFP_ASSERT(sizeof(struct ofp_error_msg) == 12);

enum ofp_stats_types {
    /* Description of this OpenFlow switch.
     * The request body is empty.
     * The reply body is struct ofp_desc_stats. */
    OFPST_DESC,

    /* Individual flow statistics.
     * The request body is struct ofp_flow_stats_request.
     * The reply body is an array of struct ofp_flow_stats. */
    OFPST_FLOW,

    /* Aggregate flow statistics.
     * The request body is struct ofp_aggregate_stats_request.
     * The reply body is struct ofp_aggregate_stats_reply. */
    OFPST_AGGREGATE,

    /* Flow table statistics.
     * The request body is empty.
     * The reply body is an array of struct ofp_table_stats. */
    OFPST_TABLE,

    // MAH: start
    // Now used for physical or virtual ports
    // Also, the request body should no longer be empty but
    // should contain a list of 32-bit port numbers to return where
    // the number of ports is inferred by the length of the header
    // MAH: end
    /* Physical port statistics.
     * The request body is empty.
     * The reply body is an array of struct ofp_port_stats. */
    OFPST_PORT,

    // MAH: start
    // The request body is empty.
    // The reply body is a single struct ofp_port_table_stats.
    OFPST_PORT_TABLE,
    // MAH: end

    /* Vendor extension.
     * The request and reply bodies begin with a 32-bit vendor ID, which takes
     * the same form as in "struct ofp_vendor".  The request and reply bodies
     * are otherwise vendor-defined. */
    OFPST_VENDOR = 0xffff
};

struct ofp_stats_request {
    struct ofp_header header;
    uint16_t type;              /* One of the OFPST_* constants. */
    uint16_t flags;             /* OFPSF_REQ_* flags (none yet defined). */
    uint8_t body[0];            /* Body of the request. */
};
OFP_ASSERT(sizeof(struct ofp_stats_request) == 12);

enum ofp_stats_reply_flags {
    OFPSF_REPLY_MORE  = 1 << 0  /* More replies to follow */
};

struct ofp_stats_reply {
    struct ofp_header header;
    uint16_t type;              /* One of the OFPST_* constants. */
    uint16_t flags;             /* OFPSF_REPLY_* flags. */
    uint8_t body[0];            /* Body of the reply. */
};
OFP_ASSERT(sizeof(struct ofp_stats_reply) == 12);

#define DESC_STR_LEN   256
#define SERIAL_NUM_LEN 32
/* Body of reply to OFPST_DESC request.  Each entry is a NULL-terminated
 * ASCII string. */
struct ofp_desc_stats {
    char mfr_desc[DESC_STR_LEN];       /* Manufacturer description. */
    char hw_desc[DESC_STR_LEN];        /* Hardware description. */
    char sw_desc[DESC_STR_LEN];        /* Software description. */
    char serial_num[SERIAL_NUM_LEN];   /* Serial number. */
};
OFP_ASSERT(sizeof(struct ofp_desc_stats) == 800);

/* Body for ofp_stats_request of type OFPST_FLOW. */
struct ofp_flow_stats_request {
    struct ofp_match match;   /* Fields to match */
    uint8_t table_id;         /* ID of table to read (from ofp_table_stats)
                                 or 0xff for all tables. */
    uint8_t pad;              /* Align to 32 bits. */
    uint16_t out_port;        /* Require matching entries to include this
                                 as an output port.  A value of OFPP_NONE
                                 indicates no restriction. */
};
// MAH: start
// add 8 more bytes since the ofp_match struct is now 8 bytes bigger
//OFP_ASSERT(sizeof(struct ofp_flow_stats_request) == 40);
OFP_ASSERT(sizeof(struct ofp_flow_stats_request) == 48);
// MAH: end

/* Body of reply to OFPST_FLOW request. */
struct ofp_flow_stats {
    uint16_t length;          /* Length of this entry. */
    uint8_t table_id;         /* ID of table flow came from. */
    uint8_t pad;
    struct ofp_match match;   /* Description of fields. */
    uint32_t duration;        /* Time flow has been alive in seconds. */
    uint16_t priority;        /* Priority of the entry. Only meaningful
                                 when this is not an exact-match entry. */
    uint16_t idle_timeout;    /* Number of seconds idle before expiration. */
    uint16_t hard_timeout;    /* Number of seconds before expiration. */
    uint16_t pad2[3];         /* Pad to 64 bits. */
    uint64_t packet_count;    /* Number of packets in flow. */
    uint64_t byte_count;      /* Number of bytes in flow. */
    struct ofp_action_header actions[0]; /* Actions. */
};
// MAH: start
// add 8 more bytes since the ofp_match struct is now 8 bytes bigger
//OFP_ASSERT(sizeof(struct ofp_flow_stats) == 72);
OFP_ASSERT(sizeof(struct ofp_flow_stats) == 80);
// MAH: end

/* Body for ofp_stats_request of type OFPST_AGGREGATE. */
struct ofp_aggregate_stats_request {
    struct ofp_match match;   /* Fields to match */
    uint8_t table_id;         /* ID of table to read (from ofp_table_stats)
                                 or 0xff for all tables. */
    uint8_t pad;              /* Align to 32 bits. */
    uint16_t out_port;        /* Require matching entries to include this
                                 as an output port.  A value of OFPP_NONE
                                 indicates no restriction. */
};
// MAH: start
// add 8 more bytes since the ofp_match struct is now 8 bytes bigger
//OFP_ASSERT(sizeof(struct ofp_aggregate_stats_request) == 40);
OFP_ASSERT(sizeof(struct ofp_aggregate_stats_request) == 48);
// MAH: end

/* Body of reply to OFPST_AGGREGATE request. */
struct ofp_aggregate_stats_reply {
    uint64_t packet_count;    /* Number of packets in flows. */
    uint64_t byte_count;      /* Number of bytes in flows. */
    uint32_t flow_count;      /* Number of flows. */
    uint8_t pad[4];           /* Align to 64 bits. */
};
OFP_ASSERT(sizeof(struct ofp_aggregate_stats_reply) == 24);

/* Body of reply to OFPST_TABLE request. */
struct ofp_table_stats {
    uint8_t table_id;        /* Identifier of table.  Lower numbered tables
                                are consulted first. */
    uint8_t pad[3];          /* Align to 32-bits */
    char name[OFP_MAX_TABLE_NAME_LEN];
    uint32_t wildcards;      /* Bitmap of OFPFW_* wildcards that are
                                supported by the table. */
    uint32_t max_entries;    /* Max number of entries supported */
    uint32_t active_count;   /* Number of active entries */
    uint64_t lookup_count;   /* Number of packets looked up in table */
    uint64_t matched_count;  /* Number of packets that hit table */
};
OFP_ASSERT(sizeof(struct ofp_table_stats) == 64);

// MAH: start
// Virtual port table stats are similar to flow table stats
// it indicates how many virtual port table entries there are
// and how many are supported by the switch, etc
/* Body of reply to OFPST_TABLE request. */
struct ofp_vport_table_stats {
    uint32_t max_vports;    /* Max number of entries supported */
    uint32_t active_vports;   /* Number of active entries */
    uint64_t lookup_count;   /* Number of port entries looked up in port table */
    uint64_t port_match_count;  /* Number of entries looked up in port table */
    uint64_t chain_match_count;  /* Number of entries accessed by chaining */
};
OFP_ASSERT(sizeof(struct ofp_vport_table_stats) == 32);
// MAH: end

// MAH: start
// Now used for physical or virtual ports
// MAH: end
/* Body of reply to OFPST_PORT request. If a counter is unsupported, set
 * the field to all ones. */
struct ofp_port_stats {
	// MAH: start
	// extend port_no to 32-bits
    //uint16_t port_no;
    //uint8_t pad[6];          /* Align to 64-bits. */
	uint32_t port_no;
	uint8_t pad[4];          /* Align to 64-bits. */
    // MAH: end
    uint64_t rx_packets;     /* Number of received packets. */
    uint64_t tx_packets;     /* Number of transmitted packets. */
    uint64_t rx_bytes;       /* Number of received bytes. */
    uint64_t tx_bytes;       /* Number of transmitted bytes. */
    uint64_t rx_dropped;     /* Number of packets dropped by RX. */
    uint64_t tx_dropped;     /* Number of packets dropped by TX. */
    uint64_t rx_errors;      /* Number of receive errors.  This is a super-set
                                of more specific receive errors and should be
                                greater than or equal to the sum of all
                                rx_*_err values. */
    uint64_t tx_errors;      /* Number of transmit errors.  This is a super-set
                                of more specific transmit errors and should be
                                greater than or equal to the sum of all
                                tx_*_err values (none currently defined.) */
    uint64_t rx_frame_err;   /* Number of frame alignment errors. */
    uint64_t rx_over_err;    /* Number of packets with RX overrun. */
    uint64_t rx_crc_err;     /* Number of CRC errors. */
    uint64_t collisions;     /* Number of collisions. */
    // MAH: start
    uint64_t mpls_ttl0_dropped;	 /* Number of MPLS packets dropped due to ttl 0. */
    // MAH: end
};
OFP_ASSERT(sizeof(struct ofp_port_stats) == 112);

/* Vendor extension. */
struct ofp_vendor_header {
    struct ofp_header header;   /* Type OFPT_VENDOR. */
    uint32_t vendor;            /* Vendor ID:
                                 * - MSB 0: low-order bytes are IEEE OUI.
                                 * - MSB != 0: defined by OpenFlow
                                 *   consortium. */
    /* Vendor-defined arbitrary additional data. */
};
OFP_ASSERT(sizeof(struct ofp_vendor_header) == 12);

#endif /* openflow/openflow.h */
