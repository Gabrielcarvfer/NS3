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


#ifndef VOIP_CLIENT_SERVER_HELPER_H_
#define VOIP_CLIENT_SERVER_HELPER_H_

#include <stdint.h>
#include <string>
#include "ns3/object-factory.h"
#include "ns3/address.h"
#include "ns3/attribute.h"
#include "ns3/net-device.h"
#include "ns3/node-container.h"
#include "ns3/application-container.h"
#include "ns3/voip-server.h"

namespace ns3 {

class VoipServerHelper
{
public:
  VoipServerHelper (uint16_t port);

  void SetAttribute (std::string name, const AttributeValue &value);

  ApplicationContainer Install (NodeContainer c);
  Ptr<VoipServer> GetServer(void);
private:
  ObjectFactory m_factory;
  Ptr<VoipServer> m_server;
};


class VoipClientHelper
{

public:
  /**
   * Create VoipClientHelper which will make life easier for people trying
   * to set up simulations with udp-client-server.
   *
   */
  VoipClientHelper ();

   /**
    *  Create VoipClientHelper which will make life easier for people trying
    * to set up simulations with udp-client-server.
    *
    * \param ip The IP address of the remote udp server
    * \param port The port number of the remote udp server
    */

  VoipClientHelper (Ipv4Address ip,uint16_t port);

  /**
   * Record an attribute to be set in each Application after it is is created.
   *
   * \param name the name of the attribute to set
   * \param value the value of the attribute to set
   */
  void SetAttribute (std::string name, const AttributeValue &value);

  /**
     * \param c the nodes
     *
     * Create one udp client application on each of the input nodes
     *
     * \returns the applications created, one application per input node.
     */
  ApplicationContainer Install (NodeContainer c);

private:
  ObjectFactory m_factory;
};

} // namespace ns3



#endif /* VOIP_CLIENT_SERVER_HELPER_H_ */
