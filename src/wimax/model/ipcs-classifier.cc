/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 *  Copyright (c) 2009 INRIA, UDcast
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
 *         Mohamed Amine Ismail <amine.ismail@sophia.inria.fr>
 *
 */

#include "ipcs-classifier.h"
#include <stdint.h>
#include "../../core/model/log.h"
#include "service-flow.h"
#include "../../network/model/packet.h"
#include "../../internet/model/ipv4-header.h"
#include "../../internet/model/udp-header.h"
#include "../../internet/model/tcp-header.h"
#include "../../network/utils/llc-snap-header.h"
#include "../../internet/model/udp-l4-protocol.h"
#include "../../internet/model/tcp-l4-protocol.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("IpcsClassifier");

NS_OBJECT_ENSURE_REGISTERED (IpcsClassifier);

TypeId IpcsClassifier::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::IpcsClassifier")
    .SetParent<Object> ()
    .SetGroupName("Wimax");
  return tid;
}

IpcsClassifier::IpcsClassifier (void)
{
}

IpcsClassifier::~IpcsClassifier (void)
{
}

ServiceFlow *
IpcsClassifier::Classify (Ptr<const Packet> packet,
                          Ptr<ServiceFlowManager> sfm, ServiceFlow::Direction dir)
{
  Ptr<Packet> C_Packet = packet->Copy ();

  LlcSnapHeader llc;
  C_Packet->RemoveHeader (llc);

  Ipv4Header ipv4Header;
  C_Packet->RemoveHeader (ipv4Header);
  Ipv4Address source_address = ipv4Header.GetSource ();
  Ipv4Address dest_address = ipv4Header.GetDestination ();
  uint8_t protocol = ipv4Header.GetProtocol ();

  uint16_t sourcePort = 0;
  uint16_t destPort = 0;
  if (protocol == UdpL4Protocol::PROT_NUMBER)
    {
      UdpHeader udpHeader;
      C_Packet->RemoveHeader (udpHeader);
      sourcePort = udpHeader.GetSourcePort ();
      destPort = udpHeader.GetDestinationPort ();
    }
  else if (protocol == TcpL4Protocol::PROT_NUMBER)
    {
      TcpHeader tcpHeader;
      C_Packet->RemoveHeader (tcpHeader);
      sourcePort = tcpHeader.GetSourcePort ();
      destPort = tcpHeader.GetDestinationPort ();
    }
  else
    {
      NS_LOG_INFO ("\t\t\tUnknown protocol: " << protocol);
      return 0;
    }

  NS_LOG_INFO ("Classifing packet: src_addr=" << source_address << " dst_addr="
                                              << dest_address << " src_port=" << sourcePort << " dst_port="
                                              << destPort << " proto=" << (uint16_t) protocol);
  return (sfm->DoClassify (source_address,
                           dest_address,
                           sourcePort,
                           destPort,
                           protocol,dir));
}

}
