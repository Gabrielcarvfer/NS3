//
// Created by Gabriel Ferreira (@gabrielcarvfer) on 27/10/22.
//

#include "ns3/E2SM-RC-control-types.h"
#include "ns3/E2SM-RC-indication-types.h"
#include "ns3/core-module.h"
#include "ns3/json.hpp"

NS_LOG_COMPONENT_DEFINE("TestE2SmRcMessages");

using namespace ns3;

void
indication_header_formats()
{
    E2SM_RC_RIC_INDICATION_HEADER msg;
    E2SM_RC_RIC_INDICATION_HEADER msg_2;
    Json json_msg;

    // format 1
    msg.format = ns3::RIC_INDICATION_HEADER_FORMAT_1;
    msg.contents.format_1.eventTriggerConditionID = 2;
    msg.contents.format_1.padding = 0;

    to_json(json_msg, msg);
    NS_ASSERT(json_msg["format"] == msg.format);
    NS_ASSERT(json_msg["contents"] == msg.contents.raw);

    from_json(json_msg, msg_2);
    NS_ASSERT(msg_2.format == msg.format);
    NS_ASSERT(msg_2.contents.format_1.eventTriggerConditionID == 2);
    NS_ASSERT(msg_2.contents.format_1.padding == 0);

    // format 2
    msg.format = ns3::RIC_INDICATION_HEADER_FORMAT_2;
    msg.contents.format_2.RNTI = 12;
    msg.contents.format_2.RICInsertStyleType =
        RIC_INSERT_SERVICE_STYLES::CONNECTED_MODE_MOBILITY_CONTROL_REQUEST::VALUE;
    msg.contents.format_2.InsertIndicationID = RIC_INSERT_SERVICE_STYLES::
        CONNECTED_MODE_MOBILITY_CONTROL_REQUEST::HANDOVER_CONTROL_REQUEST::VALUE;

    to_json(json_msg, msg);
    NS_ASSERT(json_msg["format"] == msg.format);
    NS_ASSERT(json_msg["contents"] == msg.contents.raw);

    from_json(json_msg, msg_2);
    NS_ASSERT(msg_2.format == msg.format);
    NS_ASSERT(msg_2.contents.format_2.RNTI == 12);
    NS_ASSERT(msg_2.contents.format_2.RICInsertStyleType ==
              RIC_INSERT_SERVICE_STYLES::CONNECTED_MODE_MOBILITY_CONTROL_REQUEST::VALUE);
    NS_ASSERT(msg_2.contents.format_2.InsertIndicationID ==
              RIC_INSERT_SERVICE_STYLES::CONNECTED_MODE_MOBILITY_CONTROL_REQUEST::
                  HANDOVER_CONTROL_REQUEST::VALUE);

    // format 3
    msg.format = ns3::RIC_INDICATION_HEADER_FORMAT_3;
    msg.contents.format_3.RNTI = 128;
    msg.contents.format_3.eventTriggerConditionID = 3;

    to_json(json_msg, msg);
    NS_ASSERT(json_msg["format"] == msg.format);
    NS_ASSERT(json_msg["contents"] == msg.contents.raw);

    from_json(json_msg, msg_2);
    NS_ASSERT(msg_2.format == msg.format);
    NS_ASSERT(msg_2.contents.format_3.RNTI == 128);
    NS_ASSERT(msg_2.contents.format_3.eventTriggerConditionID == 3);
}

void
control_header_formats()
{
    E2SM_RC_RIC_CONTROL_HEADER msg;
    E2SM_RC_RIC_CONTROL_HEADER msg_2;
    Json json_msg;

    // format 1
    msg.format = ns3::RC_CONTROL_HEADER_FORMAT_1;
    msg.contents.format_1.RNTI = 2;
    msg.contents.format_1.RICControlStyleType =
        RIC_CONTROL_SERVICE_STYLES::CONNECTED_MODE_MOBILITY_CONTROL::VALUE;
    msg.contents.format_1.ControlActionID =
        RIC_CONTROL_SERVICE_STYLES::CONNECTED_MODE_MOBILITY_CONTROL::HANDOVER_CONTROL::VALUE;
    msg.contents.format_1.RicDecision = ns3::RC_ACCEPT;

    to_json(json_msg, msg);
    NS_ASSERT(json_msg["format"] == msg.format);
    NS_ASSERT(json_msg["contents"] == msg.contents.raw);

    from_json(json_msg, msg_2);
    NS_ASSERT(msg_2.format == msg.format);
    NS_ASSERT(msg_2.contents.format_1.RNTI == 2);
    NS_ASSERT(msg_2.contents.format_1.RICControlStyleType ==
              RIC_CONTROL_SERVICE_STYLES::CONNECTED_MODE_MOBILITY_CONTROL::VALUE);
    NS_ASSERT(msg_2.contents.format_1.ControlActionID ==
              RIC_CONTROL_SERVICE_STYLES::CONNECTED_MODE_MOBILITY_CONTROL::HANDOVER_CONTROL::VALUE);
    NS_ASSERT(msg_2.contents.format_1.RicDecision == ns3::RC_ACCEPT);

    // format 2
    msg.format = ns3::RC_CONTROL_HEADER_FORMAT_2;
    msg.contents.format_2.RNTI = 12;
    msg.contents.format_2.RicDecision = ns3::RC_REJECT;

    to_json(json_msg, msg);
    NS_ASSERT(json_msg["format"] == msg.format);
    NS_ASSERT(json_msg["contents"] == msg.contents.raw);

    from_json(json_msg, msg_2);
    NS_ASSERT(msg_2.format == msg.format);
    NS_ASSERT(msg_2.contents.format_2.RNTI == 12);
    NS_ASSERT(msg_2.contents.format_2.RicDecision == ns3::RC_REJECT);
}

int
main()
{
    indication_header_formats();
    control_header_formats();
    return 0;
}
