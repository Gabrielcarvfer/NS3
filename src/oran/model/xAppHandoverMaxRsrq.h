#ifndef NS3_XAPP_HANDOVER_MAX_RSRP_H
#define NS3_XAPP_HANDOVER_MAX_RSRP_H

#include "ns3/xAppHandover.h"

namespace ns3
{
    class xAppHandoverMaxRsrq : public xAppHandover
    {
      public:
        xAppHandoverMaxRsrq(bool initiateHandovers = false);
        uint16_t ChooseTargetCellId(uint16_t rnti);
        void HandoverDecision(Json& payload);
        void PeriodicHandoverCheck();
        void HandoverStarted (std::string context,
                              uint64_t imsi,
                              uint16_t cellid,
                              uint16_t rnti,
                              uint16_t targetCellId);
        void HandoverSucceeded (std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti);
        void ConnectionEstablished (std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti);
      private:
        bool m_initiateHandovers;
        std::map<uint16_t, std::pair<uint64_t,uint16_t>> m_rntiToImsiAndCellid;
        std::map<uint16_t, uint64_t> m_rntiInHandover;

    };
}
#endif// NS3_XAPP_HANDOVER_MAX_RSRP_H
