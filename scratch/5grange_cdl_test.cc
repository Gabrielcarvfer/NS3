#include "ns3/lte-helper.h"
#include "ns3/epc-helper.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/lte-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-helper.h"
#include "ns3/config-store.h"
#include <vector>
#include <bitset>
#include <sys/stat.h>
//#include "ns3/cdl-spectrum-propagation-loss.h"
#include <ns3/flow-monitor-module.h>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("5gRangeCdlScript");

uint32_t lastDlTbs = 0, lastDlMcs = 0, lastUlMcs = 0, lastUlTbs = 0;

void
RangeDlSchedulingCallback (std::string path, DlSchedulingCallbackInfo dlInfo)
{
  if (lastDlMcs != (uint32_t)dlInfo.mcsTb1 || lastDlTbs != (uint32_t)dlInfo.sizeTb1)
    {
      lastDlMcs = (uint32_t)dlInfo.mcsTb1;
      lastDlTbs = (uint32_t)dlInfo.sizeTb1;
      NS_LOG_INFO(Simulator::Now() << " DL MCS: " << (uint32_t)dlInfo.mcsTb1 << " DL TBS: " << (uint32_t)dlInfo.sizeTb1 << " bytes");
      //std::cout << Simulator::Now() << " DL MCS: " << (uint32_t)dlInfo.mcsTb1 << " DL TBS: " << (uint32_t)dlInfo.sizeTb1 << " bytes" << std::endl;
    }
}

void
StartDataframeTxCallback (std::string path, Ptr<PacketBurst> pb, std::vector<int> rbs)
{
  if (pb)
    {
      std::string str_rbs = std::to_string(rbs[0]);
      for (int i = 1; i < rbs.size(); ++i)
        {
          str_rbs = str_rbs + ", " + std::to_string (rbs[i]);
        }

      //*stream->GetStream () << Simulator::Now ().GetSeconds () << " UE Phy TX - Packets: " << pb->GetNPackets () << " Size: " << pb->GetSize () << " RBs: " << str_rbs << std::endl;

      NS_LOG_INFO(Simulator::Now() << path << " UE Phy TX - Packets: " << pb->GetNPackets () << " Size: " << pb->GetSize () << " RBs: " << str_rbs);
    }
}

void
RangeUlSchedulingCallback (std::string path, uint32_t frameNo, uint32_t subframeNo, uint16_t rnti, uint8_t mcs, uint32_t sizeTb, uint8_t componentCarrierId)
{
  if (lastUlMcs != (uint32_t)mcs || lastUlTbs != (uint32_t)sizeTb)
    {
      lastUlMcs = (uint32_t)mcs;
      lastUlTbs = (uint32_t)sizeTb;
      NS_LOG_INFO(Simulator::Now() << " UL MCS: " << (uint32_t)mcs << " UL TBS: " << sizeTb << " bytes");
    }
}

void PacketCallback(const Ptr<OutputStreamWrapper> trace_file, std::string tipo, std::string path, Ptr< const Packet > packet)
{
  //NS_LOG_INFO(Simulator::Now() << " " << path << " " << tipo << " " << packet->GetSize());
  *trace_file->GetStream () << Simulator::Now() << "," << path << "," << tipo << ",1," << packet->GetSize() << std::endl;
}

void PacketBurstCallback(const Ptr<OutputStreamWrapper> trace_file, std::string tipo, std::string path, Ptr< const PacketBurst > packet)
{
  uint32_t size = 0;
  uint32_t qtd = 0;
  if (packet)
    {
      qtd = packet->GetNPackets();
      size = packet->GetSize();
    }

    //NS_LOG_INFO(Simulator::Now() << " " << path << " " << tipo << " " << qtd << " " << size);
  *trace_file->GetStream () << Simulator::Now() << "," << path << "," << tipo << "," << qtd << "," << size << std::endl;
}

void
PacketWith2AddressesCallback(const Ptr<OutputStreamWrapper> trace_file, std::string tipo, std::string path, Ptr< const Packet > packet, const Address &address, const Address &address2)
{
  //NS_LOG_INFO(Simulator::Now() << " " << path << " " << tipo << " " << packet->GetSize());
  *trace_file->GetStream () << Simulator::Now() << "," << path << "," << tipo << ",1," << packet->GetSize() << std::endl;
}

void
PacketWithAddressCallback(const Ptr<OutputStreamWrapper> trace_file, std::string tipo, std::string path, Ptr< const Packet > packet, const Address &address)
{
  //NS_LOG_INFO(Simulator::Now() << " " << path << " " << tipo << " " << packet->GetSize());
  *trace_file->GetStream () << Simulator::Now() << "," << path << "," << tipo << ",1," << packet->GetSize() << std::endl;
}


void
PhyRxCallback (const Ptr<OutputStreamWrapper> trace_file, std::string tipo, std::string path, PhyReceptionStatParameters params)
{
  *trace_file->GetStream () << Simulator::Now() << "," << path << "," << tipo << ",RX,";
  *trace_file->GetStream () << params.m_timestamp << ",";
  *trace_file->GetStream () << (uint32_t) params.m_cellId << ",";
  *trace_file->GetStream () << params.m_imsi << ",";
  *trace_file->GetStream () << params.m_rnti << ",";
  *trace_file->GetStream () << (uint32_t) params.m_txMode << ",";
  *trace_file->GetStream () << (uint32_t) params.m_layer << ",";
  *trace_file->GetStream () << (uint32_t) params.m_mcs << ",";
  *trace_file->GetStream () << params.m_size << ",";
  *trace_file->GetStream () << (uint32_t) params.m_rv << ",";
  *trace_file->GetStream () << (uint32_t) params.m_ndi << ",";
  *trace_file->GetStream () << (uint32_t) params.m_correctness << ",";
  *trace_file->GetStream () << (uint32_t) params.m_ccId << std::endl;
}

void
PhyTxCallback (const Ptr<OutputStreamWrapper> trace_file, std::string tipo, std::string path, PhyTransmissionStatParameters params)
{
  *trace_file->GetStream () << Simulator::Now() << "," << path << "," << tipo << ",TX,";
  *trace_file->GetStream () << params.m_timestamp << ",";
  *trace_file->GetStream () << (uint32_t) params.m_cellId << ",";
  *trace_file->GetStream () << params.m_imsi << ",";
  *trace_file->GetStream () << params.m_rnti << ",";
  *trace_file->GetStream () << ","; //txmode
  *trace_file->GetStream () << (uint32_t) params.m_layer << ",";
  *trace_file->GetStream () << (uint32_t) params.m_mcs << ",";
  *trace_file->GetStream () << params.m_size << ",";
  *trace_file->GetStream () << (uint32_t) params.m_rv << ",";
  *trace_file->GetStream () << (uint32_t) params.m_ndi << ",";
  *trace_file->GetStream () << ","; //correcteness
  *trace_file->GetStream () << (uint32_t) params.m_ccId << std::endl;
}

int
main (int argc, char *argv[])
{
  NS_LOG_DEBUG (" Running 5gRangeCdlScript");

  //Scenario configuration
  double simTime              = 5;
  uint16_t numberOfNodes      = 1;//132
  uint32_t m_distance         = 50001;
  uint32_t m_packetSize       = 2000; //bytes
  double interPacketInterval  = 100;  //milliseconds
  bool sendDownlink           = true;
  bool sendUplink             = false;
  bool enableLog              = true;
  std::string data_path       = "./"; //pasta a salvar os resultados

  //LTE/5G features
  uint32_t bandwidth      = 24; //6 MHz, 8 MHz or 24 MHz (6 MHz and 8 MHz uses 4 or 3 component carriers, respectively)
  bool useErrorModel      = true;
  bool usePerfectChannel  = false;
  bool useHarq            = false;
  bool useIdealRrc        = true;
  bool useCdlPathLoss     = true;
  bool forceMaxMcsSched   = false;
  double enbTxPower       = 53.0; //dBm
  double enbGain          = 9.0;  //dBi
  double ueTxPower        = 23.0; //dBm
  double ueGain           = 9.0;  //dBi
  uint32_t dlEarfcn       = 50000; //5G: 50000, LTE: 2400 for band 5 (~850MHz)
  uint32_t ulEarfcn       = 60000; //5G: 60000, LTE: 20400 for band 5 (~850MHz)
  uint32_t dlBandwidth    = 132; //6MHz = 33 RBs, 8MHz = 44 RBs, 24MHz = 132 RBs (no CA)
  uint32_t ulBandwidth    = 132; //6MHz = 33 RBs, 8MHz = 44 RBs, 24MHz = 132 RBs (no CA)

  //Colab
  int fusionAlgorithm     = 6;
  bool enableDSA          = false; //if false, channels with PUs will be automatically flagged not to be used
  bool SNRSensing         = false; //if true, SNR based sensing curves are loaded/used instead of distance based sensing curves

  //Process command line options
  CommandLine cmd;
  cmd.AddValue("simTime", "Simulation length", simTime);
  cmd.AddValue("useErrorModel", "Enable error model", useErrorModel);
  cmd.AddValue("useCdlPathLoss", "Use CDL channel model or 5G-RANGE D3.1 channel model", useCdlPathLoss);
  cmd.AddValue("distance", "Distance in meters between UE and eNB", m_distance);
  cmd.AddValue("forceMaxMcsSched", "Force scheduler to use maximum MCS, inducing errors but reaching max throughput", forceMaxMcsSched);
  cmd.Parse (argc, argv);

  std::cout << "simTime: " << simTime << std::endl;
  std::cout << "useErrorModel: " << useErrorModel << std::endl;
  std::cout << "useCdlPathLoss: " << useCdlPathLoss << std::endl;
  std::cout << "distance: " << m_distance << std::endl;
  std::cout << "forceMaxMcsSched: " << forceMaxMcsSched << std::endl;
  m_distance+=1;

  //Print information
  bool printMcsTbs        = true;
  bool printEarfcn        = false;
  bool printRBs           = false;
  bool printAppTrace      = true;
  std::string traceAppFilename = "5grange_app_trace";

  //Trace info
  std::string pcapTraceFilename = "5grange_cdl";
  bool traceIpv4 = false;
  std::string traceRlcThroughputFilename = "5grange_rlc_throughput";
  bool traceRlcThroughput = false;
  std::string traceNetworkThrFilaname = "5grange_network_throughput";

  bool traceNetworkThr = false;
  bool tracePhy = true;
  std::string tracePhyFilename = "5grange_phy_trace";

  if (enableLog)
  {
    LogComponentEnable ("5gRangeCdlScript", (LogLevel)(LOG_PREFIX_ALL | LOG_ALL));
    //LogComponentEnable ("RrFfMacScheduler", (LogLevel)(LOG_PREFIX_ALL | LOG_ALL));
  }

  std::string trimmed_interval = std::to_string(interPacketInterval).substr(0, std::to_string(interPacketInterval).find(".") + 1 + 1);
  std::string sim_name = "5gsim_n" + std::to_string (numberOfNodes) + "_p" +std::to_string (m_packetSize) + "_i" + trimmed_interval;
  data_path += sim_name + "/";

#if defined(_WIN32)
  _mkdir(data_path.c_str());
#else
  mkdir(data_path.c_str(),0777); // notice that 777 is different than 0777
#endif


  Config::SetDefault ("ns3::ComponentCarrier::DlEarfcn", UintegerValue (dlEarfcn));
  Config::SetDefault ("ns3::ComponentCarrier::UlEarfcn", UintegerValue (ulEarfcn));
  Config::SetDefault ("ns3::ComponentCarrier::DlBandwidth", UintegerValue (dlBandwidth));
  Config::SetDefault ("ns3::ComponentCarrier::UlBandwidth", UintegerValue (ulBandwidth));

  Config::SetDefault ("ns3::LteUeNetDevice::DlEarfcn", UintegerValue (dlEarfcn));
  Config::SetDefault ("ns3::LteEnbNetDevice::DlEarfcn", UintegerValue (dlEarfcn));
  Config::SetDefault ("ns3::LteEnbNetDevice::UlEarfcn", UintegerValue (ulEarfcn));
  Config::SetDefault ("ns3::LteEnbNetDevice::DlBandwidth", UintegerValue (dlBandwidth));
  Config::SetDefault ("ns3::LteEnbNetDevice::UlBandwidth", UintegerValue (ulBandwidth));

  Config::SetDefault ("ns3::LteHelper::NumberOfComponentCarriers", UintegerValue (24/bandwidth));
  Config::SetDefault ("ns3::LteHelper::UseCa", BooleanValue (bandwidth != 24));
  Config::SetDefault ("ns3::LteHelper::EnbComponentCarrierManager", StringValue ("ns3::RrComponentCarrierManager"));


  Config::SetDefault ("ns3::LteSpectrumPhy::CtrlErrorModelEnabled", BooleanValue (false));

  if (usePerfectChannel)
  {
    Config::SetDefault ("ns3::LteSpectrumPhy::DataErrorModelEnabled", BooleanValue (false));
    Config::SetDefault ("ns3::LteAmc::PerfectChannel", BooleanValue (true));
  }

  Config::SetDefault ("ns3::LteHelper::UseIdealRrc", BooleanValue (useIdealRrc));
  //Config::SetDefault ("ns3::LteAmc::AmcModel", EnumValue (LteAmc::MiErrorModel));

  Config::SetDefault("ns3::LteEnbPhy::TxPower", DoubleValue(enbTxPower));
  Config::SetDefault("ns3::LteUePhy::TxPower" , DoubleValue(ueTxPower));

  Config::SetDefault ("ns3::LteEnbRrc::SrsPeriodicity", UintegerValue (40));
  Config::SetDefault ("ns3::LteUePhy::EnableUplinkPowerControl", BooleanValue (false));
  Config::SetDefault("ns3::LteEnbMac::SpectrumSensing", BooleanValue(false));//for whatever reason, refuses to work
  Config::SetDefault("ns3::LteSpectrumPhy::SpectrumSensing", BooleanValue(false));//for whatever reason, refuses to work
  Config::SetDefault("ns3::LteEnbMac::FusionAlgorithm", UintegerValue(fusionAlgorithm));
  LteSpectrumPhy::SNRsensing = SNRSensing;

  NodeContainer allNodes;
  Config::SetDefault ("ns3::FfMacScheduler::ForceMaxMcs", BooleanValue (forceMaxMcsSched));

  Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();
  lteHelper->SetSchedulerType ("ns3::RrFfMacScheduler");
  Config::SetDefault ("ns3::RrFfMacScheduler::HarqEnabled", BooleanValue (useHarq));
  //lteHelper->SetSchedulerType ("ns3::CqaFfMacScheduler");
  //Config::SetDefault ("ns3::CqaFfMacScheduler::HarqEnabled", BooleanValue (useHarq));

  if(useCdlPathLoss)
    {
      Config::SetDefault ("ns3::TraceFadingLossModel::RbNum", UintegerValue (dlBandwidth));
      lteHelper->SetPathlossModelType (TypeId::LookupByName ("ns3::CdlSpectrumPropagationLossModel"));
      //lteHelper->SetPathlossModelAttribute ("CdlType", EnumValue (CdlSpectrumPropagationLossModel::CDL_A));
    }
  else
    {
      Config::SetDefault("ns3::RANGE5GPropagationLossModel::Frequency", DoubleValue(869e6));
      //Config::SetDefault("ns3::RANGE5GPropagationLossModel::K-value", DoubleValue(10));
      lteHelper->SetAttribute ("PathlossModel", StringValue ("ns3::RANGE5GPropagationLossModel"));
    }

  lteHelper->SetEnbAntennaModelAttribute ("Gain",     DoubleValue (enbGain));
  lteHelper->SetUeAntennaModelAttribute  ("Gain",     DoubleValue (ueGain));

  Ptr<PointToPointEpcHelper>  epcHelper = CreateObject<PointToPointEpcHelper> ();
  lteHelper->SetEpcHelper (epcHelper);
  Ptr<Node> pgw = epcHelper->GetPgwNode ();
  allNodes.Add(pgw);

  // Create a single RemoteHost
  NodeContainer remoteHostContainer;
  remoteHostContainer.Create (1);
  allNodes.Add(remoteHostContainer);
  Ptr<Node> remoteHost = remoteHostContainer.Get (0);

  NodeContainer ueNodes, enbNodes;
  enbNodes.Create(1);
  ueNodes.Create(numberOfNodes);
  allNodes.Add(enbNodes);

  // Install Mobility Model
  Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
  positionAlloc->Add (Vector(10, 0, 0)); // PGw
  positionAlloc->Add (Vector(0, 0, 0));  // Internet
  positionAlloc->Add (Vector(50000.0, 50000.0, 0));  // eNB

  //UE nodes
  Ptr<ListPositionAllocator> positionAlloc2 = CreateObject<ListPositionAllocator> ();
  for (uint16_t i = 0; i < numberOfNodes; i++)
    {
      positionAlloc2->Add (Vector(50000.0, 50000.0 + m_distance, 0));
    }

  MobilityHelper mobility;
  mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
  mobility.SetPositionAllocator(positionAlloc);
  mobility.Install(allNodes);

  mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
  mobility.SetPositionAllocator(positionAlloc2);
  mobility.Install(ueNodes);

  allNodes.Add(ueNodes);

  InternetStackHelper internet;
  internet.Install (remoteHostContainer);

  // Create the Internet
  PointToPointHelper p2ph;
  p2ph.SetDeviceAttribute ("DataRate", DataRateValue (DataRate ("100Gb/s")));
  p2ph.SetDeviceAttribute ("Mtu", UintegerValue (15000));
  p2ph.SetChannelAttribute ("Delay", TimeValue (Seconds (0.010)));
  NetDeviceContainer internetDevices = p2ph.Install (pgw, remoteHost);

  Ipv4AddressHelper ipv4h;
  ipv4h.SetBase ("1.0.0.0", "255.0.0.0");
  Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign (internetDevices);

  // interface 0 is localhost, 1 is the p2p device
  Ipv4Address remoteHostAddr = internetIpIfaces.GetAddress (1);

  Ipv4StaticRoutingHelper ipv4RoutingHelper;
  Ptr<Ipv4StaticRouting> remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting (remoteHost->GetObject<Ipv4> ());
  remoteHostStaticRouting->AddNetworkRouteTo (Ipv4Address ("7.0.0.0"), Ipv4Mask ("255.0.0.0"), 1);


  // Install LTE Devices to the nodes
  NetDeviceContainer enbLteDevs = lteHelper->InstallEnbDevice (enbNodes);
  NetDeviceContainer ueLteDevs = lteHelper->InstallUeDevice (ueNodes);

  // Install the IP stack on the UEs
  internet.Install (ueNodes);
  Ipv4InterfaceContainer ueIpIface;
  ueIpIface = epcHelper->AssignUeIpv4Address (NetDeviceContainer (ueLteDevs));
  // Assign IP address to UEs, and install applications
  for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
    {
      Ptr<Node> ueNode = ueNodes.Get (u);
      Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting (ueNode->GetObject<Ipv4> ());
      ueStaticRouting->SetDefaultRoute (epcHelper->GetUeDefaultGatewayAddress (), 1);
    }

  lteHelper->Attach (ueLteDevs, enbLteDevs.Get(0));

  uint16_t dlPort = 1234;
  uint16_t ulPort = 2000;
  ApplicationContainer clientApps;
  ApplicationContainer serverApps;

  for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
    {
      ++ulPort;
      if (sendDownlink)
        {
          //UE receives
          PacketSinkHelper dlPacketSinkHelper ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), dlPort));
          serverApps.Add (dlPacketSinkHelper.Install (ueNodes.Get(u)));

          //From remoteHost
          UdpClientHelper dlClient (ueIpIface.GetAddress (u), dlPort);
          dlClient.SetAttribute ("Interval", TimeValue (MicroSeconds(interPacketInterval)));
          dlClient.SetAttribute ("PacketSize", UintegerValue (m_packetSize));
          dlClient.SetAttribute ("MaxPackets", UintegerValue(1000000));
          clientApps.Add (dlClient.Install (remoteHost));
        }

      if (sendUplink)
        {
          //RemoteHost receives
          PacketSinkHelper ulPacketSinkHelper ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), ulPort));
          serverApps.Add (ulPacketSinkHelper.Install (remoteHost));

          //From UEs
          UdpClientHelper ulClient (remoteHostAddr, ulPort);
          ulClient.SetAttribute ("Interval", TimeValue (MicroSeconds(interPacketInterval)));
          ulClient.SetAttribute ("PacketSize", UintegerValue (m_packetSize));
          ulClient.SetAttribute ("MaxPackets", UintegerValue(1000000));
          clientApps.Add (ulClient.Install (ueNodes.Get(u)));
        }
    }

  serverApps.Start(Seconds (0.9));
  clientApps.Start(Seconds (1.0));
  clientApps.Stop(Seconds (simTime + 1.0));
  serverApps.Stop(Seconds (simTime + 1.1));

  lteHelper->EnableTraces ();

  Ptr<FlowMonitor> flowMonitor;
  FlowMonitorHelper flowHelper;
  flowMonitor = flowHelper.InstallAll();

  Ptr<RadioBearerStatsCalculator> rlcStats = lteHelper->GetRlcStats ();
  Ptr<RadioBearerStatsCalculator> pdcpStats = lteHelper->GetPdcpStats ();

  rlcStats->SetDlOutputFilename (data_path + "rlc_stats_dl.txt");
  rlcStats->SetUlOutputFilename (data_path + "rlc_stats_ul.txt");
  pdcpStats->SetDlPdcpOutputFilename (data_path + "pdcp_stats_dl.txt");
  pdcpStats->SetUlPdcpOutputFilename (data_path + "pdcp_stats_ul.txt");



  //Print Node ids
  std::vector<uint32_t> ueIds, enbIds;
  uint32_t  pgwId = pgw->GetId(), remoteHostId = remoteHost->GetId();
  NS_LOG_INFO("NODE IDs");
  NS_LOG_INFO("\tPGW: " << pgwId);
  NS_LOG_INFO("\tremoteHost: " << remoteHostId);
  NS_LOG_INFO("\teNB: ");
  for (int i = 0; i < enbNodes.GetN(); ++i)
    {
      enbIds.push_back(enbNodes.Get(i)->GetId());
      NS_LOG_INFO("\t\t eNB " << i << ": " << enbNodes.Get(i)->GetId());
    }
  NS_LOG_INFO("\tUEs: " << pgw->GetId());
  for (int i = 0; i < ueNodes.GetN(); ++i)
    {
      ueIds.push_back(ueNodes.Get(i)->GetId());
      NS_LOG_INFO("\t\t UE " << i << ": " << ueNodes.Get(i)->GetId());
    }

  //Print TBS and MCS for each subframe
  if (printMcsTbs)
    {
      Config::Connect ("/NodeList/*/DeviceList/*/$ns3::LteEnbNetDevice/LteEnbMac/DlScheduling", MakeCallback (&RangeDlSchedulingCallback));
      Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbMac/DlScheduling", MakeCallback (&RangeDlSchedulingCallback));
      //Config::Connect ("/NodeList/" + std::to_string(enbIds[0]) + "/DeviceList/0/$ns3::LteEnbNetDevice/LteEnbMac/DlScheduling", MakeCallback (&RangeDlSchedulingCallback));
      //Config::Connect ("/NodeList/" + std::to_string(enbIds[0]) + "/DeviceList/0/ComponentCarrierMap/*/LteEnbMac/DlScheduling", MakeCallback (&RangeDlSchedulingCallback));
      //Config::Connect ("/NodeList/" + std::to_string(enbIds[0]) + "/DeviceList/0/ComponentCarrierMap/*/LteEnbMac/UlScheduling",  MakeCallback (&RangeUlSchedulingCallback));
    }

  //Print RBs
  if (printRBs)
    {
      //Config::Connect ("/NodeList/2/DeviceList/" + std::to_string(enbIds[0]) + "/$ns3::LteEnbNetDevice/ComponentCarrierMap/*/FfMacScheduler/$ns3::PfFfMacScheduler/RBBitmapTrace",  MakeCallback (&RbBitmapTrace));

      //UE (Uplink)
      Config::Connect ("/NodeList/*/DeviceList/*/$ns3::LteUeNetDevice/ComponentCarrierMapUe/*/LteUePhy/StartTxDataframe", MakeCallback (&StartDataframeTxCallback));

      //eNB (Downlink)
      Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbPhy/StartTxDataframe", MakeCallback (&StartDataframeTxCallback));
    }

  if (tracePhy)
    {
      AsciiTraceHelper phy_ascii_trace;
      Ptr<OutputStreamWrapper> phy_trace = phy_ascii_trace.CreateFileStream (data_path + tracePhyFilename+ ".txt");
      Ptr<OutputStreamWrapper> phy_trace_lte = phy_ascii_trace.CreateFileStream (data_path + tracePhyFilename+ "_lte.txt");
      *phy_trace->GetStream() << "time,path,node,channel,rxtx,status,qtd_pkts,size" << std::endl;
      *phy_trace_lte->GetStream() << "time,path,node,channel,rxtx,% time,cellId,IMSI,RNTI,txMode,layer,mcs,size,rv,ndi,correct,ccId" << std::endl;

      //eNB
      Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbPhy/DlSpectrumPhy/RxEndOk", MakeBoundCallback (&PacketCallback, phy_trace, "ENB,DL,RX,OK"));
      Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbPhy/DlSpectrumPhy/RxEndError", MakeBoundCallback (&PacketCallback, phy_trace, "ENB,DL,RX,ERROR"));
      Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbPhy/DlSpectrumPhy/TxEnd", MakeBoundCallback (&PacketBurstCallback, phy_trace, "ENB,DL,TX,OK"));
      Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbPhy/UlSpectrumPhy/RxEndOk", MakeBoundCallback (&PacketCallback, phy_trace, "ENB,UL,RX,OK"));
      Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbPhy/UlSpectrumPhy/RxEndError", MakeBoundCallback (&PacketCallback, phy_trace, "ENB,UL,RX,ERROR"));
      Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbPhy/UlSpectrumPhy/TxEnd", MakeBoundCallback (&PacketBurstCallback, phy_trace, "ENB,UL,TX,OK"));
      Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbPhy/UlSpectrumPhy/UlPhyReception", MakeBoundCallback (&PhyRxCallback, phy_trace_lte, "ENB,UL"));
      Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbPhy/DlSpectrumPhy/DlPhyReception", MakeBoundCallback (&PhyRxCallback, phy_trace_lte, "ENB,DL"));
      Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbPhy/DlPhyTransmission", MakeBoundCallback (&PhyTxCallback, phy_trace_lte, "ENB,DL"));

      //UE
      Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMapUe/*/LteUePhy/DlSpectrumPhy/RxEndOk", MakeBoundCallback (&PacketCallback, phy_trace, "UE,DL,RX,OK"));
      Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMapUe/*/LteUePhy/DlSpectrumPhy/RxEndError", MakeBoundCallback (&PacketCallback, phy_trace, "UE,DL,RX,ERROR"));
      Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMapUe/*/LteUePhy/DlSpectrumPhy/TxEnd", MakeBoundCallback (&PacketBurstCallback, phy_trace, "UE,DL,TX,OK"));
      Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMapUe/*/LteUePhy/UlSpectrumPhy/RxEndOk", MakeBoundCallback (&PacketCallback, phy_trace, "UE,UL,RX,OK"));
      Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMapUe/*/LteUePhy/UlSpectrumPhy/RxEndError", MakeBoundCallback (&PacketCallback, phy_trace, "UE,UL,RX,ERROR"));
      Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMapUe/*/LteUePhy/UlSpectrumPhy/TxEnd", MakeBoundCallback (&PacketBurstCallback, phy_trace, "UE,UL,TX,OK"));
      Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMapUe/*/LteUePhy/DlSpectrumPhy/DlPhyReception", MakeBoundCallback (&PhyRxCallback, phy_trace_lte, "UE,DL"));
      Config::Connect ("/NodeList/*/DeviceList/*/ComponentCarrierMapUe/*/LteUePhy/UlPhyTransmission", MakeBoundCallback (&PhyTxCallback, phy_trace_lte, "UE,UL"));

      //RemoteHost e PGW p2p interface
      //p2ph.EnableAsciiAll("5grange_p2p_trace.txt");
      AsciiTraceHelper p2p_asciihelper;
      Ptr<OutputStreamWrapper> ascii_enb = p2p_asciihelper.CreateFileStream (data_path + "p2p_ascii_enb.txt");
      Ptr<OutputStreamWrapper> ascii_remote = p2p_asciihelper.CreateFileStream (data_path + "p2p_ascii_remote.txt");
      p2ph.EnableAscii(ascii_enb, enbIds[0], 2);
      p2ph.EnableAscii(ascii_remote, remoteHostId, 1);
    }

  //Print app trace
  if (printAppTrace)
    {
      AsciiTraceHelper app_ascii_trace;
      Ptr<OutputStreamWrapper> app_trace = app_ascii_trace.CreateFileStream (data_path + traceAppFilename + ".txt");
      *app_trace->GetStream() << "time,path,node,channel,rxtx,status,qtd_pkts,size" << std::endl;
      //RemoteHost
      //Config::Connect ("/NodeList/" + std::to_string(remoteHostId) + "/ApplicationList/0/$ns3::UdpEchoServer/RxWithAddresses", MakeBoundCallback (&PacketWithAddressCallback, app_trace, "RH -- TX OK"));
      for (int i = 0; i < ueIds.size(); i++)
        {
          //Recebido pelo UE
          Config::Connect ("/NodeList/" + std::to_string(ueIds[i]) + "/ApplicationList/0/$ns3::PacketSink/Rx", MakeBoundCallback (&PacketWithAddressCallback, app_trace, "UE,--,RX,OK"));
        }

      //Recebido pelo eNB, do remoteHost
      //Config::Connect ("/NodeList/" + std::to_string(enbIds[0]) + "/DeviceList/2/$ns3::PointToPointNetDevice/MacRx", MakeCallback (&PacketCallback));
    }

  //Trace Pcap
  if (traceIpv4)
    {
      internet.EnableAsciiIpv4All (data_path + pcapTraceFilename);
    }

  //Print Earfcn
  if (printEarfcn)
    {
      Ptr<LteEnbNetDevice> eNbDev = enbLteDevs.Get (0)->GetObject<LteEnbNetDevice> ();
      NS_LOG_INFO("eNB DL Earfcn: " << eNbDev->GetDlEarfcn () << " DL Carrier Frequency: " << LteSpectrumValueHelper::GetDownlinkCarrierFrequency (eNbDev->GetDlEarfcn ()) << " DL Band: " << (uint16_t)LteSpectrumValueHelper::GetDownlinkCarrierBand (eNbDev->GetDlEarfcn ()));
      NS_LOG_INFO("eNB DL Bandwidth: " << (int)eNbDev->GetDlBandwidth ());
      NS_LOG_INFO("eNB UL Earfcn: " << eNbDev->GetUlEarfcn () << " UL Carrier Frequency: " << LteSpectrumValueHelper::GetUplinkCarrierFrequency (eNbDev->GetUlEarfcn ()) << " UL Band: " << (uint16_t)LteSpectrumValueHelper::GetUplinkCarrierBand (eNbDev->GetUlEarfcn ()));
      NS_LOG_INFO("eNB UL Bandwidth: " << (int)eNbDev->GetUlBandwidth ());
    }

  Simulator::Stop(Seconds(simTime + 2));
  Simulator::Run();

  if (traceRlcThroughput)
    {
      AsciiTraceHelper ascii_helper;
      Ptr<OutputStreamWrapper> rlc_output_dl = ascii_helper.CreateFileStream (data_path + traceRlcThroughputFilename+ "_dl.txt");

      NS_LOG_INFO("Simulation parameters:");
      NS_LOG_INFO("\t - Nodes: " << numberOfNodes);
      NS_LOG_INFO("\t - Packet size: " << m_packetSize << " bytes");
      NS_LOG_INFO("\t - Period: " << interPacketInterval << " ms");
      NS_LOG_INFO ("\t - Maximum theoretical throughput: " << (1000/4.6) * (2292) * 132/10e6 << " mbps");
      NS_LOG_INFO("DOWNLINK THROUGHPUT");
      std::vector <uint64_t> dlDataRxed;
      double epochDuration = rlcStats->GetEpoch().GetSeconds();
      double totalDlThr = 0.0;
      for (int i = 0; i < numberOfNodes; i++)
        {
          uint64_t imsi = ueLteDevs.Get (i)->GetObject<LteUeNetDevice> ()->GetImsi ();
          uint8_t lcId = 3;
          dlDataRxed.push_back (rlcStats->GetDlRxData (imsi, lcId));
          totalDlThr+=(double)dlDataRxed.at (i) / epochDuration;
          *rlc_output_dl->GetStream () << Simulator::Now().GetNanoSeconds () << "\t" << i << "\t" << (double)dlDataRxed.at (i) / epochDuration << "\t" << (m_packetSize + 32) * (1000/interPacketInterval) << std::endl;
          NS_LOG_INFO ("\tUE " << i << " imsi " << imsi << " bytes rxed " << (double)dlDataRxed.at (i) / epochDuration << " expected " << (m_packetSize + 32) * (1000/interPacketInterval) );
        }

      if (traceNetworkThr)
        {
          Ptr<OutputStreamWrapper> net_output_dl = ascii_helper.CreateFileStream (data_path + traceNetworkThrFilaname + "_dl.txt");
          double net_real = numberOfNodes*(m_packetSize + 32) * 8 / interPacketInterval / 1000;
          *net_output_dl->GetStream ()  << interPacketInterval << "\t" << numberOfNodes << "\t" << m_packetSize << "\t" << totalDlThr*8 / 1000 / 1000 << "\t" <<  net_real << std::endl;
        }

      NS_LOG_INFO ("\t Expected: " << numberOfNodes*(m_packetSize + 32) * 8 / interPacketInterval / 1000 << " mbps");
      NS_LOG_INFO ("\t Achieved: " << totalDlThr*8 / 1000 / 1000 << " mbps");


      Ptr<OutputStreamWrapper> rlc_output_up = ascii_helper.CreateFileStream (data_path + traceRlcThroughputFilename+ "_up.txt");

      NS_LOG_INFO ("UPLINK THROUGHPUT");
      std::vector <uint64_t> ulDataRxed;
      double totalUlThr = 0.0;
      for (int i = 0; i < numberOfNodes; i++)
        {
          uint64_t imsi = ueLteDevs.Get (i)->GetObject<LteUeNetDevice> ()->GetImsi ();
          uint8_t lcId = 3;
          ulDataRxed.push_back (rlcStats->GetUlRxData (imsi, lcId));
          totalUlThr+=(double)ulDataRxed.at (i) / epochDuration;

          *rlc_output_up->GetStream () << Simulator::Now().GetNanoSeconds () << "\t" << i << "\t" << (double)ulDataRxed.at (i) / epochDuration << "\t" << (m_packetSize + 32) * (1000/interPacketInterval) << std::endl;
          NS_LOG_INFO ("\tUE " << i << " imsi " << imsi << " bytes rxed " << (double)ulDataRxed.at (i) / epochDuration << " expected " << (m_packetSize + 32) * (1000/interPacketInterval) );
        }

      if (traceNetworkThr)
        {
          Ptr<OutputStreamWrapper> net_output_ul = ascii_helper.CreateFileStream (data_path + traceNetworkThrFilaname + "_ul.txt");
          *net_output_ul->GetStream () << interPacketInterval << "\t" << numberOfNodes << "\t" << m_packetSize << "\t" << totalUlThr*8 / 1000 / 1000 << "\t" <<  numberOfNodes*(m_packetSize + 32) * 8 / interPacketInterval / 1000 << std::endl;
        }

      NS_LOG_INFO ("\t Expected: " << numberOfNodes*(m_packetSize + 32) * 8 /interPacketInterval / 1000 << " mbps");
      NS_LOG_INFO ("\t Achieved: " << totalUlThr*8 / 1000 / 1000 << " mbps");
    }

  flowMonitor->SerializeToXmlFile("flow.xml", true, true);
  Simulator::Destroy();
  return 0;

}