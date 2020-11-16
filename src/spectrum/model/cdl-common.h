//
// Created by Luis Pacheco on 15/04/2020.
//

#ifndef _CDLCOMMON_H_
#define _CDLCOMMON_H_

#include <armadillo>
#include <array>
#include <cmath>
#include <complex>
#include <vector>
#include <ns3/ula-5grange.h>
#include "5grange-cdl-params-3gpp.h"
#include "5grange-transformation-units.h"
#include <ns3/core.h>
#include <ns3/object.h>
#include <ns3/spectrum-value.h>

namespace ns3
{

class CdlCommon : public Object {
 public:
  CdlCommon () = default;

   CdlCommon (bool is_cdl_a, Ptr<Ula5gRange> ula_tx, Ptr<Ula5gRange> ula_rx, double distance);
   static TypeId GetTypeId (void);



  struct Rays {
      // ************************** NOTE:
      // *******************************************************************************
      // * In the LOS case, the first index of each angle/ray/power/XPR corresponds
      // to the single LOS ray.
      // ****************************************************************************************************************

      arma::vec AOD;      // [radians]
      arma::vec AOA;      // [radians]
      arma::vec ZOD;      // [radians]
      arma::vec ZOA;      // [radians]
      arma::vec delay;    // [seconds]---> all the rays within a cluster have the same delay
      arma::vec power;    // [linear] ---> all the rays within a cluster have the same power
      arma::cx_cube XPR;  // [linear]
      explicit Rays () = default;
      explicit Rays (unsigned int num_tot_rays)
          : AOD (num_tot_rays),
            AOA (num_tot_rays),
            ZOD (num_tot_rays),
            ZOA (num_tot_rays),
            delay (num_tot_rays),
            power (num_tot_rays),
            XPR (2, 2, num_tot_rays)
      {}
  };

  /**
 * This method computes the Channel Impulse Response (CIR) in time-delay
 * domains.
 *
 * @param time time [seconds]
 * @return a tensor with dimension [Nrx, Ntx, Nrays], where Ntx and Nrx are
 * number of virtual antennas in the transmitter and receiver, respectively,
 * and Nrays is total number of rays. When the antenna is single polarized,
 * the number of virtual and physical antennas elements are equal. When the
 * antenna is dual polarized, the number of virtual antennas is 2x the number
 * of physical antennas.
 */
  arma::cx_cube get_channel (double time) const;

  /**
   * This method computes the Channel Impulse Response (CIR) in time-frequency
   * domains.
   *
   * @param time time [seconds]
   * @param freqs_PRBs vector containing the frequencies [Hz] of each PRB.
   * @return a tensor with dimension [Nrx, Ntx, Nprbs], where Ntx and Nrx are
   * number of virtual antennas in the transmitter and receiver, respectively,
   * and Nprbs is number of PRBs.
   */
  arma::cx_cube get_channel_fr(double time, const arma::vec &freqs_PRBs) const;
  std::vector<double> get_channel_fr_5g (double time, Ptr<SpectrumValue> rxPsd);

  /**
  * Return the struct of rays in the CDL model
  */
  Rays get_rays () const noexcept;

  /**
 * Compute the path loss used in the project 5G-RANGE
 *
 * @param tx_position transmitter position [meter]
 * @param rx_position receiver position [meter]
 * @param system_freq system frequency [Hz]
 * @param k_value k-value adjustment value [dB]
 * @return the path loss in linear scale
 */
  static double get_path_loss (const arma::vec3 &tx_position, const arma::vec3 &rx_position, double system_freq, double k_value);

  static arma::vec3 vec2arma(const Vector &in);

 protected:
  /**
   * This method use the CDL_A model to setup all the rays.
   *
   * @param tx_position position of the transmitter [meter]
   * @param rx_position position of the receiver [meter]
   * @param cdl_a_param CDL_A parameters
   * @return the struct Rays with all the rays seted up
   */
  Rays setup_rays_CDL_A (const arma::vec3 &tx_position, const arma::vec3 &rx_position);

  /**
   * This method use the CDL_D model to setup all the rays.
   *
   * @param tx_position position of the transmitter [meter]
   * @param rx_position position of the receiver [meter]
   * @param cdl_d_param CDL_D parameters
   * @return the struct Rays with all the rays seted up
   */
  Rays setup_rays_CDL_D (const arma::vec3 &tx_positions, const arma::vec3 &rx_position, double system_freq);

  /**
   * This method pre-compute the antenna array patterns of both transmitter and
   * receiver for each ray. Since the rays are fixed, this calculation can be
   * one once and saved in the variables comb_patter and partial_doppler_coef to
   * improve temporal performance
   */
  void combined_pattern ();

  /// true if CDL_A model is used, otherwise CDL_D model is assumed.
  bool is_CDL_A;

  /// central frequency of the system [Hz]
  double system_freq{};
  double shadow_fading{};  // [linear]
  double path_loss{};      //  [linear]

  double m_kvalue;

  /// Total path gain. It is usefull to ensure a CIR with unitary power.
  double tot_path_gain{};
  arma::vec3 prevTxPos;
  arma::vec3 prevRxPos;
  double prevDistance{};
public:
  double get_tot_path_gain (double distance);
protected:
  /// Struct Rays
  Rays rays;

  /// Transmitter and receiver position.
  Ptr<Ula5gRange> rx;
  Ptr<Ula5gRange> tx;

  /// Variable used to storage the combined radiation power patterns
  arma::cx_cube comb_pattern;

  /// Variable used to storage the dot product of each wave front with the speed
  /// of the receiver.
  arma::cx_vec partial_doppler_coef;


  static arma::vec value2arma(Ptr<const SpectrumValue> rxPsd);
};

}
#endif //_CDLCOMMON_H_
