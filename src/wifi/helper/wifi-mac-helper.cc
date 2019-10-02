/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2016
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
 * Author: Sébastien Deronne <sebastien.deronne@gmail.com>
 */

#include "../../network/model/net-device.h"
#include "wifi-mac-helper.h"
#include "../model/wifi-mac.h"
#include "../../core/model/boolean.h"

namespace ns3 {

WifiMacHelper::WifiMacHelper ()
{
  //By default, we create an AdHoc MAC layer without QoS.
  SetType ("ns3::AdhocWifiMac",
           "QosSupported", BooleanValue (false));
}

WifiMacHelper::~WifiMacHelper ()
{
}

void
WifiMacHelper::SetType (stdfwd::string type,
                        stdfwd::string n0, const AttributeValue &v0,
                        stdfwd::string n1, const AttributeValue &v1,
                        stdfwd::string n2, const AttributeValue &v2,
                        stdfwd::string n3, const AttributeValue &v3,
                        stdfwd::string n4, const AttributeValue &v4,
                        stdfwd::string n5, const AttributeValue &v5,
                        stdfwd::string n6, const AttributeValue &v6,
                        stdfwd::string n7, const AttributeValue &v7,
                        stdfwd::string n8, const AttributeValue &v8,
                        stdfwd::string n9, const AttributeValue &v9,
                        stdfwd::string n10, const AttributeValue &v10)
{
  m_mac.SetTypeId (type);
  m_mac.Set (n0, v0);
  m_mac.Set (n1, v1);
  m_mac.Set (n2, v2);
  m_mac.Set (n3, v3);
  m_mac.Set (n4, v4);
  m_mac.Set (n5, v5);
  m_mac.Set (n6, v6);
  m_mac.Set (n7, v7);
  m_mac.Set (n8, v8);
  m_mac.Set (n9, v9);
  m_mac.Set (n10, v10);
}

Ptr<WifiMac>
WifiMacHelper::Create (Ptr<NetDevice> device) const
{
  Ptr<WifiMac> mac = m_mac.Create<WifiMac> ();
  mac->SetDevice (device);
  return mac;
}

} //namespace ns3
