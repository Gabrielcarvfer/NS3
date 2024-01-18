// Copyright (c) 2024 Centre Tecnologic de Telecomunicacions de Catalunya (CTTC)
//
// SPDX-License-Identifier: GPL-2.0-only

//
// Created by Gabriel Ferreira(@gabrielcarvfer) on 1/11/22.
//

#include "MobilityPatterns.h"

#include "ns3/E2AP.h"
#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/lte-module.h"
#include "ns3/mobility-module.h"
#include "ns3/netanim-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/xAppHandoverMaliciousPositioning.h"

#include <map>
#include <string>

NS_LOG_COMPONENT_DEFINE("PrivacySafeguardingScenario");

using namespace ns3;
using namespace oran;

/**
 * \brief Generate a reasonably good seed
 * \return a good seed
 */
unsigned int
good_seed()
{
    unsigned int random_seed, random_seed_a, random_seed_b;
    std::ifstream file("/dev/urandom", std::ios::binary);
    if (file.is_open())
    {
        char* memblock;
        int size = sizeof(int);
        memblock = new char[size];
        file.read(memblock, size);
        file.close();
        random_seed_a = *reinterpret_cast<int*>(memblock);
        delete[] memblock;
    } // end if
    else
    {
        random_seed_a = 0;
    }
    random_seed_b = std::time(0);
    random_seed = random_seed_a xor random_seed_b;
    return random_seed;
} // end good_seed()

int
main(int argc, char** argv)
{
    ns3::RngSeedManager::SetSeed(1);//good_seed());
    std::cout << "Seed " << ns3::RngSeedManager::GetSeed() << std::endl;

    GlobalValue::Bind("ChecksumEnabled", BooleanValue(false));

    uint16_t numberOfUes = 8;
    uint16_t numberOfEnbs = 3;
    uint16_t numBearersPerUe = 1;
    double simTime = 2 * 60;
    double enbTxPowerDbm = 30.0;

    std::stringstream ss;
    ss << "\n\t\tChoose one:\n"
       << "\t 0: Standard 3GPP handover (HO)\n"
       << "\t 1: Malicious HO xApp tracks UEs with RNTI.\n"
       << "\t 2: Malicious HO xApp tracks UEs without RNTI.\n";

    unsigned scenarioi = 0;
    std::string output_csv_filename = "output.csv";
    CommandLine cmd(__FILE__);
    cmd.AddValue("scenario", ss.str(), scenarioi);
    cmd.AddValue("outputFile", "Output csv file name", output_csv_filename);
    cmd.Parse(argc, argv);

    typedef enum SimulationScenarios
    {
        STANDARD_3GPP = 0,
        ORAN_BYPASS,
        ORAN_MALICIOUS_XAPP_WITH_RNTI, 
        ORAN_MALICIOUS_XAPP_WITHOUT_RNTI,
    } SimulationScenarios;

    if (scenarioi > SimulationScenarios::ORAN_MALICIOUS_XAPP_WITHOUT_RNTI)
    {
        std::cerr << "Invalid handover scenario id: " << scenarioi << std::endl;
        return -1;
    }
    SimulationScenarios scenario = static_cast<SimulationScenarios>(scenarioi);

    // change some default attributes so that they are reasonable for
    // this scenario, but do this before processing command line
    // arguments, so that the user is allowed to override these setting
    Config::SetDefault("ns3::LteHelper::UseIdealRrc", BooleanValue(true));

    Ptr<LteHelper> lteHelper = CreateObject<LteHelper>();
    Ptr<PointToPointEpcHelper> epcHelper = CreateObject<PointToPointEpcHelper>();
    epcHelper->SetAttribute("S1uLinkEnablePcap", BooleanValue(false));
    lteHelper->SetEpcHelper(epcHelper);
    lteHelper->SetSchedulerType("ns3::RrFfMacScheduler");
    
    // Our malicious xApp isn't going to handover, even though it could. So we leave the default HO algorithm.
    lteHelper->SetHandoverAlgorithmType("ns3::A2A4RsrqHandoverAlgorithm");
    lteHelper->SetHandoverAlgorithmAttribute("ServingCellThreshold", UintegerValue(30));
    lteHelper->SetHandoverAlgorithmAttribute("NeighbourCellOffset", UintegerValue(1));

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

    // Set the position of EPC e remote internet nodes
    NodeContainer backHaulNodes;
    backHaulNodes.Add(remoteHostContainer.Get(0));
    backHaulNodes.Add(pgw);
    backHaulNodes.Add(sgw);
    Ptr<Node> mme = NodeList::GetNode(2);
    backHaulNodes.Add(mme);

    Ptr<ListPositionAllocator> backHaulPositionAlloc = CreateObject<ListPositionAllocator>();
    backHaulPositionAlloc->Add(Vector(200, 1000, 0));
    backHaulPositionAlloc->Add(Vector(200, 750, 0));
    backHaulPositionAlloc->Add(Vector(200, 500, 0));
    backHaulPositionAlloc->Add(Vector(200, 250, 0));

    MobilityHelper backHaulMobility;
    backHaulMobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    backHaulMobility.SetPositionAllocator(backHaulPositionAlloc);
    backHaulMobility.Install(backHaulNodes);

    NodeContainer ueNodes;
    NodeContainer enbNodes;
    enbNodes.Create(numberOfEnbs);
    ueNodes.Create(numberOfUes);

    // Install Mobility Model in eNB
    Ptr<ListPositionAllocator> enbPositionAlloc = CreateObject<ListPositionAllocator>();
    enbPositionAlloc->Add(Vector(1000, 1000, 0));
    enbPositionAlloc->Add(Vector(2000, 1000, 0));
    enbPositionAlloc->Add(Vector(1500, 1866, 0));

    MobilityHelper enbMobility;
    enbMobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    enbMobility.SetPositionAllocator(enbPositionAlloc);
    enbMobility.Install(enbNodes);

    // Install Mobility Model in UE
    MobilityHelper ueMobility;
    ueMobility.SetMobilityModel("ns3::WaypointMobilityModel");
    ueMobility.Install(ueNodes);

    int steps = 120;
    int cycles = 5;
    Time timePerStep = Seconds(simTime)/(steps*cycles);
    Time timePerCycle = Seconds(simTime)/cycles;
    auto boundaries = BoundingBox(750, 2300, 650, 2000);
    for (int i = 0; i < std::min(numberOfUes, static_cast<uint16_t>(MobilityPatterns::NUM_PATTERNS)); i++)
    {
        auto coordinates = MobilityPatterns::GetMobilityPatternCoordinates(steps,
                                                                           boundaries,
                                                                           static_cast<MobilityPatterns::PATTERN_ENUM>(i));
        auto itCoordRev = coordinates.rbegin();
        ueNodes.Get(i)->GetObject<MobilityModel>()->SetPosition(Vector(itCoordRev->first, itCoordRev->second, 0));

        for(auto k = 0; k < cycles; k++)
        {
            auto itCoord = coordinates.begin();
            for(int j = 0; j < steps; j++, itCoord++)
            {
                Waypoint wpt(timePerCycle*k+timePerStep*j, Vector(itCoord->first, itCoord->second, 0.0));
                ueNodes.Get(i)->GetObject<WaypointMobilityModel>()->AddWaypoint(wpt);
            }
        }
    }

    // Install LTE Devices in eNB and UEs
    Config::SetDefault("ns3::LteEnbRrc::DefaultTransmissionMode", UintegerValue(2));
    Config::SetDefault("ns3::LteEnbPhy::TxPower", DoubleValue(enbTxPowerDbm));
    // Config::SetDefault("ns3::LteUePhy::TxPower", DoubleValue(50.0));
    // lteHelper->SetEnbAntennaModelAttribute ("Gain",     DoubleValue (30));
    // lteHelper->SetUeAntennaModelAttribute  ("Gain",     DoubleValue (30));
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

    Config::SetDefault("ns3::UdpClient::Interval", TimeValue(Seconds(1)));
    Config::SetDefault("ns3::UdpClient::MaxPackets", UintegerValue(1000000));

    // randomize a bit start times to avoid simulation artifacts
    // (e.g., buffer overflows due to packet transmissions happening
    // exactly at the same time)
    Ptr<UniformRandomVariable> startTimeSeconds = CreateObject<UniformRandomVariable>();
    startTimeSeconds->SetAttribute("Min", DoubleValue(1));
    startTimeSeconds->SetAttribute("Max", DoubleValue(1.9));

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

            Time startTime = Seconds(startTimeSeconds->GetValue());
            serverApps.Start(startTime);
            clientApps.Start(startTime);

        } // end for b
    }

    // Add X2 interface
    lteHelper->AddX2Interface(enbNodes);

    // Configura regra de encaminhamento para eNBs que não sejam o primeiro
    for (unsigned i = 1; i < numberOfEnbs; i++)
    {
        Ipv4StaticRoutingHelper ipv4RoutingHelper;
        Ptr<Ipv4StaticRouting> remoteHostStaticRouting =
            ipv4RoutingHelper.GetStaticRouting(enbNodes.Get(i)->GetObject<Ipv4>());
        remoteHostStaticRouting->AddNetworkRouteTo(Ipv4Address("10.0.0.6"),
                                                   Ipv4Mask("255.255.255.252"),
                                                   1);
    }

    if (scenario == SimulationScenarios::ORAN_BYPASS ||
        scenario == SimulationScenarios::ORAN_MALICIOUS_XAPP_WITH_RNTI ||
        scenario == SimulationScenarios::ORAN_MALICIOUS_XAPP_WITHOUT_RNTI)
    {
        Ptr<E2AP> e2t = CreateObject<E2AP>();
        sgw->AddApplication(e2t);

        // Configurar eNodeBs/nós E2
        Ptr<E2AP> e2n1 = CreateObject<E2AP>();
        enbNodes.Get(0)->AddApplication(e2n1);
        Simulator::Schedule(Seconds(0.1), &E2AP::Connect, e2t);
        Simulator::Schedule(Seconds(0.2), &E2AP::Connect, e2n1);
        Simulator::Schedule(Seconds(0.3), &E2AP::RegisterDefaultEndpoints, e2n1);
        Simulator::Schedule(Seconds(0.4), &E2AP::SubscribeToDefaultEndpoints, e2t, *e2n1);

        Ptr<E2AP> e2n2 = CreateObject<E2AP>();
        enbNodes.Get(1)->AddApplication(e2n2);
        Simulator::Schedule(Seconds(0.2), &E2AP::Connect, e2n2);
        Simulator::Schedule(Seconds(0.3), &E2AP::RegisterDefaultEndpoints, e2n2);
        Simulator::Schedule(Seconds(0.4), &E2AP::SubscribeToDefaultEndpoints, e2t, *e2n2);

        Ptr<E2AP> e2n3 = CreateObject<E2AP>();
        enbNodes.Get(2)->AddApplication(e2n3);
        Simulator::Schedule(Seconds(0.2), &E2AP::Connect, e2n3);
        Simulator::Schedule(Seconds(0.3), &E2AP::RegisterDefaultEndpoints, e2n3);
        Simulator::Schedule(Seconds(0.4), &E2AP::SubscribeToDefaultEndpoints, e2t, *e2n3);

        Ptr<xAppHandoverMaliciousPositioning> handoverxapp = CreateObject<xAppHandoverMaliciousPositioning>(
            scenario == SimulationScenarios::ORAN_MALICIOUS_XAPP_WITH_RNTI);
        sgw->AddApplication(handoverxapp);
    }

    AnimationInterface anim("anim.xml");
    //anim.SetMaxPktsPerTraceFile(0xFFFFFFFF);
    anim.EnablePacketMetadata(false);

    anim.UpdateNodeDescription(remoteHost->GetId(), "Remote Internet Host");
    anim.UpdateNodeColor(remoteHost->GetId(), 230, 230, 230);
    anim.UpdateNodeSize(remoteHost->GetId(), 80, 80);

    anim.UpdateNodeDescription(pgw->GetId(), "PGW");
    anim.UpdateNodeColor(pgw->GetId(), 0, 0, 255);
    anim.UpdateNodeSize(pgw->GetId(), 80, 80);

    anim.UpdateNodeDescription(sgw->GetId(), "SGW/RIC");
    anim.UpdateNodeColor(sgw->GetId(), 0, 0, 255);
    anim.UpdateNodeSize(sgw->GetId(), 80, 80);

    anim.UpdateNodeDescription(mme->GetId(), "MME");
    anim.UpdateNodeColor(mme->GetId(), 0, 0, 255);
    anim.UpdateNodeSize(mme->GetId(), 80, 80);

    for (uint32_t i = 0; i < enbNodes.GetN(); i++)
    {
        int nodeId = enbNodes.Get(i)->GetId();
        anim.UpdateNodeDescription(nodeId, "eNB" + std::to_string(i));
        anim.UpdateNodeColor(nodeId, 255, 0, 0);
        anim.UpdateNodeSize(nodeId, 80, 80);

    }
    for (uint32_t i = 0; i < ueNodes.GetN(); i++)
    {
        int nodeId = ueNodes.Get(i)->GetId();
        anim.UpdateNodeDescription(nodeId, "UE" + std::to_string(i));
        anim.UpdateNodeColor(nodeId, 0, 255, 0);
        anim.UpdateNodeSize(nodeId, 80, 80);
    }

    // Ptr<FlowMonitor> flowMonitor;
    // FlowMonitorHelper flowHelper;
    // flowMonitor = flowHelper.InstallAll();

    Simulator::Stop(Seconds(simTime));
    Simulator::Run();

    // flowMonitor->SerializeToXmlFile("flow.xml", true, false);

    Simulator::Destroy();
    return 0;
}
