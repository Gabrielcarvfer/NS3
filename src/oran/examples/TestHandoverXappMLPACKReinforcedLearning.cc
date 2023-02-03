//
// Created by Gabriel Ferreira(@gabrielcarvfer) on 1/11/22.
//

#include "ns3/E2AP.h"
#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/lte-module.h"
#include "ns3/mobility-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/xAppHandover.h"

#include <map>
#include <mlpack/core.hpp>
#include <mlpack/methods/kmeans/kmeans.hpp>
#include <mlpack/prereqs.hpp>
#include <string>

NS_LOG_COMPONENT_DEFINE("TestHandoverXappMLPACK");

using namespace ns3;

void
NotifyConnectionEstablishedUe(std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti)
{
    std::cout << context << " UE IMSI " << imsi << ": connected to CellId " << cellid
              << " with RNTI " << rnti << std::endl;
}

void
NotifyHandoverStartUe(std::string context,
                      uint64_t imsi,
                      uint16_t cellid,
                      uint16_t rnti,
                      uint16_t targetCellId)
{
    std::cout << context << " UE IMSI " << imsi << ": previously connected to CellId " << cellid
              << " with RNTI " << rnti << ", doing handover to CellId " << targetCellId
              << std::endl;
}

void
NotifyHandoverEndOkUe(std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti)
{
    std::cout << context << " UE IMSI " << imsi << ": successful handover to CellId " << cellid
              << " with RNTI " << rnti << std::endl;
}

void
NotifyConnectionEstablishedEnb(std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti)
{
    std::cout << context << " eNB CellId " << cellid << ": successful connection of UE with IMSI "
              << imsi << " RNTI " << rnti << std::endl;
}

void
NotifyHandoverStartEnb(std::string context,
                       uint64_t imsi,
                       uint16_t cellid,
                       uint16_t rnti,
                       uint16_t targetCellId)
{
    std::cout << context << " eNB CellId " << cellid << ": start handover of UE with IMSI " << imsi
              << " RNTI " << rnti << " to CellId " << targetCellId << std::endl;
}

void
NotifyHandoverEndOkEnb(std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti)
{
    std::cout << context << " eNB CellId " << cellid << ": completed handover of UE with IMSI "
              << imsi << " RNTI " << rnti << std::endl;
}

class xAppHandoverML : public xAppHandover
{
  public:
    xAppHandoverML()
        : xAppHandover()
    {
        NS_LOG_FUNCTION(this);

        Config::Connect("/NodeList/*/DeviceList/*/LteEnbRrc/HandoverEndOk",
                        MakeCallback(&xAppHandoverML::HandoverSucceeded, this));
        Config::Connect("/NodeList/*/DeviceList/*/LteUeRrc/HandoverEndError",
                        MakeCallback(&xAppHandoverML::HandoverFailed, this));
        Simulator::Schedule(Seconds(1), &xAppHandoverML::PeriodicClustering, this);
    };

    void PeriodicClustering()
    {
        NS_LOG_FUNCTION(this);

        const E2AP* ric = static_cast<const E2AP*>(m_endpointRootToInstance.at("/E2Node/0"));
        std::map<uint16_t, uint16_t> rntis;
        std::array<std::string, 4> kpmMetrics = {//"/KPM/HO.SrcCellQual.RSRP",
                                                 "/KPM/HO.SrcCellQual.RSRQ",
                                                 //"/KPM/HO.TrgtCellQual.RSRP",
                                                 "/KPM/HO.TrgtCellQual.RSRQ"};
        std::map<uint16_t, uint16_t> cells;
        uint16_t i_rnti = 0;
        uint16_t i_cell = 0;
        // Count the number of eNodeBs/E2Nodes and the number of UEs/RNTIs
        for (auto kpmMetric : kpmMetrics)
        {
            auto metricMap = ric->QueryKpmMetric(kpmMetric);
            if (metricMap.size() == 0)
            {
                continue;
            }

            for (auto& e2nodeMeasurements : metricMap)
            {
                std::string cellIdStr(e2nodeMeasurements.first.begin() +
                                          e2nodeMeasurements.first.find_last_of("/") + 1,
                                      e2nodeMeasurements.first.end());
                uint16_t cellId = std::atoi(cellIdStr.c_str());
                if (cells.find(cellId) == cells.end())
                {
                    cells[cellId] = i_cell++;
                }
                for (auto& measurementDeque : e2nodeMeasurements.second)
                {
                    uint16_t rnti = measurementDeque.measurements["RNTI"];
                    if (rntis.find(rnti) == rntis.end())
                    {
                        rntis[rnti] = i_rnti++;
                    }
                }
            }
        }

        // If there is nothing to cluster, end early
        if (rntis.size() == 0 || cells.size() == 0)
        {
            Simulator::Schedule(Seconds(1), &xAppHandoverML::PeriodicClustering, this);
            return;
        }

        // Rows are cells and columns are UEs
        arma::mat dataset = arma::zeros(cells.size(), rntis.size());
        m_rntiToCurrentCellId.clear();

        // Collate data into an armadillo matrix for processing
        for (auto kpmMetric : kpmMetrics)
        {
            auto metricMap = ric->QueryKpmMetric(kpmMetric);

            if (metricMap.size() == 0)
            {
                continue;
            }

            for (auto& e2nodeMeasurements : metricMap)

            {
                for (auto& measurementDeque : e2nodeMeasurements.second)
                {
                    uint16_t rnti = measurementDeque.measurements["RNTI"];
                    uint16_t rnti_offset = rntis.at(rnti);
                    if (kpmMetric == "/KPM/HO.SrcCellQual.RSRQ")
                    {
                        uint16_t cellId = measurementDeque.measurements["CELLID"];
                        if (cells.find(cellId + 1) == cells.end())
                            continue;
                        m_rntiToCurrentCellId[rnti] = cellId + 1;
                        uint16_t cellid_offset = cells.at(cellId + 1);
                        dataset.at(cellid_offset, rnti_offset) =
                            measurementDeque.measurements["VALUE"];
                    }
                    else
                    {
                        uint16_t cellId = measurementDeque.measurements["TARGET"];
                        uint16_t cellid_offset = cells.at(cellId);
                        dataset.at(cellid_offset, rnti_offset) =
                            measurementDeque.measurements["VALUE"];
                    }
                }
            }
        }
        // Prepare to run K-means
        arma::Row<size_t> assignments;
        mlpack::kmeans::KMeans<> k;
        arma::mat centroids;
        k.Cluster(dataset, cells.size(), assignments, centroids);

        // Print dataset with each column representing measurements from a UE
        std::cout << dataset << std::endl;

        // Print assigned clusters to each UE
        std::cout << assignments << std::endl;
        m_rntiToClusteredCellId.clear();

        // Translate assigned clusters into cellIds
        int i = 0;
        for (auto& rnti : rntis)
        {
            uint16_t cellId = -1;
            for (auto& cell : cells)
            {
                if (cell.second == (uint16_t)assignments.at(i))
                {
                    cellId = cell.first;
                    break;
                }
            }
            m_rntiToClusteredCellId[rnti.first] = cellId;
            i++;
        }
        Simulator::Schedule(Seconds(1), &xAppHandoverML::PeriodicClustering, this);
    }

    void HandoverDecision(Json& payload)
    {
        NS_LOG_FUNCTION(this);

        // Check if we are not receiving invalid payloads
        if (m_endpointRootToInstance.at(m_endpointRoot)->GetNode() !=
            m_endpointRootToInstance.at("/E2Node/0")->GetNode())
        {
            NS_ABORT_MSG("Trying to run a xApp on a E2Node is a no-no");
        }
        // Read inputs from the json
        uint16_t requestingRnti = payload["RNTI"];
        uint16_t requestedTargetCellId = payload["Target Primary Cell ID"];

        // Do the processing
        uint16_t decidedTargetCellId = requestedTargetCellId;

        // Use K-means clustering results
        if (m_rntiToClusteredCellId.find(requestingRnti) != m_rntiToClusteredCellId.end())
            decidedTargetCellId = m_rntiToClusteredCellId.at(requestingRnti);

        // If the result is invalid (same as current cell or unknown), use 0xFFFF to reject the
        // handover
        if (m_rntiToCurrentCellId.find(requestingRnti) == m_rntiToCurrentCellId.end() ||
            decidedTargetCellId == m_rntiToCurrentCellId.at(requestingRnti))
            decidedTargetCellId = std::numeric_limits<uint16_t>::max();

        // Then write the outputs to the json
        payload["Target Primary Cell ID"] = decidedTargetCellId;
        m_decision_history.push_back({requestingRnti, requestedTargetCellId, decidedTargetCellId});
    }

    void HandoverSucceeded(std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti)
    {
        NS_LOG_FUNCTION(this);

        std::cout << "yay" << std::endl; // reward predictor
    }

    void HandoverFailed(std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti)
    {
        NS_LOG_FUNCTION(this);

        std::cout << "nay" << std::endl; // punish predictor
    }

  private:
    std::deque<std::tuple<uint16_t, uint16_t, uint16_t>> m_decision_history;
    std::map<uint16_t, uint16_t> m_rntiToClusteredCellId;
    std::map<uint16_t, uint16_t> m_rntiToCurrentCellId;
};

int
main()
{
    // Testes de conexão de nós
    GlobalValue::Bind("ChecksumEnabled", BooleanValue(true));

    uint16_t numberOfUes = 4;
    uint16_t numberOfEnbs = 3;
    uint16_t numBearersPerUe = 0;
    double distance = 200.0; // m
    double yForUe = 500.0;   // m
    double speed = 1;        // 20;                                              // m/s
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

    lteHelper->SetHandoverAlgorithmType(
        "ns3::NoOpHandoverAlgorithm"); // select an algorithm that does nothing
    // lteHelper->SetHandoverAlgorithmType("ns3::A2A4RsrqHandoverAlgorithm");
    // lteHelper->SetHandoverAlgorithmAttribute("ServingCellThreshold", UintegerValue(30));
    // lteHelper->SetHandoverAlgorithmAttribute("NeighbourCellOffset", UintegerValue(1));

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
    for (uint16_t i = 1; i < numberOfEnbs + 1; i++) // i = 1 => UE is in the middle of two eNBs
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
    ueNodes.Get(1)->GetObject<MobilityModel>()->SetPosition(Vector(yForUe, yForUe, 0));
    ueNodes.Get(1)->GetObject<ConstantVelocityMobilityModel>()->SetVelocity(Vector(speed, 0, 0));
    ueNodes.Get(2)->GetObject<MobilityModel>()->SetPosition(Vector(0, 1.5 * yForUe, 0));
    ueNodes.Get(2)->GetObject<ConstantVelocityMobilityModel>()->SetVelocity(Vector(speed, 0, 0));
    ueNodes.Get(3)->GetObject<MobilityModel>()->SetPosition(Vector(0, 2.0 * yForUe, 0));
    ueNodes.Get(3)->GetObject<ConstantVelocityMobilityModel>()->SetVelocity(Vector(speed, 0, 0));

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
    for (unsigned i = 1; i < numberOfEnbs; i++)
    {
        Ipv4StaticRoutingHelper ipv4RoutingHelper;
        Ptr<Ipv4StaticRouting> remoteHostStaticRouting =
            ipv4RoutingHelper.GetStaticRouting(enbNodes.Get(i)->GetObject<Ipv4>());
        remoteHostStaticRouting->AddNetworkRouteTo(Ipv4Address("10.0.0.6"),
                                                   Ipv4Mask("255.255.255.252"),
                                                   1);
    }

    // connect custom trace sinks for RRC connection establishment and handover notification
    Config::Connect("/NodeList/*/DeviceList/*/LteEnbRrc/ConnectionEstablished",
                    MakeCallback(&NotifyConnectionEstablishedEnb));
    Config::Connect("/NodeList/*/DeviceList/*/LteUeRrc/ConnectionEstablished",
                    MakeCallback(&NotifyConnectionEstablishedUe));
    Config::Connect("/NodeList/*/DeviceList/*/LteEnbRrc/HandoverStart",
                    MakeCallback(&NotifyHandoverStartEnb));
    Config::Connect("/NodeList/*/DeviceList/*/LteUeRrc/HandoverStart",
                    MakeCallback(&NotifyHandoverStartUe));
    Config::Connect("/NodeList/*/DeviceList/*/LteEnbRrc/HandoverEndOk",
                    MakeCallback(&NotifyHandoverEndOkEnb));
    Config::Connect("/NodeList/*/DeviceList/*/LteUeRrc/HandoverEndOk",
                    MakeCallback(&NotifyHandoverEndOkUe));

    E2AP e2t;
    NS_ASSERT(e2t.m_instanceId == 0);
    NS_ASSERT(e2t.m_endpointRoot == "/E2Node/0");

    E2AP e2n1;
    NS_ASSERT(e2n1.m_instanceId == 1);
    NS_ASSERT(e2n1.m_endpointRoot == "/E2Node/1");

    NS_ASSERT(E2AP::m_endpointRootToInstance.find("/E2Node/0")->second ==
              static_cast<PubSubInfra*>(&e2t));

    // Create the handover xApp
    xAppHandoverML handoverxapp;

    // Depois de instalar aplicações, conseguiremos obter seus endereços de IP para
    // estabelecer os sockets TCP
    sgw->AddApplication(&e2t);
    sgw->AddApplication(&handoverxapp);

    // Configurar eNodeBs/nós E2
    enbNodes.Get(0)->AddApplication(&e2n1);

    Simulator::Schedule(Seconds(0.5), &E2AP::Connect, &e2t);
    Simulator::Schedule(Seconds(1.0), &E2AP::Connect, &e2n1);
    Simulator::Schedule(Seconds(2.0), &E2AP::RegisterDefaultEndpoints, &e2n1);
    Simulator::Schedule(Seconds(2.5), &E2AP::SubscribeToDefaultEndpoints, &e2t, e2n1);

    E2AP e2n2;
    enbNodes.Get(1)->AddApplication(&e2n2);
    Simulator::Schedule(Seconds(1.0), &E2AP::Connect, &e2n2);
    Simulator::Schedule(Seconds(2.0), &E2AP::RegisterDefaultEndpoints, &e2n2);
    Simulator::Schedule(Seconds(2.5), &E2AP::SubscribeToDefaultEndpoints, &e2t, e2n2);

    E2AP e2n3;
    enbNodes.Get(2)->AddApplication(&e2n3);
    Simulator::Schedule(Seconds(1.0), &E2AP::Connect, &e2n3);
    Simulator::Schedule(Seconds(2.0), &E2AP::RegisterDefaultEndpoints, &e2n3);
    Simulator::Schedule(Seconds(2.5), &E2AP::SubscribeToDefaultEndpoints, &e2t, e2n3);

    // Executa um handover do primeiro eNB para o segundo
    lteHelper->HandoverRequest(Seconds(4.0),
                               ueLteDevs.Get(0),
                               enbLteDevs.Get(0),
                               enbLteDevs.Get(1));

    // K-means clustering will move node to Cell3/enbLteDevs.Get(2) instead of
    // Cell2/enbLteDev.Get(1)

    // Executar handover de volta para primeiro eNB
    lteHelper->HandoverRequest(Seconds(5.0),
                               ueLteDevs.Get(0),
                               enbLteDevs.Get(2),
                               enbLteDevs.Get(0));

    // Executar handover do primeiro eNB para terceiro
    lteHelper->HandoverRequest(Seconds(6.0),
                               ueLteDevs.Get(0),
                               enbLteDevs.Get(0),
                               enbLteDevs.Get(2));

    // Executar handover do terceiro eNB para o primeiro
    lteHelper->HandoverRequest(Seconds(7.0),
                               ueLteDevs.Get(0),
                               enbLteDevs.Get(2),
                               enbLteDevs.Get(0));

    Simulator::Stop(Seconds(8.0));
    Simulator::Run();
    Simulator::Destroy();
    return 0;
}
