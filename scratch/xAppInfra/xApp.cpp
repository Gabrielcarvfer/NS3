//
// Created by gabriel on 29/09/22.
//

#include "xApp.h"

using namespace ns3;

void
xApp::HandlePayload(std::string endpoint, Json payload);
{
  // Handle all payload types with metrics available for the xApps to use
  switch(payload["REPORT_TYPE"])
    {
      case "E2Node_AllocatedChannels":
        {

        }
        break;
      case "E2Node_ChannelUtilization":
        {

        }
        break;
      case "E2Node_ConnectedUsers":
        {

        }
        break;
      case "E2Node_NearbyUsers":
        {

        }
        break;
    default:
      std::cout << this->m_endpointRoot << " failed to handle payload with REPORT_TYPE=" << payload["REPORT_TYPE"] << std::endl;
    }
}