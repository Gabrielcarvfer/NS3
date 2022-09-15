//
// Created by Gabriel Ferreira(@gabrielcarvfer) on 31/08/22.
//

#include "PubSubInfra.h"

template <> uint64_t PubSubInfra<xApp>::m_instanceCount = 0;
template <> Address PubSubInfra<xApp>::m_node0Address{};
template <> std::map<const std::string, const PubSubInfra<xApp>*>
    PubSubInfra<xApp>::m_endpointRootToInstance{};
template <> std::map<const std::string, std::vector<const PubSubInfra<xApp>*>>
    PubSubInfra<xApp>::m_endpointToSubscribers{};

template <> uint64_t PubSubInfra<E2Node>::m_instanceCount = 0;
template <> Address PubSubInfra<E2Node>::m_node0Address{};
template <> std::map<const std::string, const PubSubInfra<E2Node>*>
    PubSubInfra<E2Node>::m_endpointRootToInstance{};
template <> std::map<const std::string, std::vector<const PubSubInfra<E2Node>*>>
    PubSubInfra<E2Node>::m_endpointToSubscribers{};