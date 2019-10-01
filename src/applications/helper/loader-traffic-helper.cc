#include <ns3/picojson.h>
#include "loader-traffic-helper.h"
#include "ns3/json_loader.h"

using namespace ns3;

LoaderTrafficHelper::LoaderTrafficHelper()
{
}

LoaderTrafficHelper::~LoaderTrafficHelper() = default;

//For IOT traffic

ns3::ApplicationContainer LoaderTrafficHelper::LoadJsonTraffic(const ns3::NodeContainer &clientNodes, ns3::Address serverAddress, uint16_t serverPort, std::string jsonfile) {
    std::vector<float> timeToSend = {5,5,5,5,5,5,5,5,5};
    ns3::ApplicationContainer apps;

    //Read from Json
    picojson::object o = load_json(jsonfile);
    for (uint32_t i = 0; i < clientNodes.GetN(); i++)
    {

        auto time_between_packets = o["time_between_packets"].get<picojson::array>();
        int array_size = time_between_packets.size();
        timeToSend.resize(array_size);

        for (uint32_t j = 0; j < array_size; j++)
        {
            timeToSend[j] = time_between_packets[j].get<double>();
        }

        ns3::Ptr<ns3::Socket> ns3TcpSocket = ns3::Socket::CreateSocket (clientNodes.Get (i), ns3::TcpSocketFactory::GetTypeId ());
        ns3::Ptr<JsonTrafficInjectorApplication> app = ns3::CreateObject<JsonTrafficInjectorApplication> ();
        app->Setup (ns3TcpSocket, serverAddress, serverPort, o["packet_size"].get<double>(), array_size, timeToSend);
        clientNodes.Get (i)->AddApplication (app);

        //Simulator::Schedule(Seconds(o["init_time"].get<double>()), &IOTClient::Start, app);
        apps.Add(app);
    }
    return apps;
}

