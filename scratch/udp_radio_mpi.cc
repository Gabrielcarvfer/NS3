//
// Created by Gabriel Ferreira (@gabrielcarvfer) on 15/04/2018.
//

//
// Created by Gabriel Ferreira (@gabrielcarvfer) on 21/03/2018.
//

/*
 *                    Host/Rank 0                                         Host/Rank 1
 *     +--------------------------------------------+      +--------------------------------------------+
 *     |                NS3                         |      |                NS3                         |
 *     |  +--------------------------------------+  |      |  +--------------------------------------+  |
 *     |  |      Node 0             Node 1       |  |      |  |      Node 0             Node 1       |  |
 *     |  |  +-------------+   +---------------+ |  |      |  |  +-------------+   +---------------+ |  |
 *     |  |  |   HTTP Cli  |   |               | |  |      |  |  |  HTTP Serv  |   |               | |  |
 *     |  |  |    TCP      |   |     TCP       | |  |      |  |  |    TCP      |   |     TCP       | |  |
 *     |  |  |    IP       |   |     IP        | |  |      |  |  |    IP       |   |     IP        | |  |
 *     |  |  |    CSMA     |   | CSMA |  TAP   | |  |      |  |  |    CSMA     |   | CSMA |  TAP   | |  |
 *     |  |  +------|------+   +--|-------|----+ |  |      |  |  +------|------+   +--|-------|----+ |  |
 *     |  |         +=============+       |      |  |      |  |         +=============+       |      |  |
 *     |  |            CSMA  BUS          |      |  |      |  |            CSMA  BUS          |      |  |
 *     |  +-------------------------------|------+  |      |  +-------------------------------|------+  |
 *     |                           +------|-----+   |      |                           +------|-----+   |
 *     |                           | TAP DEVICE |   |      |                           | TAP DEVICE |   |
 *     |                           +------|-----+   |      |                           +------|-----+   |
 *     |                     +------------|-----+   |      |                     +------------|-----+   |
 *     |                     |  Network Adapter ----------------------------------  Network Adapter |   |
 *     |                     +-|----------------+   |      |                     +-|----------------+   |
 *     +-----------------------|--------------------+      +-----------------------|--------------------+
 *                             |                                                   |
 *     +-----------------------|--------------------+      +-----------------------|--------------------+
 *     |           +-----------|-----+              |      |           +-----------|-----+              |
 *     |           | Network Adapter |              |      |           | Network Adapter |              |
 *     |           +-----------|-----+              |      |           +-----------|-----+              |
 *     |                       |                    |      |                       |                    |
 *     |           +-----------|-----+              |      |           +-----------|-----+              |
 *     |           |      Radio      -----------------------------------      Radio      |              |
 *     |           +-----------------+              |      |           +-----------------+              |
 *     +--------------------------------------------+      +--------------------------------------------+
 *                  Radio over UDP                                      Radio over UDP
 */

#include <ns3/core-module.h>
#include <ns3/lte-module.h>
#include <ns3/internet-module.h>
#include <ns3/mobility-module.h>
#include <ns3/applications-module.h>
#include <ns3/mpi-module.h>
#include <ns3/spectrum-module.h>
#include <ns3/tap-bridge-module.h>

//Para netanim
#include <ns3/netanim-module.h>
#include <ns3/bs-net-device.h>
#include <ns3/csma-module.h>
#include <ns3/uan-module.h>
#include <ns3/point-to-point-module.h>
#include <cstdint>

using namespace ns3;




int main(int argc, char * argv[])
{
    bool nullmsg;


    CommandLine cmd;
    cmd.AddValue ("nullmsg", "Enable the use of null-message synchronization", nullmsg);
    cmd.Parse (argc, argv);

    //Configure Simulation synchronization (distributed for MPI)
    if(nullmsg)
    {
        GlobalValue::Bind ("SimulatorImplementationType", StringValue ("ns3::NullMessageSimulatorImpl"));
    }
    else
    {
        GlobalValue::Bind ("SimulatorImplementationType", StringValue ("ns3::DistributedSimulatorImpl"));
    }

    //GlobalValue::Bind ("SimulatorImplementationType", StringValue ("ns3::RealtimeSimulatorImpl"));
    GlobalValue::Bind ("ChecksumEnabled", BooleanValue (true));

    // Enable parallel simulator with the command line arguments
    MpiInterface::Enable (&argc, &argv);

    NodeContainer nodesRank0, nodesRank1, routerNodesRank0Rank1;
    nodesRank0.Create (2, 0);
    nodesRank1.Create (2, 1);
    routerNodesRank0Rank1.Add(nodesRank0.Get(1));
    routerNodesRank0Rank1.Add(nodesRank1.Get(1));

    //Enable pcap tracing for all types of connections
    CsmaHelper csmaHelper;
    std::string outputFile = "distributed-rank" + MpiInterface::GetSystemId();
    //phy.EnablePcapAll (outputFile.c_str());
    csmaHelper.EnablePcapAll (outputFile.c_str());

    //Install CSMA to rank0 and rank1 nodes
    NetDeviceContainer csmaDevicesRank0, csmaDevicesRank1, csmaRoutersRank0Rank1;
    csmaDevicesRank0 = csmaHelper.Install(nodesRank0);
    csmaDevicesRank1 = csmaHelper.Install(nodesRank1);
    csmaRoutersRank0Rank1 = csmaHelper.Install(routerNodesRank0Rank1);

    //Install Internet stack
    InternetStackHelper internetStackHelper;
    internetStackHelper.Install(nodesRank0);
    internetStackHelper.Install(nodesRank1);

    //Assign addresses to each subnetwork
    Ipv4AddressHelper ipv4AddressHelper;
    ipv4AddressHelper.SetBase ("10.1.1.0", "255.255.255.0");
    ipv4AddressHelper.Assign (csmaDevicesRank0);
    ipv4AddressHelper.NewNetwork();

    ipv4AddressHelper.SetBase ("10.1.2.0", "255.255.255.0");
    ipv4AddressHelper.Assign (csmaDevicesRank1);
    ipv4AddressHelper.NewNetwork();

    ipv4AddressHelper.SetBase ("10.1.3.0", "255.255.255.0");
    Ipv4InterfaceContainer routerInterfaces = ipv4AddressHelper.Assign (csmaRoutersRank0Rank1);

    //Install TAP Bridge to node1 of rank0 and rank1
    if (MpiInterface::GetSystemId() == 0)
    {
        TapBridgeHelper tapBridge (routerInterfaces.GetAddress(0));
        tapBridge.SetAttribute ("Mode", StringValue ("ConfigureLocal"));
        tapBridge.SetAttribute ("DeviceName", StringValue ("tap"+MpiInterface::GetSystemId()));
        tapBridge.Install (routerNodesRank0Rank1.Get (0), csmaRoutersRank0Rank1.Get (0));
    }
    else
    {
        TapBridgeHelper tapBridge (routerInterfaces.GetAddress(1));
        tapBridge.SetAttribute ("Mode", StringValue ("ConfigureLocal"));
        tapBridge.SetAttribute ("DeviceName", StringValue ("tap"+MpiInterface::GetSystemId()));
        tapBridge.Install (routerNodesRank0Rank1.Get(1), csmaRoutersRank0Rank1.Get (1));
    }



/***************************************************/
    //Generate routing tables
    Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

    //Export a Netanim animation
    BaseStationNetDevice b;
    SubscriberStationNetDevice s;
    CsmaNetDevice c;
    UanNetDevice u;

    AnimationInterface anim("anim.xml");
    anim.SetMaxPktsPerTraceFile(0xFFFFFFFF);
    anim.EnablePacketMetadata(true);

    //Run simulator for 10 seconds
    Simulator::Stop(Seconds(10));
    Simulator::Run();
    Simulator::Destroy();

    return 0;
}
