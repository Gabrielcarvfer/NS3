//
// Created by Gabriel Ferreira (@gabrielcarvfer) on 26/10/22.
//

#ifndef NS3_E2SM_RC_INDICATION_TYPES_H
#define NS3_E2SM_RC_INDICATION_TYPES_H

#include "ns3/json.hpp"

using Json = nlohmann::json;

namespace ns3
{
// O-RAN WG3 E2SM RC v01.02 7.4.1
namespace RIC_REPORT_SERVICE_STYLES
{
    namespace MESSAGE_COPY
    {
        const uint8_t VALUE = 1;
        // O-RAN WG3 E2SM RC v01.02 7.4.2.1 + RAN PARAMETERS 8.3.2
    }
    namespace CALL_PROCESS_OUTCOME
    {
        const uint8_t VALUE = 2;
        // O-RAN WG3 E2SM RC v01.02 7.4.3.1 + RAN PARAMETERS 8.2.1
    }
    namespace E2_NODE_INFORMATION
    {
        const uint8_t VALUE = 3;
        // O-RAN WG3 E2SM RC v01.02 7.4.4.1  + RAN PARAMETERS 8.3.4
    }
    namespace UE_INFORMATION
    {
        const uint8_t VALUE = 4;
        // O-RAN WG3 E2SM RC v01.02 7.4.5.1
    }
    namespace ON_DEMAND_REPORT
    {
        const uint8_t VALUE = 5;
        // O-RAN WG3 E2SM RC v01.02 7.4.6.1
    }
}

// O-RAN WG3 E2SM RC v01.02 7.5.1
namespace RIC_INSERT_SERVICE_STYLES
{
    namespace RADIO_BEARER_CONTROL_REQUEST
    {
        const uint8_t VALUE = 1;
        // O-RAN WG3 E2SM RC v01.02 7.5.2.1 + RAN PARAMETERS 8.3.2
        namespace DRB_QOS_CONFIGURATION_REQUEST{ const uint8_t VALUE = 1; }
        namespace QOS_FLOW_MAPPING_CONFIGURATION_REQUEST{ const uint8_t VALUE = 2; }
        namespace LOGICAL_CHANNEL_CONFIGURATION_REQUEST{ const uint8_t VALUE = 3; }
        namespace RADIO_ADMISSION_CONTROL_REQUEST{ const uint8_t VALUE = 4; }
        namespace DRB_TERMINATION_CONTROL_REQUEST{ const uint8_t VALUE = 5; }
        namespace DRB_SPLIT_RATION_CONTROL_REQUEST{ const uint8_t VALUE = 6; }
        namespace PDCP_DUPLICATION_CONTROL_REQUEST{ const uint8_t VALUE = 7; }
    }
    namespace RADIO_RESOURCE_ALLOCATION_CONTROL_REQUEST
    {
        const uint8_t VALUE = 2;
        // O-RAN WG3 E2SM RC v01.02 7.5.3.1 + RAN PARAMETERS 8.3.3
        namespace DRX_PARAMETER_CONFIGURATION_REQUEST{ const uint8_t VALUE = 1; }
        namespace SR_PERIODICITY_CONFIGURATION_REQUEST{ const uint8_t VALUE = 2; }
        namespace SPS_PARAMETERS_CONFIGURATION_REQUEST{ const uint8_t VALUE = 3; }
        namespace CONFIGURED_GRANT_CONTROL_REQUEST{ const uint8_t VALUE = 4; }
        namespace CQI_TABLE_CONFIGURATION_REQUEST{ const uint8_t VALUE = 5; }
        namespace SLICE_LEVEL_PRB_QUOTA_REQUEST{ const uint8_t VALUE = 6; }
    }
    namespace CONNECTED_MODE_MOBILITY_CONTROL_REQUEST
    {
        const uint8_t VALUE = 3;
        // O-RAN WG3 E2SM RC v01.02 7.5.4.1  + RAN PARAMETERS 8.3.4
        namespace HANDOVER_CONTROL_REQUEST{ const uint8_t VALUE = 1; }
        namespace CONDITIONAL_HANDOVER_CONTROL_REQUEST{ const uint8_t VALUE = 2; }
        namespace DUAL_ACTIVE_PROTOCOL_STACK_HANDOVER_CONTROL_REQUEST{ const uint8_t VALUE = 3; }
    }
    namespace RADIO_ACCESS_CONTROL_REQUEST
    {
        const uint8_t VALUE = 4;
        // O-RAN WG3 E2SM RC v01.02 7.5.5.1
        namespace UE_ADMISSION_CONTROL_REQUEST{ const uint8_t VALUE = 1; }
        namespace RACH_BACKOFF_CONTROL_REQUEST{ const uint8_t VALUE = 2; }
        namespace ACCESS_BARRING_CONTROL_REQUEST{ const uint8_t VALUE = 3; }
        namespace RRC_CONNECTION_RELEASE{ const uint8_t VALUE = 4; }
        namespace RRC_CONNECTION_REJECT{ const uint8_t VALUE = 5; }
    }
    namespace DUAL_CONNECTIVITY_CONTROL_REQUEST
    {
        const uint8_t VALUE = 5;
        // O-RAN WG3 E2SM RC v01.02 7.5.6.1
        namespace DC_SECONDARY_NODE_ADDITION_CONTROL_REQUEST{ const uint8_t VALUE = 1; }
        namespace DC_SECONDARY_NODE_MODIFICATION_AND_RELEASE_CONTROL_REQUEST{ const uint8_t VALUE = 2; }
        namespace DC_PSCELL_CHANGE_CONTROL_REQUEST{ const uint8_t VALUE = 3; }
        namespace DC_SECONDARY_NODE_CHANGE_CONTROL_REQUEST{ const uint8_t VALUE = 4; }
        namespace DC_DRB_TERMINATION_CONTROL_REQUEST{ const uint8_t VALUE = 5; }
    }
    namespace CARRIER_AGGREGATION_CONTROL_REQUEST
    {
        const uint8_t VALUE = 6;
        // O-RAN WG3 E2SM RC v01.02 7.5.7.1
        namespace CA_SECONDARY_CELL_ADDITION_CONTROL_REQUEST{ const uint8_t VALUE = 1; }
        namespace CA_SECONDARY_CELL_MODIFICATION_AND_RELEASE_CONTROL_REQUEST{ const uint8_t VALUE = 2; }
    }
    namespace IDLE_MODE_MOBILITY_CONTROL_REQUEST
    {
        const uint8_t VALUE = 7;
        // O-RAN WG3 E2SM RC v01.02 7.5.8.1
        namespace CELL_RESELECTION_PRIORITY_REQUEST{ const uint8_t VALUE = 1; }
    }
    namespace MULTIPLE_ACTIONS_CONTROL_REQUEST
    {
        const uint8_t VALUE = 255;
        // O-RAN WG3 E2SM RC v01.02 7.5.9
        // contain multiple fundamental indications such as the ones above
    }
}

enum E2SM_RC_RIC_INDICATION_HEADER_FORMAT{
    RIC_INDICATION_HEADER_FORMAT_1 = 1,
    RIC_INDICATION_HEADER_FORMAT_2,
    RIC_INDICATION_HEADER_FORMAT_3
};

typedef struct
{
    enum E2SM_RC_RIC_INDICATION_HEADER_FORMAT format;
    union
    {
        struct
        {
            uint16_t eventTriggerConditionID;
            uint16_t padding;
        }format_1;
        struct
        {
            uint16_t RNTI;
            // One of subspace VALUEs of RIC_REPORT_SERVICE_STYLES,
            // RIC_INSERT_SERVICE_STYLES or RIC_CONTROL_SERVICE_STYLES
            // todo: RIC_REPORT_SERVICE_STYLES
            uint8_t RICInsertStyleType;
            // One of subspace VALUEs within RIC_REPORT_SERVICE_STYLES,
            // RIC_INSERT_SERVICE_STYLES or RIC_CONTROL_SERVICE_STYLES
            // todo: RIC_REPORT_SERVICE_STYLES
            uint8_t InsertIndicationID;
        }format_2;
        struct
        {
            uint16_t eventTriggerConditionID;
            uint16_t RNTI;
        }format_3;
        uint32_t raw;
    } contents;
}E2SM_RC_RIC_INDICATION_HEADER;

void to_json(Json& j, const E2SM_RC_RIC_INDICATION_HEADER& p) {
    j.update(Json{ {"format", p.format}, {"contents", p.contents.raw}});
}
void from_json(const Json& j, E2SM_RC_RIC_INDICATION_HEADER& p)
{
    j.at("format").get_to(p.format);
    j.at("contents").get_to(p.contents.raw);
}


enum RIC_INDICATION_MESSAGE_FORMAT{
    RIC_INDICATION_MESSAGE_FORMAT_1 = 1,
    RIC_INDICATION_MESSAGE_FORMAT_2,
    RIC_INDICATION_MESSAGE_FORMAT_3,
    RIC_INDICATION_MESSAGE_FORMAT_4,
    RIC_INDICATION_MESSAGE_FORMAT_5,
    RIC_INDICATION_MESSAGE_FORMAT_6
};

typedef uint16_t RNTI;
typedef uint32_t RAN_PARAMETER_ID;
typedef double RAN_PARAMETER_VALUE; //todo: implement ELEMENT, STRUCT and LIST formats
typedef std::string UE_CONTEXT_INFORMATION;
typedef std::string CELL_CONTEXT_INFORMATION;
typedef uint8_t INDICATION_STYLE;
typedef uint16_t CELL_GLOBAL_ID;

typedef struct
{
    enum RIC_INDICATION_MESSAGE_FORMAT format;
    union
    {
        struct
        {
            // O-RAN WG3 E2SM RC v01.02 9.2.1.4.1
            // List of RAN parameter values
            // RAN Parameter ID, RAN Parameter Value
            std::vector<std::pair<RAN_PARAMETER_ID, RAN_PARAMETER_VALUE>> sequence_of_ran_parameters;
        }format_1;
        struct
        {
            // O-RAN WG3 E2SM RC v01.02 9.2.1.4.2
            // List of RAN parameter values per UE/RNTI
            // UE ID (RNTI), Sequence of RAN parameters
            std::vector<std::pair<RNTI, std::vector<std::pair<RAN_PARAMETER_ID, RAN_PARAMETER_VALUE>>>> sequence_of_ue_identifiers;
        }format_2;
        struct
        {
            // O-RAN WG3 E2SM RC v01.02 9.2.1.4.3
            // Cell Global ID, Cell Context Information, Cell Deleted, Neighbor Relation Table
            std::vector<std::tuple<CELL_GLOBAL_ID, CELL_CONTEXT_INFORMATION, bool, uint16_t>> sequence_of_cell_information; //todo: replace uint16_t with NEIGHBOR RELATION TABLE
        }format_3;
        struct
        {
            // O-RAN WG3 E2SM RC v01.02 9.2.1.4.4
            std::vector<std::tuple<RNTI, UE_CONTEXT_INFORMATION, CELL_GLOBAL_ID>> sequence_of_ue_information;
            // Cell Global ID, Cell Context Information, Neighbor Relation Table
            std::vector<std::tuple<CELL_GLOBAL_ID, CELL_CONTEXT_INFORMATION, uint16_t>> sequence_of_cell_information;//todo: replace uint16_t with NEIGHBOR RELATION TABLE
        }format_4;
        struct
        {
            // O-RAN WG3 E2SM RC v01.02 9.2.1.4.5
            std::vector<std::pair<RAN_PARAMETER_ID, double>> list_of_ran_parameters_requested; //todo: replace double with RAN PARAMETER VALUE TYPE
        }format_5;
        struct
        {
            // O-RAN WG3 E2SM RC v01.02 9.2.1.4.6
            // Cell Global ID, Cell Context Information, Cell Deleted, Neighbor Relation Table
            // todo: very complicated std::vector<std::tuple<INDICATION_STYLE, uint16_t, bool, uint16_t>> sequence_of_insert_styles_for_multiple_actions;
        }format_6;
        uint8_t raw[1000]; // todo: workaround this arbitrary limit
    } contents;
}RIC_INDICATION_MESSAGE;

void to_json(Json& j, const RIC_INDICATION_MESSAGE& p) {
  j.update(Json{ {"format", p.format}, {"contents", p.contents.raw}});
}
void from_json(const Json& j, RIC_INDICATION_MESSAGE& p)
{
  j.at("format").get_to(p.format);
  j.at("contents").get_to(p.contents.raw);
}

}
#endif // NS3_E2SM_RC_INDICATION_TYPES_H