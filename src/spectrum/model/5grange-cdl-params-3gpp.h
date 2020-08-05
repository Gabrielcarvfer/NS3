#ifndef CHANNEL_5GRANGE_CDLPARAMS3GPP_H
#define CHANNEL_5GRANGE_CDLPARAMS3GPP_H

#include <array>

/**
 * Scaled parameters from 3GPP CDL_A model
 */
namespace CDL_A_param {
// Ray offset within each cluster
static constexpr std::array<double, 20> fixed_ray_offset{0.0447,  -0.0447, 0.1413,  -0.1413, 0.2492,  -0.2492, 0.3715,
                                                         -0.3715, 0.5129,  -0.5129, 0.6797,  -0.6797, 0.8844,  -0.8844,
                                                         1.1481,  -1.1481, 1.5195,  -1.5195, 2.1551,  -2.1551};

// Delay of each cluster [seconds]
static constexpr std::array<double, 23> cluster_DELAY{0000000.0, 3.819e-8,  4.025e-8,  5.868e-8,  4.61e-8,   5.375e-8,
                                                      6.708e-8,  5.75e-8,   7.618e-8,  1.5375e-7, 1.8978e-7, 2.2242e-7,
                                                      2.1718e-7, 2.4942e-7, 2.5119e-7, 3.0582e-7, 4.081e-7,  4.4579e-7,
                                                      4.5695e-7, 4.7966e-7, 5.0066e-7, 5.3043e-7, 9.6586e-7};

// Azimuth of Departure of each cluster [radians]
static constexpr std::array<double, 23> cluster_AOD{
    -0.042272, -0.00099484, -0.00099484, -0.00099484, 0.021415,  0.021415,  0.021415, 0.028833,
    -0.019391, 0.037594,    -0.019705,   0.031992,    -0.03632,  -0.040823, -0.03084, -0.032289,
    0.03927,   0.035221,    0.031503,    -0.028152,   -0.036582, 0.03002,   -0.013334};

// Azimuth of arrival of each cluster [radians]
static constexpr std::array<double, 23> cluster_AOA{
    0.27021, -0.8043, -0.8043,   -0.8043,  0.40347, 0.40347, 0.40347, -0.0094771, -0.2207, 0.49616,  0.27337, -0.61046,
    0.14012, 0.40347, -0.036879, -0.12114, -0.2486, 0.58149, 0.7611,  0.81798,    0.53725, -0.79955, 0.29075};

// Zenith of Departure od each cluster [radians]
static constexpr std::array<double, 23> cluster_ZOD{0.0030892,  0.0057247, 0.0057247, 0.0057247, 0.0075049, 0.0075049,
                                                    0.0075049,  0.0092328, 0.0033859, 0.0016232, 0.0077667, 0.010542,
                                                    0.0093026,  0.0096691, 0.0028972, 0.0024784, 0.0026529, 0.0099484,
                                                    0.00066323, 0.0010297, 0.010559,  0.0013963, 0.0089012};

// Zenith of arrival of each cluster [radians]
static constexpr std::array<double, 23> cluster_ZOA{0.10488,  0.076358, 0.076358, 0.076358, 0.07861,  0.07861,
                                                    0.07861,  0.039392, 0.046845, 0.025168, 0.049183, 0.021747,
                                                    0.041155, 0.11968,  0.098192, 0.10263,  0.10304,  0.027262,
                                                    0.022742, 0.012706, 0.1221,   0.12603,  0.13055};

// Normalized Power of each cluster [linear]
static constexpr std::array<double, 23> cluster_power{0.013181,  0.28838,   0.17377,  0.11481,   0.072437, 0.043648,
                                                      0.02951,   0.025702,  0.051282, 0.0074125, 0.06309,  0.0061654,
                                                      0.016594,  0.0087089, 0.023986, 0.021378,  0.015487, 0.0069177,
                                                      0.0042654, 0.003715,  0.006309, 0.002951,  0.000309};

static constexpr double DS_rms      = 1.0e-07;    // DS rms [seconds]
static constexpr double ASD_rms     = 0.017453;   // ASD rms [radians]
static constexpr double ASA_rms     = 0.5236;     // ASA rms [radians]
static constexpr double ZSD_rms     = 0.0017453;  // ZSD rms [radians]
static constexpr double ZSA_rms     = 0.017453;   // ZSA rms [radians]
static constexpr double cluster_ASD = 0.087266;   // cluster ASD [radians]
static constexpr double cluster_ASA = 0.19199;    // cluster ASA [radians]
static constexpr double cluster_ZSD = 0.05236;    // cluster ZSD [radians]
static constexpr double cluster_ZSA = 0.05236;    // cluster [ZSA]
static constexpr double SF_stddev   = 4.47;       // standard deviation of SF [dB]
static constexpr double XPR_mean    = 10.0;       // mean of XPR [dB]
static constexpr double XPR_stddev  = 4.0;        // standard deviation of XPR [dB]

};  // namespace CDL_A_param

/**
 * Struct with the scaled parameters from 3GPP CDL_D model
 */
namespace CDL_D_param {
// Ray offset within each cluster
static constexpr std::array<double, 20> fixed_ray_offset{0.0447,  -0.0447, 0.1413,  -0.1413, 0.2492,  -0.2492, 0.3715,
                                                         -0.3715, 0.5129,  -0.5129, 0.6797,  -0.6797, 0.8844,  -0.8844,
                                                         1.1481,  -1.1481, 1.5195,  -1.5195, 2.1551,  -2.1551};

// ************************** NOTE:
// *******************************************************************************
// * The first index of each cluster parameters below (delays/angles/powers)
// corresponds to the single LOS ray.
// * After the first index, the remaining parameters corresponds to Cluster
// parameters.
// ****************************************************************************************************************

// Delay of each cluster [seconds]
static constexpr std::array<double, 14> cluster_DELAY{0.0,      0.0,      3.5e-9,   6.12e-8,  1.363e-7,
                                                      1.405e-7, 1.804e-7, 2.596e-7, 1.775e-7, 4.042e-7,
                                                      7.937e-7, 9.424e-7, 9.708e-7, 1.2525e-6};

// Azimuth of Departure of each cluster [radians]
static constexpr std::array<double, 14> cluster_AOD{0.0,       0.0,      0.099728, 0.099728, 0.099728,
                                                    0.014539,  0.014539, 0.014539, 0.038676, -0.072117,
                                                    -0.036774, 0.0588,   -0.14769, 0.086307};

// Azimuth of arrival of each cluster [radians]
static constexpr std::array<double, 14> cluster_AOA{-1.2709, -1.2709,  0.62978, 0.62978, 0.62978,  1.1509,    1.1509,
                                                    1.1509,  -0.96728, 0.52601, 0.90162, -0.84443, -0.064246, -0.59167};

// Zenith of Departure od each cluster [radians]
static constexpr std::array<double, 14> cluster_ZOD{0.076934, 0.076934, 0.066794, 0.066794, 0.066794,
                                                    0.076166, 0.076166, 0.076166, 0.076934, 0.069045,
                                                    0.071314, 0.081088, 0.062727, 0.067562};

// Zenith of arrival of each cluster [radians]
static constexpr std::array<double, 14> cluster_ZOA{1.2208, 1.2208, 1.3017, 1.3017, 1.3017, 1.1893, 1.1893,
                                                    1.1893, 1.1714, 1.1025, 1.1728, 1.3032, 1.0575, 1.092};

// Normalized Power of each cluster [linear]
static constexpr std::array<double, 14> cluster_power{0.88783,   0.041527,  0.012256,   0.0073847, 0.004879,
                                                      0.015078,  0.0090851, 0.0060025,  0.0047679, 0.0015429,
                                                      0.0040582, 0.0030784, 0.00092967, 0.0015788};

static constexpr double DS_rms      = 1.0e-7;     // DS rms [seconds]
static constexpr double ASD_rms     = 0.017453;   // ASD rms [radians]
static constexpr double ASA_rms     = 0.5236;     // ASA rms [radians]
static constexpr double ZSD_rms     = 0.0017453;  // ZSD rms [radians]
static constexpr double ZSA_rms     = 0.017453;   // ZSA rms [radians]
static constexpr double cluster_ASD = 0.087266;   // cluster ASD [radians]
static constexpr double cluster_ASA = 0.13963;    // cluster ASA [radians]
static constexpr double cluster_ZSD = 0.05236;    // cluster ZSD [radians]
static constexpr double cluster_ZSA = 0.05236;    // cluster [ZSA]
static constexpr double SF_stddev   = 4.47;       // standard deviation of SF [dB]
static constexpr double XPR_mean    = 11.0;       // mean of XPR [dB]
static constexpr double XPR_stddev  = 3.0;        // standard deviation of XPR [dB]

};  // namespace CDL_D_param

#endif  // CHANNEL_5GRANGE_CDLPARAMS3GPP_H
