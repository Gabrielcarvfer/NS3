//
// Created by Gabriel Ferreira(@gabrielcarvfer) on 31/08/22.
//

#include "PubSubInfra.h"

using namespace ns3;

std::map<const std::string, uint64_t> PubSubInfra::m_instanceCountMap{};
Address PubSubInfra::m_node0Address{};
std::map<const std::string, const PubSubInfra*>
    PubSubInfra::m_endpointRootToInstance{};
std::map<const std::string, std::vector<const PubSubInfra*>>
    PubSubInfra::m_endpointToSubscribers{};
