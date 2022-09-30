//
// Created by gabriel on 29/09/22.
//

#include "xApp.h"

using namespace ns3;

enum REPORT_TYPE{
  E2Node_AllocatedChannels = 1,
  E2Node_ChannelUtilization,
  E2Node_ConnectedUsers,
  E2Node_NearbyUsers
};

void
xApp::HandlePayload(std::string endpoint, Json payload)
{
  REPORT_TYPE type = payload["REPORT_TYPE"];
  // Handle all payload types with metrics available for the xApps to use
  switch(type)
    {
      case E2Node_AllocatedChannels:
        {

        }
        break;
      case E2Node_ChannelUtilization:
        {

        }
        break;
      case E2Node_ConnectedUsers:
        {

        }
        break;
      case E2Node_NearbyUsers:
        {

        }
        break;
    default:
      std::cout << this->m_endpointRoot << " failed to handle payload with REPORT_TYPE=" << payload["REPORT_TYPE"] << std::endl;
    }
}