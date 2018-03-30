/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011-2013 Centre Tecnologic de Telecomunicacions de Catalunya (CTTC)
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
 * Author: Jaume Nin <jnin@cttc.es>
 *         Nicola Baldo <nbaldo@cttc.es>
 *         Manuel Requena <manuel.requena@cttc.es>
 */

#ifndef EPC_HELPER_H
#define EPC_HELPER_H

#include <ns3/object.h>
#include <ns3/ipv4-address-helper.h>
#include <ns3/ipv6-address-helper.h>
#include <ns3/data-rate.h>
#include <ns3/epc-tft.h>
#include <ns3/eps-bearer.h>

namespace ns3 {

class Node;
class NetDevice;
class VirtualNetDevice;
class EpcSgwPgwApplication;
class EpcX2;
class EpcMme;

/**
 * \ingroup lte
 *
 * \brief Base helper class to handle the creation of the EPC entities.
 *
 * This class provides the API for the implementation of helpers that
 * allow to create EPC entities and the nodes and interfaces that host
 * and connect them. 
 */
class EpcHelper : public Object
{
public:
  
  /** 
   * Constructor
   */
  EpcHelper ();

  /** 
   * Destructor
   */  
  virtual ~EpcHelper ();
  
  // inherited from Object
  /**
   *  Register this type.
   *  \return The object TypeId.
   */
  static TypeId GetTypeId (void);
  virtual void DoDispose ();

  
  /** 
   * Add an eNB to the EPC
   * 
   * \param enbNode the previosuly created eNB node which is to be
   * added to the EPC
   * \param lteEnbNetDevice the LteEnbNetDevice of the eNB node
   * \param cellId ID of the eNB
   */
  virtual void AddEnb (Ptr<Node> enbNode, Ptr<NetDevice> lteEnbNetDevice, uint16_t cellId) = 0;

  /** 
   * Notify the EPC of the existance of a new UE which might attach at a later time
   * 
   * \param ueLteDevice the UE device to be attached
   * \param imsi the unique identifier of the UE
   */
  virtual void AddUe (Ptr<NetDevice> ueLteDevice, uint64_t imsi) = 0;

  /** 
   * Add an X2 interface between two eNB
   * 
   * \param enbNode1 one eNB peer of the X2 interface
   * \param enbNode2 the other eNB peer of the X2 interface
   */
  virtual void AddX2Interface (Ptr<Node> enbNode1, Ptr<Node> enbNode2) = 0;

  /** 
   * Activate an EPS bearer, setting up the corresponding S1-U tunnel.
   * 
   * 
   * 
   * \param ueLteDevice the Ipv4-enabled device of the UE, normally
   * connected via the LTE radio interface
   * \param imsi the unique identifier of the UE
   * \param tft the Traffic Flow Template of the new bearer
   * \param bearer struct describing the characteristics of the EPS bearer to be activated
   * \return bearer ID
   */
  virtual uint8_t ActivateEpsBearer (Ptr<NetDevice> ueLteDevice, uint64_t imsi, Ptr<EpcTft> tft, EpsBearer bearer) = 0;


  /** 
   * 
   * \return a pointer to the node implementing PGW
   * functionality. Note that in this particular implementation this
   * node will also hold the SGW functionality. The primary use
   * intended for this method is to allow the user to configure the Gi
   * interface of the PGW, i.e., to connect the PGW to the internet.
   */
  virtual Ptr<Node> GetPgwNode () = 0;

  /** 
   * Assign IPv4 addresses to UE devices
   * 
   * \param ueDevices the set of UE devices
   * 
   * \return the interface container, \see Ipv4AddressHelper::Assign() which has similar semantics
   */
  virtual Ipv4InterfaceContainer AssignUeIpv4Address (NetDeviceContainer ueDevices) = 0;


  /** 
   * 
   * \return the IPv4 address of the Default Gateway to be used by UEs to reach the internet
   */
  virtual Ipv4Address GetUeDefaultGatewayAddress () = 0;


};




} // namespace ns3

#endif // EPC_HELPER_H
