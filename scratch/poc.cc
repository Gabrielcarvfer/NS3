//
// Created by Gabriel Ferreira (@gabrielcarvfer) on 04/04/2019.
//

/*
 *
 * In this scenario, we have two UEs and an eNB
 *
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

//Para netanim
#include <ns3/netanim-module.h>
#include <ns3/bs-net-device.h>
#include <ns3/csma-module.h>
#include <ns3/uan-module.h>

using namespace ns3;

#include <map>
#include <ns3/contrib-haraldott-module.h>

//Simple network setup
int main()
{
    std::ios::sync_with_stdio(false);

    //LogComponentEnableAll(LOG_LEVEL_DEBUG);

    double simTime = 5;

    NodeContainer allNodes;
    Config::SetDefault ("ns3::LteEnbNetDevice::DlBandwidth", UintegerValue (100));
    Config::SetDefault ("ns3::LteEnbNetDevice::UlBandwidth", UintegerValue (100));

    Config::SetDefault ("ns3::LteSpectrumPhy::DataErrorModelEnabled", BooleanValue (true));
    Config::SetDefault ("ns3::LteSpectrumPhy::CtrlErrorModelEnabled", BooleanValue (false));

    Config::SetDefault("ns3::LteEnbMac::FusionAlgorithm", UintegerValue(LteEnbMac::MRG_AND));

    //60dBm = 1kW
    //38dBm = 6.3W
    //30dBm = 1W
    //20dBm = 100mW
    //10dBm =  10mW
    // 0dBm =   1mW
    Config::SetDefault("ns3::LteEnbPhy::TxPower", DoubleValue(38.0));
    Config::SetDefault("ns3::LteUePhy::TxPower" , DoubleValue(30.0));


    //1 Configure EPC e PGW
    Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();
    lteHelper->SetAttribute("Scheduler", StringValue("ns3::CqaFfMacScheduler")); //QoS aware scheduler

    lteHelper->SetAttribute ("PathlossModel", StringValue ("ns3::FriisPropagationLossModel"));         // Default
    //lteHelper->SetAttribute ("PathlossModel", StringValue ("ns3::RANGE5GPropagationLossModel"));


    Ptr<PointToPointEpcHelper>  epcHelper = CreateObject<PointToPointEpcHelper> ();
    lteHelper->SetEpcHelper (epcHelper);
    Ptr<Node> pgw = epcHelper->GetPgwNode ();
    allNodes.Add(pgw);

    //2 Creates the remote node (server on the internet)
    NodeContainer remoteHostContainer;
    remoteHostContainer.Create (1);
    allNodes.Add(remoteHostContainer);

    //3 Create eNB and UEs
    NodeContainer ueNodes;
    NodeContainer enbNodes;
    enbNodes.Create(1);
    ueNodes.Create(2);
    allNodes.Add(enbNodes);
    //allNodes.Add(ueNodes);

// City positions
// Unaí         50000, 50000, 0
// Natalândia   66000, 94000, 0

    //4 Aloca posições dos dispositivos
    Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
    positionAlloc->Add (Vector (    10.0,      0.0,  0.0));  // 0 - PGw
    positionAlloc->Add (Vector (     0.0,      0.0,  0.0));  // 1 - Internet
    positionAlloc->Add (Vector ( 50000.0,  50000.0,  0.0));  // 2 - eNB

    Ptr<ListPositionAllocator> positionAlloc2 = CreateObject<ListPositionAllocator> ();

    //Linear topology
    positionAlloc2->Add(Vector ( 66000.0,  94000.0,  0.0));  // 3 - UE 0
    positionAlloc2->Add(Vector (100000.0,  50000.0,  0.0));  // 4 - UE 1


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
    Ptr<Node> remoteHost = remoteHostContainer.Get (0);
    InternetStackHelper internet;
    internet.Install (remoteHostContainer);

    //7 Create backhaul link between the remote node and PGW
    PointToPointHelper p2ph;
    p2ph.SetDeviceAttribute ("DataRate", DataRateValue (DataRate ("100Gb/s")));
    p2ph.SetDeviceAttribute ("Mtu", UintegerValue (15000));
    p2ph.SetChannelAttribute ("Delay", TimeValue (Seconds (0.010)));
    NetDeviceContainer internetDevices = p2ph.Install (pgw, remoteHost);

    //8 Configure address of the PGW and the external node (subnet 1.0.0.0/8)
    Ipv4AddressHelper ipv4h;
    ipv4h.SetBase ("1.0.0.0", "255.0.0.0");
    Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign (internetDevices);

    // interface 0 is localhost/loopback, 1 is the p2p device
    Ipv4Address remoteHostAddr = internetIpIfaces.GetAddress (1);

    //9 Configures static routing between internal and external IPs of the PGW (7.0.0.0 e 1.0.0.0)
    //      Allows external nodes (internet) to reach UEs
    Ipv4StaticRoutingHelper ipv4RoutingHelper;
    Ptr<Ipv4StaticRouting> remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting (remoteHost->GetObject<Ipv4> ());
    remoteHostStaticRouting->AddNetworkRouteTo (Ipv4Address ( "7.0.0.0"), Ipv4Mask ("255.0.0.0"), 1);

    //10 Configures antenna model
    //lteHelper->SetEnbAntennaModelType ("ns3::CosineAntennaModel");
    //lteHelper->SetUeAntennaModelType  ("ns3::CosineAntennaModel");
    //lteHelper->SetEnbAntennaModelAttribute ("Orientation", DoubleValue (0.0));
    //lteHelper->SetEnbAntennaModelAttribute ("Beamwidth",   DoubleValue (35.0));
    lteHelper->SetEnbAntennaModelAttribute ("Gain",     DoubleValue (8.0));
    lteHelper->SetUeAntennaModelAttribute  ("Gain",     DoubleValue (2.0));

    //11 Installs eNB e UE network devices
    NetDeviceContainer enbLteDevs = lteHelper->InstallEnbDevice (enbNodes);
    NetDeviceContainer ueLteDevs = lteHelper->InstallUeDevice (ueNodes);


    //12 Installs TCP/IP networks stacks on the LTE devices and assign their addresses
    internet.Install (ueNodes);
    Ipv4InterfaceContainer ueIpIface;
    ueIpIface = epcHelper->AssignUeIpv4Address (NetDeviceContainer (ueLteDevs));

    //13 Modify UEs to use the EPC as the gateway (GPRS tunneling through the eNB)
    for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
    {
        Ptr<Node> ueNode = ueNodes.Get (u);
        Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting (ueNode->GetObject<Ipv4> ());
        ueStaticRouting->SetDefaultRoute (epcHelper->GetUeDefaultGatewayAddress (), 1);
    }

    //14 Associate UEs to the eNB
    lteHelper->Attach (ueLteDevs, enbLteDevs.Get(0));

    //15 Configures and install applications
    uint16_t serverPort = 9;

    UdpEchoServerHelper echoServer(serverPort); // Porta #9
    ApplicationContainer serverApps;
    ApplicationContainer serverApp;

    serverApp = echoServer.Install(remoteHost);
    serverApp.Start(Seconds(0.1));
    serverApps.Add(serverApp);

    //ECHO APP
    Ipv4Address serverAddress = remoteHost->GetObject<Ipv4>()->GetAddress(1,0).GetLocal();
    UdpEchoClientHelper echoClient(serverAddress, serverPort);
    echoClient.SetAttribute("MaxPackets", UintegerValue(1000000));
    echoClient.SetAttribute("Interval", TimeValue(MicroSeconds(100)));
    echoClient.SetAttribute("PacketSize", UintegerValue(6000));

    ApplicationContainer clientApps;
    clientApps.Add(echoClient.Install(ueNodes));
    clientApps.Start (Seconds (0.2));



    //16 Colect LTE and P2P traces
    lteHelper->EnableTraces ();
    //p2ph.EnablePcapAll("natalandia_p2p", true);


    //17 configure the interference generator (acting as a PU)
    NodeContainer waveformGeneratorNodes;
    waveformGeneratorNodes.Create(1);
    Ptr<SpectrumValue> mwoPsd =  MicrowaveOvenSpectrumValueHelper::CreatePowerSpectralDensityMwo1 (); //Basic microwave oven interference

    for (auto valIt = mwoPsd->ValuesBegin(); valIt != mwoPsd->ValuesEnd(); valIt++)
    {
        //std::cout << *valIt << " ";
        *valIt /= 8;//Decrease power levels
        //*valIt *= 16;//Increase power levels
    }
    //std::cout << std::endl;
    WaveformGeneratorHelper waveformGeneratorHelper;
    waveformGeneratorHelper.SetChannel (lteHelper->GetDownlinkSpectrumChannel());
    waveformGeneratorHelper.SetTxPowerSpectralDensity (mwoPsd);

    waveformGeneratorHelper.SetPhyAttribute ("Period", TimeValue (Seconds (1.0)));   // corresponds to 60 Hz
    waveformGeneratorHelper.SetPhyAttribute ("DutyCycle", DoubleValue (0.5));
    NetDeviceContainer waveformGeneratorDevices = waveformGeneratorHelper.Install (waveformGeneratorNodes);
    Simulator::Schedule (Seconds (2.5), &WaveformGenerator::Start, waveformGeneratorDevices.Get (0)->GetObject<NonCommunicatingNetDevice>()->GetPhy ()->GetObject<WaveformGenerator> ());



    //18 capture the spectrum transmissions
    NodeContainer spectrumAnalyzer;
    spectrumAnalyzer.Create(1);

    SpectrumAnalyzerHelper spectrumAnalyzerHelper;
    spectrumAnalyzerHelper.SetChannel (lteHelper->GetDownlinkSpectrumChannel());
    Ptr<LteEnbNetDevice> enbNetDev = enbLteDevs.Get(0)->GetObject<LteEnbNetDevice>();
    Ptr<LteEnbPhy> enbPhy = enbNetDev->GetPhy();
    Ptr<LteSpectrumPhy> enbSpectrPhy = enbPhy->GetUlSpectrumPhy();
    Ptr<const SpectrumModel> rxSpectrumModel = enbSpectrPhy->GetRxSpectrumModel();
    Ptr<SpectrumModel> model = Copy(rxSpectrumModel);
    //spectrumAnalyzerHelper.SetRxSpectrumModel ( model);
    spectrumAnalyzerHelper.SetRxSpectrumModel(SpectrumModelLte);
    spectrumAnalyzerHelper.SetPhyAttribute ("Resolution", TimeValue (MilliSeconds (1)));

    //From lte-spectrum-value-helper.cc
    const double kT_dBm_Hz = -174.0;  // dBm/Hz
    double kT_W_Hz = std::pow (10.0, (kT_dBm_Hz - 30) / 10.0);
    double noiseFigureLinear = std::pow (10.0, enbPhy->GetNoiseFigure() / 10.0);
    double noisePowerSpectralDensity =  kT_W_Hz * noiseFigureLinear;

    spectrumAnalyzerHelper.SetPhyAttribute ("NoisePowerSpectralDensity", DoubleValue (noisePowerSpectralDensity));  // -174 dBm/Hz
    spectrumAnalyzerHelper.EnableAsciiAll ("spectrum-analyzer-output");

    NetDeviceContainer spectrumDevice;
    spectrumDevice = spectrumAnalyzerHelper.Install(spectrumAnalyzer);


    NodeContainer waveNodes;
    waveNodes.Add(spectrumAnalyzer);
    waveNodes.Add(waveformGeneratorNodes);

    //19 position the interference generator and the spectrum analyzer
    Ptr<ListPositionAllocator> pos = CreateObject<ListPositionAllocator>();
    pos->Add(Vector( 50000.0,  50000.0, 0.0));
    pos->Add(Vector(100000.0, 100000.0, 0.0));
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.SetPositionAllocator(pos);
    mobility.Install(waveNodes);

    //20 install the Flow monitor
    Ptr<FlowMonitor> flowMonitor;
    FlowMonitorHelper flowHelper;
    flowMonitor = flowHelper.InstallAll();

    //21 Export the netanim animation for the simulation
    /*
    BaseStationNetDevice b;
    SubscriberStationNetDevice s;
    CsmaNetDevice c;
    UanNetDevice u;

    AnimationInterface anim("anim.xml");
    anim.SetMaxPktsPerTraceFile(0xFFFFFFFF);
    anim.EnablePacketMetadata(true);
     */

    //22 Run simulation
    Simulator::Stop(Seconds(simTime));
    Simulator::Run();

    //23 Dump flowmonitor results
    flowMonitor->SerializeToXmlFile("flow.xml", true, true);

    Simulator::Destroy();

    return 0;
}