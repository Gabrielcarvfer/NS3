#ifndef LOADER_TRAFFIC_H
#define LOADER_TRAFFIC_H

#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/json-traffic-injector-application.h"
#include "ns3/on-off-helper.h"
#include <fstream>

class LoaderTrafficHelper
{
private:
    /* data */
    std::string pathToJsonLoad;
public:
     LoaderTrafficHelper();
    ~LoaderTrafficHelper();

    ns3::ApplicationContainer LoadJsonTraffic(const ns3::NodeContainer &clientNodes,
                                              ns3::Address serverAddress,
                                              uint16_t serverPort,
                                              std::string jsonfile,
                                              bool tcp);
};

#endif /* LOADER_TRAFFIC_H */