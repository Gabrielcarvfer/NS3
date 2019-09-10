/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2003,2007 INRIA
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

#ifndef ONOE_WIFI_MANAGER_H
#define ONOE_WIFI_MANAGER_H

#include "ns3/traced-value.h"
#include "wifi-remote-station-manager.h"

namespace ns3 {

struct OnoeWifiRemoteStation;

/**
 * \brief an implementation of the rate control algorithm developed
 *        by Atsushi Onoe
 *
 * \ingroup wifi
 *
 * This algorithm is well known because it has been used as the default
 * rate control algorithm for the madwifi driver. I am not aware of
 * any publication or reference about this algorithm beyond the madwifi
 * source code.
 *
 * This RAA does not support HT, VHT nor HE modes and will error
 * exit if the user tries to configure this RAA with a Wi-Fi MAC
 * that has VhtSupported, HtSupported or HeSupported set.
 */
class OnoeWifiManager : public WifiRemoteStationManager
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);
  OnoeWifiManager ();
  virtual ~OnoeWifiManager ();


private:
  // Overridden from base class.
  void DoInitialize (void);
  WifiRemoteStation * DoCreateStation (void) const;
  void DoReportRxOk (WifiRemoteStation *station,
                     double rxSnr, WifiMode txMode);
  void DoReportRtsFailed (WifiRemoteStation *station);
  void DoReportDataFailed (WifiRemoteStation *station);
  void DoReportRtsOk (WifiRemoteStation *station,
                      double ctsSnr, WifiMode ctsMode, double rtsSnr);
  void DoReportDataOk (WifiRemoteStation *station,
                       double ackSnr, WifiMode ackMode, double dataSnr);
  void DoReportFinalRtsFailed (WifiRemoteStation *station);
  void DoReportFinalDataFailed (WifiRemoteStation *station);
  WifiTxVector DoGetDataTxVector (WifiRemoteStation *station);
  WifiTxVector DoGetRtsTxVector (WifiRemoteStation *station);
  bool IsLowLatency (void) const;

  /**
   * Update the number of retry (both short and long).
   *
   * \param station the ONOE wifi remote station
   */
  void UpdateRetry (OnoeWifiRemoteStation *station);
  /**
   * Update the mode.
   *
   * \param station the ONOE wifi remote station
   */
  void UpdateMode (OnoeWifiRemoteStation *station);

  Time m_updatePeriod; ///< update period
  uint32_t m_addCreditThreshold; ///< add credit threshold
  uint32_t m_raiseThreshold; ///< raise threshold

  TracedValue<uint64_t> m_currentRate; //!< Trace rate changes
};

} //namespace ns3

#endif /* ONOE_WIFI_MANAGER_H */
