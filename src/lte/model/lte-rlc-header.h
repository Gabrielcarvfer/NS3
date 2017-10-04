/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011 Centre Tecnologic de Telecomunicacions de Catalunya (CTTC)
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
 * Author: Manuel Requena <manuel.requena@cttc.es>
 */

#ifndef LTE_RLC_HEADER_H
#define LTE_RLC_HEADER_H

#include "ns3/header.h"
#include "ns3/lte-rlc-sequence-number.h"

#include <list>

namespace ns3 {

/**
 * \ingroup lte
 * \brief The packet header for the Radio Link Control (RLC) protocol packets
 *
 * This class has fields corresponding to those in an RLC header as well as
 * methods for serialization to and deserialization from a byte buffer.
 * It follows 3GPP TS 36.322 Radio Link Control (RLC) protocol specification.
 */
class LteRlcHeader : public Header
{
public:

  /**
   * \brief Constructor
   *
   * Creates a null header
   */
  LteRlcHeader ();
  ~LteRlcHeader ();

  void SetFramingInfo (uint8_t framingInfo);
  void SetSequenceNumber (SequenceNumber10 sequenceNumber);

  uint8_t GetFramingInfo () const;
  SequenceNumber10 GetSequenceNumber () const;

  void PushExtensionBit (uint8_t extensionBit);
  void PushLengthIndicator (uint16_t lengthIndicator);

  uint8_t PopExtensionBit (void);
  uint16_t PopLengthIndicator (void);

  typedef enum {
    DATA_FIELD_FOLLOWS  = 0,
    E_LI_FIELDS_FOLLOWS = 1
  } ExtensionBit_t;

  typedef enum {
    FIRST_BYTE    = 0x00,
    NO_FIRST_BYTE = 0x02
  } FramingInfoFirstByte_t;

  typedef enum {
    LAST_BYTE    = 0x00,
    NO_LAST_BYTE = 0x01
  } FramingInfoLastByte_t;


  static TypeId GetTypeId (void);
  virtual TypeId GetInstanceTypeId (void) const;
  virtual void Print (std::ostream &os) const;
  virtual uint32_t GetSerializedSize (void) const;
  virtual void Serialize (Buffer::Iterator start) const;
  virtual uint32_t Deserialize (Buffer::Iterator start);

private:
  uint16_t m_headerLength;
  uint8_t  m_framingInfo;      //  2 bits
  SequenceNumber10 m_sequenceNumber;

  std::list <uint8_t> m_extensionBits; // Includes extensionBit of the fixed part
  std::list <uint16_t> m_lengthIndicators;

};

}; // namespace ns3

#endif // LTE_RLC_HEADER_H
