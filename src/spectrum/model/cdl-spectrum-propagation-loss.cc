/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2020 Luis Pacheco
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Luis Pacheco <lpacheco@tuta.io>
 */

#include <ns3/log.h>
#include <ns3/mobility-model.h>
#include <ns3/enum.h>
#include <ns3/uinteger.h>
#include <ns3/double.h>
#include <ns3/boolean.h>
#include <cmath> // for M_PI
#include "cdl-spectrum-propagation-loss.h"
#include <vector>
#include <ns3/lte-spectrum-value-helper.h>
#include "ns3/lte-ue-net-device.h"
#include "ns3/lte-enb-net-device.h"
#include "ns3/node.h"
#include "ns3/core-module.h"
#include "ns3/spatially-correlated-shadowing-map.h"


namespace ns3
{

NS_OBJECT_ENSURE_REGISTERED (CdlSpectrumPropagationLossModel);

CdlSpectrumPropagationLossModel::~CdlSpectrumPropagationLossModel(){};
std::map<std::tuple<Ptr<const MobilityModel>, Ptr<const MobilityModel>>,CdlCommon> CdlSpectrumPropagationLossModel::cdlInstances;


TypeId
CdlSpectrumPropagationLossModel::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::CdlSpectrumPropagationLossModel")
      .SetParent<SpectrumPropagationLossModel> ()
      .SetGroupName ("Spectrum")
      .AddConstructor<CdlSpectrumPropagationLossModel> ()
      .AddAttribute ("CdlType",
                     "CDL Type, A or D.",
                     EnumValue (CdlSpectrumPropagationLossModel::CDL_D),
                     MakeEnumAccessor (&CdlSpectrumPropagationLossModel::m_cdlType),
                     MakeEnumChecker (CdlSpectrumPropagationLossModel::CDL_A, "CDL_A",
                                      CdlSpectrumPropagationLossModel::CDL_D, "CDL_D"))
      .AddTraceSource ("PsdReceived",
                       "PsdReceived",
                       MakeTraceSourceAccessor (&CdlSpectrumPropagationLossModel::m_psdReceived),
                       "ns3::CdlSpectrumPropagationLossModel::CdlPsdTracedCallback")
      .AddTraceSource ("PsdCalculated",
                       "PsdCalculated",
                       MakeTraceSourceAccessor (&CdlSpectrumPropagationLossModel::m_psdReceived),
                       "ns3::CdlSpectrumPropagationLossModel::CdlPsdTracedCallback")
  ;
  return tid;
}

Ptr<SpectrumValue>
CdlSpectrumPropagationLossModel::DoCalcRxPowerSpectralDensity (Ptr<const SpectrumValue> txPsd,
                                                                Ptr<const MobilityModel> a,
                                                                Ptr<const MobilityModel> b) const
{

  Ptr<SpectrumValue> rxPsd = Copy<SpectrumValue> (txPsd);
  m_psdReceived(rxPsd);
  Values::iterator vit = rxPsd->ValuesBegin ();
  Bands::const_iterator fit = rxPsd->ConstBandsBegin ();
  double system_freq;

  NS_ASSERT (a);
  NS_ASSERT (b);

  double d = a->GetDistanceFrom (b);
  //NS_ASSERT_MSG(d <= 1000, "The distance between the transmitter and receiver must be larger than 1km.");
  if (d <= 1000)
      d += 1001-d; // we should ensure nodes are closer than 1km, but getting a worse result to guarantee it will work isn't that bad
  Ptr<NetDevice> dev_a = a->GetObject<Node>()->GetDevice(0);
  Ptr<NetDevice> dev_b = b->GetObject<Node>()->GetDevice(0);

  Ptr<Ula5gRange> ula_tx, ula_rx;

  //uplink UE-eNB
  if (DynamicCast<LteUeNetDevice>(dev_a) && DynamicCast<LteEnbNetDevice>(dev_b))
    {
      ula_tx = DynamicCast<LteUeNetDevice>(dev_a)->GetPhy()->GetUplinkSpectrumPhy()->GetUla();
      ula_rx = DynamicCast<LteEnbNetDevice>(dev_b)->GetPhy()->GetUplinkSpectrumPhy()->GetUla();
      system_freq = LteSpectrumValueHelper::GetUplinkCarrierFrequency(DynamicCast<LteEnbNetDevice>(dev_b)->GetUlEarfcn());
    }
  //downlink eNB-UE
  else if (DynamicCast<LteEnbNetDevice>(dev_a) && DynamicCast<LteUeNetDevice>(dev_b))
    {
      ula_tx = DynamicCast<LteEnbNetDevice> (dev_a)->GetPhy ()->GetDownlinkSpectrumPhy ()->GetUla ();
      ula_rx = DynamicCast<LteUeNetDevice> (dev_b)->GetPhy ()->GetDownlinkSpectrumPhy ()->GetUla ();
      system_freq = LteSpectrumValueHelper::GetDownlinkCarrierFrequency(DynamicCast<LteEnbNetDevice>(dev_a)->GetDlEarfcn());
    }
  else
  {
      //workaround for other devices e.g. NonCommunicatingNetDevice - > WaveformGenerator/PU = FSPL
      // taken from RANGE5G propagation model and multi-model-spectrum-channel
      const double C = 299792458.0; // speed of light in vacuum
      const double m_systemLoss = 1.0;
      const double frequency = 713000000;
      const double m_lambda = C/frequency;
      const double numerator = m_lambda * m_lambda;
      const double m_sigma = 4.47;
      double denominator = 16 * M_PI * M_PI * d * d * m_systemLoss;
      double lossDb = 10 * log10(numerator / denominator);
      double shadowing = 0.0;
      auto rxPos = b->GetPosition();
      shadowing = SpatiallyCorrelatedShadowingMap::get_coordinate_shadowing(Vector3D(rxPos.x, rxPos.y, rxPos.z));
      lossDb += shadowing;
      double linearGain = std::pow (10.0, (lossDb) / 10.0);
      *rxPsd *= linearGain;
      return rxPsd;
  }

  if (ula_tx->GetSystemFreq() == 0.0)
  {
    ula_tx->SetSystemFreq(system_freq);
  }
  ula_tx->SetPosition (a->GetPosition());
  ula_tx->SetVelocity (a->GetVelocity());

  if (ula_rx->GetSystemFreq() == 0.0)
  {
    ula_rx->SetSystemFreq(system_freq);
  }
  ula_rx->SetPosition (b->GetPosition());
  ula_rx->SetVelocity (b->GetVelocity());

  double time = ns3::Simulator::Now().GetSeconds ();

  bool is_cdl_a = m_cdlType == CDL_A;

  auto tupleKey = std::tuple<Ptr<const MobilityModel>, Ptr<const MobilityModel>>{a,b};
  auto cdlInstance = cdlInstances.find(tupleKey);
  if (cdlInstance == cdlInstances.end())
  {
      //If CDL instance for a given pair doesn't exist, create one
      CdlCommon cdl_inst(is_cdl_a, ula_tx, ula_rx, d);
      cdlInstances.emplace(tupleKey, cdl_inst);
      cdlInstance = cdlInstances.find(tupleKey);
  }
  //CdlCommon cdlInstance = CdlCommon(is_cdl_a, ula_tx, ula_rx, d);

  double path_loss = cdlInstance->second.get_tot_path_gain(d);
  std::vector<double> losses = cdlInstance->second.get_channel_fr_5g (Simulator::Now().GetSeconds(), rxPsd);

  vit = rxPsd->ValuesBegin ();
  size_t i = 0;
  while (vit != rxPsd->ValuesEnd ())
    {
      NS_ASSERT (fit != rxPsd->ConstBandsEnd ());
      *vit *= (losses[i]*losses[i]); // Prx = Ptx / loss
      ++vit;
      ++fit;
      ++i;
    }

  m_psdCalculated(rxPsd);
  return rxPsd;
}


} // namespace ns3