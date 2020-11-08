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
    ns3::RngSeedManager::SetSeed(good_seed());
    std::cout << "Seed " << ns3::RngSeedManager::GetSeed() << std::endl;

    std::ios::sync_with_stdio(false);
    std::string data_path       = "./output/"; //folder to save results

    picojson::object inputJson = load_json("simulationParameters.json");
    picojson::object simulationParameters = inputJson["SimulationParameters"].get<picojson::object>();

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
            //carrierFreq = g_eutraChannelNumbers[i].fUlLow;
            dlEarfcn = g_eutraChannelNumbers[i].nOffsDl;
            ulEarfcn = g_eutraChannelNumbers[i].nOffsUl;
            carrierFreq *= 1000000; // MHz to Hz
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

    unsigned int numerology = (int)simulationParameters["numerology"].get<double>();
    Config::SetDefault("ns3::LteHelper::Numerology", UintegerValue(numerology));
    Config::SetDefault("ns3::LteAmc::Numerology", UintegerValue(numerology));

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

            //LteEnbMac::nonDSAChannels.push_back(channelNumber);
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
    }


    //15 Configure and install applications

    ApplicationContainer serverApps;
    ApplicationContainer serverApp;
    ApplicationContainer clientApps;
    ApplicationContainer tempUeApps;

    enum simulationCase{
        VOIP_BASE_SCENARIO            = 1<<0,
        WEB_BASE_SCENARIO             = 1<<1,
        STREAMING_BASE_SCENARIO       = 1<<2,
        VIDEOCONFERENCE_BASE_SCENARIO = 1<<3,
        BACKHAUL_BASE_SCENARIO        = 1<<4,
        IOT_BASE_SCENARIO             = 1<<5,
    };

    enum ApplicationPorts{
        voipListenPort      = 8000,
        videoconfListenPort = 8001,
        webListenPort       = 8002,
        streamingListenPort = 8003,
        backhaulListenPort  = 8004,
        iotListenPort       = 8005,
    };
    LoaderTrafficHelper loader = LoaderTrafficHelper();


    uint32_t simulationCase = 0x0FF; // Set to run everything

    simulationCase = (unsigned)simulationParameters["SimulationCase"].get<double>(); // overrided by settings file

    std::string executablePath = std::string(argv[0]); // when launching the simulations, we pass the absolute path to the executable

    std::size_t found = executablePath.find_last_of("/\\");
    executablePath = executablePath.substr(0,found+1); // get path with last separator

    int numUes = ueNodes.GetN();

    if (simulationCase & VOIP_BASE_SCENARIO)
    {
        uint16_t voipListenPort   = ApplicationPorts::voipListenPort;
        std::string voip_workload = executablePath + std::string ("voip_workload0_100s.json"); // absolute path to injected traffic

        std::map<std::pair<uint16_t, uint16_t>, bool> voipPairs;
        if (numUes == 2)
        {
            // If only two UEs in voip scenario, assume both are talking to each other with something similar to a conversation
            voipPairs.emplace(std::make_pair(0, 1), true);
        }
        else
        {
            // We generate random pairs of UEs and setup these applications to have something similar to a conversation
            make_ue_pairs(numUes, 0.3, voipPairs);
        }

        std::set<uint16_t> uesWithVoip;
        for (auto uePairsIt = voipPairs.begin(); uePairsIt != voipPairs.end(); uePairsIt++)
        {
            unsigned ue0 = uePairsIt->first.first;
            unsigned ue1 = uePairsIt->first.second;
            uesWithVoip.insert(ue0);
            uesWithVoip.insert(ue1);
            tempUeApps = loader.LoadJsonTraffic(ueNodes.Get(ue0),
                                                ueNodes.Get(ue1)->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal(),
                                                voipListenPort,
                                                voip_workload,
                                                false);
            clientApps.Add(tempUeApps);
            tempUeApps = loader.LoadJsonTraffic(ueNodes.Get(ue1),
                                                ueNodes.Get(ue0)->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal(),
                                                voipListenPort,
                                                voip_workload,
                                                false);
            clientApps.Add(tempUeApps);
        }
        PacketSinkHelper ulPacketSinkHelper ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), voipListenPort));
        for (auto ue : uesWithVoip)
            serverApps.Add(ulPacketSinkHelper.Install(ueNodes.Get(ue)));
    }

    if (simulationCase & VIDEOCONFERENCE_BASE_SCENARIO)
    {
        uint16_t videoconfListenPort   = ApplicationPorts::videoconfListenPort;
        std::string videoconf_workload = executablePath + std::string ("videoconf_workload0_100s.json"); // absolute path to injected traffic

        std::map<std::pair<uint16_t, uint16_t>, bool> videoconfPairs;
        if (numUes == 2)
        {
            // If only two UEs in voip scenario, assume both are talking to each other with something similar to a conversation
            videoconfPairs.emplace(std::make_pair(0, 1), true);
        }
        else
        {
            // We generate random pairs of UEs and setup these applications to have something similar to a conversation
            make_ue_pairs(numUes, 0.05, videoconfPairs);
        }

        std::set<uint16_t> uesWithVideoconf;
        for (auto uePairsIt = videoconfPairs.begin(); uePairsIt != videoconfPairs.end(); uePairsIt++)
        {
            unsigned ue0 = uePairsIt->first.first;
            unsigned ue1 = uePairsIt->first.second;
            uesWithVideoconf.insert(ue0);
            uesWithVideoconf.insert(ue1);
            tempUeApps = loader.LoadJsonTraffic(ueNodes.Get(ue0),
                                                ueNodes.Get(ue1)->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal(),
                                                videoconfListenPort,
                                                videoconf_workload,
                                                false);
            clientApps.Add(tempUeApps);
            tempUeApps = loader.LoadJsonTraffic(ueNodes.Get(ue1),
                                                ueNodes.Get(ue0)->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal(),
                                                videoconfListenPort,
                                                videoconf_workload,
                                                false);
            clientApps.Add(tempUeApps);
        }
        PacketSinkHelper ulPacketSinkHelper ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), videoconfListenPort));
        for (auto ue : uesWithVideoconf)
            serverApps.Add(ulPacketSinkHelper.Install(ueNodes.Get(ue)));
    }

    if (simulationCase & WEB_BASE_SCENARIO)
    {
        uint16_t webListenPort   = ApplicationPorts::webListenPort;
        std::string web_workload = executablePath + std::string ("web_workload0_100s.json");

        // client will return 30% of downlink payload to represent uplink requests to the server
        TcpEchoServerHelper echoServer(webListenPort, 0.3);

        if (numUes == 2)
        {
            //We assume both server and client are inside the same cell for measurements purposes only
            //Node 0 acts like the server and node 1 like an user, but requests are injected in the inverse order (server->client->server)
            serverApps.Add(echoServer.Install(ueNodes.Get(1)));
            tempUeApps = loader.LoadJsonTraffic(ueNodes.Get(0),
                                                ueNodes.Get(1)->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal(),
                                                webListenPort,
                                                web_workload,
                                                true);
            clientApps.Add(tempUeApps);
        }
        else
        {
            // For internet select a fraction (70%) of random UEs to receive the injected traffic coming from the remotehost
            unsigned numUesWeb = numUes * 0.7;

            std::map<uint16_t, bool> uesWithWeb;
            while(numUesWeb > 0)
            {
                unsigned ue0 = rand() % numUes;

                if (uesWithWeb.find(ue0) != uesWithWeb.end())
                    continue;

                uesWithWeb.emplace(ue0, true);

                // this is added to the client apps container, but acts as the server on the remote host
                tempUeApps = loader.LoadJsonTraffic(remoteHost,
                                                    ueNodes.Get(ue0)->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal(),
                                                    webListenPort,
                                                    web_workload,
                                                    true);
                clientApps.Add(tempUeApps);

                // this is added to the server apps container, but acts as the client on the UE
                serverApps.Add(echoServer.Install(ueNodes.Get(ue0)));
                numUesWeb--;
            }
        }
    }

    if (simulationCase & STREAMING_BASE_SCENARIO)
    {
        uint16_t streamingListenPort   = ApplicationPorts::streamingListenPort;
        std::string streaming_workload = executablePath + std::string ("stream_workload0_9mbps_100s.json");//1080p stream

        // client will return 5% of downlink payload to represent uplink requests to the server
        TcpEchoServerHelper echoServer(streamingListenPort, 0.1);

        if (numUes == 2)
        {
            //We assume both server and client are inside the same cell for measurements purposes only
            //Node 0 acts like the server and node 1 like an user, but requests are injected in the inverse order (server->client->server)
            serverApps.Add(echoServer.Install(ueNodes.Get(1)));
            tempUeApps = loader.LoadJsonTraffic(ueNodes.Get(0),
                                                ueNodes.Get(1)->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal(),
                                                streamingListenPort,
                                                streaming_workload,
                                                true);
            clientApps.Add(tempUeApps);
        }
        else
        {
            // For internet select a fraction (10%) of random UEs to receive the injected traffic coming from the remotehost
            unsigned numUesStreaming = numUes * 0.1;
            std::map<uint16_t, bool> uesWithStreaming;
            while(numUesStreaming > 0)
            {
                unsigned ue0 = rand() % numUes;

                if (uesWithStreaming.find(ue0) != uesWithStreaming.end())
                    continue;

                uesWithStreaming.emplace(ue0, true);

                // this is added to the client apps container, but acts as the server on the remote host
                tempUeApps = loader.LoadJsonTraffic(remoteHost,
                                                    ueNodes.Get(ue0)->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal(),
                                                    streamingListenPort,
                                                    streaming_workload,
                                                    true);
                clientApps.Add(tempUeApps);

                // this is added to the server apps container, but acts as the client on the UE
                serverApps.Add(echoServer.Install(ueNodes.Get(ue0)));
                numUesStreaming--;
            }
        }
    }

    if (simulationCase & BACKHAUL_BASE_SCENARIO)
    {
        uint16_t backhaulListenPort = ApplicationPorts::backhaulListenPort;
        std::string backhaul_workload_downlink = executablePath + std::string ("backhaul_dl_workload0_100s.json");
        std::string backhaul_workload_uplink   = executablePath + std::string ("backhaul_ul_workload0_100s.json");

        // the remote host sends an entire subnetwork dl traffic to a single UE, to simulate backhaul scenarios
        tempUeApps = loader.LoadJsonTraffic(remoteHost,
                                            ueNodes.Get(0)->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal(),
                                            backhaulListenPort,
                                            backhaul_workload_downlink,
                                            false);
        clientApps.Add(tempUeApps);

        // the ue sends an entire subnetwork ul traffic to the remote host, to simulate backhaul scenarios
        tempUeApps = loader.LoadJsonTraffic(ueNodes.Get(0),
                                            remoteHost->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal(),
                                            backhaulListenPort,
                                            backhaul_workload_uplink,
                                            false);
        clientApps.Add(tempUeApps);
    }

    if (simulationCase & IOT_BASE_SCENARIO)
    {
        uint16_t iotListenPort   = ApplicationPorts::iotListenPort;
        std::string iot_workload = executablePath + std::string("iot_workload0_100s_100nodes.json");

        PacketSinkHelper ulPacketSinkHelper ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), iotListenPort));
        //serverApps.Add(ulPacketSinkHelper.Install(remoteHost));
        serverApps.Add(ulPacketSinkHelper.Install(ueNodes.Get(0)));
        
        for(unsigned i = 1; i < numUes; i++)
        {
            //We assume all devices are IOT sinks, transmitting traffic of 100 IoT devices each and sending traffic to the same remote server
            tempUeApps = loader.LoadJsonTraffic(ueNodes.Get(i),
                                                //remoteHost->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal(),
                                                ueNodes.Get(0)->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal(),
                                                iotListenPort,
                                                iot_workload,
                                                false);
            clientApps.Add(tempUeApps);
        }

    }

    //Start servers before starting clients
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
    NetDeviceContainer waveformGeneratorDevices;

    for (auto & puData: puParameters)
    {
         Ptr<TvSpectrumTransmitter> phy = CreateObject<TvSpectrumTransmitter>();
         double startFreq = carrierFreq+(channelBandwidth-60000)*(puData.second[4]-2)+15000;
         double bandwidth = channelBandwidth-30000;
         phy->SetAttribute("StartFrequency", DoubleValue(startFreq));
         phy->SetAttribute("ChannelBandwidth", DoubleValue(bandwidth));
         phy->SetAttribute("BasePsd", DoubleValue(puData.second[3]));
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
         Simulator::Schedule(Seconds(1.5), &WaveformGenerator::Start, waveformGeneratorDevices.Get(
                 i)->GetObject<NonCommunicatingNetDevice>()->GetPhy()->GetObject<WaveformGenerator>());
         i++;
    }

    Ptr<FlowMonitor> flowMonitor;
    FlowMonitorHelper flowHelper;
    flowMonitor = flowHelper.InstallAll();

    //23 Run simulation
    Simulator::Stop(Seconds(simulationParameters["ts"].get<double>()+2));
    Simulator::Run();

    flowMonitor->SerializeToXmlFile("flow.xml", true, true);


    Simulator::Destroy();

    return 0;
}
