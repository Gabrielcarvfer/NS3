#ifndef CHANNEL_5GRANGE_TRANSFORMATION_UNITS_H
#define CHANNEL_5GRANGE_TRANSFORMATION_UNITS_H

#include <armadillo>
#include <ns3/core.h>
#include <ns3/vector.h>

using namespace ns3;

namespace units {
constexpr const double pi =
    3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;
}

constexpr double deg2rad(double angle) { return angle * units::pi / 180.0; }

constexpr double rad2deg(double angle) { return angle * 180.0 / units::pi; }

inline double lin2dB(double value) { return 10.0 * std::log10(value); }

inline double dB2lin(double value) { return std::pow(10.0, value / 10.0); }

inline double sind(double angle) { return std::sin(deg2rad(angle)); }

inline double cosd(double angle) { return std::cos(deg2rad(angle)); }

inline double acosd(double value) { return rad2deg(std::acos(value)); }

inline double atand(double value) { return rad2deg(std::atan(value)); }

inline double atan2d(double y, double x) {
    double angle = rad2deg(std::atan2(y, x));
    return (angle == -180.0) ? 180.0 : angle;
}

inline arma::vec3 sph2cart(double phi, double theta) {
    return arma::vec3{cosd(phi) * sind(theta), sind(phi) * sind(theta), cosd(theta)};
}

inline std::tuple<double, double> cart2sph(arma::vec3 xyz) {
    double xyz_norm = arma::norm(xyz);

    if(xyz_norm > 0.0) {
        xyz /= xyz_norm;
        return std::make_tuple(atan2d(xyz[1], xyz[0]), acosd(xyz[2]));
    } else {
        return std::make_tuple(0.0, 0.0);
    }
}

inline double Hz2GHz(double freq) { return freq / (1.0e+9); }

inline std::tuple<double, double, double, double> get_LOS_angles(const arma::vec3& bs_position,
                                                                 const arma::vec3& ue_position) {
    double AOD, ZOD;

    // AOD belongs to (-180, 180] and ZOD to [0, 180]
    std::tie(AOD, ZOD) = cart2sph(ue_position - bs_position);

    return std::make_tuple(AOD, (AOD > 0.0) ? (AOD - 180.0) : (180.0 + AOD), ZOD, 180.0 - ZOD);
}

#endif  // CHANNEL_5GRANGE_TRANSFORMATION_UNITS_H
