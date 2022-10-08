//
// Created by Gabriel Ferreira(@gabrielcarvfer) on 2/10/22.
//

#include <map>
#include <string>


#include "ns3/core-module.h"
#include "ns3/lte-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/mobility-module.h"

#include "ns3/PubSubInfra.h"
#include "ns3/xApp.h"
#include "ns3/E2AP.h"

NS_LOG_COMPONENT_DEFINE("TestE2Node");

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

int main()
{
  // Testes de conexão de nós
  GlobalValue::Bind ("ChecksumEnabled", BooleanValue (true));

  double distance = 60.0; // metros
  Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();
  Ptr<PointToPointEpcHelper> epcHelper = CreateObject<PointToPointEpcHelper> ();
  epcHelper->SetAttribute("S1uLinkEnablePcap", BooleanValue(true));
  lteHelper->SetEpcHelper (epcHelper);

  Ptr<Node> pgw = epcHelper->GetPgwNode ();
  Ptr<Node> sgw = epcHelper->GetSgwNode();

  // Create a single RemoteHost
  NodeContainer remoteHostContainer;
  remoteHostContainer.Create (1);
  Ptr<Node> remoteHost = remoteHostContainer.Get (0);
  InternetStackHelper internet;
  internet.Install (remoteHostContainer);

  // Create the Internet
  PointToPointHelper p2ph;
  p2ph.SetDeviceAttribute ("DataRate", DataRateValue (DataRate ("100Gb/s")));
  p2ph.SetDeviceAttribute ("Mtu", UintegerValue (1500));
  p2ph.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));
  NetDeviceContainer internetDevices = p2ph.Install (pgw, remoteHost);
  Ipv4AddressHelper ipv4h;
  ipv4h.SetBase ("1.0.0.0", "255.0.0.0");
  Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign (internetDevices);
  // interface 0 is localhost, 1 is the p2p device
  //Ipv4Address remoteHostAddr = internetIpIfaces.GetAddress (1);

  Ipv4StaticRoutingHelper ipv4RoutingHelper;
  Ptr<Ipv4StaticRouting> remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting (remoteHost->GetObject<Ipv4> ());
  remoteHostStaticRouting->AddNetworkRouteTo (Ipv4Address ("7.0.0.0"), Ipv4Mask ("255.0.0.0"), 1);

  NodeContainer ueNodes;
  NodeContainer enbNodes;
  int numNodePairs = 2;
  enbNodes.Create (numNodePairs);
  ueNodes.Create (numNodePairs);

  // Install Mobility Model
  Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
  for (uint16_t i = 0; i < numNodePairs; i++)
    {
      positionAlloc->Add (Vector (distance * i, 0, 0));
    }
  MobilityHelper mobility;
  mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
  mobility.SetPositionAllocator(positionAlloc);
  mobility.Install(enbNodes);
  mobility.Install(ueNodes);

  // Install LTE Devices to the nodes
  NetDeviceContainer enbLteDevs = lteHelper->InstallEnbDevice (enbNodes);
  NetDeviceContainer ueLteDevs = lteHelper->InstallUeDevice (ueNodes);

  // Install the IP stack on the UEs
  internet.Install (ueNodes);
  Ipv4InterfaceContainer ueIpIface;
  ueIpIface = epcHelper->AssignUeIpv4Address (NetDeviceContainer (ueLteDevs));
  // Assign IP address to UEs, and install applications
  for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
    {
      Ptr<Node> ueNode = ueNodes.Get (u);
      // Set the default gateway for the UE
      Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting (ueNode->GetObject<Ipv4> ());
      ueStaticRouting->SetDefaultRoute (epcHelper->GetUeDefaultGatewayAddress (), 1);
    }

  // Attach one UE per eNodeB
  for (uint16_t i = 0; i < numNodePairs; i++)
    {
      lteHelper->Attach (ueLteDevs.Get(i), enbLteDevs.Get(i));
      // side effect: the default EPS bearer will be activated
    }

  //Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

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

  //Simulator::Schedule(Seconds(1.5), &E2AP::PublishToEndpointSubscribers, &e2n1, "/E2Node/1/teste2", "{\"pimba\" : \"true\"}");

  // Teste de cancelamento de subscrição
  Simulator::Stop(Seconds(10));
  Simulator::Run();
  Simulator::Destroy();
  return 0;
}