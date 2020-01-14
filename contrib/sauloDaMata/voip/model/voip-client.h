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

#ifndef VOIP_CLIENT_H_
#define VOIP_CLIENT_H_

#include "ns3/application.h"
#include "ns3/event-id.h"
#include "ns3/ptr.h"
#include "ns3/ipv4-address.h"
#include "ns3/seq-ts-header.h"

//#include <sys/types.h>
//#include <sys/stat.h>
//#include <netinet/in.h>
//#include <stdio.h>
//#include <string.h>

#include <fstream>
#include <iostream>
#include <fstream>
#include <iomanip>

using std::ifstream;
using std::ofstream;
using std::ostream;

using std::ios;
using std::endl;

using namespace std;

namespace ns3 {

class Socket;
class Packet;

/**
 * \class VoipClient
 * \brief A Udp client. Sends UDP packet carrying sequence number and time stamp
 *  in their payloads
 *
 */
class VoipClient : public Application
{
public:


  static TypeId
  GetTypeId (void);

  VoipClient ();

  virtual ~VoipClient ();

  /**
   * \brief set the remote address and port
   * \param ip remote IP address
   * \param port remote port
   */
  void SetRemote (Ipv4Address ip, uint16_t port);

protected:
  virtual void DoDispose (void);

private:

  virtual void StartApplication (void);
  virtual void StopApplication (void);

  void Send (void);
  void HandleRead (Ptr<Socket> socket);

  Ptr<Socket> m_socket;
  Ipv4Address m_peerAddress;
  uint16_t    m_peerPort;
  EventId     m_sendEvent;
};

} // namespace ns3


#endif /* VOIP_CLIENT_H_ */
