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

    NodeContainer allNodes;
    //Config::SetDefault ("ns3::LteEnbNetDevice::DlBandwidth", UintegerValue (100));
    //Config::SetDefault ("ns3::LteEnbNetDevice::UlBandwidth", UintegerValue (100));

    Config::SetDefault ("ns3::LteSpectrumPhy::DataErrorModelEnabled", BooleanValue (true));
    Config::SetDefault ("ns3::LteSpectrumPhy::CtrlErrorModelEnabled", BooleanValue (false));

    Config::SetDefault ("ns3::LteEnbMac::FusionAlgorithm", UintegerValue(LteEnbMac::MRG_AND));

    //60dBm = 1kW
    //38dBm = 6.3W
    //30dBm = 1W
    //20dBm = 100mW
    //10dBm =  10mW
    // 0dBm =   1mW
    Config::SetDefault("ns3::LteEnbPhy::TxPower", DoubleValue(60.0));
    Config::SetDefault("ns3::LteUePhy::TxPower" , DoubleValue(30.0));

    //1 Configura EPC e PGW
    Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();
    lteHelper->SetAttribute("Scheduler", StringValue("ns3::CqaFfMacScheduler")); //QoS aware scheduler
    //lteHelper->SetAttribute("Scheduler", StringValue("ns3::NnFfMacScheduler")); //NN scheduler
    //lteHelper->SetAttribute("UseCa", BooleanValue(true)); // Carrier aggregation
    //lteHelper->SetAttribute("NumberOfComponentCarriers", UintegerValue(4)); // Carrier aggregation

    lteHelper->SetAttribute ("PathlossModel", StringValue ("ns3::FriisPropagationLossModel"));         // Default
    //lteHelper->SetAttribute ("PathlossModel", StringValue ("ns3::FriisSpectrumPropagationLossModel")); // Spectrum
    //lteHelper->SetAttribute ("PathlossModel", StringValue ("ns3::RANGE5GPropagationLossModel"));


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
    NodeContainer ueNodes;
    NodeContainer enbNodes;
    enbNodes.Create(1); // Macro cell
    ueNodes.Create(6); // Femtocell
    allNodes.Add(enbNodes);
    //allNodes.Add(ueNodes);

// City positions
// Unaí         50000, 50000, 0
// Natalândia   66000, 94000, 0

    //4 Aloca posições dos dispositivos
    Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
    positionAlloc->Add (Vector (   10.0,     0.0,  0.0));  // 0 - PGw
    positionAlloc->Add (Vector (    0.0,     0.0,  0.0));  // 1 - Internet
    positionAlloc->Add (Vector ( 5000.0,  5000.0,  0.0));  // 2 - eNB

    Ptr<ListPositionAllocator> positionAlloc2 = CreateObject<ListPositionAllocator> ();

    // All nodes in a straight line (unrealistic, but just to get different CQI levels on each UE)
    //  UE0 - 300m - UE1 - 300m - UE2 - 300m - UE3 - 300m - UE4 - 300m - UE5 - 300m - UE6 - eNB - 300m - UE7 - 300m - UE8 - 300m - UE9 - 600m - PU
    // 1.8km       1.5km         1.2km        0.9km        0.6km        0.3km            0km            0.3km        0.6km       0.9km         1.5km
    //

    /*
    positionAlloc2->Add(Vector (3200.0, 5000.0,  0.0));  // 3 - UE 0
    positionAlloc2->Add(Vector (3500.0, 5000.0,  0.0));  // 4 - UE 1
    positionAlloc2->Add(Vector (3800.0, 5000.0,  0.0));  // 5 - UE 2
    positionAlloc2->Add(Vector (4100.0, 5000.0,  0.0));  // 6 - UE 3
    positionAlloc2->Add(Vector (4400.0, 5000.0,  0.0));  // 7 - UE 4
    positionAlloc2->Add(Vector (4700.0, 5000.0,  0.0));  // 8 - UE 5
    positionAlloc2->Add(Vector (5000.0, 5000.0,  0.0));  // 9 - UE 6
    positionAlloc2->Add(Vector (5300.0, 5000.0,  0.0));  //10 - UE 7
    positionAlloc2->Add(Vector (5600.0, 5000.0,  0.0));  //11 - UE 8
    positionAlloc2->Add(Vector (5900.0, 5000.0,  0.0));  //12 - UE 9
    */

    /*
     * Circular topology
     *                               ``````````````````````
                                ``````                      `````
                             ```                                 ````
                          ```           `````````````````            ```
                       ```         `````                 ``````         ``
                     ``        ````                            ```        ``
                   ``       ```           `````````````           ```       ``
                  `       ``         `````             `````         ``       ``
                ``     ``        ```                       ````       ``       `
               ``    __        ```           ````````           ``       ``      ``
              .     |ue|     ``        ``````        `````        ``      ``      ``
             .      |__|    ``      ```                   ```       ``      `      ``
            .      .      ``      ```                        ``      ``      `      .
           ``     ``     ``      ``       `````` ``````        ``      .      .      .
           .     ``     ``     ``     __ `     ...       ```       __     .     .     ``
          ``     .      .     ``     |ue|    ` ___ ``       ``    |ue|    ``    ___     .
         __     ``     .      .      |__|  ``  \ /   ``      ``   |__|     .    \ /     .
        |ue|    .      .     `      .     ``    |      ``     ``     .      `    |      .
        |__|    .     ``     .     ``   _`_     |      _`_     .     `      .    |      .
         `.     .     .      .     .    |ue|    |     |ue|    .     ``     .     |      .
          .     .     ``     .     `    |__|   eNB    |__|  ``.     ``     .    PU      .
          .     .      .     .      .      `` 0.3km  ..`   __      .      .     .      .
          .     ``     .      .     ``      ``-.....`     |ue|    ``     .      .     ``
          .      .     ``     ``     ``                   |__|    .      .     ``     .
           .     ``     ``     ``      ``     0.6km     ``       `      .      .     ``
           ``     .      ` __    ``      ````       ````       ``      `      .      .
            .      .      |ue|    ``  __      ``````         ``       `      ``     ``
             .      .     |__|      `|ue|                  ``       ``      ``     ``
              `      ``   `````      |__|``   0.9km   `````       ``       `      ``
               .      ``       ``          ```````````     __   ```      ``      ``
                ``      ``       ```                      |ue|``       ```      ``
                 ``       ``        `````     1.2km     ``|__|       ```      ``
                   ``       ```          `````....``````           ``        ``
                     ``        ```                             ````        ``
                       ``         `````       1.5km        ````         ```
                         ```           ```````..---```````           ```
                            ````                                  ```
                                `````         1.8km          `````
                                     `````````--/--.`````````

    */

    positionAlloc2->Add(Vector (5000.0 - 1800.0, 5000.0 -     0.0,  0.0));  // 3 - UE 0
    positionAlloc2->Add(Vector (5000.0 - 1228.0, 5000.0 -   660.0,  0.0));  // 4 - UE 1
    positionAlloc2->Add(Vector (5000.0 -  944.0, 5000.0 -   966.0,  0.0));  // 5 - UE 2
    positionAlloc2->Add(Vector (5000.0 -  971.0, 5000.0 -  -505.0,  0.0));  // 6 - UE 3
    positionAlloc2->Add(Vector (5000.0 -  436.0, 5000.0 -  -587.0,  0.0));  // 7 - UE 4
    positionAlloc2->Add(Vector (5000.0 -  466.0, 5000.0 -   177.0,  0.0));  // 8 - UE 5
    positionAlloc2->Add(Vector (5000.0 -  300.0, 5000.0 -     0.0,  0.0));  // 9 - UE 6
    positionAlloc2->Add(Vector (5000.0 +  300.0, 5000.0 -     0.0,  0.0));  //10 - UE 7
    positionAlloc2->Add(Vector (5000.0 +  514.0, 5000.0 +   109.0,  0.0));  //11 - UE 8
    positionAlloc2->Add(Vector (5000.0 +  544.0, 5000.0 +   769.0,  0.0));  //12 - UE 9

    
    //5 Instala mobilidade dos dispositivos (parados)
    MobilityHelper mobility;
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.SetPositionAllocator(positionAlloc);
    mobility.Install(allNodes);

    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.SetPositionAllocator(positionAlloc2);
    mobility.Install(ueNodes);

    allNodes.Add(ueNodes);



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
    NetDeviceContainer ueLteDevs = lteHelper->InstallUeDevice (ueNodes);


    //12 Instala pilha IP nos UE e dá endereços controlados pelo EPC
    internet.Install (ueNodes);
    Ipv4InterfaceContainer ueIpIface;
    ueIpIface = epcHelper->AssignUeIpv4Address (NetDeviceContainer (ueLteDevs));

    //13 Modifica UEs para adicionar o gateway correspondendo ao EPC
    // (conexão entre UE/eNB é feita através de uma aplicação e tunelamento GPRS)
    for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
    {
        Ptr<Node> ueNode = ueNodes.Get (u);
        Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting (ueNode->GetObject<Ipv4> ());
        ueStaticRouting->SetDefaultRoute (epcHelper->GetUeDefaultGatewayAddress (), 1);
    }

    //14 Associa UE ao eNodeB
    lteHelper->Attach (ueLteDevs, enbLteDevs.Get(0));

    //enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE;
    //EpsBearer bearer (q);
    //lteHelper->ActivateDataRadioBearer (ueLteDevs, bearer);

    //Ptr<EpcTft> tft = Create<EpcTft> ();
    //if (epcDl)
    //  {
    //    EpcTft::PacketFilter dlpf;
    //    dlpf.localPortStart = dlPort;
    //    dlpf.localPortEnd = dlPort;
    //    tft->Add (dlpf);
    //  }
    //if (epcUl)
    //  {
    //    EpcTft::PacketFilter ulpf;
    //    ulpf.remotePortStart = 9;
    //    ulpf.remotePortEnd = 9;
    //    tft->Add (ulpf);
    //  }

    //if (epcDl || epcUl)
    //{
    // EpsBearer bearer (EpsBearer::GBR_GAMING);
    // lteHelper->ActivateDedicatedEpsBearer (ueLteDevs, bearer, tft);
    //}



    // 26 Configura e instala aplicações
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
    echoClient.SetAttribute("Interval", TimeValue(MilliSeconds(10)));
    echoClient.SetAttribute("PacketSize", UintegerValue(1000));

    ApplicationContainer clientApps;
    clientApps.Add(echoClient.Install(ueNodes));

    //DASH APP
    /*
    uint64_t segmentDuration = 1;
    std::string adaptationAlgo = "festive"; // festive | panda | tobasco
    std::string segmentSizeFilePath = "../../contrib/haraldott/dash/examples/segmentsizes.txt";

    TcpStreamServerHelper serverHelper(serverPort+1);
    serverApp = serverHelper.Install(remoteHost);
    serverApp.Start(Seconds(0.5));
    serverApps.Add(serverApp);


    // Install TCP/UDP Transmitter on the station
    TcpStreamClientHelper clientHelper(serverAddress, serverPort+1);
    clientHelper.SetAttribute("SegmentDuration", UintegerValue(segmentDuration));
    clientHelper.SetAttribute("SegmentSizeFilePath", StringValue(segmentSizeFilePath));
    clientHelper.SetAttribute("NumberOfClients", UintegerValue(10));
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


    //28 gerador de interferencia
    NodeContainer waveformGeneratorNodes;
    waveformGeneratorNodes.Create(1);
    Ptr<SpectrumValue> mwoPsd =  MicrowaveOvenSpectrumValueHelper::CreatePowerSpectralDensityMwo1 (); //Basic microwave oven interference

    for (auto valIt = mwoPsd->ValuesBegin(); valIt != mwoPsd->ValuesEnd(); valIt++)
    {
        *valIt /= 16;//Decrease power levels
        //*valIt *= 4;//Increase power levels
    }

    WaveformGeneratorHelper waveformGeneratorHelper;
    waveformGeneratorHelper.SetChannel (lteHelper->GetDownlinkSpectrumChannel());
    waveformGeneratorHelper.SetTxPowerSpectralDensity (mwoPsd);

    waveformGeneratorHelper.SetPhyAttribute ("Period", TimeValue (Seconds (1.0)));   // corresponds to 60 Hz
    waveformGeneratorHelper.SetPhyAttribute ("DutyCycle", DoubleValue (0.5));
    NetDeviceContainer waveformGeneratorDevices = waveformGeneratorHelper.Install (waveformGeneratorNodes);
    Simulator::Schedule (Seconds (2.5), &WaveformGenerator::Start, waveformGeneratorDevices.Get (0)->GetObject<NonCommunicatingNetDevice>()->GetPhy ()->GetObject<WaveformGenerator> ());



    //29 captura espectro
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
    spectrumAnalyzerHelper.SetRxSpectrumModel(SpectrumModelRANGE);
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

    Ptr<ListPositionAllocator> pos = CreateObject<ListPositionAllocator>();
    pos->Add(Vector(5000 + 1500.0, 5000.0, 0.0));
    pos->Add(Vector(5000 + 1500.0, 5000.0, 0.0));
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.SetPositionAllocator(pos);
    mobility.Install(waveNodes);

    //31 Flow monitor
    Ptr<FlowMonitor> flowMonitor;
    FlowMonitorHelper flowHelper;
    flowMonitor = flowHelper.InstallAll();

    //32 Exportar simulação para netanim
    BaseStationNetDevice b;
    SubscriberStationNetDevice s;
    CsmaNetDevice c;
    UanNetDevice u;

    AnimationInterface anim("anim.xml");
    anim.SetMaxPktsPerTraceFile(0xFFFFFFFF);
    anim.EnablePacketMetadata(true);

    //33 Rodar o simulador
    Simulator::Stop(Seconds(simTime));
    Simulator::Run();

    flowMonitor->SerializeToXmlFile("flow.xml", true, true);

    Simulator::Destroy();

    return 0;
}