#ifndef NS3_XAPP_HANDOVER_MAX_RSRP_H
#define NS3_XAPP_HANDOVER_MAX_RSRP_H

#include "ns3/xAppHandover.h"

/**
 * \file
 * \ingroup oran
 * ns3::xAppHandoverMaxRsrq declaration.
 */

namespace ns3
{
class xAppHandoverMaxRsrq : public xAppHandover
{
  public:
    xAppHandoverMaxRsrq(bool initiateHandovers = false);
    uint16_t ChooseTargetCellId(uint16_t rnti);
    /**
     * \brief Decides whether to reject the requested handover or reform the decision
     * \param [in, out] json Json payload with the UE to handover (RNTI)
     *                  and target cell to handover (Target Primary Cell ID).
     */
    void HandoverDecision(Json& payload);
    /**
     * \brief When the xApp triggers the handover, this functions is called periodically to
     *        check whether a handover is necessary or not.
     */
    void PeriodicHandoverCheck();
    /**
     * \brief Callback function when the handover is initiated
     * \param [in] context The context from the call
     * \param [in] imsi The subscriber permanent ID associated to the UE
     * \param [in] cellid The cell ID
     * \param [in] rnti The temporary ID from an UE that failed to handover
     * \param [in] targetCellId The cell ID of the target cell to hand the UE over
     */
    void HandoverStarted(std::string context,
                         uint64_t imsi,
                         uint16_t cellid,
                         uint16_t rnti,
                         uint16_t targetCellId);
    /**
     * \brief Callback function when the handover succeeds
     * \param [in] context The context from the call
     * \param [in] imsi The subscriber permanent ID associated to the UE
     * \param [in] cellid The cell ID
     * \param [in] rnti The new temporary ID from an UE
     */
    void HandoverSucceeded(std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti);
    /**
     * \brief Callback function when a connection is established
     * \param [in] context The context from the call
     * \param [in] imsi The subscriber permanent ID associated to the UE
     * \param [in] cellid The cell ID
     * \param [in] rnti The temporary ID from an UE that failed to handover
     */
    void ConnectionEstablished(std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti);

  private:
    bool m_initiateHandovers; ///< Flag indicates that xApp initiates the handovers
    std::map<uint16_t, std::pair<uint64_t, uint16_t>>
        m_rntiToImsiAndCellid; ///< Map of RNTIs to IMSIs and currently corrected cells
    std::map<uint16_t, uint64_t> m_rntiInHandover; ///< Map of RNTIs in handover and their IMSIs
};
} // namespace ns3
#endif // NS3_XAPP_HANDOVER_MAX_RSRP_H
