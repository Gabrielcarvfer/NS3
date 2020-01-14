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
#include "voip-client.h"

#include <stdlib.h>
#include <stdio.h>
#include "ns3/string.h"


namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("VoipClient");
NS_OBJECT_ENSURE_REGISTERED (VoipClient);

TypeId
VoipClient::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::VoipClient")
    .SetParent<Application> ()
    .AddConstructor<VoipClient> ()
    .AddAttribute ("RemoteAddress",
                   "The destination Ipv4Address of the outbound packets",
                   Ipv4AddressValue (),
                   MakeIpv4AddressAccessor (&VoipClient::m_peerAddress),
                   MakeIpv4AddressChecker ())
    .AddAttribute ("RemotePort", "The destination port of the outbound packets",
                   UintegerValue (100),
                   MakeUintegerAccessor (&VoipClient::m_peerPort),
                   MakeUintegerChecker<uint16_t> ())
    ;
  return tid;
}

VoipClient::VoipClient ()
{
  NS_LOG_FUNCTION_NOARGS ();
  m_sendEvent = EventId ();
}

VoipClient::~VoipClient ()
{
  NS_LOG_FUNCTION_NOARGS ();
}

void
VoipClient::SetRemote (Ipv4Address ip, uint16_t port)
{
  m_peerAddress = ip;
  m_peerPort = port;
}

void
VoipClient::DoDispose (void)
{
  NS_LOG_FUNCTION_NOARGS ();
  Application::DoDispose ();
}

void
VoipClient::StartApplication (void)
{
  NS_LOG_FUNCTION_NOARGS();

  if (m_socket == 0)
    {
      TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
      m_socket = Socket::CreateSocket (GetNode (), tid);
      m_socket->Bind ();
      m_socket->Connect (InetSocketAddress (m_peerAddress, m_peerPort));
    }

  m_socket->SetRecvCallback (MakeCallback (&VoipClient::HandleRead, this));

  //Delay requesting to get server on line.
  m_sendEvent = Simulator::Schedule ( Seconds(0.1) , &VoipClient::Send, this);

}

void
VoipClient::Send (void)
{
  NS_LOG_FUNCTION_NOARGS ();

  Ptr<Packet> p = Create<Packet> ();

  SeqTsHeader seqTs;
  seqTs.SetSeq (0);
  p->AddHeader (seqTs);

  m_socket->Send (p);

  NS_LOG_INFO (">> VoipClient: Sending request for VoIP traffic to VoipServer at "
                << m_peerAddress << ":" << m_peerPort);
}


void
VoipClient::StopApplication ()
{
  NS_LOG_FUNCTION_NOARGS ();
  Simulator::Cancel (m_sendEvent);
}

void
VoipClient::HandleRead (Ptr<Socket> socket)
{
  NS_LOG_FUNCTION (this << socket);
  Ptr<Packet> packet;
  Address from;
  while ((packet = socket->RecvFrom (from)))
    {
      if (InetSocketAddress::IsMatchingType (from))
        {
          if (packet->GetSize () > 0)
            {
              if (InetSocketAddress::IsMatchingType (from))
                {
                  NS_LOG_INFO ("At time " << Simulator::Now ().GetSeconds ()
                               << "s VoIPClient received "
                               <<  packet->GetSize () << " bytes from "
                               << InetSocketAddress::ConvertFrom(from).GetIpv4 ()
                               << " port " << InetSocketAddress::ConvertFrom (from).GetPort ());
                }
              else if (Inet6SocketAddress::IsMatchingType (from))
                {
                  NS_LOG_INFO ("At time " << Simulator::Now ().GetSeconds ()
                               << "s VoIPClient received "
                               <<  packet->GetSize () << " bytes from "
                               << Inet6SocketAddress::ConvertFrom(from).GetIpv6 ()
                               << " port " << Inet6SocketAddress::ConvertFrom (from).GetPort ());
                }
           }
        }
    }
}

} // Namespace ns3
