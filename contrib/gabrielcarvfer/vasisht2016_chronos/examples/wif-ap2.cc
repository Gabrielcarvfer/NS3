// Node #0 is the AP, #1 is a base station
// #1 sends UDP echo mesg to the AP; AP sends a UDP response back to the node
// Communication is possible only when the station is within a certain distance from the AP
#include <ns3/netanim-module.h>
#include <ns3/bs-net-device.h>
#include <ns3/csma-module.h>
#include <ns3/uan-module.h>
#include <ns3/basic-energy-source.h>
#include <ns3/simple-device-energy-model.h>
#include "ns3/core-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/internet-module.h"
#include "ns3/application-container.h"
#include "ns3/udp-echo-helper.h"
#include "ns3/li-ion-energy-source-helper.h"


using namespace ns3;

#define LOG(x) std::cout<<x<<std::endl

static void
PrintCellInfo (EnergySourceContainer esCon, ApplicationContainer *clientApps)
{
    for (unsigned i = 0; i < esCon.GetN(); i++)
    {
        /*
        std::cout << "Node(" << i << ") At " << Simulator::Now().GetSeconds();
        std::cout << " seconds, Cell voltage: " << esCon.Get(i)->GetSupplyVoltage();
        std::cout << " V Remaining Capacity: " << esCon.Get(i)->GetRemainingEnergy() / (3.6 * 3600) << " Ah";
        std::cout << " Remaining charge "<<esCon.Get(i)->GetEnergyFraction()*100 << "%";
        std::cout << std::endl;
        */
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
    double simulationDuration = 100.0;

    Config::SetDefault ("ns3::RandomWalk2dMobilityModel::Mode", StringValue ("Time"));
    Config::SetDefault ("ns3::RandomWalk2dMobilityModel::Time", StringValue ("2s"));
    Config::SetDefault ("ns3::RandomWalk2dMobilityModel::Speed", StringValue ("ns3::UniformRandomVariable[Min=1.0|Max=5.0]"));
    Config::SetDefault ("ns3::RandomWalk2dMobilityModel::Bounds", StringValue ("0|200|0|200"));

    CommandLine cmd;
    cmd.AddValue ("nDevices", "Number of wifi STA devices", nDevices);
    cmd.AddValue ("nAPs", "Number of wifi STA devices", nAPs);
    cmd.AddValue ("g_verbose", "Tell echo applications to log if true", g_verbose);
    cmd.AddValue ("trace", "Enable pcap tracing", trace);
    cmd.Parse(argc, argv);

    if (g_verbose)
    {
        LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_ALL);
        LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_ALL);
        LogComponentEnable("LiIonEnergySource", LOG_LEVEL_DEBUG);
        //LogComponentEnableAll(LOG_LEVEL_DEBUG);
    }

// 1. Create the nodes and hold them in a container
    NodeContainer wifiStaNodes, wifiApNodes;
    wifiStaNodes.Create(nDevices);
    wifiApNodes.Create(nAPs);
    
// 2. Create channel for communication
    YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
    YansWifiPhyHelper phy = YansWifiPhyHelper::Default();
    phy.SetChannel(channel.Create());
    
    WifiHelper wifi;
    wifi.SetRemoteStationManager("ns3::AarfWifiManager");
    
    NqosWifiMacHelper mac = NqosWifiMacHelper::Default();

// 3. Set up MAC
// 3a. Set up MAC for base stations
    Ssid ssid = Ssid("ns-3-ssid");
    mac.SetType("ns3::StaWifiMac",
                "Ssid", SsidValue(ssid),
                "ActiveProbing", BooleanValue(false));
    NetDeviceContainer staDevices;

    staDevices = wifi.Install(phy, mac, wifiStaNodes);

// 3b. Set up MAC for AP
    mac.SetType("ns3::ApWifiMac",
                "Ssid", SsidValue(ssid),
                "BeaconGeneration", BooleanValue(true),
                "BeaconInterval", TimeValue(Seconds(5)));
    NetDeviceContainer apDevices;
    apDevices = wifi.Install(phy, mac, wifiApNodes);

// 4. Set mobility of the nodes
    MobilityHelper mobility;

    // Configure mobility of APs
        mobility.SetPositionAllocator ("ns3::RandomDiscPositionAllocator",
                                       "X", StringValue ("100.0"),
                                       "Y", StringValue ("100.0"),
                                       "Rho", StringValue ("ns3::UniformRandomVariable[Min=0|Max=30]"));
        mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
        mobility.Install(wifiApNodes);

    // Configure mobility of devices
        mobility.SetPositionAllocator ("ns3::RandomDiscPositionAllocator",
                                       "X", StringValue ("100.0"),
                                       "Y", StringValue ("100.0"),
                                       "Rho", StringValue ("ns3::UniformRandomVariable[Min=0|Max=60]"));

        mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                                   "Mode", StringValue ("Time"),
                                   "Time", StringValue ("2s"),
                                   "Speed", StringValue ("ns3::UniformRandomVariable[Min=1.0|Max=10.0]"),//ConstantRandomVariable[Constant=1.0]"),
                                   "Bounds", StringValue ("0|200|0|200"));

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
    UdpEchoServerHelper echoServer(9); // Port # 9
    ApplicationContainer serverApps = echoServer.Install(wifiApNodes.Get(0));
    serverApps.Start(Seconds(3.0));
    serverApps.Stop(Seconds(simulationDuration-1.0));

// 8b. Create and setup applications (traffic source)
    UdpEchoClientHelper echoClient(wifiApInterfaces.GetAddress(0), 9);
    echoClient.SetAttribute("MaxPackets", UintegerValue(10000));
    echoClient.SetAttribute("Interval", TimeValue(Seconds(1.)));
    echoClient.SetAttribute("PacketSize", UintegerValue(1024));

    ApplicationContainer clientApps = echoClient.Install(wifiStaNodes);
    clientApps.Start(Seconds(2.0));
    clientApps.Stop(Seconds(simulationDuration-1.0));

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

// 9. Enable tracing (optional)
    phy.EnablePcapAll ("wifi-2-nodes-fixed", true);
    //wifi.EnableLogComponents();
    stack.EnablePcapIpv4("wif-ap2-ap", wifiApNodes);
    stack.EnablePcapIpv4("wif-ap2-sta", wifiStaNodes);


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
    PrintCellInfo(energySourceContainer, &clientApps);

//10. Configure animation
    BaseStationNetDevice b;
    SubscriberStationNetDevice s;
    CsmaNetDevice c;
    UanNetDevice u;

    AnimationInterface anim("anim2.xml");
    anim.SetMaxPktsPerTraceFile(0xFFFFFFFF);
    anim.SetMobilityPollInterval(Seconds(1.0));
    anim.EnablePacketMetadata(true);
    anim.EnableIpv4RouteTracking ("routingtable-wireless.xml", Seconds (0), Seconds (5), Seconds (0.25));
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