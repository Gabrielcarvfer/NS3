//
// Created by Gabriel Ferreira (@gabrielcarvfer) on 27/10/22.
//

#include "E2SM-RC-indication-types.h"
#include "E2SM-RC-control-types.h"

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
          uint16_t eventTriggerConditionId = indicationHeader.contents.format_1.eventTriggerConditionID;
          std::cout << eventTriggerConditionId << std::endl;
        }
      break;
      case RIC_INDICATION_HEADER_FORMAT_2:
        {
          // INSERT services
          uint16_t rnti = indicationHeader.contents.format_2.RNTI;
          std::cout << rnti << std::endl;
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

                          // Set target cell
                          uint16_t targetCell = RicCheckAcceptHandover (ueToHandover, requestedTargetCell);

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

                          // Send indication with control request
                          SendPayload(HANDOVER_CONTROL_MSG);
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

uint16_t
E2AP::RicCheckAcceptHandover(uint16_t rnti, uint16_t cellId)
{
  // by default, accept all handover requests
  // overriding this method allows us to change the handover acceptance algorithm
  return cellId;
}