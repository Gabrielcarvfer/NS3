#include "ns3/core-module.h"
#include "ns3/lte-module.h"
#include <ns3/lte-spectrum-value-helper.h>
#include <ns3/cdl-spectrum-propagation-loss.h>
#include <ns3/constant-position-mobility-model.h>
#include <ns3/mobility-helper.h>
#include <fstream>
#include <vector>


using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("5gRangeD31Validation");

int
main (int argc, char *argv[])
{
  NS_LOG_DEBUG (" Running 5gRangeD31Validation");
  int    reps             = 1000;
  double enbTxPower       = 53.0; //dBm
  double enbGain          = 9.0;  //dBi
  double ueTxPower        = 23.0; //dBm
  double ueGain           = 9.0;  //dBi
  int    dist             = 1001; //metros
  uint32_t bandwidth      = 24; //6 MHz, 8 MHz or 24 MHz (6 MHz and 8 MHz uses 4 or 3 component carriers, respectively)
  uint32_t dlEarfcn       = 50000;
  uint32_t ulEarfcn       = 60000;
  uint32_t dlBandwidth    = 132; //6MHz = 33 RBs, 8MHz = 44 RBs, 24MHz = 132 RBs (no CA)
  uint32_t ulBandwidth    = 132; //6MHz = 33 RBs, 8MHz = 44 RBs, 24MHz = 132 RBs (no CA)

  double m_systemLoss     = 1.0;
  double m_minLoss        = 0.0;
  double m_kValue         = 29.38;
  double m_shadowingMu    = 0.0;
  double m_shadowingSigma = 4.47;

  double system_freq = LteSpectrumValueHelper::GetCarrierFrequency(dlEarfcn);

  Config::SetDefault ("ns3::RANGE5GPropagationLossModel::Frequency", DoubleValue (system_freq));
  Config::SetDefault ("ns3::RANGE5GPropagationLossModel::SystemLoss", DoubleValue (m_systemLoss));
  Config::SetDefault ("ns3::RANGE5GPropagationLossModel::MinLoss", DoubleValue (m_minLoss));
  Config::SetDefault ("ns3::RANGE5GPropagationLossModel::K-value", DoubleValue (m_kValue));
  Config::SetDefault ("ns3::RANGE5GPropagationLossModel::ShadowingMu", DoubleValue (m_shadowingMu));
  Config::SetDefault ("ns3::RANGE5GPropagationLossModel::ShadowingSigma", DoubleValue (m_shadowingSigma));

  std::ofstream out("d31_5grange_ns3_" + std::to_string(dist) + "-m.txt", std::ios::out);

  Ptr<MobilityModel> a = CreateObject<ConstantPositionMobilityModel>();
  a->SetPosition(Vector(50000,50000,0));
  Ptr<MobilityModel> b = CreateObject<ConstantPositionMobilityModel>();
  b->SetPosition(Vector(50000+dist,50000,0));

  std::cout << "d: " << a->GetDistanceFrom(b) << std::endl;

  std::cout.precision(17);

  std::vector <int> dlRb;
  for (uint8_t i = 0; i < dlBandwidth; i++)
  {
    dlRb.push_back (i);
  }

  Ptr<SpectrumValue> rxPsd = LteSpectrumValueHelper::CreateTxPowerSpectralDensity(dlEarfcn, dlBandwidth, enbTxPower, dlRb);

  Ptr<RANGE5GPropagationLossModel> d31 = CreateObject<RANGE5GPropagationLossModel> ();

  std::vector<double> losses (reps);


  for (int r = 0; r < reps; r++)
    {
      double pathLossDb = d31->CalcRxPower(0, a, b);
      double pathGainLinear = std::pow (10.0, (pathLossDb) / 10.0);
      Ptr<SpectrumValue> curPsd = rxPsd->Copy();
      *(curPsd) *= pathGainLinear;
      auto fit = curPsd->ConstBandsBegin();
      for (int i = 0; i < dlBandwidth; i++) {
        out << curPsd->ValuesAt(i) << " ";
      }
      out << std::endl;
    }

  out.close();

  return 0;
}