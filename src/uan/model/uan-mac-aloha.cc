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

#include "uan-mac-aloha.h"
#include "uan-tx-mode.h"
#include "uan-address.h"
#include "ns3/log.h"
#include "uan-phy.h"
#include "uan-header-common.h"

#include <iostream>

namespace ns3
{

NS_LOG_COMPONENT_DEFINE ("UanMacAloha");
  
NS_OBJECT_ENSURE_REGISTERED (UanMacAloha);

UanMacAloha::UanMacAloha ()
  : UanMac (),
    m_cleared (false)
{
}

UanMacAloha::~UanMacAloha ()
{
}

void
UanMacAloha::Clear ()
{
  if (m_cleared)
    {
      return;
    }
  m_cleared = true;
  if (m_phy)
    {
      m_phy->Clear ();
      m_phy = 0;
    }
}

void
UanMacAloha::DoDispose ()
{
  Clear ();
  UanMac::DoDispose ();
}

TypeId
UanMacAloha::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::UanMacAloha")
    .SetParent<UanMac> ()
    .SetGroupName ("Uan")
    .AddConstructor<UanMacAloha> ()
  ;
  return tid;
}

Address
UanMacAloha::GetAddress (void)
{
  return m_address;
}

void
UanMacAloha::SetAddress (UanAddress addr)
{
  m_address=addr;
}
bool
UanMacAloha::Enqueue (Ptr<Packet> packet, const Address &dest, uint16_t protocolNumber)
{
  NS_LOG_DEBUG ("" << Simulator::Now ().GetSeconds () << " MAC " << UanAddress::ConvertFrom (GetAddress ()) << " Queueing packet for " << UanAddress::ConvertFrom (dest));

  if (!m_phy->IsStateTx ())
    {
      UanAddress src = UanAddress::ConvertFrom (GetAddress ());
      UanAddress udest = UanAddress::ConvertFrom (dest);

      UanHeaderCommon header;
      header.SetSrc (src);
      header.SetDest (udest);
      header.SetType (0);

      packet->AddHeader (header);
      m_phy->SendPacket (packet, protocolNumber);
      return true;
    }
  else
    return false;
}

void
UanMacAloha::SetForwardUpCb (Callback<void, Ptr<Packet>, const UanAddress& > cb)
{
  m_forUpCb = cb;
}
void
UanMacAloha::AttachPhy (Ptr<UanPhy> phy)
{
  m_phy = phy;
  m_phy->SetReceiveOkCallback (MakeCallback (&UanMacAloha::RxPacketGood, this));
  m_phy->SetReceiveErrorCallback (MakeCallback (&UanMacAloha::RxPacketError, this));

}
void
UanMacAloha::RxPacketGood (Ptr<Packet> pkt, double sinr, UanTxMode txMode)
{
  UanHeaderCommon header;
  pkt->RemoveHeader (header);
  NS_LOG_DEBUG ("Receiving packet from " << header.GetSrc () << " For " << header.GetDest ());

  if (header.GetDest () == GetAddress () || header.GetDest () == UanAddress::GetBroadcast ())
    {
      m_forUpCb (pkt, header.GetSrc ());
    }

}

void
UanMacAloha::RxPacketError (Ptr<Packet> pkt, double sinr)
{
  NS_LOG_DEBUG ("" << Simulator::Now () << " MAC " << UanAddress::ConvertFrom (GetAddress ()) << " Received packet in error with sinr " << sinr);
}

Address
UanMacAloha::GetBroadcast (void) const
{
  UanAddress broadcast (255);
  return broadcast;
}

int64_t
UanMacAloha::AssignStreams (int64_t stream)
{
  NS_LOG_FUNCTION (this << stream);
  return 0;
}

}
