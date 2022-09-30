//
// Created by gabriel on 29/09/22.
//

#ifndef NS3_DYNAMICSPECTRUMALLOCATIONXAPP_H
#define NS3_DYNAMICSPECTRUMALLOCATIONXAPP_H

#include "xApp.h"

namespace ns3
{
class dynamicSpectrumAllocationxApp : public xApp
{
public:
  dynamicSpectrumAllocationxApp () : xApp (){};
  ~dynamicSpectrumAllocationxApp (){};
  void TakeAction();
};
}
#endif //NS3_DYNAMICSPECTRUMALLOCATIONXAPP_H
