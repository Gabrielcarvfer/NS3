//
// Created by Gabriel Ferreira (@gabrielcarvfer) on 21/03/2018.
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

using namespace ns3;



//Simple network setup
int main()
{
    uint16_t numberOfNodes = 2;
    double simTime = 1.1;
    double distance = 60.0;
    double interPacketInterval = 25;

    NodeContainer allNodes;

    //1 Configura EPC e PGW
    Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();
    Ptr<PointToPointEpcHelper>  epcHelper = CreateObject<PointToPointEpcHelper> ();
    lteHelper->SetEpcHelper (epcHelper);
    Ptr<Node> pgw = epcHelper->GetPgwNode ();

    NodeContainer remoteHostContainer;
    remoteHostContainer.Create (1);
    allNodes.Add(remoteHostContainer);
    allNodes.Add(pgw);

    NodeContainer ueNodes;
    NodeContainer enbNodes;
    enbNodes.Create(numberOfNodes);
    ueNodes.Create(numberOfNodes);
    allNodes.Add(enbNodes);
    allNodes.Add(ueNodes);

    NodeContainer spectrumAnalyzer;
    spectrumAnalyzer.Create(1);
    allNodes.Add(spectrumAnalyzer);

    NodeContainer waveformGeneratorNodes;
    waveformGeneratorNodes.Create(1);
    allNodes.Add(waveformGeneratorNodes);




    Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
    positionAlloc->Add (Vector (  0.0,   0.0,  0.0));  // 0 - Remote Host
    positionAlloc->Add (Vector ( 20.0,  20.0, 20.0));  // 1 - PGW
    positionAlloc->Add (Vector (150.0,   0.0,  0.0));  // 2 - eNB 1
    positionAlloc->Add (Vector (  0.0, 150.0,  0.0));  // 3 - eNB 2
    positionAlloc->Add (Vector ( 75.0,  35.0,  0.0));  // 4 - UE 1
    positionAlloc->Add (Vector (110.0,  89.0,  0.0));  // 5 - UE 2
    positionAlloc->Add (Vector ( 75.0,  75.0,  0.0));  // 6 - Spectrum Analyzer
    positionAlloc->Add (Vector ( 74.0,  36.0,  0.0));  // 7 - Microwave Oven
    //positionAlloc->Add (Vector ( 74.0,  37.0,  0.0));  // 8 - Microwave Oven
    //positionAlloc->Add (Vector (109.0,  90.0,  0.0));  // 9 - Microwave Oven

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

    //4 Configura roteamento estático entre IP interno e externo do PGW (7.0.0.0 e 1.0.0.0)
    Ipv4StaticRoutingHelper ipv4RoutingHelper;
    Ptr<Ipv4StaticRouting> remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting (remoteHost->GetObject<Ipv4> ());
    remoteHostStaticRouting->AddNetworkRouteTo (Ipv4Address ("7.0.0.0"), Ipv4Mask ("255.0.0.0"), 1);





    //6 Instala dispositivos LTE aos nós
    NetDeviceContainer enbLteDevs = lteHelper->InstallEnbDevice (enbNodes);
    NetDeviceContainer ueLteDevs = lteHelper->InstallUeDevice (ueNodes);

    //7 Instala pilha IP nos UEs
    internet.Install (ueNodes);
    Ipv4InterfaceContainer ueIpIface;
    ueIpIface = epcHelper->AssignUeIpv4Address (NetDeviceContainer (ueLteDevs));

    //8 Configura endereço IP dos UEs e instala aplicações
    for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
    {
        Ptr<Node> ueNode = ueNodes.Get (u);
        // Set the default gateway for the UE
        Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting (ueNode->GetObject<Ipv4> ());
        ueStaticRouting->SetDefaultRoute (epcHelper->GetUeDefaultGatewayAddress (), 1);
    }

    //9 Associa um UE por eNodeB
    for (uint16_t i = 0; i < numberOfNodes; i++)
    {
        lteHelper->Attach (ueLteDevs.Get(i), enbLteDevs.Get(i));
        // side effect: the default EPS bearer will be activated
    }


    //10 Configura, instala e inicia aplicações em UEs e servidor remoto
    uint16_t dlPort = 1234;
    uint16_t ulPort = 2000;
    uint16_t otherPort = 3000;
    ApplicationContainer clientApps;
    ApplicationContainer serverApps;
    for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
    {
        ++ulPort;
        ++otherPort;
        PacketSinkHelper dlPacketSinkHelper ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), dlPort));
        PacketSinkHelper ulPacketSinkHelper ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), ulPort));
        PacketSinkHelper packetSinkHelper ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), otherPort));
        serverApps.Add (dlPacketSinkHelper.Install (ueNodes.Get(u)));
        serverApps.Add (ulPacketSinkHelper.Install (remoteHost));
        serverApps.Add (packetSinkHelper.Install (ueNodes.Get(u)));

        UdpClientHelper dlClient (ueIpIface.GetAddress (u), dlPort);
        dlClient.SetAttribute ("Interval", TimeValue (MilliSeconds(interPacketInterval)));
        dlClient.SetAttribute ("MaxPackets", UintegerValue(1000000));
        dlClient.SetAttribute ("PacketSize", UintegerValue(1500));

        UdpClientHelper ulClient (remoteHostAddr, ulPort);
        ulClient.SetAttribute ("Interval", TimeValue (MilliSeconds(interPacketInterval)));
        ulClient.SetAttribute ("MaxPackets", UintegerValue(1000000));
        ulClient.SetAttribute ("PacketSize", UintegerValue(1500));

        UdpClientHelper client (ueIpIface.GetAddress (u), otherPort);
        client.SetAttribute ("Interval", TimeValue (MilliSeconds(interPacketInterval)));
        client.SetAttribute ("MaxPackets", UintegerValue(1000000));
        client.SetAttribute ("PacketSize", UintegerValue(1500));

        clientApps.Add (dlClient.Install (remoteHost));
        clientApps.Add (ulClient.Install (ueNodes.Get(u)));
        if (u+1 < ueNodes.GetN ())
        {
            clientApps.Add (client.Install (ueNodes.Get(u+1)));
        }
        else
        {
            clientApps.Add (client.Install (ueNodes.Get((uint32_t)0)));
        }
    }

    UdpEchoServerHelper udpEchoServerHelper(ulPort+1);
    serverApps.Add(udpEchoServerHelper.Install(remoteHost));
    UdpEchoClientHelper udpEchoClientHelper(remoteHostAddr, ulPort+1);
    clientApps.Add(udpEchoClientHelper.Install(ueNodes.Get((uint32_t)0)));


    serverApps.Start (Seconds (0.01));
    clientApps.Start (Seconds (0.01));
    lteHelper->EnableTraces ();


/**************************************************/



    SpectrumAnalyzerHelper spectrumAnalyzerHelper;
    spectrumAnalyzerHelper.SetChannel (lteHelper->GetDownlinkSpectrumChannel());
    Ptr<LteEnbNetDevice> enbNetDev = enbLteDevs.Get(0)->GetObject<LteEnbNetDevice>();
    Ptr<LteEnbPhy> enbPhy = enbNetDev->GetPhy();
    Ptr<LteSpectrumPhy> enbSpectrPhy = enbPhy->GetUlSpectrumPhy();
    Ptr<const SpectrumModel> rxSpectrumModel = enbSpectrPhy->GetRxSpectrumModel();
    Ptr<SpectrumModel> model = Copy(rxSpectrumModel);
    //spectrumAnalyzerHelper.SetRxSpectrumModel ( model);
    //spectrumAnalyzerHelper.SetRxSpectrumModel(SpectrumModelLte);
    spectrumAnalyzerHelper.SetRxSpectrumModel(SpectrumModel300MHz3GhzLog);
    //spectrumAnalyzerHelper.SetRxSpectrumModel(SpectrumModel300Khz300GhzLog);
    spectrumAnalyzerHelper.SetPhyAttribute ("Resolution", TimeValue (MilliSeconds (2)));

    //From lte-spectrum-value-helper.cc
    const double kT_dBm_Hz = -174.0;  // dBm/Hz
    double kT_W_Hz = std::pow (10.0, (kT_dBm_Hz - 30) / 10.0);
    double noiseFigureLinear = std::pow (10.0, enbPhy->GetNoiseFigure() / 10.0);
    double noisePowerSpectralDensity =  kT_W_Hz * noiseFigureLinear;

    spectrumAnalyzerHelper.SetPhyAttribute ("NoisePowerSpectralDensity", DoubleValue (noisePowerSpectralDensity));  // -174 dBm/Hz
    spectrumAnalyzerHelper.EnableAsciiAll ("spectrum-analyzer-output");

    NetDeviceContainer spectrumDevice;
    spectrumDevice = spectrumAnalyzerHelper.Install(spectrumAnalyzer);


/**************************************************/
    Ptr<SpectrumValue> mwoPsd =  MicrowaveOvenSpectrumValueHelper::CreatePowerSpectralDensityMwo1 ();

    WaveformGeneratorHelper waveformGeneratorHelper;
    waveformGeneratorHelper.SetChannel (lteHelper->GetDownlinkSpectrumChannel());
    waveformGeneratorHelper.SetTxPowerSpectralDensity (mwoPsd);

    waveformGeneratorHelper.SetPhyAttribute ("Period", TimeValue (Seconds (1.0 / 60)));   // corresponds to 60 Hz
    waveformGeneratorHelper.SetPhyAttribute ("DutyCycle", DoubleValue (0.5));
    NetDeviceContainer waveformGeneratorDevices = waveformGeneratorHelper.Install (waveformGeneratorNodes);

    Simulator::Schedule (Seconds (0.1), &WaveformGenerator::Start,
                         waveformGeneratorDevices.Get (0)->GetObject<NonCommunicatingNetDevice> ()->GetPhy ()->GetObject<WaveformGenerator> ());
    //Simulator::Schedule (Seconds (0.1), &WaveformGenerator::Start,
    //                     waveformGeneratorDevices.Get (1)->GetObject<NonCommunicatingNetDevice> ()->GetPhy ()->GetObject<WaveformGenerator> ());
    //Simulator::Schedule (Seconds (0.1), &WaveformGenerator::Start,
    //                     waveformGeneratorDevices.Get (2)->GetObject<NonCommunicatingNetDevice> ()->GetPhy ()->GetObject<WaveformGenerator> ());

/***************************************************/

    //Exportar animação para o Netanim
    BaseStationNetDevice b;
    SubscriberStationNetDevice s;
    CsmaNetDevice c;
    UanNetDevice u;

    AnimationInterface anim("anim.xml");
    anim.SetMaxPktsPerTraceFile(0xFFFFFFFF);
    anim.EnablePacketMetadata(true);
    //anim.EnableIpv4RouteTracking (outputFolder+"routingtable-wireless.xml", Seconds (0), Seconds (9), Seconds (0.25));

    //Enable packet metadata print (conflicts with LTE EPC traffic flow template classifier... (derp)
    //Packet::EnablePrinting ();
    //Packet::EnableChecking ();

    //Rodar o simulador
    Simulator::Stop(Seconds(10)); // Rodar simulação por 10 segundos
    Simulator::Run();
    Simulator::Destroy();

    return 0;
}