//
// Created by Gabriel Ferreira(@gabrielcarvfer) on 31/08/22.
//

#include <algorithm>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "PubSubInfra.h"
#include "ns3/core-module.h"
#include "ns3/lte-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/mobility-module.h"

NS_LOG_COMPONENT_DEFINE("TestPubSubInfra");

using namespace ns3;

int main()
{
  // Testes básicos
  xApp xapp0;
  NS_ASSERT(xapp0.m_instanceId == 0);
  NS_ASSERT(xapp0.m_endpointRoot == "/xApp/0");

  xApp xapp1;
  NS_ASSERT(xapp1.m_instanceId == 1);
  NS_ASSERT(xapp1.m_endpointRoot == "/xApp/1");

  NS_ASSERT(xApp::m_endpointRootToInstance.find("/xApp/0")->second == static_cast<PubSubInfra<xApp>*>(&xapp0));

  //todo: Testando operator==
  // NS_ASSERT(xApp::m_endpointRootToInstance.find("/xApp/0")->second == xapp0);
  // NS_ASSERT(xApp::m_endpointRootToInstance.find("/xApp/0")->second == &xapp0);

  E2Node e2t;
  NS_ASSERT(e2t.m_instanceId == 0);
  NS_ASSERT(e2t.m_endpointRoot == "/E2Node/0");

  E2Node e2n1;
  NS_ASSERT(e2n1.m_instanceId == 1);
  NS_ASSERT(e2n1.m_endpointRoot == "/E2Node/1");

  NS_ASSERT(E2Node::m_endpointRootToInstance.find("/E2Node/0")->second == static_cast<PubSubInfra<E2Node>*>(&e2t));

  // Testes de registros de endpoint
  e2t.RegisterEndpoint("//teste");
  NS_ASSERT(E2Node::m_endpointToSubscribers.find("/E2Node/0/teste") != E2Node::m_endpointToSubscribers.end());

  e2n1.RegisterEndpoint("/teste2");
  NS_ASSERT(E2Node::m_endpointToSubscribers.find("/E2Node/1/teste2") != E2Node::m_endpointToSubscribers.end());

  // Teste de subscrição em endpoints
  e2t.SubscribeToEndpoint("/E2Node/1/teste2");
  {
    auto subscribers = E2Node::m_endpointToSubscribers.find ("/E2Node/1/teste2")->second;
    NS_ASSERT (std::find (subscribers.begin (), subscribers.end (),
                          static_cast<PubSubInfra<E2Node> *> (&e2t)) != subscribers.end ());
  }


  // Testes de serialização e deserialização JSON
  Json RPC_CALL = Json::parse(
              R"({
                "PUBLIC_RPC": {
                                "ENDPOINT": "/E2Node/0/teste",
                                "BODY": {
                                           "KEY" : "value"
                                        }
                              }
              })"
      );
  Json test = Json::parse("{\"PUBLIC_RPC\":{\"BODY\":{\"KEY\":\"value\"},\"ENDPOINT\":\"/E2Node/0/teste\"}}");
  NS_ASSERT(RPC_CALL == test);

  Ptr<Packet> post_packaging = E2Node::encodeJsonToPacket(RPC_CALL);
  Json post_depackaging = E2Node::decodePacketToJson(post_packaging);
  NS_ASSERT(RPC_CALL == post_depackaging);

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

  // Depois de instalar aplicações, conseguiremos obter seus endereços de IP para
  // estabelecer os sockets TCP
  sgw->AddApplication(&e2t);
  enbNodes.Get(0)->AddApplication(&e2n1);

  // Testes de recebimento de requisições RPC no nó 0 (E2T, xApp router)
  // Subscrição remota (abrir socket, mandar requisição, aguardar confirmação)
  e2n1.SubscribeToEndpoint("/E2Node/0/teste");

  // Publishing remoto (abrir socket, mandar requisição para nó 0, repostar a partir do nó 0 para destinatários)
  // e2n1.PublishToEndpoint("/E2Node/1/teste2", "{\"pimba\" : \"true\"}");
  Simulator::Schedule(Seconds(0.5), &E2Node::Connect, &e2t);
  Simulator::Schedule(Seconds(1), &E2Node::Connect, &e2n1);
  Simulator::Schedule(Seconds(1.5), &E2Node::PublishToEndpointSubscribers, &e2n1, "/E2Node/1/teste2", "{\"pimba\" : \"true\"}");

  Simulator::Stop(Seconds(10));
  Simulator::Run();
  Simulator::Destroy();
  return 0;
}