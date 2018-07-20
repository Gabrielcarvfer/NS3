// Node #0 is the AP, #1 is a base station
// #1 sends UDP echo mesg to the AP; AP sends a UDP response back to the node
// Communication is possible only when the station is within a certain distance from the AP

#include <random>
#include <ns3/mpi-module.h>
#include "shared.h"

using namespace ns3;

NETANIM_VARS;

EventId print_event;
void print_current_time()
{
    std::cout << "Current time: " << Simulator::Now() << std::endl;
    print_event = Simulator::Schedule(MilliSeconds(100),print_current_time);
}

int main(int argc, char *argv[])
{


    unsigned sim_id = 0, nDevicesPerAp = 5, nDevicesMovingPerAp = 2, nLevels = 1, nAPs = 10, simulationDuration = 600;
    bool g_verbose = true, trace = false, enableDynamicBeacon = false, trickleEnabled = true;
    double distanceBetweenAPs = 5.0, buildingHeight = 3.0;
    double startApplication = 1.0, endApplication = 20.0;
    double movingSTAxSpeed = 0.3, movingSTAySpeed = 0.3;
    double beaconInterval = 0.1, interestRadius = 0.85;
    unsigned scanInterval=10;
    double maxBeaconInterval = 6.4, minBeaconInterval = 0.1, apMaxRange = 30.0;
    uint64_t maxpackets = 4294967295000;
    unsigned packetSize = 10240;
    uint64_t packetInterval = 200;
    std::string outputFolder = "output/";

#ifdef WIN32
    CreateDirectory(outputFolder, NULL);
#else
    mkdir(outputFolder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

    CommandLine cmd;
    //Number of devices configuration
    cmd.AddValue ("nDevicesPerAp", "Number of static STA devices", nDevicesPerAp);
    cmd.AddValue ("nDevicesMovingPerAp", "Number of moving STA devices", nDevicesMovingPerAp);
    cmd.AddValue ("nAPs", "Number of wifi STA devices", nAPs);
    cmd.AddValue ("nLevels", "Number of levels", nLevels);

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
    cmd.AddValue ("trickleEnabled", "If true, trickle interval is inabled. Otherwise, dynamic adjustment", trickleEnabled);
    cmd.AddValue ("beaconInterval", "Beacon interval in seconds", beaconInterval);
    cmd.AddValue ("maxBeaconInterval", "Max beacon interval in seconds", maxBeaconInterval);
    cmd.AddValue ("minBeaconInterval", "Min beacon interval in seconds", minBeaconInterval);
    cmd.AddValue ("scanInterval", "Interval checked for changes in network in ms", scanInterval);
    cmd.AddValue ("interestRadius", "How much of radius show be scanned (percentile of largest known distance)", interestRadius);

    //Range of AP
    cmd.AddValue ("apMaxRange", "AP max range in meters", apMaxRange);

    //Distance between APs
    cmd.AddValue ("distanceBetweenAPs", "Average distance between APs", distanceBetweenAPs);

    //Interval between packets transmission and size of packets
    cmd.AddValue ("packetInterval", "Packet interval between transmissions", packetInterval);
    cmd.AddValue ("packetSize", "Size of packages to be sent", packetSize);

    //Simulation ID, enable verbose and tracing
    cmd.AddValue ("sim_id", "Id of simulation (used in collected traces)", sim_id);
    cmd.AddValue ("g_verbose", "Tell echo applications to log if true", g_verbose);
    cmd.AddValue ("trace", "Enable pcap tracing", trace);
    cmd.Parse(argc, argv);

    if (g_verbose)
    {
        enable_log();
    }

    //GlobalValue::Bind ("SimulatorImplementationType", StringValue ("ns3::DistributedSimulatorImpl"));

    // Enable parallel simulator with the command line arguments
    //MpiInterface::Enable (&argc, &argv);

    //unsigned numMpiNodes = MpiInterface::GetSize();
    //unsigned numApsPerNode = nAPs/numMpiNodes;
// 1. Create the nodes and hold them in a container
    NodeContainer wifiStaticStaNodes, wifiMovingStaNodes, wifiApNodes;

    /*
    for (unsigned rank = 0; rank < numMpiNodes; rank++)
    {
      wifiStaticStaNodes.Create((nDevicesPerAp - nDevicesMovingPerAp) * numApsPerNode,rank);
      wifiMovingStaNodes.Create(nDevicesMovingPerAp * numApsPerNode,rank);
      wifiApNodes.Create(numApsPerNode,rank);
    }
     */

    wifiStaticStaNodes.Create((nDevicesPerAp - nDevicesMovingPerAp) * nAPs);
    wifiMovingStaNodes.Create(nDevicesMovingPerAp * nAPs);
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

    for (unsigned i = 0; i < apDevices.GetN(); i++)
        apDevices.Get(i)->GetObject<WifiNetDevice>()->GetMac()->GetObject<RegularWifiMac>()->SetPromisc();

// 4. Set mobility of the nodes
    MobilityHelper mobility;

    //Number of APs per level
    uint32_t nApsPerLevel = (uint32_t) nAPs / nLevels;
    uint32_t nStaticDevicesPerAp = (uint32_t) nDevicesPerAp-nDevicesMovingPerAp;

    //Number of levels
    for (uint32_t j = 0; j < nLevels; j++)
    {
        //Number of rows per level
        for (uint32_t k = 0; k < 2; k++)
            for (uint32_t i = 0; i < nApsPerLevel/2; i++)
            {
                int apId = j * nApsPerLevel + (k * nApsPerLevel/2) + i;
                //if (MpiInterface::GetSystemId () == (apId / numApsPerNode))
                //{
                    double apX, apY, apZ;
                    apX = distanceBetweenAPs * (i);
                    apY = k * 2 * distanceBetweenAPs;
                    apZ = j * buildingHeight;

                    // Configure mobility of APs and related STAs
                    {
                        NodeContainer nc;
                        nc.Add(wifiApNodes.Get(apId));
                        setup_mobility2(&nc, "ns3::ConstantPositionMobilityModel", apX, apY, apZ, 0.0);
                    }

                    // Configure mobility of static devices
                    for (uint32_t staId = 0; staId < nStaticDevicesPerAp; staId++) {
                        NodeContainer nc;
                        uint32_t realStaId = (nStaticDevicesPerAp * apId) + staId;
                        nc.Add(wifiStaticStaNodes.Get(realStaId));
                        setup_mobility2(&nc, "ns3::ConstantPositionMobilityModel", apX, apY, apZ, distanceBetweenAPs*2);
                        std::cout << "Ap id: " << apId << " Sta estatico real id: " << realStaId << std::endl;

                    }

                    // Configure mobility of moving devices
                    for (uint32_t staId = 0; staId < nDevicesMovingPerAp; staId++) {
                        NodeContainer nc;
                        uint32_t realStaId = (nDevicesMovingPerAp * apId) + staId;
                        nc.Add(wifiMovingStaNodes.Get(realStaId));
                        setup_mobility2(&nc, "ns3::RandomWalk2dMobilityModel", apX, apY, apZ, distanceBetweenAPs*2);
                        Ptr<RandomWalk2dMobilityModel> mob = wifiMovingStaNodes.Get(
                                realStaId)->GetObject<RandomWalk2dMobilityModel>();
                        //mob->SetVelocity(Vector(movingSTAxSpeed, movingSTAySpeed, 0.0));
                        std::cout << "Ap id: " << apId << " Sta movel real id: " << realStaId << std::endl;

                    }
                //}
            }
    }

    //Setup switches
    NodeContainer switchNodes;
    switchNodes.Create(1);

    NodeContainer switchedNodes;
    switchedNodes.Add(switchNodes);
    switchedNodes.Add(wifiApNodes);

    CsmaHelper csmaHelper;

    NetDeviceContainer switchedDevices;
    csmaHelper.SetChannelAttribute("DataRate",StringValue("2Gbps"));
    switchedDevices = csmaHelper.Install(switchedNodes);

// 5. Configure energy model
    //LiIonEnergySourceHelper liIonEnergySourceHelper;
    //liIonEnergySourceHelper.Set("LiIonEnergySourceInitialEnergyJ", DoubleValue(watthToJoule(0.005)));
//
    //EnergySourceContainer staticEnergySourceContainer = liIonEnergySourceHelper.Install(wifiStaticStaNodes);
    //EnergySourceContainer movingEnergySourceContainer = liIonEnergySourceHelper.Install(wifiMovingStaNodes);
//
    //WifiRadioEnergyModelHelper radioEnergyModelHelper;
//
    //DeviceEnergyModelContainer staticDeviceEnergyModelContainer = radioEnergyModelHelper.Install(staticStaDevices,staticEnergySourceContainer);
    //DeviceEnergyModelContainer movingDeviceEnergyModelContainer = radioEnergyModelHelper.Install(movingStaDevices,movingEnergySourceContainer);


// 6.Add Internet layers stack
    NodeContainer allNodes;
    allNodes.Add(switchNodes);
    allNodes.Add(wifiApNodes);
    allNodes.Add(wifiStaticStaNodes);
    allNodes.Add(wifiMovingStaNodes);

    InternetStackHelper stack;
    stack.Install(allNodes);

// 7. Assign IP address to each device
    Ipv4AddressHelper address;
    NetDeviceContainer allNetDevices;
    allNetDevices.Add(apDevices);
    allNetDevices.Add(staticStaDevices);
    allNetDevices.Add(movingStaDevices);
    allNetDevices.Add(switchedDevices);

    Ipv4InterfaceContainer allNetInterfaces;
    address.SetBase("10.1.0.0", "255.255.0.0");
    allNetInterfaces = address.Assign(allNetDevices);
    
    Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

// 8a. Create and setup applications (traffic sink)
    UdpEchoServerHelper echoServer(8080); // Port
    ApplicationContainer serverApps = echoServer.Install(wifiApNodes);
    serverApps.Start(Seconds(1));
    serverApps.Stop(Seconds(simulationDuration-1));

// 8b. Create and setup applications (traffic source)


    std::normal_distribution<double> unif(packetInterval,packetInterval/4);
    std::default_random_engine re;

    ApplicationContainer clientApps;
    for (unsigned apId = 0; apId < wifiApNodes.GetN(); apId++)
    {
        //if (MpiInterface::GetSystemId () == (apId / numApsPerNode))
       //{
            UdpEchoClient2Helper echoClient(wifiApNodes.Get(apId)->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal(), 8080);
            echoClient.SetAttribute("MaxPackets", UintegerValue(maxpackets));
            echoClient.SetAttribute("Interval", TimeValue(MilliSeconds(packetInterval)));
            echoClient.SetAttribute("PacketSize", UintegerValue(packetSize));
            for (unsigned i = 0; i < nStaticDevicesPerAp; i++)
            {
                ApplicationContainer app = echoClient.Install(wifiStaticStaNodes.Get(nStaticDevicesPerAp * apId + i));
                app.Get(0)->SetAttribute("Interval", TimeValue(MilliSeconds(packetInterval + unif(re))));
                clientApps.Add(app);
            }

            for (unsigned i = 0; i < nDevicesMovingPerAp; i++)
            {
                ApplicationContainer app = echoClient.Install(wifiMovingStaNodes.Get(nDevicesMovingPerAp * apId + i));
                app.Get(0)->SetAttribute("Interval", TimeValue(MilliSeconds(packetInterval + unif(re))));
                clientApps.Add(app);
            }
        //}
    }
    clientApps.Start(Seconds(1));
    clientApps.Stop(Seconds(simulationDuration-1));


// 9. Enable tracing (optional)
    std::stringstream pcap_filename;
    //pcap_filename << "rank-" <<MpiInterface::GetSystemId () <<" wifi-"<<sim_id;
    pcap_filename << "wifi-"<<sim_id;
    //pcap_filename << "_beaconInterval-"<<(int)(beaconInterval)<<"s";
    //pcap_filename << "_packetInterval-"<<(int)(packetInterval)<<"s";
    //pcap_filename << "_packetSize-"<< packetSize<<"KB";
    phy.EnablePcap (outputFolder+pcap_filename.str(), wifiApNodes, true);

    //wifi.EnableLogComponents();
    //stack.EnablePcapIpv4("wif-ap2-ap", wifiApNodes);
    //stack.EnablePcapIpv4("wif-ap2-sta", wifiStaNodes);
    //setup_print_position_and_battery();

//10. Configure animation
    //AnimationInterface anim = AnimationInterface(outputFolder+pcap_filename.str()+"_anim.xml");

    //setup_netanim(simulationDuration, &wifiApNodes, &anim);

//11. Run and destroy simulation
    //if (MpiInterface::GetSystemId () == 0)
        //print_event = Simulator::Schedule(MilliSeconds(500),print_current_time);

    Simulator::Stop(Seconds(simulationDuration));
    Simulator::Run();
    Simulator::Destroy();

    //MpiInterface::Disable ();

    return 0;
}