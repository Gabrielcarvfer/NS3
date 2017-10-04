/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 *  Copyright (c) 2007,2008, 2009 INRIA, UDcast
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
 *         Mohamed Amine Ismail <amine.ismail@sophia.inria.fr>
 *
 */

#ifndef IPCS_CLASSIFIER_RECORD_H
#define IPCS_CLASSIFIER_RECORD_H

#include <stdint.h>
#include "ns3/ipv4-address.h"
#include "wimax-tlv.h"

namespace ns3 {

/**
 * \ingroup wimax
 */
class IpcsClassifierRecord
{
public:
  IpcsClassifierRecord ();
  ~IpcsClassifierRecord ();
  /**
   * \brief creates a classifier records and sets all its parameters
   * \param srcAddress the source ip address
   * \param srcMask the mask to apply on the source ip address
   * \param dstAddress the destination ip address
   * \param dstMask the mask to apply on the destination ip address
   * \param srcPortLow the lower boundary of the source port range
   * \param srcPortHigh the higher boundary of the source port range
   * \param dstPortLow the lower boundary of the destination port range
   * \param dstPortHigh the higher boundary of the destination port range
   * \param protocol the L4 protocol
   * \param priority the priority of this classifier
   *
   */
  IpcsClassifierRecord (Ipv4Address srcAddress, Ipv4Mask srcMask,
                        Ipv4Address dstAddress, Ipv4Mask dstMask,
                        uint16_t srcPortLow, uint16_t srcPortHigh,
                        uint16_t dstPortLow, uint16_t dstPortHigh,
                        uint8_t protocol,
                        uint8_t priority);
  /**
   * \brief Decodes a TLV and creates a classifier
   * \param tlv the TLV to decode and from which the classifier parameters will be extracted
   */
  IpcsClassifierRecord (Tlv tlv);
  /**
   * \brief Creates a TLV from this classifier
   * \return the created TLV
   */
  Tlv ToTlv (void) const;
  /**
   * \brief add a new source ip address to the classifier
   * \param srcAddress the source ip address
   * \param srcMask the mask to apply on the source ip address
   */
  void AddSrcAddr (Ipv4Address srcAddress, Ipv4Mask srcMask);
  /**
    * \brief add a new destination ip address to the classifier
    * \param dstAddress the destination ip address
    * \param dstMask the mask to apply on the destination ip address
    */
  void AddDstAddr (Ipv4Address dstAddress, Ipv4Mask dstMask);
  /**
   * \brief add a range of source port to the classifier
   * \param srcPortLow the lower boundary of the source port range
   * \param srcPortHigh the higher boundary of the source port range
   */
  void AddSrcPortRange ( uint16_t srcPortLow, uint16_t srcPortHigh);
  /**
   * \brief add a range of destination port to the classifier
   * \param dstPortLow the lower boundary of the destination port range
   * \param dstPortHigh the higher boundary of the destination port range
   */
  void AddDstPortRange ( uint16_t dstPortLow, uint16_t dstPortHigh);
  /**
   * \brief add a protocol to the classifier
   * \param proto the L4 protocol to add
   */
  void AddProtocol (uint8_t proto);
  /**
   * \brief Set the priority of this classifier
   * \param prio the priority of the classifier
   */
  void SetPriority (uint8_t prio);
  /**
   * \brief Set the index of the classifier
   * \param index the index of the classifier
   */
  void SetIndex (uint16_t index);
  /**
   * \brief check if a packets can be used with this classifier
   * \param srcAddress the source ip address of the packet
   * \param dstAddress the destination ip address of the packet
   * \param srcPort the source port of the packet
   * \param dstPort the destination port of the packet
   * \param proto The L4 protocol of the packet
   */
  bool CheckMatch (Ipv4Address srcAddress, Ipv4Address dstAddress,
                   uint16_t srcPort, uint16_t dstPort,
                   uint8_t proto) const;
  /**
   * \return the cid associated with this classifier
   */
  uint16_t GetCid (void) const;
  /**
   * \return the priority of this classifier
   */
  uint8_t GetPriority (void) const;
  /**
   * \return the index of this classifier
   */
  uint16_t GetIndex (void) const;
  /**
   * \brief Set the cid associated to this classifier
   * \param cid the connection identifier
   */
  void SetCid (uint16_t cid);


private:
  bool CheckMatchSrcAddr (Ipv4Address srcAddress) const;
  bool CheckMatchDstAddr (Ipv4Address dstAddress) const;
  bool CheckMatchSrcPort (uint16_t srcPort) const;
  bool CheckMatchDstPort (uint16_t dstPort) const;
  bool CheckMatchProtocol (uint8_t proto) const;
  struct PortRange
  {
    uint16_t PortLow;
    uint16_t PortHigh;
  };
  struct ipv4Addr
  {
    Ipv4Address Address;
    Ipv4Mask Mask;
  };

  uint8_t m_priority;
  uint16_t m_index;
  uint8_t m_tosLow;
  uint8_t m_tosHigh;
  uint8_t m_tosMask;
  std::vector<uint8_t> m_protocol;
  std::vector<struct ipv4Addr> m_srcAddr;
  std::vector<struct ipv4Addr> m_dstAddr;
  std::vector<struct PortRange> m_srcPortRange;
  std::vector<struct PortRange> m_dstPortRange;

  uint16_t m_cid;
};
} // namespace ns3

#endif /* IPCS_CLASSIFIER_RECORD_H */
