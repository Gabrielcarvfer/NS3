/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 CTTC
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
 * Author: Nicola Baldo <nbaldo@cttc.es>
 */

#pragma once


#include "spectrum-channel.h"
#include "spectrum-model.h"
#include "../../core/model/traced-callback.h"

namespace ns3 {



/**
 * \ingroup spectrum
 *
 * \brief SpectrumChannel implementation which handles a single spectrum model
 *
 * All SpectrumPhy layers attached to this SpectrumChannel
 */
class SingleModelSpectrumChannel : public SpectrumChannel
{

public:
  SingleModelSpectrumChannel ();

  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);

  // inherited from SpectrumChannel
  virtual void AddRx (Ptr<SpectrumPhy> phy);
  virtual void StartTx (Ptr<SpectrumSignalParameters> params);


  // inherited from Channel
  virtual std::size_t GetNDevices (void) const;
  virtual Ptr<NetDevice> GetDevice (std::size_t i) const;

  /// Container: SpectrumPhy objects
  typedef std::vector<Ptr<SpectrumPhy> > PhyList;

private:
  virtual void DoDispose ();

  /**
   * Used internally to reschedule transmission after the propagation delay.
   *
   * \param params
   * \param receiver
   */
  void StartRx (Ptr<SpectrumSignalParameters> params, Ptr<SpectrumPhy> receiver);

  /**
   * List of SpectrumPhy instances attached to the channel.
   */
  PhyList m_phyList;

  /**
   * SpectrumModel that this channel instance is supporting.
   */
  Ptr<const SpectrumModel> m_spectrumModel;

};

}


