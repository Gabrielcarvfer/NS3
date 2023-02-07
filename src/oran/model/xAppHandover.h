//
// Created by gabriel on 01/11/22.
//

#ifndef NS3_XAPP_HANDOVER_H
#define NS3_XAPP_HANDOVER_H

#include "xApp.h"

/**
 * \ingroup oran
 * ns3::oran::xAppHandover declaration.
 */

namespace ns3
{
namespace oran
{
/**
 * \ingroup oran
 * \class xAppHandover
 * \brief The base class of a Handover xApp
 */
class xAppHandover : public xApp
{
  public:
    xAppHandover();
    ~xAppHandover();
    /**
     * \brief Decides whether to reject the requested handover or reform the decision
     * \param [in, out] payload Json payload with the UE to handover (RNTI)
     *                  and target cell to handover (Target Primary Cell ID).
     */
    virtual void HandoverDecision(Json& payload);
};
} // namespace oran
} // namespace ns3
#endif // NS3_XAPP_HANDOVER_H
