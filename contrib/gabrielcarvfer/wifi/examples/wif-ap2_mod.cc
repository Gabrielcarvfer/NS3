// Node #0 is the AP, #1 is a base station
// #1 sends UDP echo mesg to the AP; AP sends a UDP response back to the node
// Communication is possible only when the station is within a certain distance from the AP

#include <ns3/contrib-gabrielcarvfer-module.h>

#include <ns3/netanim-module.h>
#include <ns3/bs-net-device.h>
#include <ns3/csma-module.h>
#include <ns3/uan-module.h>


#include <ns3/wifi-module.h>
#include <ns3/basic-energy-source.h>
#include <ns3/simple-device-energy-model.h>
#include <ns3/core-module.h>
#include <ns3/mobility-module.h>
#include <ns3/ipv4-global-routing-helper.h>
#include <ns3/internet-module.h>
#include <ns3/application-container.h>
#include <ns3/udp-echo-helper.h>
#include <ns3/li-ion-energy-source-helper.h>
#include <random>
//#include "shared/netanim_shared.h"
//#include "shared/inet_shared.h"

#if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__)
    #define WIN32
    #include <windows.h>
#else
    #include <sys/stat.h>
#endif

using namespace ns3;

//NS_LOG_COMPONENT_DEFINE ("wif-ap2");

#define LOG(x) std::cout<<x<<std::endl

static void
PrintCellInfo (EnergySourceContainer esCon, ApplicationContainer *clientApps)
{
    for (unsigned i = 0; i < esCon.GetN(); i++)
    {

        //std::cout << "Node(" << i << ") At " << Simulator::Now().GetSeconds();
        //std::cout << " seconds, Cell voltage: " << esCon.Get(i)->GetSupplyVoltage();
        //std::cout << " V Remaining Capacity: " << esCon.Get(i)->GetRemainingEnergy() / (3.6 * 3600) << " Ah";
        //std::cout << " Remaining charge "<<esCon.Get(i)->GetEnergyFraction()*100 << "%";
        //std::cout << std::endl;

        if (esCon.Get(i)->GetEnergyFraction() <= 0.05)
        {
            clientApps->Get(i)->SetStopTime(Simulator::Now());
        }

    }

    if (!Simulator::IsFinished ())
        Simulator::Schedule (Seconds (10), &PrintCellInfo, esCon, clientApps);

 }

double watthToJoule(double watth)
{
    return watth*3600;
}

int main(int argc, char *argv[])
{
    int nDevices = 10;
    int nAPs = 1;
    bool g_verbose = true;
    bool trace = false;
    int simulationDuration = 100;
    double beaconInterval = 1.0, packetInterval = 1000, maxBeaconInterval = 5.0, minBeaconInterval = 0.5;
    //double beaconInterval = 1, packetInterval = 1000.0, maxBeaconInterval = 1, minBeaconInterval = 1; //1s
    //double beaconInterval = 0.1, packetInterval = 1000.0, maxBeaconInterval = 0.1, minBeaconInterval = 0.1; //100ms


    unsigned packetSize = 1024;
    std::string outputFolder = "output/";

#ifdef WIN32
    CreateDirectory(outputFolder, NULL);
#else
    mkdir(outputFolder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

    CommandLine cmd;
    cmd.AddValue ("nDevices", "Number of wifi STA devices", nDevices);
    cmd.AddValue ("nAPs", "Number of wifi STA devices", nAPs);
    cmd.AddValue ("beaconInterval", "Beacon interval in seconds", beaconInterval);
    cmd.AddValue ("maxBeaconInterval", "Max beacon interval in seconds", maxBeaconInterval);
    cmd.AddValue ("minBeaconInterval", "Min beacon interval in seconds", minBeaconInterval);
    cmd.AddValue ("packetInterval", "Packet interval between transmissions", packetInterval);
    cmd.AddValue ("packetSize", "Size of packages to be sent", packetSize);
    cmd.AddValue ("g_verbose", "Tell echo applications to log if true", g_verbose);
    cmd.AddValue ("trace", "Enable pcap tracing", trace);
    cmd.Parse(argc, argv);

    if (g_verbose)
    {
        //LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_ALL);
        //LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_ALL);
        //LogComponentEnable("LiIonEnergySource", LOG_LEVEL_DEBUG);
        //LogComponentEnableAll(LOG_LEVEL_DEBUG);
        //LogComponentEnable("YansWifiPhy", LOG_LEVEL_ALL);
    }

// 1. Create the nodes and hold them in a container
    NodeContainer wifiStaNodes, wifiApNodes;
    wifiStaNodes.Create(nDevices);
    wifiApNodes.Create(nAPs);
    
// 2. Create channel for communication
    YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
    YansWifiPhyHelper phy = YansWifiPhyHelper::Default();
    channel.AddPropagationLoss("ns3::RangePropagationLossModel","MaxRange",DoubleValue(120));
    phy.SetPcapDataLinkType(YansWifiPhyHelper::DLT_IEEE802_11_RADIO); //Radiotap
    phy.SetChannel(channel.Create());

    
    WifiHelper wifi;
    wifi.SetRemoteStationManager("ns3::AarfWifiManager");
    NqosWifiMacHelper mac = NqosWifiMacHelper::Default();

// 3. Set up MAC
// 3a. Set up MAC for base stations
    //It's a really good idea to check if component from a 3rd-party lib is registered before using
//NS_OBJECT_ENSURE_REGISTERED(MacLow);
//NS_OBJECT_ENSURE_REGISTERED(RegularWifiMac);
//NS_OBJECT_ENSURE_REGISTERED(StaWifiMac);

    Ssid ssid = Ssid("ns-3-ssid");
    mac.SetType("ns3::StaWifiMac",
                "Ssid", SsidValue(ssid),
                "ActiveProbing", BooleanValue(false));
    NetDeviceContainer staDevices;

    staDevices = wifi.Install(phy, mac, wifiStaNodes);


    NS_OBJECT_ENSURE_REGISTERED (ApWifiMac);

// 3b. Set up MAC for AP
    mac.SetType("ns3::ApWifiMac",
                "Ssid", SsidValue(ssid),
                "BeaconGeneration", BooleanValue(true),
                "BeaconInterval", TimeValue(Seconds(beaconInterval)),
                "MaxBeaconInterval", TimeValue(Seconds(maxBeaconInterval)),
                "MinBeaconInterval", TimeValue(Seconds(minBeaconInterval))
                );

    NetDeviceContainer apDevices;
    apDevices = wifi.Install(phy, mac, wifiApNodes);

// 4. Set mobility of the nodes
    MobilityHelper mobility;

    // Configure mobility of APs
        mobility.SetPositionAllocator ("ns3::RandomDiscPositionAllocator",
                                       "X", StringValue ("200.0"),
                                       "Y", StringValue ("200.0"),
                                       "Rho", StringValue ("ns3::UniformRandomVariable[Min=0|Max=30]"));
        mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
        mobility.Install(wifiApNodes);

    // Configure mobility of devices
        mobility.SetPositionAllocator ("ns3::RandomDiscPositionAllocator",
                                       "X", StringValue ("200.0"),
                                       "Y", StringValue ("200.0"),
                                       "Rho", StringValue ("ns3::UniformRandomVariable[Min=0|Max=60]"));

        mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                                   "Mode", StringValue ("Time"),
                                   "Time", StringValue ("1s"),
                                   "Speed", StringValue ("ns3::UniformRandomVariable[Min=5.0|Max=15.0]"),//ConstantRandomVariable[Constant=1.0]"),
                                   "Bounds", StringValue ("0|400|0|400"));

        mobility.Install(wifiStaNodes);

// 5. Configure energy model
    LiIonEnergySourceHelper liIonEnergySourceHelper;
    liIonEnergySourceHelper.Set("LiIonEnergySourceInitialEnergyJ", DoubleValue(watthToJoule(0.005)));

    EnergySourceContainer energySourceContainer = liIonEnergySourceHelper.Install(wifiStaNodes);

    WifiRadioEnergyModelHelper radioEnergyModelHelper;

    DeviceEnergyModelContainer deviceEnergyModelContainer = radioEnergyModelHelper.Install(staDevices,energySourceContainer);


// 6.Add Internet layers stack
    InternetStackHelper stack;
    stack.Install(wifiStaNodes);
    stack.Install(wifiApNodes);

// 7. Assign IP address to each device
    Ipv4AddressHelper address;
    Ipv4InterfaceContainer wifiStaInterfaces, wifiApInterfaces;
    address.SetBase("10.1.1.0", "255.255.255.0");
    wifiApInterfaces = address.Assign(apDevices);
    wifiStaInterfaces = address.Assign(staDevices);

// 8a. Create and setup applications (traffic sink)
    UdpEchoServerHelper echoServer(8080); // Port
    ApplicationContainer serverApps = echoServer.Install(wifiApNodes.Get(0));
    serverApps.Start(Seconds(3.0));
    serverApps.Stop(Seconds(simulationDuration));

// 8b. Create and setup applications (traffic source)
    UdpEchoClientHelper echoClient(wifiApNodes.Get(0)->GetObject<Ipv4>()->GetAddress(1,0).GetLocal(), 8080);
    //echoClient.SetAttribute("MaxPackets", UintegerValue(1000));
    //echoClient.SetAttribute("Interval", TimeValue(MilliSeconds(packetInterval)));
    //echoClient.SetAttribute("PacketSize", UintegerValue(packetSize));

    //std::uniform_real_distribution<double> unif(0.0,1.0);
    //std::default_random_engine re;

    ApplicationContainer clientApps = echoClient.Install(wifiStaNodes);
    //for (unsigned i = 0; i < wifiStaNodes.GetN();i++)
    //{
    //    clientApps.Add(echoClient.Install(wifiStaNodes.Get(i)));
    //    clientApps.Get(i)->SetAttribute("Interval",TimeValue(Seconds(packetInterval+unif(re))));
    //}

    clientApps.Start(Seconds(2.0));
    clientApps.Stop(Seconds(simulationDuration));

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

// 9. Enable tracing (optional)
    std::stringstream pcap_filename;
    //pcap_filename << "wifi-2-nodes-fixed ";
    //pcap_filename << "beaconInterval-"<<(int)(beaconInterval*1000.0)<<"ms ";
    //pcap_filename << "packetInterval-"<<(int)(packetInterval*1000.0)<<"ms ";
    //pcap_filename << "packetSize-"<< packetSize<<"KB";
    pcap_filename << "wifi-ap2";
    phy.EnablePcap (outputFolder+pcap_filename.str(), wifiApNodes, true);

    //wifi.EnableLogComponents();
    //stack.EnablePcapIpv4("wif-ap2-ap", wifiApNodes);
    //stack.EnablePcapIpv4("wif-ap2-sta", wifiStaNodes);


    //Print ipv4 address of interfaces and XYZ position of nodes
    //ADD simulator print timeOfSimulation
    std::string a1,b1,c1;
    a1 = "IP addresses of base stations";
    b1 = "IP address of AP";
    c1 = "location of all nodes";

    //Simulator::Schedule(Seconds(1.01), &PrintAddresses, &wifiInterfaces, &a);
    //Simulator::Schedule(Seconds(1.02), &PrintAddresses, &wifiApInterface, &b);
    //Simulator::Schedule(Seconds(3.03), &PrintLocations, &wifiStaNodes, &c);

    //Print batteries info and disable nodes with low battery
    //PrintCellInfo(energySourceContainer, &clientApps);

//10. Configure animation
    BaseStationNetDevice b;
    SubscriberStationNetDevice s;
    CsmaNetDevice c;
    UanNetDevice u;

    AnimationInterface anim(outputFolder+"anim2.xml");
    anim.SetMaxPktsPerTraceFile(0xFFFFFFFF);
    anim.SetMobilityPollInterval(Seconds(1.0));
    anim.EnablePacketMetadata(true);
    anim.EnableIpv4RouteTracking (outputFolder+"routingtable-wireless.xml", Seconds (0), Seconds (simulationDuration), Seconds (0.25));
    anim.EnableWifiMacCounters (Seconds (0), Seconds (simulationDuration));
    anim.EnableWifiPhyCounters (Seconds (0), Seconds (simulationDuration));


    for (uint32_t i = 0; i < wifiApNodes.GetN (); ++i)
    {
        anim.UpdateNodeDescription (wifiApNodes.Get (i), "AP"); // Optional
        anim.UpdateNodeColor (wifiApNodes.Get (i), 0, 255, 0); // Optional
    }


//11. Run and destroy simulation
    Simulator::Stop(Seconds(simulationDuration));
    Simulator::Run();
    Simulator::Destroy();
    return 0;
}