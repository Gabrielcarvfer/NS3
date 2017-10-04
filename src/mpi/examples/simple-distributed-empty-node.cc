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
 *
 * This test is equivalent to simple-distributed but tests boundary cases
 * when one of the ranks has no Nodes on it.   When run on two tasks
 * rank 0 will have all the Nodes and rank 1 will be empty:
 * 
 *                 -------   -------
 *                  RANK 0    RANK 0
 *                 ------- | -------
 *                         |
 * n0 ---------|           |           |---------- n6
 *             |           |           |
 * n1 -------\ |           |           | /------- n7
 *            n4 ----------|---------- n5
 * n2 -------/ |           |           | \------- n8
 *             |           |           |
 * n3 ---------|           |           |---------- n9
 *
 *
 * When run on three tasks rank 1 has the left half of the Nodes and rank 2
 * will be empty.
 *
 *                 -------   -------
 *                  RANK 0    RANK 1
 *                 ------- | -------
 *                         |
 * n0 ---------|           |           |---------- n6
 *             |           |           |
 * n1 -------\ |           |           | /------- n7
 *            n4 ----------|---------- n5
 * n2 -------/ |           |           | \------- n8
 *             |           |           |
 * n3 ---------|           |           |---------- n9
 *
 * OnOff clients are placed on each left leaf node. Each right leaf node
 * is a packet sink for a left leaf node.  As a packet travels from one
 * logical processor to another (the link between n4 and n5), MPI messages
 * are passed containing the serialized packet. The message is then
 * deserialized into a new packet and sent on as normal.
 *
 * One packet is sent from each left leaf node.  The packet sinks on the
 * right leaf nodes output logging information when they receive the packet.
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mpi-interface.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/point-to-point-helper.h"
#include "ns3/internet-stack-helper.h"
#include "ns3/ipv4-nix-vector-helper.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/on-off-helper.h"
#include "ns3/packet-sink-helper.h"

#ifdef NS3_MPI
#include <mpi.h>
#endif

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("SimpleDistributed");

int
main (int argc, char *argv[])
{
#ifdef NS3_MPI

  bool nix = true;
  bool nullmsg = false;
  bool tracing = false;

  // Parse command line
  CommandLine cmd;
  cmd.AddValue ("nix", "Enable the use of nix-vector or global routing", nix);
  cmd.AddValue ("nullmsg", "Enable the use of null-message synchronization", nullmsg);
  cmd.AddValue ("tracing", "Enable pcap tracing", tracing);
  cmd.Parse (argc, argv);

  // Distributed simulation setup; by default use granted time window algorithm.
  if(nullmsg) 
    {
      GlobalValue::Bind ("SimulatorImplementationType",
                         StringValue ("ns3::NullMessageSimulatorImpl"));
    } 
  else 
    {
      GlobalValue::Bind ("SimulatorImplementationType",
                         StringValue ("ns3::DistributedSimulatorImpl"));
    }

  MpiInterface::Enable (&argc, &argv);

  LogComponentEnable ("PacketSink", LOG_LEVEL_INFO);

  uint32_t systemId = MpiInterface::GetSystemId ();
  uint32_t systemCount = MpiInterface::GetSize ();

  uint32_t rightHalfSystemId = 777;

  // Check for valid distributed parameters.
  // Must have 2 or 3 tasks.
  if (systemCount == 2)
    {
      rightHalfSystemId = 0;
    }
  else if (systemCount == 3)
    {
      rightHalfSystemId = 1;
    }
  else
    {
      std::cout << "This simulation requires 2 or 3 logical processors." << std::endl;
      return 1;
    }
    
  // Some default values
  Config::SetDefault ("ns3::OnOffApplication::PacketSize", UintegerValue (512));
  Config::SetDefault ("ns3::OnOffApplication::DataRate", StringValue ("1Mbps"));
  Config::SetDefault ("ns3::OnOffApplication::MaxBytes", UintegerValue (512));

  // Create leaf nodes on left with system id 0
  NodeContainer leftLeafNodes;
  leftLeafNodes.Create (4, 0);

  // Create router nodes.  Left router with system id 0, right router
  // with system id dependent on number of processors using
  // rightHalfSystemId
  NodeContainer routerNodes;
  Ptr<Node> routerNode1 = CreateObject<Node> (0);
  Ptr<Node> routerNode2 = CreateObject<Node> (rightHalfSystemId);
  routerNodes.Add (routerNode1);
  routerNodes.Add (routerNode2);

  // Create leaf nodes on left with system id rightHalfSystemId
  NodeContainer rightLeafNodes;
  rightLeafNodes.Create (4, rightHalfSystemId);

  PointToPointHelper routerLink;
  routerLink.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  routerLink.SetChannelAttribute ("Delay", StringValue ("5ms"));

  PointToPointHelper leafLink;
  leafLink.SetDeviceAttribute ("DataRate", StringValue ("1Mbps"));
  leafLink.SetChannelAttribute ("Delay", StringValue ("2ms"));

  // Add link connecting routers
  NetDeviceContainer routerDevices;
  routerDevices = routerLink.Install (routerNodes);

  // Add links for left side leaf nodes to left router
  NetDeviceContainer leftRouterDevices;
  NetDeviceContainer leftLeafDevices;
  for (uint32_t i = 0; i < 4; ++i)
    {
      NetDeviceContainer temp = leafLink.Install (leftLeafNodes.Get (i), routerNodes.Get (0));
      leftLeafDevices.Add (temp.Get (0));
      leftRouterDevices.Add (temp.Get (1));
    }

  // Add links for right side leaf nodes to right router
  NetDeviceContainer rightRouterDevices;
  NetDeviceContainer rightLeafDevices;
  for (uint32_t i = 0; i < 4; ++i)
    {
      NetDeviceContainer temp = leafLink.Install (rightLeafNodes.Get (i), routerNodes.Get (1));
      rightLeafDevices.Add (temp.Get (0));
      rightRouterDevices.Add (temp.Get (1));
    }

  InternetStackHelper stack;
  if (nix)
    {
      Ipv4NixVectorHelper nixRouting;
      stack.SetRoutingHelper (nixRouting); // has effect on the next Install ()
    }

  stack.InstallAll ();

  Ipv4InterfaceContainer routerInterfaces;
  Ipv4InterfaceContainer leftLeafInterfaces;
  Ipv4InterfaceContainer leftRouterInterfaces;
  Ipv4InterfaceContainer rightLeafInterfaces;
  Ipv4InterfaceContainer rightRouterInterfaces;

  Ipv4AddressHelper leftAddress;
  leftAddress.SetBase ("10.1.1.0", "255.255.255.0");

  Ipv4AddressHelper routerAddress;
  routerAddress.SetBase ("10.2.1.0", "255.255.255.0");

  Ipv4AddressHelper rightAddress;
  rightAddress.SetBase ("10.3.1.0", "255.255.255.0");

  // Router-to-Router interfaces
  routerInterfaces = routerAddress.Assign (routerDevices);

  // Left interfaces
  for (uint32_t i = 0; i < 4; ++i)
    {
      NetDeviceContainer ndc;
      ndc.Add (leftLeafDevices.Get (i));
      ndc.Add (leftRouterDevices.Get (i));
      Ipv4InterfaceContainer ifc = leftAddress.Assign (ndc);
      leftLeafInterfaces.Add (ifc.Get (0));
      leftRouterInterfaces.Add (ifc.Get (1));
      leftAddress.NewNetwork ();
    }

  // Right interfaces
  for (uint32_t i = 0; i < 4; ++i)
    {
      NetDeviceContainer ndc;
      ndc.Add (rightLeafDevices.Get (i));
      ndc.Add (rightRouterDevices.Get (i));
      Ipv4InterfaceContainer ifc = rightAddress.Assign (ndc);
      rightLeafInterfaces.Add (ifc.Get (0));
      rightRouterInterfaces.Add (ifc.Get (1));
      rightAddress.NewNetwork ();
    }

  if (!nix)
    {
      Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
    }

  if (tracing == true)
    {
      if (systemId == 0)
        {
          routerLink.EnablePcap("router-left", routerDevices, true);
          leafLink.EnablePcap("leaf-left", leftLeafDevices, true);
        }
      
      if (systemId == rightHalfSystemId)
        {
          routerLink.EnablePcap("router-right", routerDevices, true);
          leafLink.EnablePcap("leaf-right", rightLeafDevices, true);
        }
    }

  // Create a packet sink on the right leafs to receive packets from left leafs
  uint16_t port = 50000;
  if (systemId == rightHalfSystemId)
    {
      Address sinkLocalAddress (InetSocketAddress (Ipv4Address::GetAny (), port));
      PacketSinkHelper sinkHelper ("ns3::UdpSocketFactory", sinkLocalAddress);
      ApplicationContainer sinkApp;
      for (uint32_t i = 0; i < 4; ++i)
        {
          sinkApp.Add (sinkHelper.Install (rightLeafNodes.Get (i)));
        }
      sinkApp.Start (Seconds (1.0));
      sinkApp.Stop (Seconds (5));
    }

  // Create the OnOff applications to send
  if (systemId == 0)
    {
      OnOffHelper clientHelper ("ns3::UdpSocketFactory", Address ());
      clientHelper.SetAttribute
        ("OnTime", StringValue ("ns3::ConstantRandomVariable[Constant=1]"));
      clientHelper.SetAttribute
        ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=0]"));

      ApplicationContainer clientApps;
      for (uint32_t i = 0; i < 4; ++i)
        {
          AddressValue remoteAddress
            (InetSocketAddress (rightLeafInterfaces.GetAddress (i), port));
          clientHelper.SetAttribute ("Remote", remoteAddress);
          clientApps.Add (clientHelper.Install (leftLeafNodes.Get (i)));
        }
      clientApps.Start (Seconds (1.0));
      clientApps.Stop (Seconds (5));
    }

  Simulator::Stop (Seconds (5));
  Simulator::Run ();
  Simulator::Destroy ();
  // Exit the MPI execution environment
  MpiInterface::Disable ();
  return 0;
#else
  NS_FATAL_ERROR ("Can't use distributed simulator without MPI compiled in");
#endif
}
