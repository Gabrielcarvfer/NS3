//
// Created by Gabriel Ferreira (@gabrielcarvfer) on 01/11/22.
//

#include "xApp_Handover.h"

NS_LOG_COMPONENT_DEFINE ("xApp_Handover");

using namespace ns3;

xApp_Handover::xApp_Handover ()
    : xApp ()
{
  RegisterEndpointCallback ("/Action/HO",
                            std::bind(&xApp_Handover::HandoverDecision,
                                      this,
                                      std::placeholders::_1)
                                      );
}
xApp_Handover::~xApp_Handover ()
{
  RemoveEndpointCallback("/Action/HO");
}

void
xApp_Handover::HandoverDecision (Json& payload)
{
  NS_LOG_FUNCTION (this);

  // Check if we are not receiving invalid payloads
  if (m_endpointRootToInstance.at(m_endpointRoot)->GetNode() != m_endpointRootToInstance.at("/E2Node/0")->GetNode())
    {
      NS_ABORT_MSG("Trying to run a xApp on a E2Node is a no-no");
    }
  // Read inputs from the json
  uint16_t rnti = payload["RNTI"];
  uint16_t targetCellId = payload["Target Primary Cell ID"];

  // Do the processing
  // todo: implement some fancy logic

  // Then write the outputs to the json
  payload["Target Primary Cell ID"] = targetCellId;
}