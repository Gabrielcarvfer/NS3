#ifndef NS3_XAPP_HANDOVER_MALICIOUS_POSITIONING_H
#define NS3_XAPP_HANDOVER_MALICIOUS_POSITIONING_H

#include "ns3/vector.h"
#include "ns3/xAppHandover.h"

/**
 * \ingroup oran
 * ns3::oran::xAppHandoverMaliciousPositioning declaration.
 */

namespace ns3
{
namespace oran
{
/**
 * \ingroup oran
 * \class xAppHandoverMaliciousPositioning
 * \brief An implementation of a Handover xApp using
 * the MaliciousPositioning strategy
 */
class xAppHandoverMaliciousPositioning : public xAppHandover
{
  public:
    /**
     * \brief Constructor of xAppHandoverMaliciousPositioning.
     */
    xAppHandoverMaliciousPositioning(bool useRnti = false);

    /**
     * \brief Destructor of xAppHandoverMaliciousPositioning.
     */
    ~xAppHandoverMaliciousPositioning();

    /**
     * \brief Decides whether to reject the requested handover or reform the decision.
     * \param [in, out] payload Json payload with the UE to handover (RNTI)
     *                  and target cell to handover (Target Primary Cell ID).
     */
    void HandoverDecision(Json& payload);
    /**
     * \brief This functions is called periodically to represent the inner workings
     *        of a malicious xApp tracking users.
     */
    void PeriodicPositioning();

    std::map<uint16_t, double> GetRntiRsrqMeasurements(uint16_t rnti, Time gracePeriod = Seconds(10));
    Vector3D Multilateration(std::map<uint16_t, double>& measurements);
    Vector3D GradientDescent(std::map<uint16_t, double>& measurements, Ptr<Node> rntiNode);
    Vector3D QuadrantSearch(std::map<uint16_t, double>& measurements, Ptr<Node> rntiNode);
  private:
    std::set<uint16_t> m_rntiSet;
    std::map<uint16_t, ns3::Vector3D> m_eNbPositions;
    bool m_useRnti = false;
    std::vector<std::tuple<Time, uint16_t, uint32_t, Vector3D>> m_rntiNodeTracking;
};
} // namespace oran
} // namespace ns3
#endif // NS3_XAPP_HANDOVER_MALICIOUS_POSITIONING_H
