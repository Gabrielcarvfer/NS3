// MAH: start
#ifndef OPENFLOW_ERICSSON_EXT_H
#define OPENFLOW_ERICSSON_EXT_H 1

#include "openflow/openflow.h"


#define ERICSSON_OUI_STR "0001EC"

/* The following vendor extensions, proposed by Ericsson, are not yet
 * ready for standardization (and may never be), so they are not included in
 * openflow.h. */

#define ER_VENDOR_ID 0x000001EC

enum er_action_type {
	ERXT_POP_MPLS,				/* Pop an MLPS label.  */
	ERXT_PUSH_MPLS, 			/* Push an MPLS label. */
};


/* Header for Ericsson-defined actions.
 * Note that this is effectively an extension/subclass
 * of ofpat_action_vendor_header defined in include/openflow/openflow.h */
struct er_action_header {
    uint16_t type;                  /* OFPAT_VENDOR. */
    uint16_t len;                   /* Length is 16. */
    uint32_t vendor;                /* ER_VENDOR_ID. */
    uint16_t subtype;               /* Ericsson action type (er_action_type) */
    uint8_t pad[6];					/* align to 64-bit boundary */
};
OFP_ASSERT(sizeof(struct er_action_header) == 16);


/* Action structure for ERXT_POP_MPLS. */
struct er_action_pop_mpls {
	struct er_action_header erah;
	struct action_pop_mpls apm;
};
OFP_ASSERT(sizeof(struct er_action_pop_mpls) == (sizeof(struct er_action_header) + 8));


/* Action structure for ERXT_PUSH_MPLS. */
struct er_action_push_mpls {
	struct er_action_header erah;
	struct action_push_mpls apm;
};
OFP_ASSERT(sizeof(struct er_action_push_mpls) == (sizeof(struct er_action_header) + 8));


#endif /* openflow/ericsson-ext.h */

// MAH: end
