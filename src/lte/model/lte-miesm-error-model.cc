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
#include <ns3/lte-miesm-error-model.h>
#include <ns3/lte-module.h>

#include "json_loader.h"


namespace ns3 {

    NS_LOG_COMPONENT_DEFINE ("LteMiesmErrorModel");

    static std::vector<uint16_t> cbSizeTable5g;
    static std::vector<std::string> channelModelTable5g;
    static std::vector<uint8_t> numerologyTable5g;
    static std::vector<double> snrValueTable5g;
    static std::vector<uint16_t> speedTable5g;
    static std::map<std::string, std::vector<std::vector<double>>> blerTable5g;
    static std::unordered_map<double, uint16_t> snrIndex5g;
    static double beta5g = 1;
    bool LteMiesmErrorModel::errorDataLoaded = false;
    void LteMiesmErrorModel::LoadErrorData()
    {

        picojson::object o = load_json("../../src/lte/model/BLER/bler_5g.json");

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

        errorDataLoaded = true;
    }

    double
    LteMiesmErrorModel::Mib (const SpectrumValue& sinr, const std::vector<int>& map, uint8_t mcs)
    {
        NS_LOG_FUNCTION (sinr << &map << (uint32_t) mcs);

        if (!errorDataLoaded)
            LoadErrorData();

        uint32_t n = map.size();
        double ex = 0;
        for (uint32_t i = 0; i < n; ++i)
        {
            ex+=exp( (-1) * (sinr[map.at(i)]/beta5g) );
        }
        double snr_eff = (-1) * beta5g * log(ex/n);
        return snr_eff;
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
    LteMiesmErrorModel::MappingMiBler (double snreff, uint8_t mcs, uint16_t cbSize, uint8_t num, std::string chan)
    {

        if (!errorDataLoaded)
            LoadErrorData();

        NS_ASSERT_MSG (mcs <= MIESM_MAX_MCS, "mcs " << mcs << " is out of range");
        size_t cbSizeIndex = findIndex(cbSizeTable5g, cbSize);
        NS_ASSERT_MSG (cbSizeIndex < cbSizeTable5g.size(), "cbSize " << cbSize << " not found");

        size_t numIndex = findIndex(numerologyTable5g, num);
        NS_ASSERT_MSG (numIndex < numerologyTable5g.size(), "num " << num << " not found");

        size_t chanIndex = findIndex(channelModelTable5g, chan);
        NS_ASSERT_MSG (chanIndex < channelModelTable5g.size(), "chan " << chan << " not found");

        size_t snrIndex = snrValueTable5g.size() - 1;

        //get nearest larger snr
        for (size_t i = 0; i < snrValueTable5g.size();i++)
        {
            if (snrValueTable5g[i] >= snreff)
            {
                snrIndex = i;
                break;
            }
        }


        NS_LOG_DEBUG ("BLER of channel " << chanIndex << " numerology " << numIndex << " code block " << cbSizeIndex << " mcs " << (size_t)mcs << " snr " << snrIndex);
        std::stringstream ss;
        ss << chan << "_" << (int) num << "_" << (int) cbSize;
        std::string scen = ss.str();
        //std::cout << "pinging " << scen << std::endl;
        if (mcs>26)//todo: checar com luís
            mcs=26;
        return blerTable5g[scen][mcs][snrIndex];
        //return blerTable5g[chanIndex][numIndex][cbSizeIndex][mcs][snrIndex];
    }

    TbStats_t
    LteMiesmErrorModel::GetTbDecodificationStats (const SpectrumValue& sinr, const std::vector<int>& map, uint16_t size, uint8_t mcs, HarqProcessInfoList_t miHistory, uint8_t num, std::string chan)
    {
        NS_LOG_FUNCTION (sinr << &map << (uint32_t) size << (uint32_t) mcs);

        double snrEff = Mib(sinr, map, mcs);

        double Reff = 0.0;
        NS_ASSERT (mcs < 16);

        // estimate CB size (according to sec 5.1.2 of TS 36.212)
        uint16_t Z = 8192; // max size of a codeblock (including CRC), utilizar apenas os valores de 8192
        uint32_t B = size * 8;
        uint32_t C = 0; // no. of codeblocks
        uint32_t Cplus = 0; // no. of codeblocks with size K+
        uint32_t Kplus = 0; // no. of codeblocks with size K+
        uint32_t Cminus = 0; // no. of codeblocks with size K+
        uint32_t Kminus = 0; // no. of codeblocks with size K+
        uint32_t B1 = 0;
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
            C = ceil ((double)B / ((double)(Z-L)));
            B1 = B + C * L;
        }

        // implement a modified binary search
        int min = 0;

        int max = cbSizeTable5g.size() - 1;
        int mid = 0;

        //todo: aproveitar essa parte, escolhe a melhor configuração de codeblocks
        do
        {
            mid = (min+max) / 2;
            if (B1 > cbSizeTable5g[mid]*C)
            {
                if (B1 < cbSizeTable5g[mid+1]*C)
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
                if (B1 > cbSizeTable5g[mid-1]*C)
                {
                    break;
                }
                else
                {
                    max = mid - 1;
                }
            }
        } while ((cbSizeTable5g[mid]*C != B1) && (min < max));


        // adjust binary search to the largest integer value of K containing B1
        if (B1 > cbSizeTable5g[mid]*C)
        {
            mid ++;
        }

        uint16_t KplusId = mid;
        Kplus = cbSizeTable5g[mid];


        if (C==1)
        {
            Cplus = 1;
            Cminus = 0;
            Kminus = 0;
        }
        else
        {
            // second segmentation size: K- = maximum K in table such that K < K+
            // -fstrict-overflow sensitive, see bug 1868
            Kminus = cbSizeTable5g[ KplusId > 1 ? KplusId - 1 : 0];
            deltaK = Kplus - Kminus;
            Cminus = floor ((((double) C * Kplus) - (double)B1) / (double)deltaK);
            Cplus = C - Cminus;
        }

        NS_LOG_INFO ("--------------------LteMiesmErrorModel: TB size of " << B << " needs of " << B1 << " bits reparted in " << C << " CBs as "<< Cplus << " block(s) of " << Kplus << " and " << Cminus << " of " << Kminus);
        //fim da busca binaria, c+ CODEBLOCKS DE TAMANHO K+ e C- codeblocks de tamanho k-

        double errorRate = 1.0;
        if (C!=1)
        {
            double cbler = MappingMiBler (snrEff, mcs, Kplus, num, chan);
            errorRate *= pow (1.0 - cbler, Cplus);
            cbler = MappingMiBler (snrEff, mcs, Kminus, num, chan);
            errorRate *= pow (1.0 - cbler, Cminus);
            errorRate = 1.0 - errorRate;
        }
        else
        {
            errorRate = MappingMiBler (snrEff, mcs, Kplus, num, chan);
        }

        NS_LOG_LOGIC (" Error rate " << errorRate);
        TbStats_t ret{};
        ret.tbler = errorRate;

        return ret;
    }




} // namespace ns3
