//
// Created by Gabriel Ferreira(@gabrielcarvfer) on 1/11/22.
//

#include <map>
#include <string>

#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/lte-module.h"
#include "ns3/mobility-module.h"
#include "ns3/netanim-module.h"
#include "ns3/point-to-point-module.h"

#include "ns3/E2AP.h"
#include "ns3/xAppHandoverMaxRsrq.h"

#include "ns3/xAppHandoverMlpackKmeans.h"
#include <mlpack/prereqs.hpp>
#include <mlpack/core.hpp>
#include <mlpack/methods/kmeans/kmeans.hpp>

NS_LOG_COMPONENT_DEFINE("HandoverXappsScenario");

using namespace ns3;

class Registry
{
public:
  enum registerType{
      HANDOVER_CANCELLED_RIC = 0,
      HANDOVER_TRIGGERED_ENB,
      HANDOVER_START_ENB,
      HANDOVER_OK_ENB,
      HANDOVER_START_UE,
      HANDOVER_OK_UE,
      HANDOVER_ERROR_UE,
      CONNECTION_RECONFIGURATION_ENB,
      CONNECTION_ESTABLISHED_ENB,
      CONNECTION_ERROR_ENB,
      CONNECTION_START_UE,
      CONNECTION_ESTABLISHED_UE,
      CONNECTION_ERROR_UE,
  };
    static inline std::map<enum registerType, std::string> registerTypeStr = {
        {HANDOVER_CANCELLED_RIC,"HANDOVER_CANCELLED_RIC"},
        {HANDOVER_TRIGGERED_ENB, "HANDOVER_TRIGGERED_ENB"},
        {HANDOVER_START_ENB,"HANDOVER_START_ENB"},
        {HANDOVER_OK_ENB,"HANDOVER_OK_ENB"},
        {HANDOVER_START_UE,"HANDOVER_START_UE"},
        {HANDOVER_OK_UE,"HANDOVER_OK_UE"},
        {HANDOVER_ERROR_UE,"HANDOVER_ERROR_UE"},
        {CONNECTION_RECONFIGURATION_ENB,"CONNECTION_RECONFIGURATION_ENB"},
        {CONNECTION_ESTABLISHED_ENB,"CONNECTION_ESTABLISHED_ENB"},
        {CONNECTION_ERROR_ENB,"CONNECTION_ERROR_ENB"},
        {CONNECTION_START_UE,"CONNECTION_START_UE"},
        {CONNECTION_ESTABLISHED_UE,"CONNECTION_ESTABLISHED_UE"},
        {CONNECTION_ERROR_UE,"CONNECTION_ERROR_UE"},
    };
  Registry(uint64_t imsi, uint16_t cellId, uint16_t rnti, uint16_t trgtCellId, enum registerType type):
        m_timestamp(Simulator::Now()),
        m_imsi(imsi),
        m_srcCellId(cellId),
        m_rnti(rnti),
        m_trgtCellId(trgtCellId),
        m_type(type)
  {}
  friend std::ostream& operator<<(std::ostream& os, const Registry& dt);

  private:
    Time m_timestamp;
    uint64_t m_imsi;
    uint16_t m_srcCellId;
    uint16_t m_rnti;
    uint16_t m_trgtCellId;
    enum registerType m_type;
};

std::ostream& operator<<(std::ostream& os, const Registry& registry)
{
    os << registry.m_timestamp.GetNanoSeconds() << ","
       << registry.m_imsi << ","
       << registry.m_srcCellId << ","
       << registry.m_rnti << ","
       << registry.m_trgtCellId << ","
       << Registry::registerTypeStr.at(registry.m_type) << ",";
    return os;
}

std::vector<Registry> simulationRegistry;


void
NotifyConnectionEstablishedUe (std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti)
{
  std::cout << context << " UE IMSI " << imsi << ": connected to CellId " << cellid
            << " with RNTI " << rnti << std::endl;
  simulationRegistry.emplace_back(imsi, cellid, rnti, cellid, Registry::CONNECTION_ESTABLISHED_UE);
}


void
NotifyHandoverStartUe (std::string context,
                       uint64_t imsi,
                       uint16_t cellid,
                       uint16_t rnti,
                       uint16_t targetCellId)
{
  std::cout << context << " UE IMSI " << imsi << ": previously connected to CellId " << cellid
            << " with RNTI " << rnti << ", doing handover to CellId " << targetCellId
            << std::endl;
  simulationRegistry.emplace_back(imsi, cellid, rnti, targetCellId, Registry::HANDOVER_START_UE);
}

void
NotifyHandoverEndOkUe (std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti)
{
  std::cout << context << " UE IMSI " << imsi << ": successful handover to CellId " << cellid
            << " with RNTI " << rnti << std::endl;
  simulationRegistry.emplace_back(imsi, cellid, rnti, cellid, Registry::HANDOVER_OK_UE);

}

void
NotifyConnectionEstablishedEnb (std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti)
{
  std::cout << context << " eNB CellId " << cellid << ": successful connection of UE with IMSI "
            << imsi << " RNTI " << rnti << std::endl;
  simulationRegistry.emplace_back(imsi, cellid, rnti, cellid, Registry::CONNECTION_ESTABLISHED_ENB);
}

void
NotifyConnectionReconfigurationEnb (std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti)
{
    std::cout << context << " UE IMSI " << imsi << ": requires a reconfiguration to CellId " << cellid
              << " with RNTI " << rnti << std::endl;
    simulationRegistry.emplace_back(imsi, cellid, rnti, cellid, Registry::CONNECTION_RECONFIGURATION_ENB);
}

void
NotifyHandoverStartEnb (std::string context,
                        uint64_t imsi,
                        uint16_t cellid,
                        uint16_t rnti,
                        uint16_t targetCellId)
{
  std::cout << context << " eNB CellId " << cellid << ": start handover of UE with IMSI " << imsi
            << " RNTI " << rnti << " to CellId " << targetCellId << std::endl;
  simulationRegistry.emplace_back(imsi, cellid, rnti, targetCellId, Registry::HANDOVER_START_ENB);

}


void
NotifyHandoverCancelledEnb (std::string context,
                            uint64_t imsi,
                            uint16_t cellid,
                            uint16_t rnti,
                            uint16_t targetCellId)
{
    std::cout << context << " eNB CellId " << cellid << ": RIC cancelled handover of UE with IMSI " << imsi
              << " RNTI " << rnti << " to CellId " << targetCellId << std::endl;
    simulationRegistry.emplace_back(imsi, cellid, rnti, targetCellId, Registry::HANDOVER_CANCELLED_RIC);
}

void
NotifyHandoverTriggeredEnb (std::string context,
                            uint64_t imsi,
                            uint16_t cellid,
                            uint16_t rnti,
                            uint16_t targetCellId)
{
    std::cout << context << " eNB CellId " << cellid << ": handover triggered RIC handover control of UE with IMSI " << imsi
              << " RNTI " << rnti << " to CellId " << targetCellId << std::endl;
    simulationRegistry.emplace_back(imsi, cellid, rnti, targetCellId, Registry::HANDOVER_TRIGGERED_ENB);

}

void
NotifyHandoverEndOkEnb (std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti)
{
  std::cout << context << " eNB CellId " << cellid << ": completed handover of UE with IMSI "
            << imsi << " RNTI " << rnti << std::endl;
  simulationRegistry.emplace_back(imsi, cellid, rnti, cellid, Registry::HANDOVER_OK_ENB);
}

void
NotifyHandoverEndErrorUe (std::string context, uint64_t imsi, uint16_t cellid, uint16_t rnti)
{
    std::cout << context << " eNB CellId " << cellid << ": completed handover of UE with IMSI "
              << imsi << " RNTI " << rnti << std::endl;
    simulationRegistry.emplace_back(imsi, cellid, rnti, cellid, Registry::HANDOVER_ERROR_UE);
}

unsigned int good_seed()
{
    unsigned int random_seed, random_seed_a, random_seed_b;
    std::ifstream file ("/dev/urandom", std::ios::binary);
    if (file.is_open())
    {
      char * memblock;
      int size = sizeof(int);
      memblock = new char [size];
      file.read (memblock, size);
      file.close();
      random_seed_a = *reinterpret_cast<int*>(memblock);
      delete[] memblock;
    }// end if
    else
    {
      random_seed_a = 0;
    }
    random_seed_b = std::time(0);
    random_seed = random_seed_a xor random_seed_b;
    return random_seed;
} // end good_seed()

int main (int argc, char** argv)
{

  ns3::RngSeedManager::SetSeed(good_seed());
  std::cout << "Seed " << ns3::RngSeedManager::GetSeed() << std::endl;

  // Testes de conexão de nós
  GlobalValue::Bind ("ChecksumEnabled", BooleanValue (true));

  uint16_t numberOfUes = 6;
  uint16_t numberOfEnbs = 3;
  uint16_t numBearersPerUe = 1;
  double simTime = 10*60;
  double enbTxPowerDbm = 40.0;


  std::stringstream ss;
  ss << "\n\t\tChoose one:\n"
     << "\t 0: Standard 3GPP handover (HO)\n"
     << "\t 1: ORAN HO returns the decision taken by the eNB. HO initiated by the eNB.\n"
     << "\t 2: ORAN HO calls the Kmeans xApp to make a decision. HO initiated by the eNB.\n"
     << "\t 3: ORAN HO calls the Kmeans xApp to make a decision. HO initiated by the RIC/xApp.\n";

  unsigned scenarioi = 0;
  std::string output_csv_filename="output.csv";
  CommandLine cmd(__FILE__);
  cmd.AddValue("scenario",
               ss.str(),
               scenarioi);
  cmd.AddValue("outputFile", "Output csv file name", output_csv_filename);
  cmd.Parse(argc, argv);

  typedef enum handoverScenarios{
      STANDARD_3GPP=0,
      ORAN_BYPASS, // RIC just forwards back decision taken by the eNB
      ORAN_RIC_XAPP_KMEANS, // RIC calls the xAPP to decide whether to follow the eNB suggestion or not
      ORAN_RIC_XAPP_KMEANS_INITIATED, // eNB stops triggering handovers and just follows RIC handover commands
      ORAN_RIC_XAPP_MAXRSRQ, // RIC calls the xAPP to decide whether to follow the eNB suggestion or not
      ORAN_RIC_XAPP_MAXRSRQ_INITIATED,
  }HandoverScenarios;

  if (scenarioi > HandoverScenarios::ORAN_RIC_XAPP_MAXRSRQ_INITIATED)
  {
      std::cerr << "Invalid handover scenario id: " << scenarioi << std::endl;
      return -1;
  }
  HandoverScenarios scenario = static_cast<HandoverScenarios>(scenarioi);

  // change some default attributes so that they are reasonable for
  // this scenario, but do this before processing command line
  // arguments, so that the user is allowed to override these setting
  Config::SetDefault ("ns3::LteHelper::UseIdealRrc", BooleanValue (true));

  Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();
  Ptr<PointToPointEpcHelper> epcHelper = CreateObject<PointToPointEpcHelper> ();
  epcHelper->SetAttribute ("S1uLinkEnablePcap", BooleanValue (false));
  lteHelper->SetEpcHelper (epcHelper);
  lteHelper->SetSchedulerType ("ns3::RrFfMacScheduler");

  switch (scenario)
  {
      // all _INITIATED scenarios should be addded here
      case HandoverScenarios::ORAN_RIC_XAPP_KMEANS_INITIATED:
      case HandoverScenarios::ORAN_RIC_XAPP_MAXRSRQ_INITIATED:
          lteHelper->SetHandoverAlgorithmType(
              "ns3::NoOpHandoverAlgorithm"); // algorithm needs to manually trigger handovers
          break;
      default:
          // Generates too many requests when cancelled by the RIC
          lteHelper->SetHandoverAlgorithmType("ns3::A2A4RsrqHandoverAlgorithm");
          lteHelper->SetHandoverAlgorithmAttribute("ServingCellThreshold", UintegerValue(30));
          lteHelper->SetHandoverAlgorithmAttribute("NeighbourCellOffset", UintegerValue(1));

          // The other alternative
          //lteHelper->SetHandoverAlgorithmType ("ns3::A3RsrpHandoverAlgorithm");
          //lteHelper->SetHandoverAlgorithmAttribute ("Hysteresis",
          //                                          DoubleValue (3.0));
          //lteHelper->SetHandoverAlgorithmAttribute ("TimeToTrigger",
          //                                          TimeValue (MilliSeconds (256)));
          break;
  }

  Ptr<Node> pgw = epcHelper->GetPgwNode ();
  Ptr<Node> sgw = epcHelper->GetSgwNode ();

  // Create a single RemoteHost
  NodeContainer remoteHostContainer;
  remoteHostContainer.Create (1);
  Ptr<Node> remoteHost = remoteHostContainer.Get (0);
  InternetStackHelper internet;
  internet.Install (remoteHostContainer);

  // Create the Internet
  PointToPointHelper p2ph;
  p2ph.SetDeviceAttribute ("DataRate", DataRateValue (DataRate ("100Gb/s")));
  p2ph.SetDeviceAttribute ("Mtu", UintegerValue (1500));
  p2ph.SetChannelAttribute ("Delay", TimeValue (Seconds (0.010)));
  NetDeviceContainer internetDevices = p2ph.Install (pgw, remoteHost);
  Ipv4AddressHelper ipv4h;
  ipv4h.SetBase ("1.0.0.0", "255.0.0.0");
  Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign (internetDevices);
  Ipv4Address remoteHostAddr = internetIpIfaces.GetAddress (1);

  // Routing of the Internet Host (towards the LTE network)
  Ipv4StaticRoutingHelper ipv4RoutingHelper;
  Ptr<Ipv4StaticRouting> remoteHostStaticRouting =
      ipv4RoutingHelper.GetStaticRouting (remoteHost->GetObject<Ipv4> ());
  // interface 0 is localhost, 1 is the p2p device
  remoteHostStaticRouting->AddNetworkRouteTo (Ipv4Address ("7.0.0.0"), Ipv4Mask ("255.0.0.0"), 1);


  // Set the position of EPC e remote internet nodes
  NodeContainer backHaulNodes;
  backHaulNodes.Add(remoteHostContainer.Get(0));
  backHaulNodes.Add(pgw);
  backHaulNodes.Add(sgw);
  Ptr<Node> mme = NodeList::GetNode(2);
  backHaulNodes.Add(mme);

  Ptr<ListPositionAllocator> backHaulPositionAlloc = CreateObject<ListPositionAllocator> ();
  backHaulPositionAlloc->Add (Vector(200, 1000, 0));
  backHaulPositionAlloc->Add (Vector(200, 750, 0));
  backHaulPositionAlloc->Add (Vector(200, 500, 0));
  backHaulPositionAlloc->Add (Vector(200, 250, 0));

  MobilityHelper backHaulMobility;
  backHaulMobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  backHaulMobility.SetPositionAllocator (backHaulPositionAlloc);
  backHaulMobility.Install (backHaulNodes);

  NodeContainer ueNodes;
  NodeContainer enbNodes;
  enbNodes.Create (numberOfEnbs);
  ueNodes.Create (numberOfUes);

  // Install Mobility Model in eNB
  Ptr<ListPositionAllocator> enbPositionAlloc = CreateObject<ListPositionAllocator> ();
  enbPositionAlloc->Add (Vector(1000, 1000, 0));
  enbPositionAlloc->Add (Vector(2000, 1000, 0));
  enbPositionAlloc->Add (Vector(1500, 1866, 0));

  MobilityHelper enbMobility;
  enbMobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  enbMobility.SetPositionAllocator (enbPositionAlloc);
  enbMobility.Install (enbNodes);

  // Install Mobility Model in UE
  MobilityHelper ueMobility;
  ueMobility.SetMobilityModel ("ns3::WaypointMobilityModel");
  ueMobility.Install (ueNodes);

  double sin60 = std::sin(3.1415*60/180);
  double cos60 = std::cos(3.1415*60/180);

  std::vector<double> speedUes {0.2, 1, 5, 10, 5, 30};
  for (int i = 0; i < numberOfUes; i++)
    {
        // UEs in the intersection of the 2/3 cells
        /*
         * 1000,1250 ► 1750,1250
         *     UE ______
         *        \    /
         *    ▲    \  /   ▼
         *          \/
         *     1500, 1683
         */
        double InitPosX = 1250;
        double InitPosY = 1250;
        double PosX = InitPosX;
        double PosY = InitPosY;
        double MidX = 1500;
        double LimX = 1750; // walks 500 from the starting point
        double LimY = 1250+500*sin60;//initPosY+triangleSide*sin(angle) = 1683;

        if (i >=4)
        {
            // These UEs fly outside the cells
            InitPosX = 500;
            InitPosY = 750;
            PosX = InitPosX;
            PosY = InitPosY;
            LimX = 2500;
            LimY = 750+2000*sin60;
        }

        enum direction{
            TOP_RIGHT=0,
            BOTTOM_MID,
            TOP_LEFT
        };
        enum direction initialDirection=TOP_RIGHT;
        ueNodes.Get(i)->GetObject<MobilityModel>()->SetPosition(Vector(PosX, PosY, 0));
        double speedUe = speedUes.at(i);
        double speedCos60 = speedUe*cos60;
        double speedSin60 = speedUe*sin60;
        for (int j = 0; j < int(simTime); j++)
        {
            if (initialDirection == TOP_RIGHT)
            {
                PosX += speedUe;
                if (PosX > LimX)
                {
                    PosX = LimX;
                    initialDirection = BOTTOM_MID;
                }
            }
            if (initialDirection == BOTTOM_MID)
            {
                PosX -= speedCos60;
                PosY += speedSin60;
                if (PosY > LimY)
                {
                    PosX = MidX;
                    PosY = LimY;
                    initialDirection = TOP_LEFT;
                }
            }
            if (initialDirection == TOP_LEFT)
            {
                PosX -= speedCos60;
                PosY -= speedSin60;
                if (PosX < InitPosX)
                {
                    PosX = InitPosX;
                    PosY = InitPosY;
                    initialDirection = TOP_RIGHT;
                }
            }
            Waypoint wpt(Seconds(j), Vector(PosX, PosY, 0.0));
            ueNodes.Get(i)->GetObject<WaypointMobilityModel>()->AddWaypoint(wpt);
        }
    }

  // Install LTE Devices in eNB and UEs
  Config::SetDefault ("ns3::LteEnbRrc::DefaultTransmissionMode", UintegerValue(2));
  Config::SetDefault ("ns3::LteEnbPhy::TxPower", DoubleValue (enbTxPowerDbm));
  //Config::SetDefault("ns3::LteUePhy::TxPower", DoubleValue(50.0));
  //lteHelper->SetEnbAntennaModelAttribute ("Gain",     DoubleValue (30));
  //lteHelper->SetUeAntennaModelAttribute  ("Gain",     DoubleValue (30));
  NetDeviceContainer enbLteDevs = lteHelper->InstallEnbDevice (enbNodes);
  NetDeviceContainer ueLteDevs = lteHelper->InstallUeDevice (ueNodes);

  // Install the IP stack on the UEs
  internet.Install (ueNodes);
  Ipv4InterfaceContainer ueIpIfaces;
  ueIpIfaces = epcHelper->AssignUeIpv4Address (NetDeviceContainer(ueLteDevs));

  // Attach all UEs to the first eNodeB
  for (uint16_t i = 0; i < numberOfUes; i++)
    {
      lteHelper->Attach (ueLteDevs.Get (i), enbLteDevs.Get (0));
    }

  NS_LOG_LOGIC("setting up applications");

  // Install and start applications on UEs and remote host
  uint16_t dlPort = 10000;
  uint16_t ulPort = 20000;

  Config::SetDefault ("ns3::UdpClient::Interval", TimeValue (Seconds (1)));
  Config::SetDefault ("ns3::UdpClient::MaxPackets", UintegerValue (1000000));

  // randomize a bit start times to avoid simulation artifacts
  // (e.g., buffer overflows due to packet transmissions happening
  // exactly at the same time)
  Ptr<UniformRandomVariable> startTimeSeconds = CreateObject<UniformRandomVariable> ();
  startTimeSeconds->SetAttribute ("Min", DoubleValue (1));
  startTimeSeconds->SetAttribute ("Max", DoubleValue (1.9));

  for (uint32_t u = 0; u < numberOfUes; ++u)
    {
      Ptr<Node> ue = ueNodes.Get (u);
      // Set the default gateway for the UE
      Ptr<Ipv4StaticRouting> ueStaticRouting =
          ipv4RoutingHelper.GetStaticRouting (ue->GetObject<Ipv4> ());
      ueStaticRouting->SetDefaultRoute (epcHelper->GetUeDefaultGatewayAddress (), 1);

      for (uint32_t b = 0; b < numBearersPerUe; ++b)
        {
          ++dlPort;
          ++ulPort;

          ApplicationContainer clientApps;
          ApplicationContainer serverApps;

          NS_LOG_LOGIC("installing UDP DL app for UE " << u);
          UdpClientHelper dlClientHelper (ueIpIfaces.GetAddress (u), dlPort);
          clientApps.Add (dlClientHelper.Install (remoteHost));
          PacketSinkHelper dlPacketSinkHelper ("ns3::UdpSocketFactory",
                                               InetSocketAddress (Ipv4Address::GetAny (), dlPort));
          serverApps.Add (dlPacketSinkHelper.Install (ue));

          NS_LOG_LOGIC("installing UDP UL app for UE " << u);
          UdpClientHelper ulClientHelper (remoteHostAddr, ulPort);
          clientApps.Add (ulClientHelper.Install (ue));
          PacketSinkHelper ulPacketSinkHelper ("ns3::UdpSocketFactory",
                                               InetSocketAddress (Ipv4Address::GetAny (), ulPort));
          serverApps.Add (ulPacketSinkHelper.Install (remoteHost));

          Time startTime = Seconds (startTimeSeconds->GetValue ());
          serverApps.Start (startTime);
          clientApps.Start (startTime);

        } // end for b
    }

  // Add X2 interface
  lteHelper->AddX2Interface (enbNodes);

  // Configura regra de encaminhamento para eNBs que não sejam o primeiro
  for (unsigned i = 1; i < numberOfEnbs; i++)
    {
      Ipv4StaticRoutingHelper ipv4RoutingHelper;
      Ptr<Ipv4StaticRouting> remoteHostStaticRouting =
          ipv4RoutingHelper.GetStaticRouting (enbNodes.Get (i)->GetObject<Ipv4> ());
      remoteHostStaticRouting->AddNetworkRouteTo (Ipv4Address ("10.0.0.6"), Ipv4Mask ("255.255.255.252"), 1);
    }

  // connect custom trace sinks for RRC connection establishment and handover notification
  Config::Connect ("/NodeList/*/DeviceList/*/LteEnbRrc/ConnectionEstablished",
                   MakeCallback (&NotifyConnectionEstablishedEnb));
  Config::Connect ("/NodeList/*/DeviceList/*/LteUeRrc/ConnectionEstablished",
                   MakeCallback (&NotifyConnectionEstablishedUe));
  Config::Connect ("/NodeList/*/DeviceList/*/LteEnbRrc/HandoverStart",
                   MakeCallback (&NotifyHandoverStartEnb));
  Config::Connect ("/NodeList/*/DeviceList/*/LteUeRrc/HandoverStart",
                   MakeCallback (&NotifyHandoverStartUe));
  Config::Connect ("/NodeList/*/DeviceList/*/LteEnbRrc/HandoverEndOk",
                   MakeCallback (&NotifyHandoverEndOkEnb));
  Config::Connect ("/NodeList/*/DeviceList/*/LteUeRrc/HandoverEndOk",
                   MakeCallback (&NotifyHandoverEndOkUe));
  Config::Connect ("/NodeList/*/DeviceList/*/LteUeRrc/HandoverEndError",
                  MakeCallback (&NotifyHandoverEndErrorUe));
  Config::Connect ("/NodeList/*/DeviceList/*/LteEnbRrc/HandoverCancelled",
                  MakeCallback (&NotifyHandoverCancelledEnb));
  Config::Connect ("/NodeList/*/DeviceList/*/LteEnbRrc/HandoverTriggered",
                    MakeCallback (&NotifyHandoverTriggeredEnb));

  if (scenario == HandoverScenarios::ORAN_BYPASS
      || scenario == HandoverScenarios::ORAN_RIC_XAPP_KMEANS
      || scenario == HandoverScenarios::ORAN_RIC_XAPP_KMEANS_INITIATED
      || scenario == HandoverScenarios::ORAN_RIC_XAPP_MAXRSRQ
      || scenario == HandoverScenarios::ORAN_RIC_XAPP_MAXRSRQ_INITIATED
     )
  {
      Ptr<E2AP> e2t = CreateObject<E2AP>();
      sgw->AddApplication(e2t);

      // Create the handover xApp
      if (scenario == HandoverScenarios::ORAN_RIC_XAPP_KMEANS
          || scenario == HandoverScenarios::ORAN_RIC_XAPP_KMEANS_INITIATED)
      {
          Ptr<xAppHandoverMlpackKmeans> handoverxapp = CreateObject<xAppHandoverMlpackKmeans>(false, 1, scenario == HandoverScenarios::ORAN_RIC_XAPP_KMEANS_INITIATED);
          sgw->AddApplication(handoverxapp);
      }

      if (scenario == HandoverScenarios::ORAN_RIC_XAPP_MAXRSRQ
          || scenario == HandoverScenarios::ORAN_RIC_XAPP_MAXRSRQ_INITIATED)
      {
          Ptr<xAppHandoverMaxRsrq> handoverxapp = CreateObject<xAppHandoverMaxRsrq>(scenario == HandoverScenarios::ORAN_RIC_XAPP_MAXRSRQ_INITIATED);
          sgw->AddApplication(handoverxapp);
      }

      // Configurar eNodeBs/nós E2
      Ptr<E2AP> e2n1 = CreateObject<E2AP>();
      enbNodes.Get(0)->AddApplication(e2n1);
      Simulator::Schedule(Seconds(0.5), &E2AP::Connect, e2t);
      Simulator::Schedule(Seconds(1.0), &E2AP::Connect, e2n1);
      Simulator::Schedule(Seconds(2.0), &E2AP::RegisterDefaultEndpoints, e2n1);
      Simulator::Schedule(Seconds(2.5), &E2AP::SubscribeToDefaultEndpoints, e2t, *e2n1);

      Ptr<E2AP> e2n2 = CreateObject<E2AP>();
      enbNodes.Get(1)->AddApplication(e2n2);
      Simulator::Schedule(Seconds(1.0), &E2AP::Connect, e2n2);
      Simulator::Schedule(Seconds(2.0), &E2AP::RegisterDefaultEndpoints, e2n2);
      Simulator::Schedule(Seconds(2.5), &E2AP::SubscribeToDefaultEndpoints, e2t, *e2n2);

      Ptr<E2AP> e2n3 = CreateObject<E2AP>();
      enbNodes.Get(2)->AddApplication(e2n3);
      Simulator::Schedule(Seconds(1.0), &E2AP::Connect, e2n3);
      Simulator::Schedule(Seconds(2.0), &E2AP::RegisterDefaultEndpoints, e2n3);
      Simulator::Schedule(Seconds(2.5), &E2AP::SubscribeToDefaultEndpoints, e2t, *e2n3);
  }
  /*
  AnimationInterface anim("anim.xml");
  //anim.SetMaxPktsPerTraceFile(0xFFFFFFFF);
  anim.EnablePacketMetadata(false);

  anim.UpdateNodeDescription(remoteHost->GetId(), "Remote Internet Host");
  anim.UpdateNodeColor(remoteHost->GetId(), 230, 230, 230);
  anim.UpdateNodeSize(remoteHost->GetId(), 80, 80);

  anim.UpdateNodeDescription(pgw->GetId(), "PGW");
  anim.UpdateNodeColor(pgw->GetId(), 0, 0, 255);
  anim.UpdateNodeSize(pgw->GetId(), 80, 80);

  anim.UpdateNodeDescription(sgw->GetId(), "SGW/RIC");
  anim.UpdateNodeColor(sgw->GetId(), 0, 0, 255);
  anim.UpdateNodeSize(sgw->GetId(), 80, 80);

  anim.UpdateNodeDescription(mme->GetId(), "MME");
  anim.UpdateNodeColor(mme->GetId(), 0, 0, 255);
  anim.UpdateNodeSize(mme->GetId(), 80, 80);

  for (uint32_t i = 0; i < enbNodes.GetN(); i++)
  {
      int nodeId = enbNodes.Get(i)->GetId();
      anim.UpdateNodeDescription(nodeId, "eNB" + std::to_string(i));
      anim.UpdateNodeColor(nodeId, 255, 0, 0);
      anim.UpdateNodeSize(nodeId, 80, 80);

  }
  for (uint32_t i = 0; i < ueNodes.GetN(); i++)
  {
      int nodeId = ueNodes.Get(i)->GetId();
      anim.UpdateNodeDescription(nodeId, "UE" + std::to_string(i));
      anim.UpdateNodeColor(nodeId, 0, 255, 0);
      anim.UpdateNodeSize(nodeId, 80, 80);
  }
  */
  //Ptr<FlowMonitor> flowMonitor;
  //FlowMonitorHelper flowHelper;
  //flowMonitor = flowHelper.InstallAll();

  Simulator::Stop (Seconds(simTime));
  Simulator::Run ();

  //flowMonitor->SerializeToXmlFile("flow.xml", true, false);
  std::ofstream csvOutput(output_csv_filename);
  csvOutput << "Time (ns),IMSI,SrcCellId,RNTI,TrgtCellId,Type," << std::endl;
  for (auto& entry: simulationRegistry)
  {
      csvOutput << entry << std::endl;
  }
  csvOutput.close();
  Simulator::Destroy ();
  return 0;
}
