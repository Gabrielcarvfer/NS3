/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010 TELEMATICS LAB, DEE - Politecnico di Bari
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
 * Author: Giuseppe Piro  <g.piro@poliba.it>
 */

#ifndef LTE_SPECTRUM_VALUE_HELPER_H
#define LTE_SPECTRUM_VALUE_HELPER_H


#include <ns3/spectrum-value.h>
#include <vector>

namespace ns3 {

    /**
 * Table 5.7.3-1 "E-UTRA channel numbers" from 3GPP TS 36.101
 * The table was converted to C syntax doing a cut & paste from TS 36.101 and running the following filter:
 * awk '{if ((NR % 7) == 1) printf("{"); printf ("%s",$0); if ((NR % 7) == 0) printf("},\n"); else printf(", ");}' | sed 's/ – /, /g'
 */
    static const struct EutraChannelNumbers
    {
        uint8_t band; ///< band
        double fDlLow; ///<  DL low
        uint32_t nOffsDl; ///< number offset DL
        uint32_t rangeNdl1; ///< range DL 1
        uint32_t rangeNdl2; ///< range DL 2
        double fUlLow; ///< UL low
        uint32_t nOffsUl;  ///< number offset UL
        uint32_t rangeNul1; ///< range UL 1
        uint32_t rangeNul2; ///< range UL 2
    } g_eutraChannelNumbers[] = {
            {  1,   2110,     0,     0,   599,   1920, 18000, 18000, 18599},
            {  2,   1930,   600,   600,  1199,   1850, 18600, 18600, 19199},
            {  3,   1805,  1200,  1200,  1949,   1710, 19200, 19200, 19949},
            {  4,   2110,  1950,  1950,  2399,   1710, 19950, 19950, 20399},
            {  5,    869,  2400,  2400,  2649,    824, 20400, 20400, 20649},
            {  6,    875,  2650,  2650,  2749,    830, 20650, 20650, 20749},
            {  7,   2620,  2750,  2750,  3449,   2500, 20750, 20750, 21449},
            {  8,    925,  3450,  3450,  3799,    880, 21450, 21450, 21799},
            {  9, 1844.9,  3800,  3800,  4149, 1749.9, 21800, 21800, 22149},
            { 10,   2110,  4150,  4150,  4749,   1710, 22150, 22150, 22749},
            { 11, 1475.9,  4750,  4750,  4949, 1427.9, 22750, 22750, 22949},
            { 12,    728,  5000,  5000,  5179,    698, 23000, 23000, 23179},
            { 13,    746,  5180,  5180,  5279,    777, 23180, 23180, 23279},
            { 14,    758,  5280,  5280,  5379,    788, 23280, 23280, 23379},
            { 17,    734,  5730,  5730,  5849,    704, 23730, 23730, 23849},
            { 18,    860,  5850,  5850,  5999,    815, 23850, 23850, 23999},
            { 19,    875,  6000,  6000,  6149,    830, 24000, 24000, 24149},
            { 20,    791,  6150,  6150,  6449,    832, 24150, 24150, 24449},
            { 21, 1495.9,  6450,  6450,  6599, 1447.9, 24450, 24450, 24599},
            { 33,   1900, 36000, 36000, 36199,   1900, 36000, 36000, 36199},
            { 34,   2010, 36200, 36200, 36349,   2010, 36200, 36200, 36349},
            { 35,   1850, 36350, 36350, 36949,   1850, 36350, 36350, 36949},
            { 36,   1930, 36950, 36950, 37549,   1930, 36950, 36950, 37549},
            { 37,   1910, 37550, 37550, 37749,   1910, 37550, 37550, 37749},
            { 38,   2570, 37750, 37750, 38249,   2570, 37750, 37750, 38249},
            { 39,   1880, 38250, 38250, 38649,   1880, 38250, 38250, 38649},
            { 40,   2300, 38650, 38650, 39649,   2300, 38650, 38650, 39649},
            { 100, 182, 50000, 50000, 50900, 297, 60000, 60000, 60900},
            { 101, 462, 50901, 50901, 51901, 587, 60901, 60901, 61901}
    }; ///< eutra channel numbers

    /// number of EUTRA bands
    #define NUM_EUTRA_BANDS (sizeof (g_eutraChannelNumbers) / sizeof (EutraChannelNumbers))

/**
 * \ingroup lte
 *
 * \brief This class defines all functions to create spectrum model for lte
 */
class LteSpectrumValueHelper
{
public:
  /**
   * Calculates the carrier frequency from the E-UTRA Absolute
   * Radio Frequency Channel Number (EARFCN) according to 3GPP TS
   * 36.101 section 5.7.3 "Carrier frequency and EARFCN".
   *
   * \param earfcn the EARFCN
   *
   * \return the carrier frequency in Hz
   */
  static double GetCarrierFrequency (uint32_t earfcn);

  /**
   * Converts downlink EARFCN to corresponding LTE frequency band number.
   *
   * \param nDl the EARFCN
   *
   * \return the downlink carrier band
   */
  static uint16_t GetDownlinkCarrierBand (uint32_t nDl);

  /**
   * Converts uplink EARFCN to corresponding LTE frequency band number.
   *
   * \param nUl the EARFCN
   *
   * \return the uplink carrier band
   */
  static uint16_t GetUplinkCarrierBand (uint32_t nUl);

  /**
   * Calculates the downlink carrier frequency from the E-UTRA Absolute
   * Radio Frequency Channel Number (EARFCN) using the formula in 3GPP TS
   * 36.101 section 5.7.3 "Carrier frequency and EARFCN".
   *
   * \param earfcn the EARFCN
   *
   * \return the downlink carrier frequency in Hz
   */
  static double GetDownlinkCarrierFrequency (uint32_t earfcn);

  /**
   * Calculates the uplink carrier frequency from the E-UTRA Absolute
   * Radio Frequency Channel Number (EARFCN) using the formula in 3GPP TS
   * 36.101 section 5.7.3 "Carrier frequency and EARFCN".
   *
   * \param earfcn the EARFCN
   *
   * \return the uplink carrier frequency in Hz
   */
  static double GetUplinkCarrierFrequency (uint32_t earfcn);

  /**
   *
   *
   * \param txBandwidthConf the tranmission bandwidth
   * configuration in number of resource blocks
   *
   * \return the nominal channel bandwidth in Hz as per 3GPP TS 36.101
   */
  static double GetChannelBandwidth (uint8_t txBandwidthConf);

  /**
   *
   * \param earfcn the carrier frequency (EARFCN) at which reception
   * is made
   * \param bandwidth the Transmission Bandwidth Configuration in
   * number of resource blocks
   *
   * \return the static SpectrumModel instance corresponding to the
   * given carrier frequency and transmission bandwidth
   * configuration. If such SpectrumModel does not exist, it is
   * created.
   */
  static Ptr<SpectrumModel> GetSpectrumModel (uint32_t earfcn, uint8_t bandwidth);


  /**
   * create a spectrum value representing the power spectral
   * density of a signal to be transmitted. See 3GPP TS 36.101 for
   * a definition of most of the parameters described here.
   *
   * \param earfcn the carrier frequency (EARFCN) of the transmission
   * \param bandwidth the Transmission Bandwidth Configuration in
   * number of resource blocks
   * \param powerTx the total power in dBm over the whole bandwidth
   * \param activeRbs the list of Active Resource Blocks (PRBs)
   *
   * \return a pointer to a newly allocated SpectrumValue representing the TX Power Spectral Density in W/Hz for each Resource Block
   */
  static Ptr<SpectrumValue> CreateTxPowerSpectralDensity (uint32_t earfcn,
                                                          uint8_t bandwidth,
                                                          double powerTx,
                                                          std::vector <int> activeRbs);

  /**
   * create a spectrum value representing the power spectral
   * density of a signal to be transmitted. See 3GPP TS 36.101 for
   * a definition of most of the parameters described here.
   *
   * \param earfcn the carrier frequency (EARFCN) of the transmission
   * \param bandwidth the Transmission Bandwidth Configuration in
   * number of resource blocks
   * \param powerTx the total power in dBm over the whole bandwidth
   * \param powerTxMap the map of power in dBm for each RB,
   * if map contain power for RB, powerTx is not used for this RB,
   * otherwise powerTx is set for this RB
   * \param activeRbs the list of Active Resource Blocks (PRBs)
   *
   * \return a pointer to a newly allocated SpectrumValue representing the TX Power Spectral Density in W/Hz for each Resource Block
   */
  static Ptr<SpectrumValue> CreateTxPowerSpectralDensity (uint32_t earfcn,
                                                          uint8_t bandwidth,
                                                          double powerTx,
                                                          std::map<int, double> powerTxMap,
                                                          std::vector <int> activeRbs);

  /**
   * create a spectrum value representing the uplink power spectral
   * density of a signal to be transmitted. See 3GPP TS 36.101 for
   * a definition of most of the parameters described here.
   * This function splits the power over the active RBs instead of
   * the entire bandwidth
   * \param earfcn the carrier frequency (EARFCN) of the transmission
   * \param bandwidth the Transmission Bandwidth Configuration in
   * number of resource blocks
   * \param powerTx the total power in dBm over the whole bandwidth
   * \param activeRbs the list of Active Resource Blocks (PRBs)
   *
   * \return a pointer to a newly allocated SpectrumValue representing the TX Power Spectral Density in W/Hz for each Resource Block
   */
  static Ptr<SpectrumValue> CreateUlTxPowerSpectralDensity (uint16_t earfcn,
                                                            uint8_t bandwidth,
                                                            double powerTx,
                                                            std::vector <int> activeRbs);

  /**
   * create a SpectrumValue that models the power spectral density of AWGN
   *
   * \param earfcn the carrier frequency (EARFCN) at which reception
   * is made
   * \param bandwidth the Transmission Bandwidth Configuration in
   * number of resource blocks
   * \param noiseFigure the noise figure in dB w.r.t. a reference temperature of 290K
   *
   * \return a pointer to a newly allocated SpectrumValue representing the noise Power Spectral Density in W/Hz for each Resource Block
   */
  static Ptr<SpectrumValue> CreateNoisePowerSpectralDensity (uint32_t earfcn, uint8_t bandwidth, double noiseFigure);

  /**
   *  create a SpectrumValue that models the power spectral density of AWGN
   *
   * \param noiseFigure  the noise figure in dB  w.r.t. a reference temperature of 290K
   * \param spectrumModel the SpectrumModel instance to be used
   *
   * \return a pointer to a newly allocated SpectrumValue representing the noise Power Spectral Density in W/Hz for each Resource Block
   */
  static Ptr<SpectrumValue> CreateNoisePowerSpectralDensity (double noiseFigure, Ptr<SpectrumModel> spectrumModel);

};


} // namespace ns3



#endif /*  LTE_SPECTRUM_VALUE_HELPER_H */
