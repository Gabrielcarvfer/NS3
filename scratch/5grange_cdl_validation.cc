#include "ns3/core-module.h"
#include "ns3/lte-module.h"
#include <ns3/lte-spectrum-value-helper.h>
#include <ns3/cdl-spectrum-propagation-loss.h>
#include <ns3/constant-position-mobility-model.h>
#include <ns3/mobility-helper.h>
#include <fstream>


using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("5gRangeCdlValidation");

void printULA(Ptr<Ula5gRange> ula) {
  std::cout << "ULA: numantelem:" << ula->get_num_antenna_elem() <<   " antvirt:" << ula->get_num_virtual_ant_elem() << " pos:" << ula->get_position() << " vel:" << ula->get_velocity() << " poldual:" << ula->polarization_is_dual() << std::endl;
}

int
main (int argc, char *argv[])
{
  NS_LOG_DEBUG (" Running 5gRangeCdlValidation");

  int    reps             = 1000;
  double enbTxPower       = 53.0; //dBm
  double enbGain          = 9.0;  //dBi
  double ueTxPower        = 23.0; //dBm
  double ueGain           = 9.0;  //dBi
  int    dist             = 50000; //metros
  uint32_t bandwidth      = 24; //6 MHz, 8 MHz or 24 MHz (6 MHz and 8 MHz uses 4 or 3 component carriers, respectively)
  uint32_t dlEarfcn       = 50000;
  uint32_t ulEarfcn       = 60000;
  uint32_t dlBandwidth    = 132; //6MHz = 33 RBs, 8MHz = 44 RBs, 24MHz = 132 RBs (no CA)
  uint32_t ulBandwidth    = 132; //6MHz = 33 RBs, 8MHz = 44 RBs, 24MHz = 132 RBs (no CA)

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
  Config::SetDefault ("ns3::LteHelper::UseIdealRrc", BooleanValue (true));
  Config::SetDefault("ns3::LteEnbPhy::TxPower", DoubleValue(enbTxPower));
  Config::SetDefault("ns3::LteUePhy::TxPower" , DoubleValue(ueTxPower));
  Config::SetDefault ("ns3::LteEnbRrc::SrsPeriodicity", UintegerValue (160));
  Config::SetDefault ("ns3::LteUePhy::EnableUplinkPowerControl", BooleanValue (false));
  Config::SetDefault("ns3::LteEnbMac::SpectrumSensing", BooleanValue(false));//for whatever reason, refuses to work
  Config::SetDefault("ns3::LteSpectrumPhy::SpectrumSensing", BooleanValue(false));//for whatever reason, refuses to work
  Config::SetDefault("ns3::LteEnbMac::FusionAlgorithm", UintegerValue(6));

  Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();
  lteHelper->SetSchedulerType ("ns3::RrFfMacScheduler");
  Config::SetDefault ("ns3::RrFfMacScheduler::HarqEnabled", BooleanValue (false));
  Config::SetDefault ("ns3::TraceFadingLossModel::RbNum", UintegerValue (dlBandwidth));
  lteHelper->SetPathlossModelType (TypeId::LookupByName ("ns3::CdlSpectrumPropagationLossModel"));

  lteHelper->SetEnbAntennaModelAttribute ("Gain",     DoubleValue (enbGain));
  lteHelper->SetUeAntennaModelAttribute  ("Gain",     DoubleValue (ueGain));


  NodeContainer ueNode, enbNode;
  enbNode.Create(1);
  ueNode.Create(1);

  Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
  positionAlloc->Add (Vector(50000.0, 50000.0, 0));  // eNB

  Ptr<ListPositionAllocator> positionAlloc2 = CreateObject<ListPositionAllocator> ();
  positionAlloc2->Add (Vector(50000.0, 50000.0 + dist, 0));

  MobilityHelper mobility;
  mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
  mobility.SetPositionAllocator(positionAlloc);
  mobility.Install(enbNode);

  mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
  mobility.SetPositionAllocator(positionAlloc2);
  mobility.Install(ueNode);

  NetDeviceContainer enbLteDev = lteHelper->InstallEnbDevice (enbNode);
  NetDeviceContainer ueLteDev = lteHelper->InstallUeDevice (ueNode);

  Ptr<MobilityModel> tx = enbNode.Get(0)->GetObject<MobilityModel>();
  Ptr<MobilityModel> rx = ueNode.Get(0)->GetObject<MobilityModel>();

  double system_freq = LteSpectrumValueHelper::GetCarrierFrequency(dlEarfcn);
  std::cout.precision(17);

  std::cout << "system freq: " << system_freq << std::endl;
  LteSpectrumValueHelper svh;
  Ptr<SpectrumModel> spec = svh.GetSpectrumModel(dlEarfcn, dlBandwidth);

  std::vector <int> dlRb;
  for (uint8_t i = 0; i < dlBandwidth; i++)
  {
    dlRb.push_back (i);
  }

  Ptr<SpectrumValue> rxPsd = svh.CreateTxPowerSpectralDensity(dlEarfcn, dlBandwidth, enbGain, dlRb);


  std::ofstream out("cdl_5grange_ns3_" + std::to_string(dist) + "m.txt", std::ios::out);
  std::ofstream out_freqs("cdl_5grange_ns3_" + std::to_string(dist) + "m_freqs.txt", std::ios::out);

  for (int r = 0; r < reps; r++) {
    Ptr<CdlSpectrumPropagationLossModel> cdl = CreateObject<CdlSpectrumPropagationLossModel> ();
    auto fit = rxPsd->ConstBandsBegin();
    /*
    std::cout << "system_freq: " << system_freq << std::endl;
    std::cout << "freqs:";


    while(fit != rxPsd->ConstBandsEnd()) {
      std::cout << fit->fc << " ";
      ++fit;
    }
    std::cout << std::endl;


    std::cout << "psd:";

    fit = rxPsd->ConstBandsBegin();
    for (int i = 0; i < dlBandwidth; i++) {
      std::cout << rxPsd->ValuesAt(i) << " ";
      ++fit;
    }
    std::cout << std::endl;
    */

    Ptr<SpectrumValue> rxPsdn = cdl->DoCalcRxPowerSpectralDensity(rxPsd, tx, rx);


    /*
    fit = rxPsdn->ConstBandsBegin();
    for (int i = 0; i < dlBandwidth; i++) {
      std::cout << rxPsdn->ValuesAt(i) << " ";
      ++fit;
    }
    std::cout << std::endl;
     */

    for (int i = 0; i < dlBandwidth; i++) {
      out << rxPsdn->ValuesAt(i) << " ";
    }
    out << std::endl;
  }

  out.close();

  auto fit = rxPsd->ConstBandsBegin();
  while(fit != rxPsd->ConstBandsEnd()) {
    out_freqs << fit->fc << std::endl;
    fit++;
  }
  out_freqs.close();


  return 0;
}