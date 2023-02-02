//
// Created by Gabriel Ferreira(@gabrielcarvfer) on 31/08/22.
//

#ifndef NS3_PUBSUBINFRA_H
#define NS3_PUBSUBINFRA_H

#include "ns3/assert.h"
#include "ns3/fatal-impl.h"
#include "ns3/json.hpp"
#include <ns3/internet-module.h>
#include <ns3/network-module.h>

#include <cxxabi.h>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <regex>
#include <sstream>
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <typeinfo>
#include <utility>
#include <vector>

using Json = nlohmann::json;

namespace ns3
{

class PubSubInfra : public Application
{
  public:
    PubSubInfra(std::string className)
    {
        std::stringstream ss;
        ss << "/" << className << "/";

        // Search in the instance count map
        auto endpointRootCountIt = m_instanceCountMap.find(ss.str());
        if (endpointRootCountIt == m_instanceCountMap.end())
        {
            m_instanceCountMap.emplace(ss.str(), 0);
            endpointRootCountIt = m_instanceCountMap.find(ss.str());
        }

        // Set id of instance
        m_instanceId = endpointRootCountIt->second;

        // Increment class counter
        endpointRootCountIt->second++;

        // Set endpoint root
        ss << m_instanceId;
        m_endpointRoot = ss.str();

        // Register instance in the class for later use
        m_endpointRootToInstance.emplace(std::make_pair(m_endpointRoot, this));

        // Tenta conectar (se não estiver associado a um Node, falhará)
        // Connect();
    }

    ~PubSubInfra(){};

    bool Connect();
    void Send(Ptr<Packet> packet);
    virtual void RegisterEndpoint(std::string endpoint);
    virtual void RemoveEndpoint(std::string endpoint);
    virtual void SubscribeToEndpoint(std::string endpoint);
    virtual void PublishToEndpointSubscribers(std::string endpoint, Json json);
    void ReceivePacket(Ptr<Socket> socket);
    void ReceiveJsonPayload(Json msg);
    // To be implemented by each custom xApp and E2Node
    virtual void HandlePayload(std::string src_endpoint, std::string dest_endpoint, Json payload){};
    void RegisterEndpointCallback(std::string endpoint, std::function<void(Json&)>);
    void RemoveEndpointCallback(std::string endpoint);
    std::function<void(Json&)> GetEndpointCallback(std::string endpoint);
    // private:
    Ptr<Socket> m_socket;
    std::string m_endpointRoot; // set during initialization
    uint64_t m_instanceId = 0;  // set during initialization
    std::map<std::string, Address> m_endpointToAddressMap;
    static Address m_node0Address; // set during the first connect
    static std::map<const std::string, uint64_t>
        m_instanceCountMap; // incremented during initialization
    static std::map<const std::string, const PubSubInfra*> m_endpointRootToInstance;
    static std::map<const std::string, std::vector<std::string>> m_endpointToSubscribers;
    static std::map<const std::string, std::function<void(Json&)>> m_endpointCallbacks;
    // static methods
    Ipv4Address getNodeAddress(unsigned device = 3);
    static Ptr<Packet> encodeJsonToPacket(Json json_contents);
    static Json decodePacketToJson(Ptr<Packet> packet);
    static std::string buildEndpoint(std::string rootEndpoint, std::string endpoint);
    static bool sRegisterEndpoint(std::string rootEndpoint, std::string endpoint);
    static bool sUpdateEndpoint(std::string rootEndpoint,
                                std::string old_endpoint,
                                std::string new_endpoint);
    static bool sRemoveEndpoint(std::string rootEndpoint, std::string endpoint);
    static void sSubscribeToEndpoint(std::string subscribed_endpoint,
                                     std::string subscriber_endpoint);
    static void sUnsubscribeToEndpoint(std::string subscribed_endpoint,
                                       std::string subscriber_endpoint);
    void sPublishToEndpointSubscribers(std::string publisherEndpoint,
                                       std::string endpoint,
                                       std::string json_literal);
    static std::string getEndpointRoot(std::string endpoint);
    static std::string getSubEndpoint(std::string endpointRoot, std::string completeEndpoint);
    Address getAddressFromEndpointRoot(std::string endpoint);
    const PubSubInfra* getInstanceFromEndpointRoot(std::string endpointRoot);
};
} // namespace ns3
#endif // NS3_PUBSUBINFRA_H
