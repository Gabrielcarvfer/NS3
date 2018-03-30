/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2005,2006 INRIA
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
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 */

#ifndef ERROR_RATE_MODEL_H
#define ERROR_RATE_MODEL_H

#include "wifi-tx-vector.h"
#include "ns3/object.h"

namespace ns3 {
/**
 * \ingroup wifi
 * \brief the interface for Wifi's error models
 *
 */
class ErrorRateModel : public Object
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);

  /**
   * \param txVector a specific transmission vector including WifiMode
   * \param ber a target ber
   *
   * \return the snr which corresponds to the requested ber
   */
  double CalculateSnr (WifiTxVector txVector, double ber) const;

  /**
   * A pure virtual method that must be implemented in the subclass.
   * This method returns the probability that the given 'chunk' of the
   * packet will be successfully received by the PHY.
   *
   * A chunk can be viewed as a part of a packet with equal SNR.
   * The probability of successfully receiving the chunk depends on
   * the mode, the SNR, and the size of the chunk.
   *
   * Note that both a WifiMode and a WifiTxVector (which contains a WifiMode)
   * are passed into this method.  The WifiTxVector may be from a signal that
   * contains multiple modes (e.g. PLCP header sent differently from PLCP
   * payload).  Consequently, the mode parameter is what the method uses
   * to calculate the chunk error rate, and the txVector is used for
   * other information as needed.
   *
   * \param mode the Wi-Fi mode applicable to this chunk
   * \param txVector TXVECTOR of the overall transmission
   * \param snr the SNR of the chunk
   * \param nbits the number of bits in this chunk
   *
   * \return probability of successfully receiving the chunk
   */
  virtual double GetChunkSuccessRate (WifiMode mode, WifiTxVector txVector, double snr, uint64_t nbits) const = 0;
};

} //namespace ns3

#endif /* ERROR_RATE_MODEL_H */

