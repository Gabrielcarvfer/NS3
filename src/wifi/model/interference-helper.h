/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2005,2006 INRIA
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

#ifndef INTERFERENCE_HELPER_H
#define INTERFERENCE_HELPER_H

#include "ns3/nstime.h"
#include "wifi-tx-vector.h"
#include <map>

namespace ns3 {

class Packet;
class ErrorRateModel;

/**
 * \ingroup wifi
 * \brief handles interference calculations
 * \brief signal event for a packet.
 */
class Event : public SimpleRefCount<Event>
{
public:
  /**
   * Create an Event with the given parameters.
   *
   * \param packet the packet
   * \param txVector TXVECTOR of the packet
   * \param duration duration of the signal
   * \param rxPower the receive power (w)
   */
  Event (Ptr<const Packet> packet, WifiTxVector txVector, Time duration, double rxPower);
  ~Event ();

  /** Return the packet.
   *
   * \return the packet
   */
  Ptr<const Packet> GetPacket (void) const;
  /**
   * Return the start time of the signal.
   *
   * \return the start time of the signal
   */
  Time GetStartTime (void) const;
  /**
   * Return the end time of the signal.
   *
   * \return the end time of the signal
   */
  Time GetEndTime (void) const;
  /**
   * Return the receive power (w).
   *
   * \return the receive power (w)
   */
  double GetRxPowerW (void) const;
  /**
   * Return the TXVECTOR of the packet.
   *
   * \return the TXVECTOR of the packet
   */
  WifiTxVector GetTxVector (void) const;
  /**
   * Return the Wi-Fi mode used for the payload.
   *
   * \return the Wi-Fi mode used for the payload
   */
  WifiMode GetPayloadMode (void) const;


private:
  Ptr<const Packet> m_packet; ///< packet
  WifiTxVector m_txVector; ///< TXVECTOR
  Time m_startTime; ///< start time
  Time m_endTime; ///< end time
  double m_rxPowerW; ///< receive power in watts
};

/**
 * \ingroup wifi
 * \brief handles interference calculations
 */
class InterferenceHelper
{
public:
  /**
   * Signal event for a packet.
   */

  /**
   * A struct for both SNR and PER
   */
  struct SnrPer
  {
    double snr; ///< SNR
    double per; ///< PER
  };

  InterferenceHelper ();
  ~InterferenceHelper ();

  /**
   * Set the noise figure.
   *
   * \param value noise figure
   */
  void SetNoiseFigure (double value);
  /**
   * Set the error rate model for this interference helper.
   *
   * \param rate Error rate model
   */
  void SetErrorRateModel (const Ptr<ErrorRateModel> rate);

  /**
   * Return the error rate model.
   *
   * \return Error rate model
   */
  Ptr<ErrorRateModel> GetErrorRateModel (void) const;
  /**
   * Set the number of RX antennas in the receiver corresponding to this
   * interference helper.
   *
   * \param rx the number of RX antennas
   */
  void SetNumberOfReceiveAntennas (uint8_t rx);

  /**
   * \param energyW the minimum energy (W) requested
   *
   * \returns the expected amount of time the observed
   *          energy on the medium will be higher than
   *          the requested threshold.
   */
  Time GetEnergyDuration (double energyW) const;

  /**
   * Add the packet-related signal to interference helper.
   *
   * \param packet the packet
   * \param txVector TXVECTOR of the packet
   * \param duration the duration of the signal
   * \param rxPower receive power (W)
   *
   * \return Event
   */
  Ptr<Event> Add (Ptr<const Packet> packet, WifiTxVector txVector, Time duration, double rxPower);

  /**
   * Add a non-Wifi signal to interference helper.
   * \param duration the duration of the signal
   * \param rxPower receive power (W)
   */
  void AddForeignSignal (Time duration, double rxPower);
  /**
   * Calculate the SNIR at the start of the payload and accumulate
   * all SNIR changes in the snir vector for each MPDU of an A-MPDU.
   * This workaround is required in order to provide one PER per MPDU, for
   * reception success/failure evaluation, while hiding aggregation details from
   * this class.
   *
   * \param event the event corresponding to the first time the corresponding packet arrives
   * \param relativeMpduStartStop the time window (pair of start and end times) of PLCP payload to focus on
   *
   * \return struct of SNR and PER (with PER being evaluated over the provided time window)
   */
  struct InterferenceHelper::SnrPer CalculatePayloadSnrPer (Ptr<Event> event, std::pair<Time, Time> relativeMpduStartStop) const;
  /**
   * Calculate the SNIR for the event (starting from now until the event end).
   *
   * \param event the event corresponding to the first time the corresponding packet arrives
   *
   * \return the SNR for the packet
   */
  double CalculateSnr (Ptr<Event> event) const;
  /**
   * Calculate the SNIR at the start of the legacy PHY header and accumulate
   * all SNIR changes in the snir vector.
   *
   * \param event the event corresponding to the first time the corresponding packet arrives
   *
   * \return struct of SNR and PER
   */
  struct InterferenceHelper::SnrPer CalculateLegacyPhyHeaderSnrPer (Ptr<Event> event) const;
  /**
   * Calculate the SNIR at the start of the non-legacy PHY header and accumulate
   * all SNIR changes in the snir vector.
   *
   * \param event the event corresponding to the first time the corresponding packet arrives
   *
   * \return struct of SNR and PER
   */
  struct InterferenceHelper::SnrPer CalculateNonLegacyPhyHeaderSnrPer (Ptr<Event> event) const;

  /**
   * Notify that RX has started.
   */
  void NotifyRxStart ();
  /**
   * Notify that RX has ended.
   */
  void NotifyRxEnd ();
  /**
   * Erase all events.
   */
  void EraseEvents (void);


private:
  /**
   * Noise and Interference (thus Ni) event.
   */
  class NiChange
  {
public:
    /**
     * Create a NiChange at the given time and the amount of NI change.
     *
     * \param power the power
     * \param event causes this NI change
     */
    NiChange (double power, Ptr<Event> event);
    /**
     * Return the power
     *
     * \return the power
     */
    double GetPower (void) const;
    /**
     * Add a given amount of power.
     *
     * \param power the power to be added to the existing value
     */
    void AddPower (double power);
    /**
     * Return the event causes the corresponding NI change
     *
     * \return the event
     */
    Ptr<Event> GetEvent (void) const;


private:
    double m_power; ///< power
    Ptr<Event> m_event; ///< event
  };

  /**
   * typedef for a multimap of NiChanges
   */
  typedef std::multimap<Time, NiChange> NiChanges;

  /**
   * Append the given Event.
   *
   * \param event
   */
  void AppendEvent (Ptr<Event> event);
  /**
   * Calculate noise and interference power in W.
   *
   * \param event
   * \param ni
   *
   * \return noise and interference power
   */
  double CalculateNoiseInterferenceW (Ptr<Event> event, NiChanges *ni) const;
  /**
   * Calculate SNR (linear ratio) from the given signal power and noise+interference power.
   *
   * \param signal signal power, W
   * \param noiseInterference noise and interference power, W
   * \param channelWidth signal width in MHz
   *
   * \return SNR in linear ratio
   */
  double CalculateSnr (double signal, double noiseInterference, uint16_t channelWidth) const;
  /**
   * Calculate the success rate of the chunk given the SINR, duration, and Wi-Fi mode.
   * The duration and mode are used to calculate how many bits are present in the chunk.
   *
   * \param snir SINR
   * \param duration
   * \param mode
   * \param txVector
   *
   * \return the success rate
   */
  double CalculateChunkSuccessRate (double snir, Time duration, WifiMode mode, WifiTxVector txVector) const;
  /**
   * Calculate the error rate of the given PLCP payload only in the provided time
   * window (thus enabling per MPDU PER information). The PLCP payload can be divided into
   * multiple chunks (e.g. due to interference from other transmissions).
   *
   * \param event
   * \param ni
   * \param window time window (pair of start and end times) of PLCP payload to focus on
   *
   * \return the error rate of the payload
   */
  double CalculatePayloadPer (Ptr<const Event> event, NiChanges *ni, std::pair<Time, Time> window) const;
  /**
   * Calculate the error rate of the legacy PHY header. The legacy PHY header
   * can be divided into multiple chunks (e.g. due to interference from other transmissions).
   *
   * \param event
   * \param ni
   *
   * \return the error rate of the legacy PHY header
   */
  double CalculateLegacyPhyHeaderPer (Ptr<const Event> event, NiChanges *ni) const;
  /**
   * Calculate the error rate of the non-legacy PHY header. The non-legacy PHY header
   * can be divided into multiple chunks (e.g. due to interference from other transmissions).
   *
   * \param event
   * \param ni
   *
   * \return the error rate of the non-legacy PHY header
   */
  double CalculateNonLegacyPhyHeaderPer (Ptr<const Event> event, NiChanges *ni) const;

  double m_noiseFigure; /**< noise figure (linear) */
  Ptr<ErrorRateModel> m_errorRateModel; ///< error rate model
  uint8_t m_numRxAntennas; /**< the number of RX antennas in the corresponding receiver */
  /// Experimental: needed for energy duration calculation
  NiChanges m_niChanges;
  double m_firstPower; ///< first power
  bool m_rxing; ///< flag whether it is in receiving state

  /**
   * Returns an iterator to the first nichange that is later than moment
   *
   * \param moment time to check from
   * \returns an iterator to the list of NiChanges
   */
  NiChanges::const_iterator GetNextPosition (Time moment) const;
  /**
   * Returns an iterator to the first nichange that is later than moment
   *
   * \param moment time to check from
   * \returns an iterator to the list of NiChanges
   */
  //NiChanges::iterator GetNextPosition (Time moment);
  /**
   * Returns an iterator to the last nichange that is before than moment
   *
   * \param moment time to check from
   * \returns an iterator to the list of NiChanges
   */
  NiChanges::const_iterator GetPreviousPosition (Time moment) const;

  /**
   * Add NiChange to the list at the appropriate position and
   * return the iterator of the new event.
   *
   * \param moment
   * \param change
   * \returns the iterator of the new event
   */
  NiChanges::iterator AddNiChangeEvent (Time moment, NiChange change);
};

} //namespace ns3

#endif /* INTERFERENCE_HELPER_H */
