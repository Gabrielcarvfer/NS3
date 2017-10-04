/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011 Centre Tecnologic de Telecomunicacions de Catalunya (CTTC)
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
 * Author: Nicola Baldo <nbaldo@cttc.es>
 */

#ifndef LTE_MAC_SAP_H
#define LTE_MAC_SAP_H

#include <ns3/packet.h>

namespace ns3 {



/**
 * Service Access Point (SAP) offered by the MAC to the RLC
 * See Femto Forum MAC Scheduler Interface Specification v 1.11, Figure 1
 *
 * This is the MAC SAP Provider, i.e., the part of the SAP that contains the MAC methods called by the RLC
 */
class LteMacSapProvider
{
public:
  virtual ~LteMacSapProvider ();

  /**
   * Parameters for LteMacSapProvider::TransmitPdu
   *
   */
  struct TransmitPduParameters
  {
    Ptr<Packet> pdu;  /**< the RLC PDU */
    uint16_t    rnti; /**< the C-RNTI identifying the UE */
    uint8_t     lcid; /**< the logical channel id corresponding to the sending RLC instance */
    uint8_t     layer; /**< the layer value that was passed by the MAC in the call to NotifyTxOpportunity that generated this PDU */
    uint8_t     harqProcessId; /**< the HARQ process id that was passed by the MAC in the call to NotifyTxOpportunity that generated this PDU */
  };

  /**
   * send an RLC PDU to the MAC for transmission. This method is to be
   * called as a response to LteMacSapUser::NotifyTxOpportunity
   */
  virtual void TransmitPdu (TransmitPduParameters params) = 0;


  /**
   * Parameters for LteMacSapProvider::ReportBufferStatus
   *
   * \param params
   */
  struct ReportBufferStatusParameters
  {
    uint16_t rnti;  /**< the C-RNTI identifying the UE */
    uint8_t lcid;  /**< the logical channel id corresponding to the sending RLC instance */
    uint32_t txQueueSize;  /**< the current size of the RLC transmission queue */
    uint16_t txQueueHolDelay;  /**< the Head Of Line delay of the transmission queue */
    uint32_t retxQueueSize;  /**<  the current size of the RLC retransmission queue in bytes */
    uint16_t retxQueueHolDelay;  /**<  the Head Of Line delay of the retransmission queue */
    uint16_t statusPduSize;  /**< the current size of the pending STATUS RLC  PDU message in bytes */
  };

  /**
   * Report the RLC buffer status to the MAC
   *
   * \param params
   */
  virtual void ReportBufferStatus (ReportBufferStatusParameters params) = 0;


};


/**
 * Service Access Point (SAP) offered by the MAC to the RLC
 * See Femto Forum MAC Scheduler Interface Specification v 1.11, Figure 1
 *
 * This is the MAC SAP User, i.e., the part of the SAP that contains the RLC methods called by the MAC
 */
class LteMacSapUser
{
public:
  virtual ~LteMacSapUser ();
  /**
   * Called by the MAC to notify the RLC that the scheduler granted a
   * transmission opportunity to this RLC instance.
   *
   * \param bytes the number of bytes to transmit
   * \param layer the layer of transmission (MIMO)
   */
  virtual void NotifyTxOpportunity (uint32_t bytes, uint8_t layer, uint8_t harqId) = 0;

  /**
   * Called by the MAC to notify the RLC that an HARQ process related
   * to this RLC instance has failed
   *
   * @todo eventual parameters to be defined
   */
  virtual void NotifyHarqDeliveryFailure () = 0;


  /**
   * Called by the MAC to notify the RLC of the reception of a new PDU
   *
   * \param p
   */
  virtual void ReceivePdu (Ptr<Packet> p) = 0;

};

///////////////////////////////////////

template <class C>
class EnbMacMemberLteMacSapProvider : public LteMacSapProvider
{
public:
  EnbMacMemberLteMacSapProvider (C* mac);

  // inherited from LteMacSapProvider
  virtual void TransmitPdu (TransmitPduParameters params);
  virtual void ReportBufferStatus (ReportBufferStatusParameters params);

private:
  C* m_mac;
};


template <class C>
EnbMacMemberLteMacSapProvider<C>::EnbMacMemberLteMacSapProvider (C* mac)
  : m_mac (mac)
{
}

template <class C>
void EnbMacMemberLteMacSapProvider<C>::TransmitPdu (TransmitPduParameters params)
{
  m_mac->DoTransmitPdu (params);
}

template <class C>
void EnbMacMemberLteMacSapProvider<C>::ReportBufferStatus (ReportBufferStatusParameters params)
{
  m_mac->DoReportBufferStatus (params);
}


} // namespace ns3


#endif // LTE_MAC_SAP_H
