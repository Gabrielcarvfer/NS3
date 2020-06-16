/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2012
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
 * Authors: Frank Helbert <frank@ime.usp.br>,
 *          Luiz Arthur Feitosa dos Santos <luizsan@ime.usp.br> and
 *          Rodrigo Campiolo <campiolo@ime.usp.br>
 */

#include "ns3/log.h"
#include "ns3/ipv4-address.h"
#include "ns3/ipv6-address.h"
#include "ns3/address-utils.h"
#include "ns3/nstime.h"
#include "ns3/inet-socket-address.h"
#include "ns3/inet6-socket-address.h"
#include "ns3/socket.h"
#include "ns3/simulator.h"
#include "ns3/socket-factory.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"
#include "ns3/trace-source-accessor.h"
#include "tcp-echo-client.h"

namespace ns3 {

    NS_LOG_COMPONENT_DEFINE ("TcpEchoClientApplication");
    NS_OBJECT_ENSURE_REGISTERED (TcpEchoClient);

    TypeId
    TcpEchoClient::GetTypeId (void)
    {
        static TypeId tid = TypeId ("ns3::TcpEchoClient")
                .SetParent<Application> ()
                .AddConstructor<TcpEchoClient> ()
                .AddAttribute ("MaxPackets",
                               "The maximum number of packets the application will send",
                               UintegerValue (100),
                               MakeUintegerAccessor (&TcpEchoClient::m_count),
                               MakeUintegerChecker<uint32_t> ())
                .AddAttribute ("Interval",
                               "The time to wait between packets",
                               TimeValue (Seconds (1.0)),
                               MakeTimeAccessor (&TcpEchoClient::m_interval),
                               MakeTimeChecker ())
                .AddAttribute ("RemoteAddress",
                               "The destination address of the outbound packets",
                               AddressValue (),
                               MakeAddressAccessor (&TcpEchoClient::m_peerAddress),
                               MakeAddressChecker ())
                .AddAttribute ("RemotePort",
                               "The destination port of the outbound packets",
                               UintegerValue (0),
                               MakeUintegerAccessor (&TcpEchoClient::m_peerPort),
                               MakeUintegerChecker<uint16_t> ())
                .AddAttribute ("PacketSize", "Size of echo data in outbound packets",
                               UintegerValue (100),
                               MakeUintegerAccessor (&TcpEchoClient::SetDataSize,
                                                     &TcpEchoClient::GetDataSize),
                               MakeUintegerChecker<uint32_t> ())
                .AddTraceSource ("Tx", "A new packet is created and is sent",
                                 MakeTraceSourceAccessor (&TcpEchoClient::m_txTrace))
        ;
        return tid;
    }

    TcpEchoClient::TcpEchoClient ()
    {
        NS_LOG_FUNCTION_NOARGS ();
        m_sent = 0;
        m_bytesSent = 0;
        m_recvBack = 0;
        m_bytesRecvBack = 0;
        m_socket = 0;
        m_sendEvent = EventId ();
        m_data = 0;
        m_dataSize = 0;
    }

    TcpEchoClient::~TcpEchoClient()
    {
        NS_LOG_FUNCTION_NOARGS ();
        m_socket = 0;

                delete [] m_data;
        m_data = 0;
        m_dataSize = 0;
    }

    void
    TcpEchoClient::SetRemote (Address ip, uint16_t port)
    {
        m_peerAddress = ip;
        m_peerPort = port;
    }

    void
    TcpEchoClient::DoDispose (void)
    {
        NS_LOG_FUNCTION_NOARGS ();
        Application::DoDispose ();
    }

    void
    TcpEchoClient::StartApplication (void)
    {
        NS_LOG_FUNCTION_NOARGS ();

        if (m_socket == 0)
        {
            TypeId tid = TypeId::LookupByName ("ns3::TcpSocketFactory");
            m_socket = Socket::CreateSocket (GetNode (), tid);
            if (Ipv4Address::IsMatchingType(m_peerAddress) == true)
            {
                m_socket->Bind();
                m_socket->Connect (InetSocketAddress (Ipv4Address::ConvertFrom(m_peerAddress), m_peerPort));
            }
            else if (Ipv6Address::IsMatchingType(m_peerAddress) == true)
            {
                m_socket->Bind6();
                m_socket->Connect (Inet6SocketAddress (Ipv6Address::ConvertFrom(m_peerAddress), m_peerPort));
            }
        }

                m_socket->SetRecvCallback (MakeCallback (&TcpEchoClient::ReceivePacket, this));

                ScheduleTransmit (Seconds (0.));
    }

    void
    TcpEchoClient::StopApplication ()
    {
        NS_LOG_FUNCTION_NOARGS ();

        if (m_socket != 0)
        {
            m_socket->Close ();
            m_socket->SetRecvCallback (MakeNullCallback<void, Ptr<Socket> > ());
            m_socket = 0;
        }

                Simulator::Cancel (m_sendEvent);
    }

    void
    TcpEchoClient::SetDataSize (uint32_t dataSize)
    {
        NS_LOG_FUNCTION (dataSize);

                //
                // If the client is setting the echo packet data size this way, we infer
                // that she doesn't care about the contents of the packet at all, so
                // neither will we.
                //
                delete [] m_data;
        m_data = 0;
        m_dataSize = 0;
        m_size = dataSize;
    }

    uint32_t
    TcpEchoClient::GetDataSize (void) const
    {
        NS_LOG_FUNCTION_NOARGS ();
        return m_size;
    }

    void
    TcpEchoClient::SetFill (std::string fill)
    {
        NS_LOG_FUNCTION (fill);

                uint32_t dataSize = fill.size () + 1;

        if (dataSize != m_dataSize)
        {
            delete [] m_data;
            m_data = new uint8_t [dataSize];
            m_dataSize = dataSize;
        }

                memcpy (m_data, fill.c_str (), dataSize);

                //
                // Overwrite packet size attribute.
                //
                m_size = dataSize;
    }

    void
    TcpEchoClient::SetFill (uint8_t fill, uint32_t dataSize)
    {
        if (dataSize != m_dataSize)
        {
            delete [] m_data;
            m_data = new uint8_t [dataSize];
            m_dataSize = dataSize;
        }

                memset (m_data, fill, dataSize);

                //
                // Overwrite packet size attribute.
                //
                m_size = dataSize;
    }

    void
    TcpEchoClient::SetFill (uint8_t *fill, uint32_t fillSize, uint32_t dataSize)
    {
        if (dataSize != m_dataSize)
        {
            delete [] m_data;
            m_data = new uint8_t [dataSize];
            m_dataSize = dataSize;
        }

        if (fillSize >= dataSize)
        {
            memcpy (m_data, fill, dataSize);
            return;
        }

                //
                // Do all but the final fill.
                //
                uint32_t filled = 0;
        while (filled + fillSize < dataSize)
        {
            memcpy (&m_data[filled], fill, fillSize);
            filled += fillSize;
        }

                //
                // Last fill may be partial
                //
                memcpy (&m_data[filled], fill, dataSize - filled);

                //
                // Overwrite packet size attribute.
                //
                m_size = dataSize;
    }

    void
    TcpEchoClient::ScheduleTransmit (Time dt)
    {
        NS_LOG_FUNCTION_NOARGS ();
        m_sendEvent = Simulator::Schedule (dt, &TcpEchoClient::Send, this);
    }

    void
    TcpEchoClient::Send (void)
    {
        NS_LOG_FUNCTION_NOARGS ();

        NS_ASSERT (m_sendEvent.IsExpired ());

                Ptr<Packet> p;
        if (m_dataSize)
        {
            //
            // If m_dataSize is non-zero, we have a data buffer of the same size that we
            // are expected to copy and send.  This state of affairs is created if one of
            // the Fill functions is called.  In this case, m_size must have been set
            // to agree with m_dataSize
            //
            NS_ASSERT_MSG (m_dataSize == m_size, "TcpEchoClient::Send(): m_size and m_dataSize inconsistent");
            NS_ASSERT_MSG (m_data, "TcpEchoClient::Send(): m_dataSize but no m_data");
            p = Create<Packet> (m_data, m_dataSize);
            m_bytesSent += m_dataSize;
        }
        else
        {
            //
            // If m_dataSize is zero, the client has indicated that she doesn't care
            // about the data itself either by specifying the data size by setting
            // the corresponding atribute or by not calling a SetFill function.  In
            // this case, we don't worry about it either.  But we do allow m_size
            // to have a value different from the (zero) m_dataSize.
            //
            p = Create<Packet> (m_size);
            m_bytesSent += m_size;
        }
        // call to the trace sinks before the packet is actually sent,
        // so that tags added to the packet can be sent as well
        m_txTrace (p);
        m_socket->Send (p);

                ++m_sent;

        if (InetSocketAddress::IsMatchingType (m_peerAddress))
        {
            NS_LOG_INFO ("Sent " << m_size << " bytes to " <<
                                 InetSocketAddress::ConvertFrom (m_peerAddress));
        }
        else if (Inet6SocketAddress::IsMatchingType (m_peerAddress))
        {
            NS_LOG_INFO ("Sent " << m_size << " bytes to " <<
                                 Inet6SocketAddress::ConvertFrom (m_peerAddress));
        }

        if (m_sent < m_count)
        {
            ScheduleTransmit (m_interval);
        }
    }

    void
    TcpEchoClient::ReceivePacket (Ptr<Socket> socket)
    {
        NS_LOG_FUNCTION (this << socket);
        Ptr<Packet> packet;
        Address from;
        while ((packet = socket->RecvFrom (from)))
        {
            if (InetSocketAddress::IsMatchingType (from))
            {
                NS_LOG_INFO ("Received " << packet->GetSize () << " bytes from " <<
                                         InetSocketAddress::ConvertFrom (from).GetIpv4 ());
            }
            else if (Inet6SocketAddress::IsMatchingType (from))
            {
                NS_LOG_INFO ("Received " << packet->GetSize () << " bytes from " <<
                                         Inet6SocketAddress::ConvertFrom (from).GetIpv6 ());
            }

                    // don't check if data returned is the same data sent earlier
                    m_recvBack++;
            m_bytesRecvBack += packet->GetSize ();
        }

        if (m_count == m_recvBack)
        {
            socket->Close();
            m_socket->SetRecvCallback (MakeNullCallback<void, Ptr<Socket> > ());
            socket = 0;
        }
    }

} // Namespace ns3