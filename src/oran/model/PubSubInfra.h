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
#include <optional>
#include <regex>
#include <sstream>
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <typeinfo>
#include <utility>
#include <vector>

using Json = nlohmann::json; ///< nlohmann's Json type

/**
 * \ingroup oran
 * ns3::oran::PubSubInfra declaration.
 */

namespace ns3
{
namespace oran
{
/**
 * \ingroup oran
 * \class PubSubInfra
 * \brief Base Publisher-Subscriber infrastructure
 */
class PubSubInfra : public Application
{
  public:
    /**
     * \brief Constructor for PubSubInfra
     * \param [in] className Name of the class variant (used as the endpoint base)
     */
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

    /**
     * \brief Create a connection to the endpoint 0 (RIC)
     * \return true of the connection to the RIC succeeded and false otherwise
     */
    bool Connect();
    /**
     * \brief Send a packet
     * \param [in] packet Packet to be send
     */
    void Send(Ptr<Packet> packet);
    /**
     * \brief Register a service endpoint to the PubSub object.
     * \param [in] endpoint The service endpoint (e.g. /className/id/service).
     */
    virtual void RegisterEndpoint(std::string endpoint);
    /**
     * \brief Remove a service endpoint of the PubSub object.
     * \param [in] endpoint The service endpoint (e.g. /classname/id/service_endpoint_to_remove).
     */
    virtual void RemoveEndpoint(std::string endpoint);
    /**
     * \brief Subscribe PubSub derivate class to multicasts from a given endpoint
     * \param [in] endpoint The service endpoint being subscribed.
     */
    virtual void SubscribeToEndpoint(std::string endpoint);
    /**
     * \brief Publish json payload to all subscribers of a given endpoint
     * \param [in] endpoint The service endpoint being broadcasted to.
     * \param [in] json The payload to broadcast to subscribers.
     */
    virtual void PublishToEndpointSubscribers(std::string endpoint, Json json);
    /**
     * \brief Receive a packet
     * \param [in] socket Socket to receive packet from
     */
    void ReceivePacket(Ptr<Socket> socket);
    /**
     * \brief Receive a Json payload
     * \param [in] msg Json payload
     */
    void ReceiveJsonPayload(Json msg);
    // To be implemented by each custom xApp and E2Node
    /**
     * \brief Handle an incoming json payload sent from src_endpoint to dest_endpoint.
     * \param [in] src_endpoint The source endpoint.
     * \param [in] dest_endpoint The destination endpoint.
     * \param [in] payload Json object with the payload to be handled.
     */
    virtual void HandlePayload(std::string src_endpoint, std::string dest_endpoint, Json payload){};
    /**
     * \brief Register a custom endpoint handler.
     * \param [in] endpoint The service endpoint to handle
     * \param [in] function_ptr The handler function to service the endpoint.
     */
    void RegisterEndpointCallback(std::string endpoint, std::function<void(Json&)> function_ptr);
    /**
     * \brief Remove the custom endpoint handler.
     * \param [in] endpoint The service endpoint to remove.
     */
    void RemoveEndpointCallback(std::string endpoint);
    /**
     * \brief Retrieve the custom endpoint handler.
     * \param [in] endpoint The service endpoint to retrieve.
     * \return the function pointer for the handler
     */
    std::function<void(Json&)> GetEndpointCallback(std::string endpoint);

    /**
     * \brief Retrieve the endpoint root/prefix of a PubSubInfra object
     * \return the endpoint root
     */
    std::string GetRootEndpoint() const;
    /**
     * \brief Retrieve the instance ID of a PubSubInfra object
     * \return the instance ID
     */
    uint64_t GetInstanceID() const;
    /**
     * \brief Retrieve socket of PubSubInfra object
     * \return socket
     */
    const Ptr<const Socket> GetInstanceSocket() const;
    /**
     * \brief Retrieve the instance ID of a PubSubInfra object
     * \param [in] endpoint Endpoint root of the desired PubSubInfra object
     * \return pointer to the PubSubInfra object
     */
    static const PubSubInfra* RetrieveInstanceWithEndpoint(std::string endpoint);
    /**
     * \brief Retrieve the subscribers of a given endpoint
     * \param [in] endpoint Endpoint root of the desired PubSubInfra object
     * \return list of subscribers
     */
    static std::optional<std::vector<std::string>> RetrieveSubscribersOfEndpoint(
        std::string endpoint);
    /**
     * \brief Extract the endpoint prefix of a given endpoint
     * \param [in] endpoint Complete endpoint to a service exported by a PubSubInfra object
     * \return endpoint prefix of a PubSubInfra relative to the passed endpoint
     */
    static std::string getEndpointRoot(std::string endpoint);
    /**
     * \brief Extract the endpoint suffix of a given endpoint
     * \param [in] endpointRoot Endpoint prefix of the complete endpoint
     * \param [in] completeEndpoint Complete endpoint to a service exported by a PubSubInfra object
     * \return endpoint suffix completeEndpoint
     */
    static std::string getSubEndpoint(std::string endpointRoot, std::string completeEndpoint);
    /**
     * \brief Build a full endpoint
     * \param [in] rootEndpoint Endpoint prefix of a given PubSubInfra object
     * \param [in] endpoint Partial or complete endpoint of a service
     * \return the complete endpoint to a service, ensuring the endpoint prefix is valid
     */
    static std::string buildEndpoint(std::string rootEndpoint, std::string endpoint);
    /**
     * \brief Encode JSON to packet.
     * \param [in] json_contents JSON contents to serialize.
     * \return encoded packet containing a serialized JSON
     */
    static Ptr<Packet> encodeJsonToPacket(Json json_contents);
    /**
     * \brief Packet to decode a JSON object.
     * \param [in] packet Packet containing a serialized JSON object.
     * \return the decoded JSON object
     */
    static Json decodePacketToJson(Ptr<Packet> packet);

  protected:
    Ptr<Socket> m_socket;       ///< Socket between the current node and the RIC
    std::string m_endpointRoot; ///< Endpoint prefix, set during initialization
    uint64_t m_instanceId = 0;  ///< PubSubInfra instance ID, set during initialization
    std::map<std::string, Address>
        m_endpointToAddressMap;    ///< Map holding the address of known endpoints
    static Address m_node0Address; ///< Address of the first instance (RIC/E2 Termination), set
                                   ///< during the first connect call
    static std::map<const std::string, uint64_t>
        m_instanceCountMap; ///< Mapping of endpoint prefix and instance ID, set during
                            ///< initialization
    static std::map<const std::string, const PubSubInfra*>
        m_endpointRootToInstance; ///< Mapping between endpoint prefix and PubSubInfra object
    static std::map<const std::string, std::vector<std::string>>
        m_endpointToSubscribers; ///< Mapping of subscribed endpoints to subscriber endpoints
    static std::map<const std::string, std::function<void(Json&)>>
        m_endpointCallbacks; ///< Mapping between custom endpoints and function handlers (meant for
                             ///< xApps)
    /**
     * \brief Retrieve the IPv4 address of the specified device
     * \param [in] device Device number of Node to retrieve the IP address
     * \return IPv4 Address
     */
    Ipv4Address getNodeAddress(unsigned device = 3);
    // static methods
    /**
     * \brief Registers an endpoint in the static storage
     * \param [in] rootEndpoint Endpoint prefix of a given PubSubInfra object
     * \param [in] endpoint Partial endpoint relative to a service exported by the rootEndpoint
     * object \return true if successful and false otherwise
     */
    static bool sRegisterEndpoint(std::string rootEndpoint, std::string endpoint);
    /**
     * \brief Updates an old endpoint to a new endpoint in the static storage
     * \param [in] rootEndpoint Endpoint prefix of a given PubSubInfra object
     * \param [in] old_endpoint Partial endpoint relative to a service exported by the rootEndpoint
     * object \param [in] new_endpoint Partial endpoint relative to a service exported by the
     * rootEndpoint object \return true if successful and false otherwise
     */
    static bool sUpdateEndpoint(std::string rootEndpoint,
                                std::string old_endpoint,
                                std::string new_endpoint);
    /**
     * \brief Remove an endpoint from the static storage
     * \param [in] rootEndpoint Endpoint prefix of a given PubSubInfra object
     * \param [in] endpoint Partial endpoint relative to a service exported by the rootEndpoint
     * object \return true if successful and false otherwise
     */
    static bool sRemoveEndpoint(std::string rootEndpoint, std::string endpoint);
    /**
     * \brief Subscribe a subscribed_endpoint to a subscriber_endpoint
     * \param [in] subscribed_endpoint Endpoint prefix of a given PubSubInfra object
     * \param [in] subscriber_endpoint Complete endpoint to a service exported by a PubSubInfra
     * object
     */
    static void sSubscribeToEndpoint(std::string subscribed_endpoint,
                                     std::string subscriber_endpoint);
    /**
     * \brief Unsubscribe a subscribed_endpoint to a subscriber_endpoint
     * \param [in] subscribed_endpoint Endpoint prefix of a given PubSubInfra object
     * \param [in] subscriber_endpoint Complete endpoint to a service exported by a PubSubInfra
     * object
     */
    static void sUnsubscribeToEndpoint(std::string subscribed_endpoint,
                                       std::string subscriber_endpoint);
    /**
     * \brief Publish a message to all the subscribers of a given endpoint
     * \param [in] publisherEndpoint Endpoint prefix of a given PubSubInfra object
     * \param [in] endpoint Complete or partial endpoint to a service exported by a PubSubInfra
     * object \param [in] json_literal Message to be published to subscribers of endpoint
     */
    void sPublishToEndpointSubscribers(std::string publisherEndpoint,
                                       std::string endpoint,
                                       std::string json_literal);
    /**
     * \brief Retrieve IP address of an endpoint prefix
     * \param [in] endpoint Complete endpoint to a service exported by a PubSubInfra object
     * \return IPv4 address of the associated endpoint
     */
    Address getAddressFromEndpointRoot(std::string endpoint);
    /**
     * \brief Retrieve the PubSubInfra relative to an endpoint prefix
     * \param [in] endpointRoot Endpoint prefix/root of a PubSubInfra object
     * \return A pointer to the PubSubInfra object
     */
    const PubSubInfra* getInstanceFromEndpointRoot(std::string endpointRoot);
};
} // namespace oran
} // namespace ns3
#endif // NS3_PUBSUBINFRA_H
