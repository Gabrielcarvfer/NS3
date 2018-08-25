//
// Created by Gabriel Ferreira (@gabrielcarvfer) on 28/05/2018.
//

/*
 *
 * In this scenario, we have a single UE and eNB,
 *  also linked by a p2p connection, which the UE
 *  uses to transmit sensing data to the eNB
 *
 */

#include <ns3/core-module.h>
#include <ns3/lte-module.h>
#include <ns3/internet-module.h>
#include <ns3/mobility-module.h>
#include <ns3/applications-module.h>

//Para netanim
#include <ns3/netanim-module.h>
#include <ns3/bs-net-device.h>
#include <ns3/csma-module.h>
#include <ns3/uan-module.h>
#include <ns3/point-to-point-module.h>
#include <cstdint>
#include <ns3/spectrum-module.h>

#include "ns3/wifi-module.h"

using namespace ns3;

#include <map>
#include <ns3/olsr-helper.h>

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

    //LogComponentEnableAll(LOG_LEVEL_DEBUG);

    double simTime = 30;
    double distance = 60.0;
    double interPacketInterval = 25;

    NodeContainer allNodes;

    //1 Configura EPC e PGW
    Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();
    Ptr<PointToPointEpcHelper>  epcHelper = CreateObject<PointToPointEpcHelper> ();
    lteHelper->SetEpcHelper (epcHelper);
    Ptr<Node> pgw = epcHelper->GetPgwNode ();
    allNodes.Add(pgw);

    NodeContainer remoteHostContainer;
    remoteHostContainer.Create (1);
    allNodes.Add(remoteHostContainer);

    NodeContainer ueNodes;
    NodeContainer enbNodes;
    enbNodes.Create(1); // Macro cell
    ueNodes.Create(1); // Femtocell
    allNodes.Add(enbNodes);
    allNodes.Add(ueNodes);

// City positions
// Unaí         50000, 50000, 0
// Natalândia   66000, 94000, 0

    Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
    positionAlloc->Add (Vector (    0.0,     0.0,  0.0));  // 0 - Remote Host
    positionAlloc->Add (Vector (   10.0,     0.0,  0.0));  // 1 - PGW
    positionAlloc->Add (Vector (50000.0, 50000.0,  0.0));  // 2 - eNB 1
    //positionAlloc->Add (Vector (  0.0, 150.0,  0.0));  // 3 - eNB 2
    positionAlloc->Add (Vector (66000.0, 94000.0,  0.0));  // 4 - UE 1
    //positionAlloc->Add (Vector (110.0,  89.0,  0.0));  // 5 - UE 2

    MobilityHelper mobility;
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.SetPositionAllocator(positionAlloc);
    mobility.Install(allNodes);


    //2 Cria nó que representa "internet" (fonte/saída de tráfego externo)
    Ptr<Node> remoteHost = remoteHostContainer.Get (0);
    InternetStackHelper internet;
    internet.Install (remoteHostContainer);

    //2 Cria internet ligando nó externo ao PGW
    PointToPointHelper p2ph;
    p2ph.SetDeviceAttribute ("DataRate", DataRateValue (DataRate ("100Gb/s")));
    p2ph.SetDeviceAttribute ("Mtu", UintegerValue (1500));
    p2ph.SetChannelAttribute ("Delay", TimeValue (Seconds (0.010)));
    NetDeviceContainer internetDevices = p2ph.Install (pgw, remoteHost);

    //3 Configura endereço do PGW e nó externo (subrede 1.0.0.0/8)
    Ipv4AddressHelper ipv4h;
    ipv4h.SetBase ("1.0.0.0", "255.0.0.0");
    Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign (internetDevices);

    // interface 0 is localhost, 1 is the p2p device
    Ipv4Address remoteHostAddr = internetIpIfaces.GetAddress (1);
    //std::cout << "IP " << remoteHostAddr << std::endl;

    //4 Configura roteamento estático entre IP interno e externo do PGW (7.0.0.0 e 1.0.0.0)
    Ipv4StaticRoutingHelper ipv4RoutingHelper;
    Ptr<Ipv4StaticRouting> remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting (remoteHost->GetObject<Ipv4> ());
    remoteHostStaticRouting->AddNetworkRouteTo (Ipv4Address ( "7.0.0.0"), Ipv4Mask ("255.0.0.0"), 1);
    //remoteHostStaticRouting->AddNetworkRouteTo (Ipv4Address ("10.0.0.0"), Ipv4Mask ("255.0.0.0"), 1);


    //Ptr<Ipv4StaticRouting> pgwStaticRouting = ipv4RoutingHelper.GetStaticRouting(pgw->GetObject<Ipv4>());
    //pgwStaticRouting->AddNetworkRouteTo (Ipv4Address( "1.0.0.0"),Ipv4Mask("255.0.0.0"),0);
    //pgwStaticRouting->AddNetworkRouteTo (Ipv4Address( "7.0.0.0"),Ipv4Mask("255.0.0.0"),1);
    //pgwStaticRouting->AddNetworkRouteTo (Ipv4Address("10.0.0.0"),Ipv4Mask("255.0.0.0"),3);




    //6 Instala dispositivos LTE aos nós

    // use 0dB Pathloss, since we are testing only the antenna gain
    lteHelper->SetAttribute ("PathlossModel", StringValue ("ns3::ConstantSpectrumPropagationLossModel"));
    lteHelper->SetPathlossModelAttribute ("Loss", DoubleValue (0.0));

    lteHelper->SetEnbAntennaModelType ("ns3::CosineAntennaModel");
    lteHelper->SetEnbAntennaModelAttribute ("Orientation", DoubleValue (0.0));
    lteHelper->SetEnbAntennaModelAttribute ("Beamwidth",   DoubleValue (35.0));
    lteHelper->SetEnbAntennaModelAttribute ("MaxGain",     DoubleValue (400.0));

    NetDeviceContainer enbLteDevs = lteHelper->InstallEnbDevice (enbNodes);
    NetDeviceContainer ueLteDevs = lteHelper->InstallUeDevice (ueNodes);

    //Ptr<AntennaModel> enbAntenna = enbLteDevs.Get(0)->GetObject<std::map<uint8_t, Ptr<ComponentCarrierEnb>>->second->GetObject<LteEnbPhy>()->GetDlSpectrumPhy()->GetRxAntenna();


    //7 Instala pilha IP nos UE
    internet.Install (ueNodes);
    Ipv4InterfaceContainer ueIpIface;
    ueIpIface = epcHelper->AssignUeIpv4Address (NetDeviceContainer (ueLteDevs));

    //Ptr<Ipv4StaticRouting> enbStaticRouting = ipv4RoutingHelper.GetStaticRouting (enbNodes.Get(0)->GetObject<Ipv4> ());
    //enbStaticRouting->AddNetworkRouteTo (Ipv4Address("7.0.0.0"),Ipv4Mask("255.0.0.0"),1);

    //8 Configura endereço IP dos UEs e instala aplicações
    for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
    {
        Ptr<Node> ueNode = ueNodes.Get (u);
        // Set the default gateway for the UE
        Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting (ueNode->GetObject<Ipv4> ());
        ueStaticRouting->SetDefaultRoute (epcHelper->GetUeDefaultGatewayAddress (), 1);
    }

    //9 Associa UE ao eNodeB
    lteHelper->Attach (ueLteDevs.Get(0), enbLteDevs.Get(0));

    //10 Cria nós wifi
    NodeContainer wifiStaNodes, wifiApNodes;
    wifiApNodes.Add(ueNodes);

    wifiStaNodes.Create(10);

    positionAlloc->Add (Vector (66000.0, 94000.0,  0.0));

    for (unsigned sta = 0; sta < 10; sta++)
    {
        NodeContainer nc;
        nc.Add(wifiStaNodes.Get(sta));
        setup_mobility2(&nc, "ns3::ConstantPositionMobilityModel", 66000.0,  94000.0, 0.0, 998.0);
    }

// 2. Create channel for communication
    SpectrumChannelHelper channel = SpectrumChannelHelper::Default();
    SpectrumWifiPhyHelper phy = SpectrumWifiPhyHelper::Default();

    channel.AddPropagationLoss("ns3::RangePropagationLossModel","MaxRange",DoubleValue(5000.0));

    phy.SetChannel(channel.Create());

    WifiHelper wifi;
    wifi.SetRemoteStationManager("ns3::AarfWifiManager");

    NqosWifiMacHelper mac = NqosWifiMacHelper::Default();

// 3. Set up MAC
// 3a. Set up MAC for base stations
    Ssid ssid = Ssid("ns-3-ssid");
    mac.SetType("ns3::StaWifiMac",
                "Ssid", SsidValue(ssid),
                "ActiveProbing", BooleanValue(false));
    NetDeviceContainer staDevices;

    staDevices = wifi.Install(phy, mac, wifiStaNodes);

// 3b. Set up MAC for AP
    mac.SetType("ns3::ApWifiMac",
                "Ssid", SsidValue(ssid),
                "BeaconGeneration", BooleanValue(true),
                "BeaconInterval", TimeValue(Seconds(5)));
    NetDeviceContainer apDevices;
    apDevices = wifi.Install(phy, mac, wifiApNodes);

    InternetStackHelper stack;
    stack.Install(wifiStaNodes);

    NetDeviceContainer wifiDevices;
    wifiDevices.Add(apDevices);
    wifiDevices.Add(staDevices);

    Ipv4InterfaceContainer wifiInterfaces = epcHelper->AssignUeIpv4Address (wifiDevices);

    Ptr<Node> ApNode = wifiApNodes.Get (0);

    // Set the default gateway for the UE
    Ptr<Ipv4StaticRouting> apStaticRouting = ipv4RoutingHelper.GetStaticRouting (ueNodes.Get(0)->GetObject<Ipv4>());
    //apStaticRouting->AddNetworkRouteTo("10.0.0.0", "255.0.0.0", 1);
    //apStaticRouting->AddNetworkRouteTo(" 7.0.0.0", "255.0.0.0", 2);
    //std::cout << "Gateway AP-UE " << ueNodes.Get(0)->GetObject<Ipv4>()->GetAddress(1,0).GetLocal()<<std::endl;
    //apStaticRouting->SetDefaultRoute(ueNodes.Get(0)->GetObject<Ipv4>()->GetAddress(0,0).GetLocal(),2);
    apStaticRouting->AddNetworkRouteTo("7.0.0.0", Ipv4Mask("255.255.255.252"),2);
    //apStaticRouting->AddNetworkRouteTo(ueNodes.Get(0)->GetObject<Ipv4>()->GetAddress(1,0).GetLocal(),
    //                                    Ipv4Mask("255.255.255.253"), 2);
    //for (int i = 0; i < 2; i++)
    //    std::cout << "Enb IP " << enbNodes.Get(0)->GetObject<Ipv4>()->GetAddress(i,0).GetLocal()<<std::endl;
    //Ptr<Ipv4StaticRouting> enbStaticRouting = ipv4RoutingHelper.GetStaticRouting (enbNodes.Get(0)->GetObject<Ipv4>());

    //enbStaticRouting->AddNetworkRouteTo(enbNodes.Get(0)->GetObject<Ipv4>()->GetAddress(0,0).GetLocal(),
    //                                    Ipv4Mask("255.0.0.0"),
    //                                    0);

    Ptr<EpcSgwPgwApplication> sgwpgwapp = pgw->GetApplication(0)->GetObject<EpcSgwPgwApplication>();
    //8 Configura endereço IP dos UEs e instala aplicações
    for (uint32_t u = 0; u < wifiStaNodes.GetN (); ++u)
    {
        Ptr<Node> staNode = wifiStaNodes.Get (u);
        // Set the default gateway for the UE
        Ptr<Ipv4StaticRouting> staStaticRouting = ipv4RoutingHelper.GetStaticRouting (staNode->GetObject<Ipv4> ());
        staStaticRouting->SetDefaultRoute (ueNodes.Get(0)->GetObject<Ipv4>()->GetAddress(2,0).GetLocal(), 1);

        epcHelper->AddUe(staDevices.Get(u), 310150123450000+u);
        sgwpgwapp->SetUeAddress(310150123450000+u, staNode->GetObject<Ipv4>()->GetAddress(1,0).GetLocal(), ueNodes.Get(0)->GetObject<Ipv4>()->GetAddress(2,0).GetLocal());
    }


    //10 Configura, instala e inicia aplicações em APs e servidor remoto
    uint16_t serverPort = 9;

    // 8a. Create and setup applications (traffic sink)
    UdpEchoServerHelper echoServer(serverPort); // Port # 9
    ApplicationContainer serverApps = echoServer.Install(remoteHost);


    UdpEchoServerHelper echoServer1(2152); // GPRS port
    serverApps.Add(echoServer1.Install(remoteHost));

    serverApps.Start(Seconds(0.5));


    UdpEchoClientHelper echoClient(remoteHost->GetObject<Ipv4>()->GetAddress(1,0).GetLocal(), serverPort);
    echoClient.SetAttribute("MaxPackets", UintegerValue(10000));
    echoClient.SetAttribute("Interval", TimeValue(Seconds(1.)));
    echoClient.SetAttribute("PacketSize", UintegerValue(1024));

    ApplicationContainer clientApps;
    clientApps.Add(echoClient.Install(wifiStaNodes));
    clientApps.Start (Seconds (0.7));

    lteHelper->EnableTraces ();
    phy.EnablePcapAll ("natalandia", true);
    p2ph.EnablePcapAll("natalandia_p2p", true);

    //Ipv4GlobalRoutingHelper::PopulateRoutingTables ();


    //Exportar animação para o Netanim
    BaseStationNetDevice b;
    SubscriberStationNetDevice s;
    CsmaNetDevice c;
    UanNetDevice u;

    AnimationInterface anim("anim.xml");
    anim.SetMaxPktsPerTraceFile(0xFFFFFFFF);
    anim.EnablePacketMetadata(true);

    anim.UpdateNodeDescription (pgw, "PGW"); // Optional
    anim.UpdateNodeColor (pgw, 0, 255, 0); // Optional
    anim.UpdateNodeSize(pgw->GetId(), 100, 100);


    anim.UpdateNodeDescription (remoteHost, "Internet"); // Optional
    anim.UpdateNodeColor (remoteHost, 0, 255, 0); // Optional
    anim.UpdateNodeSize(remoteHost->GetId(), 100, 100);


    anim.UpdateNodeDescription (enbNodes.Get(0), "Enb"); // Optional
    anim.UpdateNodeColor (enbNodes.Get(0), 0, 255, 0); // Optional
    anim.UpdateNodeSize(enbNodes.Get(0)->GetId(), 100, 100);

    for (uint32_t i = 0; i < wifiApNodes.GetN (); ++i)
    {
        std::stringstream ss;
        ss << "AP" << i;
        anim.UpdateNodeDescription (wifiApNodes.Get (i), ss.str()); // Optional
        anim.UpdateNodeColor (wifiApNodes.Get (i), 0, 255, 0); // Optional
        anim.UpdateNodeSize(wifiApNodes.Get(i)->GetId(), 10, 10);
    }

    for (uint32_t i = 0; i < wifiStaNodes.GetN (); ++i)
    {
        std::stringstream ss;
        ss << "STA" << i;
        anim.UpdateNodeDescription (wifiStaNodes.Get (i), ss.str()); // Optional
        anim.UpdateNodeColor (wifiStaNodes.Get (i), 0, 255, 0); // Optional
        anim.UpdateNodeSize(wifiStaNodes.Get(i)->GetId(), 10, 10);
    }


    //Ipv4GlobalRoutingHelper g;
    //Ptr<OutputStreamWrapper> routingStream = Create<OutputStreamWrapper>
    //        ("dynamic-global-routing.routes", std::ios::out);
    //g.PrintRoutingTableAllAt (Seconds (12), routingStream);

    for (int i = 0; i < allNodes.GetN(); i++)
        for (int j = 0; j < allNodes.Get(i)->GetObject<Ipv4>()->GetNInterfaces(); j++)
            std::cout << "Node " << i << " ID "<< allNodes.Get(i)->GetId()<< " IP " << allNodes.Get(i)->GetObject<Ipv4>()->GetAddress(j,0).GetLocal()<<std::endl;

    //Rodar o simulador
    Simulator::Stop(Seconds(simTime)); // Rodar simulação por 10 segundos
    Simulator::Run();
    Simulator::Destroy();

    return 0;
}