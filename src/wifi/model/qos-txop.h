/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2006, 2009 INRIA
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
 * Authors: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 *          Mirko Banchi <mk.banchi@gmail.com>
 */

#ifndef QOS_TXOP_H
#define QOS_TXOP_H

#include "ns3/traced-value.h"
#include "block-ack-manager.h"
#include "txop.h"
#include "qos-utils.h"

class AmpduAggregationTest;
class TwoLevelAggregationTest;
class HeAggregationTest;

namespace ns3 {

class QosBlockedDestinations;
class MgtAddBaResponseHeader;
class MgtDelBaHeader;
class AggregationCapableTransmissionListener;
class WifiTxVector;

/**
 * Enumeration for type of station
 */
enum TypeOfStation
{
  STA,
  AP,
  ADHOC_STA,
  MESH,
  HT_STA,
  HT_AP,
  HT_ADHOC_STA,
  OCB
};

/**
 * \brief Handle packet fragmentation and retransmissions for QoS data frames as well
 * as MSDU aggregation (A-MSDU) and block ack sessions, for a given access class.
 * \ingroup wifi
 *
 * This class implements the packet fragmentation and retransmission policy for
 * QoS data frames. It uses the ns3::MacLow and ns3::ChannelAccessManager helper classes
 * to respectively send packets and decide when to send them. Packets are stored
 * in a ns3::WifiMacQueue until they can be sent.
 *
 * This queue contains packets for a particular access class.
 * Possibles access classes are:
 *   - AC_VO : voice, tid = 6,7
 *   - AC_VI : video, tid = 4,5
 *   - AC_BE : best-effort, tid = 0,3
 *   - AC_BK : background, tid = 1,2
 *
 * This class also implements block ack sessions and MSDU aggregation (A-MSDU).
 * If A-MSDU is enabled for that access class, it picks several packets from the
 * queue instead of a single one and sends the aggregated packet to ns3::MacLow.
 *
 * The fragmentation policy currently implemented uses a simple
 * threshold: any packet bigger than this threshold is fragmented
 * in fragments whose size is smaller than the threshold.
 *
 * The retransmission policy is also very simple: every packet is
 * retransmitted until it is either successfully transmitted or
 * it has been retransmitted up until the ssrc or slrc thresholds.
 *
 * The rts/cts policy is similar to the fragmentation policy: when
 * a packet is bigger than a threshold, the rts/cts protocol is used.
 */

class QosTxop : public Txop
{
public:
  /// Allow test cases to access private members
  friend class ::AmpduAggregationTest;
  friend class ::TwoLevelAggregationTest;
  friend class ::HeAggregationTest;

  std::map<Mac48Address, bool> m_aMpduEnabled; //!< list containing flags whether A-MPDU is enabled for a given destination address

  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);

  QosTxop ();
  virtual ~QosTxop ();

  /**
   * Check for QoS TXOP.
   *
   * \returns true if QoS TXOP.
   */
  bool IsQosTxop (void) const;

  /**
   * Set WifiRemoteStationsManager this QosTxop is associated to.
   *
   * \param remoteManager WifiRemoteStationManager.
   */
  void SetWifiRemoteStationManager (const Ptr<WifiRemoteStationManager> remoteManager);
  /**
   * Set type of station with the given type.
   *
   * \param type the type of station.
   */
  void SetTypeOfStation (TypeOfStation type);
  /**
   * Return type of station.
   *
   * \return type of station.
   */
  TypeOfStation GetTypeOfStation (void) const;

  /**
   * \param address recipient address of the peer station
   * \param tid traffic ID.
   *
   * \return true if a block ack agreement is established, false otherwise.
   *
   * Checks if a block ack agreement is established with station addressed by
   * <i>recipient</i> for tid <i>tid</i>.
   */
  bool GetBaAgreementEstablished (Mac48Address address, uint8_t tid) const;
  /**
   * \param address recipient address of the peer station
   * \param tid traffic ID.
   *
   * \return the negociated buffer size during ADDBA handshake.
   *
   * Returns the negociated buffer size during ADDBA handshake with station addressed by
   * <i>recipient</i> for tid <i>tid</i>.
   */
  uint16_t GetBaBufferSize (Mac48Address address, uint8_t tid) const;
  /**
   * \param address recipient address of the peer station
   * \param tid traffic ID.
   *
   * \return the starting sequence number of the originator transmit window.
   *
   * Returns the current starting sequence number of the transmit window on the
   * originator (WinStartO) of the Block Ack agreement established with the given
   * recipient for the given TID.
   */
  uint16_t GetBaStartingSequence (Mac48Address address, uint8_t tid) const;

  /* dcf notifications forwarded here */
  /**
   * Notify the EDCAF that access has been granted.
   */
  void NotifyAccessGranted (void);
  /**
   * Notify the EDCAF that internal collision has occurred.
   */
  void NotifyInternalCollision (void);
  /**
   * Notify the EDCAF that collision has occurred.
   */
  void NotifyCollision (void);

  /* Event handlers */
  /**
   * Event handler when a CTS timeout has occurred.
   *
   * \param mpduList the list of MPDUs that were not transmitted
   */
  void NotifyMissedCts (std::list<Ptr<WifiMacQueueItem>> mpduList);
  /**
   * Event handler when an ACK is received.
   */
  void GotAck (void);
  /**
   * Event handler when a Block ACK is received.
   *
   * \param blockAck block ack.
   * \param recipient address of the recipient.
   * \param rxSnr SNR of the block ack itself.
   * \param txMode wifi mode.
   * \param dataSnr reported data SNR from the peer.
   */
  void GotBlockAck (const CtrlBAckResponseHeader *blockAck, Mac48Address recipient, double rxSnr, WifiMode txMode, double dataSnr);
  /**
   * Event handler when a Block ACK timeout has occurred.
   * \param nMpdus number of MPDUs sent in the A-MPDU transmission that results in a Block ACK timeout.
   */
  void MissedBlockAck (uint8_t nMpdus);
  /**
   * Event handler when an ADDBA response is received.
   *
   * \param respHdr ADDBA response header.
   * \param recipient address of the recipient.
   */
  void GotAddBaResponse (const MgtAddBaResponseHeader *respHdr, Mac48Address recipient);
  /**
   * Event handler when a DELBA frame is received.
   *
   * \param delBaHdr DELBA header.
   * \param recipient address of the recipient.
   */
  void GotDelBaFrame (const MgtDelBaHeader *delBaHdr, Mac48Address recipient);
  /**
   * Event handler when an ACK is missed.
   */
  void MissedAck (void);

  /**
   * Start transmission for the next packet if allowed by the TxopLimit.
   */
  void StartNextPacket (void);
  /**
   * Event handler when a transmission that does not require an ACK has completed.
   */
  void EndTxNoAck (void);
  /**
   * Restart access request if needed.
   */
  void RestartAccessIfNeeded (void);
  /**
   * Request access from DCF manager if needed.
   */
  void StartAccessIfNeeded (void);

  /**
   * Check if Block ACK Request should be re-transmitted.
   *
   * \return true if BAR should be re-transmitted,
   *         false otherwise.
   */
  bool NeedBarRetransmission (void);

  /**
   * Check if the current packet should be fragmented.
   *
   * \return true if the current packet should be fragmented,
   *         false otherwise.
   */
  bool NeedFragmentation (void) const;

  /**
   * Get the next fragment from the packet with
   * appropriate Wifi header for the fragment.
   *
   * \param hdr Wi-Fi header.
   *
   * \return the fragment with the current fragment number.
   */
  Ptr<Packet> GetFragmentPacket (WifiMacHeader *hdr);

  /**
   * Set the access category of this EDCAF.
   *
   * \param ac access category.
   */
  void SetAccessCategory (AcIndex ac);

  /**
   * \param packet packet to send.
   * \param hdr header of packet to send.
   *
   * Store the packet in the front of the internal queue until it
   * can be sent safely.
   */
  void PushFront (Ptr<const Packet> packet, const WifiMacHeader &hdr);

  /**
   * Complete block ACK configuration.
   */
  void CompleteConfig (void);

  /**
   * Set threshold for block ACK mechanism. If number of packets in the
   * queue reaches the threshold, block ACK mechanism is used.
   *
   * \param threshold block ack threshold value.
   */
  void SetBlockAckThreshold (uint8_t threshold);
  /**
   * Return the current threshold for block ACK mechanism.
   *
   * \return the current threshold for block ACK mechanism.
   */
  uint8_t GetBlockAckThreshold (void) const;

  /**
   * Set the Block Ack inactivity timeout.
   *
   * \param timeout the Block Ack inactivity timeout.
   */
  void SetBlockAckInactivityTimeout (uint16_t timeout);
  /**
   * Sends DELBA frame to cancel a block ack agreement with sta
   * addressed by <i>addr</i> for tid <i>tid</i>.
   *
   * \param addr address of the recipient.
   * \param tid traffic ID.
   * \param byOriginator flag to indicate whether this is set by the originator.
   */
  void SendDelbaFrame (Mac48Address addr, uint8_t tid, bool byOriginator);
  /**
   * Stores an MPDU (part of an A-MPDU) in blockackagreement (i.e. the sender is waiting
   * for a blockack containing the sequence number of this MPDU).
   * It also calls NotifyMpdu transmission that updates the status of OriginatorBlockAckAgreement.
   *
   * \param mpdu received MPDU.
   */
  void CompleteMpduTx (Ptr<WifiMacQueueItem> mpdu);
  /**
   * Return whether A-MPDU is used to transmit data to a peer station.
   *
   * \param dest address of peer station
   * \returns true if A-MPDU is used by the peer station
   */
  bool GetAmpduExist (Mac48Address dest) const;
  /**
   * Set indication whether A-MPDU is used to transmit data to a peer station.
   *
   * \param dest address of peer station.
   * \param enableAmpdu flag whether A-MPDU is used or not.
   */
  void SetAmpduExist (Mac48Address dest, bool enableAmpdu);
  /**
   * Set the timeout to wait for ADDBA response.
   *
   * \param addBaResponseTimeout the timeout to wait for ADDBA response
   */
  void SetAddBaResponseTimeout (Time addBaResponseTimeout);
  /**
   * Get the timeout for ADDBA response.
   *
   * \returns the timeout to wait for ADDBA response
   */
  Time GetAddBaResponseTimeout (void) const;
  /**
   * Set the timeout for failed BA agreement. During the timeout period,
   * all packets will be transmitted using normal MPDU.
   *
   * \param failedAddBaTimeout the timeout for failed BA agreement
   */
  void SetFailedAddBaTimeout (Time failedAddBaTimeout);
  /**
   * Get the timeout for failed BA agreement.
   *
   * \returns the timeout for failed BA agreement
   */
  Time GetFailedAddBaTimeout (void) const;

  /**
   * Return the next sequence number for the given header.
   *
   * \param hdr Wi-Fi header.
   *
   * \return the next sequence number.
   */
  uint16_t GetNextSequenceNumberFor (const WifiMacHeader *hdr);
  /**
   * Return the next sequence number for the Traffic ID and destination, but do not pick it (i.e. the current sequence number remains unchanged).
   *
   * \param hdr Wi-Fi header.
   *
   * \return the next sequence number.
   */
  uint16_t PeekNextSequenceNumberFor (const WifiMacHeader *hdr);
  /**
   * Peek the next frame to transmit to the given receiver and of the given
   * TID from the Block Ack manager retransmit queue first and, if not found, from
   * the EDCA queue. If <i>tid</i> is equal to 8 (invalid value) and <i>recipient</i>
   * is the broadcast address, the first available frame is returned.
   * Note that A-MSDU aggregation is never attempted (this is relevant if the
   * frame is peeked from the EDCA queue). If the frame is peeked from the EDCA
   * queue, it is assigned a sequence number peeked from MacTxMiddle.
   *
   * \param tid traffic ID.
   * \param recipient the receiver station address.
   * \returns the peeked frame.
   */
  Ptr<const WifiMacQueueItem> PeekNextFrame (uint8_t tid = 8, Mac48Address recipient = Mac48Address::GetBroadcast ());
  /**
   * Dequeue the frame that has been previously peeked by calling PeekNextFrame
   * or PeekNextFrameByTidAndAddress. If the peeked frame is a QoS Data frame,
   * it is actually dequeued if it meets the constraint on the maximum A-MPDU
   * size (by assuming that the frame has to be aggregated to an existing A-MPDU
   * of the given size) and its transmission time does not exceed the given
   * PPDU duration limit (if strictly positive). If the peeked frame is a unicast
   * QoS Data frame stored in the EDCA queue, attempt to perform A-MSDU aggregation
   * (while meeting the constraints mentioned above) if <i>aggregate</i> is true
   * and assign a sequence number to the dequeued frame.
   *
   * \param peekedItem the peeked frame.
   * \param txVector the TX vector used to transmit the peeked frame
   * \param ampduSize the size of the existing A-MPDU, if any
   * \param ppduDurationLimit the limit on the PPDU duration
   * \returns the dequeued frame.
   */
  Ptr<WifiMacQueueItem> DequeuePeekedFrame (Ptr<const WifiMacQueueItem> peekedItem, WifiTxVector txVector,
                                            bool aggregate = true, uint32_t ampduSize = 0,
                                            Time ppduDurationLimit = Seconds (0));
  /**
   * Compute the MacLow transmission parameters for the given frame. Allowed frames
   * are those handled by a QosTxop (QoS data frames, BlockAckReq frames, ADDBA
   * Request/Response, DELBA Request).
   *
   * \param frame the given frame
   * \return the MacLow transmission parameters.
   */
  MacLowTransmissionParameters GetTransmissionParameters (Ptr<const WifiMacQueueItem> frame) const;

  /**
   * The packet we sent was successfully received by the receiver.
   *
   * \param hdr the header of the packet that we successfully sent.
   */
  void BaTxOk (const WifiMacHeader &hdr);
  /**
   * The packet we sent was successfully received by the receiver.
   *
   * \param hdr the header of the packet that we failed to sent.
   */
  void BaTxFailed (const WifiMacHeader &hdr);

  /**
   * This functions are used only to correctly set source address in A-MSDU subframes.
   * If aggregating sta is a STA (in an infrastructured network):
   *   SA = Address2
   * If aggregating sta is an AP
   *   SA = Address3
   *
   * \param hdr Wi-Fi header
   * \return Mac48Address
   */
  Mac48Address MapSrcAddressForAggregation (const WifiMacHeader &hdr);
  /**
   * This functions are used only to correctly set destination address in A-MSDU subframes.
   * If aggregating sta is a STA (in an infrastructured network):
   *   DA = Address3
   * If aggregating sta is an AP
   *   DA = Address1
   *
   * \param hdr Wi-Fi header
   * \return Mac48Address
   */
  Mac48Address MapDestAddressForAggregation (const WifiMacHeader &hdr);


private:
  /// allow AggregationCapableTransmissionListener class access
  friend class AggregationCapableTransmissionListener;

  /**
   * If number of packets in the queue reaches m_blockAckThreshold value, an ADDBA Request frame
   * is sent to destination in order to setup a block ack.
   *
   * \return true if we tried to set up block ACK, false otherwise.
   */
  bool SetupBlockAckIfNeeded (void);
  /**
   * Sends an ADDBA Request to establish a block ack agreement with sta
   * addressed by <i>recipient</i> for tid <i>tid</i>.
   *
   * \param recipient address of the recipient.
   * \param tid traffic ID.
   * \param startSeq starting sequence.
   * \param timeout timeout value.
   * \param immediateBAck flag to indicate whether immediate block ack is used.
   */
  void SendAddBaRequest (Mac48Address recipient, uint8_t tid, uint16_t startSeq,
                         uint16_t timeout, bool immediateBAck);
  /**
   * After that all packets, for which a block ack agreement was established, have been
   * transmitted, we have to send a block ack request.
   *
   * \param bar the block ack request.
   */
  void SendBlockAckRequest (const Bar &bar);
  /**
   * Check if the given MPDU is to be considered old according to the current
   * starting sequence number of the transmit window, provided that a block ack
   * agreement has been established with the recipient for the given TID.
   *
   * \param mpdu the given MPDU
   * \return true if the MPDU is to be considered old, false otherwise
   */
  bool IsQosOldPacket (Ptr<const WifiMacQueueItem> mpdu);
  /**
   * For now is typically invoked to complete transmission of a packets sent with ack policy
   * Block Ack: the packet is buffered and dcf is reset.
   */
  void CompleteTx (void);
  /**
   * Verifies if dequeued packet has to be transmitted with ack policy Block Ack. This happens
   * if an established block ack agreement exists with the receiver.
   */
  void VerifyBlockAck (void);
  /**
   * Return the remaining duration in the current TXOP.
   *
   * \return the remaining duration in the current TXOP.
   */
  Time GetTxopRemaining (void) const;
  /**
   * Update backoff and restart access if needed.
   */
  void TerminateTxop (void);

  /**
   * Calculate the size of the next fragment.
   *
   * \return the size of the next fragment.
   */
  uint32_t GetNextFragmentSize (void) const;
  /**
   * Calculate the size of the current fragment.
   *
   * \return the size of the current fragment.
   */
  uint32_t GetFragmentSize (void) const;
  /**
   * Calculate the offset for the current fragment.
   *
   * \return the offset for the current fragment.
   */
  uint32_t GetFragmentOffset (void) const;
  /**
   * Check if the current fragment is the last fragment.
   *
   * \return true if the current fragment is the last fragment,
   *         false otherwise.
   */
  bool IsLastFragment (void) const;

  /**
   * Check if the current packet is fragmented because of an exceeded TXOP duration.
   *
   * \return true if the current packet is fragmented because of an exceeded TXOP duration,
   *         false otherwise
   */
  bool IsTxopFragmentation (void) const;
  /**
   * Calculate the size of the current TXOP fragment.
   *
   * \return the size of the current TXOP fragment
   */
  uint32_t GetTxopFragmentSize (void) const;
  /**
   * Calculate the number of TXOP fragments needed for the transmission of the current packet.
   *
   * \return the number of TXOP fragments needed for the transmission of the current packet
   */
  uint32_t GetNTxopFragment (void) const;
  /**
   * Calculate the size of the next TXOP fragment.
   *
   * \param fragmentNumber number of the next fragment
   * \returns the next TXOP fragment size
   */
  uint32_t GetNextTxopFragmentSize (uint32_t fragmentNumber) const;
  /**
   * Calculate the offset for the fragment.
   *
   * \param fragmentNumber number of the fragment
   * \returns the TXOP fragment offset
   */
  uint32_t GetTxopFragmentOffset (uint32_t fragmentNumber) const;
  /**
   * Callback when ADDBA response is not received after timeout.
   *
   * \param recipient MAC address of recipient
   * \param tid traffic ID
   */
  void AddBaResponseTimeout (Mac48Address recipient, uint8_t tid);
  /**
   * Reset BA agreement after BA negotiation failed.
   *
   * \param recipient MAC address of recipient
   * \param tid traffic ID
   */
  void ResetBa (Mac48Address recipient, uint8_t tid);

  void DoDispose (void);
  void DoInitialize (void);

  AcIndex m_ac;                                         //!< the access category
  TypeOfStation m_typeOfStation;                        //!< the type of station
  Ptr<QosBlockedDestinations> m_qosBlockedDestinations; //!< QOS blocked destinations
  Ptr<BlockAckManager> m_baManager;                     //!< the Block ACK manager
  uint8_t m_blockAckThreshold;                          //!< the Block ACK threshold
  BlockAckType m_blockAckType;                          //!< the Block ACK type
  Time m_currentPacketTimestamp;                        //!< the current packet timestamp
  uint16_t m_blockAckInactivityTimeout;                 //!< the Block ACK inactivity timeout
  Bar m_currentBar;                                     //!< the current BAR
  Time m_startTxop;                                     //!< the start TXOP time
  bool m_isAccessRequestedForRts;                       //!< flag whether access is requested to transmit a RTS frame
  bool m_currentIsFragmented;                           //!< flag whether current packet is fragmented
  Time m_addBaResponseTimeout;                          //!< timeout for ADDBA response
  Time m_failedAddBaTimeout;                            //!< timeout after failed BA agreement
  bool m_useExplicitBarAfterMissedBlockAck;             //!< flag whether explicit Block Ack Request should be sent upon missed Block Ack Response

  TracedCallback<Time, Time> m_txopTrace; //!< TXOP trace callback
};

} //namespace ns3

#endif /* QOS_TXOP_H */
