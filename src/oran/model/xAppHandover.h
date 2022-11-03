//
// Created by gabriel on 01/11/22.
//

#ifndef NS3_XAPP_HANDOVER_H
#define NS3_XAPP_HANDOVER_H

#include "xApp.h"

namespace ns3
{
    class xAppHandover : public xApp {
     public:
      xAppHandover ();
      ~xAppHandover ();
      void HandoverDecision (Json& payload);
    };
}
#endif //NS3_XAPP_HANDOVER_H
