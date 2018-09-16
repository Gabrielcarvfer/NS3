/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2016 Sébastien Deronne
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

#ifndef HT_OPERATION_H
#define HT_OPERATION_H

#include "wifi-information-element.h"

/**
 * This defines the maximum number of supported MCSs that a STA is
 * allowed to have. Currently this number is set for IEEE 802.11n
 */
#define MAX_SUPPORTED_MCS  (77)

namespace ns3 {

/// HtProtectionType enumeration
enum HtProtectionType
{
  NO_PROTECTION,
  NON_MEMBER_PROTECTION,
  TWENTY_MHZ_PROTECTION,
  MIXED_MODE_PROTECTION
};

/**
 * \brief The HT Operation Information Element
 * \ingroup wifi
 *
 * This class knows how to serialise and deserialise
 * the HT Operation Information Element
 *
 * \see attribute_HtOperation
 */
class HtOperation : public WifiInformationElement
{
public:
  HtOperation ();
  /**
   * Set the HT Supported.
   *
   * \param htsupported the HT Supported flag
   */
  void SetHtSupported (uint8_t htsupported);

  /**
   * Set the Primary Channel field in the HT Operation information element.
   *
   * \param ctrl the Primary Channel field in the HT Operation information element
   */
  void SetPrimaryChannel (uint8_t ctrl);
  /**
   * Set the Information Subset 1 field in the HT Operation information element.
   *
   * \param ctrl the Information Subset 1 field in the HT Operation information element
   */
  void SetInformationSubset1 (uint8_t ctrl);
  /**
   * Set the Information Subset 2 field in the HT Operation information element.
   *
   * \param ctrl the Information Subset 2 field in the HT Operation information element
   */
  void SetInformationSubset2 (uint16_t ctrl);
  /**
   * Set the Information Subset 3 field in the HT Operation information element.
   *
   * \param ctrl the Information Subset 3 field in the HT Operation information element
   */
  void SetInformationSubset3 (uint16_t ctrl);
  /**
   * Set the Basic MCS Set field in the HT Operation information element.
   *
   * \param ctrl1 the first 64 bytes of the Basic MCS Set field in the HT Operation information element
   * \param ctrl2 the last 64 bytes of the Basic MCS Set field in the HT Operation information element
   */
  void SetBasicMcsSet (uint64_t ctrl1, uint64_t ctrl2);

  /**
   * Set the secondary channel offset.
   *
   * \param secondarychanneloffset the secondary channel offset
   */
  void SetSecondaryChannelOffset (uint8_t secondarychanneloffset);
  /**
   * Set the STA channel width.
   *
   * \param stachannelwidth the STA channel width
   */
  void SetStaChannelWidth (uint8_t stachannelwidth);
  /**
   * Set the RIFS mode.
   *
   * \param rifsmode the RIFS mode
   */
  void SetRifsMode (uint8_t rifsmode);

  /**
   * Set the HT protection.
   *
   * \param htprotection the HT protection
   */
  void SetHtProtection (uint8_t htprotection);
  /**
   * Set the non GF HT STAs present.
   *
   * \param nongfhtstaspresent the non GF HT STAs present
   */
  void SetNonGfHtStasPresent (uint8_t nongfhtstaspresent);
  /**
   * Set the OBSS non HT STAs present.
   *
   * \param obssnonhtstaspresent the OBSS non HTA STAs present
   */
  void SetObssNonHtStasPresent (uint8_t obssnonhtstaspresent);

  /**
   * Set the dual beacon.
   *
   * \param dualbeacon the dual beacon
   */
  void SetDualBeacon (uint8_t dualbeacon);
  /**
   * Set the dual CTS protection.
   *
   * \param dualctsprotection the dual CTS protection
   */
  void SetDualCtsProtection (uint8_t dualctsprotection);
  /**
   * Set the STBC beacon.
   *
   * \param stbcbeacon the STBC beacon
   */
  void SetStbcBeacon (uint8_t stbcbeacon);
  /**
   * Set the LSIG TXOP protection full support.
   *
   * \param lsigtxopprotectionfullsupport the LSIG TXOP protection full support
   */
  void SetLSigTxopProtectionFullSupport (uint8_t lsigtxopprotectionfullsupport);
  /**
   * Set the PCO active.
   *
   * \param pcoactive the PCO active
   */
  void SetPcoActive (uint8_t pcoactive);
  /**
   * Set the PCO phase.
   *
   * \param pcophase the PCO phase
   */
  void SetPhase (uint8_t pcophase);

  /**
   * Set the receive MCS bitmask.
   *
   * \param index the MCS bitmask
   */
  void SetRxMcsBitmask (uint8_t index);
  /**
   * Set the receive highest supported data rate.
   *
   * \param maxsupportedrate the maximum supported data rate
   */
  void SetRxHighestSupportedDataRate (uint16_t maxsupportedrate);
  /**
   * Set the transmit MCS set defined.
   *
   * \param txmcssetdefined the transmit MCS set defined
   */
  void SetTxMcsSetDefined (uint8_t txmcssetdefined);
  /**
   * Set the transmit / receive MCS set unequal.
   *
   * \param txrxmcssetunequal the transmit / reeive MCS set unequal
   */
  void SetTxRxMcsSetUnequal (uint8_t txrxmcssetunequal);
  /**
   * Set the transmit maximum number spatial streams.
   *
   * \param maxtxspatialstreams the maximum transmit spatial streams
   */
  void SetTxMaxNSpatialStreams (uint8_t maxtxspatialstreams);
  /**
   * Set the transmit unequal modulation.
   *
   * \param txunequalmodulation the transmit unequal modulation
   */
  void SetTxUnequalModulation (uint8_t txunequalmodulation);

  /**
   * Return the Primary Channel field in the HT Operation information element.
   *
   * \return the Primary Channel field in the HT Operation information element
   */
  uint8_t GetPrimaryChannel (void) const;
  /**
   * Return the Information Subset 1 field in the HT Operation information element.
   *
   * \return the Information Subset 1 field in the HT Operation information element
   */
  uint8_t GetInformationSubset1 (void) const;
  /**
   * Return the Information Subset 2 field in the HT Operation information element.
   *
   * \return the Information Subset 2 field in the HT Operation information element
   */
  uint16_t GetInformationSubset2 (void) const;
  /**
   * Return the Information Subset 3 field in the HT Operation information element.
   *
   * \return the Information Subset 3 field in the HT Operation information element
   */
  uint16_t GetInformationSubset3 (void) const;
  /**
   * Return the first 64 bytes of the Basic MCS Set field in the HT Operation information element.
   *
   * \return the first 64 bytes of the Basic MCS Set field in the HT Operation information element
   */
  uint64_t GetBasicMcsSet1 (void) const;
  /**
   * Return the last 64 bytes of the Basic MCS Set field in the HT Operation information element.
   *
   * \return the last 64 bytes of the Basic MCS Set field in the HT Operation information element
   */
  uint64_t GetBasicMcsSet2 (void) const;

  /**
   * Return the secondary channel offset.
   *
   * \return the secondary channel offset
   */
  uint8_t GetSecondaryChannelOffset (void) const;
  /**
   * Return the STA channel width.
   *
   * \return the STA channel width
   */
  uint8_t GetStaChannelWidth (void) const;
  /**
   * Return the RIFS mode.
   *
   * \return the RIFS mode
   */
  uint8_t GetRifsMode (void) const;

  /**
   * Return the HT protection.
   *
   * \return the HT protection
   */
  uint8_t GetHtProtection (void) const;
  /**
   * Return the non GF HT STAs present.
   *
   * \return the non GF HT STAs present
   */
  uint8_t GetNonGfHtStasPresent (void) const;
  /**
   * Return the OBSS non HT STAs present.
   *
   * \return the OBSS non HT STAs present
   */
  uint8_t GetObssNonHtStasPresent (void) const;

  /**
   * Return dual beacon.
   *
   * \return the dual beacon
   */
  uint8_t GetDualBeacon (void) const;
  /**
   * Return dual CTS protection.
   *
   * \return the dual CTS protection
   */
  uint8_t GetDualCtsProtection (void) const;
  /**
   * Return STBC beacon.
   *
   * \return the STBC beacon
   */
  uint8_t GetStbcBeacon (void) const;
  /**
   * Return LSIG TXOP protection full support.
   *
   * \return the LSIG TXOP protection full support
   */
  uint8_t GetLSigTxopProtectionFullSupport (void) const;
  /**
   * Return PCO active.
   *
   * \return the PCO active
   */
  uint8_t GetPcoActive (void) const;
  /**
   * Return phase.
   *
   * \return the phase
   */
  uint8_t GetPhase (void) const;

  /**
   * Return MCS is supported.
   *
   * \param mcs MCS
   *\
   * \return the MCS is supported
   */
  bool IsSupportedMcs (uint8_t mcs) const;
  /**
   * Return receive highest supported data rate.
   *
   * \return receive highest supported data rate
   */
  uint16_t GetRxHighestSupportedDataRate (void) const;
  /**
   * Return transmit MCS set defined.
   *
   * \return the transmit MCS set defined
   */
  uint8_t GetTxMcsSetDefined (void) const;
  /**
   * Return transmit / receive MCS set unequal.
   *
   * \return transmit / receive MCS set unequal
   */
  uint8_t GetTxRxMcsSetUnequal (void) const;
  /**
   * Return transmit maximum number spatial streams.
   *
   * \return transmit maximum number spatial streams
   */
  uint8_t GetTxMaxNSpatialStreams (void) const;
  /**
   * Return transmit unequal modulation.
   *
   * \return transmit unequal modulation
   */
  uint8_t GetTxUnequalModulation (void) const;

  /**
   * Return element ID.
   *
   * \return element ID
   */
  WifiInformationElementId ElementId () const;
  /**
   * Return information field size.
   *
   * \return information field size
   */
  uint8_t GetInformationFieldSize () const;
  /**
   * Serialize information field.
   *
   * \param start iterator
   */
  void SerializeInformationField (Buffer::Iterator start) const;
  /**
   * DeSerialize information field.
   *
   * \param start iterator
   * \param length length
   * \returns information field
   */
  uint8_t DeserializeInformationField (Buffer::Iterator start,
                                       uint8_t length);
  /**
   * This information element is a bit special in that it is only
   * included if the STA is an HT STA. To support this we
   * override the Serialize and GetSerializedSize methods of
   * WifiInformationElement.
   *
   * \param start
   *
   * \return an iterator
   */
  Buffer::Iterator Serialize (Buffer::Iterator start) const;
  /**
   * Return the serialized size of this HT Operation IE.
   *
   * \return the serialized size of this HT Operation IE
   */
  uint16_t GetSerializedSize () const;


private:
  uint8_t m_primaryChannel; ///< primary channel

  //HT Information Subset 1
  uint8_t m_secondaryChannelOffset; ///< secondary channel offset
  uint8_t m_staChannelWidth; ///< STA channel width
  uint8_t m_rifsMode; ///< RIFS mode
  uint8_t m_reservedInformationSubset1; ///< reserved information subset 1

  //HT Information Subset 2
  uint8_t m_htProtection; ///< HT protection
  uint8_t m_nonGfHtStasPresent; ///< non GF HT STAs present
  uint8_t m_reservedInformationSubset2_1; ///< reserved information subset 2-1
  uint8_t m_obssNonHtStasPresent; ///< OBSS NON HT STAs present
  uint8_t m_reservedInformationSubset2_2; ///< reserved information subset 2-2

  //HT Information Subset 3
  uint8_t m_reservedInformationSubset3_1; ///< reserved information subset 3-1
  uint8_t m_dualBeacon; ///< dual beacon
  uint8_t m_dualCtsProtection; ///< dual CTS protection
  uint8_t m_stbcBeacon; ///< STBC beacon
  uint8_t m_lSigTxopProtectionFullSupport; ///< LSIG TXOP protection full support
  uint8_t m_pcoActive; ///< PCO active
  uint8_t m_pcoPhase; ///< PCO phase
  uint8_t m_reservedInformationSubset3_2; ///< reserved information subset 3-2

  //Basic MCS Set field
  uint8_t m_reservedMcsSet1; ///< reserved MCS set 1
  uint16_t m_rxHighestSupportedDataRate; ///< receive highest supported data rate
  uint8_t m_reservedMcsSet2; ///< reserved MCS set2
  uint8_t m_txMcsSetDefined; ///< transmit MCS set defined
  uint8_t m_txRxMcsSetUnequal; ///< transmit / receive MCS set unequal
  uint8_t m_txMaxNSpatialStreams; ///< transmit maximum number spatial streams
  uint8_t m_txUnequalModulation; ///< transmit unequal modulation
  uint32_t m_reservedMcsSet3; ///< reserved MCS set 3
  uint8_t m_rxMcsBitmask[MAX_SUPPORTED_MCS]; ///< receive MCS bitmask

  /// This is used to decide whether this element should be added to the frame or not
  uint8_t m_htSupported;
};

std::ostream &operator << (std::ostream &os, const HtOperation &htOperation);

} //namespace ns3

#endif /* HT_OPERATION_H */
