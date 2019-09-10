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

#ifndef QOS_UTILS_H
#define QOS_UTILS_H

#include "ns3/ptr.h"

namespace ns3 {

class Packet;
class WifiMacHeader;
class QueueItem;

/**
 * \ingroup wifi
 * This enumeration defines the Access Categories as an enumeration
 * with values corresponding to the AC index (ACI) values specified
 * (Table 8-104 "ACI-to-AC coding"; IEEE 802.11-2012).
 */
enum AcIndex
{
  /** Best Effort */
  AC_BE = 0,
  /** Background */
  AC_BK = 1,
  /** Video */
  AC_VI = 2,
  /** Voice */
  AC_VO = 3,
  /** Total number of ACs */
  AC_BE_NQOS = 4,
  AC_UNDEF
};

/**
 * \ingroup wifi
 * Maps TID (Traffic ID) to Access classes.
 * For more details see (Table 9-1 "UP-to-AC mapping"; IEEE 802.11-2012).
 *
 * \param tid the Traffic ID to be mapped to Access class
 * \return the access class for the given TID
 */
AcIndex QosUtilsMapTidToAc (uint8_t tid);

/**
 * \ingroup wifi
 * If a qos tag is attached to the packet, returns a value < 8.
 * A value >= 8 is returned otherwise.
 *
 * \param packet the packet to checked for a QoS tag
 *
 * \return a value less than 8 if QoS tag was present, a value >= 8
 *         is returned if no QoS tag was present
 */
uint8_t QosUtilsGetTidForPacket (Ptr<const Packet> packet);

/**
 * \ingroup wifi
 * Next function is useful to correctly sort buffered packets under block ack.
 * When an BAR is received from originator station, completed "old"
 * (see section 9.10.3 in IEEE 802.11e) packets must be forwarded up before "new" packets.
 *
 * \param seqControl the sequence control field
 * \param endSequence
 *
 * \return a unique integer for the given sequence control and end sequence
 */
uint32_t QosUtilsMapSeqControlToUniqueInteger (uint16_t seqControl, uint16_t endSequence);

/**
 * \ingroup wifi
 * This function checks if packet with sequence number <i>seqNumber</i> is an "old" packet.
 * The sequence number space is considered divided into two parts, one of which is "old" and
 * one of which is "new" by means of a boundary created by adding half the sequence number
 * range to the starting sequence number <i>startingSeq</i>. So this function works fine also
 * when <i>seqNumber</i> is smaller than <i>startingSeq</i> and <i>startingSeq</i> + 2048 is greater
 * than 4096 because all comparison are circular modulo 2^12. The following are possible scenarios:
 *
 * ----- = old packets
 * +++++ = new packets
 *
 *  CASE A:
 *
 *    0                             4095
 *    |++++++|----------------|++++++|
 *           ^                ^
 *           | endSeq         | startingSeq
 *
 *
 *  CASE B:
 *
 *    0                            4095
 *    |------|++++++++++++++++|-----|
 *           ^                ^
 *           | startingSeq    | endSeq
 *
 * Here in the examples endSeq is the sequenceNumber of the "last" new packet.
 * So this function, when specified a starting sequence and a sequence number, returns true
 * if that packet (with sequence number <i>numberSeq</i>)) belongs to the section of the
 * sequence number space marked with '-' characters. The function returns false otherwise.
 *
 * \param startingSeq the starting sequence number
 * \param seqNumber the sequence number to be checked
 *
 * \return true if the packet is old, false otherwise
 */
bool QosUtilsIsOldPacket (uint16_t startingSeq, uint16_t seqNumber);

/**
 * \ingroup wifi
 * Next function is useful to get traffic id of different packet types.
 *
 * \param packet packet to check
 * \param hdr 802.11 header for packet to check
 *
 * Returns Tid of different packet types
 */
uint8_t GetTid (Ptr<const Packet> packet, const WifiMacHeader hdr);

  /**
   * \ingroup wifi
   * \brief Determine the tx queue for a given packet
   * \param item the packet
   * \returns the access category
   *
   * Modelled after the Linux function ieee80211_select_queue (net/mac80211/wme.c).
   * A SocketPriority tag is attached to the packet (or the existing one is
   * replaced) to carry the user priority, which is set to the three most
   * significant bits of the DS field (TOS field in case of IPv4 and Traffic
   * Class field in case of IPv6). The Access Category corresponding to the
   * user priority according to the QosUtilsMapTidToAc function is returned.
   *
   * The following table shows the mapping for the Diffserv Per Hop Behaviors.
   *
   * PHB  | TOS (binary) | UP  | Access Category
   * -----|--------------|-----|-----------------
   * EF   |   101110xx   |  5  |     AC_VI
   * AF11 |   001010xx   |  1  |     AC_BK
   * AF21 |   010010xx   |  2  |     AC_BK
   * AF31 |   011010xx   |  3  |     AC_BE
   * AF41 |   100010xx   |  4  |     AC_VI
   * AF12 |   001100xx   |  1  |     AC_BK
   * AF22 |   010100xx   |  2  |     AC_BK
   * AF32 |   011100xx   |  3  |     AC_BE
   * AF42 |   100100xx   |  4  |     AC_VI
   * AF13 |   001110xx   |  1  |     AC_BK
   * AF23 |   010110xx   |  2  |     AC_BK
   * AF33 |   011110xx   |  3  |     AC_BE
   * AF43 |   100110xx   |  4  |     AC_VI
   * CS0  |   000000xx   |  0  |     AC_BE
   * CS1  |   001000xx   |  1  |     AC_BK
   * CS2  |   010000xx   |  2  |     AC_BK
   * CS3  |   011000xx   |  3  |     AC_BE
   * CS4  |   100000xx   |  4  |     AC_VI
   * CS5  |   101000xx   |  5  |     AC_VI
   * CS6  |   110000xx   |  6  |     AC_VO
   * CS7  |   111000xx   |  7  |     AC_VO
   *
   * This method is called by the traffic control layer before enqueuing a
   * packet in the queue disc, if a queue disc is installed on the outgoing
   * device, or passing a packet to the device, otherwise.
   */
  uint8_t SelectQueueByDSField (Ptr<QueueItem> item);

} //namespace ns3

#endif /* QOS_UTILS_H */
