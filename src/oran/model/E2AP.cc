//
// Created by gabriel on 29/09/22.
//

#include "E2AP.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("E2AP");

enum ORAN_MESSAGE_TYPES
    {
        //RIC initiated
        RIC_SUBSCRIPTION_REQUEST,
        RIC_SUBSCRIPTION_DELETE_REQUEST,
        RIC_CONTROL_REQUEST,
        E2_SETUP_RESPONSE,
        E2_SETUP_FAILURE,
        RIC_SERVICE_QUERY,
        RIC_SERVICE_UPDATE_ACKNOWLEDGE,
        RIC_SERVICE_UPDATE_FAILURE,
        E2_NODE_CONFIGURATION_UPDATE_ACKNOWLEDGE,
        E2_NODE_CONFIGURATION_UPDATE_FAILURE,
        E2_CONNECTION_UPDATE_ACKNOWLEDGE,
        E2_CONNECTION_UPDATE_FAILURE,
        //E2 initiated
        RIC_SUBSCRIPTION_RESPONSE,
        RIC_SUBSCRIPTION_FAILURE,
        RIC_SUBSCRIPTION_DELETE_RESPONSE,
        RIC_SUBSCRIPTION_DELETE_FAILURE,
        RIC_SUBSCRIPTION_DELETE_REQUIRED,
        RIC_INDICATION,
        RIC_CONTROL_ACKNOWLEDGE,
        RIC_CONTROL_FAILURE,
        E2_SETUP_REQUEST,
        RIC_SERVICE_UPDATE,
        E2_NODE_CONFIGURATION_UPDATE,
        E2_CONNECTION_UPDATE,
        //RIC and E2 initiated
        RESET_REQUEST,
        RESET_RESPONSE,
        ERROR_INDICATION,
        E2_REMOVAL_REQUEST,
        E2_REMOVAL_RESPONSE,
        E2_REMOVAL_FAILURE,
    };

std::map<ORAN_MESSAGE_TYPES, std::string> oran_msg_str
    {
        {RIC_SUBSCRIPTION_REQUEST,                  "RIC_SUBSCRIPTION_REQUEST"},
        {RIC_SUBSCRIPTION_DELETE_REQUEST,           "RIC_SUBSCRIPTION_DELETE_REQUEST"},
        {RIC_CONTROL_REQUEST,                       "RIC_CONTROL_REQUEST"},
        {E2_SETUP_RESPONSE,                         "E2_SETUP_RESPONSE"},
        {E2_SETUP_FAILURE,                          "E2_SETUP_FAILURE"},
        {RIC_SERVICE_QUERY,                         "RIC_SERVICE_QUERY"},
        {RIC_SERVICE_UPDATE_ACKNOWLEDGE,            "RIC_SERVICE_UPDATE_ACKNOWLEDGE"},
        {RIC_SERVICE_UPDATE_FAILURE,                "RIC_SERVICE_UPDATE_FAILURE"},
        {E2_NODE_CONFIGURATION_UPDATE_ACKNOWLEDGE,  "E2_NODE_CONFIGURATION_UPDATE_ACKNOWLEDGE"},
        {E2_NODE_CONFIGURATION_UPDATE_FAILURE,      "E2_NODE_CONFIGURATION_UPDATE_FAILURE"},
        {E2_CONNECTION_UPDATE_ACKNOWLEDGE,          "E2_CONNECTION_UPDATE_ACKNOWLEDGE"},
        {E2_CONNECTION_UPDATE_FAILURE,              "E2_CONNECTION_UPDATE_FAILURE"},
        {RIC_SUBSCRIPTION_RESPONSE,                 "RIC_SUBSCRIPTION_RESPONSE"},
        {RIC_SUBSCRIPTION_FAILURE,                  "RIC_SUBSCRIPTION_FAILURE"},
        {RIC_SUBSCRIPTION_DELETE_RESPONSE,          "RIC_SUBSCRIPTION_DELETE_RESPONSE"},
        {RIC_SUBSCRIPTION_DELETE_FAILURE,           "RIC_SUBSCRIPTION_DELETE_FAILURE"},
        {RIC_SUBSCRIPTION_DELETE_REQUIRED,          "RIC_SUBSCRIPTION_DELETE_REQUIRED"},
        {RIC_INDICATION,                            "RIC_INDICATION"},
        {RIC_CONTROL_ACKNOWLEDGE,                   "RIC_CONTROL_ACKNOWLEDGE"},
        {RIC_CONTROL_FAILURE,                       "RIC_CONTROL_FAILURE"},
        {E2_SETUP_REQUEST,                          "E2_SETUP_REQUEST"},
        {RIC_SERVICE_UPDATE,                        "RIC_SERVICE_UPDATE"},
        {E2_NODE_CONFIGURATION_UPDATE,              "E2_NODE_CONFIGURATION_UPDATE"},
        {E2_CONNECTION_UPDATE,                      "E2_CONNECTION_UPDATE"},
        {RESET_REQUEST,                             "RESET_REQUEST"},
        {RESET_RESPONSE,                            "RESET_RESPONSE"},
        {ERROR_INDICATION,                          "ERROR_INDICATION"},
        {E2_REMOVAL_REQUEST,                        "E2_REMOVAL_REQUEST"},
        {E2_REMOVAL_RESPONSE,                       "E2_REMOVAL_RESPONSE"},
        {E2_REMOVAL_FAILURE,                        "E2_REMOVAL_FAILURE"},
    };

void
E2AP::HandlePayload(std::string endpoint, Json payload)
{
  NS_LOG_FUNCTION (this);

  NS_ASSERT_MSG (payload.contains("TYPE"), "Payload addressed to " + endpoint + "does not contain a message type.");
  ORAN_MESSAGE_TYPES msg_type = payload.find("TYPE").value();

  // Check if we are not receiving invalid payloads
  if(m_endpointRoot == "/E2Node/0")
    {
      // E2T can't receive messages that should have originated on the RIC (himself)
      if(msg_type < RIC_SUBSCRIPTION_RESPONSE )
        {
           std::stringstream ss;
           ss << "E2T received message addressed to himself. Type=" << oran_msg_str.at(msg_type);
           NS_ASSERT(ss.str().c_str());
        }
    }
  else
    {
      // E2 nodes can't receive messages that should have originated on E2 Nodes (himselves)
      if(RIC_SUBSCRIPTION_RESPONSE <= msg_type && msg_type <= E2_NODE_CONFIGURATION_UPDATE )
        {
          std::stringstream ss;
          ss << m_endpointRoot <<" received message addressed to himself. Type=" << oran_msg_str[msg_type];
          NS_ASSERT(ss.str().c_str());
        }
    }

  NS_LOG_FUNCTION("Handling payload " + to_string (payload));

  // Handle all O-RAN messages
  switch(msg_type)
    {
      // O-RAN WG3 E2AP v2.02 8.2.1.2
      // RIC initiated
      case RIC_SUBSCRIPTION_REQUEST:
        {
        }
        break;
      // O-RAN WG3 E2AP v2.02 8.2.1.2
      // E2 initiated
      case RIC_SUBSCRIPTION_RESPONSE:
        {
        }
        break;
      // O-RAN WG3 E2AP v2.02 8.2.1.3
      // E2 initiated
      case RIC_SUBSCRIPTION_FAILURE:
        {
        }
        break;
      // O-RAN WG3 E2AP v2.02 8.2.2.2
      // RIC initiated
      case RIC_SUBSCRIPTION_DELETE_REQUEST:
        {
        }
        break;
      // O-RAN WG3 E2AP v2.02 8.2.2.2
      // E2 initiated
      case RIC_SUBSCRIPTION_DELETE_RESPONSE:
        {
        }
        break;
      // O-RAN WG3 E2AP v2.02 8.2.2.3
      // E2 initiated
      case RIC_SUBSCRIPTION_DELETE_FAILURE:
        {
        }
        break;
      // O-RAN WG3 E2AP v2.02 8.2.2A.2
      // E2 initiated
      case RIC_SUBSCRIPTION_DELETE_REQUIRED:
        {
        }
        break;
      // O-RAN WG3 E2AP v2.02 8.2.3.2
      // E2 initiated
      case RIC_INDICATION:
        {
        }
        break;
      // O-RAN WG3 E2AP v2.02 8.2.4.2
      // RIC initiated
      case RIC_CONTROL_REQUEST:
        {
        }
        break;
      // O-RAN WG3 E2AP v2.02 8.2.4.2
      // E2 initiated
      case RIC_CONTROL_ACKNOWLEDGE:
        {
        }
        break;
      // O-RAN WG3 E2AP v2.02 8.2.4.3
      // E2 initiated
      case RIC_CONTROL_FAILURE:
        {
        }
        break;
      // O-RAN WG3 E2AP v2.02 8.3.1.2
      // E2 initiated
      case E2_SETUP_REQUEST:
        {

        }
        break;
      // O-RAN WG3 E2AP v2.02 8.3.1.2
      // RIC initiated
      case E2_SETUP_RESPONSE:
        {

        }
        break;
      // O-RAN WG3 E2AP v2.02 8.3.1.3
      // RIC initiated
      case E2_SETUP_FAILURE:
        {

        }
        break;
      // O-RAN WG3 E2AP v2.02 8.3.2.2
      // RIC or E2 initiated
      case RESET_REQUEST:
        {

        }
        break;
      // O-RAN WG3 E2AP v2.02 8.3.2.3
      // RIC or E2 initiated
      case RESET_RESPONSE:
        {

        }
        break;
      // O-RAN WG3 E2AP v2.02 8.3.3.2
      // RIC or E2 initiated
      case ERROR_INDICATION:
        {

        }
        break;
      // O-RAN WG3 E2AP v2.02 8.3.4.2
      // RIC initiated
      case RIC_SERVICE_QUERY:
        {

        }
        break;
      // O-RAN WG3 E2AP v2.02 8.3.4.2
      // E2 initiated
      case RIC_SERVICE_UPDATE:
        {

        }
        break;
      // O-RAN WG3 E2AP v2.02 8.3.4.2
      // RIC initiated
      case RIC_SERVICE_UPDATE_ACKNOWLEDGE:
        {

        }
        break;
      // O-RAN WG3 E2AP v2.02 8.3.4.3
      // RIC initiated
        case RIC_SERVICE_UPDATE_FAILURE:
        {

        }
        break;
      // O-RAN WG3 E2AP v2.02 8.3.5.2
      // E2 initiated
      case E2_NODE_CONFIGURATION_UPDATE:
        {
          bool successful = true;
          bool temp = true;
          std::vector<std::string> failed_addition_list {};
          std::vector<std::vector<std::string>> failed_update_list {};
          std::vector<std::string> failed_removal_list {};

          if(payload.contains("COMPONENT_CONFIGURATION_ADDITION_LIST"))
            {
              for(std::string new_endpoint: payload.find("COMPONENT_CONFIGURATION_ADDITION_LIST").value())
                {
                  temp = true & sRegisterEndpoint (endpoint, new_endpoint);
                  if (!temp)
                    {
                      failed_addition_list.push_back(new_endpoint);
                    }
                  successful &= temp;
                }
            }
          if(payload.contains("COMPONENT_CONFIGURATION_UPDATE_LIST"))
            {
              for(std::vector<std::string> endpoints: payload.find("COMPONENT_CONFIGURATION_UPDATE_LIST").value())
                {
                  temp = true & sUpdateEndpoint (endpoint, endpoints[0], endpoints[1]);
                  if (!temp)
                    {
                      failed_update_list.push_back(endpoints);
                    }
                  successful &= temp;
                }
            }
          if(payload.contains("COMPONENT_CONFIGURATION_REMOVAL_LIST"))
            {
              for(std::string old_endpoint: payload.find("COMPONENT_CONFIGURATION_REMOVAL_LIST").value())
                {
                  temp = true & sRemoveEndpoint (endpoint, old_endpoint);
                  if (!temp)
                    {
                      failed_removal_list.push_back({endpoint});
                    }
                  successful &= temp;
                }
            }
          if(successful)
            {
              Json E2_NODE_CONFIGURATION_UPDATE_ACKNOWLEDGE_MESSAGE;
              E2_NODE_CONFIGURATION_UPDATE_ACKNOWLEDGE_MESSAGE["ENDPOINT"] = endpoint;
              E2_NODE_CONFIGURATION_UPDATE_ACKNOWLEDGE_MESSAGE["PAYLOAD"]["TYPE"] = E2_NODE_CONFIGURATION_UPDATE_ACKNOWLEDGE;
              if(payload.contains("COMPONENT_CONFIGURATION_ADDITION_LIST"))
                {
                  E2_NODE_CONFIGURATION_UPDATE_ACKNOWLEDGE_MESSAGE["PAYLOAD"]["COMPONENT_CONFIGURATION_ADDITION_LIST"] = payload.find("COMPONENT_CONFIGURATION_ADDITION_LIST").value();
                }
              if(payload.contains("COMPONENT_CONFIGURATION_UPDATE_LIST"))
                {
                  E2_NODE_CONFIGURATION_UPDATE_ACKNOWLEDGE_MESSAGE["PAYLOAD"]["COMPONENT_CONFIGURATION_UPDATE_LIST"] = payload.find("COMPONENT_CONFIGURATION_UPDATE_LIST").value();
                }
              if(payload.contains("COMPONENT_CONFIGURATION_REMOVAL_LIST"))
                {
                  E2_NODE_CONFIGURATION_UPDATE_ACKNOWLEDGE_MESSAGE["PAYLOAD"]["COMPONENT_CONFIGURATION_REMOVAL_LIST"] = payload.find("COMPONENT_CONFIGURATION_REMOVAL_LIST").value();
                }
              SendPayload (E2_NODE_CONFIGURATION_UPDATE_ACKNOWLEDGE_MESSAGE);
            }
          else
            {
              Json E2_NODE_CONFIGURATION_UPDATE_FAILURE_MESSAGE;
              E2_NODE_CONFIGURATION_UPDATE_FAILURE_MESSAGE["ENDPOINT"] = endpoint;
              E2_NODE_CONFIGURATION_UPDATE_FAILURE_MESSAGE["PAYLOAD"]["TYPE"] = E2_NODE_CONFIGURATION_UPDATE_FAILURE;
              if(payload.contains("COMPONENT_CONFIGURATION_ADDITION_LIST"))
                {
                  E2_NODE_CONFIGURATION_UPDATE_FAILURE_MESSAGE["PAYLOAD"]["COMPONENT_CONFIGURATION_ADDITION_LIST"] = failed_addition_list;
                }
              if(payload.contains("COMPONENT_CONFIGURATION_UPDATE_LIST"))
                {
                  E2_NODE_CONFIGURATION_UPDATE_FAILURE_MESSAGE["PAYLOAD"]["COMPONENT_CONFIGURATION_UPDATE_LIST"] = failed_update_list;
                }
              if(payload.contains("COMPONENT_CONFIGURATION_REMOVAL_LIST"))
                {
                  E2_NODE_CONFIGURATION_UPDATE_FAILURE_MESSAGE["PAYLOAD"]["COMPONENT_CONFIGURATION_REMOVAL_LIST"] = failed_removal_list;
                }
              SendPayload (E2_NODE_CONFIGURATION_UPDATE_FAILURE_MESSAGE);
            }
        }
        break;
      // O-RAN WG3 E2AP v2.02 8.3.5.2
      // RIC initiated
      case E2_NODE_CONFIGURATION_UPDATE_ACKNOWLEDGE:
        {
          //todo: handle successful case
          NS_LOG_FUNCTION ("Received E2_NODE_CONFIGURATION_UPDATE_ACKNOWLEDGE from RIC: " + to_string(payload));
        }
        break;
      // O-RAN WG3 E2AP v2.02 8.3.5.3
      // RIC initiated
      case E2_NODE_CONFIGURATION_UPDATE_FAILURE:
        {
          //todo: handle failure case
          NS_LOG_FUNCTION ("Received E2_NODE_CONFIGURATION_UPDATE_FAILURE from RIC: " + to_string(payload));
        }
        break;
      // O-RAN WG3 E2AP v2.02 8.3.6.2
      // RIC initiated
      case E2_CONNECTION_UPDATE:
        {

        }
        break;
      // O-RAN WG3 E2AP v2.02 8.3.6.2
      // E2 initiated
      case E2_CONNECTION_UPDATE_ACKNOWLEDGE:
        {

        }
        break;
      // O-RAN WG3 E2AP v2.02 8.3.6.3
      // E2 initiated
      case E2_CONNECTION_UPDATE_FAILURE:
        {

        }
        break;
      // O-RAN WG3 E2AP v2.02 8.3.7.2
      // RIC or E2 initiated
      case E2_REMOVAL_REQUEST:
        {

        }
        break;
      // O-RAN WG3 E2AP v2.02 8.3.7.2
      // RIC or E2 initiated
      case E2_REMOVAL_RESPONSE:
        {

        }
        break;
      // O-RAN WG3 E2AP v2.02 8.3.7.3
      // RIC or E2 initiated
      case E2_REMOVAL_FAILURE:
        {

        }
        break;
    default:
      std::cout << this->m_endpointRoot << " failed to handle payload with RPC=" << payload["RPC"] << std::endl;
    }
}

void
E2AP::SendPayload (Json payload)
{
  if (m_endpointRoot != "/E2Node/0")
    {
      NS_LOG_FUNCTION ("Sending the payload of type " + oran_msg_str.at(payload.at("PAYLOAD").at("TYPE")) + " to the RIC: " + to_string(payload));
      m_socket->SendTo (encodeJsonToPacket (payload), 0, m_node0Address);
    }
  else
    {
      NS_LOG_FUNCTION ("RIC handling the payload of type " + oran_msg_str.at(payload.at("PAYLOAD").at("TYPE")) + " locally: " + to_string(payload));
      HandlePayload (m_endpointRoot, payload.at ("PAYLOAD"));
    }
}

void
E2AP::RegisterEndpoint(std::string endpoint)
{
  NS_LOG_FUNCTION (this);
  Json E2_NODE_CONFIGURATION_UPDATE_MESSAGE;
  E2_NODE_CONFIGURATION_UPDATE_MESSAGE["ENDPOINT"] = m_endpointRoot;
  E2_NODE_CONFIGURATION_UPDATE_MESSAGE["PAYLOAD"]["TYPE"] = E2_NODE_CONFIGURATION_UPDATE;
  E2_NODE_CONFIGURATION_UPDATE_MESSAGE["PAYLOAD"]["COMPONENT_CONFIGURATION_ADDITION_LIST"] = std::vector<std::string>{endpoint};
  SendPayload (E2_NODE_CONFIGURATION_UPDATE_MESSAGE);
}

void
E2AP::UpdateEndpoint(std::string old_endpoint, std::string new_endpoint)
{
  NS_LOG_FUNCTION (this);
  Json E2_NODE_CONFIGURATION_UPDATE_MESSAGE;
  E2_NODE_CONFIGURATION_UPDATE_MESSAGE["ENDPOINT"] = m_endpointRoot;
  E2_NODE_CONFIGURATION_UPDATE_MESSAGE["PAYLOAD"]["TYPE"] = E2_NODE_CONFIGURATION_UPDATE;
  E2_NODE_CONFIGURATION_UPDATE_MESSAGE["PAYLOAD"]["COMPONENT_CONFIGURATION_UPDATE_LIST"] = std::vector<std::vector<std::string>>{{old_endpoint, new_endpoint}};
  SendPayload (E2_NODE_CONFIGURATION_UPDATE_MESSAGE);
}

void
E2AP::RemoveEndpoint(std::string endpoint)
{
  NS_LOG_FUNCTION (this);
  Json E2_NODE_CONFIGURATION_UPDATE_MESSAGE;
  E2_NODE_CONFIGURATION_UPDATE_MESSAGE["ENDPOINT"] = m_endpointRoot;
  E2_NODE_CONFIGURATION_UPDATE_MESSAGE["PAYLOAD"]["TYPE"] = E2_NODE_CONFIGURATION_UPDATE;
  E2_NODE_CONFIGURATION_UPDATE_MESSAGE["PAYLOAD"]["COMPONENT_CONFIGURATION_REMOVAL_LIST"] = std::vector<std::string>{endpoint};
  SendPayload (E2_NODE_CONFIGURATION_UPDATE_MESSAGE);
}

void
E2AP::SubscribeToEndpoint (std::string endpoint)
{
  NS_LOG_FUNCTION (m_endpointRoot + " subscribing to endpoint " + endpoint);
  Json RIC_SUBSCRIPTION_REQUEST_MESSAGE;
  RIC_SUBSCRIPTION_REQUEST_MESSAGE["ENDPOINT"] = m_endpointRoot;
  RIC_SUBSCRIPTION_REQUEST_MESSAGE["PAYLOAD"]["TYPE"] = RIC_SUBSCRIPTION_REQUEST;
  RIC_SUBSCRIPTION_REQUEST_MESSAGE["PAYLOAD"]["RIC Subscription Details"];
  RIC_SUBSCRIPTION_REQUEST_MESSAGE["PAYLOAD"]["RIC Subscription Details"]["RIC Event Trigger Definition"]; //todo
  RIC_SUBSCRIPTION_REQUEST_MESSAGE["PAYLOAD"]["RIC Subscription Details"]["Sequence of Actions"];//todo
  SendPayload (RIC_SUBSCRIPTION_REQUEST_MESSAGE);
  //sSubscribeToEndpoint (endpoint, this);
}

// O-RAN WG3 E2SM KPM v2.00.03 7.3.2
// Trigger timer: only for REPORT, not INSERT/POLICY
// ["periodic"] = KPM interval


// O-RAN WG3 E2SM RC v01.02 7.3.1
std::vector<std::tuple<enum RIC_EVENT_TRIGGER_DEFINITION_STYLES, std::string, std::pair<uint8_t, uint8_t>>>
    RIC_EVENT_TRIGGER_DEFINITION_SUPPORTED_RIC_SERVICE_STYLE
    {
    {MESSAGE_EVENT,"REPORT", {1,1}},
    {MESSAGE_EVENT, "POLICY", {1,7}},
    {CALL_PROCESS_BREAKPOINT,"REPORT", {2,2}},
    {CALL_PROCESS_BREAKPOINT,"INSERT", {1,7}},
    {CALL_PROCESS_BREAKPOINT,"POLICY", {1,8}},
    {E2_NODE_INFORMATION_CHANGE,"REPORT", {3,3}},
    {UE_INFORMATION_CHANGE,"REPORT", {4,4}},
    {ON_DEMAND,"REPORT", {5,5}},
};


// O-RAN WG3 E2SM KPM v2.00.03 7.4.1
// REPORT services
enum REPORT_KPM_SERVICES {
  E2_NODE_MEASUREMENT = 1,
  E2_NODE_MEASUREMENT_FOR_SINGLE_UE,
  E2_NODE_CONDITIONAL_MEASUREMENT_FOR_UES,
  E2_NODE_CONDITIONAL_MEASUREMENT_SET_FOR_UES,
  E2_NODE_MEASUREMENT_FOR_MULTIPLE_UES
};

// REPORTed measurements
// 5G https://www.etsi.org/deliver/etsi_TS/128500_128599/128552/16.10.00_60/ts_128552v161000p.pdf
// 4G https://www.etsi.org/deliver/etsi_TS/132400_132499/132425/14.01.00_60/ts_132425v140100p.pdf