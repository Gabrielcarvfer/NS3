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

#ifndef TCP_ECHO_HELPER
#define TCP_ECHO_HELPER

#include <stdint.h>
#include "ns3/application-container.h"
#include "ns3/node-container.h"
#include "ns3/object-factory.h"
#include "ns3/ipv4-address.h"

namespace ns3 {

    class TcpEchoClient;

/**
 * \brief Create a server application which waits for TCP connections.
 * This server receive TCP packets and send back to the client.
 *
 */

    class TcpEchoServerHelper
    {
    public:
        /**
         * Create TcpEchoServerHelper which will make life easier for people trying
         * to set up simulations with TCP echos.
         *
         * \param port The port the server will wait on for incoming packets
         */
        TcpEchoServerHelper (uint16_t port);

        /**
         * Create TcpEchoServerHelper which will make life easier for people trying
         * to set up simulations with TCP echos.
         *
         * \param port The port the server will wait on for incoming packets
         * \param echoFraction How much of the received payload should be sent back
         */
        TcpEchoServerHelper (uint16_t port, double echoFraction);

        /**
         * Record an attribute to be set in each Application after it is is created.
         *
         * \param name the name of the attribute to set
         * \param value the value of the attribute to set
         */
        void SetAttribute (std::string name, const AttributeValue &value);

        /**
         * Create a TcpEchoServerApplication on the specified Node.
         *
         * \param node The node on which to create the Application.  The node is
         *             specified by a Ptr<Node>.
         *
         * \returns An ApplicationContainer holding the Application created,
         */
        ApplicationContainer Install (Ptr<Node> node) const;

        /**
         * Create a TcpEchoServerApplication on specified node
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
         * Create one TCP echo server application on each of the Nodes in the
         * NodeContainer.
         *
         * \returns The applications created, one Application per Node in the
         *          NodeContainer.
         */
        ApplicationContainer Install (NodeContainer c) const;

    private:
        /**
         * \internal
         */
        Ptr<Application> InstallPriv (Ptr<Node> node) const;

        ObjectFactory m_factory;
    };

/**
 * \brief create an application which sends a TCP packet and waits for an echo of this packet
 */
    class TcpEchoClientHelper
    {
    public:
        /**
         * Create TcpEchoClientHelper which will make life easier for people trying
         * to set up simulations with TCP echos.
         *
         * \param ip The IP address of the remote TCP echo server
         * \param port The port number of the remote TCP echo server
         */
        TcpEchoClientHelper (Address ip, uint16_t port);

        /**
         * Record an attribute to be set in each Application after it is created.
         *
         * \param name the name of the attribute to set
         * \param value the value of the attribute to set
         */
        void SetAttribute (std::string name, const AttributeValue &value);

        /**
         * Given a pointer to a TcpEchoClient application, set the data fill of the TCP
         * packet (what is sent as data to the server) to the contents of the fill
         * string (including the trailing zero terminator).
         *
         * \warning The size of resulting echo packets will be automatically adjusted
         * to reflect the size of the fill string -- this means that the PacketSize
         * attribute may be changed as a result of this call.
         *
         * \param app Smart pointer to the application (real type must be TcpEchoClient).
         * \param fill The string to use as the actual echo data bytes.
         */
        void SetFill (Ptr<Application> app, std::string fill);

        /**
         * Given a pointer to a TcpEchoClient application, set the data fill of the
         * packet (what is sent as data to the server) to the contents of the fill
         * byte.
         *
         * The fill byte will be used to initialize the contents of the data packet.
         *
         * \warning The size of resulting echo packets will be automatically adjusted
         * to reflect the dataLength parameter -- this means that the PacketSize
         * attribute may be changed as a result of this call.
         *
         * \param app Smart pointer to the application (real type must be TcpEchoClient).
         * \param fill The byte to be repeated in constructing the packet data.
         * \param dataLength The desired length of the resulting echo packet data.
         */
        void SetFill (Ptr<Application> app, uint8_t fill, uint32_t dataLength);

        /**
         * Given a pointer to a TcpEchoClient application, set the data fill of the
         * packet (what is sent as data to the server) to the contents of the fill
         * buffer, repeated as many times as is required.
         *
         * Initializing the fill to the contents of a single buffer is accomplished
         * by providing a complete buffer with fillLength set to your desired
         * dataLength
         *
         * \warning The size of resulting echo packets will be automatically adjusted
         * to reflect the dataLength parameter -- this means that the PacketSize
         * attribute of the Application may be changed as a result of this call.
         *
         * \param app Smart pointer to the application (real type must be TcpEchoClient).
         * \param fill The fill pattern to use when constructing packets.
         * \param fillLength The number of bytes in the provided fill pattern.
         * \param dataLength The desired length of the final echo data.
         */
        void SetFill (Ptr<Application> app, uint8_t *fill, uint32_t fillLength, uint32_t dataLength);

        /**
         * Create a TCP echo client application on the specified node.  The Node
         * is provided as a Ptr<Node>.
         *
         * \param node The Ptr<Node> on which to create the TcpEchoClientApplication.
         *
         * \returns An ApplicationContainer that holds a Ptr<Application> to the
         *          application created
         */
        ApplicationContainer Install (Ptr<Node> node) ;

        /**
         * Create a TCP echo client application on the specified node.  The Node
         * is provided as a string name of a Node that has been previously
         * associated using the Object Name Service.
         *
         * \param nodeName The name of the node on which to create the TcpEchoClientApplication
         *
         * \returns An ApplicationContainer that holds a Ptr<Application> to the
         *          application created
         */
        ApplicationContainer Install (std::string nodeName) ;

        /**
         * \param c the nodes
         *
         * Create one TCP echo client application on each of the input nodes
         *
         * \returns the applications created, one application per input node.
         */
        ApplicationContainer Install (NodeContainer c);
        Ptr<TcpEchoClient> GetClient (void);
    private:
        Ptr<Application> InstallPriv (Ptr<Node> node);
        ObjectFactory m_factory;
        Ptr<TcpEchoClient> m_client;
    };

} // namespace ns3
#endif