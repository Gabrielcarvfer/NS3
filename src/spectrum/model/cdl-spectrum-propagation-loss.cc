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

namespace ns3
{

NS_OBJECT_ENSURE_REGISTERED (CdlSpectrumPropagationLossModel);

CdlSpectrumPropagationLossModel::~CdlSpectrumPropagationLossModel ()
{
}

TypeId
CdlSpectrumPropagationLossModel::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::CdlSpectrumPropagationLossModel")
      .SetParent<SpectrumPropagationLossModel> ()
      .SetGroupName ("Spectrum")
      .AddConstructor<CdlSpectrumPropagationLossModel> ()
      .AddAttribute ("CdlType",
                     "CDL Type, A or D.",
                     EnumValue (CdlSpectrumPropagationLossModel::CDL_A),
                     MakeEnumAccessor (&CdlSpectrumPropagationLossModel::m_cdlType),
                     MakeEnumChecker (CdlSpectrumPropagationLossModel::CDL_A, "CDL_A",
                                      CdlSpectrumPropagationLossModel::CDL_D, "CDL_D"));
  ;
  return tid;
}

Ptr<SpectrumValue>
CdlSpectrumPropagationLossModel::DoCalcRxPowerSpectralDensity (Ptr<const SpectrumValue> txPsd,
                                                                Ptr<const MobilityModel> a,
                                                                Ptr<const MobilityModel> b) const
{

  Ptr<SpectrumValue> rxPsd = Copy<SpectrumValue> (txPsd);
  Values::iterator vit = rxPsd->ValuesBegin ();
  Bands::const_iterator fit = rxPsd->ConstBandsBegin ();
  double system_freq;

  NS_ASSERT (a);
  NS_ASSERT (b);

  double d = a->GetDistanceFrom (b) / (1.0e3);
  NS_ASSERT_MSG(d <= 1.0, "The distance between the transmitter and receiver must be larger than 1km.");

  Ptr<NetDevice> dev_a = a->GetObject<Node>()->GetDevice(0);
  Ptr<NetDevice> dev_b = b->GetObject<Node>()->GetDevice(0);

  Ptr<Ula5gRange> ula_tx, ula_rx;

  //uplink
  if (DynamicCast<LteUeNetDevice>(dev_a))
    {
      ula_tx = DynamicCast<LteUeNetDevice>(dev_a)->GetPhy()->GetUplinkSpectrumPhy()->GetUla();
      ula_rx = DynamicCast<LteEnbNetDevice>(dev_b)->GetPhy()->GetUplinkSpectrumPhy()->GetUla();
      system_freq = LteSpectrumValueHelper::GetUplinkCarrierFrequency(DynamicCast<LteEnbNetDevice>(dev_b)->GetUlEarfcn());
    }
  //downlink
  else
    {
      ula_tx = DynamicCast<LteEnbNetDevice> (dev_a)->GetPhy ()->GetDownlinkSpectrumPhy ()->GetUla ();
      ula_rx = DynamicCast<LteUeNetDevice> (dev_b)->GetPhy ()->GetDownlinkSpectrumPhy ()->GetUla ();
      system_freq = LteSpectrumValueHelper::GetDownlinkCarrierFrequency(DynamicCast<LteEnbNetDevice>(dev_a)->GetDlEarfcn());
    }

  if (ula_tx->GetSystemFreq() == 0.0)
  {
    ula_tx->SetSystemFreq(system_freq);
  }
  ula_tx->SetPosition (a->GetPosition ());
  ula_tx->SetVelocity (a->GetVelocity());

  if (ula_rx->GetSystemFreq() == 0.0)
  {
    ula_rx->SetSystemFreq(system_freq);
  }
  ula_rx->SetPosition (b->GetPosition ());
  ula_rx->SetVelocity (b->GetVelocity());

  double time = ns3::Simulator::Now().GetSeconds ();

  bool is_cdl_a = true;

  if(m_cdlType != CDL_A)
    {
     is_cdl_a = false;
    }

  CdlCommon cdl_inst(is_cdl_a, ula_tx, ula_rx);
  double path_loss = cdl_inst.get_tot_path_gain();

  *(rxPsd) *= path_loss;

  std::vector<double> losses = cdl_inst.get_channel_fr_5g (0, rxPsd);

  vit = rxPsd->ValuesBegin ();
  size_t i = 0;
  while (vit != rxPsd->ValuesEnd ())
    {
      NS_ASSERT (fit != rxPsd->ConstBandsEnd ());
      *vit /= losses[i]; // Prx = Ptx / loss
      ++vit;
      ++fit;
      ++i;
    }

  return rxPsd;
}


} // namespace ns3