//
// Created by Gabriel Ferreira (@gabrielcarvfer) on 26/10/22.
//

#ifndef NS3_E2SM_RC_INDICATION_TYPES_H
#define NS3_E2SM_RC_INDICATION_TYPES_H

#include "ns3/json.hpp"

using Json = nlohmann::json; ///< nlohmann's Json type

/**
 * \ingroup oran
 * E2SM RC indication types and format declarations.
 */

namespace ns3
{
namespace oran
{
// O-RAN WG3 E2SM RC v01.02 7.4.1
/**
 * \brief E2SM RC RIC Report Service Indication styles and service types
 */
namespace RIC_REPORT_SERVICE_STYLES
{
/**
* \brief E2SM RC RIC Report Indication styles and service types
 */
namespace MESSAGE_COPY
{
const uint8_t VALUE = 1; ///< E2SM RC RIC Report Indication's Message Copy service
// O-RAN WG3 E2SM RC v01.02 7.4.2.1 + RAN PARAMETERS 8.3.2
} // namespace MESSAGE_COPY

namespace CALL_PROCESS_OUTCOME
{
const uint8_t VALUE = 2; ///< E2SM RC RIC Report Indication's Call Process Outcome service
// O-RAN WG3 E2SM RC v01.02 7.4.3.1 + RAN PARAMETERS 8.2.1
} // namespace CALL_PROCESS_OUTCOME

namespace E2_NODE_INFORMATION
{
const uint8_t VALUE = 3; ///< E2SM RC RIC Report Indication's E2 Node Information service
// O-RAN WG3 E2SM RC v01.02 7.4.4.1  + RAN PARAMETERS 8.3.4
} // namespace E2_NODE_INFORMATION

namespace UE_INFORMATION
{
const uint8_t VALUE = 4; ///< E2SM RC RIC Report Indication's UE Information service
// O-RAN WG3 E2SM RC v01.02 7.4.5.1
} // namespace UE_INFORMATION

namespace ON_DEMAND_REPORT
{
const uint8_t VALUE = 5; ///< E2SM RC RIC Report Indication's On Demand service
// O-RAN WG3 E2SM RC v01.02 7.4.6.1
} // namespace ON_DEMAND_REPORT
} // namespace RIC_REPORT_SERVICE_STYLES

// O-RAN WG3 E2SM RC v01.02 7.5.1
/**
 * \brief E2SM RC RIC Insert Service Indication styles and service types
 */
namespace RIC_INSERT_SERVICE_STYLES
{
/**
 * \brief E2SM RC Radio Bearer Control Request style and associated service types
 */
namespace RADIO_BEARER_CONTROL_REQUEST
{
const uint8_t VALUE = 1; ///< E2SM RC Radio Bearer Control Request style

// O-RAN WG3 E2SM RC v01.02 7.5.2.1 + RAN PARAMETERS 8.3.2
namespace DRB_QOS_CONFIGURATION_REQUEST
{
const uint8_t VALUE = 1; ///< E2SM RC Radio Bearer Control Request's DRB QoS Configuration Request service
}

namespace QOS_FLOW_MAPPING_CONFIGURATION_REQUEST
{
const uint8_t VALUE = 2; ///< E2SM RC Radio Bearer Control Request's QoS Flow Mapping Configuration Request service
}

namespace LOGICAL_CHANNEL_CONFIGURATION_REQUEST
{
const uint8_t VALUE = 3; ///< E2SM RC Radio Bearer Control Request's Logical Channel Configuration Request service
}

namespace RADIO_ADMISSION_CONTROL_REQUEST
{
const uint8_t VALUE = 4; ///< E2SM RC Radio Bearer Control Request's Radio Admission Control Request service
}

namespace DRB_TERMINATION_CONTROL_REQUEST
{
const uint8_t VALUE = 5; ///< E2SM RC Radio Bearer Control Request's DRB Termination Control Request service
}

namespace DRB_SPLIT_RATION_CONTROL_REQUEST
{
const uint8_t VALUE = 6; ///< E2SM RC Radio Bearer Control Request's DRB Split Ration Control Request service
}

namespace PDCP_DUPLICATION_CONTROL_REQUEST
{
const uint8_t VALUE = 7; ///< E2SM RC Radio Bearer Control Request's PDCP Duplication Control Request service
}
} // namespace RADIO_BEARER_CONTROL_REQUEST

/**
 * \brief E2SM RC Radio Resource Allocation Control Request style and associated service types
 */
namespace RADIO_RESOURCE_ALLOCATION_CONTROL_REQUEST
{
const uint8_t VALUE = 2;  ///< E2SM RC Radio Resource Allocation Control Request style

// O-RAN WG3 E2SM RC v01.02 7.5.3.1 + RAN PARAMETERS 8.3.3
namespace DRX_PARAMETER_CONFIGURATION_REQUEST
{
const uint8_t VALUE = 1; ///< E2SM RC Radio Resource Allocation Control Request's DRX Parameter Configuration Request service
}

namespace SR_PERIODICITY_CONFIGURATION_REQUEST
{
const uint8_t VALUE = 2; ///< E2SM RC Radio Resource Allocation Control Request's SR Periodicity Configuration Request service
}

namespace SPS_PARAMETERS_CONFIGURATION_REQUEST
{
const uint8_t VALUE = 3; ///< E2SM RC Radio Resource Allocation Control Request's SPS Parameters Configuration Request service
}

namespace CONFIGURED_GRANT_CONTROL_REQUEST
{
const uint8_t VALUE = 4; ///< E2SM RC Radio Resource Allocation Control Request's Configured Grant Control Request service
}

namespace CQI_TABLE_CONFIGURATION_REQUEST
{
const uint8_t VALUE = 5; ///< E2SM RC Radio Resource Allocation Control Request's CQI Table Configuration Request service
}

namespace SLICE_LEVEL_PRB_QUOTA_REQUEST
{
const uint8_t VALUE = 6; ///< E2SM RC Radio Resource Allocation Control Request's Slice Level PRB Quota Request service
}
} // namespace RADIO_RESOURCE_ALLOCATION_CONTROL_REQUEST

namespace CONNECTED_MODE_MOBILITY_CONTROL_REQUEST
{
const uint8_t VALUE = 3;  ///< E2SM RC Connected Mode Mobility Control Request style

// O-RAN WG3 E2SM RC v01.02 7.5.4.1  + RAN PARAMETERS 8.3.4
namespace HANDOVER_CONTROL_REQUEST
{
const uint8_t VALUE = 1; ///< E2SM RC Connected Mode Mobility Control Request's Handover Control Request service
}

namespace CONDITIONAL_HANDOVER_CONTROL_REQUEST
{
const uint8_t VALUE = 2; ///< E2SM RC Connected Mode Mobility Control Request's Conditional Handover Control Request service
}

namespace DUAL_ACTIVE_PROTOCOL_STACK_HANDOVER_CONTROL_REQUEST
{
const uint8_t VALUE = 3; ///< E2SM RC Connected Mode Mobility Control Request's Dual Active Protocol Stack Handover Control Request service
}
} // namespace CONNECTED_MODE_MOBILITY_CONTROL_REQUEST

namespace RADIO_ACCESS_CONTROL_REQUEST
{
const uint8_t VALUE = 4;  ///< E2SM RC Radio Access Control Request style

// O-RAN WG3 E2SM RC v01.02 7.5.5.1
namespace UE_ADMISSION_CONTROL_REQUEST
{
const uint8_t VALUE = 1; ///< E2SM RC Radio Access Control Request's UE Admission Control Request service
}

namespace RACH_BACKOFF_CONTROL_REQUEST
{
const uint8_t VALUE = 2; ///< E2SM RC Radio Access Control Request's RACH Backoff Control Request service
}

namespace ACCESS_BARRING_CONTROL_REQUEST
{
const uint8_t VALUE = 3; ///< E2SM RC Radio Access Control Request's Access Barring Control Request service
}

namespace RRC_CONNECTION_RELEASE
{
const uint8_t VALUE = 4; ///< E2SM RC Radio Access Control Request's RRC Connection Release service
}

namespace RRC_CONNECTION_REJECT
{
const uint8_t VALUE = 5; ///< E2SM RC Radio Access Control Request's RRC Connection Reject service
}
} // namespace RADIO_ACCESS_CONTROL_REQUEST

namespace DUAL_CONNECTIVITY_CONTROL_REQUEST
{
const uint8_t VALUE = 5;  ///< E2SM RC Dual Connectivity Control Request style

// O-RAN WG3 E2SM RC v01.02 7.5.6.1
namespace DC_SECONDARY_NODE_ADDITION_CONTROL_REQUEST
{
const uint8_t VALUE = 1; ///< E2SM RC Dual Connectivity Control Request's DC Secondary Node Addition Control Request service
}

namespace DC_SECONDARY_NODE_MODIFICATION_AND_RELEASE_CONTROL_REQUEST
{
const uint8_t VALUE = 2; ///< E2SM RC Dual Connectivity Control Request's DC Secondary Node Modification and Release Control Request service
}

namespace DC_PSCELL_CHANGE_CONTROL_REQUEST
{
const uint8_t VALUE = 3; ///< E2SM RC Dual Connectivity Control Request's DC PSCell Change Control Request service
}

namespace DC_SECONDARY_NODE_CHANGE_CONTROL_REQUEST
{
const uint8_t VALUE = 4; ///< E2SM RC Dual Connectivity Control Request's DC Secondary Node Change Control Request service
}

namespace DC_DRB_TERMINATION_CONTROL_REQUEST
{
const uint8_t VALUE = 5; ///< E2SM RC Dual Connectivity Control Request's DC DRB Termination Control Request service
}
} // namespace DUAL_CONNECTIVITY_CONTROL_REQUEST

namespace CARRIER_AGGREGATION_CONTROL_REQUEST
{
const uint8_t VALUE = 6;  ///< E2SM RC Carrier Aggregation Control Request style

// O-RAN WG3 E2SM RC v01.02 7.5.7.1
namespace CA_SECONDARY_CELL_ADDITION_CONTROL_REQUEST
{
const uint8_t VALUE = 1; ///< E2SM RC Carrier Aggregation Control Request's CA Secondary Cell Addition Control Request service
}

namespace CA_SECONDARY_CELL_MODIFICATION_AND_RELEASE_CONTROL_REQUEST
{
const uint8_t VALUE = 2; ///< E2SM RC Carrier Aggregation Control Request's CA Secondary Cell Modification and Release Control Request service
}
} // namespace CARRIER_AGGREGATION_CONTROL_REQUEST

namespace IDLE_MODE_MOBILITY_CONTROL_REQUEST
{
const uint8_t VALUE = 7;  ///< E2SM RC Idle Mode Mobility Control Request style

// O-RAN WG3 E2SM RC v01.02 7.5.8.1
namespace CELL_RESELECTION_PRIORITY_REQUEST
{
const uint8_t VALUE = 1; ///< E2SM RC Idle Mode Mobility Control Request's Cell Reselection Priority Request service
}
} // namespace IDLE_MODE_MOBILITY_CONTROL_REQUEST

namespace MULTIPLE_ACTIONS_CONTROL_REQUEST
{
const uint8_t VALUE = 255;  ///< E2SM RC Multiple Actions Control Request style
// O-RAN WG3 E2SM RC v01.02 7.5.9
// contain multiple fundamental indications such as the ones above
} // namespace MULTIPLE_ACTIONS_CONTROL_REQUEST
} // namespace RIC_INSERT_SERVICE_STYLES

/**
 * \brief E2SM RC Indication header formats
 */
enum E2SM_RC_RIC_INDICATION_HEADER_FORMAT
{
    RIC_INDICATION_HEADER_FORMAT_1 = 1,
    RIC_INDICATION_HEADER_FORMAT_2,
    RIC_INDICATION_HEADER_FORMAT_3
};

/**
 * \brief E2SM RC Indication header
 */
typedef struct
{
    enum E2SM_RC_RIC_INDICATION_HEADER_FORMAT format; ///< Indication Header format

    union {
        struct
        {
            uint16_t eventTriggerConditionID; ///< Condition ID for event that triggered the indication
            uint16_t padding; ///< Unused bytes
        } format_1; ///< Indication Header format 1 contents

        struct
        {
            uint16_t RNTI; ///< UE's RNTI identifier
            // One of subspace VALUEs of RIC_REPORT_SERVICE_STYLES,
            // RIC_INSERT_SERVICE_STYLES or RIC_CONTROL_SERVICE_STYLES
            // todo: RIC_REPORT_SERVICE_STYLES
            uint8_t RICInsertStyleType; ///< E2SM Indication style
            // One of subspace VALUEs within RIC_REPORT_SERVICE_STYLES,
            // RIC_INSERT_SERVICE_STYLES or RIC_CONTROL_SERVICE_STYLES
            // todo: RIC_REPORT_SERVICE_STYLES
            uint8_t InsertIndicationID; ///< E2SM Indication service
        } format_2; ///< Indication Header format 2 contents

        struct
        {
            uint16_t eventTriggerConditionID; ///< Condition ID for event that triggered the indication
            uint16_t RNTI; ///< UE's RNTI identifier
        } format_3; ///< Indication Header format 3 contents

        uint32_t raw; ///< Indication Header raw contents
    } contents;  ///< Indication Header contents
} E2SM_RC_RIC_INDICATION_HEADER;

/**
 * \brief E2SM RC RIC Indication Header to Json
 * \param j Json object that will be encoded
 * \param p E2SM_RC_RIC_INDICATION_HEADER to encode to the Json
 */
void
to_json(Json& j, const E2SM_RC_RIC_INDICATION_HEADER& p)
{
    j.update(Json{{"format", p.format}, {"contents", p.contents.raw}});
}

/**
 * \brief Json to E2SM RC RIC Indication Header
 * \param j Json object that will be decoded
 * \param p E2SM_RC_RIC_INDICATION_HEADER to decode from the Json
 */
void
from_json(const Json& j, E2SM_RC_RIC_INDICATION_HEADER& p)
{
    j.at("format").get_to(p.format);
    j.at("contents").get_to(p.contents.raw);
}

/**
 * \brief E2SM RC Indication formats
 */
enum RIC_INDICATION_MESSAGE_FORMAT
{
    RIC_INDICATION_MESSAGE_FORMAT_1 = 1,
    RIC_INDICATION_MESSAGE_FORMAT_2,
    RIC_INDICATION_MESSAGE_FORMAT_3,
    RIC_INDICATION_MESSAGE_FORMAT_4,
    RIC_INDICATION_MESSAGE_FORMAT_5,
    RIC_INDICATION_MESSAGE_FORMAT_6
};

typedef uint16_t RNTI;
typedef uint32_t RAN_PARAMETER_ID;
typedef double RAN_PARAMETER_VALUE; // todo: implement ELEMENT, STRUCT and LIST formats
typedef std::string UE_CONTEXT_INFORMATION;
typedef std::string CELL_CONTEXT_INFORMATION;
typedef uint8_t INDICATION_STYLE;
typedef uint16_t CELL_GLOBAL_ID;

/**
 * \brief E2SM KPM Indication message formats
 */
typedef struct
{
    enum RIC_INDICATION_MESSAGE_FORMAT format; ///< Control Indication Message format

    union {
        struct
        {
            // O-RAN WG3 E2SM RC v01.02 9.2.1.4.1
            // List of RAN parameter values
            // RAN Parameter ID, RAN Parameter Value
            std::vector<std::pair<RAN_PARAMETER_ID, RAN_PARAMETER_VALUE>>
                sequence_of_ran_parameters;
        } format_1; ///< E2SM RC Indication Message format 1 contents

        struct
        {
            // O-RAN WG3 E2SM RC v01.02 9.2.1.4.2
            // List of RAN parameter values per UE/RNTI
            // UE ID (RNTI), Sequence of RAN parameters
            std::vector<
                std::pair<RNTI, std::vector<std::pair<RAN_PARAMETER_ID, RAN_PARAMETER_VALUE>>>>
                sequence_of_ue_identifiers;
        } format_2; ///< E2SM RC Indication Message format 2 contents

        struct
        {
            // O-RAN WG3 E2SM RC v01.02 9.2.1.4.3
            // Cell Global ID, Cell Context Information, Cell Deleted, Neighbor Relation Table
            std::vector<std::tuple<CELL_GLOBAL_ID, CELL_CONTEXT_INFORMATION, bool, uint16_t>>
                sequence_of_cell_information; // todo: replace uint16_t with NEIGHBOR RELATION TABLE
        } format_3; ///< E2SM RC Indication Message format 3 contents

        struct
        {
            // O-RAN WG3 E2SM RC v01.02 9.2.1.4.4
            std::vector<std::tuple<RNTI, UE_CONTEXT_INFORMATION, CELL_GLOBAL_ID>>
                sequence_of_ue_information;
            // Cell Global ID, Cell Context Information, Neighbor Relation Table
            std::vector<std::tuple<CELL_GLOBAL_ID, CELL_CONTEXT_INFORMATION, uint16_t>>
                sequence_of_cell_information; // todo: replace uint16_t with NEIGHBOR RELATION TABLE
        } format_4; ///< E2SM RC Indication Message format 4 contents

        struct
        {
            // O-RAN WG3 E2SM RC v01.02 9.2.1.4.5
            std::vector<std::pair<RAN_PARAMETER_ID, double>>
                list_of_ran_parameters_requested; // todo: replace double with RAN PARAMETER VALUE
                                                  // TYPE
        } format_5; ///< E2SM RC Indication Message format 5 contents

        struct
        {
            // O-RAN WG3 E2SM RC v01.02 9.2.1.4.6
            // Cell Global ID, Cell Context Information, Cell Deleted, Neighbor Relation Table
            // todo: very complicated std::vector<std::tuple<INDICATION_STYLE, uint16_t, bool,
            // uint16_t>> sequence_of_insert_styles_for_multiple_actions;
        } format_6; ///< E2SM RC Indication Message format 6 contents

        uint8_t raw[1000]; ///< E2SM RC Indication Message raw contents todo: workaround this arbitrary limit
    } contents; ///< E2SM RC Indication Message contents
} RIC_INDICATION_MESSAGE;

/**
 * \brief E2SM RC RIC Indication Message to Json
 * \param j Json object that will be encoded
 * \param p RIC_INDICATION_MESSAGE to encode to the Json
 */
void
to_json(Json& j, const RIC_INDICATION_MESSAGE& p)
{
    j.update(Json{{"format", p.format}, {"contents", p.contents.raw}});
}

/**
 * \brief Json to E2SM RC RIC Indication Message
 * \param j Json object that will be decoded
 * \param p RIC_INDICATION_MESSAGE to decode from the Json
 */
void
from_json(const Json& j, RIC_INDICATION_MESSAGE& p)
{
    j.at("format").get_to(p.format);
    j.at("contents").get_to(p.contents.raw);
}

} // namespace oran
} // namespace ns3
#endif // NS3_E2SM_RC_INDICATION_TYPES_H
