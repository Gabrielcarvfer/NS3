/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 University of Washington
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
 * Author: Leonard Tracy <lentracy@gmail.com>
 */

#ifndef UAN_MAC_H
#define UAN_MAC_H

#include "ns3/address.h"
#include "ns3/object.h"
#include "ns3/packet.h"

#include "ns3/address.h"
#include "ns3/nstime.h"
#include "ns3/ptr.h"

namespace ns3 {

class UanPhy;
class UanChannel;
class UanNetDevice;
class UanTransducer;
class UanTxMode;
class UanAddress;



/**
 * \ingroup uan
 *
 * Virtual base class for all UAN MAC protocols.
 */
class UanMac : public Object
{
public:
  /**
   * Register this type.
   * \return The TypeId.
   */
   static TypeId GetTypeId (void);

  /**
   * Get the MAC Address.
   *
   * \return MAC Address.
   */
  virtual Address GetAddress (void) = 0;

  /**
   * Set the address.
   *
   * \param addr UanAddress for this MAC.
   */
  virtual void SetAddress (UanAddress addr) = 0;

  /**
   * Enqueue packet to be transmitted.
   *
   * \param pkt Packet to be transmitted.
   * \param dest Destination address.
   * \param protocolNumber Protocol number.  Usage varies by MAC.
   * \return True if packet was successfully enqueued.
   */
  virtual bool Enqueue (Ptr<Packet> pkt, const Address &dest, uint16_t protocolNumber) = 0;
  /**
   * Set the callback to forward packets up to higher layers.
   * 
   * \param cb The callback.
   * \pname{packet} The packet.
   * \pname{address} The source address.
   */
  virtual void SetForwardUpCb (Callback<void, Ptr<Packet>, const UanAddress&> cb) = 0;

  /**
   * Attach PHY layer to this MAC.
   *
   * Some MACs may be designed to work with multiple PHY
   * layers.  Others may only work with one.
   *
   * \param phy Phy layer to attach to this MAC.
   */
  virtual void AttachPhy (Ptr<UanPhy> phy) = 0;

  /**
   * Get the broadcast address.
   *
   * \return The broadcast address.
   */
  virtual Address GetBroadcast (void) const = 0;

  /** Clears all pointer references. */
  virtual void Clear (void) = 0;

 /**
  * Assign a fixed random variable stream number to the random variables
  * used by this model.  Return the number of streams (possibly zero) that
  * have been assigned.
  *
  * \param stream First stream index to use.
  * \return The number of stream indices assigned by this model.
  */
  virtual int64_t AssignStreams (int64_t stream) = 0;

  /**
   *  TracedCallback signature for packet reception/enqueue/dequeue events.
   *
   * \param [in] packet The Packet.
   * \param [in] mode The UanTxMode.
   */
  typedef void (* PacketModeTracedCallback)
    (Ptr<const Packet> packet, UanTxMode mode);

};  // class UanMac

} // namespace ns3

#endif /* UAN_MAC_H */
