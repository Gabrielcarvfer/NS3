//#include "xAppInfrastructure/PubSubInfra.h"

#include <cstdint>
#include <ostream>
#include <string>

#include "ns3/animation-interface.h"
#include "ns3/boolean.h"
#include "ns3/command-line.h"
#include "ns3/config.h"
#include "ns3/double.h"
#include "ns3/eps-bearer.h"
#include "ns3/fatal-error.h"
#include "ns3/log.h"
#include "ns3/lte-enb-net-device.h"
#include "ns3/lte-enb-phy.h"
#include "ns3/lte-ffr-algorithm.h"
#include "ns3/lte-helper.h"
#include "ns3/lte-rrc-sap.h"
#include "ns3/lte-spectrum-phy.h"
#include "ns3/lte-spectrum-value-helper.h"
#include "ns3/mobility-helper.h"
#include "ns3/net-device-container.h"
#include "ns3/net-device.h"
#include "ns3/node-container.h"
#include "ns3/nstime.h"
#include "ns3/object-factory.h"
#include "ns3/object.h"
#include "ns3/pointer.h"
#include "ns3/position-allocator.h"
#include "ns3/ptr.h"
#include "ns3/rng-seed-manager.h"
#include "ns3/simulator.h"
#include "ns3/spectrum-analyzer-helper.h"
#include "ns3/spectrum-channel.h"
#include "ns3/spectrum-model.h"
#include "ns3/string.h"
#include "ns3/uinteger.h"
#include "ns3/vector.h"
#include "ns3/fatal-impl.h"

NS_LOG_COMPONENT_DEFINE("topologia");

using namespace ns3;

int main (int argc, char *argv[])
{
  Config::SetDefault ("ns3::LteSpectrumPhy::CtrlErrorModelEnabled", BooleanValue (true));
  Config::SetDefault ("ns3::LteSpectrumPhy::DataErrorModelEnabled", BooleanValue (true));
  Config::SetDefault ("ns3::LteHelper::UseIdealRrc", BooleanValue (true));
  Config::SetDefault ("ns3::LteHelper::UsePdschForCqiGeneration", BooleanValue (true));

  //Uplink Power Control
  Config::SetDefault ("ns3::LteUePhy::EnableUplinkPowerControl", BooleanValue (true));
  Config::SetDefault ("ns3::LteUePowerControl::ClosedLoop", BooleanValue (true));
  Config::SetDefault ("ns3::LteUePowerControl::AccumulationEnabled", BooleanValue (false));

  uint32_t runId = 3;
  double simTime = 2.500;
  bool generateSpectrumTrace = false;
  bool generateRem = false;
  int32_t remRbId = -1;
  uint16_t bandwidth = 25;
  double distance = 1000;

  // Command line arguments
  CommandLine cmd (__FILE__);
  cmd.AddValue ("simTime", "Total duration of the simulation (in seconds)", simTime);
  cmd.AddValue ("generateSpectrumTrace", "if true, will generate a Spectrum Analyzer trace", generateSpectrumTrace);
  cmd.AddValue ("generateRem", "if true, will generate a REM and then abort the simulation", generateRem);
  cmd.AddValue ("remRbId", "Resource Block Id, for which REM will be generated,"
                "default value is -1, what means REM will be averaged from all RBs", remRbId);
  cmd.AddValue ("runId", "runId", runId);
  cmd.Parse (argc, argv);

  RngSeedManager::SetSeed (1);
  RngSeedManager::SetRun (runId);

  Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();

  // Create Nodes: eNodeB and UE
  NodeContainer enbNodes;
  NodeContainer centerUeNodes;
  NodeContainer edgeUeNodes;
  enbNodes.Create (3);
  centerUeNodes.Create (3);
  edgeUeNodes.Create (3);


/*   the topology is the following:
 *                 eNB3
 *                /     \
 *               /       \
 *              /         \
 *             /           \
 *   distance /             \ distance
 *           /      UEs      \
 *          /                 \
 *         /                   \
 *        /                     \
 *       /                       \
 *   eNB1-------------------------eNB2
 *                  distance
 */

  // Install Mobility Model
  Ptr<ListPositionAllocator> enbPositionAlloc = CreateObject<ListPositionAllocator> ();
  enbPositionAlloc->Add (Vector (0.0, 0.0, 0.0));                       // eNB1
  enbPositionAlloc->Add (Vector (distance,  0.0, 0.0));                 // eNB2
  enbPositionAlloc->Add (Vector (distance * 0.5, distance * 0.866, 0.0));   // eNB3
  MobilityHelper mobility;
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.SetPositionAllocator (enbPositionAlloc);
  mobility.Install (enbNodes);


  Ptr<ListPositionAllocator> edgeUePositionAlloc = CreateObject<ListPositionAllocator> ();
  edgeUePositionAlloc->Add (Vector (distance * 0.5, distance * 0.28867, 0.0));  // edgeUE1
  edgeUePositionAlloc->Add (Vector (distance * 0.5, distance * 0.28867, 0.0));  // edgeUE2
  edgeUePositionAlloc->Add (Vector (distance * 0.5, distance * 0.28867, 0.0));  // edgeUE3
  mobility.SetPositionAllocator (edgeUePositionAlloc);
  mobility.Install (edgeUeNodes);

  std::stringstream ss;
  ObjectFactory pos;
  pos.SetTypeId ("ns3::RandomRectanglePositionAllocator");
  // e.g. ns3::UniformRandomVariable[Min=0.0|Max=300.0]
  ss << "ns3::UniformRandomVariable[Min=" << distance * 0.2 << "|Max=" << distance * 0.7 << "]";
  pos.Set ("X", StringValue (ss.str()));
  ss.clear();
  ss << "ns3::UniformRandomVariable[Min=" << distance * 0.2 << "|Max=" << distance * 0.7 << "]";
  pos.Set ("Y", StringValue (ss.str()));
  Ptr<PositionAllocator> centerUePositionAlloc = pos.Create ()->GetObject<PositionAllocator> ();
  mobility.SetPositionAllocator (centerUePositionAlloc);
  mobility.Install (centerUeNodes);


  // Create Devices and install them in the Nodes (eNB and UE)
  NetDeviceContainer enbDevs;
  NetDeviceContainer edgeUeDevs;
  NetDeviceContainer centerUeDevs;
  lteHelper->SetSchedulerType ("ns3::RrFfMacScheduler");
  lteHelper->SetEnbDeviceAttribute ("DlBandwidth", UintegerValue (bandwidth));
  lteHelper->SetEnbDeviceAttribute ("UlBandwidth", UintegerValue (bandwidth));

  std::string frAlgorithmType = lteHelper->GetFfrAlgorithmType ();
  NS_LOG_DEBUG ("FrAlgorithmType: " << frAlgorithmType);

  if (frAlgorithmType == "ns3::LteFrHardAlgorithm")
    {

      //Nothing to configure here in automatic mode

    }
  else if (frAlgorithmType == "ns3::LteFrStrictAlgorithm")
    {

      lteHelper->SetFfrAlgorithmAttribute ("RsrqThreshold", UintegerValue (32));
      lteHelper->SetFfrAlgorithmAttribute ("CenterPowerOffset",
                                           UintegerValue (LteRrcSap::PdschConfigDedicated::dB_6));
      lteHelper->SetFfrAlgorithmAttribute ("EdgePowerOffset",
                                           UintegerValue (LteRrcSap::PdschConfigDedicated::dB3));
      lteHelper->SetFfrAlgorithmAttribute ("CenterAreaTpc", UintegerValue (0));
      lteHelper->SetFfrAlgorithmAttribute ("EdgeAreaTpc", UintegerValue (3));

      //ns3::LteFrStrictAlgorithm works with Absolute Mode Uplink Power Control
      Config::SetDefault ("ns3::LteUePowerControl::AccumulationEnabled", BooleanValue (false));

    }
  else if (frAlgorithmType == "ns3::LteFrSoftAlgorithm")
    {

      lteHelper->SetFfrAlgorithmAttribute ("AllowCenterUeUseEdgeSubBand", BooleanValue (true));
      lteHelper->SetFfrAlgorithmAttribute ("RsrqThreshold", UintegerValue (25));
      lteHelper->SetFfrAlgorithmAttribute ("CenterPowerOffset",
                                           UintegerValue (LteRrcSap::PdschConfigDedicated::dB_6));
      lteHelper->SetFfrAlgorithmAttribute ("EdgePowerOffset",
                                           UintegerValue (LteRrcSap::PdschConfigDedicated::dB3));
      lteHelper->SetFfrAlgorithmAttribute ("CenterAreaTpc", UintegerValue (0));
      lteHelper->SetFfrAlgorithmAttribute ("EdgeAreaTpc", UintegerValue (3));

      //ns3::LteFrSoftAlgorithm works with Absolute Mode Uplink Power Control
      Config::SetDefault ("ns3::LteUePowerControl::AccumulationEnabled", BooleanValue (false));

    }
  else if (frAlgorithmType == "ns3::LteFfrSoftAlgorithm")
    {

      lteHelper->SetFfrAlgorithmAttribute ("CenterRsrqThreshold", UintegerValue (30));
      lteHelper->SetFfrAlgorithmAttribute ("EdgeRsrqThreshold", UintegerValue (25));
      lteHelper->SetFfrAlgorithmAttribute ("CenterAreaPowerOffset",
                                           UintegerValue (LteRrcSap::PdschConfigDedicated::dB_6));
      lteHelper->SetFfrAlgorithmAttribute ("MediumAreaPowerOffset",
                                           UintegerValue (LteRrcSap::PdschConfigDedicated::dB_1dot77));
      lteHelper->SetFfrAlgorithmAttribute ("EdgeAreaPowerOffset",
                                           UintegerValue (LteRrcSap::PdschConfigDedicated::dB3));
      lteHelper->SetFfrAlgorithmAttribute ("CenterAreaTpc", UintegerValue (1));
      lteHelper->SetFfrAlgorithmAttribute ("MediumAreaTpc", UintegerValue (2));
      lteHelper->SetFfrAlgorithmAttribute ("EdgeAreaTpc", UintegerValue (3));

      //ns3::LteFfrSoftAlgorithm works with Absolute Mode Uplink Power Control
      Config::SetDefault ("ns3::LteUePowerControl::AccumulationEnabled", BooleanValue (false));

    }
  else if (frAlgorithmType == "ns3::LteFfrEnhancedAlgorithm")
    {

      lteHelper->SetFfrAlgorithmAttribute ("RsrqThreshold", UintegerValue (25));
      lteHelper->SetFfrAlgorithmAttribute ("DlCqiThreshold", UintegerValue (10));
      lteHelper->SetFfrAlgorithmAttribute ("UlCqiThreshold", UintegerValue (10));
      lteHelper->SetFfrAlgorithmAttribute ("CenterAreaPowerOffset",
                                           UintegerValue (LteRrcSap::PdschConfigDedicated::dB_6));
      lteHelper->SetFfrAlgorithmAttribute ("EdgeAreaPowerOffset",
                                           UintegerValue (LteRrcSap::PdschConfigDedicated::dB3));
      lteHelper->SetFfrAlgorithmAttribute ("CenterAreaTpc", UintegerValue (0));
      lteHelper->SetFfrAlgorithmAttribute ("EdgeAreaTpc", UintegerValue (3));

      //ns3::LteFfrEnhancedAlgorithm works with Absolute Mode Uplink Power Control
      Config::SetDefault ("ns3::LteUePowerControl::AccumulationEnabled", BooleanValue (false));

    }
  else if (frAlgorithmType == "ns3::LteFfrDistributedAlgorithm")
    {

      NS_FATAL_ERROR ("ns3::LteFfrDistributedAlgorithm not supported in this example. Please run lena-distributed-ffr");

    }
  else
    {
      lteHelper->SetFfrAlgorithmType ("ns3::LteFrNoOpAlgorithm");
    }

  lteHelper->SetFfrAlgorithmAttribute ("FrCellTypeId", UintegerValue (1));
  enbDevs.Add (lteHelper->InstallEnbDevice (enbNodes.Get (0)));

  lteHelper->SetFfrAlgorithmAttribute ("FrCellTypeId", UintegerValue (2));
  enbDevs.Add (lteHelper->InstallEnbDevice (enbNodes.Get (1)));

  lteHelper->SetFfrAlgorithmAttribute ("FrCellTypeId", UintegerValue (3));
  enbDevs.Add (lteHelper->InstallEnbDevice (enbNodes.Get (2)));

  //FR algorithm reconfiguration if needed
  PointerValue tmp;
  enbDevs.Get (0)->GetAttribute ("LteFfrAlgorithm", tmp);
  Ptr<LteFfrAlgorithm> ffrAlgorithm = DynamicCast<LteFfrAlgorithm> (tmp.GetObject ());
  ffrAlgorithm->SetAttribute ("FrCellTypeId", UintegerValue (1));


  //Install Ue Device
  edgeUeDevs = lteHelper->InstallUeDevice (edgeUeNodes);
  centerUeDevs = lteHelper->InstallUeDevice (centerUeNodes);

  // Attach edge UEs to eNbs
  for (uint32_t i = 0; i < edgeUeDevs.GetN (); i++)
    {
      lteHelper->Attach (edgeUeDevs.Get (i), enbDevs.Get (i));
    }
  // Attach center UEs to eNbs
  for (uint32_t i = 0; i < centerUeDevs.GetN (); i++)
    {
      lteHelper->Attach (centerUeDevs.Get (i), enbDevs.Get (i));
    }

  // Activate a data radio bearer
  enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE;
  EpsBearer bearer (q);
  lteHelper->ActivateDataRadioBearer (edgeUeDevs, bearer);
  lteHelper->ActivateDataRadioBearer (centerUeDevs, bearer);

  //Spectrum analyzer
  NodeContainer spectrumAnalyzerNodes;
  spectrumAnalyzerNodes.Create (1);
  SpectrumAnalyzerHelper spectrumAnalyzerHelper;

  if (generateSpectrumTrace)
    {
      Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
      //position of Spectrum Analyzer
//	  positionAlloc->Add (Vector (0.0, 0.0, 0.0));                              // eNB1
//	  positionAlloc->Add (Vector (distance,  0.0, 0.0));                        // eNB2
      positionAlloc->Add (Vector (distance * 0.5, distance * 0.866, 0.0));          // eNB3

      MobilityHelper mobility;
      mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
      mobility.SetPositionAllocator (positionAlloc);
      mobility.Install (spectrumAnalyzerNodes);

      Ptr<LteSpectrumPhy> enbDlSpectrumPhy = enbDevs.Get (0)->GetObject<LteEnbNetDevice> ()->GetPhy ()->GetDownlinkSpectrumPhy ()->GetObject<LteSpectrumPhy> ();
      Ptr<SpectrumChannel> dlChannel = enbDlSpectrumPhy->GetChannel ();

      spectrumAnalyzerHelper.SetChannel (dlChannel);
      Ptr<SpectrumModel> sm = LteSpectrumValueHelper::GetSpectrumModel (100, bandwidth);
      spectrumAnalyzerHelper.SetRxSpectrumModel (sm);
      spectrumAnalyzerHelper.SetPhyAttribute ("Resolution", TimeValue (MicroSeconds (10)));
      spectrumAnalyzerHelper.SetPhyAttribute ("NoisePowerSpectralDensity", DoubleValue (1e-15));     // -120 dBm/Hz
      spectrumAnalyzerHelper.EnableAsciiAll ("spectrum-analyzer-output");
      spectrumAnalyzerHelper.Install (spectrumAnalyzerNodes);
    }

  AnimationInterface anim("./anim.xml");
  Simulator::Stop (Seconds (simTime));
  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
