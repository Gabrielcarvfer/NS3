//
// Created by Gabriel Ferreira (@gabrielcarvfer) on 27/10/22.
//

#include "E2SM-RC-indication-types.h"
#include "E2SM-RC-control-types.h"
#include <ns3/lte-enb-rrc.h>

void
E2AP::HandleE2SmRcIndicationPayload (std::string& src_endpoint, std::string& dest_endpoint, Json& payload)
{
  NS_LOG_FUNCTION(this);

  E2SM_RC_RIC_INDICATION_HEADER indicationHeader;
  NS_ASSERT(payload.contains ("HEADER"));
  from_json (payload["HEADER"], indicationHeader);

  switch (indicationHeader.format)
    {
      case RIC_INDICATION_HEADER_FORMAT_1:
        {
          // REPORT services
          //uint16_t eventTriggerConditionId = indicationHeader.contents.format_1.eventTriggerConditionID;
        }
      break;
      case RIC_INDICATION_HEADER_FORMAT_2:
        {
          // INSERT services
          uint16_t rnti = indicationHeader.contents.format_2.RNTI;
          switch (indicationHeader.contents.format_2.RICInsertStyleType)
            {
              case RIC_INSERT_SERVICE_STYLES::RADIO_BEARER_CONTROL_REQUEST::VALUE:
                {
                  switch (indicationHeader.contents.format_2.InsertIndicationID)
                    {
                      case RIC_INSERT_SERVICE_STYLES::RADIO_BEARER_CONTROL_REQUEST::DRB_QOS_CONFIGURATION_REQUEST::VALUE:
                        {

                        }
                      break;
                      case RIC_INSERT_SERVICE_STYLES::RADIO_BEARER_CONTROL_REQUEST::QOS_FLOW_MAPPING_CONFIGURATION_REQUEST::VALUE:
                        {

                        }
                      break;
                      case RIC_INSERT_SERVICE_STYLES::RADIO_BEARER_CONTROL_REQUEST::LOGICAL_CHANNEL_CONFIGURATION_REQUEST::VALUE:
                        {

                        }
                      break;
                      case RIC_INSERT_SERVICE_STYLES::RADIO_BEARER_CONTROL_REQUEST::RADIO_ADMISSION_CONTROL_REQUEST::VALUE:
                        {

                        }
                      break;
                      case RIC_INSERT_SERVICE_STYLES::RADIO_BEARER_CONTROL_REQUEST::DRB_TERMINATION_CONTROL_REQUEST::VALUE:
                        {

                        }
                      break;
                      case RIC_INSERT_SERVICE_STYLES::RADIO_BEARER_CONTROL_REQUEST::DRB_SPLIT_RATION_CONTROL_REQUEST::VALUE:
                        {

                        }
                      break;
                      case RIC_INSERT_SERVICE_STYLES::RADIO_BEARER_CONTROL_REQUEST::PDCP_DUPLICATION_CONTROL_REQUEST::VALUE:
                        {

                        }
                      break;
                      default:
                        NS_ABORT_MSG("Unknown Radio Bearer Control Request Indication ID");
                    }
                }
              break;
              case RIC_INSERT_SERVICE_STYLES::RADIO_RESOURCE_ALLOCATION_CONTROL_REQUEST::VALUE:
                {
                  switch (indicationHeader.contents.format_2.InsertIndicationID)
                    {
                      case RIC_INSERT_SERVICE_STYLES::RADIO_RESOURCE_ALLOCATION_CONTROL_REQUEST::DRX_PARAMETER_CONFIGURATION_REQUEST::VALUE:
                        {

                        }
                      break;
                      case RIC_INSERT_SERVICE_STYLES::RADIO_RESOURCE_ALLOCATION_CONTROL_REQUEST::SR_PERIODICITY_CONFIGURATION_REQUEST::VALUE:
                        {

                        }
                      break;
                      case RIC_INSERT_SERVICE_STYLES::RADIO_RESOURCE_ALLOCATION_CONTROL_REQUEST::SPS_PARAMETERS_CONFIGURATION_REQUEST::VALUE:
                        {

                        }
                      break;
                      case RIC_INSERT_SERVICE_STYLES::RADIO_RESOURCE_ALLOCATION_CONTROL_REQUEST::CONFIGURED_GRANT_CONTROL_REQUEST::VALUE:
                        {

                        }
                      break;
                      case RIC_INSERT_SERVICE_STYLES::RADIO_RESOURCE_ALLOCATION_CONTROL_REQUEST::CQI_TABLE_CONFIGURATION_REQUEST::VALUE:
                        {

                        }
                      break;
                      case RIC_INSERT_SERVICE_STYLES::RADIO_RESOURCE_ALLOCATION_CONTROL_REQUEST::SLICE_LEVEL_PRB_QUOTA_REQUEST::VALUE:
                        {

                        }
                      break;
                      default:
                        NS_ABORT_MSG("Unknown Radio Resource Allocation Control Request Indication ID");
                    }
                }
              break;
              case RIC_INSERT_SERVICE_STYLES::CONNECTED_MODE_MOBILITY_CONTROL_REQUEST::VALUE:
                {
                  switch (indicationHeader.contents.format_2.InsertIndicationID)
                    {
                      case RIC_INSERT_SERVICE_STYLES::CONNECTED_MODE_MOBILITY_CONTROL_REQUEST::HANDOVER_CONTROL_REQUEST::VALUE:
                        {
                          //RAN parameters from 8.4.4.1
                          if (!payload["MESSAGE"].contains ("Target Primary Cell ID"))
                            {
                              //todo: send RIC_CONTROL_FAILURE
                              return;
                            }
                          // UE wants to switch to a different cell
                          uint16_t ueToHandover = indicationHeader.contents.format_2.RNTI;
                          uint16_t requestedTargetCell = payload["MESSAGE"]["Target Primary Cell ID"];

                          // Measure time spent on xApp
                          auto startTimeXapp = std::chrono::high_resolution_clock::now();

                          // Set target cell to the requested by default
                          uint16_t targetCell = requestedTargetCell;
                          std::function<void(Json&)> handoverHandler = GetEndpointCallback("/Action/HO");
                          if (handoverHandler)
                            {
                              Json temp;
                              temp["RNTI"] = ueToHandover;
                              temp["Target Primary Cell ID"] = requestedTargetCell;
                              handoverHandler(temp);
                              targetCell = temp["Target Primary Cell ID"];
                            }
                          // Measure time spent on xApp
                          auto endTimeXapp = std::chrono::high_resolution_clock::now();
                          uint64_t nsDelayXapp = std::chrono::duration_cast<std::chrono::nanoseconds>(endTimeXapp - startTimeXapp).count();

                          // Send CONNECTED_MODE_MOBILITY_CONTROL::HANDOVER_CONTROL
                          E2SM_RC_RIC_CONTROL_HEADER hdr;
                          hdr.format = ns3::RC_CONTROL_HEADER_FORMAT_1;
                          hdr.contents.format_1.RNTI = rnti;
                          hdr.contents.format_1.RICControlStyleType = RIC_CONTROL_SERVICE_STYLES::CONNECTED_MODE_MOBILITY_CONTROL::VALUE;
                          hdr.contents.format_1.ControlActionID = RIC_CONTROL_SERVICE_STYLES::CONNECTED_MODE_MOBILITY_CONTROL::HANDOVER_CONTROL::VALUE;
                          hdr.contents.format_1.RicDecision = targetCell != std::numeric_limits<uint16_t>::max() ? RC_ACCEPT : RC_REJECT;
                          Json json_hdr;
                          to_json (json_hdr, hdr);

                          Json HANDOVER_CONTROL_MSG;
                          HANDOVER_CONTROL_MSG["DEST_ENDPOINT"] = src_endpoint;
                          HANDOVER_CONTROL_MSG["PAYLOAD"]["TYPE"] = RIC_CONTROL_REQUEST;
                          HANDOVER_CONTROL_MSG["PAYLOAD"]["SERVICE_MODEL"] = E2SM_RC;
                          HANDOVER_CONTROL_MSG["PAYLOAD"]["HEADER"] = json_hdr;
                          HANDOVER_CONTROL_MSG["PAYLOAD"]["MESSAGE"]["Target Primary Cell ID"] = targetCell;

                          // Send indication with control request with delay to account for the xApp processing time
                          Simulator::Schedule(NanoSeconds(nsDelayXapp), &E2AP::SendPayload, this, HANDOVER_CONTROL_MSG);
                        }
                      break;
                      case RIC_INSERT_SERVICE_STYLES::CONNECTED_MODE_MOBILITY_CONTROL_REQUEST::CONDITIONAL_HANDOVER_CONTROL_REQUEST::VALUE:
                        {

                        }
                      break;
                      case RIC_INSERT_SERVICE_STYLES::CONNECTED_MODE_MOBILITY_CONTROL_REQUEST::DUAL_ACTIVE_PROTOCOL_STACK_HANDOVER_CONTROL_REQUEST::VALUE:
                        {

                        }
                      break;
                      default:
                        NS_ABORT_MSG("Unknown Radio Resource Allocation Control Request Indication ID");
                    }
                }
              break;
              case RIC_INSERT_SERVICE_STYLES::RADIO_ACCESS_CONTROL_REQUEST::VALUE:
                {
                  switch (indicationHeader.contents.format_2.InsertIndicationID)
                    {
                      case RIC_INSERT_SERVICE_STYLES::RADIO_ACCESS_CONTROL_REQUEST::UE_ADMISSION_CONTROL_REQUEST::VALUE:
                        {

                        }
                      break;
                      case RIC_INSERT_SERVICE_STYLES::RADIO_ACCESS_CONTROL_REQUEST::RACH_BACKOFF_CONTROL_REQUEST::VALUE:
                        {

                        }
                      break;
                      case RIC_INSERT_SERVICE_STYLES::RADIO_ACCESS_CONTROL_REQUEST::ACCESS_BARRING_CONTROL_REQUEST::VALUE:
                        {

                        }
                      break;
                      case RIC_INSERT_SERVICE_STYLES::RADIO_ACCESS_CONTROL_REQUEST::RRC_CONNECTION_RELEASE::VALUE:
                        {

                        }
                      break;
                      case RIC_INSERT_SERVICE_STYLES::RADIO_ACCESS_CONTROL_REQUEST::RRC_CONNECTION_REJECT::VALUE:
                        {

                        }
                      break;
                      default:
                        NS_ABORT_MSG("Unknown Radio Resource Allocation Control Request Indication ID");
                    }
                }
              break;
              case RIC_INSERT_SERVICE_STYLES::DUAL_CONNECTIVITY_CONTROL_REQUEST::VALUE:
                {
                  switch (indicationHeader.contents.format_2.InsertIndicationID)
                    {
                      case RIC_INSERT_SERVICE_STYLES::DUAL_CONNECTIVITY_CONTROL_REQUEST::DC_SECONDARY_NODE_ADDITION_CONTROL_REQUEST::VALUE:
                        {

                        }
                      break;
                      case RIC_INSERT_SERVICE_STYLES::DUAL_CONNECTIVITY_CONTROL_REQUEST::DC_SECONDARY_NODE_MODIFICATION_AND_RELEASE_CONTROL_REQUEST::VALUE:
                        {

                        }
                      break;
                      case RIC_INSERT_SERVICE_STYLES::DUAL_CONNECTIVITY_CONTROL_REQUEST::DC_PSCELL_CHANGE_CONTROL_REQUEST::VALUE:
                        {

                        }
                      break;
                      case RIC_INSERT_SERVICE_STYLES::DUAL_CONNECTIVITY_CONTROL_REQUEST::DC_SECONDARY_NODE_CHANGE_CONTROL_REQUEST::VALUE:
                        {

                        }
                      break;
                      case RIC_INSERT_SERVICE_STYLES::DUAL_CONNECTIVITY_CONTROL_REQUEST::DC_DRB_TERMINATION_CONTROL_REQUEST::VALUE:
                        {

                        }
                      break;
                      default:
                        NS_ABORT_MSG("Unknown Radio Resource Allocation Control Request Indication ID");
                    }
                }
              break;
              case RIC_INSERT_SERVICE_STYLES::CARRIER_AGGREGATION_CONTROL_REQUEST::VALUE:
                {
                  switch (indicationHeader.contents.format_2.InsertIndicationID)
                    {
                      case RIC_INSERT_SERVICE_STYLES::CARRIER_AGGREGATION_CONTROL_REQUEST::CA_SECONDARY_CELL_ADDITION_CONTROL_REQUEST::VALUE:
                        {

                        }
                      break;
                      case RIC_INSERT_SERVICE_STYLES::CARRIER_AGGREGATION_CONTROL_REQUEST::CA_SECONDARY_CELL_MODIFICATION_AND_RELEASE_CONTROL_REQUEST::VALUE:
                        {

                        }
                      break;
                      default:
                        NS_ABORT_MSG("Unknown Radio Resource Allocation Control Request Indication ID");
                    }
                }
              break;
              case RIC_INSERT_SERVICE_STYLES::IDLE_MODE_MOBILITY_CONTROL_REQUEST::VALUE:
                {
                  switch (indicationHeader.contents.format_2.InsertIndicationID)
                    {
                      case RIC_INSERT_SERVICE_STYLES::IDLE_MODE_MOBILITY_CONTROL_REQUEST::CELL_RESELECTION_PRIORITY_REQUEST::VALUE:
                        {

                        }
                      break;
                      default:
                        NS_ABORT_MSG("Unknown Radio Resource Allocation Control Request Indication ID");
                    }
                }
              break;
              default:
                NS_ABORT_MSG("Unknown RIC Insert Style type");
            }
        }
      break;
      case RIC_INDICATION_HEADER_FORMAT_3:
        {
          //todo: INSERT Multiple Actions Control Request
        }
      break;
      default:
        NS_ABORT_MSG("Unknown RIC Indication Header Format");
    }
}

void
E2AP::HandleE2SmRcControlRequest (std::string& src_endpoint, std::string& dest_endpoint, Json& payload)
{
  NS_LOG_FUNCTION(this);

  E2SM_RC_RIC_CONTROL_HEADER controlHeader;
  NS_ASSERT(payload.contains ("HEADER"));
  from_json (payload["HEADER"], controlHeader);

  switch (controlHeader.format)
    {
      case RC_CONTROL_HEADER_FORMAT_1:
        switch (controlHeader.contents.format_1.RICControlStyleType)
          {
            case RIC_CONTROL_SERVICE_STYLES::RADIO_BEARER_CONTROL::VALUE:
              break;
            case RIC_CONTROL_SERVICE_STYLES::RADIO_RESOURCE_ALLOCATION_CONTROL::VALUE:
              break;
            case RIC_CONTROL_SERVICE_STYLES::CONNECTED_MODE_MOBILITY_CONTROL::VALUE:
              switch (controlHeader.contents.format_1.ControlActionID)
                {
                  case RIC_CONTROL_SERVICE_STYLES::CONNECTED_MODE_MOBILITY_CONTROL::HANDOVER_CONTROL::VALUE:
                    {
                      auto handoverRequestIt = m_pendingRequestsPerRnti.find ("HO");
                      if (handoverRequestIt == m_pendingRequestsPerRnti.end ())
                        {
                          m_pendingRequestsPerRnti.emplace ("HO", std::map<uint16_t, Json>{});
                          handoverRequestIt = m_pendingRequestsPerRnti.find ("HO");
                        }
                      auto UeRntiIt = handoverRequestIt->second.find (controlHeader.contents.format_1.RNTI);
                      if (UeRntiIt == handoverRequestIt->second.end ())
                        {
                          //todo: send control failure: no pending handover
                        }
                      else
                        {
                          UeRntiIt->second = payload;
                        }
                    }
                    break;
                  case RIC_CONTROL_SERVICE_STYLES::CONNECTED_MODE_MOBILITY_CONTROL::CONDITIONAL_HANDOVER_CONTROL::VALUE:
                  case RIC_CONTROL_SERVICE_STYLES::CONNECTED_MODE_MOBILITY_CONTROL::DUAL_ACTIVE_PROTOCOL_STACK_HANDOVER_CONTROL::VALUE:
                  default:
                    NS_ASSERT("Unimplemented controls");
                    break;
                }
              break;
            case RIC_CONTROL_SERVICE_STYLES::RADIO_ACCESS_CONTROL::VALUE:
              break;
            case RIC_CONTROL_SERVICE_STYLES::DUAL_CONNECTIVITY_CONTROL::VALUE:
              break;
            case RIC_CONTROL_SERVICE_STYLES::CARRIER_AGGREGATION_CONTROL::VALUE:
              break;
            case RIC_CONTROL_SERVICE_STYLES::IDLE_MODE_MOBILITY_CONTROL::VALUE:
              break;
            case RIC_CONTROL_SERVICE_STYLES::UE_INFORMATION_AND_ASSIGNMENT::VALUE:
              break;
            case RIC_CONTROL_SERVICE_STYLES::MEASUREMENT_REPORTING_CONFIGURATION_CONTROL::VALUE:
              break;
            case RIC_CONTROL_SERVICE_STYLES::MULTIPLE_ACTIONS_CONTROL::VALUE:
              break;
            default:
              NS_ASSERT("Unknown RIC Control Style");
              break;
          }
        break;
      case RC_CONTROL_HEADER_FORMAT_2:
      case RC_CONTROL_HEADER_FORMAT_3:
      default:
        NS_ASSERT("Unsupported RIC Control Request header format");
        break;
    }
}

std::optional<uint16_t>
E2AP::E2SmRcHandoverControl(uint16_t rnti, uint16_t cellId, LteEnbRrc& rrc)
{
    auto handoverRequestIt = m_pendingRequestsPerRnti.find ("HO");
    if (handoverRequestIt == m_pendingRequestsPerRnti.end ())
    {
        m_pendingRequestsPerRnti.emplace ("HO", std::map<uint16_t, Json>{});
        handoverRequestIt = m_pendingRequestsPerRnti.find ("HO");
    }
    auto UeRntiIt = handoverRequestIt->second.find (rnti);
    if (UeRntiIt == handoverRequestIt->second.end ())
    {
        // In case there is no pending request, we need to send a control indication,
        // then wait for a response
        E2SM_RC_RIC_INDICATION_HEADER hdr;
        hdr.format = ns3::RIC_INDICATION_HEADER_FORMAT_2;
        hdr.contents.format_2.RNTI = rnti;
        hdr.contents.format_2.RICInsertStyleType = RIC_INSERT_SERVICE_STYLES::CONNECTED_MODE_MOBILITY_CONTROL_REQUEST::VALUE;
        hdr.contents.format_2.InsertIndicationID = RIC_INSERT_SERVICE_STYLES::CONNECTED_MODE_MOBILITY_CONTROL_REQUEST::HANDOVER_CONTROL_REQUEST::VALUE;
        Json json_hdr;
        to_json (json_hdr, hdr);

        Json HANDOVER_CONTROL_REQUEST_MSG;
        HANDOVER_CONTROL_REQUEST_MSG["DEST_ENDPOINT"] = "/E2Node/0";
        HANDOVER_CONTROL_REQUEST_MSG["PAYLOAD"]["TYPE"] = RIC_INDICATION;
        HANDOVER_CONTROL_REQUEST_MSG["PAYLOAD"]["SERVICE_MODEL"] = E2SM_RC;
        HANDOVER_CONTROL_REQUEST_MSG["PAYLOAD"]["HEADER"] = json_hdr;
        HANDOVER_CONTROL_REQUEST_MSG["PAYLOAD"]["MESSAGE"]["Target Primary Cell ID"] = cellId;//starts counting from 1

        // Create a pending request entry for the current rnti
        handoverRequestIt->second.emplace (rnti, Json{});

        // Send indication with control request
        SendPayload(HANDOVER_CONTROL_REQUEST_MSG);

        // Record start time for handover control request
        Ptr<UeManager> ueManager = rrc.GetUeManager(rnti);

        if(rrc.HasUeManager(rnti))
        {
            Ptr<UeManager> ueManager = rrc.GetUeManager(rnti);
            rrc.m_handoverTriggeredTrace(ueManager->GetImsi(),
                                     rrc.ComponentCarrierToCellId(ueManager->GetComponentCarrierId()),
                                     rnti,
                                     cellId);
        }
        else
        {
            rrc.m_handoverTriggeredTrace(std::numeric_limits<uint64_t>::max(),
                                     rrc.GetFirstCellId().value(),
                                     rnti,
                                     cellId);
        }

        // Skip the end of this function
        return {};
    }

    if (!UeRntiIt->second.contains("HEADER"))
    {
        return {};
    }

    // Retrieve RIC Control Request message payload
    Json ricControlRequest = UeRntiIt->second;

    // Remove pending message entry
    handoverRequestIt->second.erase(UeRntiIt->first);

    E2SM_RC_RIC_CONTROL_HEADER controlHeader;
    NS_ASSERT(ricControlRequest.contains ("HEADER"));
    from_json (ricControlRequest["HEADER"], controlHeader);

    switch (controlHeader.format)
    {
    case RC_CONTROL_HEADER_FORMAT_1:
        if (controlHeader.contents.format_1.RicDecision == RC_REJECT)
        {
            NS_LOG_FUNCTION ("RIC Rejected Handover Request from UE " + std::to_string(rnti) + " to Cell " + std::to_string(cellId));
            if(rrc.HasUeManager(rnti))
            {
                Ptr<UeManager> ueManager = rrc.GetUeManager(rnti);
                // try to find the current cell ID based on the UeManager
                rrc.m_handoverCancelledTrace(ueManager->GetImsi(),
                                         rrc.ComponentCarrierToCellId(ueManager->GetComponentCarrierId()),
                                         rnti,
                                         cellId);
            }
            else
            {
                rrc.m_handoverCancelledTrace(std::numeric_limits<uint64_t>::max(),
                                         rrc.GetFirstCellId().value(),
                                         rnti,
                                         cellId);
            }
            return std::numeric_limits<uint16_t>::max();
        }
        if (controlHeader.contents.format_1.RICControlStyleType != RIC_CONTROL_SERVICE_STYLES::CONNECTED_MODE_MOBILITY_CONTROL::VALUE)
        {
            NS_ASSERT("Incorrect RIC Control Style");
            //todo: control failure
        }
        if (controlHeader.contents.format_1.ControlActionID != RIC_CONTROL_SERVICE_STYLES::CONNECTED_MODE_MOBILITY_CONTROL::HANDOVER_CONTROL::VALUE)
        {
            NS_ASSERT("Incorrect RIC Control Action ID");
            //todo: control failure
        }
        break;
    case RC_CONTROL_HEADER_FORMAT_2:
        if (controlHeader.contents.format_2.RicDecision == RC_REJECT)
        {
            NS_LOG_FUNCTION ("RIC Rejected Handover Request from UE " + std::to_string(rnti) + " to Cell " + std::to_string(cellId));
        }
        // connect to the current CellId
        break;
    default:
        NS_ASSERT("Unknown RC Control Header format");
    }

    // todo: implement the proper way
    // If we succeeded, check if the target cell still is the same
    //E2SM_RC_RIC_CONTROL_MESSAGE controlMessage;
    //NS_ASSERT(UeRntiIt->second["MESSAGE"]);
    //from_json (UeRntiIt->second["MESSAGE"], controlMessage);
    //if (controlMessage.format != E2SM_RC_RIC_CONTROL_MESSAGE_FORMAT_1)
    //  {
    //    NS_ASSERT("Incorrect Control Message format for Handover");
    //  }
    //else
    //  {
    //    cellId = controlMessage.contents.format_1.sequence_of_ran_parameters.find(RAN_PARAMETER_ID)
    //  }
    //
    // temporary hack
    cellId = ricControlRequest["MESSAGE"]["Target Primary Cell ID"];
    return cellId;
}
