#include "ns3/core-module.h"
#include "ns3/network-module.h"

#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/lte-module.h"
#include "ns3/config-store.h"
#include "ns3/contrib-notopoloko-module.h"
#include <fstream>

//NS_LOG_COMPONENT_DEFINE ("POC_LOADER");

// static void
// CwndChange (uint32_t oldCwnd, uint32_t newCwnd)
// {
//   NS_LOG_UNCOND (Simulator::Now ().GetSeconds () << "\t" << newCwnd);
// }

// void PathLossChange(ns3::Ptr< const ns3::SpectrumPhy > txPhy, ns3::Ptr< const ns3::SpectrumPhy > rxPhy, double lossDb) {
//   NS_LOG_UNCOND("Loss in DB: " << lossDb);
// }

// static void
// RxDrop (Ptr<const Packet> p)
// {
//   NS_LOG_UNCOND ("RxDrop at " << Simulator::Now ().GetSeconds ());
// }

int 
main (int argc, char *argv[])
{
  uint16_t numberOfNodes = 1;
  double simTime = 100;
  double radius = 10.0;
  // bool useCa = false;
  bool genTraces = false;

  // Command line arguments
  ns3::CommandLine cmd;
  cmd.AddValue("numberOfNodes", "Number of UE nodes", numberOfNodes);
  cmd.AddValue("simTime", "Total duration of the simulation [s])", simTime);
  cmd.AddValue("radius", "Cell radius [m]", radius);
  cmd.AddValue("genTraces", "Generate log traces from internet node", genTraces);
  // cmd.AddValue("useCa", "Whether to use carrier aggregation.", useCa);
  cmd.Parse(argc, argv);

  // if (useCa)
  //  {
  //    Config::SetDefault ("ns3::LteHelper::UseCa", BooleanValue (useCa));
  //    Config::SetDefault ("ns3::LteHelper::NumberOfComponentCarriers", UintegerValue (2));
  //    Config::SetDefault ("ns3::LteHelper::EnbComponentCarrierManager", StringValue ("ns3::RrComponentCarrierManager"));
  //  }

  ns3::Ptr< ns3::LteHelper > lteHelper = ns3::CreateObject< ns3::LteHelper > ();
  ns3::Ptr<ns3::PointToPointEpcHelper>  epcHelper = ns3::CreateObject<ns3::PointToPointEpcHelper> ();
  lteHelper->SetEpcHelper (epcHelper);
  // lteHelper->SetAttribute("Mtu", UintegerValue(1500));
  // lteHelper->SetAttribute ("PathlossModel", ns3::StringValue ("PachecoPropagationLossModel"));
  // ConfigStore inputConfig;
  // inputConfig.ConfigureDefaults();

  // parse again so you can override default values from the command line
  cmd.Parse(argc, argv);

  ns3::Ptr<ns3::Node> pgw = epcHelper->GetPgwNode ();

   // Create a single RemoteHost
  ns3::NodeContainer remoteHostContainer;
  remoteHostContainer.Create (1);
  ns3::Ptr<ns3::Node> remoteHost = remoteHostContainer.Get (0);
  ns3::InternetStackHelper internet;
  internet.Install (remoteHostContainer);

  // Create the Internet
  ns3::PointToPointHelper p2ph;
  p2ph.SetDeviceAttribute ("DataRate", ns3::DataRateValue (ns3::DataRate ("100Gb/s")));
  p2ph.SetDeviceAttribute ("Mtu", ns3::UintegerValue (1500));
  p2ph.SetChannelAttribute ("Delay", ns3::TimeValue (ns3::Seconds (0.010)));
  ns3::NetDeviceContainer internetDevices = p2ph.Install (pgw, remoteHost);
  ns3::Ipv4AddressHelper ipv4h;
  ipv4h.SetBase ("1.0.0.0", "255.0.0.0");
  ns3::Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign (internetDevices);
  // interface 0 is localhost, 1 is the p2p device
  ns3::Ipv4Address remoteHostAddr = internetIpIfaces.GetAddress (1);

  ns3::Ipv4StaticRoutingHelper ipv4RoutingHelper;
  ns3::Ptr<ns3::Ipv4StaticRouting> remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting (remoteHost->GetObject<ns3::Ipv4> ());
  remoteHostStaticRouting->AddNetworkRouteTo (ns3::Ipv4Address ("7.0.0.0"), ns3::Ipv4Mask ("255.0.0.0"), 1);

  ns3::NodeContainer ueNodes;
  ns3::NodeContainer enbNodes;
  enbNodes.Create(1);
  ueNodes.Create(numberOfNodes);

  // Install Mobility Model
  ns3::Ptr<ns3::ListPositionAllocator> positionAlloc = ns3::CreateObject<ns3::ListPositionAllocator> ();
  positionAlloc->Add (ns3::Vector(0, 0, 0));
  ns3::MobilityHelper mobility;
  mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
  mobility.SetPositionAllocator(positionAlloc);
  mobility.Install(enbNodes);


  ns3::MobilityHelper uemobility;
  uemobility.SetPositionAllocator ("ns3::UniformDiscPositionAllocator",
                                    "X", ns3::DoubleValue (0.0),
                                    "Y", ns3::DoubleValue (0.0),
                                    "rho", ns3::DoubleValue (radius));
  uemobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  uemobility.Install (ueNodes);

  ns3::MobilityHelper::GetDistanceSquaredBetween(enbNodes.Get(0), ueNodes.Get(0));
  // Install LTE Devices to the nodes
  ns3::NetDeviceContainer enbLteDevs = lteHelper->InstallEnbDevice (enbNodes);
  ns3::NetDeviceContainer ueLteDevs = lteHelper->InstallUeDevice (ueNodes);

  // Install the IP stack on the UEs
  internet.Install (ueNodes);
  ns3::Ipv4InterfaceContainer ueIpIface;
  ueIpIface = epcHelper->AssignUeIpv4Address (ns3::NetDeviceContainer (ueLteDevs));
  // Assign IP address to UEs, and install applications
  for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
    {
      ns3::Ptr<ns3::Node> ueNode = ueNodes.Get (u);
      // Set the default gateway for the UE
      ns3::Ptr<ns3::Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting (ueNode->GetObject<ns3::Ipv4> ());
      ueStaticRouting->SetDefaultRoute (epcHelper->GetUeDefaultGatewayAddress (), 1);
    }

  // Attach one UE per eNodeB
  lteHelper->Attach(ueLteDevs, enbLteDevs.Get(0));
  // for (uint16_t i = 0; i < numberOfNodes; i++)
  //     {
  //       lteHelper->Attach (ueLteDevs.Get(i), enbLteDevs.Get(i));
  //       // side effect: the default EPS bearer will be activated
  //     }


  // Install and start applications on UEs and remote host
  // uint16_t dlPort = 1234;
  uint16_t ulPort = 2000;
  // uint16_t otherPort = 3000;
  ns3::ApplicationContainer clientVoIPApps, clientIOTApps;
  ns3::ApplicationContainer serverApps;

  ns3::PacketSinkHelper ulPacketSinkHelper ("ns3::TcpSocketFactory", ns3::InetSocketAddress (ns3::Ipv4Address::GetAny (), ulPort));
  serverApps.Add (ulPacketSinkHelper.Install (remoteHost));

  // UdpClientHelper ulClient (remoteHostAddr, ulPort);
  // ulClient.SetAttribute ("Interval", TimeValue (MilliSeconds(interPacketInterval)));
  // ulClient.SetAttribute ("MaxPackets", UintegerValue(1000000));

  // clientApps.Add (ulClient.Install (ueNodes.Get(0)));

  LoaderTrafficHelper loader = LoaderTrafficHelper();
  clientIOTApps = loader.LoadJsonTraffic(ueNodes, remoteHostAddr, ulPort, "voip_charge.json" );
  serverApps.Start (ns3::Seconds (0));
  clientIOTApps.Start (ns3::Seconds (1));
  // lteHelper->EnableTraces ();
  // Uncomment to enable PCAP tracing

    // lteHelper->EnableTraces();
    p2ph.EnablePcapAll("POC-IOT");


  ns3::Simulator::Stop(ns3::Seconds(simTime));
  ns3::Simulator::Run();

  /*GtkConfigStore config;
  config.ConfigureAttributes();*/
  std::cout << "Ending simulation at: " << ns3::Simulator::Now() << std::endl;
  ns3::Simulator::Destroy();
  return 0;
}

