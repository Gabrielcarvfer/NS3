//
// Created by Gabriel Ferreira(@gabrielcarvfer) on 31/08/22.
//

#ifndef NS3_PUBSUBINFRA_H
#define NS3_PUBSUBINFRA_H

#include <cxxabi.h>
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <sstream>
#include <regex>
#include <iostream>
#include <typeinfo>
#include <iterator>
#include <map>
#include <utility>
#include <vector>
#include <functional>

#include "json.hpp"

#include <ns3/network-module.h>
#include <ns3/internet-module.h>
#include "ns3/assert.h"
#include "ns3/fatal-impl.h"

using Json = nlohmann::json;

namespace ns3 {

class PubSubInfra : public Application
{
public:
  PubSubInfra (std::string className)
  {
    std::stringstream ss;
    ss << "/" << className << "/";

    // Search in the instance count map
    auto endpointRootCountIt = m_instanceCountMap.find (ss.str ());
    if (endpointRootCountIt == m_instanceCountMap.end ())
      {
        m_instanceCountMap.emplace (ss.str (), 0);
        endpointRootCountIt = m_instanceCountMap.find (ss.str ());
      }

    // Set id of instance
    m_instanceId = endpointRootCountIt->second;

    // Increment class counter
    endpointRootCountIt->second++;

    // Set endpoint root
    ss << m_instanceId;
    m_endpointRoot = ss.str ();

    // Register instance in the class for later use
    m_endpointRootToInstance.emplace (std::make_pair (m_endpointRoot, this));

    // Tenta conectar (se não estiver associado a um Node, falhará)
    //Connect();
  }
  ~PubSubInfra (){};

  bool Connect ();
  void Send (Ptr<Packet> packet);
  void RegisterEndpoint (std::string endpoint);
  void SubscribeToEndpoint (std::string endpoint);
  void PublishToEndpointSubscribers (std::string endpoint, Json json);
  void ReceivePacket (Ptr<Socket> socket);
  void ReceiveJsonPayload (Json msg);
  // To be implemented by each custom xApp and E2Node
  virtual void HandlePayload (std::string endpoint, Json payload){};
  //private:
  Ptr<Socket> m_socket;
  std::string m_endpointRoot; // set during initialization
  uint64_t m_instanceId = 0; // set during initialization
  std::map<std::string, Ptr<Socket>> m_endpointToSocketMap;
  static Address m_node0Address; // set during the first connect
  static std::map<const std::string, uint64_t>
      m_instanceCountMap; // incremented during initialization
  static std::map<const std::string, const PubSubInfra *> m_endpointRootToInstance;
  static std::map<const std::string, std::vector<const PubSubInfra *>> m_endpointToSubscribers;
//static methods
  Ipv4Address getNodeAddress (unsigned device = 3);
  static Ptr<Packet> encodeJsonToPacket (Json json_contents);
  static Json decodePacketToJson (Ptr<Packet> packet);
  static std::string buildEndpoint(std::string rootEndpoint, std::string endpoint);
  static bool sRegisterEndpoint (std::string rootEndpoint, std::string endpoint);
  static bool sUpdateEndpoint (std::string rootEndpoint, std::string old_endpoint, std::string new_endpoint);
  static bool sRemoveEndpoint (std::string rootEndpoint, std::string endpoint);
  static void sSubscribeToEndpoint (std::string endpoint, PubSubInfra *subscriber);
  void sPublishToEndpointSubscribers (std::string publisherEndpoint, std::string endpoint,  std::string json_literal);
};
}//namespace ns3
#endif //NS3_PUBSUBINFRA_H
