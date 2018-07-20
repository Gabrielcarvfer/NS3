// Node #0 is the AP, #1 is a base station
// #1 sends UDP echo mesg to the AP; AP sends a UDP response back to the node
// Communication is possible only when the station is within a certain distance from the AP

#include <random>
#include "shared.h"

using namespace ns3;

NETANIM_VARS;

int main(int argc, char *argv[])
{
    int sim_id = 0, nDevices = 10, nMovingDevices = 1, nAPs = 2, simulationDuration = 20;
    bool g_verbose = true, trace = false, enableDynamicBeacon = false, trickleEnabled = false, uniform_dist = true;
    double startApplication = 1.0, endApplication = 20.0;
    double movingSTAxSpeed = 15.0, movingSTAySpeed = 15.0;
    double beaconInterval = 0.1,  maxAPDeviceRadius = 100.0, interestRadius = 0.85;
    unsigned scanInterval=10;
    double maxBeaconInterval = 6.4, minBeaconInterval = 0.1, apMaxRange = 120.0, distanceBetweenAPs = 80.0;
    unsigned maxpackets = 4294967295, packetSize = 1024;
    uint64_t packetInterval = 100;
    std::string outputFolder = "output";


    CommandLine cmd;
    //Number of devices configuration
    cmd.AddValue ("nDevices", "Number of static STA devices", nDevices);
    cmd.AddValue ("nMovingDevices", "Number of moving STA devices", nMovingDevices);
    cmd.AddValue ("nAPs", "Number of wifi STA devices", nAPs);
    cmd.AddValue ("maxAPDeviceRadius", "Max distance between AP and its STAs", maxAPDeviceRadius);

    //Moving STAs speed
    cmd.AddValue ("movingSTAxSpeed", "Speed of moving STAs on X axis", movingSTAxSpeed);
    cmd.AddValue ("movingSTAySpeed", "Speed of moving STAs on y axis", movingSTAySpeed);

    //Simulation duration
    cmd.AddValue ("simulationDuration", "Duration of simulation", simulationDuration);

    //Application duration
    cmd.AddValue ("startApplication", "When on simulation the application start", startApplication);
    cmd.AddValue ("endApplication",   "When on simulation the application stop", endApplication);

    //Beaconing parameters
    cmd.AddValue ("enableDynamicBeacon", "Enable the beacon interval to be dynamically adjusted", enableDynamicBeacon);
    cmd.AddValue ("beaconInterval", "Beacon interval in seconds", beaconInterval);
    cmd.AddValue ("trickleEnabled", "If true, trickle interval is inabled. Otherwise, dynamic adjustment", trickleEnabled);
    cmd.AddValue ("maxBeaconInterval", "Max beacon interval in seconds", maxBeaconInterval);
    cmd.AddValue ("minBeaconInterval", "Min beacon interval in seconds", minBeaconInterval);
    cmd.AddValue ("scanInterval", "Interval checked for changes in network in ms", scanInterval);
    cmd.AddValue ("interestRadius", "How much of radius show be scanned (percentile of largest known distance)", interestRadius);

    //Range of AP
    cmd.AddValue ("apMaxRange", "AP max range in meters", apMaxRange);

    //Distance between APs
    cmd.AddValue ("distanceBetweenAPs", "Average distance between APs", distanceBetweenAPs);

    //Interval between packets transmission and size of packets
    cmd.AddValue ("uniform_dist", "Distribution is uniform(true) or normal(false)", uniform_dist);
    cmd.AddValue ("packetInterval", "Packet interval between transmissions", packetInterval);
    cmd.AddValue ("packetSize", "Size of packages to be sent", packetSize);

    //Simulation ID, enable verbose and tracing
    cmd.AddValue ("sim_id", "Id of simulation (used in collected traces)", sim_id);
    cmd.AddValue ("g_verbose", "Tell echo applications to log if true", g_verbose);
    cmd.AddValue ("trace", "Enable pcap tracing", trace);
    cmd.Parse(argc, argv);

    std::stringstream outputFolderID;
    outputFolderID << outputFolder << sim_id;
#ifdef WIN32
    CreateDirectory(outputFolderID.str().c_str(), NULL);
#else
    mkdir(outputFolderID.str().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
    if (g_verbose)
    {
        enable_log();
    }

// 1. Create the nodes and hold them in a container
    NodeContainer wifiStaticStaNodes, wifiMovingStaNodes, wifiApNodes;
    wifiStaticStaNodes.Create(nDevices);
    wifiMovingStaNodes.Create(nMovingDevices);
    wifiApNodes.Create(nAPs);
    
// 2. Create channel for communication
    YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
    YansWifiPhyHelper phy = YansWifiPhyHelper::Default();
    channel.AddPropagationLoss("ns3::RangePropagationLossModel","MaxRange",DoubleValue(apMaxRange));

    phy.SetPcapDataLinkType(YansWifiPhyHelper::DLT_IEEE802_11_RADIO); //Radiotap
    phy.SetChannel(channel.Create());
    
    WifiHelper wifi;
    wifi.SetStandard(WIFI_PHY_STANDARD_80211n_2_4GHZ);
    wifi.SetRemoteStationManager("ns3::IdealWifiManager");
    NqosWifiMacHelper mac = NqosWifiMacHelper::Default();

// 3. Set up MAC
// 3a. Set up MAC for base stations
    Ssid ssid = Ssid("ns-3-ssid");
    mac.SetType("ns3::StaWifiMac",
                "Ssid", SsidValue(ssid),
                "ActiveProbing", BooleanValue(false));
    NetDeviceContainer staticStaDevices, movingStaDevices;

    staticStaDevices = wifi.Install(phy, mac, wifiStaticStaNodes);
    movingStaDevices = wifi.Install(phy, mac, wifiMovingStaNodes);


// 3b. Set up MAC for AP
    mac.SetType("ns3::ApWifiMac",
                "Ssid", SsidValue(ssid),
                "BeaconGeneration", BooleanValue(true),
                "BeaconInterval", TimeValue(Seconds(beaconInterval)),
                "MaxBeaconInterval", TimeValue(Seconds(maxBeaconInterval)),
                "MinBeaconInterval", TimeValue(Seconds(minBeaconInterval)),
                "EnableDynamicBeacon", BooleanValue(enableDynamicBeacon),
                "DynamicBeaconAdjustment", BooleanValue(trickleEnabled),
                "ScanInterval", UintegerValue(scanInterval),
                "InterestRadius", DoubleValue(interestRadius)
                );

    NetDeviceContainer apDevices;
    apDevices = wifi.Install(phy, mac, wifiApNodes);

// 4. Set mobility of the nodes
    MobilityHelper mobility;
    
    // Configure mobility of APs
    if (nAPs < 3)
        for (int i = 0; i < wifiApNodes.GetN(); i++)
        {
            NodeContainer nc;
            nc.Add(wifiApNodes.Get(i));
            setup_mobility(&nc, "ns3::ConstantPositionMobilityModel", 150+distanceBetweenAPs*(i), 150+distanceBetweenAPs*(i), 0.0);
        }
        
    //4 nodes
    if (nAPs == 4)
    {
        {
            NodeContainer nc;
            nc.Add(wifiApNodes.Get(0));
            setup_mobility(&nc, "ns3::ConstantPositionMobilityModel", 150 + distanceBetweenAPs * (0),
                           150 + distanceBetweenAPs * (0), 0.0);
        }
        {
            NodeContainer nc;
            nc.Add(wifiApNodes.Get(1));
            setup_mobility(&nc, "ns3::ConstantPositionMobilityModel", 150 + distanceBetweenAPs * (1),
                           150 + distanceBetweenAPs * (0), 0.0);
        }
        {
            NodeContainer nc;
            nc.Add(wifiApNodes.Get(2));
            setup_mobility(&nc, "ns3::ConstantPositionMobilityModel", 150 + distanceBetweenAPs * (0),
                           150 + distanceBetweenAPs * (1), 0.0);
        }
        {
            NodeContainer nc;
            nc.Add(wifiApNodes.Get(3));
            setup_mobility(&nc, "ns3::ConstantPositionMobilityModel", 150 + distanceBetweenAPs * (1),
                           150 + distanceBetweenAPs * (1), 0.0);
        }

    }

    // Configure mobility of static devices
    setup_mobility(&wifiStaticStaNodes, "ns3::ConstantPositionMobilityModel", 150.0, 150.0, maxAPDeviceRadius);

    // Configure mobility of moving devices
    setup_mobility(&wifiMovingStaNodes, "ns3::ConstantVelocityMobilityModel", 0.0, 0.0, 10.0);

    for (int i = 0; i < wifiMovingStaNodes.GetN(); i++)
    {
        Ptr<ConstantVelocityMobilityModel> mob = wifiMovingStaNodes.Get(i)->GetObject<ConstantVelocityMobilityModel>();
        mob->SetVelocity(Vector(movingSTAxSpeed, movingSTAySpeed, 0.0));
    }

// 5. Configure energy model
    LiIonEnergySourceHelper liIonEnergySourceHelper;
    liIonEnergySourceHelper.Set("LiIonEnergySourceInitialEnergyJ", DoubleValue(watthToJoule(0.005)));

    EnergySourceContainer staticEnergySourceContainer = liIonEnergySourceHelper.Install(wifiStaticStaNodes);
    EnergySourceContainer movingEnergySourceContainer = liIonEnergySourceHelper.Install(wifiMovingStaNodes);

    WifiRadioEnergyModelHelper radioEnergyModelHelper;

    DeviceEnergyModelContainer staticDeviceEnergyModelContainer = radioEnergyModelHelper.Install(staticStaDevices,staticEnergySourceContainer);
    DeviceEnergyModelContainer movingDeviceEnergyModelContainer = radioEnergyModelHelper.Install(movingStaDevices,movingEnergySourceContainer);


// 6.Add Internet layers stack
    InternetStackHelper stack;
    stack.Install(wifiStaticStaNodes);
    stack.Install(wifiMovingStaNodes);
    stack.Install(wifiApNodes);

// 7. Assign IP address to each device
    Ipv4AddressHelper address;
    Ipv4InterfaceContainer wifiStaticStaInterfaces, wifiMovingStaInterfaces, wifiApInterfaces;
    address.SetBase("10.1.1.0", "255.255.255.0");
    wifiApInterfaces = address.Assign(apDevices);
    wifiStaticStaInterfaces = address.Assign(staticStaDevices);
    wifiMovingStaInterfaces = address.Assign(movingStaDevices);
    

// 8a. Create and setup applications (traffic sink)
    UdpEchoServerHelper echoServer(8080); // Port
    ApplicationContainer serverApps = echoServer.Install(wifiApNodes.Get(0));
    serverApps.Start(Seconds(startApplication));
    serverApps.Stop(Seconds(endApplication));

// 8b. Create and setup applications (traffic source)
    UdpEchoClientHelper echoClient(wifiApNodes.Get(0)->GetObject<Ipv4>()->GetAddress(1,0).GetLocal(), 8080);
    echoClient.SetAttribute("MaxPackets", UintegerValue(maxpackets));
    echoClient.SetAttribute("Interval", TimeValue(MilliSeconds(packetInterval)));
    echoClient.SetAttribute("PacketSize", UintegerValue(packetSize));

    ApplicationContainer clientApps = echoClient.Install(wifiStaticStaNodes);

    if (uniform_dist)
    {
        std::uniform_real_distribution<double> unif(0.0, 1.0);
        std::default_random_engine re;
        for (unsigned i = 0; i < wifiStaticStaNodes.GetN();i++)
        {
            clientApps.Add(echoClient.Install(wifiStaticStaNodes.Get(i)));
            clientApps.Get(i)->SetAttribute("Interval",TimeValue(Seconds(packetInterval+unif(re))));
        }
    }
    else
    {
        std::normal_distribution<double> unif(packetInterval,packetInterval/4);
        std::default_random_engine re;
        for (unsigned i = 0; i < wifiStaticStaNodes.GetN();i++)
        {
            clientApps.Add(echoClient.Install(wifiStaticStaNodes.Get(i)));
            clientApps.Get(i)->SetAttribute("Interval",TimeValue(Seconds(packetInterval+unif(re))));
        }
    }


    clientApps.Start(Seconds(startApplication));
    clientApps.Stop(Seconds(endApplication));

    echoClient.SetAttribute("Interval", TimeValue(MilliSeconds(packetInterval)));
    ApplicationContainer movingClientApp = echoClient.Install(wifiMovingStaNodes);
    movingClientApp.Start(Seconds(startApplication));
    movingClientApp.Stop(Seconds(endApplication));


// 9. Enable tracing (optional)
    std::stringstream pcap_filename;
    pcap_filename << "wifi-"<<sim_id;
    //pcap_filename << "_beaconInterval-"<<(int)(beaconInterval)<<"s";
    //pcap_filename << "_packetInterval-"<<(int)(packetInterval)<<"s";
    //pcap_filename << "_packetSize-"<< packetSize<<"KB";
    phy.EnablePcap (outputFolderID.str()+"/"+pcap_filename.str(), wifiApNodes, true);

    //wifi.EnableLogComponents();
    //stack.EnablePcapIpv4("wif-ap2-ap", wifiApNodes);
    //stack.EnablePcapIpv4("wif-ap2-sta", wifiStaNodes);
    setup_print_position_and_battery();

//10. Configure animation
    //AnimationInterface anim = AnimationInterface(outputFolderID.str()+"/"+pcap_filename.str()+"_anim.xml");

    //setup_netanim(simulationDuration, &wifiApNodes, &anim);

//11. Run and destroy simulation
    Simulator::Stop(Seconds(simulationDuration));
    Simulator::Run();
    Simulator::Destroy();
    return 0;
}