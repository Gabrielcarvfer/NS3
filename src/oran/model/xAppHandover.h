//
// Created by gabriel on 01/11/22.
//

#ifndef NS3_XAPP_HANDOVER_H
#define NS3_XAPP_HANDOVER_H

#include "xApp.h"

namespace ns3
{
class xAppHandover : public xApp
{
  public:
    xAppHandover();
    ~xAppHandover();
    virtual void HandoverDecision(Json& payload);
};
} // namespace ns3
#endif // NS3_XAPP_HANDOVER_H