#include <ns3/picojson.h>
#include "loader-traffic-helper.h"
#include "ns3/json_loader.h"

using namespace ns3;

LoaderTrafficHelper::LoaderTrafficHelper()
{
}

LoaderTrafficHelper::~LoaderTrafficHelper() = default;

//For IOT traffic
ns3::ApplicationContainer LoaderTrafficHelper::LoadJsonTraffic(const ns3::NodeContainer &clientNodes,
                                                               ns3::Address serverAddress,
                                                               uint16_t serverPort,
                                                               std::string jsonfile,
                                                               bool tcp)
{
    return LoadJsonTraffic(clientNodes, serverAddress, serverPort, jsonfile, tcp, 1);
}

ns3::ApplicationContainer LoaderTrafficHelper::LoadJsonTraffic(const ns3::NodeContainer &clientNodes,
                                                               ns3::Address serverAddress,
                                                               uint16_t serverPort,
                                                               std::string jsonfile,
                                                               bool tcp,
                                                               uint16_t portsToSpreadTraffic)
{
    std::vector<float> timeToSend{0};
    ns3::ApplicationContainer apps;

    //Read from Json
    picojson::object o = load_json(jsonfile);

    if (o["time_between_packets"].is<double>())
    {
        // Used for uniformly spaced packets
        timeToSend[0] = o["time_between_packets"].get<double>();
    }
    else
    {
        auto time_between_packets = o["time_between_packets"].get<picojson::array>();
        int array_size = time_between_packets.size();
        timeToSend.resize(array_size);

        for (uint32_t j = 0; j < array_size; j++)
        {
            timeToSend[j] = time_between_packets[j].get<double>();
        }
    }
    std::vector<uint32_t> packetSizes{};
    if (o["packet_size"].is<double>())
    {
        // Used for uniformly sized packets
        double packetSize = o["packet_size"].get<double>();
        packetSizes.push_back(packetSize);
    }
    else
    {
        auto packet_sizes_array = o["packet_size"].get<picojson::array>();
        packetSizes.resize(packet_sizes_array.size());
        for (uint32_t j = 0; j < packet_sizes_array.size(); j++)
        {
            packetSizes[j] = (uint32_t) packet_sizes_array[j].get<double>();
        }
    }

    for (uint32_t i = 0; i < clientNodes.GetN(); i++)
    {
        ns3::Ptr<JsonTrafficInjectorApplication> app = ns3::CreateObject<JsonTrafficInjectorApplication> ();
        app->Setup (serverAddress, serverPort, packetSizes, timeToSend, tcp, portsToSpreadTraffic);
        clientNodes.Get (i)->AddApplication (app);
        apps.Add(app);
    }
    return apps;
}

