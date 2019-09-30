/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2007, 2008 University of Washington
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
 * Author: George Riley <riley@ece.gatech.edu>
 */

#include <iostream>

#include "point-to-point-remote-channel.h"
#include "point-to-point-net-device.h"
#include "../../network/model/packet.h"
#include "../../core/model/simulator.h"
#include "../../core/model/log.h"
#include "../../mpi/model/mpi-interface.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("PointToPointRemoteChannel");

NS_OBJECT_ENSURE_REGISTERED (PointToPointRemoteChannel);

TypeId
PointToPointRemoteChannel::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PointToPointRemoteChannel")
    .SetParent<PointToPointChannel> ()
    .SetGroupName ("PointToPoint")
    .AddConstructor<PointToPointRemoteChannel> ()
  ;
  return tid;
}

PointToPointRemoteChannel::PointToPointRemoteChannel ()
  : PointToPointChannel ()
{
}

PointToPointRemoteChannel::~PointToPointRemoteChannel ()
{
}

bool
PointToPointRemoteChannel::TransmitStart (
  Ptr<const Packet> p,
  Ptr<PointToPointNetDevice> src,
  Time txTime)
{
  NS_LOG_FUNCTION (this << p << src);
  NS_LOG_LOGIC ("UID is " << p->GetUid () << ")");

  IsInitialized ();

  uint32_t wire = src == GetSource (0) ? 0 : 1;
  Ptr<PointToPointNetDevice> dst = GetDestination (wire);

#ifdef NS3_MPI
  // Calculate the rxTime (absolute)
  Time rxTime = Simulator::Now () + txTime + GetDelay ();
  MpiInterface::SendPacket (p->Copy (), rxTime, dst->GetNode ()->GetId (), dst->GetIfIndex ());
#else
  NS_FATAL_ERROR ("Can't use distributed simulator without MPI compiled in");
#endif
  return true;
}

} // namespace ns3
