#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/applications-module.h"
#include "ns3/lte-module.h"
#include "ns3/config-store.h"
#include "ns3/buildings-helper.h"
#include "ns3/netanim-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
using namespace std;
using namespace ns3;

int main (int argc, char *argv[])
{

    SeedManager::SetRun(42);
    //whether to use carrier aggregation
    bool useCa = false;
    double simTime = 30;
    double interPacketInterval = 25;
    uint32_t nEnb = 1;
    uint32_t nUE = 2;

    CommandLine cmd;
    cmd.AddValue("useCa", "Whether to use carrier aggregation.", useCa);
    cmd.AddValue("nUe", "Number of UEs", nUE);
    cmd.AddValue("simTime", "Total duration of the simulation (in seconds)", simTime);

    // Parse again so you can override default values from the command line
    cmd.Parse (argc, argv);

    if (useCa)
    {
        Config::SetDefault ("ns3::LteHelper::UseCa", BooleanValue (useCa));
        Config::SetDefault ("ns3::LteHelper::NumberOfComponentCarriers", UintegerValue (2));
        Config::SetDefault ("ns3::LteHelper::EnbComponentCarrierManager", StringValue ("ns3::RrComponentCarrierManager"));
    }

    // Geometry of the scenario (meters)
    double roomLength = 50000;
    double nodeHeight = 1.5;
    double bsHeight = 5;

    // Container for all nodes
    NodeContainer allNodes;
    // LTE HELPER constructor
    Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();
    Ptr<PointToPointEpcHelper> epcHelper = CreateObject<PointToPointEpcHelper>();
    lteHelper->SetEpcHelper(epcHelper);
    /************* ANTENNA SETUP ************/
    lteHelper->SetAttribute("PathlossModel", StringValue("ns3::FriisPropagationLossModel"));
    lteHelper->SetPathlossModelAttribute("SystemLoss", DoubleValue(0.0));
    lteHelper->SetEnbAntennaModelType("ns3::CosineAntennaModel");
    lteHelper->SetEnbAntennaModelAttribute("Orientation", DoubleValue(0));
    lteHelper->SetEnbAntennaModelAttribute("Beamwidth", DoubleValue(35));
    lteHelper->SetEnbAntennaModelAttribute("MaxGain", DoubleValue(400));
    // Default scheduler is PF, uncomment to use RR
    //lteHelper->SetSchedulerType ("ns3::RrFfMacScheduler");

    // PGW constructor
    Ptr<Node> pgw = epcHelper->GetPgwNode();
    
    allNodes.Add(pgw);
    // Uncomment to enable logging
//  lteHelper->EnableLogComponents ();

    // Remote Host
    NodeContainer remoteHostContainer;
    remoteHostContainer.Create(1);
    allNodes.Add(remoteHostContainer);

    // Create Nodes: eNodeB and UE
    NodeContainer enbNodes;
    NodeContainer ueNodes;
    // As there is only one floor just create everything within node container
    enbNodes.Create (nEnb);
    ueNodes.Create (nUE);
    allNodes.Add(enbNodes);
    allNodes.Add(ueNodes);

    /***************MOBILITY SETUP**************/
    Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator>();
    positionAlloc->Add(Vector(10, 0, 0)); // 0 - PGW
    positionAlloc->Add(Vector(0, 0, 0)); // 1 - Internet
    positionAlloc->Add(Vector(12500, 12500, bsHeight)); // 2 - eNB
    for (uint32_t j=0;j<nUE;j++){
        Ptr<UniformRandomVariable> posX = CreateObject<UniformRandomVariable> ();
        Ptr<UniformRandomVariable> posY = CreateObject<UniformRandomVariable> ();
        positionAlloc->Add(Vector(posX->GetValue()*roomLength, posY->GetValue()*roomLength, nodeHeight));
    }
    MobilityHelper mobility;
    mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
    mobility.SetPositionAllocator(positionAlloc);
    mobility.Install (allNodes);

    /*****************IP STACK SETUP**************/
    Ptr<Node> remoteHost = remoteHostContainer.Get(0);
    InternetStackHelper internet;
    internet.Install(remoteHostContainer);

    // Connect internet to PGW
    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", DataRateValue(DataRate ("100Gb/s")));
    p2p.SetDeviceAttribute("Mtu", UintegerValue(1500));
    p2p.SetChannelAttribute("Delay", TimeValue(Seconds(0.010)));
    NetDeviceContainer internetDevices = p2p.Install(pgw, remoteHost);

    // Put IP in nodes
    Ipv4AddressHelper ipv4h;
    ipv4h.SetBase("1.0.0.0","255.0.0.0");
    Ipv4InterfaceContainer internetIPfaces = ipv4h.Assign(internetDevices);

    Ipv4StaticRoutingHelper ipv4RoutingHelper;
    Ptr<Ipv4StaticRouting> remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting(remoteHost->GetObject<Ipv4>());
    remoteHostStaticRouting->AddNetworkRouteTo(Ipv4Address("7.0.0.0"), Ipv4Mask("255.0.0.0"),1);

    /*******************CREATE LTE DEVICES**************/
    // Create Devices and install them in the Nodes (eNB and UE)
    NetDeviceContainer enbDevs = lteHelper->InstallEnbDevice(enbNodes);
    NetDeviceContainer ueDevs = lteHelper->InstallUeDevice (ueNodes);
    internet.Install(ueNodes);
    Ipv4InterfaceContainer ueIPface = epcHelper->AssignUeIpv4Address(NetDeviceContainer(ueDevs));

    for(uint32_t j = 0;j<ueNodes.GetN();++j){
        Ptr<Node> ueNode = ueNodes.Get(j);
        Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting(ueNode->GetObject<Ipv4>());
        ueStaticRouting->SetDefaultRoute(epcHelper->GetUeDefaultGatewayAddress(), 1);
    }
    // Attach a UE devices to a eNB
    lteHelper->Attach (ueDevs, enbDevs.Get (0));

    // Activate a data radio bearer
    // enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE;
    // EpsBearer bearer (q);
    // lteHelper->ActivateDataRadioBearer (ueDevs, bearer);


    /************APPLICATION SETUP********************/
    uint16_t serverPort = 9;




    // HTTP Stuff
    Ipv4Address serverAddress = remoteHost->GetObject<Ipv4>()->GetAddress(1,0).GetLocal();
    // Create HTTP Server
    ThreeGppHttpServerHelper serverHelper(serverAddress);
    ApplicationContainer serverApps = serverHelper.Install(remoteHost);
    // SETUP CALLBACKS FOR TRACING
    Ptr<ThreeGppHttpServer> httpServer = serverApps.Get(0)->GetObject<ThreeGppHttpServer>();
    // httpServer->TraceConnectWithoutContext("ConnectionEstablished", MakeCallback(&ServerConnectionEstablished));
    // httpServer->TraceConnectWithoutContext("MainObject",MakeCallback(&EmbeddedObjectGenerated));
    // httpServer->TraceConnectWithoutContext("Tx", MakeCallback(&ServerTx));
    // SETUP HTTP VARIABLES
    PointerValue varPtr;
    httpServer->GetAttribute("Variables", varPtr);
    Ptr<ThreeGppHttpVariables> httpVariables = varPtr.Get<ThreeGppHttpVariables>();
    httpVariables->SetMainObjectSizeMean(102400); //100kB
    httpVariables->SetMainObjectSizeStdDev(40960); //40kB
    // START SERVER
    serverApps.Start(Seconds(0.5));
    // Create HTTP Client
    ThreeGppHttpClientHelper clientHelper(serverAddress);
    ApplicationContainer clientApps;
    clientApps.Add(clientHelper.Install(ueNodes));
    // SETUP CALLBACKS FOR CLIENT TRACING
    Ptr<ThreeGppHttpClient> htttpClient = clientApps.Get(0)->GetObject<ThreeGppHttpClient>();
    // htttpClient->TraceConnectWithoutContext("RxMainObject", MakeCallback(&ClientMainObjectReceived));
    // htttpClient->TraceConnectWithoutContext("RxEmbeddedObject", MakeCallback(&ClientEmbeddedObjectReceived));
    // htttpClient->TraceConnectWithoutContext("Rx", MakeCallback(&ClientRx));
    clientApps.Start(Seconds(0.7));
    clientApps.Stop(Seconds(simTime));
    /*********ENABLE TRACES****************/

    // RUN SIM
    lteHelper->EnableTraces ();

    AnimationInterface anim("animation.xml");
    anim.SetMobilityPollInterval(Seconds(.25));
    anim.SetMaxPktsPerTraceFile(0xFFFFFFFF);
    anim.EnablePacketMetadata(true);

    // Start simulation and frees up when done
    Simulator::Stop (Seconds (simTime+1));
    Simulator::Run ();
    Simulator::Destroy ();
    return 0;
}
