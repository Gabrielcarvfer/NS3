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
#ifndef TCP_STREAM_HELPER_H
#define TCP_STREAM_HELPER_H

#include <stdint.h>
#include "ns3/application-container.h"
#include "ns3/node-container.h"
#include "ns3/object-factory.h"
#include "ns3/ipv4-address.h"
#include "ns3/ipv6-address.h"

namespace ns3 {

/**
 * \ingroup TcpStream
 * \brief Create a server application which waits for input UDP packets
 *        and sends them back to the original sender.
 */
class TcpStreamServerHelper
{
public:
  /**
   * Create TcpStreamServerHelper which will make life easier for people trying
   * to set up simulations with echos.
   *
   * \param port The port the server will wait on for incoming packets
   */
  TcpStreamServerHelper (uint16_t port);

  /**
   * Record an attribute to be set in each Application after it is is created.
   *
   * \param name the name of the attribute to set
   * \param value the value of the attribute to set
   */
  void SetAttribute (std::string name, const AttributeValue &value);

  /**
   * Create a TcpStreamServerApplication on the specified Node.
   *
   * \param node The node on which to create the Application.  The node is
   *             specified by a Ptr<Node>.
   *
   * \returns An ApplicationContainer holding the Application created,
   */
  ApplicationContainer Install (Ptr<Node> node) const;

  /**
   * Create a TcpStreamServerApplication on specified node
   *
   * \param nodeName The node on which to create the application.  The node
   *                 is specified by a node name previously registered with
   *                 the Object Name Service.
   *
   * \returns An ApplicationContainer holding the Application created.
   */
  ApplicationContainer Install (std::string nodeName) const;

  /**
   * \param c The nodes on which to create the Applications.  The nodes
   *          are specified by a NodeContainer.
   *
   * Create one tcp stream server application on each of the Nodes in the
   * NodeContainer.
   *
   * \returns The applications created, one Application per Node in the 
   *          NodeContainer.
   */
  ApplicationContainer Install (NodeContainer c) const;

private:
  /**
   * Install an ns3::TcpStreamServer on the node configured with all the
   * attributes set with SetAttribute.
   *
   * \param node The node on which an TcpStreamServer will be installed.
   * \returns Ptr to the application installed.
   */
  Ptr<Application> InstallPriv (Ptr<Node> node) const;

  ObjectFactory m_factory; //!< Object factory.
};

/**
 * \ingroup TcpStream
 * \brief Create an application which sends a UDP packet and waits for an echo of this packet
 */
class TcpStreamClientHelper
{
public:
  /**
   * Create TcpStreamClientHelper which will make life easier for people trying
   * to set up simulations with echos.
   *
   * \param ip The IP address of the remote tcp stream server
   * \param port The port number of the remote tcp stream server
   */
  TcpStreamClientHelper (Address ip, uint16_t port);
  /**
   * Create TcpStreamClientHelper which will make life easier for people trying
   * to set up simulations with echos.
   *
   * \param ip The IPv4 address of the remote tcp stream server
   * \param port The port number of the remote tcp stream server
   */
  TcpStreamClientHelper (Ipv4Address ip, uint16_t port);
  /**
   * Create TcpStreamClientHelper which will make life easier for people trying
   * to set up simulations with echos.
   *
   * \param ip The IPv6 address of the remote tcp stream server
   * \param port The port number of the remote tcp stream server
   */
  TcpStreamClientHelper (Ipv6Address ip, uint16_t port);

  /**
   * Record an attribute to be set in each Application after it is is created.
   *
   * \param name the name of the attribute to set
   * \param value the value of the attribute to set
   */
  void SetAttribute (std::string name, const AttributeValue &value);

  /**
   * \param clients the nodes with the name of the adaptation algorithm to be used
   *
   * Create one tcp stream client application on each of the input nodes and
   * instantiate an adaptation algorithm on each of the tcp stream client according
   * to the given string.
   *
   * \returns the applications created, one application per input node.
   */
  ApplicationContainer Install (std::vector <std::pair <Ptr<Node>, std::string> > clients) const;

private:
  /**
   * Install an ns3::TcpStreamClient on the node configured with all the
   * attributes set with SetAttribute.
   *
   * \param node The node on which an TcpStreamClient will be installed.
   * \param algo A string containing the name of the adaptation algorithm to be used on this client
   * \param clientId distinguish this client object from other parallel running clients, for logging purposes
   * \param simulationId distinguish this simulation from other subsequently started simulations, for logging purposes
   * \returns Ptr to the application installed.
   */
  Ptr<Application> InstallPriv (Ptr<Node> node, std::string algo, uint16_t clientId) const;
  ObjectFactory m_factory; //!< Object factory.
};

} // namespace ns3

#endif /* TCP_STREAM_HELPER_H */
