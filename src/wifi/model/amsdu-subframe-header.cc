/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 MIRKO BANCHI
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
 * Author: Mirko Banchi <mk.banchi@gmail.com>
 */

#include "amsdu-subframe-header.h"
#include "ns3/address-utils.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("AmsduSubframeHeader");

NS_OBJECT_ENSURE_REGISTERED (AmsduSubframeHeader);

TypeId
AmsduSubframeHeader::GetTypeId ()
{
  static TypeId tid = TypeId ("ns3::AmsduSubframeHeader")
    .SetParent<Header> ()
    .SetGroupName ("Wifi")
    .AddConstructor<AmsduSubframeHeader> ()
  ;
  return tid;
}

TypeId
AmsduSubframeHeader::GetInstanceTypeId (void) const
{
  return GetTypeId ();
}

AmsduSubframeHeader::AmsduSubframeHeader ()
  : m_length (0)
{
  NS_LOG_FUNCTION (this);
}

AmsduSubframeHeader::~AmsduSubframeHeader ()
{
  NS_LOG_FUNCTION (this);
}

uint32_t
AmsduSubframeHeader::GetSerializedSize () const
{
  NS_LOG_FUNCTION (this);
  return (6 + 6 + 2);
}

void
AmsduSubframeHeader::Serialize (Buffer::Iterator i) const
{
  NS_LOG_FUNCTION (this << &i);
  WriteTo (i, m_da);
  WriteTo (i, m_sa);
  i.WriteHtonU16 (m_length);
}

uint32_t
AmsduSubframeHeader::Deserialize (Buffer::Iterator start)
{
  NS_LOG_FUNCTION (this << &start);
  Buffer::Iterator i = start;
  ReadFrom (i, m_da);
  ReadFrom (i, m_sa);
  m_length = i.ReadNtohU16 ();
  return i.GetDistanceFrom (start);
}

void
AmsduSubframeHeader::Print (std::ostream &os) const
{
  NS_LOG_FUNCTION (this << &os);
  os << "DA = " << m_da << ", SA = " << m_sa << ", length = " << m_length;
}

void
AmsduSubframeHeader::SetDestinationAddr (Mac48Address to)
{
  NS_LOG_FUNCTION (this << to);
  m_da = to;
}

void
AmsduSubframeHeader::SetSourceAddr (Mac48Address from)
{
  NS_LOG_FUNCTION (this << from);
  m_sa = from;
}

void
AmsduSubframeHeader::SetLength (uint16_t length)
{
  NS_LOG_FUNCTION (this << length);
  m_length = length;
}

Mac48Address
AmsduSubframeHeader::GetDestinationAddr (void) const
{
  NS_LOG_FUNCTION (this);
  return m_da;
}

Mac48Address
AmsduSubframeHeader::GetSourceAddr (void) const
{
  NS_LOG_FUNCTION (this);
  return m_sa;
}

uint16_t
AmsduSubframeHeader::GetLength (void) const
{
  NS_LOG_FUNCTION (this);
  return m_length;
}

} //namespace ns3
