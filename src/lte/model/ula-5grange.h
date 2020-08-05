//
// Created by Luis Pacheco on 19/04/2020.
//

#ifndef _ULA5GRANGE_H_
#define _ULA5GRANGE_H_

#include <armadillo>
#include <ns3/core.h>
#include <ns3/object.h>
#include <ns3/vector.h>
#include <ns3/double.h>
#include <ns3/uinteger.h>
#include <ns3/enum.h>
#include <ns3/5grange-transformation-units.h>

namespace ns3
{

enum PolarizationType5g {
    HORIZONTAL_ONLY,
    VERTICAL_ONLY,
    CROSS_90,
    CROSS_45
};

enum AntennaType5g {
    ISOTROPIC,
    A3GPP
};

class AntennaElement {
 private:
  /// Position of the antenna element [m].
  const arma::vec3 position;

  /// Bearing angle [deg]. It uses as reference the X axis and positive rotations are assumed from X to Y.
  const double bearing;

  /// Polarization type
  const PolarizationType5g pol_type;

  /// Maximum antenna element gain [dBi]
  const double max_gain;

  /// Rotation matrix used to convert the angles from GCS to LCS.
  arma::mat33 transf_mat;

  /// Used to selec the type of radiation power pattern.
  const bool rad_pp_is_isotropic;

 public:
  /**
   * Main constructor
   *
   * @param position position of the antenna element [m].
   * @param bearing bearing angle [deg].
   * @param pol_type polarization type. Set:
   *  pol_type = 0,  Horizontal only (90 deg)
   *  pol_type = 1,  Vertical only (0 deg)
   *  pol_type = 2,  Cross 0 / 90unsigned int pol_type;
   *  pol_type = 3   Cross -45 / +45
   *  @param max_gain maximum antenna element gain [dBi].
   *  @param rad_pp_is_isotropic used to selec the radiation power pattern. Set as TRUE for isotropic and FALSE
   *  for the radiation power pattern defined in 3GPP TR 38.901
   */
  AntennaElement(const arma::vec3 &position, double bearing, PolarizationType5g pol_type, double max_gain,
                  bool rad_pp_is_isotropic);

  /**
   * Computes the antenna element fields
   *
   * @param phi_gcs azimuth angle [deg].
   * @param theta_gcs zenit angle [deg].
   * @return a matrix 2xN, where N = 1 of the antenna element is single polarized and N = 2 if it is dual polarized.
   */
  arma::mat get_ant_fields(double phi_gcs, double theta_gcs) const noexcept;

  /**
   * Computes the radiation power pattern
   * @param phi_lcs azimuth angle in LCS [deg].
   * @param theta_lcs zenith angle in LCS [deg].
   * @return the radiation power pattern in LCS in the range 0.001 and 1.0 [lin].
   */
  double get_rad_pp(double phi_lcs, double theta_lcs) const noexcept;

  /**
   * @return the position of the antenna element [m].
   */
  arma::vec3 get_position() const noexcept;
};

class Ula5gRange: public Object {

 public:

  /**
   * Main constructor
   *
   * @param setup_ula object to setup the ULA.
   */
  Ula5gRange();

  /**
 * \brief Get the type ID.
 * \return the object TypeId
 */
  static TypeId GetTypeId (void);

  /**
   * Computes the array response.
   *
   * @param phi_GCS azimuth angle in GCS [deg].
   * @param theta_GCS zenith angle in GCS [deg].
   */
  arma::cx_mat get_array_response(double phi_GCS, double theta_GCS) const noexcept;

  unsigned int get_num_antenna_elem() const noexcept;

  unsigned int get_num_virtual_ant_elem() const noexcept;

  bool polarization_is_dual() const noexcept;

  arma::vec3 get_velocity() const noexcept;

  arma::vec3 get_position() const noexcept;

  void set_velocity(const arma::vec3 &velocity);

  bool rad_pp_is_isotropic();

  unsigned int GetNumAntElem () const;
  void SetNumAntElem (unsigned int m_numantelem);
  double GetBearing () const;
  void SetBearing (double m_bearing);
  double GetMaxGain () const;
  void SetMaxGain (double m_maxgain);
  void SetPosition(const Vector &pos);
  arma::vec3 GetPosition() const;
  void SetVelocity(const Vector &vel);
  arma::vec3 GetVelocity() const;
  arma::vec3 vec2arma (const Vector &in);
  double GetWavelength () const;
  double GetSpacing () const;
  double GetSystemFreq() const;
  void SetSystemFreq(double m_systemfreq);
 private:
  /// Vector of antenna elements.
  std::vector<AntennaElement> ae_vec;

  /// Number of virtual antenna elements in the ULA.
  unsigned int num_virtual_ant_elem;

  /**
   * method used to generate the ULA.
   *
   * @param setup_ula object to setup the ULA.
   * @return vector of antenna elements.
   */
  std::vector<AntennaElement> initialize_ant_elem_vec();

  void ConfigureUla();

  double m_bearing;
  double m_maxgain;
  double m_wavelength;
  double m_spacing;
  double m_systemfreq;
  PolarizationType5g m_poltype;
  unsigned int m_numantelem;
  AntennaType5g m_anttype;
  arma::vec3 m_position;
  arma::vec3 m_velocity;
};

}
#endif //_ULA5GRANGE_H_
