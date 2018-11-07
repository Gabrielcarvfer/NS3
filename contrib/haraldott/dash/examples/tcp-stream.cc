/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright 2016 Technische Universitaet Berlin
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

// - TCP Stream server and user-defined number of clients connected with an AP
// - WiFi connection
// - Tracing of throughput, packet information is done in the client

#include <fstream>
#include "ns3/core-module.h"
#include "ns3/applications-module.h"
#include "ns3/internet-module.h"
#include "ns3/network-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include <ns3/buildings-module.h>
#include "ns3/building-position-allocator.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#include <ns3/flow-monitor-module.h>
#include <ns3/dash-module.h>
#include <ns3/point-to-point-module.h>

template<typename T>
std::string ToString(T val)
{
    std::stringstream stream;
    stream << val;
    return stream.str();
}

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("TcpStreamExample");

int
main(int argc, char *argv[])
{
//
// Users may find it convenient to turn on explicit debugging
// for selected modules; the below lines suggest how to do this
//
// #if 1
//   LogComponentEnable ("TcpStreamExample", LOG_LEVEL_INFO);
//   LogComponentEnable ("TcpStreamClientApplication", LOG_LEVEL_INFO);
//   LogComponentEnable ("TcpStreamServerApplication", LOG_LEVEL_INFO);
// #endif


    // The simulation id is used to distinguish log file results from potentially multiple consequent simulation runs.
    uint32_t simulationId = 1;
    uint32_t numberOfClients = 10;
    uint64_t segmentDuration = 100;
    std::string adaptationAlgo = "festive"; // festive | panda | tobasco
    std::string segmentSizeFilePath = "segmentsizes.txt";

    bool shortGuardInterval = true;

    CommandLine cmd;
    cmd.Usage("Simulation of streaming with DASH.\n");
    cmd.AddValue("simulationId", "The simulation's index (for logging purposes)", simulationId);
    cmd.AddValue("numberOfClients", "The number of clients", numberOfClients);
    cmd.AddValue("segmentDuration", "The duration of a video segment in microseconds", segmentDuration);
    cmd.AddValue("adaptationAlgo", "The adaptation algorithm that the client uses for the simulation", adaptationAlgo);
    cmd.AddValue("segmentSizeFile",
                 "The relative path (from ns-3.x directory) to the file containing the segment sizes in bytes",
                 segmentSizeFilePath);
    cmd.Parse(argc, argv);


    Config::SetDefault("ns3::TcpSocket::SegmentSize", UintegerValue(1446));
    Config::SetDefault("ns3::TcpSocket::SndBufSize", UintegerValue(524288));
    Config::SetDefault("ns3::TcpSocket::RcvBufSize", UintegerValue(524288));


    WifiHelper wifiHelper;
    wifiHelper.SetStandard(WIFI_PHY_STANDARD_80211n_5GHZ);
    wifiHelper.SetRemoteStationManager("ns3::MinstrelHtWifiManager");//


    /* Set up Legacy Channel */
    YansWifiChannelHelper wifiChannel = YansWifiChannelHelper::Default();
    // We do not set an explicit propagation loss model here, we just use the default ones that get applied with the building model.

    /* Setup Physical Layer */
    YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default();
    wifiPhy.SetPcapDataLinkType(YansWifiPhyHelper::DLT_IEEE802_11_RADIO);
    wifiPhy.Set("TxPowerStart", DoubleValue(20.0));//
    wifiPhy.Set("TxPowerEnd", DoubleValue(20.0));//
    wifiPhy.Set("TxPowerLevels", UintegerValue(1));//
    wifiPhy.Set("TxGain", DoubleValue(0));//
    wifiPhy.Set("RxGain", DoubleValue(0));//
    wifiPhy.SetErrorRateModel("ns3::YansErrorRateModel");//
    wifiPhy.SetChannel(wifiChannel.Create());
    wifiPhy.Set("ShortGuardEnabled", BooleanValue(shortGuardInterval));
    wifiPhy.Set("Antennas", UintegerValue(4));
    // wifiPhy.Set ("RxAntennas", UintegerValue (4));

    /* Create Nodes */
    NodeContainer networkNodes;
    networkNodes.Create(numberOfClients + 2);

    /* Determin access point and server node */
    Ptr<Node> apNode = networkNodes.Get(0);
    Ptr<Node> serverNode = networkNodes.Get(1);

    /* Configure clients as STAs in the WLAN */
    NodeContainer staContainer;
    /* Begin at +2, because position 0 is the access point and position 1 is the server */
    for (NodeContainer::Iterator i = networkNodes.Begin() + 2; i != networkNodes.End(); ++i)
    {
        staContainer.Add(*i);
    }

    /* Determin client nodes for object creation with client helper class */
    std::vector<std::pair<Ptr<Node>, std::string> > clients;
    for (NodeContainer::Iterator i = networkNodes.Begin() + 2; i != networkNodes.End(); ++i)
    {
        std::pair<Ptr<Node>, std::string> client(*i, adaptationAlgo);
        clients.push_back(client);
    }

    /* Set up WAN link between server node and access point*/
    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate",
                           StringValue("100000kb/s")); // This must not be more than the maximum throughput in 802.11n
    p2p.SetDeviceAttribute("Mtu", UintegerValue(1500));
    p2p.SetChannelAttribute("Delay", StringValue("45ms"));
    NetDeviceContainer wanIpDevices;
    wanIpDevices = p2p.Install(serverNode, apNode);

    /* create MAC layers */
    WifiMacHelper wifiMac;
    /* WLAN configuration */
    Ssid ssid = Ssid("network");
    /* Configure STAs for WLAN*/

    wifiMac.SetType("ns3::StaWifiMac",
                    "Ssid", SsidValue(ssid));
    NetDeviceContainer staDevices;
    staDevices = wifiHelper.Install(wifiPhy, wifiMac, staContainer);

    /* Configure AP for WLAN*/
    wifiMac.SetType("ns3::ApWifiMac",
                    "Ssid", SsidValue(ssid));
    NetDeviceContainer apDevice;
    apDevice = wifiHelper.Install(wifiPhy, wifiMac, apNode);


    Config::Set("/NodeList/*/DeviceList/*/$ns3::WifiNetDevice/Phy/ChannelWidth", UintegerValue(40));

    /* Determin WLAN devices (AP and STAs) */
    NetDeviceContainer wlanDevices;
    wlanDevices.Add(staDevices);
    wlanDevices.Add(apDevice);

    /* Internet stack */
    InternetStackHelper stack;
    stack.Install(networkNodes);

    /* Assign IP addresses */
    Ipv4AddressHelper address;

    /* IPs for WAN */
    address.SetBase("76.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer wanInterface = address.Assign(wanIpDevices);
    Address serverAddress = Address(wanInterface.GetAddress(0));

    /* IPs for WLAN (STAs and AP) */
    address.SetBase("192.168.1.0", "255.255.255.0");
    address.Assign(wlanDevices);

    /* Populate routing table */
    Ipv4GlobalRoutingHelper::PopulateRoutingTables();
    uint16_t port = 9;


//////////////////////////////////////////////////////////////////////////////////////////////////
//// Set up Building
//////////////////////////////////////////////////////////////////////////////////////////////////
    double roomHeight = 3;
    double roomLength = 6;
    double roomWidth = 5;
    uint32_t xRooms = 8;
    uint32_t yRooms = 3;
    uint32_t nFloors = 6;

    Ptr<Building> b = CreateObject<Building>();
    b->SetBoundaries(Box(0.0, xRooms * roomWidth,
                         0.0, yRooms * roomLength,
                         0.0, nFloors * roomHeight));
    b->SetBuildingType(Building::Office);
    b->SetExtWallsType(Building::ConcreteWithWindows);
    b->SetNFloors(6);
    b->SetNRoomsX(8);
    b->SetNRoomsY(3);

    Vector posAp = Vector(1.0, 1.0, 1.0);
    // give the server node any position, it does not have influence on the simulation, it has to be set though,
    // because when we do: mobility.Install (networkNodes);, there has to be a position as place holder for the server
    // because otherwise the first client would not get assigned the desired position.
    Vector posServer = Vector(1.5, 1.5, 1.5);

    /* Set up positions of nodes (AP and server) */
    Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator>();
    positionAlloc->Add(posAp);
    positionAlloc->Add(posServer);


    Ptr<RandomRoomPositionAllocator> randPosAlloc = CreateObject<RandomRoomPositionAllocator>();
    randPosAlloc->AssignStreams(simulationId);

    // create folder so we can log the positions of the clients
    const char *mylogsDir = ("mylogs/");
    mkdir(mylogsDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    const char *tobascoDir = ("mylogs/" + adaptationAlgo).c_str();
    mkdir(tobascoDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    const char *dir = ("mylogs/" + adaptationAlgo + "/" + ToString(numberOfClients) + "/").c_str();
    mkdir(dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    std::ofstream clientPosLog;
    std::string clientPos =
            "mylogs/" + adaptationAlgo + "/" + ToString(numberOfClients) + "/" + "sim" + ToString(simulationId) + "_" +
            "clientPos.txt";
    clientPosLog.open(clientPos.c_str());
    NS_ASSERT_MSG (clientPosLog.is_open(), "Couldn't open clientPosLog file");

    // allocate clients to positions
    for (uint i = 0; i < numberOfClients; i++)
    {
        Vector pos = Vector(randPosAlloc->GetNext());
        positionAlloc->Add(pos);

        // log client positions
        clientPosLog << ToString(pos.x) << ", " << ToString(pos.y) << ", " << ToString(pos.z) << "\n";
        clientPosLog.flush();
    }


    MobilityHelper mobility;
    mobility.SetPositionAllocator(positionAlloc);
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    // install all of the nodes that have been added to positionAlloc to the mobility model
    mobility.Install(networkNodes);
    BuildingsHelper::Install(networkNodes); // networkNodes contains all nodes, stations and ap
    BuildingsHelper::MakeMobilityModelConsistent();

    // if logging of the packets between AP---Server or AP and the STAs is wanted, these two lines can be activated

    p2p.EnablePcapAll("p2p-", true);
    wifiPhy.EnablePcapAll("wifi-", true);



    /* Install TCP Receiver on the access point */
    TcpStreamServerHelper serverHelper(port);
    ApplicationContainer serverApp = serverHelper.Install(serverNode);
    serverApp.Start(Seconds(1.0));

    /* Install TCP/UDP Transmitter on the station */
    TcpStreamClientHelper clientHelper(serverAddress, port);
    clientHelper.SetAttribute("SegmentDuration", UintegerValue(segmentDuration));
    clientHelper.SetAttribute("SegmentSizeFilePath", StringValue(segmentSizeFilePath));
    clientHelper.SetAttribute("NumberOfClients", UintegerValue(numberOfClients));
    clientHelper.SetAttribute("SimulationId", UintegerValue(simulationId));
    ApplicationContainer clientApps = clientHelper.Install(clients);
    for (uint i = 0; i < clientApps.GetN(); i++)
    {
        double startTime = i * 3;
        clientApps.Get(i)->SetStartTime(Seconds(startTime));
    }


    NS_LOG_INFO ("Run Simulation.");
    NS_LOG_INFO ("Sim: " << simulationId << "Clients: " << numberOfClients);
    Simulator::Stop(Seconds(500));
    Simulator::Run();
    Simulator::Destroy();
    NS_LOG_INFO ("Done.");

}
