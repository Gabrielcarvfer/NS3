/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 Strasbourg University
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
 * Author: David Gross <gdavid.devel@gmail.com>
 *         Sebastien Vincent <vincent@clarinet.u-strasbg.fr>
 */

// Network topology
// //
// //             n0   R    n1
// //             |    _    |
// //             ====|_|====
// //                router
// // - R sends RA to n0's subnet (2001:1::/64 and 2001:ABCD::/64);
// // - R interface to n0 has two addresses with following prefixes 2001:1::/64 and 2001:ABCD::/64;
// // - R sends RA to n1's subnet (2001:2::/64);
// // - n0 ping6 n1.
// //
// // - Tracing of queues and packet receptions to file "radvd-two-prefix.tr"

#include <fstream>
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-apps-module.h"

#include "ns3/ipv6-routing-table-entry.h"
#include "ns3/radvd.h"
#include "ns3/radvd-interface.h"
#include "ns3/radvd-prefix.h"
#include "ns3/ipv6-static-routing-helper.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("RadvdTwoPrefixExample");

/**
 * \class IpAddressHelper
 * \brief Helper to print a node's IP addresses.
 */
class IpAddressHelper
{
public:
  /**
   * \brief Print the node's IP addresses.
   * \param n the node
   */
  inline void PrintIpAddresses (Ptr<Node>& n)
  {
    Ptr<Ipv6> ipv6 = n->GetObject<Ipv6> ();
    uint32_t nInterfaces = ipv6->GetNInterfaces();

    std::cout << "Node: " << ipv6->GetObject<Node> ()->GetId ()
        << " Time: " << Simulator::Now ().GetSeconds () << "s "
        << "IPv6 addresses" << std::endl;
    std::cout << "(Interface index, Address index)\t" << "IPv6 Address" << std::endl;

    for (uint32_t i = 0; i < nInterfaces; i++)
      {
        for (uint32_t j = 0; j < ipv6->GetNAddresses(i); j++)
          {
            std::cout << "(" << int(i) << "," << int(j) << ")\t" << ipv6->GetAddress(i,j) << std::endl;
          }
      }
    std::cout << std::endl;
  }
};

int main (int argc, char** argv)
{
  bool verbose = false;

  CommandLine cmd;
  cmd.AddValue ("verbose", "turn on log components", verbose);
  cmd.Parse (argc, argv);

  if (verbose)
    {
      LogComponentEnable ("Ipv6L3Protocol", LOG_LEVEL_ALL);
      LogComponentEnable ("Ipv6RawSocketImpl", LOG_LEVEL_ALL);
      LogComponentEnable ("Icmpv6L4Protocol", LOG_LEVEL_ALL);
      LogComponentEnable ("Ipv6StaticRouting", LOG_LEVEL_ALL);
      LogComponentEnable ("Ipv6Interface", LOG_LEVEL_ALL);
      LogComponentEnable ("RadvdApplication", LOG_LEVEL_ALL);
      LogComponentEnable ("Ping6Application", LOG_LEVEL_ALL);
    }

  NS_LOG_INFO ("Create nodes.");
  Ptr<Node> n0 = CreateObject<Node> ();
  Ptr<Node> r = CreateObject<Node> ();
  Ptr<Node> n1 = CreateObject<Node> ();

  NodeContainer net1 (n0, r);
  NodeContainer net2 (r, n1);
  NodeContainer all (n0, r, n1);

  NS_LOG_INFO ("Create IPv6 Internet Stack");
  InternetStackHelper internetv6;
  internetv6.Install (all);

  NS_LOG_INFO ("Create channels.");
  CsmaHelper csma;
  csma.SetChannelAttribute ("DataRate", DataRateValue (5000000));
  csma.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (2)));
  NetDeviceContainer d1 = csma.Install (net1); /* n0 - R */
  NetDeviceContainer d2 = csma.Install (net2); /* R - n1 */

  NS_LOG_INFO ("Create networks and assign IPv6 Addresses.");
  Ipv6AddressHelper ipv6;

  /* first subnet */
  ipv6.SetBase (Ipv6Address ("2001:1::"), Ipv6Prefix (64));
  NetDeviceContainer tmp;
  tmp.Add (d1.Get (0)); /* n0 */
  Ipv6InterfaceContainer iic1 = ipv6.AssignWithoutAddress (tmp); /* n0 interface */

  NetDeviceContainer tmp2;
  tmp2.Add (d1.Get (1)); /* R */
  Ipv6InterfaceContainer iicr1 = ipv6.Assign (tmp2); /* R interface to the first subnet is just statically assigned */
  iicr1.SetForwarding (0, true);
  iic1.Add (iicr1);

  /* add another IPv6 address for second prefix advertised on first subnet */
  ipv6.SetBase (Ipv6Address ("2001:ABCD::2"), Ipv6Prefix (64));
  ipv6.Assign (tmp2);

  /* second subnet R - n1 */
  ipv6.SetBase (Ipv6Address ("2001:2::"), Ipv6Prefix (64));
  NetDeviceContainer tmp3;
  tmp3.Add (d2.Get (0)); /* R */
  Ipv6InterfaceContainer iicr2 = ipv6.Assign (tmp3); /* R interface */
  iicr2.SetForwarding (0, true);

  NetDeviceContainer tmp4;
  tmp4.Add (d2.Get (1)); /* n1 */
  Ipv6InterfaceContainer iic2 = ipv6.AssignWithoutAddress (tmp4); 
  iic2.Add (iicr2);

  /* radvd configuration */
  RadvdHelper radvdHelper;
  /* R interface (n0 - R) */
  radvdHelper.AddAnnouncedPrefix(iic1.GetInterfaceIndex (1), Ipv6Address("2001:ABCD::0"), 64);
  radvdHelper.AddAnnouncedPrefix(iic1.GetInterfaceIndex (1), Ipv6Address("2001:1::0"), 64);

  // Set some non-standard timers so the simulation is not taking ages
  Ptr<RadvdInterface> routerInterface = radvdHelper.GetRadvdInterface(iic1.GetInterfaceIndex (1));
  routerInterface->SetMaxRtrAdvInterval (2000);
  routerInterface->SetMinRtrAdvInterval (1000);
  RadvdInterface::RadvdPrefixList prefixList = routerInterface->GetPrefixes ();
  for (RadvdInterface::RadvdPrefixListI iter = prefixList.begin(); iter != prefixList.end(); iter++)
    {
      (*iter)->SetPreferredLifeTime (3);
      (*iter)->SetValidLifeTime (5);
    }

  /* R interface (R - n1) */
  radvdHelper.AddAnnouncedPrefix(iic2.GetInterfaceIndex (1), Ipv6Address("2001:2::0"), 64);

  // Set some non-standard timers so the simulation is not taking ages
  routerInterface = radvdHelper.GetRadvdInterface(iic2.GetInterfaceIndex (1));
  routerInterface->SetMaxRtrAdvInterval (2000);
  routerInterface->SetMinRtrAdvInterval (1000);
  prefixList = routerInterface->GetPrefixes ();
  for (RadvdInterface::RadvdPrefixListI iter = prefixList.begin(); iter != prefixList.end(); iter++)
    {
      (*iter)->SetPreferredLifeTime (3);
      (*iter)->SetValidLifeTime (5);
    }

  ApplicationContainer radvdApps = radvdHelper.Install(r);
  radvdApps.Start (Seconds (1.0));
  radvdApps.Stop (Seconds (2.0));

  /* Create a Ping6 application to send ICMPv6 echo request from n0 to n1 via R */
  uint32_t packetSize = 1024;
  uint32_t maxPacketCount = 8;
  Time interPacketInterval = Seconds (1.);
  Ping6Helper ping6;

  /* ping6.SetLocal (iic1.GetAddress (0, 1)); */
  ping6.SetRemote (Ipv6Address ("2001:2::200:ff:fe00:4")); /* should be n1 address after autoconfiguration */
  ping6.SetIfIndex (iic1.GetInterfaceIndex (0));

  ping6.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
  ping6.SetAttribute ("Interval", TimeValue (interPacketInterval));
  ping6.SetAttribute ("PacketSize", UintegerValue (packetSize));
  ApplicationContainer apps = ping6.Install (net1.Get (0));
  apps.Start (Seconds (2.0));
  apps.Stop (Seconds (9.0));

  Ipv6StaticRoutingHelper routingHelper;
  Ptr<OutputStreamWrapper> routingStream = Create<OutputStreamWrapper> (&std::cout);
  routingHelper.PrintRoutingTableAt (Seconds (2.0), n0, routingStream);
  routingHelper.PrintRoutingTableAt (Seconds (10.0), n0, routingStream);

  IpAddressHelper ipAddressHelper;
  /* RA should be received, two prefixes + routes + default route should be present */
  Simulator::Schedule (Seconds (2.0), &IpAddressHelper::PrintIpAddresses, &ipAddressHelper, n0);
  /* at the end, RA addresses and routes should be cleared */
  Simulator::Schedule (Seconds (10.0), &IpAddressHelper::PrintIpAddresses, &ipAddressHelper, n0);

  AsciiTraceHelper ascii;
  csma.EnableAsciiAll (ascii.CreateFileStream ("radvd-two-prefix.tr"));
  csma.EnablePcapAll (std::string ("radvd-two-prefix"), true);

  NS_LOG_INFO ("Run Simulation.");
  Simulator::Run ();
  Simulator::Destroy ();
  NS_LOG_INFO ("Done.");
}

