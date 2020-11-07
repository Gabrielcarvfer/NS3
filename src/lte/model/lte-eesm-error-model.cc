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

#include <list>
#include <utility>
#include <vector>
#include <ns3/log.h>
#include <ns3/pointer.h>
#include <stdint.h>
#include <cmath>
#include <string>
#include "stdlib.h"
#include <unordered_map>
#include <ns3/lte-eesm-error-model.h>
#include <ns3/lte-module.h>

#include "json_loader.h"


namespace ns3 {

    NS_LOG_COMPONENT_DEFINE ("LteEesmErrorModel");

    static std::vector<uint16_t> cbSizeTable5g;
    static std::vector<std::string> channelModelTable5g;
    static std::vector<uint8_t> numerologyTable5g;
    static std::vector<double> snrValueTable5g;
    static std::vector<uint16_t> speedTable5g;
    static std::map<std::string, std::vector<std::vector<double>>> blerTable5g;
    static std::map<std::string, std::map<uint16_t, std::map<uint16_t,double>>> betaTable5g;
    static std::unordered_map<double, uint16_t> snrIndex5g;
    bool LteEesmErrorModel::errorDataLoaded = false;
    void LteEesmErrorModel::LoadErrorData()
    {
        if (errorDataLoaded)
            return;

        picojson::object o = load_json(PROJECT_SOURCE_PATH"/src/lte/model/BLER/bler_5g.json");

        {
            auto temp = o["Channel Models"].get<picojson::array>();
            for (auto it = temp.begin(); it != temp.end(); it++)
            {
                channelModelTable5g.push_back(it->to_str());
            }
        }

        {
            auto temp = o["Block Sizes"].get<picojson::array>();
            for (auto it = temp.begin(); it != temp.end(); it++)
                cbSizeTable5g.push_back((uint16_t)it->get<double>());
        }

        {
            auto temp = o["Numerologies"].get<picojson::array>();
            for (auto it = temp.begin(); it != temp.end(); it++)
                numerologyTable5g.push_back((uint8_t)it->get<double>());
        }
        {
            auto temp = o["SNR values"].get<picojson::array>();
            for (auto it = temp.begin(); it != temp.end(); it++)
                snrValueTable5g.push_back(it->get<double>());
        }
        {
            auto temp = o["Speeds"].get<picojson::array>();
            for (auto it = temp.begin(); it != temp.end(); it++)
                speedTable5g.push_back((uint16_t)it->get<double>());
        }
        {
            auto temp = o["BLER"].get<picojson::object>();
            for (auto channel = temp.begin(); channel != temp.end(); channel++)
            {
                auto cur_channel = channel->second.get<picojson::object>();
                for (auto num = cur_channel.begin (); num != cur_channel.end (); num++)
                {
                    auto cur_num = num->second.get<picojson::object>();
                    for (auto cb = cur_num.begin (); cb != cur_num.end (); cb++)
                    {
                        std::vector<std::vector<double>> tempMcs;
                        auto cur_cb = cb->second.get<picojson::array>();
                        for (auto mcs = cur_cb.begin (); mcs != cur_cb.end (); mcs++)
                        {
                            auto cur_mcs = mcs->get<picojson::array> ();
                            std::vector<double> bler_snr;
                            for (auto bler = cur_mcs.begin (); bler != cur_mcs.end (); bler++)
                            {
                                bler_snr.push_back (bler->get<double> ());
                            }
                            tempMcs.push_back (bler_snr);
                        }
                        std::stringstream ss;
                        ss << channel->first << "_" << num->first << "_" << cb->first;
                        std::string scen = ss.str();
                        //std::cout << scen << std::endl;
                        blerTable5g[scen] = tempMcs;
                    }
                }
            }
        }

        o = load_json(PROJECT_SOURCE_PATH"/src/lte/model/BLER/beta_values.json");
        {
            auto temp = o["channel"].get<picojson::object>();
            for (auto channel = temp.begin(); channel != temp.end(); channel++)
            {
                //std::cout << "ch " << channel->first << std::endl;
                auto cur_channel = channel->second.get<picojson::object>()["numerology"].get<picojson::object>();
                for (auto num = cur_channel.begin (); num != cur_channel.end (); num++)
                {
                    //std::cout << "num " << num->first << std::endl;
                    auto cur_num = num->second.get<picojson::object>()["block_size"].get<picojson::object>();
                    for (auto cb = cur_num.begin (); cb != cur_num.end (); cb++)
                    {
                        //std::cout << "cbsize " << cb->first << std::endl;
                        std::map<uint16_t, std::map<uint16_t,double>> tempMcs;
                        auto cur_cb = cb->second.get<picojson::object>()["MCS"].get<picojson::object>();
                        for (auto mcs = cur_cb.begin (); mcs != cur_cb.end (); mcs++)
                        {
                            //std::cout << "mcs " << mcs->first << std::endl;
                            auto mcsi = std::stoi(mcs->first);
                            auto cur_mcs = mcs->second.get<picojson::object> ()["speed"].get<picojson::object>();
                            std::map<uint16_t, double> speed_beta;
                            for (auto speed = cur_mcs.begin (); speed != cur_mcs.end (); speed++)
                            {
                                //std::cout << "speed " << speed->first << std::endl;
                                double beta = std::stod(speed->second.get<std::string>());
                                //std::stringstream ss1;
                                //ss1 << "ch " << channel->first << "_" << num->first << "_" << cb->first << " mcs " << mcs->first << " speed " << speed->first << " beta " << beta << std::endl;
                                //std::cout << ss1.str() << std::endl;
                                speed_beta.emplace(std::stoi(speed->first), beta);
                            }
                            tempMcs.emplace(mcsi-1, speed_beta);
                        }
                        std::stringstream ss;
                        ss << channel->first << "_" << num->first << "_" << cb->first;
                        std::string scen = ss.str();
                        //std::cout << scen << std::endl;
                        betaTable5g.emplace(scen, tempMcs);
                    }
                }
            }
        }
        errorDataLoaded = true;
    }


    template <class T>
    size_t
    findIndex(std::vector<T> vec, T val)
    {
        size_t i = 0;
        for (auto it : vec)
        {
            if (val == it) {
                return i;
            }
            i++;
        }

        return vec.size();
    }

    double
    LteEesmErrorModel::MappingMiBler (double snreff, uint8_t mcs, uint16_t cbSize, uint8_t num, std::string chan)
    {

        if (!errorDataLoaded)
            LoadErrorData();

        unsigned snrIndex = snrValueTable5g.size() - 1;
        //std::cout << snreff << std::endl;
        //get nearest larger snr
        for (unsigned i = 0; i < snrValueTable5g.size();i++)
        {
            if (snrValueTable5g[i] >= snreff)
            {
                snrIndex = i;
                break;
            }
        }
        
        std::stringstream ss;
        ss << chan << "_" << (int) num << "_" << (int) cbSize;
        std::string scen = ss.str();

        double bler = 1.0;
        if (blerTable5g.find(scen) != blerTable5g.end())
            bler = blerTable5g[scen][mcs][snrIndex];
        //std::cout << "snrIndex " << snrIndex << " scenario " << scen << " cbler " << bler << std::endl;
        return bler;
    }

    TbStats_t
    LteEesmErrorModel::GetTbDecodificationStats (const SpectrumValue& sinr,
                                                 const std::vector<int>& map,
                                                 uint16_t prb_size,
                                                 uint32_t size,
                                                 uint8_t mcs,
                                                 HarqProcessInfoList_t miHistory,
                                                 uint8_t num,
                                                 std::string chan,
                                                 double speed)
    {
        std::vector<double> sinrAsDoubles;
        for (int i = 0; i < sinr.ConstValuesEnd()-sinr.ConstValuesBegin(); i++)
        {
            sinrAsDoubles.push_back(sinr.ValuesAt(i));
        }
        return GetTbDecodificationStatsDoubles(sinrAsDoubles, map, prb_size, size, mcs, miHistory, num, chan, speed);
    }

    TbStats_t
    LteEesmErrorModel::GetTbDecodificationStatsDoubles (std::vector<double> sinr,
                                                        const std::vector<int>& map,
                                                        uint16_t prb_size,
                                                        uint32_t size,
                                                        uint8_t mcs,
                                                        HarqProcessInfoList_t miHistory,
                                                        uint8_t num,
                                                        std::string chan,
                                                        double speed)
    {
        NS_LOG_FUNCTION (sinr << &map << (uint32_t) size << (uint32_t) mcs);

        if (map.size() == 0)
            return TbStats_t{};

        if (!errorDataLoaded)
        {
            LoadErrorData();
        }

        /**
         * Size variable refers to the transport block size (TBS), but
         * but transmission is made using code blocks (CBs).
         * Code block sizes (CBSs) are defined by the MCS and numerology.
         *
         * We have a few cases:
         *  1 - TBS fits into a single CB, where the CB used will be the smaller CB in which the payload can fit
         *  2 - TBS requires multiple CBs, which can be of equal or different sizes
         *          e.g. 9000 bits requires a CB with 8192 bits (bigsize) and a CB with 1024 bits (smallsize)
         *          e.g. 10kb requires a CB with 8192 bits + CB with 2048 bits
         *          e.g. 18kb requires two CBs with 8192 bits + CB with 4096 bits
         *                  (last part would fit in 2048 bits, but there is additional fragmenting overhead)
         */
        int tbs_bits = size * 8;
        int big_cb_size, small_cb_size, big_cb_num, small_cb_num;
        big_cb_size = small_cb_size = big_cb_num = small_cb_num = 0;

        {
            // estimate CB size (according to sec 5.1.2 of TS 36.212)
            uint16_t Z = 8192; // max size of a codeblock (including CRC)
            uint32_t B = tbs_bits;
            uint32_t C = 0; // no. of codeblocks
            uint32_t B1 = 0; // tbs + codeblock CRCs overhead
            uint32_t deltaK = 0;
            if (B <= Z)
            {
                // only one codeblock
                //L = 0;
                C = 1;
                B1 = B;
            }
            else
            {
                uint32_t L = 24;
                C = ceil((double) B / ((double) (Z - L)));
                B1 = B + C * L;
            }

            // implement a modified binary search
            int min = 0;

            int max = cbSizeTable5g.size() - 1;
            int mid = 0;

            //todo: aproveitar essa parte, escolhe a melhor configuração de codeblocks
            do
            {
                mid = (min + max) / 2;
                if (B1 > cbSizeTable5g[mid] * C)
                {
                    if (B1 < cbSizeTable5g[mid + 1] * C)
                    {
                        break;
                    }
                    else
                    {
                        min = mid + 1;
                    }
                }
                else
                {
                    if ( (mid-1 >= 0) && B1 > cbSizeTable5g[mid - 1] * C)
                    {
                        break;
                    }
                    else
                    {
                        max = mid - 1;
                    }
                }
            } while ((cbSizeTable5g[mid] * C != B1) && (min < max));

            // adjust binary search to the largest integer value of K containing B1
            if (B1 > cbSizeTable5g[mid] * C)
            {
                mid++;
            }

            uint16_t KplusId = mid;
            big_cb_size = cbSizeTable5g[mid];

            if (C == 1)
            {
                small_cb_num = 1;
                small_cb_size = big_cb_size;
                big_cb_num = 0;
                big_cb_size = 0;
            }
            else
            {
                // second segmentation size: K- = maximum K in table such that K < K+
                // -fstrict-overflow sensitive, see bug 1868
                small_cb_size = cbSizeTable5g[KplusId > 1 ? KplusId - 1 : 0];
                deltaK = big_cb_size - small_cb_size;
                small_cb_num = floor((((double) C * big_cb_size) - (double) B1) / (double) deltaK);
                big_cb_num = C - small_cb_num;
            }
            //std::cout << "tbs bits " << tbs_bits << " B1 " << B1 << std::endl;
        }

        // Load beta values from the lookup table
        // todo: interpolate beta with speed
        double beta5gBig = 1;
        double beta5gSmall = 1;

        {
            // Retrieve beta keys for big and small CBs
            std::stringstream ss;
            ss << chan << "_" << int(num) << "_" << big_cb_size;
            std::string betaKeyBig = ss.str();
            std::stringstream ss1;
            ss1 << chan << "_" << int(num) << "_" << small_cb_size;
            std::string betaKeySmall = ss1.str();

            if (big_cb_num > 0)
                if (betaTable5g.find(betaKeyBig) != betaTable5g.end())
                {
                    auto betaTable5gMcsAndSpeed = betaTable5g[betaKeyBig][mcs];
                    double interpolatedBeta = betaTable5gMcsAndSpeed.begin()->second;
                    for (auto it = betaTable5gMcsAndSpeed.begin(); it != betaTable5gMcsAndSpeed.end(), it->first != speed; it++)
                    {
                        if (it->first > speed)
                        {
                            interpolatedBeta = (interpolatedBeta + it->second) / 2;
                            break;
                        }
                        interpolatedBeta = it->second;
                    }
                    beta5gBig = interpolatedBeta;
                }
                else
                    std::cout << betaKeyBig << " is missing from the beta registry" << std::endl;

            if (small_cb_num > 0)
                if (betaTable5g.find(betaKeySmall) != betaTable5g.end())
                {
                    auto betaTable5gMcsAndSpeed = betaTable5g[betaKeySmall][mcs];
                    double interpolatedBeta = betaTable5gMcsAndSpeed.begin()->second;
                    for (auto it = betaTable5gMcsAndSpeed.begin(); it != betaTable5gMcsAndSpeed.end(), it->first != speed; it++)
                    {
                        if (it->first > speed)
                        {
                            interpolatedBeta = (interpolatedBeta + it->second) / 2;
                            break;
                        }
                        interpolatedBeta = it->second;
                    }
                    beta5gSmall = interpolatedBeta;
                }
                else
                    std::cout << betaKeySmall << " is missing from the beta registry" << std::endl;
        }

        /**
         * Originally, the effective SNR of the TBS was calculated as the SNR of the PRBs
         *
         * uint32_t n = map.size();
         * double ex = 0;
         * for (auto mapVal : map)
         * {
         *     ex += -(sinr[mapVal])/beta5gBig;
         * }
         * double snr_eff =  -beta5gBig * ex/n;
         *
         * However, the 5G-RANGE beta values are per CB.
         * We use the MCS to find the bit capacity of the PRBs
         * Then compute a weighted mean SNR of the PRBs inside of each CB
         *
         *
         *  TBS
         * +-------------------------------------+
         * |   CB0                      CB1      |
         * | +-----------------------+---------+ |
         * | | RB0  1  2  3  4  5  6 :7  8  9  | |
         * | | +--+--+--+--+--+--+--+--+--+--+ | |
         * | | |  |  |  |  |  |  |  |: |  |  | | |
         * | | |  |  |  |  |  |  |  |: |  |  | | |
         * | | +--+--+--+--+--+--+--+--+--+--+ | |
         * | |                       :         | |
         * | +-----------------------+---------+ |
         * |                                     |
         * +-------------------------------------+
         *
         *   TBS
         * +-------------------------------------+
         * |   CB0                               |
         * | +---------------------------------+ |
         * | | RB0  1  2  3  4  5  6  7  8  9  | |
         * | | +--+--+--+--+--+--+--+--+--+--+ | |
         * | | |  |  |  |  |  |  |  |  |  |  | | |
         * | | |  |  |  |  |  |  |  |  |  |  | | |
         * | | +--+--+--+--+--+--+--+-++--+--+ | |
         * | |                                 | |
         * | +---------------------------------+ |
         * |                                     |
         * +-------------------------------------+
         *
         *   TBS
         * +-------------------------------------+
         * |   CB0               CB1             |
         * | +----------------+----------------+ |
         * | | RB0  1  2  3  4: 5  6  7  8  9  | |
         * | | +--+--+--+--+--+--+--+--+--+--+ | |
         * | | |  |  |  |  |  :  |  |  |  |  | | |
         * | | |  |  |  |  |  :  |  |  |  |  | | |
         * | | +--+--+--+--+--+--+--+-++--+--+ | |
         * | |                :                | |
         * | +----------------+----------------+ |
         * |                                     |
         * +-------------------------------------+
         *
         * SNR_EFF(CB0) = (1*RB0 + 1*RB1 + ... + 0.x*RB7)/7.x
         * SNR_EFF(CB1) = ((1-0.x)*RB7 + 1*RB8 + ... + 1*RB10)/(4-0.x)
         *
         */

        std::vector<std::tuple<int, double, double>> cb_snr_components;
        int smallBeta = big_cb_num;
        {
            uint32_t n = map.size();
            // Calculate the SINR components of the CBS
            auto it = map.begin();
            double curr_prb_sinr = sinr[*it];

            // Proceed to CB SINR fraction calculations
            int tbs_size = tbs_bits;
            double curr_cb_size = big_cb_num > 0 ? big_cb_size : (small_cb_num > 0 ? small_cb_size : 0);
            int curr_cb_index, used_budget, prb_budget, new_cb_budget, new_cb_size;
            curr_cb_index = used_budget = prb_budget = new_cb_budget = new_cb_size = 0;
            double prb_fraction = 0.0;
            while (tbs_size > 0)
            {
                if ( it == map.end() )
                    break; // codeblock doesnt fit into transport block

                // fetch remaining bits of current PRB
                prb_budget = prb_size - used_budget;

                // calculate remaining bits of current CB
                new_cb_size = curr_cb_size > prb_budget ? curr_cb_size - prb_budget : 0;

                //calculate remaining bits of current PRB after subtracting those used for the CB
                prb_budget = new_cb_size > 0 ? 0 : prb_budget - curr_cb_size;

                // calculate fraction of PRB used by the CB
                prb_fraction = (curr_cb_size - new_cb_size) / prb_size;

                // store SINR and fraction of CB used for effective SNR calculation
                cb_snr_components.emplace_back(curr_cb_index, curr_prb_sinr, prb_fraction);

                // update remaining bits of CB
                curr_cb_size = new_cb_size;

                // update remaining bits of PRB
                used_budget = prb_size - prb_budget;

                // if current CB has been fulfilled
                if (curr_cb_size == 0)
                {
                    // subtract fulfilled CB and discount size from TBS
                    if (big_cb_num > 0)
                    {
                        big_cb_num--;
                        tbs_size -= big_cb_size;
                    }
                    else if (small_cb_num > 0)
                    {
                        small_cb_num--;
                        tbs_size -= small_cb_size;
                    }
                    else
                        break;

                    // break loop if all code blocks have been processed
                    if ((big_cb_num + small_cb_num) == 0)
                        break;

                    curr_cb_size = big_cb_num > 0 ? big_cb_size : (small_cb_num > 0 ? small_cb_size : curr_cb_size);
                    curr_cb_index++;
                }

                // if current PRB has been exhausted
                if (used_budget == prb_size)
                {
                    it++;
                    if (it != map.end())
                    {
                        curr_prb_sinr = sinr[*it];
                        used_budget = 0;
                    }
                }
            }
        }

        std::vector<double> tbs_snr_components;
        double errorRate = 1.0;
        {
            double n = 0;
            int curr_cb = 0;
            double avg_cb_sinr = 0;
            double snrEff = 0;
            double cbler = 0;
            double beta = curr_cb < smallBeta ? beta5gBig : beta5gSmall;
            unsigned cb_size = curr_cb < smallBeta ? big_cb_size : small_cb_size;

            // compute mean SINR of CBs based on PRBs SINR and fraction used
            for (auto entry: cb_snr_components)
            {
                // fetch precalculated values of SINR of a PRB and fraction used by a certain indexed CB
                int cb_index = std::get<0>(entry);
                double prb_sinr = std::get<1>(entry);
                double prb_fraction = std::get<2>(entry);

                // when a different CB is reached
                if (cb_index != curr_cb)
                {
                    // calculate the effective SNR and corresponding BLER
                    snrEff = -beta*log(avg_cb_sinr/n);
                    //snrEff = 10*log10(avg_cb_sinr/n);
                    cbler = MappingMiBler(snrEff, mcs, cb_size, num, chan);

                    // then aggregate the error rate of the TB
                    errorRate *= (1.0 - cbler);

                    // and finally reset the variables that will get reused by the next CB
                    n = 0;
                    avg_cb_sinr = 0;
                    curr_cb = cb_index;
                    beta = curr_cb < smallBeta ? beta5gBig : beta5gSmall;
                    cb_size = curr_cb < smallBeta ? big_cb_size : small_cb_size;
                }

                // calculate effective SNR fraction of the current PRB of a given CB
                avg_cb_sinr += exp(-10 * log10(prb_sinr) / beta) * prb_fraction;
                //avg_cb_sinr += prb_sinr * prb_fraction;
                n += prb_fraction;

            }
            // calculate the effective SNR and corresponding BLER of the last CB
            snrEff = -beta*log(avg_cb_sinr/n);
            //snrEff = 10*log10(avg_cb_sinr/n);
            cbler = MappingMiBler(snrEff, mcs, cb_size, num, chan);

            // then aggregate the error rate of the TB
            errorRate *= (1.0 - cbler);
            //std::cout << "sinr " << snrEff << " cbs " << small_cb_size << " cbler " << cbler << " tbler "<< 1-errorRate << std::endl;
        }

        // compute final TB error rate
        errorRate = 1.0 - errorRate;

        NS_LOG_LOGIC (" Error rate " << errorRate);
        TbStats_t ret{};
        ret.tbler = errorRate;

        return ret;
    }




} // namespace ns3
