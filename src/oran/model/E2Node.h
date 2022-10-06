//
// Created by gabriel on 29/09/22.
//

#ifndef NS3_E2NODE_H
#define NS3_E2NODE_H

#include "PubSubInfra.h"

namespace ns3 {

class E2Node : public PubSubInfra
{
public:
  E2Node () : PubSubInfra ("E2Node"){};
  ~E2Node (){};
  void HandlePayload (std::string endpoint, Json payload);
  void RegisterEndpoint(std::string endpoint);
  void UpdateEndpoint(std::string old_endpoint, std::string new_endpoint);
  void RemoveEndpoint(std::string endpoint);
  void SubscribeToEndpoint (std::string endpoint);
private:
  void SendPayload(Json payload);
};

// O-RAN WG3 E2SM RC v01.02 7.3.1
enum RIC_EVENT_TRIGGER_DEFINITION_STYLES
{
  MESSAGE_EVENT = 1,
  CALL_PROCESS_BREAKPOINT,
  E2_NODE_INFORMATION_CHANGE,
  UE_INFORMATION_CHANGE,
  ON_DEMAND
};

}
#endif //NS3_E2NODE_H
