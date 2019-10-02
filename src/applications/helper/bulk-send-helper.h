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
 * Author: Geoge Riley <riley@ece.gatech.edu>
 * Adapted from OnOffHelper by:
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 */

#pragma once

#include "../../../3rd-party/cpp-std-fwd/stdfwd.h"
#include "../../../3rd-party/cpp-std-fwd/stdfwd.h"
#include "../../core/model/object-factory.h"
#include "../../network/model/address.h"
#include "../../core/model/attribute.h"
#include "../../network/model/net-device.h"
#include "../../network/helper/node-container.h"
#include "../../network/helper/application-container.h"

namespace ns3 {

/**
 * \ingroup bulksend
 * \brief A helper to make it easier to instantiate an ns3::BulkSendApplication
 * on a set of nodes.
 */
class BulkSendHelper
{
public:
  /**
   * Create an BulkSendHelper to make it easier to work with BulkSendApplications
   *
   * \param protocol the name of the protocol to use to send traffic
   *        by the applications. This string identifies the socket
   *        factory type used to create sockets for the applications.
   *        A typical value would be ns3::UdpSocketFactory.
   * \param address the address of the remote node to send traffic
   *        to.
   */
  BulkSendHelper (stdfwd::string protocol, Address address);

  /**
   * Helper function used to set the underlying application attributes, 
   * _not_ the socket attributes.
   *
   * \param name the name of the application attribute to set
   * \param value the value of the application attribute to set
   */
  void SetAttribute (stdfwd::string name, const AttributeValue &value);

  /**
   * Install an ns3::BulkSendApplication on each node of the input container
   * configured with all the attributes set with SetAttribute.
   *
   * \param c NodeContainer of the set of nodes on which an BulkSendApplication
   * will be installed.
   * \returns Container of Ptr to the applications installed.
   */
  ApplicationContainer Install (NodeContainer c) const;

  /**
   * Install an ns3::BulkSendApplication on the node configured with all the
   * attributes set with SetAttribute.
   *
   * \param node The node on which an BulkSendApplication will be installed.
   * \returns Container of Ptr to the applications installed.
   */
  ApplicationContainer Install (Ptr<Node> node) const;

  /**
   * Install an ns3::BulkSendApplication on the node configured with all the
   * attributes set with SetAttribute.
   *
   * \param nodeName The node on which an BulkSendApplication will be installed.
   * \returns Container of Ptr to the applications installed.
   */
  ApplicationContainer Install (stdfwd::string nodeName) const;

private:
  /**
   * Install an ns3::BulkSendApplication on the node configured with all the
   * attributes set with SetAttribute.
   *
   * \param node The node on which an BulkSendApplication will be installed.
   * \returns Ptr to the application installed.
   */
  Ptr<Application> InstallPriv (Ptr<Node> node) const;

  ObjectFactory m_factory; //!< Object factory.
};

} // namespace ns3



