/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 MIRKO BANCHI
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
 * Author: Mirko Banchi <mk.banchi@gmail.com>
 */

#ifndef MSDU_AGGREGATOR_H
#define MSDU_AGGREGATOR_H

#include "ns3/packet.h"
#include "ns3/object.h"
#include "amsdu-subframe-header.h"

namespace ns3 {

class WifiMacHeader;

/**
 * \brief Aggregator used to construct A-MSDUs
 * \ingroup wifi
 */
class MsduAggregator : public Object
{
public:
  /// DeaggregatedMsdus typedef
  typedef std::list<std::pair<Ptr<Packet>, AmsduSubframeHeader> > DeaggregatedMsdus;
  /// DeaggregatedMsdusCI typedef
  typedef std::list<std::pair<Ptr<Packet>, AmsduSubframeHeader> >::const_iterator DeaggregatedMsdusCI;

  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);

  MsduAggregator ();
  virtual ~MsduAggregator ();

  /**
   * Sets the maximum A-MSDU size in bytes.
   * Value 0 means that MSDU aggregation is disabled.
   *
   * \param maxSize the maximum A-MSDU size in bytes.
   */
  void SetMaxAmsduSize (uint16_t maxSize);
  /**
   * Returns the maximum A-MSDU size in bytes.
   * Value 0 means that MSDU aggregation is disabled.
   *
   * \return the maximum A-MSDU size in bytes.
   */
  uint16_t GetMaxAmsduSize (void) const;

  /**
   * Adds <i>packet</i> to <i>aggregatedPacket</i>. In concrete aggregator's implementation is
   * specified how and if <i>packet</i> can be added to <i>aggregatedPacket</i>. If <i>packet</i>
   * can be added returns true, false otherwise.
   *
   * \param packet the packet.
   * \param aggregatedPacket the aggregated packet.
   * \param src the source address.
   * \param dest the destination address
   * \return true if successful.
   */
  bool Aggregate (Ptr<const Packet> packet, Ptr<Packet> aggregatedPacket,
                  Mac48Address src, Mac48Address dest) const;

  /**
   *
   * \param aggregatedPacket the aggregated packet.
   * \returns DeaggregatedMsdus.
   */
  static DeaggregatedMsdus Deaggregate (Ptr<Packet> aggregatedPacket);


private:
  /**
   * Calculates how much padding must be added to the end of aggregated packet,
   * after that a new packet is added.
   * Each A-MSDU subframe is padded so that its length is multiple of 4 octets.
   *
   * \param packet
   *
   * \return the number of octets required for padding
   */
  uint8_t CalculatePadding (Ptr<const Packet> packet) const;

  uint16_t m_maxAmsduLength; ///< maximum AMSDU length
};

} //namespace ns3

#endif /* MSDU_AGGREGATOR_H */
