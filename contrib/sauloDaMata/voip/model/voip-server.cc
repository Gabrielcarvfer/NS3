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


#include "ns3/log.h"
#include "ns3/ipv4-address.h"
#include "ns3/nstime.h"
#include "ns3/inet-socket-address.h"
#include "ns3/socket.h"
#include "ns3/simulator.h"
#include "ns3/socket-factory.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"
#include "ns3/string.h"

#include "voip-server.h"

NS_LOG_COMPONENT_DEFINE ("VoipServer");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (VoipServer);

TypeId
VoipServer::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::VoipServer")
    .SetParent<Application> ()
    .AddConstructor<VoipServer> ()
    .AddAttribute ("Port",
                   "Port to listen for incoming packets.",
                   UintegerValue (100),
                   MakeUintegerAccessor (&VoipServer::m_port),
                   MakeUintegerChecker<uint16_t> ())
    .AddAttribute ("PacketSize", "The size of packets (in bytes). Choose between 40, 50 and 60 bytes.",
                   UintegerValue (60),
                   MakeUintegerAccessor (&VoipServer::m_packetSize),
                   MakeUintegerChecker<uint32_t> (40, 60))
    .AddAttribute ("Interval",
                   "The time to wait between packets. Adjust this according to the packet size and codec rate.",
                   TimeValue (Seconds (0.06)),
                   MakeTimeAccessor (&VoipServer::m_interval),
                   MakeTimeChecker ())
  ;
  return tid;
}

VoipServer::VoipServer ()
 {
  NS_LOG_FUNCTION (this);
  m_socket = 0;
  m_packetSize = 0;
  m_packetId = 0;
  m_sendEvent = EventId ();
}

VoipServer::~VoipServer ()
{
  NS_LOG_FUNCTION (this);
}

void
VoipServer::DoDispose (void)
{
  NS_LOG_FUNCTION (this);
  Application::DoDispose ();
}

void
VoipServer::StartApplication (void)
{
  NS_LOG_FUNCTION_NOARGS();

  Ptr<Socket> socket = 0;
  Ptr<Socket> socket6 = 0;

  if (socket == 0)
    {
      TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
      socket = Socket::CreateSocket (GetNode (), tid);
      InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (),
                                                   m_port);
      socket->Bind (local);

      socket->SetRecvCallback (MakeCallback (&VoipServer::HandleRead, this));
    }


  if (socket6 == 0)
    {
      TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
      socket6 = Socket::CreateSocket (GetNode (), tid);
      Inet6SocketAddress local = Inet6SocketAddress (Ipv6Address::GetAny (),
                                                   m_port);
      socket6->Bind (local);

      socket6->SetRecvCallback (MakeCallback (&VoipServer::HandleRead, this));
    }
}

void
VoipServer::StopApplication ()
{
  NS_LOG_FUNCTION_NOARGS();
}


void
VoipServer::Send ()
{
  NS_LOG_FUNCTION (this);
  NS_ASSERT (m_sendEvent.IsExpired ());

  // Using compressed IP/UDP/RTP header. 40 bytes become 2 bytes. Then, 38 bytes must be removed from payload.
  Ptr<Packet> p = Create<Packet> (m_packetSize - (38));
  m_packetId++;

  SeqTsHeader seqTs;
  seqTs.SetSeq (m_packetId);
  p->AddHeader (seqTs);
  m_socket->SendTo(p, 0, m_peerAddress);

  if (InetSocketAddress::IsMatchingType (m_peerAddress))
    {
      NS_LOG_DEBUG(">> VoipServer: Send packet at " << Simulator::Now().GetSeconds() << "s\tid: " << m_packetId
                    << "\t" << p->GetSize() << " bytes to " << InetSocketAddress::ConvertFrom (m_peerAddress).GetIpv4 ());
    }
  else if (Inet6SocketAddress::IsMatchingType (m_peerAddress))
    {
      NS_LOG_DEBUG(">> voipServer: Send packet at " << Simulator::Now().GetSeconds() << "s\tid: " << m_packetId
                    << "\t" << p->GetSize() << " bytes to " << Inet6SocketAddress::ConvertFrom (m_peerAddress).GetIpv6 ());
    }

  m_sendEvent = Simulator::Schedule (m_interval, &VoipServer::Send, this);
}

void
VoipServer::HandleRead (Ptr<Socket> socket)
{
  NS_LOG_FUNCTION_NOARGS();

  Ptr<Packet> packet;
  Address from;
  m_socket = socket;


  while ((packet = socket->RecvFrom (from)))
    {
      m_peerAddress = from;
      if (InetSocketAddress::IsMatchingType (from))
        {
          NS_LOG_INFO (">> VoipServer: Client at " << InetSocketAddress::ConvertFrom (from).GetIpv4 ()
                        << " is requesting a VoIP traffic.");
        }
      else if (Inet6SocketAddress::IsMatchingType (from))
        {
             NS_LOG_INFO (">> VoipServer: Client at " << Inet6SocketAddress::ConvertFrom (from).GetIpv6 ()
                           << " is requesting a VoIP traffic.");
        }

      m_sendEvent = Simulator::ScheduleNow (&VoipServer::Send, this);
    }
}

} // Namespace ns3
