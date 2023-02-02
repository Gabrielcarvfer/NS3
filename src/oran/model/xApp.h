//
// Created by gabriel on 29/09/22.
//

#ifndef NS3_XAPP_H
#define NS3_XAPP_H

#include "PubSubInfra.h"

/**
 * \file
 * \ingroup oran
 * ns3::xApp declaration.
 */

namespace ns3
{

/**
 * Base xApp infrastructure
 */
class xApp : public PubSubInfra
{
  public:
    xApp()
        : PubSubInfra("xApp"){};
    ~xApp(){};
};

} // namespace ns3
#endif // NS3_XAPP_H
