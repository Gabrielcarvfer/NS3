//
// Created by gabriel on 12/6/17.
//

#include <random>
#include "shared.h"





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

bool enable_log()
{
    //LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_ALL);
    //LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_ALL);
    //LogComponentEnable("LiIonEnergySource", LOG_LEVEL_DEBUG);
    //LogComponentEnableAll(LOG_LEVEL_DEBUG);
    //LogComponentEnable("YansWifiPhy", LOG_LEVEL_ALL);
}

void setup_mobility(NodeContainer * nodes, std::string mobilityModel, double x, double y, double maxRho)
{
    MobilityHelper mobility;
    std::stringstream ss;
    ss << "ns3::UniformRandomVariable[Min=0|Max="<<maxRho<<"]";

    mobility.SetPositionAllocator ("ns3::RandomDiscPositionAllocator",
                                   "X", StringValue (std::to_string(x)),
                                   "Y", StringValue (std::to_string(y)),
                                   "Rho", StringValue (ss.str()));
    mobility.SetMobilityModel(mobilityModel);
    mobility.Install(*nodes);
}


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


void setup_print_position_and_battery()
{
    //Print ipv4 address of interfaces and XYZ position of nodes
    //ADD simulator print timeOfSimulation
    //std::string a1,b1,c1;
    //a1 = "IP addresses of base stations";
    //b1 = "IP address of AP";
    //c1 = "location of all nodes";

    //Simulator::Schedule(Seconds(1.01), &PrintAddresses, &wifiInterfaces, &a);
    //Simulator::Schedule(Seconds(1.02), &PrintAddresses, &wifiApInterface, &b);
    //Simulator::Schedule(Seconds(3.03), &PrintLocations, &wifiStaNodes, &c);

    //Print batteries info and disable nodes with low battery
    //PrintCellInfo(energySourceContainer, &clientApps);
}

void setup_netanim(int simulationDuration, NodeContainer * wifiApNodes, AnimationInterface * anim)
{
    anim->SetMaxPktsPerTraceFile(0xFFFFFFFF);
    anim->SetMobilityPollInterval(Seconds(0.1));
    anim->EnablePacketMetadata(true);
    //anim.EnableIpv4RouteTracking (outputFolder+"routingtable-wireless.xml", Seconds (0), Seconds (simulationDuration), Seconds (0.25));
    anim->EnableWifiMacCounters (Seconds (0), Seconds (simulationDuration));
    anim->EnableWifiPhyCounters (Seconds (0), Seconds (simulationDuration));


    for (uint32_t i = 0; i < wifiApNodes->GetN (); ++i)
    {
        //anim->UpdateNodeDescription (wifiApNodes->Get (i), "AP"); // Optional
        anim->UpdateNodeColor (wifiApNodes->Get (i), 0, 255, 0); // Optional
    }
}


static void changeNetwork(Ptr<Node> station, Ptr<Node> ap1, Ptr<Node> ap2)
{
    //station.GetObject<Ipv4Address>()->Set("10.1.2.2");
    auto staMac = station->GetObject<MacLow>()->GetAddress();
    ap1->GetObject<ApWifiMac>()->m_staList.remove(staMac);
    ap2->GetObject<ApWifiMac>()->m_staList.emplace_back(staMac);
    station->GetObject<Ipv4>()->GetAddress(1,0).SetLocal("10.1.2.2");
}