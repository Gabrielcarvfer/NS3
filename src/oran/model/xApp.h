//
// Created by gabriel on 29/09/22.
//

#ifndef NS3_XAPP_H
#define NS3_XAPP_H

#include "PubSubInfra.h"

/**
 * \ingroup oran
 * ns3::oran::xApp declaration.
 */

namespace ns3
{
namespace oran
{

/**
 * \ingroup oran
 * \class xApp
 * \brief Base xApp infrastructure
 */
class xApp : public PubSubInfra
{
  public:
    xApp()
        : PubSubInfra("xApp"){};
    ~xApp(){};
};

} // namespace oran
} // namespace ns3
#endif // NS3_XAPP_H
