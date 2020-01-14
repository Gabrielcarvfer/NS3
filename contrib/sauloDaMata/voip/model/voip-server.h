/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2013 Federal University of Uberlandia
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
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Saulo da Mata <damata.saulo@gmail.com>
 */

#ifndef VOIP_SERVER_H_
#define VOIP_SERVER_H_

#include "ns3/application.h"
#include "ns3/event-id.h"
#include "ns3/ptr.h"
#include "ns3/address.h"
#include "ns3/ipv4-address.h"
#include "ns3/seq-ts-header.h"
#include "ns3/socket.h"

namespace ns3 {

class VoipServer : public Application
{
public:
  static TypeId GetTypeId (void);
  VoipServer ();
  virtual ~VoipServer ();

protected:
  virtual void DoDispose (void);

private:

  virtual void StartApplication (void);
  virtual void StopApplication (void);

  void HandleRead (Ptr<Socket> socket);
  void Send();

  uint16_t    m_packetSize;
  uint32_t    m_packetId;
  uint16_t    m_port;
  Ptr<Socket> m_socket;
  Address     m_peerAddress;
  EventId     m_sendEvent;
  Time        m_interval;

};

} // namespace ns3

#endif /* VOIP_SERVER_H_ */
