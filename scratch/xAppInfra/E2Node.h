//
// Created by gabriel on 29/09/22.
//

#ifndef NS3_E2NODE_H
#define NS3_E2NODE_H

#include "PubSubInfra.h"

namespace ns3 {

class E2Node : public PubSubInfra
{
public:
  E2Node () : PubSubInfra ("E2Node"){};
  ~E2Node (){};
};

}
#endif //NS3_E2NODE_H
