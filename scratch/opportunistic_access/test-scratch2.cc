//
// Created by  Gabriel Ferreira (@gabrielcarvfer) on 17-Jan-19.
//



#include <ns3/core-module.h>
#include <ns3/lte-module.h>
#include <ns3/internet-module.h>
#include <ns3/mobility-module.h>
#include <ns3/applications-module.h>
#include <ns3/flow-monitor-module.h>
#include <ns3/wifi-module.h>
#include <ns3/olsr-helper.h>

//Para netanim
#include <ns3/netanim-module.h>
#include <ns3/bs-net-device.h>
#include <ns3/csma-module.h>
#include <ns3/uan-module.h>
#include <ns3/point-to-point-module.h>
#include <cstdint>
#include <ns3/spectrum-module.h>



using namespace ns3;

#include <map>
#include <ns3/contrib-haraldott-module.h>

void setup_mobility2(NodeContainer * nodes, std::string mobilityModel, double x, double y, double z, double radius)
{
    MobilityHelper mobility;

    Ptr<RandomBoxPositionAllocator> randomPositionAlloc = CreateObject<RandomBoxPositionAllocator> ();
    Ptr<UniformRandomVariable> xVal = CreateObject<UniformRandomVariable> ();
    xVal->SetAttribute ("Min", DoubleValue (x-radius));
    xVal->SetAttribute ("Max", DoubleValue (x+radius));
    Ptr<UniformRandomVariable> yVal = CreateObject<UniformRandomVariable> ();
    yVal->SetAttribute ("Min", DoubleValue (y-radius));
    yVal->SetAttribute ("Max", DoubleValue (y+radius));
    Ptr<UniformRandomVariable> zVal = CreateObject<UniformRandomVariable> ();
    zVal->SetAttribute ("Min", DoubleValue (z));
    zVal->SetAttribute ("Max", DoubleValue (z));

    mobility.SetPositionAllocator("ns3::RandomBoxPositionAllocator",
                                  "X", PointerValue (xVal),
                                  "Y", PointerValue (yVal),
                                  "Z", PointerValue (zVal)
    );
    mobility.SetMobilityModel(mobilityModel);
    mobility.Install(*nodes);
}

void print_ips(Ptr<Ipv4> ips)
{
    std::cout << "IPs" << std::endl;
    for (int i = 0; i < ips->GetNInterfaces(); i++)
    {
        std::cout << ips->GetAddress(i+1,0).GetLocal() << std::endl;
    }
    std::cout << std::endl;
}

//Simple network setup
int main()
{
    std::ios::sync_with_stdio(false);

    //LogComponentEnableAll(LOG_LEVEL_DEBUG);

    double simTime = 2;
    double distance = 60.0;
    double interPacketInterval = 25;

    //Config::SetDefault ("ns3::LteEnbRrc::SrsPeriodicity", UintegerValue(40));


    NodeContainer allNodes;
    bool useCa = true;

    //1 Configura EPC e PGW
    Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();
    lteHelper->SetAttribute("Scheduler", StringValue("ns3::CqaFfMacScheduler")); //QoS aware scheduler
    //lteHelper->SetAttribute("Scheduler", StringValue("ns3::NnFfMacScheduler")); //NN scheduler
    //lteHelper->SetAttribute("UseCa", BooleanValue(true)); // Carrier aggregation
    //lteHelper->SetAttribute("NumberOfComponentCarriers", UintegerValue(4)); // Carrier aggregation


    Ptr<PointToPointEpcHelper>  epcHelper = CreateObject<PointToPointEpcHelper> ();
    lteHelper->SetEpcHelper (epcHelper);
    Ptr<Node> pgw = epcHelper->GetPgwNode ();
    allNodes.Add(pgw);

    //2 Cria nó remoto
    NodeContainer remoteHostContainer;
    remoteHostContainer.Create (1);
    allNodes.Add(remoteHostContainer);

    //3 Cria eNodeBs e UEs
    NodeContainer ueNodesUnai, ueNodesNatalandia, allUeNodes;
    NodeContainer enbNodes;
    enbNodes.Create(1); // Macro cell
    ueNodesUnai.Create(1);
    ueNodesNatalandia.Create(10);
    allUeNodes.Add(ueNodesUnai);
    allUeNodes.Add(ueNodesNatalandia);
    allNodes.Add(enbNodes);
    //allNodes.Add(ueNodes);

// City positions
// Unaí         50000, 50000, 0
// Natalândia   66000, 94000, 0

    //4 Aloca posições dos dispositivos
    Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
    positionAlloc->Add (Vector (   10.0,     0.0,  0.0));  // 0 - PGw
    positionAlloc->Add (Vector (    0.0,     0.0,  0.0));  // 1 - Internet
    positionAlloc->Add (Vector (50000.0, 50000.0,  0.0));  // 2 - eNB

    //5 Instala mobilidade dos dispositivos (parados)
    MobilityHelper mobility;
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.SetPositionAllocator(positionAlloc);
    mobility.Install(allNodes);

    //setup_mobility2(&ueNodesUnai, "ns3::RandomWalk2dMobilityModel", 50000.0, 50000.0, 0.0, 1000.0);
    //setup_mobility2(&ueNodesNatalandia, "ns3::RandomWalk2dMobilityModel", 55000.0, 50000.0, 0.0, 3000.0);

    setup_mobility2(&ueNodesUnai,       "ns3::ConstantPositionMobilityModel", 50000.0, 50000.0, 0.0, 1000.0);
    setup_mobility2(&ueNodesNatalandia, "ns3::ConstantPositionMobilityModel", 55000.0, 50000.0, 0.0, 3000.0);

    allNodes.Add(allUeNodes);



    //6 Instala pilha IP no nó que representa "internet" (fonte/saída de tráfego externo)
    Ptr<Node> remoteHost = remoteHostContainer.Get (0);
    InternetStackHelper internet;
    internet.Install (remoteHostContainer);

    //7 Cria "internet" ligando nó externo ao PGW
    PointToPointHelper p2ph;
    p2ph.SetDeviceAttribute ("DataRate", DataRateValue (DataRate ("100Gb/s")));
    p2ph.SetDeviceAttribute ("Mtu", UintegerValue (1500));
    p2ph.SetChannelAttribute ("Delay", TimeValue (Seconds (0.010)));
    NetDeviceContainer internetDevices = p2ph.Install (pgw, remoteHost);

    //8 Configura endereço do PGW e nó externo (subrede 1.0.0.0/8)
    Ipv4AddressHelper ipv4h;
    ipv4h.SetBase ("1.0.0.0", "255.0.0.0");
    Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign (internetDevices);

    // interface 0 is localhost/loopback, 1 is the p2p device
    Ipv4Address remoteHostAddr = internetIpIfaces.GetAddress (1);

    //9 Configura roteamento estático entre IP interno e externo do PGW (7.0.0.0 e 1.0.0.0)
    //      Permitindo que nós externos (internet) consigam mandar pacotes para UEs
    Ipv4StaticRoutingHelper ipv4RoutingHelper;
    Ptr<Ipv4StaticRouting> remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting (remoteHost->GetObject<Ipv4> ());
    remoteHostStaticRouting->AddNetworkRouteTo (Ipv4Address ( "7.0.0.0"), Ipv4Mask ("255.0.0.0"), 1);



    //10 Configura antena e modelo de atenuação LTE, de maneira picareteada para garantir alcance absurdo
    //lteHelper->SetAttribute ("PathlossModel", StringValue ("ns3::ConstantSpectrumPropagationLossModel"));
    //lteHelper->SetPathlossModelAttribute ("Loss", DoubleValue (0.0));
    //lteHelper->SetEnbAntennaModelType ("ns3::CosineAntennaModel");
    //lteHelper->SetEnbAntennaModelAttribute ("Orientation", DoubleValue (0.0));
    //lteHelper->SetEnbAntennaModelAttribute ("Beamwidth",   DoubleValue (35.0));
    //lteHelper->SetEnbAntennaModelAttribute ("MaxGain",     DoubleValue (30.0));

    //11 Instala eNodeB e UE
    NetDeviceContainer enbLteDevs = lteHelper->InstallEnbDevice (enbNodes);
    NetDeviceContainer ueLteDevs = lteHelper->InstallUeDevice (allUeNodes);


    //12 Instala pilha IP nos UE e dá endereços controlados pelo EPC
    internet.Install (allUeNodes);
    Ipv4InterfaceContainer ueIpIface;
    ueIpIface = epcHelper->AssignUeIpv4Address (NetDeviceContainer (ueLteDevs));

    //13 Modifica UEs para adicionar o gateway correspondendo ao EPC
    // (conexão entre UE/eNB é feita através de uma aplicação e tunelamento GPRS)
    for (uint32_t u = 0; u < allUeNodes.GetN (); ++u)
    {
        Ptr<Node> ueNode = allUeNodes.Get (u);
        Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting (ueNode->GetObject<Ipv4> ());
        ueStaticRouting->SetDefaultRoute (epcHelper->GetUeDefaultGatewayAddress (), 1);
    }

    //14 Associa UE ao eNodeB
    lteHelper->Attach (ueLteDevs, enbLteDevs.Get(0));

    //enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE;
    //EpsBearer bearer (q);
    //lteHelper->ActivateDataRadioBearer (ueLteDevs, bearer);

    Ptr<EpcTft> tft = Create<EpcTft> ();
    //if (epcDl)
    //  {
    //    EpcTft::PacketFilter dlpf;
    //    dlpf.localPortStart = dlPort;
    //    dlpf.localPortEnd = dlPort;
    //    tft->Add (dlpf);
    //  }
    //if (epcUl)
    //  {
    EpcTft::PacketFilter ulpf;
    ulpf.remotePortStart = 9;
    ulpf.remotePortEnd = 9;
    tft->Add (ulpf);
    //  }

    //if (epcDl || epcUl)
    //{
    EpsBearer bearer (EpsBearer::GBR_GAMING);
    lteHelper->ActivateDedicatedEpsBearer (ueLteDevs, bearer, tft);
    //}



    // 26 Configura e instala aplicações
    uint16_t serverPort = 9;

    UdpEchoServerHelper echoServer(serverPort); // Porta #9
    ApplicationContainer serverApps = echoServer.Install(remoteHost);

    serverApps.Start(Seconds(0.1));

    //ECHO APP
    Ipv4Address serverAddress = remoteHost->GetObject<Ipv4>()->GetAddress(1,0).GetLocal();
    UdpEchoClientHelper echoClient(serverAddress, serverPort);
    echoClient.SetAttribute("MaxPackets", UintegerValue(1000000));
    echoClient.SetAttribute("Interval", TimeValue(MilliSeconds(500)));
    echoClient.SetAttribute("PacketSize", UintegerValue(100));

    ApplicationContainer clientApps;
    clientApps.Add(echoClient.Install(ueNodesUnai));

    UdpEchoClientHelper echoClient2(serverAddress, serverPort);
    echoClient2.SetAttribute("MaxPackets", UintegerValue(1000000));
    echoClient2.SetAttribute("Interval", TimeValue(MilliSeconds(200)));
    echoClient2.SetAttribute("PacketSize", UintegerValue(10));

    clientApps.Add(echoClient2.Install(ueNodesNatalandia));

    //DASH APP
    /*
    uint64_t segmentDuration = 1;
    std::string adaptationAlgo = "festive"; // festive | panda | tobasco
    std::string segmentSizeFilePath = "../../contrib/haraldott/dash/examples/segmentsizes.txt";
 
    TcpStreamServerHelper serverHelper(serverPort+1);
    ApplicationContainer serverApp = serverHelper.Install(remoteHost);
    serverApp.Start(Seconds(0.5));
 
    // Install TCP/UDP Transmitter on the station
    TcpStreamClientHelper clientHelper(serverAddress, serverPort+1);
    clientHelper.SetAttribute("SegmentDuration", UintegerValue(segmentDuration));
    clientHelper.SetAttribute("SegmentSizeFilePath", StringValue(segmentSizeFilePath));
    clientHelper.SetAttribute("NumberOfClients", UintegerValue(1));
    clientHelper.SetAttribute("SimulationId", UintegerValue(0));
    std::vector<std::pair<Ptr<Node>, std::string> > clients;
    for (NodeContainer::Iterator i = ueNodes.Begin(); i != ueNodes.End(); ++i)
    {
        std::pair<Ptr<Node>, std::string> client(*i, adaptationAlgo);
        clients.push_back(client);
    }
 
    clientApps.Add(clientHelper.Install(clients));
    */
    clientApps.Start (Seconds (0.2));



    //27 Coleta traces LTE, WiFi e P2P
    lteHelper->EnableTraces ();
    //p2ph.EnablePcapAll("natalandia_p2p", true);

    //31 Flow monitor
    Ptr<FlowMonitor> flowMonitor;
    FlowMonitorHelper flowHelper;
    flowMonitor = flowHelper.InstallAll();


    //32 Rodar o simulador
    Simulator::Stop(Seconds(simTime));
    Simulator::Run();

    flowMonitor->SerializeToXmlFile("flow.xml", true, true);

    Simulator::Destroy();

    return 0;
}