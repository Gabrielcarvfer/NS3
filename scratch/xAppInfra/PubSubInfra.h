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

  bool
  Connect ()
  {
    auto node = GetNode ();
    if (!node)
      return false;

    if (node && m_socket)
      return true;

    // Estabeler socket com nó 0 do mesmo tipo de aplicação
    TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
    m_socket = Socket::CreateSocket (node, tid);
    if (m_endpointRoot == "/E2Node/0")
      {
        uint16_t portBase = 8000;
        uint8_t tries = 3;

        while (true)
          {
            if (tries == 0)
              {
                NS_FATAL_ERROR ("Failed to bind socket");
              }

            m_node0Address = InetSocketAddress (Ipv4Address ("10.0.0.6"), portBase);

            if (m_socket->Bind (m_node0Address) != -1)
              {
                break;
              }
            tries--;
            portBase++;
          }
        std::cout << "Binding port at " << m_endpointRoot << std::endl;
      }
    else
      {
        if (m_socket->Bind () == -1)
          {
            NS_FATAL_ERROR (
                "Failed to bind socket"); //InetSocketAddress(Ipv4Address::GetAny(), 8123));
          }

        std::cout << "Binding port at " << m_endpointRoot << std::endl;

        m_socket->Connect (m_node0Address);
        std::cout << "Connecting to " << m_endpointRootToInstance.begin ()->first << " from "
                  << m_endpointRoot << std::endl;

        Json REGISTER_CALL;
        REGISTER_CALL["ENDPOINT"] = m_endpointRoot;
        REGISTER_CALL["INTENT"] = "REGISTER";
        Simulator::Schedule (Seconds (0.1), &PubSubInfra::Send, this,
                             encodeJsonToPacket (REGISTER_CALL));
      }
    m_socket->SetRecvCallback (MakeCallback (&PubSubInfra::ReceivePacket, this));
    return true;
  }

  void
  Send (Ptr<Packet> packet)
  {
    std::cout << this->m_endpointRoot << " sending packet " << packet << std::endl;
    m_socket->Send (packet);
  }

  void
  RegisterEndpoint (std::string endpoint)
  {
    std::cout << this->m_endpointRoot << " registering endpoint " << endpoint << std::endl;

    // Inclui prefixo ao endpoint se não estiver presente
    if (endpoint.find (this->m_endpointRoot) == std::string::npos)
      {
        endpoint = this->m_endpointRoot + endpoint;
      }

    // Remove // duplicados
    std::regex e ("//"); // matches derived type
    std::string result;
    std::regex_replace (std::back_inserter (result), endpoint.begin (), endpoint.end (), e, "/");

    // Chama método estático para fazer o registro
    sRegisterEndpoint (result);
  }

  void
  SubscribeToEndpoint (std::string endpoint)
  {
    std::cout << this->m_endpointRoot << " subscribing to endpoint " << endpoint << std::endl;
    sSubscribeToEndpoint (endpoint, this);
  }

  void
  PublishToEndpointSubscribers (std::string endpoint, Json json)
  {
    if (this->m_endpointRoot == "/E2Node/0")
      {
        // Nó 0 age como roteador
        sPublishToEndpointSubscribers (this->m_endpointRoot, endpoint, json.dump ());
      }
    else
      {
        // Outros nós serializaram JSON e transmitem para o nó zero para retransmissão.
        Json RPC_CALL;
        RPC_CALL["ENDPOINT"] = endpoint;
        RPC_CALL["INTENT"] = "RPC";
        RPC_CALL["RPC"] = "GET"; // Forward from source endpoint to subscribed endpoints
        RPC_CALL["PAYLOAD"] = json;

        // alternativamente, envie RPC para E2T (node 0)
        m_socket->SendTo (encodeJsonToPacket (RPC_CALL), 0, m_node0Address);
      }
  }

  void
  ReceivePacket (Ptr<Socket> socket)
  {
    Ptr<Packet> packet;
    Address from;
    while ((packet = socket->RecvFrom (from)))
      {
        // decode packet to json
        Json msg = decodePacketToJson (packet);

        NS_ASSERT (msg.contains ("ENDPOINT"));
        std::string endpoint = msg.find ("ENDPOINT")->get<std::string> ();
        if (m_endpointToSocketMap.find (endpoint) == m_endpointToSocketMap.end ())
          {

            m_endpointToSocketMap.emplace (endpoint, socket);
          }

        std::cout << "Endpoint " << m_endpointRoot << " received message " << msg.dump ()
                  << std::endl;

        ReceiveJsonPayload (msg);
      }
  }

  void
  ReceiveJsonPayload (Json msg)
  {
    NS_ASSERT (msg.contains ("INTENT"));
    NS_ASSERT (msg.contains ("ENDPOINT"));

    std::string intent = msg.find ("INTENT")->get<std::string> ();

    if (intent == "RPC")
      {
        NS_ASSERT (msg.contains ("RPC"));
        std::string rpc = msg.find ("RPC")->get<std::string> ();
        NS_ASSERT (msg.contains ("PAYLOAD"));

        if (rpc == "GET")
          {
            // Forward incoming message to endpoint subscribers
            PublishToEndpointSubscribers (msg.find ("ENDPOINT")->get<std::string> (),
                                          msg.find ("PAYLOAD")->get<Json> ());
          }
        else if (rpc == "POST")
          {
            // Forward incoming message to endpoint
          }
        else
          {
            NS_ASSERT ("Incorrect RPC intent");
          }
      }
    else if (intent == "REGISTER")
      {
        // Just opening the socket
      }
    else if (intent == "SUBSCRIPTION")
      {
        NS_ASSERT (msg.contains ("PAYLOAD"));
        HandlePayload (msg.find ("ENDPOINT")->get<std::string> (),
                       msg.find ("PAYLOAD")->get<Json> ());
      }
    else
      {
        std::cout << "ReceiveJsonPayload (" << this << "): Unrecognized intent" << std::endl;
      }
  }
  // To be implemented by each custom xApp and E2Node
  void HandlePayload (std::string endpoint, Json payload){};
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

  Ipv4Address
  getNodeAddress (unsigned device = 3)
  {
    Ptr<Ipv4> ipv4 = GetNode ()->GetObject<Ipv4> ();
    return ipv4->GetAddress (device, 0).GetLocal ();
  }

#define LEN64 (sizeof (uint64_t))
  static Ptr<Packet>
  encodeJsonToPacket (Json json_contents)
  {
    std::string json_literal = json_contents.dump ();
    uint64_t size = json_literal.size () + 1;
    uint8_t *data_block = new uint8_t[LEN64 + size];
    memcpy (&data_block[0], &size, LEN64);
    memcpy (&data_block[LEN64], json_literal.data (), size);
    Ptr<Packet> p = Create<Packet> (data_block, LEN64 + size);
    delete[] data_block; // Deleted by packet
    return p;
  }

  static Json
  decodePacketToJson (Ptr<Packet> packet)
  {
    uint64_t size;
    packet->CopyData ((uint8_t *) &size, LEN64);
    uint8_t *json_literal = new uint8_t[LEN64 + size];
    packet->CopyData (json_literal, LEN64 + size);
    Json json = Json::parse ((char *) &json_literal[LEN64]);
    delete[] json_literal;
    return json;
  }

  static void
  sRegisterEndpoint (std::string endpoint)
  {
    // If registered endpoint doesn't exist, register it
    if (m_endpointToSubscribers.find (endpoint) == m_endpointToSubscribers.end ())
      {
        m_endpointToSubscribers.emplace (endpoint, std::vector<const PubSubInfra *>{});
      }
    else
      {
        NS_ASSERT_MSG (false, "Endpoint is already registered: " << endpoint);
      }
  }

  static void
  sSubscribeToEndpoint (std::string endpoint, PubSubInfra *subscriber)
  {

    // Register the subscriber to the endpoint
    auto endpointIt = m_endpointToSubscribers.find (endpoint);
    if (m_endpointToSubscribers.find (endpoint) == m_endpointToSubscribers.end ())
      {
        NS_ASSERT_MSG (false, "Subscriber tried to subscribe to non-existant endpoint: subscriber "
                                  << subscriber->m_endpointRoot << ", endpoint " << endpoint);
      }
    endpointIt->second.push_back (subscriber);
  }

  void
  sPublishToEndpointSubscribers (std::string publisherEndpoint, std::string endpoint,
                                 std::string json_literal)
  {
    // Check if publisher is registered
    auto publisherEndpointIt = m_endpointRootToInstance.find (publisherEndpoint);
    if (publisherEndpointIt == m_endpointRootToInstance.end ())
      {
        NS_ASSERT_MSG (false, "Publisher endpoint is not registered: " << publisherEndpoint);
      }

    // Check if updated endpoint is registered
    auto EndpointIt = m_endpointToSubscribers.find (endpoint);
    if (EndpointIt == m_endpointToSubscribers.end ())
      {
        NS_ASSERT_MSG (false, "Endpoint" << endpoint << " is not registered");
      }

    // Forward published message to each subscriber
    for (auto &subscriber : EndpointIt->second)
      {
        if (subscriber == this)
          {
            // Handle locally
            Json payload;
            payload["ENDPOINT"] = endpoint;
            payload["INTENT"] = "SUBSCRIPTION";
            payload["PAYLOAD"] = json_literal;
            ReceiveJsonPayload (payload);
          }
        else
          {
            // Retransmit
          }
        std::cout
            << json_literal << " " << subscriber
            << std::
                   endl; //subscriber->ScheduleReceivePacket(json_literal); // pulando toda a pilha de rede
      }
  }
};
}//namespace ns3
#endif //NS3_PUBSUBINFRA_H
