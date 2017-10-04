/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
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
 */

// Test program for this 3-router scenario, using global routing
//
// (a.a.a.a/32)A<--x.x.x.0/30-->B<--y.y.y.0/30-->C(c.c.c.c/32)

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

#include "ns3/csma-net-device.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-static-routing.h"
#include "ns3/ipv4-global-routing.h"
#include "ns3/ipv4-list-routing.h"
#include "ns3/ipv4-routing-table-entry.h"
#include "ns3/global-router-interface.h"
#include "ns3/ipv4-static-routing-helper.h"
#include "ns3/ipv4-list-routing-helper.h"
#include "ns3/ipv4-global-routing-helper.h"

using namespace ns3;
using std::cout;

NS_LOG_COMPONENT_DEFINE ("GlobalRouterInjectionTest");

int 
main (int argc, char *argv[])
{

  // Allow the user to override any of the defaults and the above
  // DefaultValue::Bind ()s at run-time, via command-line arguments
  CommandLine cmd;
  cmd.Parse (argc, argv);

  Ptr<Node> nA = CreateObject<Node> ();
  Ptr<Node> nB = CreateObject<Node> ();
  Ptr<Node> nC = CreateObject<Node> ();

  NodeContainer c = NodeContainer (nA, nB, nC);

  InternetStackHelper internet;

  // Point-to-point links
  NodeContainer nAnB = NodeContainer (nA, nB);
  NodeContainer nBnC = NodeContainer (nB, nC);

  internet.Install (nAnB);
  Ipv4ListRoutingHelper staticonly;
  Ipv4ListRoutingHelper staticRouting;
  staticonly.Add (staticRouting, 0);
  internet.SetRoutingHelper (staticonly);  // has effect on the next Install ()
  internet.Install (NodeContainer (nC));

  // We create the channels first without any IP addressing information
  PointToPointHelper p2p;
  p2p.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));
  NetDeviceContainer dAdB = p2p.Install (nAnB);

  NetDeviceContainer dBdC = p2p.Install (nBnC);;

  Ptr<CsmaNetDevice> deviceA = CreateObject<CsmaNetDevice> ();
  deviceA->SetAddress (Mac48Address::Allocate ());
  nA->AddDevice (deviceA);

  Ptr<CsmaNetDevice> deviceC = CreateObject<CsmaNetDevice> ();
  deviceC->SetAddress (Mac48Address::Allocate ());
  nC->AddDevice (deviceC);

  // Later, we add IP addresses.
  Ipv4AddressHelper ipv4;
  ipv4.SetBase ("10.1.1.0", "255.255.255.252");
  Ipv4InterfaceContainer iAiB = ipv4.Assign (dAdB);

  ipv4.SetBase ("10.1.1.4", "255.255.255.252");
  Ipv4InterfaceContainer iBiC = ipv4.Assign (dBdC);

  Ptr<Ipv4> ipv4A = nA->GetObject<Ipv4> ();
  Ptr<Ipv4> ipv4B = nB->GetObject<Ipv4> ();
  Ptr<Ipv4> ipv4C = nC->GetObject<Ipv4> ();

  int32_t ifIndexA = ipv4A->AddInterface (deviceA);
  int32_t ifIndexC = ipv4C->AddInterface (deviceC);

  Ipv4InterfaceAddress ifInAddrA = Ipv4InterfaceAddress (Ipv4Address ("172.16.1.1"), Ipv4Mask ("255.255.255.255"));
  ipv4A->AddAddress (ifIndexA, ifInAddrA);
  ipv4A->SetMetric (ifIndexA, 1);
  ipv4A->SetUp (ifIndexA);

  Ipv4InterfaceAddress ifInAddrC = Ipv4InterfaceAddress (Ipv4Address ("192.168.1.1"), Ipv4Mask ("255.255.255.255"));
  ipv4C->AddAddress (ifIndexC, ifInAddrC);
  ipv4C->SetMetric (ifIndexC, 1);
  ipv4C->SetUp (ifIndexC);
 
  // Create router nodes, initialize routing database and set up the routing
  // tables in the nodes.

  // Populate routing tables for nodes nA and nB
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
  // Inject global routes from Node B, including transit network...
  Ptr<GlobalRouter> globalRouterB = nB->GetObject<GlobalRouter> ();
  globalRouterB->InjectRoute ("10.1.1.4", "255.255.255.252");
  // ...and the host in network "C"
  globalRouterB->InjectRoute ("192.168.1.1", "255.255.255.255");

  Ipv4GlobalRoutingHelper::RecomputeRoutingTables ();
  // In addition, nB needs a static route to nC so it knows what to do with stuff
  // going to 192.168.1.1
  Ipv4StaticRoutingHelper ipv4RoutingHelper;
  Ptr<Ipv4StaticRouting> staticRoutingB = ipv4RoutingHelper.GetStaticRouting (ipv4B);
  staticRoutingB->AddHostRouteTo (Ipv4Address ("192.168.1.1"), Ipv4Address ("10.1.1.6"),2);

  // Create the OnOff application to send UDP datagrams of size
  // 210 bytes at a rate of 448 Kb/s
  uint16_t port = 9;   // Discard port (RFC 863)
  OnOffHelper onoff ("ns3::UdpSocketFactory", 
                     Address (InetSocketAddress (ifInAddrC.GetLocal (), port)));
  onoff.SetConstantRate (DataRate (6000));
  ApplicationContainer apps = onoff.Install (nA);
  apps.Start (Seconds (1.0));
  apps.Stop (Seconds (10.0));

  // Create a packet sink to receive these packets
  PacketSinkHelper sink ("ns3::UdpSocketFactory",
                         Address (InetSocketAddress (Ipv4Address::GetAny (), port)));
  apps = sink.Install (nC);
  apps.Start (Seconds (1.0));
  apps.Stop (Seconds (10.0));

  AsciiTraceHelper ascii;
  p2p.EnableAsciiAll (ascii.CreateFileStream ("global-routing-injection32.tr"));
  p2p.EnablePcapAll ("global-routing-injection32");

  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}
