/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2005,2006,2007 INRIA
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

#ifndef WIFI_REMOTE_STATION_MANAGER_H
#define WIFI_REMOTE_STATION_MANAGER_H

#include "ns3/traced-callback.h"
#include "ns3/object.h"
#include "ns3/data-rate.h"
#include "ns3/mac48-address.h"
#include "wifi-mode.h"
#include "wifi-utils.h"
#include "wifi-remote-station-info.h"
#include "ht-capabilities.h"
#include "vht-capabilities.h"
#include "he-capabilities.h"

namespace ns3 {

class WifiPhy;
class WifiMac;
class WifiMacHeader;
class Packet;
class WifiTxVector;

struct WifiRemoteStationState;

/**
 * \brief hold per-remote-station state.
 *
 * The state in this class is used to keep track
 * of association status if we are in an infrastructure
 * network and to perform the selection of tx parameters
 * on a per-packet basis.
 *
 * This class is typically subclassed and extended by
 * rate control implementations
 */
struct WifiRemoteStation
{
  virtual ~WifiRemoteStation () {};
  WifiRemoteStationState *m_state;  //!< Remote station state
  uint32_t m_ssrc;                  //!< STA short retry count
  uint32_t m_slrc;                  //!< STA long retry count
  uint8_t m_tid;                    //!< traffic ID
};

/**
 * A struct that holds information about each remote station.
 */
struct WifiRemoteStationState
{
  /**
   * State of the station
   */
  enum
  {
    BRAND_NEW,
    DISASSOC,
    WAIT_ASSOC_TX_OK,
    GOT_ASSOC_TX_OK
  } m_state;

  /**
   * This member is the list of WifiMode objects that comprise the
   * OperationalRateSet parameter for this remote station. This list
   * is constructed through calls to
   * WifiRemoteStationManager::AddSupportedMode(), and an API that
   * allows external access to it is available through
   * WifiRemoteStationManager::GetNSupported() and
   * WifiRemoteStationManager::GetSupported().
   */
  WifiModeList m_operationalRateSet; //!< opertional rate set
  WifiModeList m_operationalMcsSet; //!< operational MCS set
  Mac48Address m_address;  //!< Mac48Address of the remote station
  WifiRemoteStationInfo m_info; //!< remote station info
  Ptr<const HtCapabilities> m_htCapabilities;  //!< remote station HT capabilities
  Ptr<const VhtCapabilities> m_vhtCapabilities;  //!< remote station VHT capabilities
  Ptr<const HeCapabilities> m_heCapabilities;  //!< remote station HE capabilities

  uint16_t m_channelWidth;    //!< Channel width (in MHz) supported by the remote station
  uint16_t m_guardInterval;   //!< HE Guard interval duration (in nanoseconds) supported by the remote station
  uint8_t m_ness;             //!< Number of streams in beamforming of the remote station
  bool m_aggregation;         //!< Flag if MPDU aggregation is used by the remote station
  bool m_shortPreamble;       //!< Flag if short PLCP preamble is supported by the remote station
  bool m_shortSlotTime;       //!< Flag if short ERP slot time is supported by the remote station
  bool m_qosSupported;        //!< Flag if HT is supported by the station
};

/**
 * \ingroup wifi
 * \brief hold a list of per-remote-station state.
 *
 * \sa ns3::WifiRemoteStation.
 */
class WifiRemoteStationManager : public Object
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);

  WifiRemoteStationManager ();
  virtual ~WifiRemoteStationManager ();

  /// ProtectionMode enumeration
  enum ProtectionMode
  {
    RTS_CTS,
    CTS_TO_SELF
  };

  /**
   * A vector of WifiRemoteStations
   */
  typedef std::vector <WifiRemoteStation *> Stations;
  /**
   * A vector of WifiRemoteStationStates
   */
  typedef std::vector <WifiRemoteStationState *> StationStates;

  /**
   * Set up PHY associated with this device since it is the object that
   * knows the full set of transmit rates that are supported.
   *
   * \param phy the PHY of this device
   */
  virtual void SetupPhy (const Ptr<WifiPhy> phy);
  /**
   * Set up MAC associated with this device since it is the object that
   * knows the full set of timing parameters (e.g. IFS).
   *
   * \param mac the MAC of this device
   */
  virtual void SetupMac (const Ptr<WifiMac> mac);

  /**
   * Sets the maximum STA short retry count (SSRC).
   *
   * \param maxSsrc the maximum SSRC
   */
  void SetMaxSsrc (uint32_t maxSsrc);
  /**
   * Sets the maximum STA long retry count (SLRC).
   *
   * \param maxSlrc the maximum SLRC
   */
  void SetMaxSlrc (uint32_t maxSlrc);
  /**
   * Sets the RTS threshold.
   *
   * \param threshold the RTS threshold
   */
  void SetRtsCtsThreshold (uint32_t threshold);

  /**
   * Return the fragmentation threshold.
   *
   * \return the fragmentation threshold
   */
  uint32_t GetFragmentationThreshold (void) const;
  /**
   * Sets a fragmentation threshold. The method calls a private method
   * DoSetFragmentationThreshold that checks the validity of the value given.
   *
   * \param threshold the fragmentation threshold
   */
  void SetFragmentationThreshold (uint32_t threshold);
  /**
   * Typically called to update the fragmentation threshold at the start of a new transmission.
   * This avoid that the fragmentation threshold gets changed during a transmission (see bug 730).
   */
  void UpdateFragmentationThreshold (void);

  /**
   * Records QoS support of the remote station.
   *
   * \param from the address of the station being recorded
   * \param qosSupported whether the station supports QoS
   */
  void SetQosSupport (Mac48Address from, bool qosSupported);
  /**
   * Records HT capabilities of the remote station.
   *
   * \param from the address of the station being recorded
   * \param htcapabilities the HT capabilities of the station
   */
  void AddStationHtCapabilities (Mac48Address from, HtCapabilities htcapabilities);
  /**
   * Records VHT capabilities of the remote station.
   *
   * \param from the address of the station being recorded
   * \param vhtcapabilities the VHT capabilities of the station
   */
  void AddStationVhtCapabilities (Mac48Address from, VhtCapabilities vhtcapabilities);
  /**
   * Records HE capabilities of the remote station.
   *
   * \param from the address of the station being recorded
   * \param hecapabilities the HE capabilities of the station
   */
  void AddStationHeCapabilities (Mac48Address from, HeCapabilities hecapabilities);
  /**
   * Return the HT capabilities sent by the remote station.
   *
   * \param from the address of the remote station
   * \return the HT capabilities sent by the remote station
   */
  Ptr<const HtCapabilities> GetStationHtCapabilities (Mac48Address from);
  /**
   * Return the VHT capabilities sent by the remote station.
   *
   * \param from the address of the remote station
   * \return the VHT capabilities sent by the remote station
   */
  Ptr<const VhtCapabilities> GetStationVhtCapabilities (Mac48Address from);
  /**
   * Return the HE capabilities sent by the remote station.
   *
   * \param from the address of the remote station
   * \return the HE capabilities sent by the remote station
   */
  Ptr<const HeCapabilities> GetStationHeCapabilities (Mac48Address from);
  /**
   * Return whether the device has HT capability support enabled.
   *
   * \return true if HT capability support is enabled, false otherwise
   */
  bool GetHtSupported (void) const;
  /**
   * Return whether the device has VHT capability support enabled.
   *
   * \return true if VHT capability support is enabled, false otherwise
   */
  bool GetVhtSupported (void) const;
  /**
   * Return whether the device has HE capability support enabled.
   *
   * \return true if HE capability support is enabled, false otherwise
   */
  bool GetHeSupported (void) const;
  /**
   * Enable or disable PCF capability support.
   *
   * \param enable enable or disable PCF capability support
   */
  void SetPcfSupported (bool enable);
  /**
   * Return whether the device has PCF capability support enabled.
   *
   * \return true if PCF capability support is enabled, false otherwise
   */
  bool GetPcfSupported (void) const;
  /**
   * Return whether the device has HT Greenfield support enabled.
   *
   * \return true if HT Grenfield support is enabled, false otherwise
   */
  bool GetGreenfieldSupported (void) const;
  /**
   * Return whether the device has SGI support enabled.
   *
   * \return true if SGI support is enabled, false otherwise
   */
  bool GetShortGuardIntervalSupported (void) const;
  /**
   * Return the supported HE guard interval duration (in nanoseconds).
   *
   * \return the supported HE guard interval duration (in nanoseconds)
   */
  uint16_t GetGuardInterval (void) const;
  /**
   * Enable or disable protection for non-ERP stations.
   *
   * \param enable enable or disable protection for non-ERP stations
   */
  void SetUseNonErpProtection (bool enable);
  /**
   * Return whether the device supports protection of non-ERP stations.
   *
   * \return true if protection for non-ERP stations is enabled,
   *         false otherwise
   */
  bool GetUseNonErpProtection (void) const;
  /**
   * Enable or disable protection for non-HT stations.
   *
   * \param enable enable or disable protection for non-HT stations
   */
  void SetUseNonHtProtection (bool enable);
  /**
   * Return whether the device supports protection of non-HT stations.
   *
   * \return true if protection for non-HT stations is enabled,
   *         false otherwise
   */
  bool GetUseNonHtProtection (void) const;
  /**
   * Enable or disable protection for stations that do not support HT greenfield format.
   *
   * \param enable enable or disable protection for stations that do not support HT greenfield format
   */
  void SetUseGreenfieldProtection (bool enable);
  /**
   * Return whether protection for stations that do not support HT greenfield format is enabled.
   *
   * \return true if protection for stations that do not support HT greenfield is enabled,
   *         false otherwise
   */
  bool GetUseGreenfieldProtection (void) const;
  /**
   * Enable or disable short PLCP preambles.
   *
   * \param enable enable or disable short PLCP preambles
   */
  void SetShortPreambleEnabled (bool enable);
  /**
   * Return whether the device uses short PLCP preambles.
   *
   * \return true if short PLCP preambles are enabled,
   *         false otherwise
   */
  bool GetShortPreambleEnabled (void) const;
  /**
   * Enable or disable short slot time.
   *
   * \param enable enable or disable short slot time
   */
  void SetShortSlotTimeEnabled (bool enable);
  /**
   * Return whether the device uses short slot time.
   *
   * \return true if short slot time is enabled,
   *         false otherwise
   */
  bool GetShortSlotTimeEnabled (void) const;
  /**
   * Permit or prohibit RIFS.
   *
   * \param allow permit or prohibit RIFS
   */
  void SetRifsPermitted (bool allow);
  /**
   * Return whether the device can use RIFS.
   *
   * \return true if RIFS is permitted,
   *         false otherwise
   */
  bool GetRifsPermitted (void) const;

  /**
   * Reset the station, invoked in a STA upon dis-association or in an AP upon reboot.
   */
  void Reset (void);

  /**
   * Invoked in a STA upon association to store the set of rates which belong to the
   * BSSBasicRateSet of the associated AP and which are supported locally.
   * Invoked in an AP to configure the BSSBasicRateSet.
   *
   * \param mode the WifiMode to be added to the basic mode set
   */
  void AddBasicMode (WifiMode mode);
  /**
   * Return the default transmission mode.
   *
   * \return WifiMode the default transmission mode
   */
  WifiMode GetDefaultMode (void) const;
  /**
   * Return the number of basic modes we support.
   *
   * \return the number of basic modes we support
   */
  uint8_t GetNBasicModes (void) const;
  /**
   * Return a basic mode from the set of basic modes.
   *
   * \param i index of the basic mode in the basic mode set
   *
   * \return the basic mode at the given index
   */
  WifiMode GetBasicMode (uint8_t i) const;
  /**
   * Return the number of non-ERP basic modes we support.
   *
   * \return the number of basic modes we support
   */
  uint32_t GetNNonErpBasicModes (void) const;
  /**
   * Return a basic mode from the set of basic modes that is not an ERP mode.
   *
   * \param i index of the basic mode in the basic mode set
   *
   * \return the basic mode at the given index
   */
  WifiMode GetNonErpBasicMode (uint8_t i) const;
  /**
   * Return whether the station supports Greenfield or not.
   *
   * \param address the address of the station
   *
   * \return true if Greenfield is supported by the station,
   *         false otherwise
   */
  bool GetGreenfieldSupported (Mac48Address address) const;
  /**
   * Return whether the station supports short PLCP preamble or not.
   *
   * \param address the address of the station
   *
   * \return true if short PLCP preamble is supported by the station,
   *         false otherwise
   */
  bool GetShortPreambleSupported (Mac48Address address) const;
  /**
   * Return whether the station supports short ERP slot time or not.
   *
   * \param address the address of the station
   *
   * \return true if short ERP slot time is supported by the station,
   *         false otherwise
   */
  bool GetShortSlotTimeSupported (Mac48Address address) const;
  /**
   * Return whether the given station is QoS capable.
   *
   * \param address the address of the station
   *
   * \return true if the station has QoS capabilities,
   *         false otherwise
   */
  bool GetQosSupported (Mac48Address address) const;
  /**
   * Add a given Modulation and Coding Scheme (MCS) index to
   * the set of basic MCS.
   *
   * \param mcs the WifiMode to be added to the basic MCS set
   */
  void AddBasicMcs (WifiMode mcs);
  /**
   * Return the default Modulation and Coding Scheme (MCS) index.
   *
   * \return the default WifiMode
   */
  WifiMode GetDefaultMcs (void) const;
  /**
   * Return the number of basic MCS index.
   *
   * \return the number of basic MCS index
   */
  uint8_t GetNBasicMcs (void) const;
  /**
   * Return the MCS at the given <i>list</i> index.
   *
   * \param i the position in the list
   *
   * \return the basic mcs at the given list index
   */
  WifiMode GetBasicMcs (uint8_t i) const;
  /**
   * Record the MCS index supported by the station.
   *
   * \param address the address of the station
   * \param mcs the WifiMode supported by the station
   */
  void AddSupportedMcs (Mac48Address address, WifiMode mcs);
  /**
   * Return the channel width supported by the station.
   *
   * \param address the address of the station
   *
   * \return the channel width supported by the station
   */
  uint16_t GetChannelWidthSupported (Mac48Address address) const;
  /**
   * Return whether the station supports HT/VHT short guard interval.
   *
   * \param address the address of the station
   *
   * \return true if the station supports HT/VHT short guard interval,
   *         false otherwise
   */
  bool GetShortGuardIntervalSupported (Mac48Address address) const;
  /**
   * Return the number of spatial streams supported by the station.
   *
   * \param address the address of the station
   *
   * \return the number of spatial streams supported by the station
   */
  uint8_t GetNumberOfSupportedStreams (Mac48Address address) const;
  /**
   * Return the number of MCS supported by the station.
   *
   * \param address the address of the station
   *
   * \return the number of MCS supported by the station
   */
  uint8_t GetNMcsSupported (Mac48Address address) const;
  /**
   * Return whether the station supports HT or not.
   *
   * \param address the address of the station
   *
   * \return true if HT is supported by the station,
   *         false otherwise
   */
  bool GetHtSupported (Mac48Address address) const;
  /**
   * Return whether the station supports VHT or not.
   *
   * \param address the address of the station
   *
   * \return true if VHT is supported by the station,
   *         false otherwise
   */
  bool GetVhtSupported (Mac48Address address) const;
  /**
   * Return whether the station supports HE or not.
   *
   * \param address the address of the station
   *
   * \return true if HE is supported by the station,
   *         false otherwise
   */
  bool GetHeSupported (Mac48Address address) const;

  /**
   * Return a mode for non-unicast packets.
   *
   * \return WifiMode for non-unicast packets
   */
  WifiMode GetNonUnicastMode (void) const;

  /**
   * Invoked in a STA or AP to store the set of
   * modes supported by a destination which is
   * also supported locally.
   * The set of supported modes includes
   * the BSSBasicRateSet.
   *
   * \param address the address of the station being recorded
   * \param mode the WifiMode supports by the station
   */
  void AddSupportedMode (Mac48Address address, WifiMode mode);
  /**
   * Invoked in a STA or AP to store all of the modes supported
   * by a destination which is also supported locally.
   * The set of supported modes includes the BSSBasicRateSet.
   *
   * \param address the address of the station being recorded
   */
  void AddAllSupportedModes (Mac48Address address);
  /**
   * Invoked in a STA or AP to store all of the MCS supported
   * by a destination which is also supported locally.
   *
   * \param address the address of the station being recorded
   */
  void AddAllSupportedMcs (Mac48Address address);
  /**
   * Invoked in a STA or AP to delete all of the supported MCS by a destination.
   *
   * \param address the address of the station being recorded
   */
  void RemoveAllSupportedMcs (Mac48Address address);
  /**
   * Record whether the short PLCP preamble is supported by the station.
   *
   * \param address the address of the station
   * \param isShortPreambleSupported whether or not short PLCP preamble is supported by the station
   */
  void AddSupportedPlcpPreamble (Mac48Address address, bool isShortPreambleSupported);
  /**
   * Record whether the short ERP slot time is supported by the station.
   *
   * \param address the address of the station
   * \param isShortSlotTimeSupported whether or not short ERP slot time is supported by the station
   */
  void AddSupportedErpSlotTime (Mac48Address address, bool isShortSlotTimeSupported);
  /**
   * Return whether the station state is brand new.
   *
   * \param address the address of the station
   *
   * \return true if the state of the station is brand new,
   *         false otherwise
   */
  bool IsBrandNew (Mac48Address address) const;
  /**
   * Return whether the station associated.
   *
   * \param address the address of the station
   *
   * \return true if the station is associated,
   *         false otherwise
   */
  bool IsAssociated (Mac48Address address) const;
  /**
   * Return whether we are waiting for an ACK for
   * the association response we sent.
   *
   * \param address the address of the station
   *
   * \return true if the station is associated,
   *         false otherwise
   */
  bool IsWaitAssocTxOk (Mac48Address address) const;
  /**
   * Records that we are waiting for an ACK for
   * the association response we sent.
   *
   * \param address the address of the station
   */
  void RecordWaitAssocTxOk (Mac48Address address);
  /**
   * Records that we got an ACK for
   * the association response we sent.
   *
   * \param address the address of the station
   */
  void RecordGotAssocTxOk (Mac48Address address);
  /**
   * Records that we missed an ACK for
   * the association response we sent.
   *
   * \param address the address of the station
   */
  void RecordGotAssocTxFailed (Mac48Address address);
  /**
   * Records that the STA was disassociated.
   *
   * \param address the address of the station
   */
  void RecordDisassociated (Mac48Address address);

  /**
   * \param address remote address
   * \param header MAC header
   * \param packet the packet to queue
   *
   * This method is typically invoked just before queuing a packet for transmission.
   * It is a no-op unless the IsLowLatency attribute of the attached ns3::WifiRemoteStationManager
   * is set to false, in which case, the tx parameters of the packet are calculated and stored in
   * the packet as a tag. These tx parameters are later retrieved from GetDadaMode and GetRtsMode.
   */
  void PrepareForQueue (Mac48Address address, const WifiMacHeader *header,
                        Ptr<const Packet> packet);

  /**
   * \param address remote address
   * \param header MAC header
   * \param packet the packet to send
   *
   * \return the TXVECTOR to use to send this packet
   */
  WifiTxVector GetDataTxVector (Mac48Address address, const WifiMacHeader *header,
                                Ptr<const Packet> packet);
  /**
   * \param address remote address
   * \param header MAC header
   * \param packet the packet to send
   *
   * \return the TXVECTOR to use to send the RTS prior to the
   *         transmission of the data packet itself.
   */
  WifiTxVector GetRtsTxVector (Mac48Address address, const WifiMacHeader *header,
                               Ptr<const Packet> packet);
  /**
   * \param header MAC header
   * \param packet the packet to send
   *
   * \return the transmission mode to use to send the CTS-to-self prior to the
   *         transmission of the data packet itself.
   */
  WifiTxVector GetCtsToSelfTxVector (const WifiMacHeader *header,
                                     Ptr<const Packet> packet);
  /**
   * Since CTS-to-self parameters are not dependent on the station,
   * it is implemented in wifiremote station manager
   *
   * \return the transmission mode to use to send the CTS-to-self prior to the
   *         transmission of the data packet itself.
   */
  WifiTxVector DoGetCtsToSelfTxVector (void);

  /**
   * Should be invoked whenever the RtsTimeout associated to a transmission
   * attempt expires.
   *
   * \param address the address of the receiver
   * \param header MAC header of the DATA packet
   */
  void ReportRtsFailed (Mac48Address address, const WifiMacHeader *header);
  /**
   * Should be invoked whenever the AckTimeout associated to a transmission
   * attempt expires.
   *
   * \param address the address of the receiver
   * \param header MAC header of the DATA packet
   * \param packetSize the size of the DATA packet
   */
  void ReportDataFailed (Mac48Address address, const WifiMacHeader *header,
                         uint32_t packetSize);
  /**
   * Should be invoked whenever we receive the Cts associated to an RTS
   * we just sent. Note that we also get the SNR of the RTS we sent since
   * the receiver put a SnrTag in the CTS.
   *
   * \param address the address of the receiver
   * \param header MAC header of the DATA packet
   * \param ctsSnr the SNR of the CTS we received
   * \param ctsMode the WifiMode the receiver used to send the CTS
   * \param rtsSnr the SNR of the RTS we sent
   */
  void ReportRtsOk (Mac48Address address, const WifiMacHeader *header,
                    double ctsSnr, WifiMode ctsMode, double rtsSnr);
  /**
   * Should be invoked whenever we receive the Ack associated to a data packet
   * we just sent.
   *
   * \param address the address of the receiver
   * \param header MAC header of the DATA packet
   * \param ackSnr the SNR of the ACK we received
   * \param ackMode the WifiMode the receiver used to send the ACK
   * \param dataSnr the SNR of the DATA we sent
   * \param packetSize the size of the DATA packet
   */
  void ReportDataOk (Mac48Address address, const WifiMacHeader *header,
                     double ackSnr, WifiMode ackMode, double dataSnr,
                     uint32_t packetSize);
  /**
   * Should be invoked after calling ReportRtsFailed if
   * NeedRetransmission returns false
   *
   * \param address the address of the receiver
   * \param header MAC header of the DATA packet
   */
  void ReportFinalRtsFailed (Mac48Address address, const WifiMacHeader *header);
  /**
   * Should be invoked after calling ReportDataFailed if
   * NeedRetransmission returns false
   *
   * \param address the address of the receiver
   * \param header MAC header of the DATA packet
   * \param packetSize the size of the DATA packet
   */
  void ReportFinalDataFailed (Mac48Address address, const WifiMacHeader *header,
                              uint32_t packetSize);
  /**
   * Typically called per A-MPDU, either when a Block ACK was successfully
   * received or when a BlockAckTimeout has elapsed.
   *
   * \param address the address of the receiver
   * \param tid TID of the DATA packet
   * \param nSuccessfulMpdus number of successfully transmitted MPDUs.
   * A value of 0 means that the Block ACK was missed.
   * \param nFailedMpdus number of unsuccessfully transmitted MPDUs.
   * \param rxSnr received SNR of the block ack frame itself
   * \param dataSnr data SNR reported by remote station
   */
  void ReportAmpduTxStatus (Mac48Address address, uint8_t tid, uint8_t nSuccessfulMpdus, uint8_t nFailedMpdus, double rxSnr, double dataSnr);

  /**
   * \param address remote address
   * \param header MAC header
   * \param rxSnr the snr of the packet received
   * \param txMode the transmission mode used for the packet received.
   *
   * Should be invoked whenever a packet is successfully received.
   */
  void ReportRxOk (Mac48Address address, const WifiMacHeader *header,
                   double rxSnr, WifiMode txMode);

  /**
   * \param address remote address
   * \param header MAC header
   * \param packet the packet to send
   * \param txVector the TXVECTOR of the packet to send
   *
   * \return true if we want to use an RTS/CTS handshake for this
   *         packet before sending it, false otherwise.
   */
  bool NeedRts (Mac48Address address, const WifiMacHeader *header,
                Ptr<const Packet> packet, WifiTxVector txVector);
  /**
   * Return if we need to do Cts-to-self before sending a DATA.
   *
   * \param txVector the TXVECTOR of the packet to be sent
   *
   * \return true if Cts-to-self is needed,
   *         false otherwise
   */
  bool NeedCtsToSelf (WifiTxVector txVector);

  /**
   * \param address remote address
   * \param header MAC header
   * \param packet the packet to send
   *
   * \return true if we want to resend a packet after a failed transmission attempt,
   *         false otherwise.
   */
  bool NeedRetransmission (Mac48Address address, const WifiMacHeader *header,
                           Ptr<const Packet> packet);
  /**
   * \param address remote address
   * \param header MAC header
   * \param packet the packet to send
   *
   * \return true if this packet should be fragmented,
   *         false otherwise.
   */
  bool NeedFragmentation (Mac48Address address, const WifiMacHeader *header,
                          Ptr<const Packet> packet);
  /**
   * \param address remote address
   * \param header MAC header
   * \param packet the packet to send
   * \param fragmentNumber the fragment index of the next fragment to send (starts at zero).
   *
   * \return the size of the corresponding fragment.
   */
  uint32_t GetFragmentSize (Mac48Address address, const WifiMacHeader *header,
                            Ptr<const Packet> packet, uint32_t fragmentNumber);
  /**
   * \param address remote address
   * \param header MAC header
   * \param packet the packet to send
   * \param fragmentNumber the fragment index of the next fragment to send (starts at zero).
   *
   * \return the offset within the original packet where this fragment starts.
   */
  uint32_t GetFragmentOffset (Mac48Address address, const WifiMacHeader *header,
                              Ptr<const Packet> packet, uint32_t fragmentNumber);
  /**
   * \param address remote address
   * \param header MAC header
   * \param packet the packet to send
   * \param fragmentNumber the fragment index of the next fragment to send (starts at zero).
   *
   * \return true if this is the last fragment, false otherwise.
   */
  bool IsLastFragment (Mac48Address address, const WifiMacHeader *header,
                       Ptr<const Packet> packet, uint32_t fragmentNumber);

  /**
   * \return the default transmission power
   */
  uint8_t GetDefaultTxPowerLevel (void) const;
  /**
   * \param address of the remote station
   *
   * \return information regarding the remote station associated with the given address
   */
  WifiRemoteStationInfo GetInfo (Mac48Address address);
  /**
   * Set the default transmission power level
   *
   * \param txPower the default transmission power level
   */
  void SetDefaultTxPowerLevel (uint8_t txPower);
  /**
   * \return the number of antennas supported by the phy layer
   */
  uint8_t GetNumberOfAntennas (void) const;
  /**
   * \return the maximum number of spatial streams supported by the phy layer
   */
  uint8_t GetMaxNumberOfTransmitStreams (void) const;
  /**
   * \returns whether HT greenfield should be used for a given destination address.
   *
   * \param dest the destination address
   *
   * \return whether HT greenfield should be used for a given destination address
   */
  bool UseGreenfieldForDestination (Mac48Address dest) const;

  /**
   * TracedCallback signature for power change events.
   *
   * \param [in] oldPower The previous power (in dBm).
   * \param [in] newPower The new power (in dBm).
   * \param [in] address The remote station MAC address.
   */
  typedef void (*PowerChangeTracedCallback)(double oldPower, double newPower, Mac48Address remoteAddress);

  /**
   * TracedCallback signature for rate change events.
   *
   * \param [in] oldRate The previous data rate.
   * \param [in] newRate The new data rate.
   * \param [in] address The remote station MAC address.
   */
  typedef void (*RateChangeTracedCallback)(DataRate oldRate, DataRate newRate, Mac48Address remoteAddress);


protected:
  virtual void DoDispose (void);
  /**
   * Return whether mode associated with the specified station at the specified index.
   *
   * \param station the station being queried
   * \param i the index
   *
   * \return WifiMode at the given index of the specified station
   */
  WifiMode GetSupported (const WifiRemoteStation *station, uint8_t i) const;
  /**
   * Return the number of modes supported by the given station.
   *
   * \param station the station being queried
   *
   * \return the number of modes supported by the given station
   */
  uint8_t GetNSupported (const WifiRemoteStation *station) const;
  /**
   * Return whether the given station is QoS capable.
   *
   * \param station the station being queried
   *
   * \return true if the station has QoS capabilities,
   *         false otherwise
   */
  bool GetQosSupported (const WifiRemoteStation *station) const;
  /**
   * Return whether the given station is HT capable.
   *
   * \param station the station being queried
   *
   * \return true if the station has HT capabilities,
   *         false otherwise
   */
  bool GetHtSupported (const WifiRemoteStation *station) const;
  /**
   * Return whether the given station is VHT capable.
   *
   * \param station the station being queried
   *
   * \return true if the station has VHT capabilities,
   *         false otherwise
   */
  bool GetVhtSupported (const WifiRemoteStation *station) const;
  /**
   * Return whether the given station is HE capable.
   *
   * \param station the station being queried
   *
   * \return true if the station has HE capabilities,
   *         false otherwise
   */
  bool GetHeSupported (const WifiRemoteStation *station) const;
  /**
   * Return the WifiMode supported by the specified station at the specified index.
   *
   * \param station the station being queried
   * \param i the index
   *
   * \return the WifiMode at the given index of the specified station
   */

  WifiMode GetMcsSupported (const WifiRemoteStation *station, uint8_t i) const;
  /**
   * Return the number of MCS supported by the given station.
   *
   * \param station the station being queried
   *
   * \return the number of MCS supported by the given station
   */
  uint8_t GetNMcsSupported (const WifiRemoteStation *station) const;
  /**
   * Return whether non-ERP mode associated with the specified station at the specified index.
   *
   * \param station the station being queried
   * \param i the index
   *
   * \return WifiMode at the given index of the specified station
   */
  WifiMode GetNonErpSupported (const WifiRemoteStation *station, uint8_t i) const;
  /**
   * Return the number of non-ERP modes supported by the given station.
   *
   * \param station the station being queried
   *
   * \return the number of non-ERP modes supported by the given station
   */
  uint32_t GetNNonErpSupported (const WifiRemoteStation *station) const;
  /**
   * Return the address of the station.
   *
   * \param station the station being queried
   *
   * \return the address of the station
   */
  Mac48Address GetAddress (const WifiRemoteStation *station) const;
  /**
   * Return the channel width supported by the station.
   *
   * \param station the station being queried
   *
   * \return the channel width (in MHz) supported by the station
   */
  uint16_t GetChannelWidth (const WifiRemoteStation *station) const;
  /**
   * Return whether the given station supports HT/VHT short guard interval.
   *
   * \param station the station being queried
   *
   * \return true if the station supports HT/VHT short guard interval,
   *         false otherwise
   */
  bool GetShortGuardIntervalSupported (const WifiRemoteStation *station) const;
  /**
   * Return the HE guard interval duration supported by the station.
   *
   * \param station the station being queried
   *
   * \return the HE guard interval duration (in nanoseconds) supported by the station
   */
  uint16_t GetGuardInterval (const WifiRemoteStation *station) const;
  /**
   * Return whether the given station supports A-MPDU.
   *
   * \param station the station being queried
   *
   * \return true if the station supports MPDU aggregation,
   *         false otherwise
   */
  bool GetAggregation (const WifiRemoteStation *station) const;
  /**
   * Return whether the station supports Greenfield or not.
   *
   * \param station the station being queried
   *
   * \return true if Greenfield is supported by the station,
   *         false otherwise
   */
  bool GetGreenfield (const WifiRemoteStation *station) const;

  /**
   * Return the number of supported streams the station has.
   *
   * \param station the station being queried
   *
   * \return the number of supported streams the station has
   */
  uint8_t GetNumberOfSupportedStreams (const WifiRemoteStation *station) const;
  /**
   * \returns the number of Ness the station has.
   *
   * \param station the station being queried
   *
   * \return the number of Ness the station has
   */
  uint8_t GetNess (const WifiRemoteStation *station) const;

  /**
   * Return the WifiPhy.
   *
   * \return WifiPhy
   */
  Ptr<WifiPhy> GetPhy (void) const;
  /**
   * Return the WifiMac.
   *
   * \return WifiMac
   */
  Ptr<WifiMac> GetMac (void) const;


private:
  /**
   * \param station the station that we need to communicate
   * \param packet the packet to send
   * \param normally indicates whether the normal 802.11 rts enable mechanism would
   *        request that the rts is sent or not.
   *
   * \return true if we want to use an RTS/CTS handshake for this packet before sending it,
   *         false otherwise.
   *
   * Note: This method is called before a unicast packet is sent on the medium.
   */
  virtual bool DoNeedRts (WifiRemoteStation *station,
                          Ptr<const Packet> packet, bool normally);
  /**
   * \param station the station that we need to communicate
   * \param packet the packet to send
   * \param normally indicates whether the normal 802.11 data retransmission mechanism
   *        would request that the data is retransmitted or not.
   * \return true if we want to resend a packet after a failed transmission attempt,
   *         false otherwise.
   *
   * Note: This method is called after any unicast packet transmission (control, management,
   *       or data) has been attempted and has failed.
   */
  virtual bool DoNeedRetransmission (WifiRemoteStation *station,
                                     Ptr<const Packet> packet, bool normally);
  /**
   * \param station the station that we need to communicate
   * \param packet the packet to send
   * \param normally indicates whether the normal 802.11 data fragmentation mechanism
   *        would request that the data packet is fragmented or not.
   *
   * \return true if this packet should be fragmented,
   *         false otherwise.
   *
   * Note: This method is called before sending a unicast packet.
   */
  virtual bool DoNeedFragmentation (WifiRemoteStation *station,
                                    Ptr<const Packet> packet, bool normally);
  /**
   * \return whether this manager is a manager designed to work in low-latency environments.
   *
   * Note: In this context, low vs high latency is defined in <i>IEEE 802.11 Rate Adaptation:
   * A Practical Approach</i>, by M. Lacage, M.H. Manshaei, and T. Turletti.
   */
  virtual bool IsLowLatency (void) const = 0;
  /**
   * \return a new station data structure
   */
  virtual WifiRemoteStation* DoCreateStation (void) const = 0;
  /**
    * \param station the station that we need to communicate
    *
    * \return the TXVECTOR to use to send a packet to the station
    *
    * Note: This method is called before sending a unicast packet or a fragment
    *       of a unicast packet to decide which transmission mode to use.
    */
  virtual WifiTxVector DoGetDataTxVector (WifiRemoteStation *station) = 0;
  /**
   * \param station the station that we need to communicate
   *
   * \return the transmission mode to use to send an rts to the station
   *
   * Note: This method is called before sending an rts to a station
   *       to decide which transmission mode to use for the rts.
   */
  virtual WifiTxVector DoGetRtsTxVector (WifiRemoteStation *station) = 0;

  /**
   * This method is a pure virtual method that must be implemented by the sub-class.
   * This allows different types of WifiRemoteStationManager to respond differently,
   *
   * \param station the station that we failed to send RTS
   */
  virtual void DoReportRtsFailed (WifiRemoteStation *station) = 0;
  /**
   * This method is a pure virtual method that must be implemented by the sub-class.
   * This allows different types of WifiRemoteStationManager to respond differently,
   *
   * \param station the station that we failed to send DATA
   */
  virtual void DoReportDataFailed (WifiRemoteStation *station) = 0;
  /**
   * This method is a pure virtual method that must be implemented by the sub-class.
   * This allows different types of WifiRemoteStationManager to respond differently,
   *
   * \param station the station that we successfully sent RTS
   * \param ctsSnr the SNR of the CTS we received
   * \param ctsMode the WifiMode the receiver used to send the CTS
   * \param rtsSnr the SNR of the RTS we sent
   */
  virtual void DoReportRtsOk (WifiRemoteStation *station,
                              double ctsSnr, WifiMode ctsMode, double rtsSnr) = 0;
  /**
   * This method is a pure virtual method that must be implemented by the sub-class.
   * This allows different types of WifiRemoteStationManager to respond differently,
   *
   * \param station the station that we successfully sent RTS
   * \param ackSnr the SNR of the ACK we received
   * \param ackMode the WifiMode the receiver used to send the ACK
   * \param dataSnr the SNR of the DATA we sent
   */
  virtual void DoReportDataOk (WifiRemoteStation *station,
                               double ackSnr, WifiMode ackMode, double dataSnr) = 0;
  /**
   * This method is a pure virtual method that must be implemented by the sub-class.
   * This allows different types of WifiRemoteStationManager to respond differently,
   *
   * \param station the station that we failed to send RTS
   */
  virtual void DoReportFinalRtsFailed (WifiRemoteStation *station) = 0;
  /**
   * This method is a pure virtual method that must be implemented by the sub-class.
   * This allows different types of WifiRemoteStationManager to respond differently,
   *
   * \param station the station that we failed to send DATA
   */
  virtual void DoReportFinalDataFailed (WifiRemoteStation *station) = 0;
  /**
   * This method is a pure virtual method that must be implemented by the sub-class.
   * This allows different types of WifiRemoteStationManager to respond differently,
   *
   * \param station the station that sent the DATA to us
   * \param rxSnr the SNR of the DATA we received
   * \param txMode the WifiMode the sender used to send the DATA
   */
  virtual void DoReportRxOk (WifiRemoteStation *station,
                             double rxSnr, WifiMode txMode) = 0;
  /**
   * Typically called per A-MPDU, either when a Block ACK was successfully received
   * or when a BlockAckTimeout has elapsed. This method is a virtual method that must
   * be implemented by the sub-class intended to handle A-MPDUs. This allows different
   * types of WifiRemoteStationManager to respond differently.
   *
   * \param station the station that sent the DATA to us
   * \param nSuccessfulMpdus number of successfully transmitted MPDUs.
   *        A value of 0 means that the Block ACK was missed.
   * \param nFailedMpdus number of unsuccessfully transmitted MPDUs.
   * \param rxSnr received SNR of the block ack frame itself
   * \param dataSnr data SNR reported by remote station
   */
  virtual void DoReportAmpduTxStatus (WifiRemoteStation *station, uint8_t nSuccessfulMpdus, uint8_t nFailedMpdus, double rxSnr, double dataSnr);

  /**
   * Return the state of the station associated with the given address.
   *
   * \param address the address of the station
   * \return WifiRemoteStationState corresponding to the address
   */
  WifiRemoteStationState* LookupState (Mac48Address address) const;
  /**
   * Return the station associated with the given address and TID.
   *
   * \param address the address of the station
   * \param tid the TID
   *
   * \return WifiRemoteStation corresponding to the address
   */
  WifiRemoteStation* Lookup (Mac48Address address, uint8_t tid) const;
  /// Find a remote station by its remote address and TID taken from MAC header
  /**
   * Return the station associated with the given address and MAC header.
   * It simply gets TID from the MAC header and calls Lookup with tid.
   *
   * \param address the address of the station
   * \param header MAC header
   *
   * \return WifiRemoteStation corresponding to the address
   */
  WifiRemoteStation* Lookup (Mac48Address address, const WifiMacHeader *header) const;

  /**
   * Actually sets the fragmentation threshold, it also checks the validity of
   * the given threshold.
   *
   * \param threshold the fragmentation threshold
   */
  void DoSetFragmentationThreshold (uint32_t threshold);
  /**
   * Return the current fragmentation threshold
   *
   * \return the fragmentation threshold
   */
  uint32_t DoGetFragmentationThreshold (void) const;
  /**
   * Return the number of fragments needed for the given packet.
   *
   * \param header MAC header
   * \param packet the packet to be fragmented
   *
   * \return the number of fragments needed
   */
  uint32_t GetNFragments (const WifiMacHeader *header, Ptr<const Packet> packet);

  /**
   * This is a pointer to the WifiPhy associated with this
   * WifiRemoteStationManager that is set on call to
   * WifiRemoteStationManager::SetupPhy(). Through this pointer the
   * station manager can determine PHY characteristics, such as the
   * set of all transmission rates that may be supported (the
   * "DeviceRateSet").
   */
  Ptr<WifiPhy> m_wifiPhy;
  /**
   * This is a pointer to the WifiMac associated with this
   * WifiRemoteStationManager that is set on call to
   * WifiRemoteStationManager::SetupMac(). Through this pointer the
   * station manager can determine MAC characteristics, such as the
   * interframe spaces.
   */
  Ptr<WifiMac> m_wifiMac;

  /**
   * This member is the list of WifiMode objects that comprise the
   * BSSBasicRateSet parameter. This list is constructed through calls
   * to WifiRemoteStationManager::AddBasicMode(), and an API that
   * allows external access to it is available through
   * WifiRemoteStationManager::GetNBasicModes() and
   * WifiRemoteStationManager::GetBasicMode().
   */
  WifiModeList m_bssBasicRateSet; //!< basic rate set
  WifiModeList m_bssBasicMcsSet; //!< basic MCS set

  StationStates m_states;  //!< States of known stations
  Stations m_stations;     //!< Information for each known stations

  WifiMode m_defaultTxMode; //!< The default transmission mode
  WifiMode m_defaultTxMcs;   //!< The default transmission modulation-coding scheme (MCS)

  bool m_pcfSupported; //!< Flag if PCF capability is supported
  uint32_t m_maxSsrc;  //!< Maximum STA short retry count (SSRC)
  uint32_t m_maxSlrc;  //!< Maximum STA long retry count (SLRC)
  uint32_t m_rtsCtsThreshold;  //!< Threshold for RTS/CTS
  uint32_t m_fragmentationThreshold;  //!< Current threshold for fragmentation
  uint32_t m_nextFragmentationThreshold;  //!< Threshold for fragmentation that will be used for the next transmission
  uint8_t m_defaultTxPowerLevel;  //!< Default tranmission power level
  WifiMode m_nonUnicastMode;  //!< Transmission mode for non-unicast DATA frames
  bool m_useNonErpProtection; //!< flag if protection for non-ERP stations against ERP transmissions is enabled
  bool m_useNonHtProtection;  //!< flag if protection for non-HT stations against HT transmissions is enabled
  bool m_useGreenfieldProtection; //!< flag if protection for stations that do not support HT greenfield format is enabled
  bool m_shortPreambleEnabled; //!< flag if short PLCP preamble is enabled
  bool m_shortSlotTimeEnabled; //!< flag if short slot time is enabled
  bool m_rifsPermitted;        //!< flag if RIFS is enabled
  ProtectionMode m_erpProtectionMode; //!< Protection mode for ERP stations when non-ERP stations are detected
  ProtectionMode m_htProtectionMode;  //!< Protection mode for HT stations when non-HT stations are detected

  /**
   * The trace source fired when the transmission of a single RTS has failed
   */
  TracedCallback<Mac48Address> m_macTxRtsFailed;
  /**
   * The trace source fired when the transmission of a single data packet has failed
   */
  TracedCallback<Mac48Address> m_macTxDataFailed;
  /**
   * The trace source fired when the transmission of a RTS has
   * exceeded the maximum number of attempts
   */
  TracedCallback<Mac48Address> m_macTxFinalRtsFailed;
  /**
   * The trace source fired when the transmission of a data packet has
   * exceeded the maximum number of attempts
   */
  TracedCallback<Mac48Address> m_macTxFinalDataFailed;
};

} //namespace ns3

#endif /* WIFI_REMOTE_STATION_MANAGER_H */
