/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2013
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
 * Authors: Ghada Badawy <gbadawy@gmail.com>
 *          Sébastien Deronne <sebastien.deronne@gmail.com>
 */

#ifndef HT_CAPABILITIES_H
#define HT_CAPABILITIES_H

#include "wifi-information-element.h"

/**
 * This defines the maximum number of supported MCSs that a STA is
 * allowed to have. Currently this number is set for IEEE 802.11n
 */
#define MAX_SUPPORTED_MCS  (77)

namespace ns3 {

/**
 * \brief The HT Capabilities Information Element
 * \ingroup wifi
 *
 * This class knows how to serialise and deserialise the HT Capabilities Information Element
 *
 * \see attribute_HtCapabilities
 */
class HtCapabilities : public WifiInformationElement
{
public:
  HtCapabilities ();
  /**
   * Set the HT supported field.
   *
   * \param htsupported the HT supported field
   */
  void SetHtSupported (uint8_t htsupported);

  /**
   * Set the HT Capabilties Info field in the HT Capabilities information element.
   *
   * \param ctrl the HT Capabilties Info field in the HT Capabilities information element
   */
  void SetHtCapabilitiesInfo (uint16_t ctrl);
  /**
   * Set the A-MPDU Parameters field in the HT Capabilities information element.
   *
   * \param ctrl the A-MPDU Parameters field in the HT Capabilities information element
   */
  void SetAmpduParameters (uint8_t ctrl);
  /**
   * Set the Supported MCS Set field in the HT Capabilities information element.
   *
   * \param ctrl1 the first 64 bytes of the Supported MCS Set field in the HT Capabilities information element
   * \param ctrl2 the last 64 bytes of the Supported MCS Set field in the HT Capabilities information element
   */
  void SetSupportedMcsSet (uint64_t ctrl1, uint64_t ctrl2);
  /**
   * Set the Extended HT Capabilties field in the HT Capabilities information element.
   *
   * \param ctrl the Extended HT Capabilties field in the HT Capabilities information element
   */
  void SetExtendedHtCapabilities (uint16_t ctrl);
  /**
   * Set the Transmit Beamforming (TxBF) Capabilties field in the HT Capabilities information element.
   *
   * \param ctrl the Transmit Beamforming (TxBF) Capabilties field in the HT Capabilities information element
   */
  void SetTxBfCapabilities (uint32_t ctrl);
  /**
   * Set the the Antenna Selection (ASEL) Capabilties field in the HT Capabilities information element.
   *
   * \param ctrl the Antenna Selection (ASEL) Capabilties field in the HT Capabilities information element
   */
  void SetAntennaSelectionCapabilities (uint8_t ctrl);

  /**
   * Set the LDPC field.
   *
   * \param ldpc
   */
  void SetLdpc (uint8_t ldpc);
  /**
   * Set the supported channel width field.
   *
   * \param supportedchannelwidth
   */
  void SetSupportedChannelWidth (uint8_t supportedchannelwidth);
  /**
   * Set the green field.
   *
   * \param greenfield
   */
  void SetGreenfield (uint8_t greenfield);
  /**
   * Set the short guard interval 20 field.
   *
   * \param shortguardinterval
   */
  void SetShortGuardInterval20 (uint8_t shortguardinterval);
  /**
   * Set the short guard interval 40 field.
   *
   * \param shortguardinterval
   */
  void SetShortGuardInterval40 (uint8_t shortguardinterval);
  /**
   * Set the maximum AMSDU length.
   *
   * \param maxamsdulength
   */
  void SetMaxAmsduLength (uint8_t maxamsdulength);
  /**
   * Set the LSIG protection support.
   *
   * \param lsigprotection
   */
  void SetLSigProtectionSupport (uint8_t lsigprotection);

  /**
   * Set the maximum AMPDU length.
   *
   * \param maxampdulength
   */
  void SetMaxAmpduLength (uint8_t maxampdulength);

  /**
   * Set the receive MCS bitmask.
   *
   * \param index
   */
  void SetRxMcsBitmask (uint8_t index);
  /**
   * Set the receive highest supported data rate.
   *
   * \param maxsupportedrate
   */
  void SetRxHighestSupportedDataRate (uint16_t maxsupportedrate);
  /**
   * Set the transmit MCS set defined.
   *
   * \param txmcssetdefined
   */
  void SetTxMcsSetDefined (uint8_t txmcssetdefined);
  /**
   * Set the transmit / receive MCS set unequal.
   *
   * \param txrxmcssetunequal
   */
  void SetTxRxMcsSetUnequal (uint8_t txrxmcssetunequal);
  /**
   * Set the transmit maximum N spatial streams.
   *
   * \param maxtxspatialstreams
   */
  void SetTxMaxNSpatialStreams (uint8_t maxtxspatialstreams);
  /**
   * Set the transmit unequal modulation.
   *
   * \param txunequalmodulation
   */
  void SetTxUnequalModulation (uint8_t txunequalmodulation);

  /**
   * Return the HT Capabilties Info field in the HT Capabilities information element.
   *
   * \return the HT Capabilties Info field in the HT Capabilities information element
   */
  uint16_t GetHtCapabilitiesInfo (void) const;
  /**
   * Return the A-MPDU Parameters field in the HT Capabilities information element.
   *
   * \return the A-MPDU Parameters field in the HT Capabilities information element
   */
  uint8_t GetAmpduParameters (void) const;
  /**
   * Return the first 64 bytes of the Supported MCS Set field in the HT Capabilities information element.
   *
   * \return the first 64 bytes of the Supported MCS Set field in the HT Capabilities information element
   */
  uint64_t GetSupportedMcsSet1 (void) const;
  /**
   * Return the last 64 bytes of the Supported MCS Set field in the HT Capabilities information element.
   *
   * \return the last 64 bytes of the Supported MCS Set field in the HT Capabilities information element
   */
  uint64_t GetSupportedMcsSet2 (void) const;
  /**
   * Return the Extended HT Capabilties field in the HT Capabilities information element.
   *
   * \return the Extended HT Capabilties field in the HT Capabilities information element
   */
  uint16_t GetExtendedHtCapabilities (void) const;
  /**
   * Return the Transmit Beamforming (TxBF) Capabilties field in the HT Capabilities information element.
   *
   * \return the Transmit Beamforming (TxBF) Capabilties field in the HT Capabilities information element
   */
  uint32_t GetTxBfCapabilities (void) const;
  /**
   * Return the Antenna Selection (ASEL) Capabilties field in the HT Capabilities information element.
   *
   * \return the Antenna Selection (ASEL) Capabilties field in the HT Capabilities information element
   */
  uint8_t GetAntennaSelectionCapabilities (void) const;

  /**
   * Return LDPC.
   *
   * \return the LDPC value
   */
  uint8_t GetLdpc (void) const;
  /**
   * Return the supported channel width.
   *
   * \return the supported chanel width
   */
  uint8_t GetSupportedChannelWidth (void) const;
  /**
   * Return the green field.
   *
   * \return the green field
   */
  uint8_t GetGreenfield (void) const;
  /**
   * Return the short guard interval 20 value.
   *
   * \return the short guard interval 20 value
   */
  uint8_t GetShortGuardInterval20 (void) const;
  /**
   * Return the short guard interval 40 value.
   *
   * \return the short guard interval 40 value
   */
  uint8_t GetShortGuardInterval40 (void) const;
  /**
   * Return the maximum AMSDU length.
   *
   * \return the maximum AMSDU length
   */
  uint8_t GetMaxAmsduLength (void) const;
  /**
   * Return the LSIG protection support.
   *
   * \return the LSIG protection support
   */
  uint8_t GetLSigProtectionSupport (void) const;

  /**
   * Return the maximum AMPDU length.
   *
   * \return the maximum AMPDU length
   */
  uint8_t GetMaxAmpduLength (void) const;
  /**
   * Return the minimum MPDU start space.
   *
   * \return the minimum MPDU start space
   */
  uint8_t GetMinMpduStartSpace (void) const;

  /**
   * Return the receive MCS bitmask.
   *
   * \return the receive MCS bitmask
   */
  uint8_t* GetRxMcsBitmask ();
  /**
   * Return the is MCS supported flag.
   *
   * \param mcs is MCS supported flag
   *
   * \return true if successful
   */
  bool IsSupportedMcs (uint8_t mcs) const;
  /**
   * Return the receive highest supported antennas.
   *
   * \return the receive highest supported antennas
   */
  uint8_t GetRxHighestSupportedAntennas (void) const;
  /**
   * Return the receive highest supported data rate.
   *
   * \return the receive highest supported data rate
   */
  uint16_t GetRxHighestSupportedDataRate (void) const;
  /**
   * Return the transmit MCS set defined.
   *
   * \return the transmit MCS set defined
   */
  uint8_t GetTxMcsSetDefined (void) const;
  /**
   * Return the transmit / receive MCS set unequal.
   *
   * \return the transmit / receive MCS set unequal
   */
  uint8_t GetTxRxMcsSetUnequal (void) const;
  /**
   * Return the transmit maximum spatial streams.
   *
   * \return the transmit maximum spatial streams
   */
  uint8_t GetTxMaxNSpatialStreams (void) const;
  /**
   * Return the transmit unequal modulation.
   *
   * \return the transmit unequal modulation
   */
  uint8_t GetTxUnequalModulation (void) const;

  /**
   * Return the element ID.
   *
   * \return the element ID
   */
  WifiInformationElementId ElementId () const;
  /**
   * Return the information field size.
   *
   * \return the information field size
   */
  uint8_t GetInformationFieldSize () const;
  /**
   * Serialize the information field.
   *
   * \param start the information field
   */
  void SerializeInformationField (Buffer::Iterator start) const;
  /**
   * Return the information field.
   *
   * \param start field
   * \param length field length
   *
   * \return the information field
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
   * Return the serialized size of this HT capability
   * information element.
   *
   * \return the serialized size of this HT capability information element
   */
  uint16_t GetSerializedSize () const;


private:
  //HT Capabilties Info field
  uint8_t m_ldpc; ///< LDPC
  uint8_t m_supportedChannelWidth; ///< supported channel width
  uint8_t m_smPowerSave; ///< SM power save
  uint8_t m_greenField; ///< green field
  uint8_t m_shortGuardInterval20; ///< short guard interval 20
  uint8_t m_shortGuardInterval40; ///< short guard interval 40
  uint8_t m_txStbc; ///< transmit STBC
  uint8_t m_rxStbc; ///< receive STBC
  uint8_t m_htDelayedBlockAck; ///< HT delayed block ack
  uint8_t m_maxAmsduLength; ///< maximum AMSDU length
  uint8_t m_dssMode40; ///< DSS mode 40
  uint8_t m_psmpSupport; ///< PSMP support
  uint8_t m_fortyMhzIntolerant; ///< 40 Mhz intolerant
  uint8_t m_lsigProtectionSupport; ///< LSIG protection support

  //A-MPDU Parameters field
  uint8_t m_maxAmpduLength; ///< maximum AMPDU length
  uint8_t m_minMpduStartSpace; ///< minimum MPDU start space
  uint8_t m_ampduReserved; ///< AMPDU reserved

  //Supported MCS Set field
  uint8_t m_reservedMcsSet1; ///< reserved MCS set 1
  uint16_t m_rxHighestSupportedDataRate; ///< receive highest supported data rate
  uint8_t m_reservedMcsSet2; ///< reserved MCS set 2
  uint8_t m_txMcsSetDefined; ///< transmit MCS set defined
  uint8_t m_txRxMcsSetUnequal; ///< transmit / receive MCS set unequal
  uint8_t m_txMaxNSpatialStreams; ///< transmit maximum number spatial streams
  uint8_t m_txUnequalModulation; ///< transmit unequal modulation
  uint32_t m_reservedMcsSet3; ///< reserved MCS set 3
  uint8_t m_rxMcsBitmask[MAX_SUPPORTED_MCS]; ///< receive MCS bitmask

  //HT Extended Capabilties field
  uint8_t m_pco; ///< PCO
  uint8_t m_pcoTransitionTime; ///< PCO trnsition time
  uint8_t m_reservedExtendedCapabilities; ///< reserved extended capabilities
  uint8_t m_mcsFeedback; ///< MCS feedback
  uint8_t m_htcSupport; ///< HTS support
  uint8_t m_reverzeDirectionResponder; ///< reverse direction responder
  uint8_t m_reservedExtendedCapabilities2; ///< reserver extended capabilities 2

  //Transmit Beamforming Capabilities field
  uint8_t m_implicitRxBfCapable; ///< implicit receive BF capable
  uint8_t m_rxStaggeredSoundingCapable; ///< receive staggered sounding capable
  uint8_t m_txStaggeredSoundingCapable; ///< transmit staggered soundign capable
  uint8_t m_rxNdpCapable; ///< receive NDP capable
  uint8_t m_txNdpCapable; ///< transmit NDP capable
  uint8_t m_implicitTxBfCapable; ///< implicit transmit BF capable
  uint8_t m_calibration; ///< calibration
  uint8_t m_explicitCsiTxBfCapable; ///< explicit CSI transmit BF capable
  uint8_t m_explicitNoncompressedSteeringCapable; ///< explicit non compressed steeering capable
  uint8_t m_explicitCompressedSteeringCapable; ///< explicit compressed steeering capable
  uint8_t m_explicitTxBfCsiFeedback; ///< explicit transmit BF CSI feedback
  uint8_t m_explicitNoncompressedBfFeedbackCapable; ///< eplicit non complressed BF feedback capable
  uint8_t m_explicitCompressedBfFeedbackCapable; ///< explicit compressed BF feedback capable
  uint8_t m_minimalGrouping; ///< minimal grouping
  uint8_t m_csiNBfAntennasSupported; ///< CSI NBF antenna supported
  uint8_t m_noncompressedSteeringNBfAntennasSupported; ///< non compressed steering NBF antenna supported
  uint8_t m_compressedSteeringNBfAntennasSupported; ///< compressed steering NBF antenna supported
  uint8_t m_csiMaxNRowsBfSupported; ///< CSI maximum number rows BF supported
  uint8_t m_channelEstimationCapability; ///< channel estimation capability
  uint8_t m_reservedTxBf; ///< reserved  transmit BF

  //ASEL Capabilities field
  uint8_t m_antennaSelectionCapability; ///< antenna selection capability
  uint8_t m_explicitCsiFeedbackBasedTxASelCapable; ///< explicit CSI feedback based transmit a sel capable
  uint8_t m_antennaIndicesFeedbackBasedTxASelCapable; ///< antenna indices feedback absed transmit a sel capable
  uint8_t m_explicitCsiFeedbackCapable; ///< explicit CSI feedback capable
  uint8_t m_antennaIndicesFeedbackCapable; ///< antenna indices feedback capable
  uint8_t m_rxASelCapable; ///< receive a sel capable
  uint8_t m_txSoundingPpdusCapable; ///< sounding PPDUS capable
  uint8_t m_reservedASel; ///< reserved a sel

  /// This is used to decide whether this element should be added to the frame or not
  uint8_t m_htSupported;
};

std::ostream &operator << (std::ostream &os, const HtCapabilities &htcapabilities);
std::istream &operator >> (std::istream &is, HtCapabilities &htcapabilities);

ATTRIBUTE_HELPER_HEADER (HtCapabilities);

} //namespace ns3

#endif /* HT_CAPABILITY_H */
