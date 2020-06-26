/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2020 Luis Pacheco
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
 *
 * Original Work Authors:
 *      Luis Pacheco <lpacheco@tuta.io>
 */

#ifndef LTE_MIESM_ERROR_MODEL_H
#define LTE_MIESM_ERROR_MODEL_H

#include <list>
#include <vector>
#include <unordered_map>
#include <ns3/ptr.h>
#include <stdint.h>
#include <ns3/spectrum-value.h>
#include <ns3/lte-harq-phy.h>
#include <ns3/lte-common.h>
#include <ns3/lte-module.h>


namespace ns3 {

/// MAX_MCS
    const uint16_t MIESM_MAX_MCS = 27;

/**
 * This class provides the BLER estimation based on mutual information metrics
 */
    class LteMiesmErrorModel
    {

    public:
        /**
         * \brief find the mmib (mean mutual information per bit) for different modulations of the specified TB
         * \param sinr the perceived sinrs in the whole bandwidth
         * \param map the actives RBs for the TB
         * \param mcs the MCS of the TB
         * \return the mmib
         */
        static double Mib (const SpectrumValue& sinr,
                           const std::vector<int>& map,
                           uint8_t mcs,
                           std::string chan,
                           int num,
                           int size,
                           double speed);
        /**
         * \brief map the mmib (mean mutual information per bit) for different MCS
         * \param mib mean mutual information per bit of a code-block
         * \param ecrId Effective Code Rate ID
         * \param cbSize the size of the CB
         * \return the code block error rate
         */
        static double MappingMiBler (double snreff, uint8_t mcs, uint16_t cbSize, uint8_t num, std::string chan);

        /**
         * \brief run the error-model algorithm for the specified TB
         * \param sinr the perceived sinrs in the whole bandwidth
         * \param map the actives RBs for the TB
         * \param size the size in bytes of the TB
         * \param mcs the MCS of the TB
         * \param miHistory  MI of past transmissions (in case of retx)
         * \return the TB error rate and MI
         */
        static TbStats_t GetTbDecodificationStats (const SpectrumValue& sinr, const std::vector<int>& map, uint16_t size, uint8_t mcs, HarqProcessInfoList_t miHistory, uint8_t num, std::string chan, double speed);
        /**
        * \brief load error-model data from the input json file
        *
        *
        */
        static void LoadErrorData();

        static bool errorDataLoaded;


    };


} // namespace ns3

#endif /* LTE_MIESM_ERROR_MODEL_H */
