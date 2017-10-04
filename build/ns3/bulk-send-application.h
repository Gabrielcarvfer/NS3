/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010 Georgia Institute of Technology
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
 * Author: George F. Riley <riley@ece.gatech.edu>
 */

#ifndef BULK_SEND_APPLICATION_H
#define BULK_SEND_APPLICATION_H

#include "ns3/address.h"
#include "ns3/application.h"
#include "ns3/event-id.h"
#include "ns3/ptr.h"
#include "ns3/traced-callback.h"

namespace ns3 {

class Address;
class Socket;

/**
 * \ingroup applications
 * \defgroup bulksend BulkSendApplication
 *
 * This traffic generator simply sends data
 * as fast as possible up to MaxBytes or until
 * the application is stopped (if MaxBytes is
 * zero). Once the lower layer send buffer is
 * filled, it waits until space is free to
 * send more data, essentially keeping a
 * constant flow of data. Only SOCK_STREAM 
 * and SOCK_SEQPACKET sockets are supported. 
 * For example, TCP sockets can be used, but 
 * UDP sockets can not be used.
 */

/**
 * \ingroup bulksend
 *
 * \brief Send as much traffic as possible, trying to fill the bandwidth.
 *
 * This traffic generator simply sends data
 * as fast as possible up to MaxBytes or until
 * the application is stopped (if MaxBytes is
 * zero). Once the lower layer send buffer is
 * filled, it waits until space is free to
 * send more data, essentially keeping a
 * constant flow of data. Only SOCK_STREAM
 * and SOCK_SEQPACKET sockets are supported.
 * For example, TCP sockets can be used, but
 * UDP sockets can not be used.
 *
 */
class BulkSendApplication : public Application
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);

  BulkSendApplication ();

  virtual ~BulkSendApplication ();

  /**
   * \brief Set the upper bound for the total number of bytes to send.
   *
   * Once this bound is reached, no more application bytes are sent. If the
   * application is stopped during the simulation and restarted, the 
   * total number of bytes sent is not reset; however, the maxBytes 
   * bound is still effective and the application will continue sending 
   * up to maxBytes. The value zero for maxBytes means that 
   * there is no upper bound; i.e. data is sent until the application 
   * or simulation is stopped.
   *
   * \param maxBytes the upper bound of bytes to send
   */
  void SetMaxBytes (uint64_t maxBytes);

  /**
   * \brief Get the socket this application is attached to.
   * \return pointer to associated socket
   */
  Ptr<Socket> GetSocket (void) const;

protected:
  virtual void DoDispose (void);
private:
  // inherited from Application base class.
  virtual void StartApplication (void);    // Called at time specified by Start
  virtual void StopApplication (void);     // Called at time specified by Stop

  /**
   * \brief Send data until the L4 transmission buffer is full.
   */
  void SendData ();

  Ptr<Socket>     m_socket;       //!< Associated socket
  Address         m_peer;         //!< Peer address
  bool            m_connected;    //!< True if connected
  uint32_t        m_sendSize;     //!< Size of data to send each time
  uint64_t        m_maxBytes;     //!< Limit total number of bytes sent
  uint64_t        m_totBytes;     //!< Total bytes sent so far
  TypeId          m_tid;          //!< The type of protocol to use.

  /// Traced Callback: sent packets
  TracedCallback<Ptr<const Packet> > m_txTrace;

private:
  /**
   * \brief Connection Succeeded (called by Socket through a callback)
   * \param socket the connected socket
   */
  void ConnectionSucceeded (Ptr<Socket> socket);
  /**
   * \brief Connection Failed (called by Socket through a callback)
   * \param socket the connected socket
   */
  void ConnectionFailed (Ptr<Socket> socket);
  /**
   * \brief Send more data as soon as some has been transmitted.
   */
  void DataSend (Ptr<Socket>, uint32_t); // for socket's SetSendCallback
};

} // namespace ns3

#endif /* BULK_SEND_APPLICATION_H */
