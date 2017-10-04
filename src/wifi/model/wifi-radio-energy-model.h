/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010 Network Security Lab, University of Washington, Seattle.
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
 * Authors: Sidharth Nabar <snabar@uw.edu>, He Wu <mdzz@u.washington.edu>
 */

#ifndef WIFI_RADIO_ENERGY_MODEL_H
#define WIFI_RADIO_ENERGY_MODEL_H

#include "ns3/device-energy-model.h"
#include "ns3/nstime.h"
#include "ns3/event-id.h"
#include "ns3/traced-value.h"
#include "ns3/wifi-phy.h"

namespace ns3 {

class WifiTxCurrentModel;

/**
 * \ingroup energy
 * A WifiPhy listener class for notifying the WifiRadioEnergyModel of Wifi radio
 * state change.
 *
 */
class WifiRadioEnergyModelPhyListener : public WifiPhyListener
{
public:
  /**
   * Callback type for updating the transmit current based on the nominal tx power.
   */
  typedef Callback<void, double> UpdateTxCurrentCallback;

  WifiRadioEnergyModelPhyListener ();
  virtual ~WifiRadioEnergyModelPhyListener ();

  /**
   * \brief Sets the change state callback. Used by helper class.
   *
   * \param callback Change state callback.
   */
  void SetChangeStateCallback (DeviceEnergyModel::ChangeStateCallback callback);

  /**
   * \brief Sets the update tx current callback.
   *
   * \param callback Update tx current callback.
   */
  void SetUpdateTxCurrentCallback (UpdateTxCurrentCallback callback);

  /**
   * \brief Switches the WifiRadioEnergyModel to RX state.
   *
   * \param duration the expected duration of the packet reception.
   *
   * Defined in ns3::WifiPhyListener
   */
  virtual void NotifyRxStart (Time duration);

  /**
   * \brief Switches the WifiRadioEnergyModel back to IDLE state.
   *
   * Defined in ns3::WifiPhyListener
   *
   * Note that for the WifiRadioEnergyModel, the behavior of the function is the
   * same as NotifyRxEndError.
   */
  virtual void NotifyRxEndOk (void);

  /**
   * \brief Switches the WifiRadioEnergyModel back to IDLE state.
   *
   * Defined in ns3::WifiPhyListener
   *
   * Note that for the WifiRadioEnergyModel, the behavior of the function is the
   * same as NotifyRxEndOk.
   */
  virtual void NotifyRxEndError (void);

  /**
   * \brief Switches the WifiRadioEnergyModel to TX state and switches back to
   * IDLE after TX duration.
   *
   * \param duration the expected transmission duration.
   * \param txPowerDbm the nominal tx power in dBm
   *
   * Defined in ns3::WifiPhyListener
   */
  virtual void NotifyTxStart (Time duration, double txPowerDbm);

  /**
   * \param duration the expected busy duration.
   *
   * Defined in ns3::WifiPhyListener
   */
  virtual void NotifyMaybeCcaBusyStart (Time duration);

  /**
   * \param duration the expected channel switching duration.
   *
   * Defined in ns3::WifiPhyListener
   */
  virtual void NotifySwitchingStart (Time duration);

  /**
   * Defined in ns3::WifiPhyListener
   */
  virtual void NotifySleep (void);

  /**
   * Defined in ns3::WifiPhyListener
   */
  virtual void NotifyWakeup (void);

private:
  /**
   * A helper function that makes scheduling m_changeStateCallback possible.
   */
  void SwitchToIdle (void);

private:
  /**
   * Change state callback used to notify the WifiRadioEnergyModel of a state
   * change.
   */
  DeviceEnergyModel::ChangeStateCallback m_changeStateCallback;

  /**
   * Callback used to update the tx current stored in WifiRadioEnergyModel based on 
   * the nominal tx power used to transmit the current frame.
   */
  UpdateTxCurrentCallback m_updateTxCurrentCallback;

  EventId m_switchToIdleEvent;
};

// -------------------------------------------------------------------------- //

/**
 * \ingroup energy
 * \brief A WiFi radio energy model.
 * 
 * 4 states are defined for the radio: TX, RX, IDLE, SLEEP. Default state is
 * IDLE.
 * The different types of transactions that are defined are: 
 *  1. Tx: State goes from IDLE to TX, radio is in TX state for TX_duration,
 *     then state goes from TX to IDLE.
 *  2. Rx: State goes from IDLE to RX, radio is in RX state for RX_duration,
 *     then state goes from RX to IDLE.
 *  3. Go_to_Sleep: State goes from IDLE to SLEEP.
 *  4. End_of_Sleep: State goes from SLEEP to IDLE.
 * The class keeps track of what state the radio is currently in.
 *
 * Energy calculation: For each transaction, this model notifies EnergySource
 * object. The EnergySource object will query this model for the total current.
 * Then the EnergySource object uses the total current to calculate energy.
 *
 * Default values for power consumption are based on measurements reported in:
 * 
 * Daniel Halperin, Ben Greenstein, Anmol Sheth, David Wetherall,
 * "Demystifying 802.11n power consumption", Proceedings of HotPower'10 
 * 
 * Power consumption in Watts (single antenna):
 * 
 * \f$ P_{tx} = 1.14 \f$ (transmit at 0dBm)
 * 
 * \f$ P_{rx} = 0.94 \f$
 * 
 * \f$ P_{idle} = 0.82 \f$
 * 
 * \f$ P_{sleep} = 0.10 \f$
 * 
 * Hence, considering the default supply voltage of 3.0 V for the basic energy
 * source, the default current values in Ampere are:
 * 
 * \f$ I_{tx} = 0.380 \f$
 * 
 * \f$ I_{rx} = 0.313 \f$
 * 
 * \f$ I_{idle} = 0.273 \f$
 * 
 * \f$ I_{sleep} = 0.033 \f$
 * 
 * The dependence of the power consumption in transmission mode on the nominal
 * transmit power can also be achieved through a wifi tx current model.
 *
 */
class WifiRadioEnergyModel : public DeviceEnergyModel
{
public:
  /**
   * Callback type for energy depletion handling.
   */
  typedef Callback<void> WifiRadioEnergyDepletionCallback;

  /**
   * Callback type for energy recharged handling.
   */
  typedef Callback<void> WifiRadioEnergyRechargedCallback;

public:
  static TypeId GetTypeId (void);
  WifiRadioEnergyModel ();
  virtual ~WifiRadioEnergyModel ();

  /**
   * \brief Sets pointer to EnergySouce installed on node.
   *
   * \param source Pointer to EnergySource installed on node.
   *
   * Implements DeviceEnergyModel::SetEnergySource.
   */
  virtual void SetEnergySource (Ptr<EnergySource> source);

  /**
   * \returns Total energy consumption of the wifi device.
   *
   * Implements DeviceEnergyModel::GetTotalEnergyConsumption.
   */
  virtual double GetTotalEnergyConsumption (void) const;

  // Setter & getters for state power consumption.
  double GetIdleCurrentA (void) const;
  void SetIdleCurrentA (double idleCurrentA);
  double GetCcaBusyCurrentA (void) const;
  void SetCcaBusyCurrentA (double ccaBusyCurrentA);
  double GetTxCurrentA (void) const;
  void SetTxCurrentA (double txCurrentA);
  double GetRxCurrentA (void) const;
  void SetRxCurrentA (double rxCurrentA);
  double GetSwitchingCurrentA (void) const;
  void SetSwitchingCurrentA (double switchingCurrentA);
  double GetSleepCurrentA (void) const;
  void SetSleepCurrentA (double sleepCurrentA);

  /**
   * \returns Current state.
   */
  WifiPhy::State GetCurrentState (void) const;

  /**
   * \param callback Callback function.
   *
   * Sets callback for energy depletion handling.
   */
  void SetEnergyDepletionCallback (WifiRadioEnergyDepletionCallback callback);

  /**
   * \param callback Callback function.
   *
   * Sets callback for energy recharged handling.
   */
  void SetEnergyRechargedCallback (WifiRadioEnergyRechargedCallback callback);

  /**
   * \param model the model used to compute the wifi tx current.
   */
  void SetTxCurrentModel (Ptr<WifiTxCurrentModel> model);

  /**
   * \brief Calls the CalcTxCurrent method of the tx current model to
   *        compute the tx current based on such model
   * 
   * \param txPowerDbm the nominal tx power in dBm
   */
  void SetTxCurrentFromModel (double txPowerDbm);

  /**
   * \brief Changes state of the WifiRadioEnergyMode.
   *
   * \param newState New state the wifi radio is in.
   *
   * Implements DeviceEnergyModel::ChangeState.
   */
  virtual void ChangeState (int newState);

  /**
   * \brief Handles energy depletion.
   *
   * Implements DeviceEnergyModel::HandleEnergyDepletion
   */
  virtual void HandleEnergyDepletion (void);

  /**
   * \brief Handles energy recharged.
   *
   * Implements DeviceEnergyModel::HandleEnergyRecharged
   */
  virtual void HandleEnergyRecharged (void);

  /**
   * \returns Pointer to the PHY listener.
   */
  WifiRadioEnergyModelPhyListener * GetPhyListener (void);


private:
  void DoDispose (void);

  /**
   * \returns Current draw of device, at current state.
   *
   * Implements DeviceEnergyModel::GetCurrentA.
   */
  virtual double DoGetCurrentA (void) const;

  /**
   * \param state New state the radio device is currently in.
   *
   * Sets current state. This function is private so that only the energy model
   * can change its own state.
   */
  void SetWifiRadioState (const WifiPhy::State state);

private:
  Ptr<EnergySource> m_source;

  // Member variables for current draw in different radio modes.
  double m_txCurrentA;
  double m_rxCurrentA;
  double m_idleCurrentA;
  double m_ccaBusyCurrentA;
  double m_switchingCurrentA;
  double m_sleepCurrentA;
  Ptr<WifiTxCurrentModel> m_txCurrentModel;

  // This variable keeps track of the total energy consumed by this model.
  TracedValue<double> m_totalEnergyConsumption;

  // State variables.
  WifiPhy::State m_currentState;  // current state the radio is in
  Time m_lastUpdateTime;          // time stamp of previous energy update

  uint8_t m_nPendingChangeState;
  bool m_isSupersededChangeState;

  // Energy depletion callback
  WifiRadioEnergyDepletionCallback m_energyDepletionCallback;

  // Energy recharged callback
  WifiRadioEnergyRechargedCallback m_energyRechargedCallback;

  // WifiPhy listener
  WifiRadioEnergyModelPhyListener *m_listener;
};

} // namespace ns3

#endif /* WIFI_RADIO_ENERGY_MODEL_H */
