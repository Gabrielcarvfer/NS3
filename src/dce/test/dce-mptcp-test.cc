#include "ns3/test.h"
#include "ns3/dce-module.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

static std::string g_testError;

using namespace ns3;
namespace ns3 {

class DceMptcpTestCase : public TestCase
{
public:
  DceMptcpTestCase (std::string testname, Time maxDuration, std::string sock_factory, bool skip);
private:
  virtual void DoRun (void);
  virtual void DoBasicRun (void);
  virtual void DoAddrTestRun (void);
  static void Finished (int *pstatus, uint16_t pid, int status);

  std::string m_testname;
  Time m_maxDuration;
  std::string m_sockf;
  bool m_skip;
};

DceMptcpTestCase::DceMptcpTestCase (std::string testname, Time maxDuration, std::string sock_factory, bool skip)
  : TestCase (std::string ("") + (skip ? "(SKIP) " : "" ) + testname),
    m_testname (testname), 
    m_maxDuration (maxDuration),
    m_sockf (sock_factory), 
    m_skip (skip)
{
//  mtrace ();
}
void
DceMptcpTestCase::Finished (int *pstatus, uint16_t pid, int status)
{
  *pstatus = status;
}
bool g_rcv0 = false;
bool g_rcv1 = false;
static void
ReceivedBytes (std::string context, Ptr<const Packet> originalPacket)
{
  Ptr<Packet> packet = originalPacket->Copy ();
  PppHeader ppp;
  Ipv4Header v4hdr;

  packet->RemoveHeader (ppp);
  if (ppp.GetProtocol () == 0x0021) // IPv4
    {
      packet->RemoveHeader (v4hdr);
      if (v4hdr.GetSource () == Ipv4Address ("10.1.0.1"))
        {
          std::cout << "saddr1 = " << v4hdr.GetSource () << std::endl;
          g_rcv0 = true;
        }
      if (v4hdr.GetSource () == Ipv4Address ("10.1.1.1"))
        {
          std::cout << "saddr2 = " << v4hdr.GetSource () << std::endl;
          g_rcv1 = true;
        }
    }

  if (0)
    {
      std::cout << context << " " << packet << std::endl;
      packet->Print (std::cout);
      std::cout << std::endl;
    }
}

bool isMptcpEnabled = false;
static void
SetMptcpEnabled (std::string key, std::string value)
{
  std::cout << key << "=" << value << std::endl;
  if (key == ".net.mptcp.mptcp_debug" &&
      value.find ("1") != std::string::npos)
    {
      isMptcpEnabled = true;
    }
}

void
DceMptcpTestCase::DoBasicRun (void)
{
  g_rcv0 = false;
  g_rcv1 = false;

  uint32_t nRtrs = 2;
  std::string m_rate = "200Bps";
  NodeContainer nodes, routers;
  nodes.Create (2);
  routers.Create (nRtrs);

  DceManagerHelper dceManager;
  dceManager.SetNetworkStack("ns3::LinuxSocketFdFactory",
                             "Library", StringValue ("liblinux.so"));

  LinuxStackHelper stack;
  stack.Install (nodes);
  stack.Install (routers);

  dceManager.Install (nodes);
  dceManager.Install (routers);

  LinuxStackHelper::SysctlGet (nodes.Get (0), Seconds (1.0),
                               ".net.mptcp.mptcp_debug", &SetMptcpEnabled);

  PointToPointHelper pointToPoint;
  NetDeviceContainer devices1, devices2;
  Ipv4AddressHelper address1, address2;
  std::ostringstream cmd_oss;
  address1.SetBase ("10.1.0.0", "255.255.255.0");
  address2.SetBase ("10.2.0.0", "255.255.255.0");

  for (uint32_t i = 0; i < nRtrs; i++)
    {
      // Left link
      pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
      pointToPoint.SetChannelAttribute ("Delay", StringValue ("10ms"));
      devices1 = pointToPoint.Install (nodes.Get (0), routers.Get (i));
      // Assign ip addresses
      Ipv4InterfaceContainer if1 = address1.Assign (devices1);
      address1.NewNetwork ();
      // setup ip routes
      cmd_oss.str ("");
      cmd_oss << "rule add from " << if1.GetAddress (0, 0) << " table " << (i+1);
      LinuxStackHelper::RunIp (nodes.Get (0), Seconds (0.1), cmd_oss.str ().c_str ());
      cmd_oss.str ("");
      cmd_oss << "route add 10.1." << i << ".0/24 dev sim" << i << " scope link table " << (i+1);
      LinuxStackHelper::RunIp (nodes.Get (0), Seconds (0.1), cmd_oss.str ().c_str ());
      cmd_oss.str ("");
      cmd_oss << "route add default via " << if1.GetAddress (1, 0) << " dev sim" << i << " table " << (i+1);
      LinuxStackHelper::RunIp (nodes.Get (0), Seconds (0.1), cmd_oss.str ().c_str ());
      cmd_oss.str ("");
      cmd_oss << "route add 10.1.0.0/16 via " << if1.GetAddress (1, 0) << " dev sim0";
      LinuxStackHelper::RunIp (routers.Get (i), Seconds (0.2), cmd_oss.str ().c_str ());

      // delete address at 20sec
      LinuxStackHelper::RunIp (nodes.Get (0), Seconds (20), "-f inet addr delete 10.1.1.1/24 dev sim1");

      // Right link
      pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("100Mbps"));
      pointToPoint.SetChannelAttribute ("Delay", StringValue ("1ns"));
      devices2 = pointToPoint.Install (nodes.Get (1), routers.Get (i));
      // Assign ip addresses
      Ipv4InterfaceContainer if2 = address2.Assign (devices2);
      address2.NewNetwork ();
      // setup ip routes
      cmd_oss.str ("");
      cmd_oss << "rule add from " << if2.GetAddress (0, 0) << " table " << (i+1);
      LinuxStackHelper::RunIp (nodes.Get (1), Seconds (0.1), cmd_oss.str ().c_str ());
      cmd_oss.str ("");
      cmd_oss << "route add 10.2." << i << ".0/24 dev sim" << i << " scope link table " << (i+1);
      LinuxStackHelper::RunIp (nodes.Get (1), Seconds (0.1), cmd_oss.str ().c_str ());
      cmd_oss.str ("");
      cmd_oss << "route add default via " << if2.GetAddress (1, 0) << " dev sim" << i << " table " << (i+1);
      LinuxStackHelper::RunIp (nodes.Get (1), Seconds (0.1), cmd_oss.str ().c_str ());
      cmd_oss.str ("");
      cmd_oss << "route add 10.2.0.0/16 via " << if2.GetAddress (1, 0) << " dev sim1";
      LinuxStackHelper::RunIp (routers.Get (i), Seconds (0.2), cmd_oss.str ().c_str ());
    }

  // default route
  LinuxStackHelper::RunIp (nodes.Get (0), Seconds (0.1), "route add default via 10.1.0.2 dev sim0");
  LinuxStackHelper::RunIp (nodes.Get (1), Seconds (0.1), "route add default via 10.2.0.2 dev sim0");
  LinuxStackHelper::RunIp (nodes.Get (0), Seconds (0.1), "rule show");

  // debug
  stack.SysctlSet (nodes, ".net.mptcp.mptcp_debug", "1");

  ApplicationContainer apps;
  OnOffHelper onoff = OnOffHelper (m_sockf,
                                   InetSocketAddress ("10.2.0.1", 9));
  onoff.SetAttribute ("OnTime", StringValue ("ns3::ConstantRandomVariable[Constant=1]"));
  onoff.SetAttribute ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=0]"));
  onoff.SetAttribute ("PacketSize", StringValue ("1024"));
  onoff.SetAttribute ("DataRate", StringValue (m_rate));
  apps = onoff.Install (nodes.Get (0));
  apps.Start (Seconds (4.0));

  PacketSinkHelper sink = PacketSinkHelper (m_sockf,
                                            InetSocketAddress (Ipv4Address::GetAny (), 9));
  apps = sink.Install (nodes.Get (1));
  apps.Start (Seconds (3.9999));
  Config::Connect ("/NodeList/1/DeviceList/*/$ns3::PointToPointNetDevice/PhyRxEnd",
                   MakeCallback (&ReceivedBytes));

  //  pointToPoint.EnablePcapAll ("dce-cradle-simple");
  if (m_maxDuration.IsStrictlyPositive ()) {
      Simulator::Stop (m_maxDuration);
    }
  Simulator::Run ();

  Ptr<PacketSink> pktsink;
  pktsink = apps.Get (0)->GetObject<PacketSink> ();;
  std::cout << "Total Rx(0) = " << pktsink->GetTotalRx () << 
    " bytes";
  std::cout << std::endl;
  Simulator::Destroy ();

  if (!isMptcpEnabled)
    {
      std::cout << "Probably failed? Because mptcp disabled kernel. SKIP." << std::endl;
      return;
    }

  int status = (g_rcv0 == true && g_rcv1 == true);
  NS_TEST_ASSERT_MSG_EQ (status, 1, "Process did not return successfully: " << g_testError);
}

void
DceMptcpTestCase::DoAddrTestRun (void)
{
  g_rcv0 = false;
  g_rcv1 = false;

  double stopTime = 15.0;
  std::string p2pdelay = "10ms";
  std::string iperfTime = "10";

  PointToPointHelper pointToPoint;
  NodeContainer nodes;
  LinuxStackHelper stack;
  DceManagerHelper dceManager;
  NetDeviceContainer clientDevices;

  nodes.Create (3);

  dceManager.SetNetworkStack ("ns3::LinuxSocketFdFactory", "Library", StringValue ("liblinux.so"));
  stack.Install (nodes);
  dceManager.Install (nodes);

  LinuxStackHelper::SysctlGet (nodes.Get (0), Seconds (1.0),
                               ".net.mptcp.mptcp_debug", &SetMptcpEnabled);

  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("100Kb/s"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue (p2pdelay));
  pointToPoint.Install(nodes.Get(1), nodes.Get(2));

  /*Setup Server Routes*/
  LinuxStackHelper::RunIp (nodes.Get (2), Seconds (0.1), "link set up dev sim0");
  LinuxStackHelper::RunIp (nodes.Get (2), Seconds (0.1), "addr add 172.16.1.1/24 dev sim0");
  LinuxStackHelper::RunIp (nodes.Get (2), Seconds (0.1), "route add 10.1.0.0/24 via 172.16.1.10 dev sim0");
  LinuxStackHelper::RunIp (nodes.Get (2), Seconds (0.1), "route add 10.1.1.0/24 via 172.16.1.10 dev sim0");

  /*Setup Gateway->Server*/
  LinuxStackHelper::RunIp (nodes.Get (1), Seconds (0.1), "link set up dev sim0");
  LinuxStackHelper::RunIp (nodes.Get (1), Seconds (0.1), "addr add 172.16.1.10/24 dev sim0");

  /*Setup Client Addresses*/
  pointToPoint.Install(nodes.Get(0), nodes.Get(1));
  LinuxStackHelper::RunIp (nodes.Get (0), Seconds (0.1), "link set up dev sim0");
  LinuxStackHelper::RunIp (nodes.Get (0), Seconds (0.2), "addr add 10.1.0.1/24 dev sim0");
  LinuxStackHelper::RunIp (nodes.Get (0), Seconds (0.3), "route add default via 10.1.0.10 dev sim0 metric 1");
  LinuxStackHelper::RunIp (nodes.Get (0), Seconds (0.4), "rule add from 10.1.0.0/24 lookup 1");
  LinuxStackHelper::RunIp (nodes.Get (0), Seconds (0.3), "route add default via 10.1.0.10 dev sim0 table 1");
  LinuxStackHelper::RunIp (nodes.Get (0), Seconds (0.1), "route add 10.1.0.0/24 dev sim0 table 1");

  LinuxStackHelper::RunIp (nodes.Get (0), Seconds (3.2), "addr add 10.1.1.1/24 dev sim0");
  LinuxStackHelper::RunIp (nodes.Get (0), Seconds (3.3), "route add default via 10.1.1.10 dev sim0 metric 1");
  LinuxStackHelper::RunIp (nodes.Get (0), Seconds (3.4), "rule add from 10.1.1.0/24 lookup 1");
  LinuxStackHelper::RunIp (nodes.Get (0), Seconds (3.3), "route add default via 10.1.1.10 dev sim0 table 1");
  LinuxStackHelper::RunIp (nodes.Get (0), Seconds (3.1), "route add 10.1.1.0/24 dev sim0 table 1");

  /*Setup Gateway Addresses*/
  LinuxStackHelper::RunIp (nodes.Get (1), Seconds (0.1), "link set up dev sim1");
  LinuxStackHelper::RunIp (nodes.Get (1), Seconds (0.2), "addr add 10.1.0.10/24 dev sim1");
  LinuxStackHelper::RunIp (nodes.Get (1), Seconds (3), "addr add 10.1.1.10/24 dev sim1");

  /*Enable Multipath and debugging etc*/
  stack.SysctlSet (nodes, ".net.ipv4.conf.default.forwarding", "1");
  stack.SysctlSet (nodes, ".net.mptcp.mptcp_debug", "1");
  stack.SysctlSet (nodes, ".net.mptcp.mptcp_enabled", "1");
  stack.SysctlSet (nodes, ".net.mptcp.mptcp_path_manager", "fullmesh");
  stack.SysctlSet (nodes, ".net.ipv4.tcp_congestion_control", "olia");

  DceApplicationHelper dce;
  ApplicationContainer apps;

  dce.SetStackSize (1 << 20);

  /*Setup iPerf session*/
  std::string iperfArgs = "-c 172.16.1.1 --time 10 -i 1";
  dce.SetBinary ("iperf");
  dce.ResetArguments ();
  dce.ResetEnvironment ();
  dce.ParseArguments (iperfArgs.c_str ());
  apps = dce.Install (nodes.Get (0));
  apps.Start (Seconds (10.0));

  dce.SetBinary ("iperf");
  dce.ResetArguments ();
  dce.ResetEnvironment ();
  dce.AddArgument ("-s");
  apps = dce.Install (nodes.Get (2));
  apps.Start (Seconds (8.00));

  Config::Connect ("/NodeList/2/DeviceList/*/$ns3::PointToPointNetDevice/PhyRxEnd",
                   MakeCallback (&ReceivedBytes));

  // pointToPoint.EnablePcapAll("mptcp-address-test");

  Simulator::Stop (Seconds (stopTime));
  Simulator::Run ();
  Simulator::Destroy ();

  if (!isMptcpEnabled)
    {
      std::cout << "Probably failed? Because mptcp disabled kernel. SKIP." << std::endl;
      return;
    }

  int status = (g_rcv0 == true && g_rcv1 == true);
  NS_TEST_ASSERT_MSG_EQ (status, 1, "Process did not return successfully: " << g_testError);
}

void
DceMptcpTestCase::DoRun (void)
{
  // Disable it for a while
  // Bug 1908 - LogComponentEnable causes SIGILL with static and optimized build
  // LogComponentEnable ("PacketSink", LOG_LEVEL_INFO);
  if (m_skip)
    {
      return;
    }

  if (m_testname == "basic")
    {
      DoBasicRun ();
    }
  else if (m_testname == "addr-test")
    {
      DoAddrTestRun ();
    }

}

static class DceMptcpTestSuite : public TestSuite
{
public:
  DceMptcpTestSuite ();
private:
} g_processTests;
//


DceMptcpTestSuite::DceMptcpTestSuite ()
  : TestSuite ("dce-mptcp", UNIT)
{
  typedef struct {
    const char *name;
    const char *sockf;
    int duration;
    bool isSkip;
  } testPair;

  testPair tests[] = {
    {"basic", "ns3::LinuxTcpSocketFactory", 30, false},
    {"addr-test", "ns3::LinuxTcpSocketFactory", 30, false},
  };

  Packet::EnablePrinting ();
  // for the moment: not supported dce cradle for freebsd
  std::string filePath = SearchExecFile ("DCE_PATH", "liblinux.so", 0);
  for (unsigned int i = 0; i < sizeof(tests)/sizeof(testPair); i++)
    {
      if (filePath.length () <= 0)
        {
          tests[i].isSkip = true;
        }

      AddTestCase (new DceMptcpTestCase (tests[i].name,
                                         Seconds (tests[i].duration),
                                         tests[i].sockf,
                                         tests[i].isSkip
                                         ),
                   TestCase::QUICK);
    }
}

} // namespace ns3
