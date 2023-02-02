//
// Created by gabriel on 01/11/22.
//

#ifndef NS3_XAPP_HANDOVER_H
#define NS3_XAPP_HANDOVER_H

#include "xApp.h"

/**
 * \file
 * \ingroup oran
 * ns3::xAppHandover declaration.
 */

namespace ns3
{
class xAppHandover : public xApp
{
  public:
    xAppHandover();
    ~xAppHandover();
    /**
     * \brief Decides whether to reject the requested handover or reform the decision
     * \param [in, out] json Json payload with the UE to handover (RNTI)
     *                  and target cell to handover (Target Primary Cell ID).
     */
    virtual void HandoverDecision(Json& payload);
};
} // namespace ns3
#endif // NS3_XAPP_HANDOVER_H
