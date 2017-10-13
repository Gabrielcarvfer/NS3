/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2013
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
 * Author: Ghada Badawy <gbadawy@gmail.com>
 */

#ifndef MPDU_STANDARD_AGGREGATOR_H
#define MPDU_STANDARD_AGGREGATOR_H

#include "mpdu-aggregator.h"

namespace ns3 {

/**
 * \ingroup wifi
 * Standard MPDU aggregator
 *
 */
class MpduStandardAggregator : public MpduAggregator
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);
  MpduStandardAggregator ();
  ~MpduStandardAggregator ();

  /**
   * Sets the maximum A-MPDU size in bytes.
   * Value 0 means that MPDU aggregation is disabled.
   *
   * \param maxSize the maximum A-MPDU size in bytes.
   */
  void SetMaxAmpduSize (uint32_t maxSize);
  /**
   * Returns the maximum A-MPDU size in bytes.
   * Value 0 means that MPDU aggregation is disabled.
   *
   * \return the maximum A-MPDU size in bytes.
   */
  uint32_t GetMaxAmpduSize (void) const;
  /**
   * \param packet packet we have to insert into <i>aggregatedPacket</i>.
   * \param aggregatedPacket packet that will contain <i>packet</i>, if aggregation is possible.
   *
   * \return true if <i>packet</i> can be aggregated to <i>aggregatedPacket</i>,
   *         false otherwise.
   *
   * This method performs an MPDU aggregation.
   * Returns true if <i>packet</i> can be aggregated to <i>aggregatedPacket</i>, false otherwise.
   */
  bool Aggregate (Ptr<const Packet> packet, Ptr<Packet> aggregatedPacket) const;
  /**
   * \param packet the packet we want to insert into <i>aggregatedPacket</i>.
   * \param aggregatedPacket packet that will contain the packet of size <i>packetSize</i>, if aggregation is possible.
   *
   * This method performs a VHT/HE single MPDU aggregation.
   */
  void AggregateSingleMpdu (Ptr<const Packet> packet, Ptr<Packet> aggregatedPacket) const;
  /**
   * \param packet the packet we want to insert into <i>aggregatedPacket</i>.
   * \param last true if it is the last packet.
   * \param isSingleMpdu true if it is a single MPDU
   *
   * Adds A-MPDU subframe header and padding to each MPDU that is part of an A-MPDU before it is sent.
   */
  void AddHeaderAndPad (Ptr<Packet> packet, bool last, bool isSingleMpdu) const;
  /**
   * \param packetSize size of the packet we want to insert into <i>aggregatedPacket</i>.
   * \param aggregatedPacket packet that will contain the packet of size <i>packetSize</i>, if aggregation is possible.
   * \param blockAckSize size of the piggybacked block ack request
   *
   * \return true if the packet of size <i>packetSize</i> can be aggregated to <i>aggregatedPacket</i>,
   *         false otherwise.
   *
   * This method is used to determine if a packet could be aggregated to an A-MPDU without exceeding the maximum packet size.
   */
  bool CanBeAggregated (uint32_t packetSize, Ptr<Packet> aggregatedPacket, uint8_t blockAckSize) const;
  /**
   * \param packet the packet
   * \return the padding that must be added to the end of an aggregated packet
   *
   * Calculates how much padding must be added to the end of an aggregated packet, after that a new packet is added.
   * Each A-MPDU subframe is padded so that its length is multiple of 4 octets.
   */
  uint32_t CalculatePadding (Ptr<const Packet> packet) const;


private:
  uint32_t m_maxAmpduLength; //!< Maximum length in bytes of A-MPDUs
};

} //namespace ns3

#endif /* MPDU_STANDARD_AGGREGATOR_H */
