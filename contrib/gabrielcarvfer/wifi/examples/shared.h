//
// Created by gabriel on 12/6/17.
//

#ifndef SHARED_CC
#define SHARED_CC


#include <ns3/netanim-module.h>
#include <ns3/bs-net-device.h>
#include <ns3/csma-module.h>
#include <ns3/uan-module.h>


#include <ns3/wifi-module.h>
#include <ns3/core-module.h>
#include <ns3/mobility-module.h>
#include <ns3/ipv4-global-routing-helper.h>
#include <ns3/internet-module.h>
#include <ns3/application-container.h>
#include <ns3/udp-echo-helper.h>
#include <ns3/li-ion-energy-source-helper.h>

#if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__)
#define WIN32
    #include <windows.h>
#else
#include <sys/stat.h>
#include <ns3/single-model-spectrum-channel.h>
#include <ns3/propagation-loss-model.h>
#include <ns3/propagation-delay-model.h>

#endif

using namespace ns3;

#define LOG(x) std::cout<<x<<std::endl


#define NETANIM_VARS BaseStationNetDevice b;\
SubscriberStationNetDevice s;\
CsmaNetDevice c;\
UanNetDevice u\

static void
PrintCellInfo (EnergySourceContainer esCon, ApplicationContainer *clientApps);

double watthToJoule(double watth);

bool enable_log();

void setup_mobility(NodeContainer * nodes, std::string mobilityModel, std::string x, std::string y, bool sta);

void setup_print_position_and_battery();
void setup_netanim(std::string outputFolder,
                   std::string output_anim_file,
                   int simulationDuration,
                   NodeContainer * wifiApNodes);
static void changeNetwork(Ptr<Node> station, Ptr<Node> ap1, Ptr<Node> ap2);

#endif //Shared.cc
