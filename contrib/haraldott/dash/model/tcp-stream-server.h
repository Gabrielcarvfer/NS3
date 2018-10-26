/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright 2016 Technische Universitaet Berlin
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
 */

#ifndef TCP_STREAM_SERVER_H
#define TCP_STREAM_SERVER_H

#include "ns3/application.h"
#include "ns3/event-id.h"
#include "ns3/ptr.h"
#include "ns3/address.h"
#include "ns3/traced-callback.h"
#include <map>
#include "ns3/random-variable-stream.h"

namespace ns3 {



class Socket;
class Packet;
class PropagationDelayModel;

/**
 * \ingroup applications
 * \defgroup tcpStream TcpStream
 */

/**
 * \ingroup tcpStream
 * \brief data strucute the server uses to manage the following data for every client separately.
 */
struct callbackData
{
  uint32_t currentTxBytes;//!< already sent bytes for this particular segment, set to 0 if sent bytes == packetSizeToReturn, so transmission for this segment is over
  uint32_t packetSizeToReturn;//!< total amount of bytes that have to be returned to the client
  bool send;//!< true as long as there are still bytes left to be sent for the current segment
};

/**
 * \ingroup tcpStream
 * \brief A Tcp Stream server
 *
 * Clients sent messages with the amount of bytes they want the server to return to them.
 */
class TcpStreamServer : public Application
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);
  TcpStreamServer ();
  virtual ~TcpStreamServer ();

protected:
  virtual void DoDispose (void);

private:
  virtual void StartApplication (void);
  virtual void StopApplication (void);

  /**
   * \brief Handle a packet reception, and set SendCallback to HandlSend.
   *
   * This function is called by lower layers. The received packet's content
   * gets deserialized by GetCommand (Ptr<Packet> packet). If the packets content
   * contains a string composed of an int with
   * value n, then n bytes will be sent back to the sender.
   *
   * \param socket the socket the packet was received to.
   */
  void HandleRead (Ptr<Socket> socket);

  /**
   * \brief send packetSizeToReturn bytes to the client connected to socket.
   *
   * This function is called once by HandleRead (Ptr<Socket> socket) after a send of n (i.e.
   * a segment of n) bytes was requested by the client. If n > socket->GetTxAvailable (),
   * (this is the current space available in the buffer in bytes), then socket->GetTxAvailable () bytes
   * are written into the buffer. This function will get called again through the SendCallback when
   * space in the buffer has freed up.
   * The amount of sent bytes for this particular segment and for the client connected with
   * this socket is stored in m_callbackData [from].currentTxBytes, so the server can access the already sent bytes
   * through the value of from, which is provided by socket, because there is a socket instance for every connected client.
   * m_callbackData [from].send indicates for the client with address from that the server has not yet sent
   * m_callbackData [from].packetSizeToReturn bytes. When the number of bytes should be sent is
   * reached, m_callbackData [from].send will be set to false and the server stops sending
   * bytes to the client until he requests another segment.
   *
   * \param socket the socket the request for a segment was received to and where the server will send packetSizeToReturn bytes to.
   * \param packetSizeToReturn the full segment size in bytes that has to be returned to the client
   */
  void HandleSend (Ptr<Socket> socket, uint32_t packetSizeToReturn);

  /**
   * \brief Set callback functions for receive and send.
   * Add the newly connected client to m_connectedClients and allocate callbackData structure for this client.
   */
  void HandleAccept (Ptr<Socket> s, const Address& from);

  void HandlePeerClose (Ptr<Socket> socket);
  void HandlePeerError (Ptr<Socket> socket);

  /**
   * \brief Deserialize what the client has sent us.
   * \param packet the data the client has sent us
   * \return the deserialized packet content as a string
   */
  int64_t GetCommand (Ptr<Packet> packet);

  uint16_t m_port; //!< Port on which we listen for incoming packets.
  Ptr<Socket> m_socket; //!< IPv4 Socket
  Ptr<Socket> m_socket6; //!< IPv6 Socket
  std::map <Address, callbackData> m_callbackData; //!< With this it is possible to access the currentTxBytes, the packetSizeToReturn and the send boolean through the from value of the client.
  std::vector<Address> m_connectedClients; //!< Vector which holds the list of currently connected clients.


};

} // namespace ns3

#endif /* TCP_STREAM_SERVER_H */

