/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011 Yufei Cheng
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
 * Author: Yufei Cheng   <yfcheng@ittc.ku.edu>
 *
 * James P.G. Sterbenz <jpgs@ittc.ku.edu>, director
 * ResiliNets Research Group  http://wiki.ittc.ku.edu/resilinets
 * Information and Telecommunication Technology Center (ITTC)
 * and Department of Electrical Engineering and Computer Science
 * The University of Kansas Lawrence, KS USA.
 *
 * Work supported in part by NSF FIND (Future Internet Design) Program
 * under grant CNS-0626918 (Postmodern Internet Architecture),
 * NSF grant CNS-1050226 (Multilayer Network Resilience Analysis and Experimentation on GENI),
 * US Department of Defense (DoD), and ITTC at The University of Kansas.
 */

#include "dsr-helper.h"
#include "../../network/helper/node-container.h"
#include "../../network/model/node.h"
#include "../../core/model/callback.h"
#include "../../core/model/ptr.h"
#include "../../core/model/log.h"
#include "../../internet/model/tcp-l4-protocol.h"
#include "../../internet/model/udp-l4-protocol.h"
#include "../model/dsr-options.h"
#include "../model/dsr-routing.h"
#include "../../internet/model/ipv4-route.h"
#include "../../network/model/node-list.h"
#include "../../core/model/names.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("DsrHelper");

DsrHelper::DsrHelper ()
{
  NS_LOG_FUNCTION (this);
  m_agentFactory.SetTypeId ("ns3::dsr::DsrRouting");
}

DsrHelper::DsrHelper (const DsrHelper &o)
  : m_agentFactory (o.m_agentFactory)
{
  NS_LOG_FUNCTION (this);
}

DsrHelper::~DsrHelper ()
{
  NS_LOG_FUNCTION (this);
}

DsrHelper*
DsrHelper::Copy (void) const
{
  NS_LOG_FUNCTION (this);
  return new DsrHelper (*this);
}

Ptr<ns3::dsr::DsrRouting>
DsrHelper::Create (Ptr<Node> node) const
{
  NS_LOG_FUNCTION (this);
  Ptr<ns3::dsr::DsrRouting> agent = m_agentFactory.Create<ns3::dsr::DsrRouting> ();
  // deal with the downtargets, install UdpL4Protocol, TcpL4Protocol, Icmpv4L4Protocol
  Ptr<UdpL4Protocol> udp = node->GetObject<UdpL4Protocol> ();
  agent->SetDownTarget (udp->GetDownTarget ());
  udp->SetDownTarget (MakeCallback (&dsr::DsrRouting::Send, agent));
  Ptr<TcpL4Protocol> tcp = node->GetObject<TcpL4Protocol> ();
  tcp->SetDownTarget (MakeCallback (&dsr::DsrRouting::Send, agent));
  Ptr<Icmpv4L4Protocol> icmp = node->GetObject<Icmpv4L4Protocol> ();
  icmp->SetDownTarget (MakeCallback (&dsr::DsrRouting::Send, agent));
  node->AggregateObject (agent);
  return agent;
}

void
DsrHelper::Set (std::string name, const AttributeValue &value)
{
  m_agentFactory.Set (name, value);
}

} // namespace ns3
