#ifndef NS3_XAPP_HANDOVER_MLPACK_KMEANS_H
#define NS3_XAPP_HANDOVER_MLPACK_KMEANS_H

#include "ns3/xAppHandover.h"

/**
 * \ingroup oran
 * ns3::oran::xAppHandoverMlpackKmeans declaration.
 */

namespace ns3
{
namespace oran
{
/**
 * \ingroup oran
 * \class xAppHandoverMlpackKmeans
 * \brief An implementation of a Handover xApp using
 * MlPack's implementation of K-Means clustering
 */
class xAppHandoverMlpackKmeans : public xAppHandover
{
  public:
    /**
     * \brief Decides whether to reject the requested handover or reform the decision
     * \param [in] kmeansEmptyPolicy Enable K-Means policy that allows empty clusters
     * \param [in] clusteringPeriodicitySec Period between K-Means clusterings
     * \param [in] initiateHandovers Flag controls whether the xApp should initiate handovers
     */
    xAppHandoverMlpackKmeans(bool kmeansEmptyPolicy = false,
                             float clusteringPeriodicitySec = 1.0,
                             bool initiateHandovers = false);
    /**
     * \brief Decides whether to reject the requested handover or reform the decision
     * \param [in, out] payload Json payload with the UE to handover (RNTI)
     *                  and target cell to handover (Target Primary Cell ID).
     */
    void HandoverDecision(Json& payload);
    /**
     * \brief Callback function when the handover succeeds
     * \param [in] context The context from the call
     * \param [in] imsi The subscriber permanent ID associated to the UE
     * \param [in] cellid The cell ID
     * \param [in] rnti The new temporary ID from the UE
     */
    void HandoverSucceeded(std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti);
    /**
     * \brief Callback function when the handover fails
     * \param [in] context The context from the call
     * \param [in] imsi The subscriber permanent ID associated to the UE
     * \param [in] cellid The cell ID
     * \param [in] rnti The temporary ID from the UE that failed to handover
     */
    void HandoverFailed(std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti);
    /**
     * \brief Callback function when the handover is initiated
     * \param [in] context The context from the call
     * \param [in] imsi The subscriber permanent ID associated to the UE
     * \param [in] cellid The cell ID
     * \param [in] rnti The temporary ID from the UE that failed to handover
     * \param [in] targetCellId The cell ID of the target cell to hand the UE over
     */
    void HandoverStarted(std::string context,
                         uint64_t imsi,
                         uint16_t cellid,
                         uint16_t rnti,
                         uint16_t targetCellId);
    /**
     * \brief Callback function when a connection is established
     * \param [in] context The context from the call
     * \param [in] imsi The subscriber permanent ID associated to the UE
     * \param [in] cellid The cell ID
     * \param [in] rnti The temporary ID from the UE that failed to handover
     */
    void ConnectionEstablished(std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti);
    /**
     * \brief Periodically clusters RNTIs into different cells
     */
    void PeriodicClustering();

  private:
    std::deque<std::tuple<uint16_t, uint16_t, uint16_t>>
        m_decision_history; ///< Keeps track of previous decisions
    std::map<uint16_t, uint16_t>
        m_rntiToClusteredCellId; ///< Map of RNTIs to their clustered cell ID
    std::map<uint16_t, uint16_t>
        m_rntiToCurrentCellId;        ///< Map of RNTIs to their currently connected cell ID
    bool m_kmeansKeepEmptyPolicy;     ///< Flag indicates if the policy to allow empty clusters is
                                      ///< enabled
    float m_clusteringPeriodicitySec; ///< Periodicity to re-cluster RNTIs
    bool m_initiateHandovers;         ///< Flag indicates if the xApp initiates the handovers
    std::map<uint16_t, uint64_t> m_imsiInHandover; ///< Map of RNTIs in handover and their IMSIs
};
} // namespace oran
} // namespace ns3
#endif // NS3_XAPP_HANDOVER_MLPACK_KMEANS_H
