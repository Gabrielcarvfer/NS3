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

//Simple network setup
int main() {
    std::ios::sync_with_stdio(false);


    double simTime = 10;
    double enbTxPower              =  53.0; //dBm
    double enbGain                 =   9.0; //dBi
    double ueTxPower               =  23.0; //dBm
    double ueGain                  =   9.0; //dBi
    double carrierFrequency        = 869e6; //Hz
    double channelBandwidth        =  20e6; //Hz
    double ueTxPeriodSec           =   0.1; //sec     | 48Mbps throughput at the LTE uplink
    int    ueTxSizeBytes           =   6e5; //bytes  /
    std::string propagationModel   = "ns3::FriisPropagationLossModel"; //or ns3::RANGE5GPropagationLossModel

    //Default COLAB parameters
    bool   enableDSA               =  false; //if false, channels with PUs will be automatically flagged not to be used
    bool   SNRSensing              =  false; //if true, SNR based sensing curves are loaded/used instead of distance based sensing curves
    int    fusionAlgorithm         = LteEnbMac::MRG_1_OF_N;

    // Default MHM parameters
    int attackers_per_channel = 0;
    bool markov_detection = false;
    bool harmonic_detection = false;

    // Default 5G-RANGE parameters



    Config::SetDefault("ns3::LteEnbRrc::SrsPeriodicity", UintegerValue(160));
    Config::SetDefault("ns3::LteEnbMac::SpectrumSensing", BooleanValue(false));//for whatever reason, refuses to work
    Config::SetDefault("ns3::LteSpectrumPhy::SpectrumSensing", BooleanValue(false));//for whatever reason, refuses to work


    static GlobalValue g_attackers_per_channel =
            GlobalValue ("ATTACKERS_PER_CHANNEL", "Number of attackers per channel",
                         IntegerValue (attackers_per_channel),
                         MakeIntegerChecker<int64_t>());

    static GlobalValue g_markov_detection =
            GlobalValue ("MARKOV_DETECTION", "Use Markov-chain to improve individual sensing report",
                         BooleanValue (markov_detection),
                         MakeBooleanChecker());

    static GlobalValue g_harmonic_detection =
            GlobalValue ("HARMONIC_DETECTION", "Use harmonic detection to prevent Byzantine attackers",
                         BooleanValue (harmonic_detection),
                         MakeBooleanChecker());

    picojson::object inputJson = load_json("simulationParameters.json");

    //       numUE/eNB      [ X      Y        Z      txPower  Gain]
    std::map<int, std::vector<double>> enbParameters;
    std::map<int, std::vector<double>> ueParameters;

    //       numUE/eNB      [X      Y        Z      txPower  fc      bw      duty   period]
    std::map<int, std::vector<double>> puParameters;
    //Load simulation parameters from json file
    {

        picojson::object parameters = inputJson["SimulationParameters"].get<picojson::object>();

        simTime          = parameters["ts"].get<double>();
        carrierFrequency = parameters["fc"].get<double>();
        channelBandwidth = parameters["bw"].get<double>();
        fusionAlgorithm  = (int)parameters["fusionAlgorithm"].get<double>();
        propagationModel = parameters["propagationModel"].get<std::string>();
        enableDSA        = parameters["enableDSA"].get<bool>();
        SNRSensing       = parameters["SNRSensing"].get<bool>();
        ueTxPeriodSec    = parameters["ueTxPeriodSec"].get<double>();
        ueTxSizeBytes    = (int) parameters["ueTxSizeBytes"].get<double>();

        LteSpectrumPhy::SNRsensing = SNRSensing;

        //Load PU data
        picojson::object PUjson = inputJson["PU"].get<picojson::object>();
        for (picojson::value::object::const_iterator i = PUjson.begin(); i != PUjson.end(); i++)
        {
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
            double txPower            = puContents["tx_power"].get<double>();
            double bandwidth          = puContents["bw"].get<double>();
            double puCarrierFrequency = puContents["fc"].get<double>();
            double dutyCycle          = puContents["duty_cycle"].get<double>();
            double period             = puContents["period"].get<double>();
            puParameters.emplace(puId, std::vector<double> {coordinatesVector[0], coordinatesVector[1], coordinatesVector[2], txPower, puCarrierFrequency, bandwidth, dutyCycle, period});

            int puSubchannel = (int) (puCarrierFrequency-(carrierFrequency-channelBandwidth/2))/(channelBandwidth/4);
            if(!enableDSA)
                LteEnbMac::nonDSAChannels.push_back(puSubchannel);
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

            //Read eNB tx power and gain
            double txPower          = enbContents["tx_power"].get<double>();
            double antennaGain      = enbContents["gain"].get<double>();
            enbParameters.emplace(enbId, std::vector<double>{coordinatesVector[0], coordinatesVector[1], coordinatesVector[2], txPower, antennaGain});
            enbTxPower = txPower;
            enbGain    = antennaGain;
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

            //Read eNB tx power and gain
            double txPower          = ueContents["tx_power"].get<double>();
            double antennaGain      = ueContents["gain"].get<double>();
            ueParameters.emplace(ueId, std::vector<double> {coordinatesVector[0], coordinatesVector[1], coordinatesVector[2], txPower, antennaGain});
            ueTxPower = txPower;
            ueGain    = antennaGain;
        }
    }


    //LogComponentEnableAll(LOG_LEVEL_DEBUG);

    NodeContainer allNodes;
    Ptr<LteHelper> lteHelper = CreateObject<LteHelper>();

    //0.1 Configure channel bandwidth
    Config::SetDefault("ns3::LteEnbNetDevice::DlBandwidth", UintegerValue(100));
    Config::SetDefault("ns3::LteEnbNetDevice::UlBandwidth", UintegerValue(100));

    //0.2 Configure channel frequency
    Config::SetDefault("ns3::LteEnbNetDevice::DlEarfcn",    UintegerValue(2400)); // band 5 (~850MHz), check src/lte/model/lte-spectrum-value-helper.cc for references
    Config::SetDefault("ns3::LteEnbNetDevice::UlEarfcn",    UintegerValue(20400));// band 5 (~850MHz), check src/lte/model/lte-spectrum-value-helper.cc for references

    //0.3 Configure error model (disable error model for control channel, assuming it works on a different channel without interference)
    Config::SetDefault("ns3::LteSpectrumPhy::DataErrorModelEnabled", BooleanValue(true));
    Config::SetDefault("ns3::LteSpectrumPhy::CtrlErrorModelEnabled", BooleanValue(false));

    //0.4 Configure fusion algorithm for the collaborative sensing
    Config::SetDefault("ns3::LteEnbMac::FusionAlgorithm", UintegerValue(fusionAlgorithm));

    lteHelper->SetAttribute("Scheduler", StringValue("ns3::RrFfMacScheduler"));
    //lteHelper->SetAttribute("Scheduler", StringValue("ns3::CqaFfMacScheduler")); //QoS aware scheduler
    //lteHelper->SetAttribute("Scheduler", StringValue("ns3::NnFfMacScheduler")); //NN scheduler

    //60dBm = 1    kW
    //53dBm = 200  kW // Taken from
    //49dBm =  80   W // http://5g-range.eu/wp-content/uploads/2018/04/D3.1-Physical-layer-of-the-5G-RANGE-Part-I.zip
    //38dBm = 6.3   W
    //30dBm =   1   W
    //20dBm = 100  mW
    //10dBm =  10  mW
    // 0dBm =   1  mW


    //0.5 Configure Tx power for UEs and eNB
    Config::SetDefault("ns3::LteEnbPhy::TxPower", DoubleValue(enbTxPower));
    Config::SetDefault("ns3::LteUePhy::TxPower",  DoubleValue(ueTxPower));
    Config::SetDefault("ns3::LteUePhy::EnableUplinkPowerControl",  BooleanValue(false));


    Config::SetDefault("ns3::RANGE5GPropagationLossModel::K-value", DoubleValue(4));


    //0.6 Configure antenna gains for UEs and eNB
    lteHelper->SetEnbAntennaModelAttribute("Gain", DoubleValue(enbGain)); // Taken from
    lteHelper->SetUeAntennaModelAttribute( "Gain", DoubleValue(ueGain)); // http://5g-range.eu/wp-content/uploads/2018/04/D3.1-Physical-layer-of-the-5G-RANGE-Part-I.zip

    //0.7 Select the eNB MAC Scheduler

    //0.8 Select the propagation loss model
    std::stringstream ss;
    ss << propagationModel << "::Frequency";
    Config::SetDefault(ss.str(), DoubleValue(carrierFrequency));
    lteHelper->SetAttribute("PathlossModel", StringValue(propagationModel));


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

    // interface 0 is localhost/loopback, 1 is the p2p device
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

    //13 Modify UEs to use the EPC as the gateway (GPRS tunneling through the eNB)
    for (uint32_t u = 0; u < ueNodes.GetN(); ++u) {
        Ptr<Node> ueNode = ueNodes.Get(u);
        Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting(ueNode->GetObject<Ipv4>());
        ueStaticRouting->SetDefaultRoute(epcHelper->GetUeDefaultGatewayAddress(), 1);
    }

    //14 Associate UEs to the eNB
    lteHelper->Attach(ueLteDevs, enbLteDevs.Get(0));

    //15 Configure and install applications
    uint16_t serverPort = 9;

    UdpEchoServerHelper echoServer(serverPort); // Porta #9
    ApplicationContainer serverApps;
    ApplicationContainer serverApp;

//#define UE_SRV
#ifndef UE_SRV
    serverApp = echoServer.Install(remoteHost);
#else
    serverApp = echoServer.Install(ueNodes.Get(0));
#endif
    serverApps.Add(serverApp);
    serverApp.Start(Seconds(0.1));

//ECHO APP
#ifndef UE_SRV
    Ipv4Address serverAddress = remoteHost->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal();
    UdpEchoClientHelper echoClient(serverAddress, serverPort);
#else
    Ipv4Address serverAddress = ueNodes.Get(0)->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal();
    UdpEchoClientHelper echoClient(serverAddress, serverPort);
#endif
    echoClient.SetAttribute("MaxPackets", UintegerValue(1000000));
    echoClient.SetAttribute("Interval", TimeValue(Seconds(ueTxPeriodSec)));
    echoClient.SetAttribute("PacketSize", UintegerValue(ueTxSizeBytes));

    ApplicationContainer clientApps;
#ifndef UE_SRV
    clientApps.Add(echoClient.Install(ueNodes));
#else
    clientApps.Add(echoClient.Install(remoteHost));
#endif
    clientApps.Start(Seconds(0.2));



    //16 Colect LTE and P2P traces
    //lteHelper->EnableTraces();
    p2ph.EnablePcapAll("p2p", false);


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
         phy->SetAttribute("StartFrequency", DoubleValue(puData.second[4]));
         phy->SetAttribute("ChannelBandwidth", DoubleValue(puData.second[5]));
         phy->SetAttribute("BasePsd", DoubleValue(basePsdWattsHz));
         phy->SetAttribute("TvType", EnumValue(TvSpectrumTransmitter::TVTYPE_COFDM));//TVTYPE_8VSB or TVTYPE_ANALOG
         phy->CreateTvPsd();

         /* Test max PSD value */
         Ptr<SpectrumValue> psd = phy->GetTxPsd();

         WaveformGeneratorHelper waveformGeneratorHelper;
         waveformGeneratorHelper.SetChannel(lteHelper->GetDownlinkSpectrumChannel());
         waveformGeneratorHelper.SetTxPowerSpectralDensity(psd);

         waveformGeneratorHelper.SetPhyAttribute("Period", TimeValue(Seconds(puData.second[7])));   // corresponds to 60 Hz
         waveformGeneratorHelper.SetPhyAttribute("DutyCycle", DoubleValue(puData.second[6]));
         waveformGeneratorDevices.Add(waveformGeneratorHelper.Install(waveformGeneratorNodes.Get(i)));
         Simulator::Schedule(Seconds(2.5)+Seconds(puData.second[7]), &WaveformGenerator::Start, waveformGeneratorDevices.Get(
                 waveformGeneratorDevices.GetN()-1)->GetObject<NonCommunicatingNetDevice>()->GetPhy()->GetObject<WaveformGenerator>());
         i++;
    }


    //20 capture the spectrum transmissions with the spectrum analyzer
    //SpectrumAnalyzerHelper spectrumAnalyzerHelper;
    //spectrumAnalyzerHelper.SetChannel (lteHelper->GetDownlinkSpectrumChannel());
    //Ptr<LteEnbNetDevice> enbNetDev = enbLteDevs.Get(0)->GetObject<LteEnbNetDevice>();
    //Ptr<LteEnbPhy> enbPhy = enbNetDev->GetPhy();
    //Ptr<LteSpectrumPhy> enbSpectrPhy = enbPhy->GetUlSpectrumPhy();
    //Ptr<const SpectrumModel> rxSpectrumModel = enbSpectrPhy->GetRxSpectrumModel();
    //Ptr<SpectrumModel> model = Copy(rxSpectrumModel);
    //spectrumAnalyzerHelper.SetRxSpectrumModel(SpectrumModelRANGE);
    //spectrumAnalyzerHelper.SetPhyAttribute ("Resolution", TimeValue (MilliSeconds (1)));

    //From lte-spectrum-value-helper.cc
    //const double kT_dBm_Hz = -174.0;  // dBm/Hz
    //double kT_W_Hz = std::pow (10.0, (kT_dBm_Hz - 30) / 10.0);
    //double noiseFigureLinear = std::pow (10.0, enbPhy->GetNoiseFigure() / 10.0);
    //double noisePowerSpectralDensity =  kT_W_Hz * noiseFigureLinear;

    //spectrumAnalyzerHelper.SetPhyAttribute ("NoisePowerSpectralDensity", DoubleValue (noisePowerSpectralDensity));  // -174 dBm/Hz
    //spectrumAnalyzerHelper.EnableAsciiAll ("spectrum-analyzer-output");

    //NetDeviceContainer spectrumDevice;
    //spectrumDevice = spectrumAnalyzerHelper.Install(spectrumAnalyzer);

    //21 install the Flow monitor
    Ptr<FlowMonitor> flowMonitor;
    FlowMonitorHelper flowHelper;
    flowMonitor = flowHelper.InstallAll();

    //22 Export the netanim animation for the simulation

    //BaseStationNetDevice b;
    //SubscriberStationNetDevice s;
    //CsmaNetDevice c;
    //UanNetDevice u;

    //AnimationInterface anim("anim.xml");
    //anim.SetMaxPktsPerTraceFile(0xFFFFFFFF);
    //anim.EnablePacketMetadata(true);


    //23 Run simulation
    Simulator::Stop(Seconds(simTime));
    Simulator::Run();

    //24 Dump flowmonitor results
    flowMonitor->SerializeToXmlFile("flow.xml", true, true);

    Simulator::Destroy();

    return 0;
}
