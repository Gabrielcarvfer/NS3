/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2006 INRIA
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

#ifndef SSID_H
#define SSID_H

#include "wifi-information-element.h"

namespace ns3 {

/**
 * \ingroup wifi
 *
 * The IEEE 802.11 SSID Information Element
 *
 * \see attribute_Ssid
 */
class Ssid : public WifiInformationElement
{
public:
  // broadcast ssid
  Ssid ();
  /**
   * Create SSID from a given string
   *
   * \param s SSID in string
   */
  Ssid (std::string s);

  /**
   * Check if the two SSIDs are equal.
   *
   * \param o SSID to compare to
   *
   * \return true if the two SSIDs are equal,
   *         false otherwise
   */
  bool IsEqual (const Ssid& o) const;
  /**
   * Check if the SSID is broadcast.
   *
   * \return true if the SSID is broadcast,
   *         false otherwise
   */
  bool IsBroadcast (void) const;

  /**
   * Peek the SSID.
   *
   * \return a pointer to SSID string
   */
  char* PeekString (void) const;

  /**
   * Get the ElementID.
   *
   * \returns the element ID
   */
  WifiInformationElementId ElementId () const;

  /**
   * Get the information field size.
   *
   * \returns the information field size
   */
  uint8_t GetInformationFieldSize () const;

  /**
   * Get the information field size.
   *
   * \param start the information field iterator
   */
  void SerializeInformationField (Buffer::Iterator start) const;

  /**
   * Get the information field size.
   *
   * \param start the information field iterator
   * \param length the size of the information field
   * \returns the size of the field read
   */
  uint8_t DeserializeInformationField (Buffer::Iterator start,
                                       uint8_t length);

private:
  uint8_t m_ssid[33]; //!< Raw SSID value
  uint8_t m_length;   //!< Length of the SSID
};

std::ostream &operator << (std::ostream &os, const Ssid &ssid);
std::istream &operator >> (std::istream &is, Ssid &ssid);

ATTRIBUTE_HELPER_HEADER (Ssid);

} //namespace ns3

#endif /* SSID_H */
