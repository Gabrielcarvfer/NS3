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

#ifndef CDL_SPECTRUMPROPAGATION_LOSS_H_
#define CDL_SPECTRUMPROPAGATION_LOSS_H_

#include <ns3/spectrum-propagation-loss-model.h>
#include <ns3/ula-5grange.h>
#include <ns3/cdl-common.h>
#include <ns3/simulator.h>
namespace ns3 {


/**
 * \ingroup spectrum
 * \brief Clustered delay line for Line of Sight
 */
class CdlSpectrumPropagationLossModel : public SpectrumPropagationLossModel
{

 public:

  CdlSpectrumPropagationLossModel() = default;
  ~CdlSpectrumPropagationLossModel ();

  /**
 * \brief Get the type ID.
 * \return the object TypeId
 */
  static TypeId GetTypeId ();

  virtual Ptr<SpectrumValue> DoCalcRxPowerSpectralDensity (Ptr<const SpectrumValue> txPsd,
                                                           Ptr<const MobilityModel> a,
                                                           Ptr<const MobilityModel> b) const;


  enum CdlType {
      CDL_A, CDL_D
  };

  typedef void (* CdlPsdTracedCallback)
      (Ptr<SpectrumValue> psd);

 private:
  CdlType m_cdlType;
  TracedCallback<Ptr<SpectrumValue>> m_psdReceived;
  TracedCallback<Ptr<SpectrumValue>> m_psdCalculated;
  static std::map<std::tuple<Ptr<const MobilityModel>, Ptr<const MobilityModel>>,CdlCommon> cdlInstances;

};

}

#endif //CDL_SPECTRUMPROPAGATION_LOSS_H_
