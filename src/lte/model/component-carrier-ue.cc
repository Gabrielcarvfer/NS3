/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2015 Danilo Abrignani
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Danilo Abrignani <danilo.abrignani@unibo.it>
 */

#include "component-carrier-ue.h"
#include "../../core/model/uinteger.h"
#include "../../core/model/boolean.h"
#include "../../core/model/simulator.h"
#include "../../core/model/log.h"
#include "../../core/model/abort.h"
#include "lte-ue-phy.h"
#include "lte-ue-mac.h"
#include "../../core/model/pointer.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("ComponentCarrierUe");

NS_OBJECT_ENSURE_REGISTERED ( ComponentCarrierUe);

TypeId ComponentCarrierUe::GetTypeId (void)
{
  static TypeId
    tid =
    TypeId ("ns3::ComponentCarrierUe")
    .SetParent<ComponentCarrier> ()
    .AddConstructor<ComponentCarrierUe> ()
    .AddAttribute ("LteUePhy",
                   "The PHY associated to this EnbNetDevice",
                   PointerValue (),
                   MakePointerAccessor (&ComponentCarrierUe::m_phy),
                   MakePointerChecker <LteUePhy> ())
    .AddAttribute ("LteUeMac",
                   "The MAC associated to this UeNetDevice",
                   PointerValue (),
                   MakePointerAccessor (&ComponentCarrierUe::m_mac),
                   MakePointerChecker <LteUeMac> ())
  ;
  return tid;
}
ComponentCarrierUe::ComponentCarrierUe ()
{
  NS_LOG_FUNCTION (this);
}

ComponentCarrierUe::~ComponentCarrierUe (void)
{
  NS_LOG_FUNCTION (this);
}

void
ComponentCarrierUe::DoDispose ()
{
  NS_LOG_FUNCTION (this);
  m_phy->Dispose ();
  m_phy = 0;
  m_mac->Dispose ();
  m_mac = 0;
  Object::DoDispose ();
}


void
ComponentCarrierUe::DoInitialize (void)
{
  NS_LOG_FUNCTION (this);
  m_isConstructed = true;
  m_phy->Initialize ();
  m_mac->Initialize();
}

void
ComponentCarrierUe::SetPhy (Ptr<LteUePhy> s)
{
  NS_LOG_FUNCTION (this);
  m_phy = s;
}


Ptr<LteUePhy>
ComponentCarrierUe::GetPhy () const
{
  NS_LOG_FUNCTION (this);
  return m_phy;
}

void 
ComponentCarrierUe::SetMac (Ptr<LteUeMac> s)
{
  NS_LOG_FUNCTION (this);
  m_mac = s;
}

Ptr<LteUeMac>
ComponentCarrierUe::GetMac () const
{
  NS_LOG_FUNCTION (this);
  return m_mac;
}

} // namespace ns3


