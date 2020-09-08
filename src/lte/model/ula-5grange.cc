//
// Created by Luis Pacheco on 19/04/2020.
//

#include "ula-5grange.h"

namespace ns3
{
NS_OBJECT_ENSURE_REGISTERED (Ula5gRange);

TypeId
Ula5gRange::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::Ula5gRange")
      .SetParent<Object> ()
      .SetGroupName ("Lte")
      .AddAttribute ("Bearing",
                     "Bearing.",
                     DoubleValue (0),
                     MakeDoubleAccessor (&Ula5gRange::SetBearing,
                                         &Ula5gRange::GetBearing),
                     MakeDoubleChecker<double> ())
      .AddAttribute ("MaxGain",
                     "MaxGain.",
                     DoubleValue (0),
                     MakeDoubleAccessor (&Ula5gRange::SetMaxGain,
                                         &Ula5gRange::GetMaxGain),
                     MakeDoubleChecker<double> ())
      .AddAttribute ("NumAntElem",
                     "Number of Antenna Elements.",
                     UintegerValue (1),
                     MakeUintegerAccessor (&Ula5gRange::SetNumAntElem,
                                           &Ula5gRange::GetNumAntElem),
                     MakeUintegerChecker<uint32_t> ())
      .AddAttribute ("PolarizationType5g",
                     "Polarization Type.",
                     EnumValue (ns3::VERTICAL_ONLY),
                     MakeEnumAccessor (&Ula5gRange::m_poltype),
                     MakeEnumChecker (ns3::HORIZONTAL_ONLY, "HorizontalOnly",
                                      ns3::VERTICAL_ONLY, "VerticalOnly",
                                      ns3::CROSS_90, "Cross_0_90",
                                      ns3::CROSS_45, "Cross_-45_45"))
      .AddAttribute ("AntennaType5g",
                     "Antenna Type.",
                     EnumValue (ns3::ISOTROPIC),
                     MakeEnumAccessor (&Ula5gRange::m_anttype),
                     MakeEnumChecker (ns3::ISOTROPIC, "Isotropic",
                                      ns3::A3GPP, "3GPP"));
  return tid;
}

Ula5gRange::Ula5gRange() : m_wavelength(0), m_systemfreq(0), m_spacing(0)
{
}

void Ula5gRange::ConfigureUla()
{

  if (m_systemfreq == 0)
    return;

  double speed_of_light = 299792458;
  m_wavelength = speed_of_light/m_systemfreq;
  m_spacing = m_wavelength/2;
  if (polarization_is_dual ())
    {
      num_virtual_ant_elem = 2 * this->m_numantelem;
    }
  else
    {
      num_virtual_ant_elem = this->m_numantelem;
    }

  ae_vec = initialize_ant_elem_vec();
}

std::vector<AntennaElement> Ula5gRange::initialize_ant_elem_vec ()
{
  arma::mat ant_element_vec_positions (3, m_numantelem, arma::fill::zeros);
  if (m_numantelem > 1)
    {
      double ula_size = (static_cast<double>(m_numantelem) - 1.0) * m_spacing;
      ant_element_vec_positions.row (2) = arma::linspace (-ula_size / 2.0, ula_size / 2.0, m_numantelem)
          .st ();
    }

  std::vector<AntennaElement> ant_elem_vec;
  ant_elem_vec.reserve (m_numantelem);

  for (unsigned int id_ant_elem = 0; id_ant_elem < m_numantelem; id_ant_elem++)
    {
      ant_elem_vec.emplace_back (ant_element_vec_positions.col (id_ant_elem), m_bearing, m_poltype,
                                 m_maxgain, rad_pp_is_isotropic());
    }
  return ant_elem_vec;
}

bool Ula5gRange::rad_pp_is_isotropic() {
  return m_anttype == AntennaType5g::ISOTROPIC;
}

arma::cx_mat Ula5gRange::get_array_response (double phi_GCS, double theta_GCS) const noexcept
{
  arma::cx_mat array_resp (2, num_virtual_ant_elem);

  arma::vec3 wave_front = sph2cart (phi_GCS, theta_GCS);

  unsigned int pol_factor = polarization_is_dual () ? 2 : 1;

  auto i = std::complex<double> (0.0, 1.0);
  for (unsigned int id_ant_elem = 0; id_ant_elem < ae_vec.size (); id_ant_elem++)
    {
      arma::vec3 delta_pos = ae_vec[id_ant_elem].get_position () - m_position;
      arma::mat tmp = ae_vec[id_ant_elem].get_ant_fields (phi_GCS, theta_GCS);

      // first_row, first_col, last_row, last_col
      unsigned int first_col = pol_factor * id_ant_elem;
      unsigned int last_col = first_col + pol_factor - 1;

      array_resp.submat (0, first_col, 1, last_col) =
          ae_vec[id_ant_elem].get_ant_fields (phi_GCS, theta_GCS) *
          exp (2.0 * arma::datum::pi * i * arma::dot (wave_front, delta_pos) /m_wavelength);
    }
  return array_resp;
}

arma::vec3 Ula5gRange::get_velocity () const noexcept
{
  return m_velocity;
}

unsigned int Ula5gRange::get_num_antenna_elem () const noexcept
{
  return ae_vec.size ();
}

unsigned int Ula5gRange::get_num_virtual_ant_elem () const noexcept
{
  return num_virtual_ant_elem;
}

bool Ula5gRange::polarization_is_dual () const noexcept
{
  return m_poltype == PolarizationType5g::CROSS_90 || m_poltype == PolarizationType5g::CROSS_45;
}

arma::vec3 Ula5gRange::get_position () const noexcept
{
  return m_position;
}

void Ula5gRange::set_velocity (const arma::vec3 &velocity)
{
  m_velocity = velocity;
}

double Ula5gRange::GetBearing () const
{
  return m_bearing;
}

void Ula5gRange::SetBearing (double m_bearing)
{
  Ula5gRange::m_bearing = m_bearing;
  ConfigureUla();
}

double Ula5gRange::GetMaxGain () const
{
  return m_maxgain;
}

void Ula5gRange::SetMaxGain (double m_maxgain)
{
  Ula5gRange::m_maxgain = m_maxgain;
  ConfigureUla();
}

unsigned int Ula5gRange::GetNumAntElem () const
{
  return m_numantelem;
}

void Ula5gRange::SetNumAntElem (unsigned int m_numantelem)
{
  Ula5gRange::m_numantelem = m_numantelem;
  ConfigureUla();
}

void Ula5gRange::SetPosition (const Vector &pos)
{
  m_position = vec2arma(pos);
}

arma::vec3 Ula5gRange::GetPosition () const
{
  return m_position;
}

arma::vec3 Ula5gRange::GetVelocity () const
{
  return m_velocity;
}

void Ula5gRange::SetVelocity (const Vector &vel)
{
  m_velocity = vec2arma(vel);
}

arma::vec3 Ula5gRange::vec2arma (const Vector &in)
{
  return arma::vec3{in.x, in.y, in.z};
}

double Ula5gRange::GetSystemFreq () const
{
  return m_systemfreq;
}

void Ula5gRange::SetSystemFreq (double m_systemfreq)
{
  Ula5gRange::m_systemfreq = m_systemfreq;
  ConfigureUla();
}

double Ula5gRange::GetSpacing () const
{
  return m_spacing;
}

double Ula5gRange::GetWavelength () const
{
  return m_wavelength;
}


AntennaElement::AntennaElement(const arma::vec3 &position, double bearing, PolarizationType5g pol_type, double max_gain,
                                 bool rad_pp_is_isotropic)
    : position(position),
      bearing(bearing),
      pol_type(pol_type),
      max_gain(max_gain),
      rad_pp_is_isotropic(rad_pp_is_isotropic) {
  double a = bearing;  // Bearing
  double b = 0.0;      // Downtilting disable
  double g = 0.0;      // % the rotations over the X-axis are disable

  transf_mat = {{cosd(a) * cosd(b), sind(a) * cosd(b), -sind(b)},
                {cosd(a) * sind(b) * sind(g) - sind(a) * cosd(g), sind(a) * sind(b) * sind(g) + cosd(a) * cosd(g),
                 cosd(b) * sind(g)},
                {cosd(a) * sind(b) * cosd(g) + sind(a) * sind(g), sind(a) * sind(b) * cosd(g) - cosd(a) * sind(g),
                 cosd(b) * cosd(g)}};
}

arma::mat AntennaElement::get_ant_fields(double phi_gcs, double theta_gcs) const noexcept {
  arma::vec xyz = sph2cart(phi_gcs, theta_gcs);

  // Angles in spherical coord. LCS
  double phi_lcs, theta_lcs;
  std::tie(phi_lcs, theta_lcs) = cart2sph(transf_mat * xyz);

  // Antenna element gain (linear).
  double gain = dB2lin(max_gain) * get_rad_pp(phi_lcs, theta_lcs);

  // Determining the fields in LCS accoring to the polarization type
  unsigned int num_pol = (pol_type == PolarizationType5g::CROSS_90 || pol_type == PolarizationType5g::CROSS_45) ? 2 : 1;
  arma::mat fields_LCS(num_pol, 2);

  switch(pol_type) {
  case HORIZONTAL_ONLY:  // Horizontal pol.
    fields_LCS = sqrt(gain) * arma::mat{{cosd(90.0), sind(90.0)}};
      break;
  case VERTICAL_ONLY:  // Vertical pol.
    fields_LCS = sqrt(gain) * arma::mat{{cosd(0.0), sind(0.0)}};
      break;
  case CROSS_90:  // Vertical and Horizontal pols.
    fields_LCS = sqrt(gain) * arma::mat{{cosd(0.0), sind(0.0)}, {cosd(90.0), sind(90.0)}};
      break;
  case CROSS_45:  // Cros - pol - 45 deg and +45
    fields_LCS = sqrt(gain) * arma::mat{{cosd(-45.0), sind(-45.0)}, {cosd(45.0), sind(45.0)}};
    }

  // Determine the full rotation mtx
  double a = bearing;  // bearing
  double b = 0.0;      // downtilt

  // Angle "psi" computed as in 3GPP TR 38.901, V14.0.0, (2017-03), p.p. 17, equation (7.1-15), with gamma = 0 deg

  double real_part_psi = cosd(b) * sind(theta_gcs) - sind(b) * cosd(theta_gcs) * cosd(phi_gcs - a);
  double imag_part_psi = sind(b) * sind(phi_gcs - a);
  double psi           = atan2d(imag_part_psi, real_part_psi);

  arma::mat22 rotation_mtx = arma::mat22{{cosd(psi), -sind(psi)}, {sind(psi), cosd(psi)}};

  // fields in GCS
  return rotation_mtx * fields_LCS.st();
}

double AntennaElement::get_rad_pp(double phi_lcs, double theta_lcs) const noexcept {
  if(this->rad_pp_is_isotropic) {
      return 1.0;

    } else {
      // 'phi_lcs' and 'theta_lcs' also in LCS.
      // 3GPP Radiation power pattern from TR 38901

      double A_phi_0    = -std::min(30.0, 12.0 * std::pow((theta_lcs - 90.0) / 65.0, 2.0));
      double A_theta_90 = -std::min(30.0, 12.0 * std::pow((phi_lcs) / 65.0, 2.0));

      return dB2lin(-std::min(30.0, -(A_phi_0 + A_theta_90)));
    }
}

arma::vec3 AntennaElement::get_position() const noexcept { return position; }

}