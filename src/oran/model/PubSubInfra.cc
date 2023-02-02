//
// Created by Gabriel Ferreira(@gabrielcarvfer) on 31/08/22.
//

#include "PubSubInfra.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("PubSubInfra");

std::map<const std::string, uint64_t> PubSubInfra::m_instanceCountMap{};
Address PubSubInfra::m_node0Address{};
std::map<const std::string, const PubSubInfra*> PubSubInfra::m_endpointRootToInstance{};
std::map<const std::string, std::vector<std::string>> PubSubInfra::m_endpointToSubscribers{};
std::map<const std::string, std::function<void(Json&)>> PubSubInfra::m_endpointCallbacks{};

bool
PubSubInfra::Connect()
{
    NS_LOG_FUNCTION(this);

    auto node = GetNode();
    if (!node)
        return false;

    if (node && m_socket)
        return true;

    // Estabelecer socket com nó 0 do mesmo tipo de aplicação
    TypeId tid = TypeId::LookupByName("ns3::UdpSocketFactory");
    m_socket = Socket::CreateSocket(node, tid);
    if (m_endpointRoot == "/E2Node/0")
    {
        uint16_t portBase = 8000;
        uint8_t tries = 3;

        while (true)
        {
            if (tries == 0)
            {
                NS_FATAL_ERROR("Failed to bind socket");
            }

            m_node0Address = InetSocketAddress(Ipv4Address("10.0.0.6"), portBase);

            if (m_socket->Bind(m_node0Address) != -1)
            {
                break;
            }
            tries--;
            portBase++;
        }
        NS_LOG_FUNCTION("Binding port at " + m_endpointRoot);
    }
    else
    {
        if (m_socket->Bind() == -1)
        {
            NS_FATAL_ERROR(
                "Failed to bind socket"); // InetSocketAddress(Ipv4Address::GetAny(), 8123));
        }

        NS_LOG_FUNCTION("Binding port at " + m_endpointRoot);

        m_socket->Connect(m_node0Address);
        NS_LOG_FUNCTION("Connecting to " + m_endpointRootToInstance.begin()->first + " from " +
                        m_endpointRoot);

        Json REGISTER_CALL;
        REGISTER_CALL["SRC_ENDPOINT"] = m_endpointRoot;
        REGISTER_CALL["DEST_ENDPOINT"] = "/E2Node/0/";
        REGISTER_CALL["INTENT"] = "REGISTER";
        REGISTER_CALL["PAYLOAD"] = ""; // Empty payload
        Simulator::Schedule(Seconds(0.1),
                            &PubSubInfra::Send,
                            this,
                            encodeJsonToPacket(REGISTER_CALL));
    }
    m_socket->SetRecvCallback(MakeCallback(&PubSubInfra::ReceivePacket, this));
    return true;
}

void
PubSubInfra::Send(Ptr<Packet> packet)
{
    NS_LOG_FUNCTION(this);
    NS_LOG_FUNCTION(this->m_endpointRoot + " sending packet " << packet);
    m_socket->Send(packet);
}

void
PubSubInfra::RegisterEndpoint(std::string endpoint)
{
    NS_LOG_FUNCTION(this);

    // Chama método estático para fazer o registro
    sRegisterEndpoint(m_endpointRoot, endpoint);
}

void
PubSubInfra::SubscribeToEndpoint(std::string endpoint)
{
    NS_LOG_FUNCTION(m_endpointRoot + " subscribing to endpoint " + endpoint);
    sSubscribeToEndpoint(endpoint, m_endpointRoot);
}

void
PubSubInfra::PublishToEndpointSubscribers(std::string endpoint, Json json)
{
    NS_LOG_FUNCTION(this);

    if (this->m_endpointRoot == "/E2Node/0")
    {
        // Nó 0 age como roteador
        sPublishToEndpointSubscribers(this->m_endpointRoot, endpoint, json.dump());
    }
    else
    {
        // Outros nós serializaram JSON e transmitem para o nó zero para retransmissão.
        Json RPC_CALL;
        RPC_CALL["SRC_ENDPOINT"] = m_endpointRoot;
        RPC_CALL["DEST_ENDPOINT"] = endpoint;
        RPC_CALL["INTENT"] = "RPC";
        RPC_CALL["RPC"] = "GET"; // Forward from source endpoint to subscribed endpoints
        RPC_CALL["PAYLOAD"] = json;

        // alternativamente, envie RPC para E2T (node 0)
        m_socket->SendTo(encodeJsonToPacket(RPC_CALL), 0, m_node0Address);
    }
}

void
PubSubInfra::ReceivePacket(Ptr<Socket> socket)
{
    NS_LOG_FUNCTION(this);

    Ptr<Packet> packet;
    Address from;
    while ((packet = socket->RecvFrom(from)))
    {
        // decode packet to json
        Json msg = decodePacketToJson(packet);
        // std::cout << to_string(msg) << std::endl;
        NS_ASSERT(msg.contains("SRC_ENDPOINT"));
        std::string endpoint = msg.find("SRC_ENDPOINT")->get<std::string>();
        if (m_endpointToAddressMap.find(endpoint) == m_endpointToAddressMap.end())
        {
            m_endpointToAddressMap.emplace(endpoint, from);
        }

        NS_LOG_FUNCTION("Endpoint " + m_endpointRoot + " received message: " + msg.dump());
        ReceiveJsonPayload(msg);
    }
}

void
PubSubInfra::ReceiveJsonPayload(Json msg)
{
    NS_LOG_FUNCTION(this);

    NS_ASSERT(msg.contains("DEST_ENDPOINT"));
    if (msg.contains("INTENT"))
    {
        std::string rpc;
        if (msg.contains("RPC"))
        {
            rpc = msg.find("RPC")->get<std::string>();
        }
        else
        {
            rpc = msg.find("INTENT")->get<std::string>();
        }
        NS_ASSERT(msg.contains("PAYLOAD"));
        NS_LOG_FUNCTION(rpc + " handling of " + to_string(msg));
        if (rpc == "GET")
        {
            // Forward incoming message to endpoint subscribers
            PublishToEndpointSubscribers(msg.find("DEST_ENDPOINT")->get<std::string>(),
                                         msg.find("PAYLOAD")->get<Json>());
        }
        else if (rpc == "POST")
        {
            // Forward incoming message to endpoint
        }
        else if (rpc == "REGISTER")
        {
            // Do nothing
        }
        else
        {
            NS_ASSERT("Incorrect RPC intent");
        }
    }
    else
    {
        if (msg.contains("PAYLOAD"))
        {
            Json payload;
            msg.at("PAYLOAD").get_to(payload);
            HandlePayload(msg["SRC_ENDPOINT"], msg["DEST_ENDPOINT"], payload);
        }
        else
        {
            std::cout << "ReceiveJsonPayload (" << this << "): Unrecognized intent and no payload"
                      << std::endl;
        }
    }
}

// private methods
Ipv4Address
PubSubInfra::getNodeAddress(unsigned device)
{
    NS_LOG_FUNCTION(this);

    Ptr<Ipv4> ipv4 = GetNode()->GetObject<Ipv4>();
    return ipv4->GetAddress(device, 0).GetLocal();
}

// static methods
#define LEN64 (sizeof(uint64_t))

Ptr<Packet>
PubSubInfra::encodeJsonToPacket(Json json_contents)
{
    NS_LOG_FUNCTION_NOARGS();

    std::string json_literal = json_contents.dump();
    uint64_t size = json_literal.size() + 1;
    uint8_t* data_block = new uint8_t[LEN64 + size]{0};
    memcpy(&data_block[0], &size, LEN64);
    memcpy(&data_block[LEN64], json_literal.data(), size);
    Ptr<Packet> p = Create<Packet>(data_block, LEN64 + size);
    delete[] data_block; // Deleted by packet
    return p;
}

Json
PubSubInfra::decodePacketToJson(Ptr<Packet> packet)
{
    NS_LOG_FUNCTION_NOARGS();

    uint64_t size;
    packet->CopyData((uint8_t*)&size, LEN64);
    uint8_t* json_literal = new uint8_t[LEN64 + size];
    packet->CopyData(json_literal, LEN64 + size);
    Json json = Json::parse((char*)&json_literal[LEN64]);
    delete[] json_literal;
    return json;
}

std::string
PubSubInfra::buildEndpoint(std::string rootEndpoint, std::string endpoint)
{
    // Inclui prefixo ao endpoint se não estiver presente
    if (endpoint.find(rootEndpoint) == std::string::npos)
    {
        endpoint = rootEndpoint + endpoint;
    }

    // Remove // duplicados
    std::regex e("//"); // matches derived type
    std::string result;
    std::regex_replace(std::back_inserter(result), endpoint.begin(), endpoint.end(), e, "/");
    return result;
}

bool
PubSubInfra::sRegisterEndpoint(std::string rootEndpoint, std::string endpoint)
{
    NS_LOG_FUNCTION(rootEndpoint + " registering endpoint " + endpoint);
    std::string resulting_endpoint = buildEndpoint(rootEndpoint, endpoint);

    // If registered endpoint doesn't exist, register it
    if (m_endpointToSubscribers.find(resulting_endpoint) == m_endpointToSubscribers.end())
    {
        m_endpointToSubscribers.emplace(resulting_endpoint, std::vector<std::string>{});
        NS_LOG_FUNCTION("Successful registration of endpoint " + resulting_endpoint);
        return true;
    }
    else
    {
        NS_LOG_FUNCTION("Failed to register endpoint " + resulting_endpoint);
        return false;
    }
}

bool
PubSubInfra::sUpdateEndpoint(std::string rootEndpoint,
                             std::string old_endpoint,
                             std::string new_endpoint)
{
    NS_LOG_FUNCTION(rootEndpoint + " updating endpoint " + old_endpoint + " with new endpoint " +
                    new_endpoint);
    bool successful = true;

    std::string resulting_old_endpoint = buildEndpoint(rootEndpoint, old_endpoint);
    std::string resulting_new_endpoint = buildEndpoint(rootEndpoint, new_endpoint);

    // Check if old endpoint exists
    successful &=
        m_endpointToSubscribers.find(resulting_old_endpoint) != m_endpointToSubscribers.end();
    if (!successful)
    {
        NS_LOG_FUNCTION("Can't update inexisting endpoint " + resulting_old_endpoint);
        return false;
    }

    // Create new endpoint
    successful &= sRegisterEndpoint(rootEndpoint, new_endpoint);
    if (!successful)
    {
        NS_LOG_FUNCTION("Can't create new endpoint " + resulting_new_endpoint);
        return false;
    }

    // Move subscribers from old endpoint
    m_endpointToSubscribers.find(resulting_new_endpoint)->second =
        m_endpointToSubscribers.find(resulting_old_endpoint)->second;

    // Remove old endpoint
    successful &= sRemoveEndpoint(rootEndpoint, old_endpoint);
    if (!successful)
    {
        NS_LOG_FUNCTION("Can't remove old endpoint " + resulting_old_endpoint);
        return false;
    }
    return true;
}

void
PubSubInfra::RemoveEndpoint(std::string endpoint)
{
    NS_LOG_FUNCTION(m_endpointRoot + " removing endpoint " + endpoint);
    sRemoveEndpoint(m_endpointRoot, endpoint);
}

bool
PubSubInfra::sRemoveEndpoint(std::string rootEndpoint, std::string endpoint)
{
    NS_LOG_FUNCTION(rootEndpoint + " removing endpoint " + endpoint);
    std::string resulting_endpoint = buildEndpoint(rootEndpoint, endpoint);

    auto it = m_endpointToSubscribers.find(resulting_endpoint);
    if (it == m_endpointToSubscribers.end())
    {
        return false;
    }
    else
    {
        m_endpointToSubscribers.erase(resulting_endpoint);
        return true;
    }
}

void
PubSubInfra::sSubscribeToEndpoint(std::string subscribed_endpoint, std::string subscriber_endpoint)
{
    NS_LOG_FUNCTION_NOARGS();

    // Register the subscriber to the endpoint
    auto endpointIt = m_endpointToSubscribers.find(subscribed_endpoint);
    if (m_endpointToSubscribers.find(subscribed_endpoint) == m_endpointToSubscribers.end())
    {
        NS_ASSERT_MSG(false,
                      "Subscriber tried to subscribe to non-existant endpoint: subscriber "
                          << getEndpointRoot(subscriber_endpoint) << ", endpoint "
                          << subscribed_endpoint);
    }
    endpointIt->second.push_back(getEndpointRoot(subscriber_endpoint));
}

void
PubSubInfra::sUnsubscribeToEndpoint(std::string subscribed_endpoint,
                                    std::string subscriber_endpoint)
{
    NS_LOG_FUNCTION_NOARGS();

    // Search for subscribed endpoint
    auto endpointIt = m_endpointToSubscribers.find(subscribed_endpoint);

    NS_ASSERT_MSG(
        m_endpointToSubscribers.find(subscribed_endpoint) != m_endpointToSubscribers.end(),
        "Subscriber tried to unsubscribe to non-existant endpoint: subscriber "
            << getEndpointRoot(subscriber_endpoint) << ", endpoint " << subscribed_endpoint);

    // Then search for the subscriber position
    auto subscriberEndpointIt = std::find(endpointIt->second.begin(),
                                          endpointIt->second.end(),
                                          getEndpointRoot(subscriber_endpoint));

    NS_ASSERT_MSG(subscriberEndpointIt != endpointIt->second.end(),
                  "Non-existing subscriber " + subscriber_endpoint + " for endpoint " +
                      subscriber_endpoint);

    // Finally, remove the subscriber from the list of subscribers
    endpointIt->second.erase(subscriberEndpointIt);
}

void
PubSubInfra::sPublishToEndpointSubscribers(std::string publisherEndpoint,
                                           std::string endpoint,
                                           std::string json_literal)
{
    NS_LOG_FUNCTION(this);

    // Check if publisher is registered
    auto publisherEndpointIt = m_endpointRootToInstance.find(publisherEndpoint);
    if (publisherEndpointIt == m_endpointRootToInstance.end())
    {
        NS_ASSERT_MSG(false, "Publisher endpoint is not registered: " << publisherEndpoint);
    }

    // Check if updated endpoint is registered
    auto EndpointIt = m_endpointToSubscribers.find(endpoint);
    if (EndpointIt == m_endpointToSubscribers.end())
    {
        NS_ASSERT_MSG(false, "DEST_ENDPOINT" << endpoint << " is not registered");
    }

    // Forward published message to each subscriber
    for (auto subscriber : EndpointIt->second)
    {
        if (getInstanceFromEndpointRoot(subscriber) == this)
        {
            // Handle locally
            Json payload;
            payload["SRC_ENDPOINT"] = m_endpointRoot;
            payload["DEST_ENDPOINT"] = endpoint;
            payload["INTENT"] = "SUBSCRIPTION";
            payload["PAYLOAD"] = json_literal;
            ReceiveJsonPayload(payload);
        }
        else
        {
            // Retransmit
        }
        std::cout << json_literal << " " << subscriber
                  << std::endl; // subscriber->ScheduleReceivePacket(json_literal); // pulando toda
                                // a pilha de rede
    }
}

std::string
PubSubInfra::getEndpointRoot(std::string endpoint)
{
    // trim everything after the second /
    uint16_t slashes = 0;
    for (auto character : endpoint)
    {
        slashes += character == '/';
    }
    while (slashes > 2)
    {
        endpoint = endpoint.substr(0, endpoint.find_last_of('/'));
        slashes--;
    }
    return endpoint;
}

std::string
PubSubInfra::getSubEndpoint(std::string endpointRoot, std::string completeEndpoint)
{
    return completeEndpoint.substr(endpointRoot.size(),
                                   completeEndpoint.size() - endpointRoot.size());
}

Address
PubSubInfra::getAddressFromEndpointRoot(std::string endpoint)
{
    auto it = m_endpointToAddressMap.find(endpoint);
    if (it == m_endpointToAddressMap.end())
    {
        NS_ABORT_MSG("No address for endpoint: " + endpoint);
    }
    return it->second;
}

const PubSubInfra*
PubSubInfra::getInstanceFromEndpointRoot(std::string endpointRoot)
{
    auto it = m_endpointRootToInstance.find(getEndpointRoot(endpointRoot));
    if (it == m_endpointRootToInstance.end())
    {
        NS_ABORT_MSG("Inexisting instance with endpoint " + endpointRoot);
    }
    return it->second;
}

void
PubSubInfra::RegisterEndpointCallback(std::string endpoint, std::function<void(Json&)> callback)
{
    m_endpointCallbacks[endpoint] = callback;
}

void
PubSubInfra::RemoveEndpointCallback(std::string endpoint)
{
    if (m_endpointCallbacks.find(endpoint) != m_endpointCallbacks.end())
    {
        m_endpointCallbacks.erase(endpoint);
    }
}

std::function<void(Json&)>
PubSubInfra::GetEndpointCallback(std::string endpoint)
{
    if (m_endpointCallbacks.find(endpoint) == m_endpointCallbacks.end())
    {
        return nullptr;
    }
    return m_endpointCallbacks.at(endpoint);
}
