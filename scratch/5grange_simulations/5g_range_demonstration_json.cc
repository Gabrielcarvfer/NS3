//
// Created by Gabriel Ferreira (@gabrielcarvfer) in 24/04/2019.
// Updated for 5G-RANGE compatibility in 1/10/2020
//

/*
 *
 * In this scenario, we have two UEs and an eNB
 *
 * USE NS_LOG=LteEnbPhy:LteEnbMac:CqaFfMacScheduler:LteUePhy:LteUeMac to debug timing issues
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

NS_LOG_COMPONENT_DEFINE ("5gRangeDemonstration");

uint32_t lastDlTbs = 0, lastDlMcs = 0, lastUlMcs = 0, lastUlTbs = 0;

void
RangeDlSchedulingCallback (std::string path, DlSchedulingCallbackInfo dlInfo)
{
    if (lastDlMcs != (uint32_t)dlInfo.mcsTb1 || lastDlTbs != (uint32_t)dlInfo.sizeTb1)
    {
        lastDlMcs = (uint32_t)dlInfo.mcsTb1;
        lastDlTbs = (uint32_t)dlInfo.sizeTb1;
        NS_LOG_INFO(Simulator::Now() << " DL MCS: " << (uint32_t)dlInfo.mcsTb1 << " DL TBS: " << (uint32_t)dlInfo.sizeTb1 << " bytes");
        //std::cout << Simulator::Now() << " DL MCS: " << (uint32_t)dlInfo.mcsTb1 << " DL TBS: " << (uint32_t)dlInfo.sizeTb1 << " bytes" << std::endl;
    }
}

void
StartDataframeTxCallback (std::string path, Ptr<PacketBurst> pb, std::vector<int> rbs)
{
    if (pb)
    {
        std::string str_rbs = std::to_string(rbs[0]);
        for (int i = 1; i < rbs.size(); ++i)
        {
            str_rbs = str_rbs + ", " + std::to_string (rbs[i]);
        }

        //*stream->GetStream () << Simulator::Now ().GetSeconds () << " UE Phy TX - Packets: " << pb->GetNPackets () << " Size: " << pb->GetSize () << " RBs: " << str_rbs << std::endl;

        NS_LOG_INFO(Simulator::Now() << path << " UE Phy TX - Packets: " << pb->GetNPackets () << " Size: " << pb->GetSize () << " RBs: " << str_rbs);
    }
}

void
RangeUlSchedulingCallback (std::string path, uint32_t frameNo, uint32_t subframeNo, uint16_t rnti, uint8_t mcs, uint32_t sizeTb, uint8_t componentCarrierId)
{
    if (lastUlMcs != (uint32_t)mcs || lastUlTbs != (uint32_t)sizeTb)
    {
        lastUlMcs = (uint32_t)mcs;
        lastUlTbs = (uint32_t)sizeTb;
        NS_LOG_INFO(Simulator::Now() << " UL MCS: " << (uint32_t)mcs << " UL TBS: " << sizeTb << " bytes");
    }
}

void PacketCallback(const Ptr<OutputStreamWrapper> trace_file, std::string tipo, std::string path, Ptr< const Packet > packet)
{
    //NS_LOG_INFO(Simulator::Now() << " " << path << " " << tipo << " " << packet->GetSize());
    *trace_file->GetStream () << Simulator::Now() << "," << path << "," << tipo << ",1," << packet->GetSize() << std::endl;
}

void PacketBurstCallback(const Ptr<OutputStreamWrapper> trace_file, std::string tipo, std::string path, Ptr< const PacketBurst > packet)
{
    uint32_t size = 0;
    uint32_t qtd = 0;
    if (packet)
    {
        qtd = packet->GetNPackets();
        size = packet->GetSize();
    }

    //NS_LOG_INFO(Simulator::Now() << " " << path << " " << tipo << " " << qtd << " " << size);
    *trace_file->GetStream () << Simulator::Now() << "," << path << "," << tipo << "," << qtd << "," << size << std::endl;
}

void
PacketWith2AddressesCallback(const Ptr<OutputStreamWrapper> trace_file, std::string tipo, std::string path, Ptr< const Packet > packet, const Address &address, const Address &address2)
{
    //NS_LOG_INFO(Simulator::Now() << " " << path << " " << tipo << " " << packet->GetSize());
    *trace_file->GetStream () << Simulator::Now() << "," << path << "," << tipo << ",1," << packet->GetSize() << std::endl;
}

void
PacketWithAddressCallback(const Ptr<OutputStreamWrapper> trace_file, std::string tipo, std::string path, Ptr< const Packet > packet, const Address &address)
{
    //NS_LOG_INFO(Simulator::Now() << " " << path << " " << tipo << " " << packet->GetSize());
    *trace_file->GetStream () << Simulator::Now() << "," << path << "," << tipo << ",1," << packet->GetSize() << std::endl;
}


void
PhyRxCallback (const Ptr<OutputStreamWrapper> trace_file, std::string tipo, std::string path, PhyReceptionStatParameters params)
{
    *trace_file->GetStream () << Simulator::Now() << "," << path << "," << tipo << ",RX,";
    *trace_file->GetStream () << params.m_timestamp << ",";
    *trace_file->GetStream () << (uint32_t) params.m_cellId << ",";
    *trace_file->GetStream () << params.m_imsi << ",";
    *trace_file->GetStream () << params.m_rnti << ",";
    *trace_file->GetStream () << (uint32_t) params.m_txMode << ",";
    *trace_file->GetStream () << (uint32_t) params.m_layer << ",";
    *trace_file->GetStream () << (uint32_t) params.m_mcs << ",";
    *trace_file->GetStream () << params.m_size << ",";
    *trace_file->GetStream () << (uint32_t) params.m_rv << ",";
    *trace_file->GetStream () << (uint32_t) params.m_ndi << ",";
    *trace_file->GetStream () << (uint32_t) params.m_correctness << ",";
    *trace_file->GetStream () << (uint32_t) params.m_ccId << std::endl;
}

void
PhyTxCallback (const Ptr<OutputStreamWrapper> trace_file, std::string tipo, std::string path, PhyTransmissionStatParameters params)
{
    *trace_file->GetStream () << Simulator::Now() << "," << path << "," << tipo << ",TX,";
    *trace_file->GetStream () << params.m_timestamp << ",";
    *trace_file->GetStream () << (uint32_t) params.m_cellId << ",";
    *trace_file->GetStream () << params.m_imsi << ",";
    *trace_file->GetStream () << params.m_rnti << ",";
    *trace_file->GetStream () << ","; //txmode
    *trace_file->GetStream () << (uint32_t) params.m_layer << ",";
    *trace_file->GetStream () << (uint32_t) params.m_mcs << ",";
    *trace_file->GetStream () << params.m_size << ",";
    *trace_file->GetStream () << (uint32_t) params.m_rv << ",";
    *trace_file->GetStream () << (uint32_t) params.m_ndi << ",";
    *trace_file->GetStream () << ","; //correcteness
    *trace_file->GetStream () << (uint32_t) params.m_ccId << std::endl;
}

unsigned int good_seed()
{
    unsigned int random_seed, random_seed_a, random_seed_b;
    std::ifstream file ("/dev/urandom", std::ios::binary);
    if (file.is_open())
    {
        char * memblock;
        int size = sizeof(int);
        memblock = new char [size];
        file.read (memblock, size);
        file.close();
        random_seed_a = *reinterpret_cast<int*>(memblock);
        delete[] memblock;
    }// end if
    else
    {
        random_seed_a = 0;
    }
    random_seed_b = std::time(0);
    random_seed = random_seed_a xor random_seed_b;
    return random_seed;
} // end good_seed()

//Simple network setup
int main(int argc, char * argv[]) {
    ns3::RngSeedManager::SetSeed(good_seed());
    std::cout << "Seed " << ns3::RngSeedManager::GetSeed() << std::endl;

    std::ios::sync_with_stdio(false);
    std::string data_path       = "./output/"; //folder to save results

    picojson::object inputJson = load_json("simulationParameters.json");
    picojson::object simulationParameters = inputJson["SimulationParameters"].get<picojson::object>();
#if defined(_WIN32)
    _mkdir(data_path.c_str());
#else
    mkdir(data_path.c_str(),0777); // notice that 777 is different than 0777
#endif

    //Get EARFCN for specified frequency band
    double carrierFreq = 0.0;
    int dlBandwidth, ulBandwidth;
    int channelBandwidth = 6000000; // 6MHz
    dlBandwidth = ulBandwidth = (int)(simulationParameters["bw"].get<double>()*5.5); // 33 RBs per 6MHz channel (BR)
    // or 44 RBs per 8MHz channel (UE)
    // or 5.5 RBs per 1MHz

    //Find DL and UL frequencies based on the bands
    {
        int freqBand = (int) simulationParameters["freqBand"].get<double>();
        uint32_t dlEarfcn, ulEarfcn;

        for (int i = 0; i < NUM_EUTRA_BANDS; i++)
        {
            if (freqBand != g_eutraChannelNumbers[i].band)
                continue;
            carrierFreq = g_eutraChannelNumbers[i].fDlLow;
            dlEarfcn = g_eutraChannelNumbers[i].nOffsDl;
            ulEarfcn = g_eutraChannelNumbers[i].nOffsUl;
            carrierFreq *= 1000000; // Hz to MHz
        }

        Config::SetDefault ("ns3::ComponentCarrier::DlEarfcn", UintegerValue (dlEarfcn));
        Config::SetDefault ("ns3::ComponentCarrier::UlEarfcn", UintegerValue (ulEarfcn));
        Config::SetDefault ("ns3::ComponentCarrier::DlBandwidth", UintegerValue (dlBandwidth));
        Config::SetDefault ("ns3::ComponentCarrier::UlBandwidth", UintegerValue (ulBandwidth));

        Config::SetDefault ("ns3::LteUeNetDevice::DlEarfcn", UintegerValue (dlEarfcn));
        Config::SetDefault ("ns3::LteEnbNetDevice::DlEarfcn", UintegerValue (dlEarfcn));
        Config::SetDefault ("ns3::LteEnbNetDevice::UlEarfcn", UintegerValue (ulEarfcn));
        Config::SetDefault ("ns3::LteEnbNetDevice::DlBandwidth", UintegerValue (dlBandwidth));
        Config::SetDefault ("ns3::LteEnbNetDevice::UlBandwidth", UintegerValue (ulBandwidth));
    }

    Config::SetDefault ("ns3::LteHelper::NumberOfComponentCarriers", UintegerValue (1));
    Config::SetDefault ("ns3::LteHelper::UseCa", BooleanValue (false));
    Config::SetDefault ("ns3::LteHelper::EnbComponentCarrierManager", StringValue ("ns3::RrComponentCarrierManager"));
    Config::SetDefault ("ns3::LteSpectrumPhy::CtrlErrorModelEnabled", BooleanValue (false));
    Config::SetDefault ("ns3::LteHelper::UseIdealRrc", BooleanValue (true));

    {
        // Even though the json parameters assume individual txPower for eNB and UEs, we use a single one
        double enbTxPower = inputJson["eNB"].get<picojson::object>().begin()->second.get<picojson::object>()["tx_power"].get<double>();
        double ueTxPower =  inputJson["UE"].get<picojson::object>().begin()->second.get<picojson::object>()["tx_power"].get<double>();

        Config::SetDefault("ns3::LteEnbPhy::TxPower", DoubleValue(enbTxPower));
        Config::SetDefault("ns3::LteUePhy::TxPower", DoubleValue(ueTxPower));
    }

    Config::SetDefault ("ns3::LteUePhy::EnableUplinkPowerControl", BooleanValue (false));

    bool enableDSA = simulationParameters["enableDSA"].get<bool>();
    {
        Config::SetDefault("ns3::LteEnbMac::SpectrumSensing",
                           BooleanValue(enableDSA));
        Config::SetDefault("ns3::LteSpectrumPhy::SpectrumSensing",
                           BooleanValue(enableDSA));
        Config::SetDefault("ns3::LteEnbMac::FusionAlgorithm",
                           UintegerValue((int)simulationParameters["fusionAlgorithm"].get<double>()));
        LteSpectrumPhy::SNRsensing = false;
    }
    NodeContainer allNodes;

    Config::SetDefault("ns3::LteHelper::Numerology", UintegerValue((int)simulationParameters["numerology"].get<double>()));

    Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();
    lteHelper->SetSchedulerType ("ns3::RrFfMacScheduler");
    Config::SetDefault ("ns3::RrFfMacScheduler::HarqEnabled", BooleanValue (simulationParameters["useHarq"].get<bool>()));

    Config::SetDefault ("ns3::LteEnbRrc::DefaultTransmissionMode",
                        UintegerValue ((int)simulationParameters["mimoMode"].get<double>()));

    if(simulationParameters["useCdlPathLoss"].get<bool>())
    {
        Config::SetDefault("ns3::Ula5gRange::NumAntElem",
                           UintegerValue((int)simulationParameters["numAntennas"].get<double>()));

        Config::SetDefault ("ns3::CdlCommon::KValue",
                            DoubleValue(simulationParameters["kval"].get<double>()));

        Config::SetDefault ("ns3::TraceFadingLossModel::RbNum", UintegerValue (dlBandwidth));
        std::string cdlType = simulationParameters["cdlType"].get<std::string>();
        if (cdlType == "CDL_A")
        {
            Config::SetDefault("ns3::CdlSpectrumPropagationLossModel::CdlType",
                               EnumValue(CdlSpectrumPropagationLossModel::CDL_A));
            Config::SetDefault("ns3::LteAmc::ChannelModel", StringValue("CDL_A"));
        }
        lteHelper->SetPathlossModelType (TypeId::LookupByName ("ns3::CdlSpectrumPropagationLossModel"));
        if (cdlType == "CDL_A")
            lteHelper->SetAttribute("ChannelModel", StringValue("CDL_A"));
    }
    else
    {
        Config::SetDefault("ns3::RANGE5GPropagationLossModel::Frequency", DoubleValue(carrierFreq));
        Config::SetDefault("ns3::RANGE5GPropagationLossModel::K-value",
                           DoubleValue(simulationParameters["kval"].get<double>()));
        lteHelper->SetAttribute ("PathlossModel", StringValue ("ns3::RANGE5GPropagationLossModel"));
    }

    {
        // Even though the json parameters assume individual txPower for eNB and UEs, we use a single one
        double enbGain = inputJson["eNB"].get<picojson::object>().begin()->second.get<picojson::object>()["gain"].get<double>();
        double ueGain =  inputJson["UE"].get<picojson::object>().begin()->second.get<picojson::object>()["gain"].get<double>();

        lteHelper->SetEnbAntennaModelAttribute ("Gain",     DoubleValue (enbGain));
        lteHelper->SetUeAntennaModelAttribute  ("Gain",     DoubleValue (ueGain));
    }
    ns3::RngSeedManager::SetRun((int)simulationParameters["Run"].get<double>());

    // Default 5G-RANGE parameters
    Config::SetDefault("ns3::LteEnbRrc::SrsPeriodicity", UintegerValue(160));

    static GlobalValue g_max_mcs_sched =
            GlobalValue ("MAX_MCS_SCHED", "Force maximum MCS value",
                         UintegerValue (0),
                         MakeUintegerChecker<uint16_t>());

    static GlobalValue g_attackers_per_channel =
            GlobalValue ("ATTACKERS_PER_CHANNEL", "Number of attackers per channel",
                         IntegerValue ((int)simulationParameters["attackers_per_channel"].get<double>()),
                         MakeIntegerChecker<int64_t>());

    static GlobalValue g_markov_detection =
            GlobalValue ("MARKOV_DETECTION", "Use Markov-chain to improve individual sensing report",
                         BooleanValue (simulationParameters["markov_detection"].get<bool>()),
                         MakeBooleanChecker());

    static GlobalValue g_harmonic_detection =
            GlobalValue ("HARMONIC_DETECTION", "Use harmonic detection to prevent Byzantine attackers",
                         BooleanValue (simulationParameters["harmonic_detection"].get<bool>()),
                         MakeBooleanChecker());


    //       UE/eNB      [ X      Y        Z ]
    std::map<int, std::vector<double>> enbParameters;
    std::map<int, std::vector<double>> ueParameters;

    //       PU      [X      Y        Z      txPower  channelNumber     dutyCycle   period]
    std::map<int, std::vector<double>> puParameters;
    //Load simulation parameters from json file
    {
        //Load PU data
        picojson::object PUjson = inputJson["PU"].get<picojson::object>();
        for (picojson::value::object::const_iterator i = PUjson.begin(); i != PUjson.end(); i++)
        {
            if (!enableDSA)
                break;
            //Copy PU number
            int puId = std::stoi(i->first);

            //Copy contents
            picojson::object puContents = i->second.get<picojson::object>();

            //Read PU coordinates
            std::vector<double> coordinatesVector;
            picojson::array coordinatesArray = puContents["position"].get<picojson::array>();
            for (auto it = coordinatesArray.begin(); it != coordinatesArray.end(); it++)
                coordinatesVector.push_back(it->get<double>());

            //Read PU tx power, bw, fc, duty and period
            double channelNumber      = puContents["channel"].get<double>();
            double dutyCycle          = puContents["duty_cycle"].get<double>();
            double period             = puContents["period"].get<double>();
            double txPower            = puContents["tx_power"].get<double>();
            puParameters.emplace(puId, std::vector<double> {coordinatesVector[0], coordinatesVector[1], coordinatesVector[2], txPower, channelNumber, dutyCycle, period});

            LteEnbMac::nonDSAChannels.push_back(channelNumber);
        }
        
        //Load eNB data
        picojson::object eNBjson = inputJson["eNB"].get<picojson::object>();
        for (picojson::value::object::const_iterator i = eNBjson.begin(); i != eNBjson.end(); i++)
        {
            //Copy eNB number
            int enbId = std::stoi(i->first);

            //Copy contents
            picojson::object enbContents = i->second.get<picojson::object>();

            //Read eNB coordinates
            std::vector<double> coordinatesVector;
            picojson::array coordinatesArray = enbContents["position"].get<picojson::array>();
            for (auto it = coordinatesArray.begin(); it != coordinatesArray.end(); it++)
                coordinatesVector.push_back(it->get<double>());
            enbParameters.emplace(enbId, coordinatesVector);
        }

        //Load UE data
        picojson::object UEjson = inputJson["UE"].get<picojson::object>();
        for (picojson::value::object::const_iterator i = UEjson.begin(); i != UEjson.end(); i++)
        {
            //Copy UE number
            int ueId = std::stoi(i->first);
            //std::cout << ueId << std::endl;

            //Copy contents
            picojson::object ueContents = i->second.get<picojson::object>();

            //Read UE coordinates
            std::vector<double> coordinatesVector;
            picojson::array coordinatesArray = ueContents["position"].get<picojson::array>();
            for (auto it = coordinatesArray.begin(); it != coordinatesArray.end(); it++)
                coordinatesVector.push_back(it->get<double>());
            ueParameters.emplace(ueId, coordinatesVector);
        }
    }

    //Setup shadowing map
    if ((int)simulationParameters["Run"].get<double>() < 4)
        SpatiallyCorrelatedShadowingMap(0, 4.47, 110);
    else
        SpatiallyCorrelatedShadowingMap(0, 18*4.47, 110);// 18* is an adjustment factor for exponential-decay of spatial correlation

    //Print information
    bool printMcsTbs        = true;
    bool printEarfcn        = false;
    bool printRBs           = false;
    bool printAppTrace      = true;
    std::string traceAppFilename = "5grange_app_trace";

    //Trace info
    std::string pcapTraceFilename = "5grange_cdl";
    bool traceIpv4 = false;
    std::string traceRlcThroughputFilename = "5grange_rlc_throughput";
    bool traceRlcThroughput = false;
    std::string traceNetworkThrFilaname = "5grange_network_throughput";

    bool traceNetworkThr = false;
    bool tracePhy = true;
    std::string tracePhyFilename = "5grange_phy_trace";

    lteHelper->SetAttribute("Scheduler", StringValue("ns3::RrFfMacScheduler"));
    //lteHelper->SetAttribute("Scheduler", StringValue("ns3::CqaFfMacScheduler")); //QoS aware scheduler
    //lteHelper->SetAttribute("Scheduler", StringValue("ns3::NnFfMacScheduler")); //NN scheduler

    //1 Configure EPC e PGW
    Ptr<PointToPointEpcHelper> epcHelper = CreateObject<PointToPointEpcHelper>();
    lteHelper->SetEpcHelper(epcHelper);
    Ptr<Node> pgw = epcHelper->GetPgwNode();
    allNodes.Add(pgw);

    //2 Create the remote node (server on the internet)
    NodeContainer remoteHostContainer;
    remoteHostContainer.Create(1);
    allNodes.Add(remoteHostContainer);

    //3 Create eNB and UEs
    NodeContainer ueNodes;
    NodeContainer enbNodes;
    enbNodes.Create(enbParameters.size());
    ueNodes.Create(ueParameters.size());
    allNodes.Add(enbNodes);

    //4 Aloca posições dos dispositivos
    Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator>();
    positionAlloc->Add(Vector(   10.0,     0.0, 0.0));  // 0 - PGw
    positionAlloc->Add(Vector(    0.0,     0.0, 0.0));  // 1 - Internet

    for (auto & enbData: enbParameters)
    {
        positionAlloc->Add(Vector(enbData.second[0], enbData.second[1], enbData.second[2]));  // 2 - eNB

    }

    Ptr<ListPositionAllocator> positionAlloc2 = CreateObject<ListPositionAllocator>();

    for (auto & ueData : ueParameters)
    {
        positionAlloc2->Add(Vector( ueData.second[0], ueData.second[1], ueData.second[2])); //  1 - UE 0
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
    Ptr<Node> remoteHost = remoteHostContainer.Get(0);
    InternetStackHelper internet;
    internet.Install(remoteHostContainer);

    //7 Create backhaul link between the remote node and PGW
    PointToPointHelper p2ph;
    p2ph.SetDeviceAttribute("DataRate", DataRateValue(DataRate("100Gb/s")));
    p2ph.SetDeviceAttribute("Mtu", UintegerValue(15000));
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
    Ptr<Ipv4StaticRouting> remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting(remoteHost->GetObject<Ipv4>());
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
    for (uint32_t u = 0; u < ueNodes.GetN(); u++)
    {
        Ptr<Node> ueNode = ueNodes.Get(u);
        Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting(ueNode->GetObject<Ipv4>());
        ueStaticRouting->SetDefaultRoute(epcHelper->GetUeDefaultGatewayAddress(), 1);
        //for (uint32_t uu = 0; uu < ueNodes.GetN(); uu++)
        //{
        //    if (u == uu)
        //        continue;
        //    ueStaticRouting->AddHostRouteTo(ueNodes.Get(uu)->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal(),
        //                                epcHelper->GetUeDefaultGatewayAddress(),
        //                                1,
        //                                0);
        //}

    }



    //15 Configure and install applications
    uint16_t voipListenPort = 300;
    uint16_t webListenPort = 8080;

    ApplicationContainer serverApps;
    ApplicationContainer serverApp;
    ApplicationContainer clientApps;
    ApplicationContainer tempUeApps;

    enum simulationCase{
        VOIP_BASE_SCENARIO = 1<<0,
        WEB_BASE_SCENARIO  = 1<<1,
        STREAMING_BASE_SCENARIO = 1<<2,
        VIDEOCONFERENCE_BASE_SCENARIO = 1<<3,
    };
    LoaderTrafficHelper loader = LoaderTrafficHelper();


    uint16_t simulationScenario = 3;
    std::string executablePath = std::string(argv[0]); // when launching the simulations, we pass the absolute path to the executable

    std::size_t found = executablePath.find_last_of("/\\");
    executablePath = executablePath.substr(0,found+1); // get path with last separator

    std::string voip_charge_10s = executablePath + std::string ("voip_charge0_10s.json"); // absolute path to injected traffic
    if (simulationScenario & VOIP_BASE_SCENARIO)
    {
        //In this scenario we should have only two UEs talking to each other to see how the network behaves
        TcpEchoServerHelper echoServer(voipListenPort);
        serverApps.Add(echoServer.Install(ueNodes));
        tempUeApps = loader.LoadJsonTraffic(ueNodes.Get(0), ueNodes.Get(1)->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal(), voipListenPort, voip_charge_10s);
        clientApps.Add(tempUeApps);
        tempUeApps = loader.LoadJsonTraffic(ueNodes.Get(1), ueNodes.Get(0)->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal(), voipListenPort, voip_charge_10s);
        clientApps.Add(tempUeApps);
    }

    std::string web_charge_10s = executablePath + std::string ("web_charge0_10s.json");
    if (simulationScenario & WEB_BASE_SCENARIO)
    {
        //In this scenario we should have only two UEs talking to each other to see how the network behaves
        TcpEchoServerHelper echoServer(webListenPort);
        serverApps.Add(echoServer.Install(ueNodes));
        auto addr1 = ueNodes.Get(1)->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal();
        tempUeApps = loader.LoadJsonTraffic(ueNodes.Get(0), ueNodes.Get(1)->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal(), webListenPort, web_charge_10s);
        clientApps.Add(tempUeApps);
        auto addr0 = ueNodes.Get(0)->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal();

        tempUeApps = loader.LoadJsonTraffic(ueNodes.Get(1), ueNodes.Get(0)->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal(), webListenPort, web_charge_10s);
        clientApps.Add(tempUeApps);
    }





    //Echo server on remote host and echo clients on UEs
    //UdpEchoServerHelper echoServer(serverPort); // Porta #9
    //serverApp = echoServer.Install(remoteHost);
    //serverApps.Add(serverApp);
    serverApps.Start(Seconds(0.9));
    clientApps.Start(Seconds(1.0));



    //17 Create interference generators (PUs) and spectrum analyzers (1 per PU)
    NodeContainer waveformGeneratorNodes;
    waveformGeneratorNodes.Create(puParameters.size());

    NodeContainer spectrumAnalyzer;
    spectrumAnalyzer.Create(puParameters.size());

    NodeContainer waveNodes;
    waveNodes.Add(waveformGeneratorNodes);
    waveNodes.Add(spectrumAnalyzer);

    //18 add mobility model and positions to waveNodes (PUs and spectrum analyzer) to prevent errors during their setup
    Ptr<ListPositionAllocator> pos = CreateObject<ListPositionAllocator>();

    for (auto & puData : puParameters)
    {
        pos->Add(Vector( puData.second[0], puData.second[1], puData.second[2])); //  PU
    }

    for (auto & puData : puParameters)
    {
        pos->Add(Vector( puData.second[0], puData.second[1], puData.second[2])); //  PU companion / spectrum analyzer
    }

    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.SetPositionAllocator(pos);
    mobility.Install(waveNodes);

    //19 configure the interference generator (acting as a PU)
    int i = 0;
    double j = 0.3;

    NetDeviceContainer waveformGeneratorDevices;

    for (auto & puData: puParameters)
    {
         double basePsdWattsHz = pow (10.0, (puData.second[3] - 30) / 10.0); // convert dBm to W/Hz

         Ptr<TvSpectrumTransmitter> phy = CreateObject<TvSpectrumTransmitter>();
         phy->SetAttribute("StartFrequency", DoubleValue(carrierFreq+(channelBandwidth-60000)*(puData.second[4]-2)));
         phy->SetAttribute("ChannelBandwidth", DoubleValue(channelBandwidth-30000));
         phy->SetAttribute("BasePsd", DoubleValue(basePsdWattsHz));
         phy->SetAttribute("TvType", EnumValue(TvSpectrumTransmitter::TVTYPE_COFDM));//TVTYPE_8VSB or TVTYPE_ANALOG
         phy->CreateTvPsd();

         /* Test max PSD value */
         Ptr<SpectrumValue> psd = phy->GetTxPsd();

         WaveformGeneratorHelper waveformGeneratorHelper;
         waveformGeneratorHelper.SetChannel(lteHelper->GetDownlinkSpectrumChannel());
         waveformGeneratorHelper.SetTxPowerSpectralDensity(psd);

         waveformGeneratorHelper.SetPhyAttribute("Period", TimeValue(Seconds(puData.second[6])));   // corresponds to 60 Hz
         waveformGeneratorHelper.SetPhyAttribute("DutyCycle", DoubleValue(puData.second[5]));
         waveformGeneratorDevices.Add(waveformGeneratorHelper.Install(waveformGeneratorNodes.Get(i)));
         Simulator::Schedule(Seconds(2.5)+Seconds(puData.second[6]), &WaveformGenerator::Start, waveformGeneratorDevices.Get(
                 waveformGeneratorDevices.GetN()-1)->GetObject<NonCommunicatingNetDevice>()->GetPhy()->GetObject<WaveformGenerator>());
         i++;
    }


    lteHelper->EnableTraces ();

    Ptr<FlowMonitor> flowMonitor;
    FlowMonitorHelper flowHelper;
    flowMonitor = flowHelper.InstallAll();

    Ptr<RadioBearerStatsCalculator> rlcStats = lteHelper->GetRlcStats ();
    Ptr<RadioBearerStatsCalculator> pdcpStats = lteHelper->GetPdcpStats ();

    rlcStats->SetDlOutputFilename (data_path + "rlc_stats_dl.txt");
    rlcStats->SetUlOutputFilename (data_path + "rlc_stats_ul.txt");
    pdcpStats->SetDlPdcpOutputFilename (data_path + "pdcp_stats_dl.txt");
    pdcpStats->SetUlPdcpOutputFilename (data_path + "pdcp_stats_ul.txt");

    //Print Node ids
    int numberOfNodes = ueParameters.size();
    uint32_t m_packetSize       = 2000; //bytes
    double interPacketInterval  = 100;  //milliseconds
    std::vector<uint32_t> ueIds, enbIds;
    uint32_t  pgwId = pgw->GetId(), remoteHostId = remoteHost->GetId();
    NS_LOG_INFO("NODE IDs");
    NS_LOG_INFO("\tPGW: " << pgwId);
    NS_LOG_INFO("\tremoteHost: " << remoteHostId);
    NS_LOG_INFO("\teNB: ");
    for (int i = 0; i < enbNodes.GetN(); ++i)
    {
        enbIds.push_back(enbNodes.Get(i)->GetId());
        NS_LOG_INFO("\t\t eNB " << i << ": " << enbNodes.Get(i)->GetId());
    }
    NS_LOG_INFO("\tUEs: " << pgw->GetId());
    for (int i = 0; i < ueNodes.GetN(); ++i)
    {
        ueIds.push_back(ueNodes.Get(i)->GetId());
        NS_LOG_INFO("\t\t UE " << i << ": " << ueNodes.Get(i)->GetId());
    }

    //Print TBS and MCS for each subframe
    if (printMcsTbs)
    {
        Config::Connect ("/NodeList/*/DeviceList/*/$ns3::LteEnbNetDevice/LteEnbMac/DlScheduling", MakeCallback (&RangeDlSchedulingCallback));
        Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbMac/DlScheduling", MakeCallback (&RangeDlSchedulingCallback));
        //Config::Connect ("/NodeList/" + std::to_string(enbIds[0]) + "/DeviceList/0/$ns3::LteEnbNetDevice/LteEnbMac/DlScheduling", MakeCallback (&RangeDlSchedulingCallback));
        //Config::Connect ("/NodeList/" + std::to_string(enbIds[0]) + "/DeviceList/0/ComponentCarrierMap/*/LteEnbMac/DlScheduling", MakeCallback (&RangeDlSchedulingCallback));
        //Config::Connect ("/NodeList/" + std::to_string(enbIds[0]) + "/DeviceList/0/ComponentCarrierMap/*/LteEnbMac/UlScheduling",  MakeCallback (&RangeUlSchedulingCallback));
    }

    //Print RBs
    if (printRBs)
    {
        //Config::Connect ("/NodeList/2/DeviceList/" + std::to_string(enbIds[0]) + "/$ns3::LteEnbNetDevice/ComponentCarrierMap/*/FfMacScheduler/$ns3::PfFfMacScheduler/RBBitmapTrace",  MakeCallback (&RbBitmapTrace));

        //UE (Uplink)
        Config::Connect ("/NodeList/*/DeviceList/*/$ns3::LteUeNetDevice/ComponentCarrierMapUe/*/LteUePhy/StartTxDataframe", MakeCallback (&StartDataframeTxCallback));

        //eNB (Downlink)
        Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbPhy/StartTxDataframe", MakeCallback (&StartDataframeTxCallback));
    }

    if (tracePhy)
    {
        AsciiTraceHelper phy_ascii_trace;
        Ptr<OutputStreamWrapper> phy_trace = phy_ascii_trace.CreateFileStream (data_path + tracePhyFilename+ ".txt");
        Ptr<OutputStreamWrapper> phy_trace_lte = phy_ascii_trace.CreateFileStream (data_path + tracePhyFilename+ "_lte.txt");
        *phy_trace->GetStream() << "time,path,node,channel,rxtx,status,qtd_pkts,size" << std::endl;
        *phy_trace_lte->GetStream() << "time,path,node,channel,rxtx,% time,cellId,IMSI,RNTI,txMode,layer,mcs,size,rv,ndi,correct,ccId" << std::endl;

        //eNB
        Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbPhy/DlSpectrumPhy/RxEndOk", MakeBoundCallback (&PacketCallback, phy_trace, "ENB,DL,RX,OK"));
        Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbPhy/DlSpectrumPhy/RxEndError", MakeBoundCallback (&PacketCallback, phy_trace, "ENB,DL,RX,ERROR"));
        Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbPhy/DlSpectrumPhy/TxEnd", MakeBoundCallback (&PacketBurstCallback, phy_trace, "ENB,DL,TX,OK"));
        Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbPhy/UlSpectrumPhy/RxEndOk", MakeBoundCallback (&PacketCallback, phy_trace, "ENB,UL,RX,OK"));
        Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbPhy/UlSpectrumPhy/RxEndError", MakeBoundCallback (&PacketCallback, phy_trace, "ENB,UL,RX,ERROR"));
        Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbPhy/UlSpectrumPhy/TxEnd", MakeBoundCallback (&PacketBurstCallback, phy_trace, "ENB,UL,TX,OK"));
        Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbPhy/UlSpectrumPhy/UlPhyReception", MakeBoundCallback (&PhyRxCallback, phy_trace_lte, "ENB,UL"));
        Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbPhy/DlSpectrumPhy/DlPhyReception", MakeBoundCallback (&PhyRxCallback, phy_trace_lte, "ENB,DL"));
        Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbPhy/DlPhyTransmission", MakeBoundCallback (&PhyTxCallback, phy_trace_lte, "ENB,DL"));

        //UE
        Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMapUe/*/LteUePhy/DlSpectrumPhy/RxEndOk", MakeBoundCallback (&PacketCallback, phy_trace, "UE,DL,RX,OK"));
        Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMapUe/*/LteUePhy/DlSpectrumPhy/RxEndError", MakeBoundCallback (&PacketCallback, phy_trace, "UE,DL,RX,ERROR"));
        Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMapUe/*/LteUePhy/DlSpectrumPhy/TxEnd", MakeBoundCallback (&PacketBurstCallback, phy_trace, "UE,DL,TX,OK"));
        Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMapUe/*/LteUePhy/UlSpectrumPhy/RxEndOk", MakeBoundCallback (&PacketCallback, phy_trace, "UE,UL,RX,OK"));
        Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMapUe/*/LteUePhy/UlSpectrumPhy/RxEndError", MakeBoundCallback (&PacketCallback, phy_trace, "UE,UL,RX,ERROR"));
        Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMapUe/*/LteUePhy/UlSpectrumPhy/TxEnd", MakeBoundCallback (&PacketBurstCallback, phy_trace, "UE,UL,TX,OK"));
        Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMapUe/*/LteUePhy/DlSpectrumPhy/DlPhyReception", MakeBoundCallback (&PhyRxCallback, phy_trace_lte, "UE,DL"));
        Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMapUe/*/LteUePhy/UlPhyTransmission", MakeBoundCallback (&PhyTxCallback, phy_trace_lte, "UE,UL"));

        //RemoteHost e PGW p2p interface
        //p2ph.EnableAsciiAll("5grange_p2p_trace.txt");
        AsciiTraceHelper p2p_asciihelper;
        Ptr<OutputStreamWrapper> ascii_enb = p2p_asciihelper.CreateFileStream (data_path + "p2p_ascii_enb.txt");
        Ptr<OutputStreamWrapper> ascii_remote = p2p_asciihelper.CreateFileStream (data_path + "p2p_ascii_remote.txt");
        p2ph.EnableAscii(ascii_enb, enbIds[0], 2);
        p2ph.EnableAscii(ascii_remote, remoteHostId, 1);
    }

    //Print app trace
    if (printAppTrace)
    {
        AsciiTraceHelper app_ascii_trace;
        Ptr<OutputStreamWrapper> app_trace = app_ascii_trace.CreateFileStream (data_path + traceAppFilename + ".txt");
        *app_trace->GetStream() << "time,path,node,channel,rxtx,status,qtd_pkts,size" << std::endl;
        //RemoteHost
        //Config::Connect ("/NodeList/" + std::to_string(remoteHostId) + "/ApplicationList/0/$ns3::UdpEchoServer/RxWithAddresses", MakeBoundCallback (&PacketWithAddressCallback, app_trace, "RH -- TX OK"));
        for (int i = 0; i < ueIds.size(); i++)
        {
            //Recebido pelo UE
            Config::Connect ("/NodeList/" + std::to_string(ueIds[i]) + "/ApplicationList/0/$ns3::PacketSink/Rx", MakeBoundCallback (&PacketWithAddressCallback, app_trace, "UE,--,RX,OK"));
        }

        //Recebido pelo eNB, do remoteHost
        //Config::Connect ("/NodeList/" + std::to_string(enbIds[0]) + "/DeviceList/2/$ns3::PointToPointNetDevice/MacRx", MakeCallback (&PacketCallback));
    }

    //Trace Pcap
    if (traceIpv4)
    {
        internet.EnableAsciiIpv4All (data_path + pcapTraceFilename);
    }
    //internet.EnablePcapIpv4All(data_path+"fil.pcap");

    //Print Earfcn
    if (printEarfcn)
    {
        Ptr<LteEnbNetDevice> eNbDev = enbLteDevs.Get (0)->GetObject<LteEnbNetDevice> ();
        NS_LOG_INFO("eNB DL Earfcn: " << eNbDev->GetDlEarfcn () << " DL Carrier Frequency: " << LteSpectrumValueHelper::GetDownlinkCarrierFrequency (eNbDev->GetDlEarfcn ()) << " DL Band: " << (uint16_t)LteSpectrumValueHelper::GetDownlinkCarrierBand (eNbDev->GetDlEarfcn ()));
        NS_LOG_INFO("eNB DL Bandwidth: " << (int)eNbDev->GetDlBandwidth ());
        NS_LOG_INFO("eNB UL Earfcn: " << eNbDev->GetUlEarfcn () << " UL Carrier Frequency: " << LteSpectrumValueHelper::GetUplinkCarrierFrequency (eNbDev->GetUlEarfcn ()) << " UL Band: " << (uint16_t)LteSpectrumValueHelper::GetUplinkCarrierBand (eNbDev->GetUlEarfcn ()));
        NS_LOG_INFO("eNB UL Bandwidth: " << (int)eNbDev->GetUlBandwidth ());
    }

    Ipv4GlobalRoutingHelper g;
    Ptr<OutputStreamWrapper> routingStream = Create<OutputStreamWrapper>
            ("dynamic-global-routing.routes", std::ios::out);
    g.PrintRoutingTableAllAt (Seconds (1), routingStream);

    //23 Run simulation
    Simulator::Stop(Seconds(simulationParameters["ts"].get<double>()+2));
    Simulator::Run();


    if (traceRlcThroughput)
    {
        AsciiTraceHelper ascii_helper;
        Ptr<OutputStreamWrapper> rlc_output_dl = ascii_helper.CreateFileStream (data_path + traceRlcThroughputFilename+ "_dl.txt");

        NS_LOG_INFO("Simulation parameters:");
        NS_LOG_INFO("\t - Nodes: " << numberOfNodes);
        NS_LOG_INFO("\t - Packet size: " << m_packetSize << " bytes");
        NS_LOG_INFO("\t - Period: " << interPacketInterval << " ms");
        NS_LOG_INFO ("\t - Maximum theoretical throughput: " << (1000/4.6) * (2292) * 132/10e6 << " mbps");
        NS_LOG_INFO("DOWNLINK THROUGHPUT");
        std::vector <uint64_t> dlDataRxed;
        double epochDuration = rlcStats->GetEpoch().GetSeconds();
        double totalDlThr = 0.0;
        for (int i = 0; i < numberOfNodes; i++)
        {
            uint64_t imsi = ueLteDevs.Get (i)->GetObject<LteUeNetDevice> ()->GetImsi ();
            uint8_t lcId = 3;
            dlDataRxed.push_back (rlcStats->GetDlRxData (imsi, lcId));
            totalDlThr+=(double)dlDataRxed.at (i) / epochDuration;
            *rlc_output_dl->GetStream () << Simulator::Now().GetNanoSeconds () << "\t" << i << "\t" << (double)dlDataRxed.at (i) / epochDuration << "\t" << (m_packetSize + 32) * (1000/interPacketInterval) << std::endl;
            NS_LOG_INFO ("\tUE " << i << " imsi " << imsi << " bytes rxed " << (double)dlDataRxed.at (i) / epochDuration << " expected " << (m_packetSize + 32) * (1000/interPacketInterval) );
        }

        if (traceNetworkThr)
        {
            Ptr<OutputStreamWrapper> net_output_dl = ascii_helper.CreateFileStream (data_path + traceNetworkThrFilaname + "_dl.txt");
            double net_real = numberOfNodes*(m_packetSize + 32) * 8 / interPacketInterval / 1000;
            *net_output_dl->GetStream ()  << interPacketInterval << "\t" << numberOfNodes << "\t" << m_packetSize << "\t" << totalDlThr*8 / 1000 / 1000 << "\t" <<  net_real << std::endl;
        }

        NS_LOG_INFO ("\t Expected: " << numberOfNodes*(m_packetSize + 32) * 8 / interPacketInterval / 1000 << " mbps");
        NS_LOG_INFO ("\t Achieved: " << totalDlThr*8 / 1000 / 1000 << " mbps");


        Ptr<OutputStreamWrapper> rlc_output_up = ascii_helper.CreateFileStream (data_path + traceRlcThroughputFilename+ "_up.txt");

        NS_LOG_INFO ("UPLINK THROUGHPUT");
        std::vector <uint64_t> ulDataRxed;
        double totalUlThr = 0.0;
        for (int i = 0; i < numberOfNodes; i++)
        {
            uint64_t imsi = ueLteDevs.Get (i)->GetObject<LteUeNetDevice> ()->GetImsi ();
            uint8_t lcId = 3;
            ulDataRxed.push_back (rlcStats->GetUlRxData (imsi, lcId));
            totalUlThr+=(double)ulDataRxed.at (i) / epochDuration;

            *rlc_output_up->GetStream () << Simulator::Now().GetNanoSeconds () << "\t" << i << "\t" << (double)ulDataRxed.at (i) / epochDuration << "\t" << (m_packetSize + 32) * (1000/interPacketInterval) << std::endl;
            NS_LOG_INFO ("\tUE " << i << " imsi " << imsi << " bytes rxed " << (double)ulDataRxed.at (i) / epochDuration << " expected " << (m_packetSize + 32) * (1000/interPacketInterval) );
        }

        if (traceNetworkThr)
        {
            Ptr<OutputStreamWrapper> net_output_ul = ascii_helper.CreateFileStream (data_path + traceNetworkThrFilaname + "_ul.txt");
            *net_output_ul->GetStream () << interPacketInterval << "\t" << numberOfNodes << "\t" << m_packetSize << "\t" << totalUlThr*8 / 1000 / 1000 << "\t" <<  numberOfNodes*(m_packetSize + 32) * 8 / interPacketInterval / 1000 << std::endl;
        }

        NS_LOG_INFO ("\t Expected: " << numberOfNodes*(m_packetSize + 32) * 8 /interPacketInterval / 1000 << " mbps");
        NS_LOG_INFO ("\t Achieved: " << totalUlThr*8 / 1000 / 1000 << " mbps");
    }

    flowMonitor->SerializeToXmlFile("flow.xml", true, true);



    Simulator::Destroy();

    return 0;
}
