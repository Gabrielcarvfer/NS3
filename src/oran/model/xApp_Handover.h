//
// Created by gabriel on 01/11/22.
//

#ifndef _XAPP_HANDOVER_H_
#define _XAPP_HANDOVER_H_

#include "xApp.h"

namespace ns3
{
    class xApp_Handover : public xApp {
     public:
      xApp_Handover ();
      ~xApp_Handover ();
      void HandoverDecision (Json& payload);
    };
}
#endif //_XAPP_HANDOVER_H_
