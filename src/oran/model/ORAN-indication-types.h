//
// Created by Gabriel Ferreira (@gabrielcarvfer) on 26/10/22.
//

#ifndef NS3_ORAN_INDICATION_TYPES_H
#define NS3_ORAN_INDICATION_TYPES_H

#include "ns3/json.hpp"

using Json = nlohmann::json;

namespace ns3
{
// O-RAN WG3 E2SM RC v01.02 7.4.1
namespace RIC_REPORT_SERVICE_STYLES
{
    namespace MESSAGE_COPY
    {
        uint8_t VALUE = 1;
        // O-RAN WG3 E2SM RC v01.02 7.4.2.1 + RAN PARAMETERS 8.3.2
    }
    namespace CALL_PROCESS_OUTCOME
    {
        uint8_t VALUE = 2;
        // O-RAN WG3 E2SM RC v01.02 7.4.3.1 + RAN PARAMETERS 8.2.1
    }
    namespace E2_NODE_INFORMATION
    {
        uint8_t VALUE = 3;
        // O-RAN WG3 E2SM RC v01.02 7.4.4.1  + RAN PARAMETERS 8.3.4
    }
    namespace UE_INFORMATION
    {
        uint8_t VALUE = 4;
        // O-RAN WG3 E2SM RC v01.02 7.4.5.1
    }
    namespace ON_DEMAND_REPORT
    {
        uint8_t VALUE = 5;
        // O-RAN WG3 E2SM RC v01.02 7.4.6.1
    }
}

// O-RAN WG3 E2SM RC v01.02 7.5.1
namespace RIC_INSERT_SERVICE_STYLES
{
    namespace RADIO_BEARER_CONTROL_REQUEST
    {
        uint8_t VALUE = 1;
        // O-RAN WG3 E2SM RC v01.02 7.5.2.1 + RAN PARAMETERS 8.3.2
        namespace DRB_QOS_CONFIGURATION_REQUEST{ uint8_t VALUE = 1; }
        namespace QOS_FLOW_MAPPING_CONFIGURATION_REQUEST{ uint8_t VALUE = 2; }
        namespace LOGICAL_CHANNEL_CONFIGURATION_REQUEST{ uint8_t VALUE = 3; }
        namespace RADIO_ADMISSION_CONTROL_REQUEST{ uint8_t VALUE = 4; }
        namespace DRB_TERMINATION_CONTROL_REQUEST{ uint8_t VALUE = 5; }
        namespace DRB_SPLIT_RATION_CONTROL_REQUEST{ uint8_t VALUE = 6; }
        namespace PDCP_DUPLICATION_CONTROL_REQUEST{ uint8_t VALUE = 7; }
    }
    namespace RADIO_RESOURCE_ALLOCATION_CONTROL_REQUEST
    {
        uint8_t VALUE = 2;
        // O-RAN WG3 E2SM RC v01.02 7.5.3.1 + RAN PARAMETERS 8.3.3
        namespace DRX_PARAMETER_CONFIGURATION_REQUEST{ uint8_t VALUE = 1; }
        namespace SR_PERIODICITY_CONFIGURATION_REQUEST{ uint8_t VALUE = 2; }
        namespace SPS_PARAMETERS_CONFIGURATION_REQUEST{ uint8_t VALUE = 3; }
        namespace CONFIGURED_GRANT_CONTROL_REQUEST{ uint8_t VALUE = 4; }
        namespace CQI_TABLE_CONFIGURATION_REQUEST{ uint8_t VALUE = 5; }
        namespace SLICE_LEVEL_PRB_QUOTA_REQUEST{ uint8_t VALUE = 6; }
    }
    namespace CONNECTED_MODE_MOBILITY_CONTROL_REQUEST
    {
        uint8_t VALUE = 3;
        // O-RAN WG3 E2SM RC v01.02 7.5.4.1  + RAN PARAMETERS 8.3.4
        namespace HANDOVER_CONTROL_REQUEST{ uint8_t VALUE = 1; }
        namespace CONDITIONAL_HANDOVER_CONTROL_REQUEST{ uint8_t VALUE = 2; }
        namespace DUAL_ACTIVE_PROTOCOL_STACK_HANDOVER_CONTROL_REQUEST{ uint8_t VALUE = 3; }
    }
    namespace RADIO_ACCESS_CONTROL_REQUEST
    {
        uint8_t VALUE = 4;
        // O-RAN WG3 E2SM RC v01.02 7.5.5.1
        namespace UE_ADMISSION_CONTROL_REQUEST{ uint8_t VALUE = 1; }
        namespace RACH_BACKOFF_CONTROL_REQUEST{ uint8_t VALUE = 2; }
        namespace ACCESS_BARRING_CONTROL_REQUEST{ uint8_t VALUE = 3; }
        namespace RRC_CONNECTION_RELEASE{ uint8_t VALUE = 4; }
        namespace RRC_CONNECTION_REJECT{ uint8_t VALUE = 5; }
    }
    namespace DUAL_CONNECTIVITY_CONTROL_REQUEST
    {
        uint8_t VALUE = 5;
        // O-RAN WG3 E2SM RC v01.02 7.5.6.1
        namespace DC_SECONDARY_NODE_ADDITION_CONTROL_REQUEST{ uint8_t VALUE = 1; }
        namespace DC_SECONDARY_NODE_MODIFICATION_AND_RELEASE_CONTROL_REQUEST{ uint8_t VALUE = 2; }
        namespace DC_PSCELL_CHANGE_CONTROL_REQUEST{ uint8_t VALUE = 3; }
        namespace DC_SECONDARY_NODE_CHANGE_CONTROL_REQUEST{ uint8_t VALUE = 4; }
        namespace DC_DRB_TERMINATION_CONTROL_REQUEST{ uint8_t VALUE = 5; }
    }
    namespace CARRIER_AGGREGATION_CONTROL_REQUEST
    {
        uint8_t VALUE = 6;
        // O-RAN WG3 E2SM RC v01.02 7.5.7.1
        namespace CA_SECONDARY_CELL_ADDITION_CONTROL_REQUEST{ uint8_t VALUE = 1; }
        namespace CA_SECONDARY_CELL_MODIFICATION_AND_RELEASE_CONTROL_REQUEST{ uint8_t VALUE = 2; }
    }
    namespace IDLE_MODE_MOBILITY_CONTROL_REQUEST
    {
        uint8_t VALUE = 7;
        // O-RAN WG3 E2SM RC v01.02 7.5.8.1
        namespace CELL_RESELECTION_PRIORITY_REQUEST{ uint8_t VALUE = 1; }
    }
    namespace MULTIPLE_ACTIONS_CONTROL_REQUEST
    {
        uint8_t VALUE = 255;
        // O-RAN WG3 E2SM RC v01.02 7.5.9
        // contain multiple fundamental indications such as the ones above
    }
}

// O-RAN WG3 E2SM RC v01.02 7.6.1
namespace RIC_CONTROL_SERVICE_STYLES
{
    namespace RADIO_BEARER_CONTROL
    {
        uint8_t VALUE = 1;
        // O-RAN WG3 E2SM RC v01.02 7.6.2.1 + RAN PARAMETERS 8.4.2
        namespace DRB_QOS_CONFIGURATION{ uint8_t VALUE = 1; }
        namespace QOS_FLOW_MAPPING_CONFIGURATION{ uint8_t VALUE = 2; }
        namespace LOGICAL_CHANNEL_CONFIGURATION{ uint8_t VALUE = 3; }
        namespace RADIO_ADMISSION_CONTROL{ uint8_t VALUE = 4; }
        namespace DRB_TERMINATION_CONTROL{ uint8_t VALUE = 5; }
        namespace DRB_SPLIT_RATION_CONTROL{ uint8_t VALUE = 6; }
        namespace PDCP_DUPLICATION_CONTROL{ uint8_t VALUE = 7; }
    }
    namespace RADIO_RESOURCE_ALLOCATION_CONTROL
    {
        uint8_t VALUE = 2;
        // O-RAN WG3 E2SM RC v01.02 7.6.3.1
        namespace DRX_PARAMETER_CONFIGURATION{ uint8_t VALUE = 1; }
        namespace SR_PERIODICITY_CONFIGURATION{ uint8_t VALUE = 2; }
        namespace SPS_PARAMETERS_CONFIGURATION{ uint8_t VALUE = 3; }
        namespace CONFIGURED_GRANT_CONTROL{ uint8_t VALUE = 4; }
        namespace CQI_TABLE_CONFIGURATION{ uint8_t VALUE = 5; }
        namespace SLICE_LEVEL_PRB_QUOTA{ uint8_t VALUE = 6; }
    }
    namespace CONNECTED_MODE_MOBILITY_CONTROL
    {
        uint8_t VALUE = 3;
        // O-RAN WG3 E2SM RC v01.02 7.6.4.1 + RAN PARAMETERS 8.4.4
        namespace HANDOVER_CONTROL{ uint8_t VALUE = 1; }
        namespace CONDITIONAL_HANDOVER_CONTROL{ uint8_t VALUE = 2; }
        namespace DUAL_ACTIVE_PROTOCOL_STACK_HANDOVER_CONTROL{ uint8_t VALUE = 3; }
    }
    namespace RADIO_ACCESS_CONTROL
    {
        uint8_t VALUE = 4;
        // O-RAN WG3 E2SM RC v01.02 7.6.5.1
        namespace UE_ADMISSION_CONTROL{ uint8_t VALUE = 1; }
        namespace RACH_BACKOFF_CONTROL{ uint8_t VALUE = 2; }
        namespace ACCESS_BARRING_CONTROL{ uint8_t VALUE = 3; }
        namespace RRC_CONNECTION_RELEASE_CONTROL{ uint8_t VALUE = 4; }
        namespace RRC_CONNECTION_REJECT_CONTROL{ uint8_t VALUE = 5; }
    }
    namespace DUAL_CONNECTIVITY_CONTROL
    {
        uint8_t VALUE = 5;
        // O-RAN WG3 E2SM RC v01.02 7.6.6.1 +
        namespace DC_SECONDARY_NODE_ADDITION_CONTROL{ uint8_t VALUE = 1; }
        namespace DC_SECONDARY_NODE_MODIFICATION_AND_RELEASE_CONTROL{ uint8_t VALUE = 2; }
        namespace DC_PSCELL_CHANGE_CONTROL{ uint8_t VALUE = 3; }
        namespace DC_SECONDARY_NODE_CHANGE_CONTROL{ uint8_t VALUE = 4; }
        namespace DC_DRB_TERMINATION_CONTROL{ uint8_t VALUE = 5; }
    }
    namespace CARRIER_AGGREGATION_CONTROL
    {
        uint8_t VALUE = 6;
        // O-RAN WG3 E2SM RC v01.02 7.6.7.1
        namespace CA_SECONDARY_CELL_ADDITION_CONTROL{ uint8_t VALUE = 1; }
        namespace CA_SECONDARY_CELL_MODIFICATION_AND_RELEASE_CONTROL{ uint8_t VALUE = 2; }
    }
    namespace IDLE_MODE_MOBILITY_CONTROL
    {
        uint8_t VALUE = 7;
        // O-RAN WG3 E2SM RC v01.02 7.6.8.1
        namespace CELL_RESELECTION_PRIORITY_CONTROL{ uint8_t VALUE = 1; }
    }
    namespace UE_INFORMATION_AND_ASSIGNMENT
    {
        uint8_t VALUE = 8;
        // O-RAN WG3 E2SM RC v01.02 7.6.9.1
        namespace UE_TO_EXPLICIT_UE_LIST_ASSIGNMENT_COMMAND{ uint8_t VALUE = 1; }
    }
    namespace MEASUREMENT_REPORTING_CONFIGURATION_CONTROL
    {
        uint8_t VALUE = 9;
        // O-RAN WG3 E2SM RC v01.02 7.6.11.1
        namespace ADD_MR_CONFIGURATION{ uint8_t VALUE = 1; }
        namespace MODIFY_MR_CONFIGURATION{ uint8_t VALUE = 2; }
        namespace DELETE_MR_CONFIGURATION{ uint8_t VALUE = 3; }
    }
    namespace MULTIPLE_ACTIONS_CONTROL
    {
        uint8_t VALUE = 255;
        // O-RAN WG3 E2SM RC v01.02 7.6.10
        // contain multiple fundamental indications such as the ones above
    }
}

enum RIC_INDICATION_HEADER_FORMAT{
    RIC_INDICATION_HEADER_FORMAT_1 = 1,
    RIC_INDICATION_HEADER_FORMAT_2,
    RIC_INDICATION_HEADER_FORMAT_3
};

typedef struct
{
    enum RIC_INDICATION_HEADER_FORMAT format;
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
}RIC_INDICATION_HEADER;

void to_json(Json& j, const RIC_INDICATION_HEADER& p) {
    j.update(Json{ {"format", p.format}, {"contents", p.contents.raw}});
}
void from_json(const Json& j, RIC_INDICATION_HEADER& p)
{
    j.at("format").get_to(p.format);
    j.at("contents").get_to(p.contents.raw);
}

}
#endif // NS3_ORAN_INDICATION_TYPES_H
