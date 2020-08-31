//
// Created by Luis Pacheco on 15/04/2020.
//

#include "cdl-common.h"
#include <complex>
#include <ns3/double.h>
#include <ns3/enum.h>
#include <ns3/uinteger.h>

namespace ns3
{

TypeId
CdlCommon::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::CdlCommon")
      .SetParent<Object> ()
      .SetGroupName ("Spectrum")
      .AddConstructor<CdlCommon> ()
      .AddAttribute ("KValue",
                     "KValue",
                     DoubleValue (29.38),
                     MakeDoubleAccessor (&CdlCommon::m_kvalue),
                     MakeDoubleChecker<double> ());
  return tid;
}

CdlCommon::CdlCommon(bool is_cdl_a, Ptr<Ula5gRange> ula_tx, Ptr<Ula5gRange> ula_rx) :
    is_CDL_A(is_cdl_a),
    tx(ula_tx),
    rx(ula_rx),
    system_freq(ula_tx->GetSystemFreq())
{

  if (is_cdl_a) {
      rays = setup_rays_CDL_A (tx->GetPosition (), rx->GetPosition ());
      shadow_fading = dB2lin (-CDL_A_param::SF_stddev * arma::randn ());
    } else {
      rays = setup_rays_CDL_D (tx->GetPosition (), rx->GetPosition (), system_freq);
      shadow_fading = dB2lin (-CDL_D_param::SF_stddev * arma::randn ());
    }

  path_loss = get_path_loss (tx->GetPosition (), rx->GetPosition (), system_freq);
  tot_path_gain = (1.0 / path_loss) * shadow_fading;
  combined_pattern ();
}

arma::vec CdlCommon::value2arma(Ptr<const SpectrumValue> rxPsd)
{
  auto fit = rxPsd->ConstBandsBegin ();
  Ptr<const SpectrumModel> sp = rxPsd->GetSpectrumModel ();
  arma::vec freqs_PRBs(sp->GetNumBands ());

  size_t i = 0;
  while (fit != rxPsd->ConstBandsEnd ())
    {
      freqs_PRBs(i) = fit->fc;
      ++i;
      ++fit;
    }
    
    return freqs_PRBs;
}

std::vector<double> CdlCommon::get_channel_fr_5g (double time, Ptr<SpectrumValue> rxPsd)
{
  combined_pattern();
  arma::vec freqs_PRBs = value2arma(rxPsd);

  arma::cx_cube fr_losses = get_channel_fr(time, freqs_PRBs);

  auto num_fr = static_cast<unsigned int>(freqs_PRBs.n_elem);
  std::vector<double> fading(num_fr);

  for (unsigned int id_fr = 0; id_fr < num_fr; id_fr++)
    {
      //fading[id_fr] = 20 * std::log10 (std::abs (fr_losses(0,0,id_fr)));
      fading[id_fr] = std::abs (fr_losses(0,0,id_fr));
    }

    return fading;
}

arma::cx_cube CdlCommon::get_channel_fr(double time, const arma::vec &freqs_PRBs) const
{
  arma::cx_cube cir = get_channel (time);

  auto num_tx = static_cast<unsigned int>(cir.n_cols);
  auto num_rx = static_cast<unsigned int>(cir.n_rows);
  auto num_rays = static_cast<unsigned int>(cir.n_slices);
  auto num_fr = static_cast<unsigned int>(freqs_PRBs.n_elem);

  arma::cx_cube cir_fr (num_rx, num_tx, num_fr);

  for (unsigned int id_tx = 0; id_tx < num_tx; id_tx++)
    {
      for (unsigned int id_rx = 0; id_rx < num_rx; id_rx++)
        {
          for (unsigned int id_fr = 0; id_fr < num_fr; id_fr++)
            {
              std::complex<double> channel_freq = 0.0;

              for (unsigned int id_ray = 0; id_ray < num_rays; id_ray++)
                {
                  std::complex<double> param = -1i * 2.0 * units::pi * freqs_PRBs (id_fr) * rays.delay (id_ray);
                  param = exp(param);
                  channel_freq = channel_freq + cir.at (id_rx, id_tx, id_ray)*param;
                }
              cir_fr.at (id_rx, id_tx, id_fr) = channel_freq;
            }
        }
    }

  return cir_fr;
}

arma::cx_cube CdlCommon::get_channel (double time) const
{
  auto num_tot_rays = static_cast<unsigned int>(rays.delay.size ());

  arma::cx_cube cir (comb_pattern.n_rows, comb_pattern.n_cols, comb_pattern.n_slices);

  for (unsigned int id_ray = 0; id_ray < num_tot_rays; id_ray++)
    {
      cir.slice (id_ray) = comb_pattern.slice (id_ray) * std::exp (time * partial_doppler_coef (id_ray));
    }

  return cir;
}

CdlCommon::Rays CdlCommon::setup_rays_CDL_A (const arma::vec3 &tx_position, const arma::vec3 &rx_position)
{
  unsigned int num_cl = CDL_A_param::cluster_DELAY.size ();
  unsigned int num_ray = CDL_A_param::fixed_ray_offset.size ();

  auto rays = Rays (num_cl * num_ray);

  // LOS ray
  double AOD_LOS, AOA_LOS, ZOD_LOS, ZOA_LOS;
  std::tie (AOD_LOS, AOA_LOS, ZOD_LOS, ZOA_LOS) = get_LOS_angles (tx_position, rx_position);

  AOD_LOS = deg2rad (AOD_LOS);
  AOA_LOS = deg2rad (AOA_LOS);
  ZOD_LOS = deg2rad (ZOD_LOS);
  ZOA_LOS = deg2rad (ZOA_LOS);

  // Angles, delay and power for each ray
  for (unsigned int id_cl = 0; id_cl < num_cl; id_cl++)
    {
      for (unsigned int id_ray = 0; id_ray < num_ray; id_ray++)
        {
          rays.AOD (id_cl * num_ray + id_ray) = AOD_LOS + CDL_A_param::cluster_AOD[id_cl] +
                                                CDL_A_param::cluster_ASD * CDL_A_param::fixed_ray_offset[id_ray];

          rays.AOA (id_cl * num_ray + id_ray) = AOA_LOS + CDL_A_param::cluster_AOA[id_cl] +
                                                CDL_A_param::cluster_ASA * CDL_A_param::fixed_ray_offset[id_ray];

          rays.ZOD (id_cl * num_ray + id_ray) = ZOD_LOS + CDL_A_param::cluster_ZOD[id_cl] +
                                                CDL_A_param::cluster_ZSD * CDL_A_param::fixed_ray_offset[id_ray];

          rays.ZOA (id_cl * num_ray + id_ray) = ZOA_LOS + CDL_A_param::cluster_ZOA[id_cl] +
                                                CDL_A_param::cluster_ZSA * CDL_A_param::fixed_ray_offset[id_ray];

          rays.delay (id_cl * num_ray + id_ray) = CDL_A_param::cluster_DELAY[id_cl];

          rays.power (id_cl * num_ray + id_ray) = CDL_A_param::cluster_power[id_cl] / static_cast<double>(num_ray);
        }
    }

  // Initial phases
  arma::cube init_phases_tmp =
      -arma::datum::pi + 2.0 * arma::datum::pi * arma::cube (2, 2, num_cl * num_ray, arma::fill::randu);
  arma::cx_cube init_phases = arma::exp (1i * init_phases_tmp);

  // XPR
  arma::vec xpr_lin = CDL_A_param::XPR_mean + CDL_A_param::XPR_stddev * arma::randn (num_cl * num_ray);
  xpr_lin.for_each ([] (double &val)
                    { val = std::pow (10.0, val / 10.0); });

  // Combining XPR with initial phases

  arma::mat imag_xpr = arma::mat (2, 2, arma::fill::zeros);

  for (unsigned int id_tot_ray = 0; id_tot_ray < num_cl * num_ray; id_tot_ray++)
    {
      arma::mat real_xpr =
          arma::mat{{1.0, 1.0 / std::sqrt (xpr_lin (id_tot_ray))}, {1.0 / std::sqrt (xpr_lin (id_tot_ray)), 1.0}};

      rays.XPR.slice (id_tot_ray) = init_phases.slice (id_tot_ray) % arma::cx_mat (real_xpr, imag_xpr);
    }

  return rays;
}

CdlCommon::Rays
CdlCommon::setup_rays_CDL_D (const arma::vec3 &tx_positions, const arma::vec3 &rx_position, double system_freq)
{
  unsigned int num_cl = CDL_D_param::cluster_DELAY.size () - 1;  // one of them is the Single LOS Ray
  unsigned int num_ray = CDL_D_param::fixed_ray_offset.size ();

  // There are  num_cl * num_ray rays + 1 (single LOS ray)
  auto rays = Rays (num_cl * num_ray + 1);

  // LOS ray
  double AOD_LOS, AOA_LOS, ZOD_LOS, ZOA_LOS;
  std::tie (AOD_LOS, AOA_LOS, ZOD_LOS, ZOA_LOS) = get_LOS_angles (tx_positions, rx_position);

  ZOA_LOS = deg2rad (AOD_LOS);
  ZOA_LOS = deg2rad (AOA_LOS);
  ZOA_LOS = deg2rad (ZOD_LOS);
  ZOA_LOS = deg2rad (ZOA_LOS);

  // Configuring the single LOS ray
  rays.AOD (0) = AOD_LOS;
  rays.AOA (0) = AOA_LOS;
  rays.ZOD (0) = ZOD_LOS;
  rays.ZOA (0) = ZOA_LOS;

  rays.delay (0) = CDL_D_param::cluster_DELAY[0];

  rays.power (0) = CDL_D_param::cluster_power[0];

  double dist_3D = arma::norm (tx_positions - rx_position);

  double wave_length = arma::datum::c_0 / system_freq;

  std::complex<double> param = -2.0 * arma::datum::pi * 1i * dist_3D / wave_length;
  rays.XPR.slice (0) = std::exp (param) * arma::mat22{{1.0, 0.0}, {0.0, -1.0}};

  // Angles, delay and power for each ray
  for (unsigned int id_cl = 0; id_cl < num_cl; id_cl++)
    {
      for (unsigned int id_ray = 0; id_ray < num_ray; id_ray++)
        {
          rays.AOD (id_cl * num_ray + id_ray + 1) = AOD_LOS + CDL_D_param::cluster_AOD[id_cl + 1] +
                                                    CDL_D_param::cluster_ASD * CDL_D_param::fixed_ray_offset[id_ray];

          rays.AOA (id_cl * num_ray + id_ray + 1) = AOA_LOS + CDL_D_param::cluster_AOA[id_cl + 1] +
                                                    CDL_D_param::cluster_ASA * CDL_D_param::fixed_ray_offset[id_ray];

          rays.ZOD (id_cl * num_ray + id_ray + 1) = ZOD_LOS + CDL_D_param::cluster_ZOD[id_cl + 1] +
                                                    CDL_D_param::cluster_ZSD * CDL_D_param::fixed_ray_offset[id_ray];

          rays.ZOA (id_cl * num_ray + id_ray + 1) = ZOA_LOS + CDL_D_param::cluster_ZOA[id_cl + 1] +
                                                    CDL_D_param::cluster_ZSA * CDL_D_param::fixed_ray_offset[id_ray];

          rays.delay (id_cl * num_ray + id_ray + 1) = CDL_D_param::cluster_DELAY[id_cl + 1];

          rays.power (id_cl * num_ray + id_ray + 1) =
              CDL_D_param::cluster_power[id_cl + 1] / static_cast<double>(num_ray);
        }
    }

  // Initial phases
  arma::cube init_phases_tmp =
      -arma::datum::pi + 2.0 * arma::datum::pi * arma::cube (2, 2, num_cl * num_ray, arma::fill::randu);
  arma::cx_cube init_phases = arma::exp (1i * init_phases_tmp);

  // XPR
  arma::vec xpr_lin = CDL_D_param::XPR_mean + CDL_D_param::XPR_stddev * arma::randn (num_cl * num_ray);
  xpr_lin.for_each ([] (double &val)
                    { val = std::pow (10.0, val / 10.0); });

  arma::mat imag_xpr = arma::mat (2, 2, arma::fill::zeros);

  // Combining XPR with initial phases
  for (unsigned int id_tot_ray = 0; id_tot_ray < num_cl * num_ray; id_tot_ray++)
    {
      arma::mat real_xpr =
          arma::mat{{1.0, 1.0 / std::sqrt (xpr_lin (id_tot_ray))}, {1.0 / std::sqrt (xpr_lin (id_tot_ray)), 1.0}};
      rays.XPR.slice (id_tot_ray + 1) = init_phases.slice (id_tot_ray) % arma::cx_mat (real_xpr, imag_xpr);
    }

  return rays;
}

void CdlCommon::combined_pattern ()
{
  // Number total of rays
  auto num_tot_rays = static_cast<unsigned int>(rays.delay.size ());

  // Number of polarization employed at BS and UE, respectively.
  unsigned int num_pol_tx = tx->polarization_is_dual () ? 2 : 1;
  unsigned int num_pol_rx = rx->polarization_is_dual () ? 2 : 1;

  // Combined Patterns (CP)
  comb_pattern
      .set_size (num_pol_rx * rx->GetNumAntElem (), num_pol_tx * tx->GetNumAntElem (), num_tot_rays);
  partial_doppler_coef.set_size (num_tot_rays);

  double wave_length = arma::datum::c_0 / system_freq;

  auto num_tx = tx->get_num_virtual_ant_elem ();
  auto num_rx = rx->get_num_virtual_ant_elem ();

  for (unsigned int id_ray = 0; id_ray < num_tot_rays; id_ray++)
    {
      arma::cx_mat22 xpr_mat = rays.XPR.slice (id_ray);

      // The antennas need the angles in degrees and the frequency in GHz
      arma::cx_mat tx_gain = tx->get_array_response (rad2deg (rays.AOD (id_ray)), rad2deg (rays.ZOD (id_ray)));

      arma::cx_mat rx_gain = rx->get_array_response (rad2deg (rays.AOA (id_ray)), rad2deg (rays.ZOA (id_ray)));

      arma::vec3 wave_front = sph2cart (rad2deg (rays.AOA (id_ray)), rad2deg (rays.ZOA (id_ray)));

      partial_doppler_coef (id_ray) = 1i * 2.0 * units::pi * arma::dot (rx->GetVelocity(), wave_front) / wave_length;

      // For each antenna antenna element at BS and UE the channel is calculated
      auto magnitude_field = std::sqrt (rays.power (id_ray) * tot_path_gain);
      for (unsigned int id_tx = 0; id_tx < num_tx; id_tx++)
        {
          for (unsigned int id_rx = 0; id_rx < num_rx; id_rx++)
            {
              comb_pattern.at (id_rx, id_tx, id_ray) =
                  arma::as_scalar (magnitude_field * rx_gain.col (id_rx).st () * xpr_mat * tx_gain.col (id_tx));
            }
        }
    }  // END FOR for each ray
}

double CdlCommon::get_path_loss (const arma::vec3 &tx_position, const arma::vec3 &rx_position, double system_freq)
{
  double distance_km = arma::norm (tx_position - rx_position) / (1.0e3);

  if (distance_km <= 1.0)
    {
      throw std::runtime_error (
          "The distance between the transmitter and "
          "receiver must be larger than 1km.");
    }

  double fc = system_freq / (1.0e6);

  double Pl_dB = 32.44 + 20 * log10 (fc) + 20 * log10 (distance_km) + 29.38;

  return std::pow (10.0, Pl_dB / 10.0);
}

CdlCommon::Rays CdlCommon::get_rays () const noexcept
{  return rays;
}

arma::vec3 CdlCommon::vec2arma (const Vector &in)
{
  return arma::vec3{in.x, in.y, in.z};
}
double
CdlCommon::get_tot_path_gain () const
{
  return tot_path_gain;
}
}
