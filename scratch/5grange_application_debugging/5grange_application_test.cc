//
// Created by Gabriel Ferreira (@gabrielcarvfer) in 24/04/2019.
// Updated for 5G-RANGE compatibility in 1/10/2020
//

/*
 *
 * In this scenario, we have two UEs and an eNB
 *
 * USE NS_LOG=LteEnbPhy:LteEnbMac:CqaFfMacScheduler:LteUePhy:LteUeMac to debug timing issues
 * NS_LOG=LteSpectrumPhy:LteUePhy:RrFfMacScheduler:LteRlcUm:LteEnbPhy;OPENBLAS_NUM_THREADS=1
 */

#include <ns3/core-module.h>
#include <ns3/lte-module.h>
#include <ns3/internet-module.h>
#include <ns3/mobility-module.h>
#include <ns3/applications-module.h>
#include <ns3/flow-monitor-module.h>
#include <ns3/wifi-module.h>
#include <ns3/olsr-helper.h>


#include <ns3/point-to-point-module.h>
#include <cstdint>
#include <ns3/spectrum-module.h>

#include "../3rd-party/picojson/picojson.h"
#include "../3rd-party/json-loader/json_loader.h"

#include <map>
#include <ns3/contrib-haraldott-module.h>
#include <sys/stat.h>
#include "ns3/spatially-correlated-shadowing-map.h"
#include "ns3/contrib-notopoloko-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("5gApplicationTest");

void make_ue_pairs(uint32_t numUes, float fraction, std::map<std::pair<uint16_t, uint16_t>, bool> &uePairs)
{
  // if more than 2 UEs, we assume a fraction of the UEs are talking to each other
  int numPairs = numUes * fraction / 2;
  numPairs = numPairs > 0 ? numPairs : 1;
  uint16_t prevSize = 0;
  uint16_t currSize = 0;
  while (numPairs > 0)
  {
    uint16_t ue0 = rand() % numUes;
    uint16_t ue1 = rand() % numUes;
    if (ue0 == ue1)
      continue;
    uePairs.emplace(std::make_pair(ue0, ue1), true);
    currSize = uePairs.size();
    if (prevSize != currSize)
      numPairs--;
    prevSize = currSize;
  }
}


//Simple network setup
int main(int argc, char * argv[]) {
    ns3::RngSeedManager::SetSeed(1);
    std::cout << "Seed " << ns3::RngSeedManager::GetSeed() << std::endl;

    std::ios::sync_with_stdio(false);
    std::string data_path = "./output/"; //folder to save results



    int nUes = 0;
    double ue_x, ue_y, ue_z;
    ue_x = ue_y = ue_z = 0.0;

    bool tcp = 0;
    float interval = 1.0;
    uint16_t pkt_size = 100;

    CommandLine cmd;
    cmd.AddValue("nUes", "Number of UEs", nUes);
    cmd.AddValue("x", "x-coordinate", ue_x);
    cmd.AddValue("y", "y-coordinate", ue_y);
    cmd.AddValue("z", "z-coordinate", ue_z);
    cmd.AddValue("tcp", "Tcp=1, udp=0", tcp);
    cmd.AddValue("pkt_size", "Size of packets", pkt_size);
    cmd.AddValue("interval", "Interval between packets", interval);

    cmd.Parse(argc, argv);
    std::cout << interval << std::endl;

    //Get EARFCN for specified frequency band
    double carrierFreq = 0.0;
    int dlBandwidth, ulBandwidth;
    int channelBandwidth = 6000000; // 6MHz
    dlBandwidth = ulBandwidth = 132; // 33 RBs per 6MHz channel (BR)
    // or 44 RBs per 8MHz channel (UE)
    // or 5.5 RBs per 1MHz

    //Find DL and UL frequencies based on the bands
    {
        int freqBand = 100;
        uint32_t dlEarfcn, ulEarfcn;

        for (int i = 0; i < NUM_EUTRA_BANDS; i++) {
            if (freqBand != g_eutraChannelNumbers[i].band)
                continue;
            carrierFreq = g_eutraChannelNumbers[i].fDlLow;
            //carrierFreq = g_eutraChannelNumbers[i].fUlLow;
            dlEarfcn = g_eutraChannelNumbers[i].nOffsDl;
            ulEarfcn = g_eutraChannelNumbers[i].nOffsUl;
            carrierFreq *= 1000000; // MHz to Hz
        }

        Config::SetDefault("ns3::ComponentCarrier::DlEarfcn", UintegerValue(dlEarfcn));
        Config::SetDefault("ns3::ComponentCarrier::UlEarfcn", UintegerValue(ulEarfcn));
        Config::SetDefault("ns3::ComponentCarrier::DlBandwidth", UintegerValue(dlBandwidth));
        Config::SetDefault("ns3::ComponentCarrier::UlBandwidth", UintegerValue(ulBandwidth));

        Config::SetDefault("ns3::LteUeNetDevice::DlEarfcn", UintegerValue(dlEarfcn));
        Config::SetDefault("ns3::LteEnbNetDevice::DlEarfcn", UintegerValue(dlEarfcn));
        Config::SetDefault("ns3::LteEnbNetDevice::UlEarfcn", UintegerValue(ulEarfcn));
        Config::SetDefault("ns3::LteEnbNetDevice::DlBandwidth", UintegerValue(dlBandwidth));
        Config::SetDefault("ns3::LteEnbNetDevice::UlBandwidth", UintegerValue(ulBandwidth));
    }

    Config::SetDefault("ns3::LteHelper::NumberOfComponentCarriers", UintegerValue(1));
    Config::SetDefault("ns3::LteHelper::UseCa", BooleanValue(false));
    Config::SetDefault("ns3::LteHelper::EnbComponentCarrierManager", StringValue("ns3::RrComponentCarrierManager"));
    Config::SetDefault("ns3::LteSpectrumPhy::CtrlErrorModelEnabled", BooleanValue(false));
    Config::SetDefault("ns3::LteHelper::UseIdealRrc", BooleanValue(true));

    {
        // Even though the json parameters assume individual txPower for eNB and UEs, we use a single one
        double enbTxPower = 40.8;
        double ueTxPower = 23;

        Config::SetDefault("ns3::LteEnbPhy::TxPower", DoubleValue(enbTxPower));
        Config::SetDefault("ns3::LteUePhy::TxPower", DoubleValue(ueTxPower));
    }

    Config::SetDefault("ns3::LteUePhy::EnableUplinkPowerControl", BooleanValue(false));

    bool enableDSA = false;
    {
        Config::SetDefault("ns3::LteEnbMac::SpectrumSensing",
                           BooleanValue(enableDSA));
        Config::SetDefault("ns3::LteSpectrumPhy::SpectrumSensing",
                           BooleanValue(enableDSA));
        Config::SetDefault("ns3::LteEnbMac::FusionAlgorithm",
                           UintegerValue(6));
        LteSpectrumPhy::SNRsensing = false;
    }
    NodeContainer allNodes;

    unsigned int numerology = 0;
    Config::SetDefault("ns3::LteHelper::Numerology", UintegerValue(numerology));
    Config::SetDefault("ns3::LteAmc::Numerology", UintegerValue(numerology));

    Ptr <LteHelper> lteHelper = CreateObject<LteHelper>();
    lteHelper->SetSchedulerType("ns3::RrFfMacScheduler");
    Config::SetDefault("ns3::RrFfMacScheduler::HarqEnabled", BooleanValue(true));

    //lteHelper->SetSchedulerType ("ns3::PfFfMacScheduler");
    //Config::SetDefault ("ns3::PfFfMacScheduler::HarqEnabled", BooleanValue (simulationParameters["useHarq"].get<bool>()));

    Config::SetDefault("ns3::LteEnbRrc::DefaultTransmissionMode",
                       UintegerValue(1));

    if (true) {
        Config::SetDefault("ns3::Ula5gRange::NumAntElem",
                           UintegerValue(2));

        Config::SetDefault("ns3::CdlCommon::KValue",
                           DoubleValue(0.0));

        Config::SetDefault("ns3::TraceFadingLossModel::RbNum", UintegerValue(dlBandwidth));
        std::string cdlType = "CDL_D";
        if (cdlType == "CDL_A") {
            Config::SetDefault("ns3::CdlSpectrumPropagationLossModel::CdlType",
                               EnumValue(CdlSpectrumPropagationLossModel::CDL_A));
            Config::SetDefault("ns3::LteAmc::ChannelModel", StringValue("CDL_A"));
        }
        lteHelper->SetPathlossModelType(TypeId::LookupByName("ns3::CdlSpectrumPropagationLossModel"));
        if (cdlType == "CDL_A")
            lteHelper->SetAttribute("ChannelModel", StringValue("CDL_A"));
    } else {
        Config::SetDefault("ns3::RANGE5GPropagationLossModel::Frequency", DoubleValue(carrierFreq));
        Config::SetDefault("ns3::RANGE5GPropagationLossModel::K-value",
                           DoubleValue(0));
        lteHelper->SetAttribute("PathlossModel", StringValue("ns3::RANGE5GPropagationLossModel"));
    }

    {
        // Even though the json parameters assume individual txPower for eNB and UEs, we use a single one
        double enbGain = 9;
        double ueGain = 9;

        lteHelper->SetEnbAntennaModelAttribute("Gain", DoubleValue(enbGain));
        lteHelper->SetUeAntennaModelAttribute("Gain", DoubleValue(ueGain));
    }
    ns3::RngSeedManager::SetRun(0);

    // Default 5G-RANGE parameters
    Config::SetDefault("ns3::LteEnbRrc::SrsPeriodicity", UintegerValue(160));

    static GlobalValue g_max_mcs_sched =
            GlobalValue("MAX_MCS_SCHED", "Force maximum MCS value",
                        UintegerValue(0),
                        MakeUintegerChecker<uint16_t>());

    static GlobalValue g_attackers_per_channel =
            GlobalValue("ATTACKERS_PER_CHANNEL", "Number of attackers per channel",
                        IntegerValue(0),
                        MakeIntegerChecker<int64_t>());

    static GlobalValue g_markov_detection =
            GlobalValue("MARKOV_DETECTION", "Use Markov-chain to improve individual sensing report",
                        BooleanValue(0),
                        MakeBooleanChecker());

    static GlobalValue g_harmonic_detection =
            GlobalValue("HARMONIC_DETECTION", "Use harmonic detection to prevent Byzantine attackers",
                        BooleanValue(0),
                        MakeBooleanChecker());

    //Setup shadowing map
    SpatiallyCorrelatedShadowingMap(0, 0, 110,
                                    false);// 18* is an adjustment factor for exponential-decay of spatial correlation

    lteHelper->SetAttribute("Scheduler", StringValue("ns3::RrFfMacScheduler"));
    //lteHelper->SetAttribute("Scheduler", StringValue("ns3::CqaFfMacScheduler")); //QoS aware scheduler
    //lteHelper->SetAttribute("Scheduler", StringValue("ns3::NnFfMacScheduler")); //NN scheduler

    //1 Configure EPC e PGW
    Ptr <PointToPointEpcHelper> epcHelper = CreateObject<PointToPointEpcHelper>();
    lteHelper->SetEpcHelper(epcHelper);
    Ptr <Node> pgw = epcHelper->GetPgwNode();
    allNodes.Add(pgw);

    //2 Create the remote node (server on the internet)
    NodeContainer remoteHostContainer;
    remoteHostContainer.Create(1);
    allNodes.Add(remoteHostContainer);

    //3 Create eNB and UEs
    NodeContainer ueNodes;
    NodeContainer enbNodes;
    enbNodes.Create(1);
    ueNodes.Create(nUes);
    allNodes.Add(enbNodes);

    //4 Aloca posições dos dispositivos
    Ptr <ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator>();
    positionAlloc->Add(Vector(10.0, 0.0, 0.0));  // 0 - PGw
    positionAlloc->Add(Vector(0.0, 0.0, 0.0));  // 1 - Internet
    positionAlloc->Add(Vector(50000, 50000, 50000));  // 2 - eNB

    Ptr <ListPositionAllocator> positionAlloc2 = CreateObject<ListPositionAllocator>();

    for (int ue = 0; ue < nUes; ue++) {
        positionAlloc2->Add(Vector(ue_x, ue_y, ue_z)); //  1 - UE 0
    }


    //5 Install mobility model to the nodes
    MobilityHelper mobility;
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.SetPositionAllocator(positionAlloc);
    mobility.Install(allNodes);

    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.SetPositionAllocator(positionAlloc2);
    mobility.Install(ueNodes);

    allNodes.Add(ueNodes);


    //6 Install TCP/IP stack to the remote node
    Ptr <Node> remoteHost = remoteHostContainer.Get(0);
    InternetStackHelper internet;
    internet.Install(remoteHostContainer);

    //7 Create backhaul link between the remote node and PGW
    PointToPointHelper p2ph;
    p2ph.SetDeviceAttribute("DataRate", DataRateValue(DataRate("100Gb/s")));
    p2ph.SetDeviceAttribute("Mtu", UintegerValue(1500));
    p2ph.SetChannelAttribute("Delay", TimeValue(Seconds(0.010)));
    NetDeviceContainer internetDevices = p2ph.Install(pgw, remoteHost);

    //8 Configure address of the PGW and the external node (subnet 1.0.0.0/8)
    Ipv4AddressHelper ipv4h;
    ipv4h.SetBase("1.0.0.0", "255.0.0.0");
    Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign(internetDevices);

    // interface 0 is from PGW, 1 is from remotehost
    Ipv4Address remoteHostAddr = internetIpIfaces.GetAddress(1);

    //9 Configure static routing between internal and external IPs of the PGW (7.0.0.0 e 1.0.0.0)
    //      Allows external nodes (internet) to reach UEs
    Ipv4StaticRoutingHelper ipv4RoutingHelper;
    Ptr <Ipv4StaticRouting> remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting(remoteHost->GetObject<Ipv4>());
    remoteHostStaticRouting->AddNetworkRouteTo(Ipv4Address("7.0.0.0"), Ipv4Mask("255.0.0.0"), 1);

    //11 Install eNB e UE network devices
    NetDeviceContainer enbLteDevs = lteHelper->InstallEnbDevice(enbNodes);
    NetDeviceContainer ueLteDevs = lteHelper->InstallUeDevice(ueNodes);

    //12 Install TCP/IP networks stacks on the LTE devices and assign their addresses
    internet.Install(ueNodes);
    Ipv4InterfaceContainer ueIpIface;
    ueIpIface = epcHelper->AssignUeIpv4Address(NetDeviceContainer(ueLteDevs));

    //13 Associate UEs to the eNB
    lteHelper->Attach(ueLteDevs, enbLteDevs.Get(0));

    //14 Modify UEs to use the EPC as the gateway (GPRS tunneling through the eNB)
    for (uint32_t u = 0; u < ueNodes.GetN(); u++) {
        Ptr <Node> ueNode = ueNodes.Get(u);
        Ptr <Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting(ueNode->GetObject<Ipv4>());
        ueStaticRouting->SetDefaultRoute(epcHelper->GetUeDefaultGatewayAddress(), 1);
    }


    //15 Configure and install applications

    ApplicationContainer serverApps;
    ApplicationContainer serverApp;
    ApplicationContainer clientApps;
    ApplicationContainer tempUeApps;

    enum simCase {
        UDP = 0,
        TCP = 1
    };

  std::map<std::pair<uint16_t, uint16_t>, bool> uePairs;

  uint16_t simulationCasePort = 8000;
#define SEND_TO_SERVER
#ifdef SEND_TO_SERVER
  Ipv4Address remoteAddress = remoteHost->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal();//i+1

  PacketSinkHelper dlTcpPacketSinkHelper("ns3::TcpSocketFactory",
                                         InetSocketAddress(Ipv4Address::GetAny(), simulationCasePort));
  serverApps.Add(dlTcpPacketSinkHelper.Install(remoteHost));
  for(int i = 0; i < ueNodes.GetN(); i++)
  {
      interval = (float) (rand() % 1000+1);
      srand(interval);
      std::cout << "UE " << i << " interval " << interval << std::endl;
      if (tcp)
      {
        TcpEchoClientHelper packet_generator(remoteAddress, simulationCasePort);
        packet_generator.SetAttribute("MaxPackets", UintegerValue(1000000));
        packet_generator.SetAttribute("Interval", TimeValue(MilliSeconds(interval)));//interval
        packet_generator.SetAttribute("PacketSize", UintegerValue(pkt_size));
        clientApps.Add(packet_generator.Install(ueNodes.Get(i)));
      }
      else
      {
        UdpEchoClientHelper packet_generator(remoteAddress, simulationCasePort);
        packet_generator.SetAttribute("MaxPackets", UintegerValue(1000000));
        packet_generator.SetAttribute("Interval", TimeValue(MilliSeconds(interval)));
        packet_generator.SetAttribute("PacketSize", UintegerValue(pkt_size));
        clientApps.Add(packet_generator.Install(ueNodes.Get(i)));
      }
  }
#endif

#ifdef SEND_BETWEEN_UES_THROUGH_SERVER
    for(int i = 0; i < ueNodes.GetN()-1; i+=2) {
        Ipv4Address remoteAddress = ueNodes.Get(i + 1)->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal();

        if (tcp)
        {
            PacketSinkHelper dlTcpPacketSinkHelper("ns3::TcpSocketFactory",
                                                   InetSocketAddress(Ipv4Address::GetAny(), simulationCasePort));
            serverApps.Add(dlTcpPacketSinkHelper.Install(ueNodes.Get(i + 1)));
        }
        else
        {

            PacketSinkHelper dlUdpPacketSinkHelper("ns3::UdpSocketFactory",
                                                   InetSocketAddress(Ipv4Address::GetAny(), simulationCasePort));
            serverApps.Add(dlUdpPacketSinkHelper.Install(ueNodes.Get(i + 1)));
        }


        if (tcp)
        {
            TcpEchoClientHelper packet_generator(remoteAddress, simulationCasePort);
            packet_generator.SetAttribute("MaxPackets", UintegerValue(1000000));
            packet_generator.SetAttribute("Interval", TimeValue(Seconds(interval)));
            packet_generator.SetAttribute("PacketSize", UintegerValue(pkt_size));
            clientApps.Add(packet_generator.Install(ueNodes.Get(i)));
        }
        else
        {
            UdpEchoClientHelper packet_generator(remoteAddress, simulationCasePort);
            packet_generator.SetAttribute("MaxPackets", UintegerValue(1000000));
            packet_generator.SetAttribute("Interval", TimeValue(Seconds(interval)));
            packet_generator.SetAttribute("PacketSize", UintegerValue(pkt_size));
            clientApps.Add(packet_generator.Install(ueNodes.Get(i)));
        }
    }
#endif
  //Start servers before starting clients
  serverApps.Start(Seconds(0.9));
  clientApps.Start(Seconds(1.0));

  Ptr<FlowMonitor> flowMonitor;
  FlowMonitorHelper flowHelper;
  flowMonitor = flowHelper.InstallAll();

  clientApps.Stop(Seconds(11));
  //23 Run simulation
  Simulator::Stop(Seconds(15));
  Simulator::Run();

  flowMonitor->SerializeToXmlFile("flow.xml", true, true);


  Simulator::Destroy();

  return 0;
}
