/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 IITP RAS
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
 * Authors: Pavel Boyko <boyko@iitp.ru>
 */

#pragma once
#include "../../../core/model/test.h"
#include "../../../network/helper/node-container.h"
#include "../../../core/model/nstime.h"

using namespace ns3;
/**
 * \ingroup dot11s-test
 * \ingroup tests
 * 
 * \brief Peering Management Protocol regression test
 * 
 * Initiate scenario with 2 stations. Procedure of opening peer link
 * is the following:
 * \verbatim
 * |----------->|  Beacon
 * |<-----------|  Peer Link Open frame 
 * |----------->|  Peer Link Open frame
 * |----------->|  Peer Link Confirm frame
 * |<-----------|  Peer Link Confirm frame
 * |............|
 * |<---------->|  Other beacons
 * \endverbatim
 */
class PeerManagementProtocolRegressionTest : public TestCase
{
public:
  PeerManagementProtocolRegressionTest ();
  ~PeerManagementProtocolRegressionTest ();

private:
  /// \internal It is important to have pointers here
  NodeContainer * m_nodes;
  /// Simulation time
  Time m_time;

  /// Create nodes function
  void CreateNodes ();
  /// Create devices function
  void CreateDevices ();
  /// Check results function
  void CheckResults ();
  void DoRun ();
};


