/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2005 INRIA
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

#pragma once

#include <map>
#include "../../core/model/simple-ref-count.h"
#include "../../core/model/callback.h"

namespace ns3 {

class WifiMacHeader;
class OriginatorRxStatus;
class Packet;
class Mac48Address;

/**
 * \ingroup wifi
 *
 * This class handles duplicate detection and recomposition of fragments.
 */
class MacRxMiddle : public SimpleRefCount<MacRxMiddle>
{
public:
  /**
   * typedef for callback
   */
  typedef Callback<void, Ptr<Packet>, const WifiMacHeader*> ForwardUpCallback;

  MacRxMiddle ();
  ~MacRxMiddle ();

  /**
   * Set a callback to forward the packet up.
   *
   * \param callback
   */
  void SetForwardCallback (ForwardUpCallback callback);

  /**
   * Set a callback to trigger the next PCF frame.
   *
   * \param callback
   */
  void SetPcfCallback (Callback<void> callback);

  /**
   * Receive a packet.
   *
   * \param packet the packet
   * \param hdr MAC header
   */
  void Receive (Ptr<Packet> packet, const WifiMacHeader *hdr);


private:
  /// allow MacRxMiddleTest associated class access
  friend class MacRxMiddleTest;
  /**
   * Look up for OriginatorRxStatus associated with the sender address
   * (by looking at ADDR2 field in the header).
   * The method creates a new OriginatorRxStatus if one is not already presented.
   *
   * \param hdr
   *
   * \return OriginatorRxStatus
   */
  OriginatorRxStatus* Lookup (const WifiMacHeader* hdr);
  /**
   * Check if we have already received the packet from the sender before
   * (by looking at the sequence control field).
   *
   * \param hdr
   * \param originator
   *
   * \return true if we already received the packet previously,
   *         false otherwise
   */
  bool IsDuplicate (const WifiMacHeader* hdr, OriginatorRxStatus *originator) const;
  /**
   * Check if the received packet is a fragment and handle it appropriately.
   * If the packet is not a fragment, the method returns the packet.
   * If the packet is a fragment (not the last fragment), the method initiates
   * de-fragmentation process and return 0.
   * If the packet is the last fragment, the method tries to re-construct the full packet
   * and return the packet if success.
   *
   * \param packet
   * \param hdr
   * \param originator
   *
   * \return a packet if the packet is successfully reassembled (or not a fragment),
   *         0 if we failed to reassemble the packet (e.g. missing fragments/out-of-order).
   */
  Ptr<Packet> HandleFragments (Ptr<Packet> packet, const WifiMacHeader* hdr,
                               OriginatorRxStatus *originator);

  /**
   * typedef for a map between address and OriginatorRxStatus
   */
  typedef std::map <Mac48Address, OriginatorRxStatus *, std::less<Mac48Address> > Originators;
  /**
   * typedef for a map between address, OriginatorRxStatus, and Traffic ID
   */
  typedef std::map <std::pair<Mac48Address, uint8_t>, OriginatorRxStatus *, std::less<std::pair<Mac48Address,uint8_t> > > QosOriginators;
  /**
   * typedef for an iterator for Originators
   */
  typedef std::map <Mac48Address, OriginatorRxStatus *, std::less<Mac48Address> >::iterator OriginatorsI;
  /**
   * typedef for an iterator for QosOriginators
   */
  typedef std::map <std::pair<Mac48Address, uint8_t>, OriginatorRxStatus *, std::less<std::pair<Mac48Address,uint8_t> > >::iterator QosOriginatorsI;

  Originators m_originatorStatus; ///< originator status
  QosOriginators m_qosOriginatorStatus; ///< QOS originator status
  ForwardUpCallback m_callback; ///< forward up callback

  Callback<void> m_pcfCallback; //!< PCF callback
};

} //namespace ns3


