/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2008 INRIA
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
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 */
#include "tcp-stream-helper.h"
#include "ns3/tcp-stream-server.h"
#include "ns3/tcp-stream-client.h"
#include "ns3/uinteger.h"
#include "ns3/names.h"

namespace ns3 {

TcpStreamServerHelper::TcpStreamServerHelper (uint16_t port)
{
  m_factory.SetTypeId (TcpStreamServer::GetTypeId ());
  SetAttribute ("Port", UintegerValue (port));
}

void 
TcpStreamServerHelper::SetAttribute (
  std::string name, 
  const AttributeValue &value)
{
  m_factory.Set (name, value);
}

ApplicationContainer
TcpStreamServerHelper::Install (Ptr<Node> node) const
{
  return ApplicationContainer (InstallPriv (node));
}

ApplicationContainer
TcpStreamServerHelper::Install (std::string nodeName) const
{
  Ptr<Node> node = Names::Find<Node> (nodeName);
  return ApplicationContainer (InstallPriv (node));
}

ApplicationContainer
TcpStreamServerHelper::Install (NodeContainer c) const
{
  ApplicationContainer apps;
  for (NodeContainer::Iterator i = c.Begin (); i != c.End (); ++i)
    {
      apps.Add (InstallPriv (*i));
    }

  return apps;
}

Ptr<Application>
TcpStreamServerHelper::InstallPriv (Ptr<Node> node) const
{
  Ptr<Application> app = m_factory.Create<TcpStreamServer> ();
  node->AddApplication (app);

  return app;
}

TcpStreamClientHelper::TcpStreamClientHelper (Address address, uint16_t port)
{
  m_factory.SetTypeId (TcpStreamClient::GetTypeId ());
  SetAttribute ("RemoteAddress", AddressValue (address));
  SetAttribute ("RemotePort", UintegerValue (port));
}

TcpStreamClientHelper::TcpStreamClientHelper (Ipv4Address address, uint16_t port)
{
  m_factory.SetTypeId (TcpStreamClient::GetTypeId ());
  SetAttribute ("RemoteAddress", AddressValue (Address(address)));
  SetAttribute ("RemotePort", UintegerValue (port));
}

TcpStreamClientHelper::TcpStreamClientHelper (Ipv6Address address, uint16_t port)
{
  m_factory.SetTypeId (TcpStreamClient::GetTypeId ());
  SetAttribute ("RemoteAddress", AddressValue (Address(address)));
  SetAttribute ("RemotePort", UintegerValue (port));
}

void 
TcpStreamClientHelper::SetAttribute (std::string name, const AttributeValue &value)
{
  m_factory.Set (name, value);
}

ApplicationContainer
TcpStreamClientHelper::Install (std::vector <std::pair <Ptr<Node>, std::string> > clients) const
{
  ApplicationContainer apps;

  for (uint64_t i = 0; i < clients.size (); i++)
    {
      apps.Add (InstallPriv (clients.at (i).first, clients.at (i).second, i));
    }

  return apps;
}

Ptr<Application>
TcpStreamClientHelper::InstallPriv (Ptr<Node> node, std::string algo, uint16_t clientId) const
{
  Ptr<Application> app = m_factory.Create<TcpStreamClient> ();
  app->GetObject<TcpStreamClient> ()->SetAttribute ("ClientId", UintegerValue (clientId));
  app->GetObject<TcpStreamClient> ()->Initialise (algo, clientId);
  node->AddApplication (app);

  return app;
}

} // namespace ns3
