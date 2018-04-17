//
// Created by Gabriel Ferreira (@gabrielcarvfer) on 10/04/2018.
//
//DCE_PATH=./ ./test_dce

#include <chrono>
#include <thread>
#include "ns3/network-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/dce-module.h"

using namespace ns3;

int main (int argc, char *argv[])
{
    CommandLine cmd;
    cmd.Parse (argc, argv);

    NodeContainer nodes;
    nodes.Create (1);

    InternetStackHelper stack;
    stack.Install (nodes);

    DceManagerHelper dceManager;
    dceManager.SetVirtualPath("./");
    dceManager.Install (nodes);

    DceApplicationHelper dce;
    ApplicationContainer apps, temp;

    dce.SetStackSize (1 << 20);

    dce.SetBinary ("tcp-server");
    dce.ResetArguments ();
    temp = dce.Install (nodes.Get (0));
    temp.Start (Seconds (4.0));
    apps.Add(temp);

    dce.SetBinary ("tcp-client");
    dce.ResetArguments ();
    dce.AddArgument ("127.0.0.1");
    temp = dce.Install (nodes.Get (0));
    temp.Start (Seconds (4.5));
    apps.Add(temp);

    Simulator::Stop (Seconds (600.0));
    Simulator::Run ();
    Simulator::Destroy ();

    std::cout<< "Done!"<<std::endl;
    return 0;
}