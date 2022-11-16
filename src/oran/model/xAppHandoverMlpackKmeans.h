#ifndef NS3_XAPP_HANDOVER_MLPACK_KMEANS_H
#define NS3_XAPP_HANDOVER_MLPACK_KMEANS_H

#include "ns3/xAppHandover.h"

namespace ns3
{
    class xAppHandoverMlpackKmeans : public xAppHandover
    {
      public:
        xAppHandoverMlpackKmeans(bool kmeansEmptyPolicy = false);
        void HandoverDecision(Json& payload);
        void HandoverSucceeded(std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti);
        void HandoverFailed(std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti);
        void PeriodicClustering ();
      private:
        std::deque<std::tuple<uint16_t, uint16_t, uint16_t>> m_decision_history;
        std::map<uint16_t, uint16_t> m_rntiToClusteredCellId;
        std::map<uint16_t, uint16_t> m_rntiToCurrentCellId;
        bool m_kmeansKeepEmptyPolicy;
    };
}
#endif// NS3_XAPP_HANDOVER_MLPACK_KMEANS_H
