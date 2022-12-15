//
// Created by Gabriel Ferreira(@gabrielcarvfer) on 2/10/22.
//

#include <map>
#include <string>


#include "ns3/core-module.h"
#include "ns3/lte-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/mobility-module.h"
#include "ns3/applications-module.h"

#include "ns3/PubSubInfra.h"
#include "ns3/xApp.h"
#include "ns3/E2AP.h"

NS_LOG_COMPONENT_DEFINE("TestE2AP");

using namespace ns3;


void CheckConnected(E2AP * node)
{
  NS_ASSERT_MSG(node->m_socket, node->m_endpointRoot+" could not connect to E2T");
}

void CheckEndpointRegistered(std::string endpoint)
{
  NS_ASSERT(E2AP::m_endpointToSubscribers.find(endpoint) != E2AP::m_endpointToSubscribers.end());
}

void CheckEndpointNotRegistered(std::string endpoint)
{
  NS_ASSERT(E2AP::m_endpointToSubscribers.find(endpoint) == E2AP::m_endpointToSubscribers.end());
}

void CheckEndpointSubscribed(std::string nodeRootEndpoint, std::string endpoint)
{
  auto subscribers = E2AP::m_endpointToSubscribers.find (endpoint)->second;
  NS_ASSERT (std::find (subscribers.begin (), subscribers.end (), nodeRootEndpoint) != subscribers.end ());
}

void CheckEndpointUnsubscribed(std::string nodeRootEndpoint, std::string endpoint)
{
  auto subscribers = E2AP::m_endpointToSubscribers.find (endpoint)->second;
  NS_ASSERT (std::find (subscribers.begin (), subscribers.end (), nodeRootEndpoint) == subscribers.end ());
}

void CheckEndpointUnsubscribedRetainsData(E2AP* node, std::string endpoint)
{
    auto kpmIt = node->m_kpmToEndpointStorage.find(E2AP::getSubEndpoint(E2AP::getEndpointRoot(endpoint), endpoint));
    NS_ASSERT(kpmIt != node->m_kpmToEndpointStorage.end());

    auto subscriberIt = kpmIt->second.find(E2AP::getEndpointRoot(endpoint));
    NS_ASSERT(subscriberIt != kpmIt->second.end());
}

void CheckEndpointPeriodicReport(E2AP* node, std::string kpm, std::string endpointRoot)
{
  auto kpmIt = node->m_kpmToEndpointStorage.find(kpm);
  NS_ASSERT_MSG (kpmIt != node->m_kpmToEndpointStorage.end(), "KPM periodic report was not received: " + kpm);
  auto reportingE2NodeIt = kpmIt->second.find(endpointRoot);
  NS_ASSERT_MSG(reportingE2NodeIt != kpmIt->second.end(), endpointRoot + " periodic report for KPM " + kpm + " was not received");
}

int main()
{
  // Testes de conexão de nós
  GlobalValue::Bind ("ChecksumEnabled", BooleanValue (true));

  uint16_t numberOfUes = 1;
  uint16_t numberOfEnbs = 3;
  uint16_t numBearersPerUe = 0;
  double distance = 200.0;                                        // m
  double yForUe = 500.0;                                          // m
  double speed = 1;//20;                                              // m/s
  double enbTxPowerDbm = 46.0;

  // change some default attributes so that they are reasonable for
  // this scenario, but do this before processing command line
  // arguments, so that the user is allowed to override these settings
  Config::SetDefault("ns3::UdpClient::Interval", TimeValue(MilliSeconds(10)));
  Config::SetDefault("ns3::UdpClient::MaxPackets", UintegerValue(1000000));
  Config::SetDefault("ns3::LteHelper::UseIdealRrc", BooleanValue(true));

  Ptr<LteHelper> lteHelper = CreateObject<LteHelper>();
  Ptr<PointToPointEpcHelper> epcHelper = CreateObject<PointToPointEpcHelper>();
  epcHelper->SetAttribute("S1uLinkEnablePcap", BooleanValue(true));
  lteHelper->SetEpcHelper(epcHelper);
  lteHelper->SetSchedulerType("ns3::RrFfMacScheduler");

  lteHelper->SetHandoverAlgorithmType ("ns3::NoOpHandoverAlgorithm"); // select an algorithm that does nothing
  //lteHelper->SetHandoverAlgorithmType("ns3::A2A4RsrqHandoverAlgorithm");
  //lteHelper->SetHandoverAlgorithmAttribute("ServingCellThreshold", UintegerValue(30));
  //lteHelper->SetHandoverAlgorithmAttribute("NeighbourCellOffset", UintegerValue(1));

  //  lteHelper->SetHandoverAlgorithmType ("ns3::A3RsrpHandoverAlgorithm");
  //  lteHelper->SetHandoverAlgorithmAttribute ("Hysteresis",
  //                                            DoubleValue (3.0));
  //  lteHelper->SetHandoverAlgorithmAttribute ("TimeToTrigger",
  //                                            TimeValue (MilliSeconds (256)));

  Ptr<Node> pgw = epcHelper->GetPgwNode();
  Ptr<Node> sgw = epcHelper->GetSgwNode();

  // Create a single RemoteHost
  NodeContainer remoteHostContainer;
  remoteHostContainer.Create(1);
  Ptr<Node> remoteHost = remoteHostContainer.Get(0);
  InternetStackHelper internet;
  internet.Install(remoteHostContainer);

  // Create the Internet
  PointToPointHelper p2ph;
  p2ph.SetDeviceAttribute("DataRate", DataRateValue(DataRate("100Gb/s")));
  p2ph.SetDeviceAttribute("Mtu", UintegerValue(1500));
  p2ph.SetChannelAttribute("Delay", TimeValue(Seconds(0.010)));
  NetDeviceContainer internetDevices = p2ph.Install(pgw, remoteHost);
  Ipv4AddressHelper ipv4h;
  ipv4h.SetBase("1.0.0.0", "255.0.0.0");
  Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign(internetDevices);
  Ipv4Address remoteHostAddr = internetIpIfaces.GetAddress(1);

  // Routing of the Internet Host (towards the LTE network)
  Ipv4StaticRoutingHelper ipv4RoutingHelper;
  Ptr<Ipv4StaticRouting> remoteHostStaticRouting =
      ipv4RoutingHelper.GetStaticRouting(remoteHost->GetObject<Ipv4>());
  // interface 0 is localhost, 1 is the p2p device
  remoteHostStaticRouting->AddNetworkRouteTo(Ipv4Address("7.0.0.0"), Ipv4Mask("255.0.0.0"), 1);

  /*
     * Network topology:
     *
     *      |     + --------------------------------------------------------->
     *      |     UE
     *      |
     *      |               d                   d                   d
     *    y |     |-------------------x-------------------x-------------------
     *      |     |                 eNodeB              eNodeB
     *      |   d |
     *      |     |
     *      |     |                                             d = distance
     *            o (0, 0, 0)                                   y = yForUe
   */

  NodeContainer ueNodes;
  NodeContainer enbNodes;
  enbNodes.Create(numberOfEnbs);
  ueNodes.Create(numberOfUes);

  // Install Mobility Model in eNB
  Ptr<ListPositionAllocator> enbPositionAlloc = CreateObject<ListPositionAllocator>();
  for (uint16_t i = 1; i < numberOfEnbs+1; i++)// i = 1 => UE is in the middle of two eNBs
  {
      Vector enbPosition(distance * (i + 1), distance, 0);
      enbPositionAlloc->Add(enbPosition);
  }
  MobilityHelper enbMobility;
  enbMobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
  enbMobility.SetPositionAllocator(enbPositionAlloc);
  enbMobility.Install(enbNodes);

  // Install Mobility Model in UE
  MobilityHelper ueMobility;
  ueMobility.SetMobilityModel("ns3::ConstantVelocityMobilityModel");
  ueMobility.Install(ueNodes);
  ueNodes.Get(0)->GetObject<MobilityModel>()->SetPosition(Vector(0, yForUe, 0));
  ueNodes.Get(0)->GetObject<ConstantVelocityMobilityModel>()->SetVelocity(Vector(speed, 0, 0));

  // Install LTE Devices in eNB and UEs
  Config::SetDefault("ns3::LteEnbPhy::TxPower", DoubleValue(enbTxPowerDbm));
  NetDeviceContainer enbLteDevs = lteHelper->InstallEnbDevice(enbNodes);
  NetDeviceContainer ueLteDevs = lteHelper->InstallUeDevice(ueNodes);

  // Install the IP stack on the UEs
  internet.Install(ueNodes);
  Ipv4InterfaceContainer ueIpIfaces;
  ueIpIfaces = epcHelper->AssignUeIpv4Address(NetDeviceContainer(ueLteDevs));

  // Attach all UEs to the first eNodeB
  for (uint16_t i = 0; i < numberOfUes; i++)
  {
      lteHelper->Attach(ueLteDevs.Get(i), enbLteDevs.Get(0));
  }

  NS_LOG_LOGIC("setting up applications");

  // Install and start applications on UEs and remote host
  uint16_t dlPort = 10000;
  uint16_t ulPort = 20000;

  // randomize a bit start times to avoid simulation artifacts
  // (e.g., buffer overflows due to packet transmissions happening
  // exactly at the same time)
  Ptr<UniformRandomVariable> startTimeSeconds = CreateObject<UniformRandomVariable>();
  startTimeSeconds->SetAttribute("Min", DoubleValue(0));
  startTimeSeconds->SetAttribute("Max", DoubleValue(0.010));

  for (uint32_t u = 0; u < numberOfUes; ++u)
  {
      Ptr<Node> ue = ueNodes.Get(u);
      // Set the default gateway for the UE
      Ptr<Ipv4StaticRouting> ueStaticRouting =
          ipv4RoutingHelper.GetStaticRouting(ue->GetObject<Ipv4>());
      ueStaticRouting->SetDefaultRoute(epcHelper->GetUeDefaultGatewayAddress(), 1);

      for (uint32_t b = 0; b < numBearersPerUe; ++b)
      {
          ++dlPort;
          ++ulPort;

          ApplicationContainer clientApps;
          ApplicationContainer serverApps;

          NS_LOG_LOGIC("installing UDP DL app for UE " << u);
          UdpClientHelper dlClientHelper(ueIpIfaces.GetAddress(u), dlPort);
          clientApps.Add(dlClientHelper.Install(remoteHost));
          PacketSinkHelper dlPacketSinkHelper("ns3::UdpSocketFactory",
                                              InetSocketAddress(Ipv4Address::GetAny(), dlPort));
          serverApps.Add(dlPacketSinkHelper.Install(ue));

          NS_LOG_LOGIC("installing UDP UL app for UE " << u);
          UdpClientHelper ulClientHelper(remoteHostAddr, ulPort);
          clientApps.Add(ulClientHelper.Install(ue));
          PacketSinkHelper ulPacketSinkHelper("ns3::UdpSocketFactory",
                                              InetSocketAddress(Ipv4Address::GetAny(), ulPort));
          serverApps.Add(ulPacketSinkHelper.Install(remoteHost));

          Ptr<EpcTft> tft = Create<EpcTft>();
          EpcTft::PacketFilter dlpf;
          dlpf.localPortStart = dlPort;
          dlpf.localPortEnd = dlPort;
          tft->Add(dlpf);
          EpcTft::PacketFilter ulpf;
          ulpf.remotePortStart = ulPort;
          ulpf.remotePortEnd = ulPort;
          tft->Add(ulpf);
          EpsBearer bearer(EpsBearer::NGBR_VIDEO_TCP_DEFAULT);
          lteHelper->ActivateDedicatedEpsBearer(ueLteDevs.Get(u), bearer, tft);

          Time startTime = Seconds(startTimeSeconds->GetValue());
          serverApps.Start(startTime);
          clientApps.Start(startTime);

      } // end for b
  }

  // Add X2 interface
  lteHelper->AddX2Interface(enbNodes);

  // Configura regra de encaminhamento para eNBs que não sejam o primeiro
  for(unsigned i = 1; i < numberOfEnbs; i++)
    {
      Ipv4StaticRoutingHelper ipv4RoutingHelper;
      Ptr<Ipv4StaticRouting> remoteHostStaticRouting =
          ipv4RoutingHelper.GetStaticRouting(enbNodes.Get (i)->GetObject<Ipv4>());
      remoteHostStaticRouting->AddNetworkRouteTo(Ipv4Address("10.0.0.6"), Ipv4Mask("255.255.255.252"), 1);
    }

  E2AP e2t;
  NS_ASSERT(e2t.m_instanceId == 0);
  NS_ASSERT(e2t.m_endpointRoot == "/E2Node/0");

  E2AP e2n1;
  NS_ASSERT(e2n1.m_instanceId == 1);
  NS_ASSERT(e2n1.m_endpointRoot == "/E2Node/1");

  NS_ASSERT(E2AP::m_endpointRootToInstance.find("/E2Node/0")->second == static_cast<PubSubInfra*>(&e2t));

  // Depois de instalar aplicações, conseguiremos obter seus endereços de IP para
  // estabelecer os sockets TCP
  sgw->AddApplication(&e2t);
  enbNodes.Get(0)->AddApplication(&e2n1);

  /*
   * E2T                        E2Node1
   *  │                            │
   *  │                            │
   *  ├─────┐                      │
   *  │     │ 0.5s Connect         │
   *  │     │ (open socket         │
   *  │◄────┘  and listen)         │
   *  │                            │
   *  │◄───────────────────────────┤
   *  │        1s Connect          │
   *  │        (register           │
   *  │         to RIC)            │
   *  │                            │
   *  ├───────────────────────────►│
   *  │    1.5s CheckConnected     │
   *  │    (check if connection    │
   *  │     was established)       │
   *  ▼                            ▼
   *  t                            t
   */
  Simulator::Schedule(Seconds(0.5), &E2AP::Connect, &e2t);
  Simulator::Schedule(Seconds(1), &E2AP::Connect, &e2n1);
  Simulator::Schedule(Seconds(1.5), &CheckConnected, &e2n1);

  // Testes de registros de endpoints bem-sucedidos
  Simulator::Schedule (Seconds(2.0), &E2AP::RegisterEndpoint, &e2t, "//teste");
  Simulator::Schedule (Seconds(2.0), &E2AP::RegisterEndpoint, &e2n1, "/teste2");
  Simulator::Schedule (Seconds(2.5), &CheckEndpointRegistered, "/E2Node/0/teste");
  Simulator::Schedule (Seconds(2.5), &CheckEndpointRegistered, "/E2Node/1/teste2");

  // Testes de registros de endpoints mal-sucedidos
  Simulator::Schedule (Seconds(3.0), &E2AP::RegisterEndpoint, &e2t, "//teste");
  Simulator::Schedule (Seconds(3.0), &E2AP::RegisterEndpoint, &e2n1, "/teste2");

  // Testes de atualizações de endpoints
  Simulator::Schedule (Seconds(3.5), &E2AP::UpdateEndpoint, &e2n1, "/teste2", "/teste3");
  Simulator::Schedule (Seconds(4.0), &CheckEndpointNotRegistered, "/E2Node/1/teste2");
  Simulator::Schedule (Seconds(4.0), &CheckEndpointRegistered, "/E2Node/1/teste3");

  // Testes de remoção de endpoints
  Simulator::Schedule (Seconds(4.5), &E2AP::RemoveEndpoint, &e2n1, "/teste3");
  Simulator::Schedule (Seconds(5.0), &CheckEndpointNotRegistered, "/E2Node/1/teste3");

  // Teste de subscrição em endpoints
  Simulator::Schedule (Seconds(5.5), &E2AP::RegisterEndpoint, &e2n1, "/");
  Simulator::Schedule (Seconds(6.0), &E2AP::SubscribeToEndpoint, &e2t, "/E2Node/1/");
  Simulator::Schedule (Seconds(6.5), &CheckEndpointSubscribed, e2t.m_endpointRoot, "/E2Node/1/");

  // Teste de recebimento de medições periódicas
  Simulator::Schedule (Seconds(7.6), &CheckEndpointPeriodicReport, &e2t, "/", "/E2Node/1");

  // Teste de cancelamento de subscrição em endpoints vindo do RIC
  Simulator::Schedule (Seconds(8.0), &E2AP::UnsubscribeToEndpoint, &e2t, "/E2Node/1/");
  Simulator::Schedule (Seconds(8.5), &CheckEndpointUnsubscribed, e2t.m_endpointRoot, "/E2Node/1/");

  // Tentar cancelar subscrição já cancelada (cheque nos logs por SUBSCRIPTION_DELETE_FAILURE)
  Simulator::Schedule (Seconds(9.0), &E2AP::UnsubscribeToEndpoint, &e2t, "/E2Node/1/");

  // Publicar endpoints padrão
  Simulator::Schedule(Seconds(10), &E2AP::RegisterDefaultEndpoints, &e2n1);

  // Assinar endpoints padrão
  Simulator::Schedule(Seconds(12), &E2AP::SubscribeToDefaultEndpoints, &e2t, e2n1);

  // Teste de cancelamento de subscrição
  Simulator::Schedule (Seconds(14.0), &E2AP::UnsubscribeToEndpoint, &e2t, "/E2Node/1/KPM/HO.SrcCellQual.RSRQ");
  Simulator::Schedule (Seconds(14.5), &CheckEndpointUnsubscribed, e2t.m_endpointRoot, "/E2Node/1/KPM/HO.SrcCellQual.RSRQ");
  Simulator::Schedule (Seconds(14.5), &CheckEndpointUnsubscribedRetainsData, &e2t, "/E2Node/1/KPM/HO.SrcCellQual.RSRQ");

  // Teste reinscrever na mesma subscrição
  Simulator::Schedule (Seconds(15.5), &E2AP::SubscribeToEndpoint, &e2t, "/E2Node/1/KPM/HO.SrcCellQual.RSRQ");
  Simulator::Schedule (Seconds(16.0), &CheckEndpointSubscribed, e2t.m_endpointRoot, "/E2Node/1/KPM/HO.SrcCellQual.RSRQ");
  Simulator::Schedule (Seconds(16.0), &CheckEndpointUnsubscribedRetainsData, &e2t, "/E2Node/1/KPM/HO.SrcCellQual.RSRQ");

  Simulator::Stop(Seconds(18.0));
  Simulator::Run();
  Simulator::Destroy();
  return 0;
}