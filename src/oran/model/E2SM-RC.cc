//
// Created by Gabriel Ferreira (@gabrielcarvfer) on 27/10/22.
//

#include "E2SM-RC-indication-types.h"

void
E2AP::HandleE2SmRcIndicationPayload (std::string& src_endpoint, std::string& dest_endpoint, Json& payload)
{
  NS_LOG_FUNCTION(this);

  E2SM_RC_RIC_INDICATION_HEADER indicationHeader;
  NS_ASSERT(payload["MESSAGE"].contains ("HEADER"));
  from_json (payload["MESSAGE"]["HEADER"], indicationHeader);

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
                          if(!payload["MESSAGE"].contains("TargetPrimaryCellID"))
                            {
                              //todo: send RIC_CONTROL_FAILURE
                              return;
                            }
                          // UE wants to switch to a different cell
                          uint16_t ueToHandover = indicationHeader.contents.format_2.RNTI;
                          uint16_t targetCell = payload["MESSAGE"].contains("TargetPrimaryCellID");

                          // Set target cell
                          //Send CONNECTED_MODE_MOBILITY_CONTROL::HANDOVER_CONTROL

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