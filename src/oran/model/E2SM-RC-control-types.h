//
// Created by Gabriel Ferreira (@gabrielcarvfer) on 28/10/22.
//

#ifndef NS3_E2SM_RC_CONTROL_TYPES_H
#define NS3_E2SM_RC_CONTROL_TYPES_H

#include "ns3/json.hpp"

using Json = nlohmann::json; ///< nlohmann's Json type

/**
 * \file
 * \ingroup oran
 * E2SM RC control types and format declarations.
 */

namespace ns3
{

// O-RAN WG3 E2SM RC v01.02 7.6.1
/**
 * \brief E2SM RC Control styles and service types
 */
namespace RIC_CONTROL_SERVICE_STYLES
{
/**
 * \brief E2SM RC Radio Bearer Control style and associated service types
 */
namespace RADIO_BEARER_CONTROL
{
const uint8_t VALUE = 1; ///< E2SM RC Radio Bearer Control style

// O-RAN WG3 E2SM RC v01.02 7.6.2.1 + RAN PARAMETERS 8.4.2
namespace DRB_QOS_CONFIGURATION
{
const uint8_t VALUE = 1; ///< E2SM RC Radio Bearer Control's DRB QoS Configuration service
}

namespace QOS_FLOW_MAPPING_CONFIGURATION
{
const uint8_t VALUE = 2; ///< E2SM RC Radio Bearer Control's DRB QoS Flow Mapping Configuration service
}

namespace LOGICAL_CHANNEL_CONFIGURATION
{
const uint8_t VALUE = 3; ///< E2SM RC Radio Bearer Control's Logical Channel Configuration service
}

namespace RADIO_ADMISSION_CONTROL
{
const uint8_t VALUE = 4; ///< E2SM RC Radio Bearer Control's Radio Admission Control service
}

namespace DRB_TERMINATION_CONTROL
{
const uint8_t VALUE = 5; ///< E2SM RC Radio Bearer Control's DRB Termination Control service
}

namespace DRB_SPLIT_RATION_CONTROL
{
const uint8_t VALUE = 6; ///< E2SM RC Radio Bearer Control's DRB Split Ration Control service
}

namespace PDCP_DUPLICATION_CONTROL
{
const uint8_t VALUE = 7; ///< E2SM RC Radio Bearer Control's PDCP Duplication Control service
}
} // namespace RADIO_BEARER_CONTROL

/**
 * \brief E2SM RC Radio Resource Allocation Control style and associated service types
 */
namespace RADIO_RESOURCE_ALLOCATION_CONTROL
{
const uint8_t VALUE = 2; ///< E2SM RC Radio Resource Allocation Control style

// O-RAN WG3 E2SM RC v01.02 7.6.3.1
namespace DRX_PARAMETER_CONFIGURATION
{
const uint8_t VALUE = 1; ///< E2SM RC Radio Resource Allocation Control's DRX Parameter Configuration service
}

namespace SR_PERIODICITY_CONFIGURATION
{
const uint8_t VALUE = 2; ///< E2SM RC Radio Resource Allocation Control's SR Periodicity Configuration service
}

namespace SPS_PARAMETERS_CONFIGURATION
{
const uint8_t VALUE = 3; ///< E2SM RC Radio Resource Allocation Control's SPS Parameters Configuration service
}

namespace CONFIGURED_GRANT_CONTROL
{
const uint8_t VALUE = 4; ///< E2SM RC Radio Resource Allocation Control's Configured Grant Control service
}

namespace CQI_TABLE_CONFIGURATION
{
const uint8_t VALUE = 5; ///< E2SM RC Radio Resource Allocation Control's CQI Table Configuration service
}

namespace SLICE_LEVEL_PRB_QUOTA
{
const uint8_t VALUE = 6; ///< E2SM RC Radio Resource Allocation Control's Slice Level PRB Quota service
}
} // namespace RADIO_RESOURCE_ALLOCATION_CONTROL

/**
 * \brief E2SM RC Connected Mobility Control style and associated service types
 */
namespace CONNECTED_MODE_MOBILITY_CONTROL
{
const uint8_t VALUE = 3; ///< E2SM RC Connected Mobility Control style

// O-RAN WG3 E2SM RC v01.02 7.6.4.1 + RAN PARAMETERS 8.4.4
namespace HANDOVER_CONTROL
{
const uint8_t VALUE = 1; ///< E2SM RC Connected Mobility Control's Handover Control service
}

namespace CONDITIONAL_HANDOVER_CONTROL
{
const uint8_t VALUE = 2; ///< E2SM RC Connected Mobility Control's Conditional Handover Control service
}

namespace DUAL_ACTIVE_PROTOCOL_STACK_HANDOVER_CONTROL
{
const uint8_t VALUE = 3; ///< E2SM RC Connected Mobility Control's Dual Active Protocol Stack Handover Control service
}
} // namespace CONNECTED_MODE_MOBILITY_CONTROL

/**
 * \brief E2SM RC Radio Access Control style and associated service types
 */
namespace RADIO_ACCESS_CONTROL
{
const uint8_t VALUE = 4; ///< E2SM RC Radio Access Allocation Control style

// O-RAN WG3 E2SM RC v01.02 7.6.5.1
namespace UE_ADMISSION_CONTROL
{
const uint8_t VALUE = 1; ///< E2SM RC Radio Access Allocation Control's UE Admission Control service
}

namespace RACH_BACKOFF_CONTROL
{
const uint8_t VALUE = 2; ///< E2SM RC Radio Access Allocation Control's RACH Backoff Control service
}

namespace ACCESS_BARRING_CONTROL
{
const uint8_t VALUE = 3; ///< E2SM RC Radio Access Allocation Control's Access Barring Control service
}

namespace RRC_CONNECTION_RELEASE_CONTROL
{
const uint8_t VALUE = 4; ///< E2SM RC Radio Access Allocation Control's RRC Connection Release Control service
}

namespace RRC_CONNECTION_REJECT_CONTROL
{
const uint8_t VALUE = 5; ///< E2SM RC Radio Access Allocation Control's RRC Connection Reject Control service
}
} // namespace RADIO_ACCESS_CONTROL

/**
 * \brief E2SM RC Dual Connectivity Control style and associated service types
 */
namespace DUAL_CONNECTIVITY_CONTROL
{
const uint8_t VALUE = 5; ///< E2SM RC Dual Connectivity Control style

// O-RAN WG3 E2SM RC v01.02 7.6.6.1 +
namespace DC_SECONDARY_NODE_ADDITION_CONTROL
{
const uint8_t VALUE = 1; ///< E2SM RC Dual Connectivity Control's DC Secondary Node Addition Control service
}

namespace DC_SECONDARY_NODE_MODIFICATION_AND_RELEASE_CONTROL
{
const uint8_t VALUE = 2; ///< E2SM RC Dual Connectivity Control's DC Secondary Node Modification and Release Control service
}

namespace DC_PSCELL_CHANGE_CONTROL
{
const uint8_t VALUE = 3; ///< E2SM RC Dual Connectivity Control's DC PSCell Change Control service
}

namespace DC_SECONDARY_NODE_CHANGE_CONTROL
{
const uint8_t VALUE = 4; ///< E2SM RC Dual Connectivity Control's DC Secondary Node Change Control service
}

namespace DC_DRB_TERMINATION_CONTROL
{
const uint8_t VALUE = 5; ///< E2SM RC Dual Connectivity Control's DC DRB Termination Control service
}
} // namespace DUAL_CONNECTIVITY_CONTROL

/**
 * \brief E2SM RC Carrier Aggregation Control style and associated service types
 */
namespace CARRIER_AGGREGATION_CONTROL
{
const uint8_t VALUE = 6; ///< E2SM RC Carrier Aggregation Control style

// O-RAN WG3 E2SM RC v01.02 7.6.7.1
namespace CA_SECONDARY_CELL_ADDITION_CONTROL
{
const uint8_t VALUE = 1; ///< E2SM RC Carrier Aggregation Control's CA Secondary Cell Addition Control service
}

namespace CA_SECONDARY_CELL_MODIFICATION_AND_RELEASE_CONTROL
{
const uint8_t VALUE = 2; ///< E2SM RC Carrier Aggregation Control's CA Secondary Cell Modification and Release Control service
}
} // namespace CARRIER_AGGREGATION_CONTROL

/**
 * \brief E2SM RC Idle Mode Mobility Control style and associated service types
 */
namespace IDLE_MODE_MOBILITY_CONTROL
{
const uint8_t VALUE = 7; ///< E2SM RC Idle Mode Mobility Control style

// O-RAN WG3 E2SM RC v01.02 7.6.8.1
namespace CELL_RESELECTION_PRIORITY_CONTROL
{
const uint8_t VALUE = 1; ///< E2SM RC Idle Mode Mobility Control's Cell Reselection Priority Control service
}
} // namespace IDLE_MODE_MOBILITY_CONTROL

/**
 * \brief E2SM RC UE Information and Assignment Control style and associated service types
 */
namespace UE_INFORMATION_AND_ASSIGNMENT
{
const uint8_t VALUE = 8; ///< E2SM RC UE Information and Assignment Control style

// O-RAN WG3 E2SM RC v01.02 7.6.9.1
namespace UE_TO_EXPLICIT_UE_LIST_ASSIGNMENT_COMMAND
{
const uint8_t VALUE = 1; ///< E2SM RC UE Information and Assistant Control's UE-to-UE Explicit List Assignment Control service
}
} // namespace UE_INFORMATION_AND_ASSIGNMENT

/**
 * \brief E2SM RC Measurement Reporting Configuration Control style and associated service types
 */
namespace MEASUREMENT_REPORTING_CONFIGURATION_CONTROL
{
const uint8_t VALUE = 9; ///< E2SM RC Measurement Reporting Configuration Control style

// O-RAN WG3 E2SM RC v01.02 7.6.11.1
namespace ADD_MR_CONFIGURATION
{
const uint8_t VALUE = 1; ///< E2SM RC Measurement Reporting Configuration Control's Add MR Configuration service
}

namespace MODIFY_MR_CONFIGURATION
{
const uint8_t VALUE = 2; ///< E2SM RC Measurement Reporting Configuration Control's Modify MR Configuration service
}

namespace DELETE_MR_CONFIGURATION
{
const uint8_t VALUE = 3; ///< E2SM RC Measurement Reporting Configuration Control's Delete MR Configuration service
}
} // namespace MEASUREMENT_REPORTING_CONFIGURATION_CONTROL

/**
 * \brief E2SM RC Multiple Actions Control style and associated service types
 */
namespace MULTIPLE_ACTIONS_CONTROL
{
const uint8_t VALUE = 255; ///< E2SM RC Multiple Actions Control style
// O-RAN WG3 E2SM RC v01.02 7.6.10
// contain multiple fundamental indications such as the ones above
} // namespace MULTIPLE_ACTIONS_CONTROL
} // namespace RIC_CONTROL_SERVICE_STYLES

/**
 * \brief E2SM RC Control Request header format enumeration
 */
enum E2SM_RC_RIC_CONTROL_HEADER_FORMAT
{
    RC_CONTROL_HEADER_FORMAT_1 = 1,
    RC_CONTROL_HEADER_FORMAT_2,
    RC_CONTROL_HEADER_FORMAT_3
};

/**
 * \brief E2SM RC Control Request's RIC decision enumeration
 */
enum E2SM_RC_RIC_CONTROL_DECISION : uint8_t
{
    RC_ACCEPT = 1,
    RC_REJECT
};

/**
 * \brief E2SM RC Control Request Header structure
 */
typedef struct
{
    enum E2SM_RC_RIC_CONTROL_HEADER_FORMAT format; ///< Control Request Header format

    union {
        struct
        {
            uint16_t RNTI; ///< UE's RNTI identifier
            uint8_t RICControlStyleType;  ///< E2SM Control style
            uint8_t ControlActionID; ///< E2SM Control style's service
            // only used when responding to an Insert Indication
            E2SM_RC_RIC_CONTROL_DECISION RicDecision; ///< RIC Decision for a Control Indication received
        } format_1; ///< Control Request Header format 1 contents

        struct
        {
            uint16_t RNTI; ///< UE's RNTI identifier
            E2SM_RC_RIC_CONTROL_DECISION RicDecision; ///< RIC Decision for a Control Indication received
        } format_2; ///< Control Request Header format 2 contents

        uint64_t raw; ///< Control Request Header raw data
    } contents; ///< Control Request Header contents
} E2SM_RC_RIC_CONTROL_HEADER;

/**
 * \brief E2SM RC Control Request header to Json
 * \param j Json object that will be encoded
 * \param p E2SM_RC_RIC_CONTROL_HEADER to encode to the Json
 */
void
to_json(Json& j, const E2SM_RC_RIC_CONTROL_HEADER& p)
{
    j.update(Json{{"format", p.format}, {"contents", p.contents.raw}});
}

/**
 * \brief Json to E2SM RC Control Request header
 * \param j Json object that will be decoded
 * \param p E2SM_RC_RIC_CONTROL_HEADER to decode from the Json
 */
void
from_json(const Json& j, E2SM_RC_RIC_CONTROL_HEADER& p)
{
    j.at("format").get_to(p.format);
    j.at("contents").get_to(p.contents.raw);
}

/**
 * \brief E2SM RC Control Message format enumeration
 */
enum E2SM_RC_RIC_CONTROL_MESSAGE_FORMAT
{
    E2SM_RC_RIC_CONTROL_MESSAGE_FORMAT_1 = 1,
    E2SM_RC_RIC_CONTROL_MESSAGE_FORMAT_2
};

typedef uint16_t RNTI; ///< Define RNTI as uint16_t
typedef uint32_t RAN_PARAMETER_ID; ///< Define RAN_PARAMETER_ID as uint32_t
typedef double RAN_PARAMETER_VALUE; ///< Define RAN_PARAMETER_VALUE as double. todo: implement ELEMENT, STRUCT and LIST formats
typedef std::string UE_CONTEXT_INFORMATION; ///< Define UE_CONTEXT_INFORMATION as a std::string
typedef std::string CELL_CONTEXT_INFORMATION; ///< Define CELL_CONTEXT_INFORMATION as a std::string
typedef uint8_t INDICATION_STYLE; ///< Define INDICATION_STYLE as uint8_t
typedef uint16_t CELL_GLOBAL_ID; ///< Define CELL_GLOBAL_ID as uint16_t

/**
 * \brief E2SM RC Control Message structure
 */
typedef struct
{
    enum E2SM_RC_RIC_CONTROL_MESSAGE_FORMAT format; ///< Control Request Message format

    union {
        struct
        {
            // O-RAN WG3 E2SM RC v01.02 9.2.1.4.1
            // List of RAN parameter values
            // RAN Parameter ID, RAN Parameter Value
            std::vector<std::pair<RAN_PARAMETER_ID, RAN_PARAMETER_VALUE>>
                sequence_of_ran_parameters; ///< List of parameters
        } format_1; ///< Control Message format 1 contents

        struct
        {
            // O-RAN WG3 E2SM RC v01.02 9.2.1.4.2
            // List of RAN parameter values per UE/RNTI
            // UE ID (RNTI), Sequence of RAN parameters
            std::vector<
                std::pair<RNTI, std::vector<std::pair<RAN_PARAMETER_ID, RAN_PARAMETER_VALUE>>>>
                sequence_of_ue_identifiers; ///< List of parameters per RNTI
        } format_2; ///< Control Message format 2 contents

        struct
        {
            // O-RAN WG3 E2SM RC v01.02 9.2.1.4.3
            // Cell Global ID, Cell Context Information, Cell Deleted, Neighbor Relation Table
            std::vector<std::tuple<CELL_GLOBAL_ID, CELL_CONTEXT_INFORMATION, bool, uint16_t>>
                sequence_of_cell_information; ///< Sequence of cell information todo: replace uint16_t with NEIGHBOR RELATION TABLE
        } format_3; ///< Control Message format 3 contents

        struct
        {
            // O-RAN WG3 E2SM RC v01.02 9.2.1.4.4
            std::vector<std::tuple<RNTI, UE_CONTEXT_INFORMATION, CELL_GLOBAL_ID>>
                sequence_of_ue_information; ///< Sequence of UE information
            // Cell Global ID, Cell Context Information, Neighbor Relation Table
            std::vector<std::tuple<CELL_GLOBAL_ID, CELL_CONTEXT_INFORMATION, uint16_t>>
                sequence_of_cell_information; ///< Sequence of cell information todo: replace uint16_t with NEIGHBOR RELATION TABLE
        } format_4; ///< Control Message format 4 contents

        struct
        {
            // O-RAN WG3 E2SM RC v01.02 9.2.1.4.5
            std::vector<std::pair<RAN_PARAMETER_ID, double>>
                list_of_ran_parameters_requested; ///< List of requested parameters
                                                   // todo: replace double with RAN PARAMETER VALUE
                                                  // TYPE
        } format_5; ///< Control Message format 5 contents

        struct
        {
            // O-RAN WG3 E2SM RC v01.02 9.2.1.4.6
            // Cell Global ID, Cell Context Information, Cell Deleted, Neighbor Relation Table
            // todo: very complicated std::vector<std::tuple<INDICATION_STYLE, uint16_t, bool,
            // uint16_t>> sequence_of_insert_styles_for_multiple_actions;
        } format_6; ///< Control Message format 6 contents

        uint8_t raw[1000];  ///< Control Message raw data todo: workaround this arbitrary limit
    } contents; ///< Control Message contents
} E2SM_RC_RIC_CONTROL_MESSAGE;

/**
 * \brief E2SM RC Control Request message to Json
 * \param j Json object that will be encoded
 * \param p E2SM_RC_RIC_CONTROL_MESSAGE to encode to the Json
 */
void
to_json(Json& j, const E2SM_RC_RIC_CONTROL_MESSAGE& p)
{
    j.update(Json{{"format", p.format}, {"contents", p.contents.raw}});
}

/**
 * \brief Json to E2SM RC Control Request message
 * \param j Json object that will be decoded
 * \param p E2SM_RC_RIC_CONTROL_MESSAGE to decode from the Json
 */
void
from_json(const Json& j, E2SM_RC_RIC_CONTROL_MESSAGE& p)
{
    j.at("format").get_to(p.format);
    j.at("contents").get_to(p.contents.raw);
}

} // namespace ns3
#endif // NS3_E2SM_RC_CONTROL_TYPES_H
