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
 * Original Author: Giuseppe Piro  <g.piro@poliba.it>
 * Modified by:     Marco Miozzo   <mmiozzo@cttc.es>
 *                  Nicola Baldo   <nbaldo@cttc.es>
 */


#include <ns3/lte-amc.h>
#include <ns3/log.h>
#include <ns3/assert.h>
#include <ns3/math.h>
#include <vector>
#include <ns3/spectrum-value.h>
#include <ns3/double.h>
#include "ns3/enum.h"
#include <ns3/lte-mi-error-model.h>
#include <ns3/lte-miesm-error-model.h>
#include <ns3/string.h>
#include "json_loader.h"



namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("LteAmc");

NS_OBJECT_ENSURE_REGISTERED (LteAmc);

/**
 * Table of CQI index and its spectral efficiency. Taken from 3GPP TSG-RAN WG1
 * [R1-081483 Conveying MCS and TB size via PDCCH]
 * (http://www.3gpp.org/ftp/tsg_ran/WG1_RL1/TSGR1_52b/Docs/R1-081483.zip)
 * file `TBS_support.xls` tab "MCS Table" (rounded to 2 decimal digits).
 * The index of the vector (range 0-15) identifies the CQI value.
 */
static const double SpectralEfficiencyForCqi[16] = {
  0.0, // out of range
  0.083, 0.250, 0.417, 0.750, 1.000,
  1.500, 2.167, 3.000, 3.500, 4.500,
  5.250, 6.000, 6.667, 7.000, 7.667
};

#if 0 // currently unused
/**
 * Table of MCS index (IMCS) and its TBS index (ITBS). Taken from 3GPP TS
 * 36.213 v8.8.0 Table 7.1.7.1-1: _Modulation and TBS index table for PDSCH_.
 * The index of the vector (range 0-31; valid values 0-28) identifies the MCS
 * index. Note that this is similar to the one in R1-081483, but:
 * - a few values are different; and
 * - in R1-081483, a valid MCS index is in the range of 1-30 (not 0-28).
 */
static const int ModulationSchemeForMcs[32] = {
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
  4, 4, 4, 4, 4, 4, 4,
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
  2,  // reserved
  4,  // reserved
  6,  // reserved
};
#endif

/**
 * Table of MCS index and its spectral efficiency. Taken from 3GPP TSG-RAN WG1
 * [R1-081483 Conveying MCS and TB size via PDCCH]
 * (http://www.3gpp.org/ftp/tsg_ran/WG1_RL1/TSGR1_52b/Docs/R1-081483.zip)
 * file `TBS_support.xls` tab "MCS Table" (rounded to 2 decimal digits).
 * The index of the vector (range 0-31) corresponds to the MCS index according
 * to the convention in TS 36.213 (i.e., the MCS index reported in R1-081483
 * minus one)
 */
static const double SpectralEfficiencyForMcs[27] = {
            0.083, 0.167, 0.250, 0.333, 0.417, 0.583, 0.750, 0.833, 1.000,
            1.166, 1.500, 1.833, 2.167, 2.500, 3.000, 3.333, 3.500, 4.000,
            4.500, 4.750, 5.250, 5.500, 6.000, 6.667, 7.000, 7.333, 7.667
    };


/**
 * Table of number of physical resource blocks (NPRB), TBS index (ITBS), and
 * their associated transport block size. Taken from 3GPP TS 36.213 v8.8.0
 * Table 7.1.7.2.1-1: _Transport block size table (dimension 27×110)_.
 * \note For NPRB = 1 and ITBS = 6 the standard returns 328, but it is not
 *       consistent with the other values, therefore we use 88 obtained by
 *       following the sequence of NPRB = 1 values.
 */
//                            MCS   NUMEROLOGY   TBS
static std::map<std::tuple<uint8_t, uint8_t>, uint32_t> prb5gSize;
bool LteAmc::prbDataLoaded = false;


void LteAmc::LoadPrbData()
{
    picojson::object o = load_json("../../src/lte/model/BLER/TBS_MCS.json");

    auto itbs_o = o["TBS"].get<picojson::object>();

    auto mcs_o = itbs_o["MCS"].get<picojson::object>();
    for (auto mcs = mcs_o.begin(); mcs != mcs_o.end(); mcs++)
    {
        auto mcs_i = std::stoi(mcs->first);
        //std::cout << mcs_i << std::endl;

        auto numrbs_o = mcs->second.get<picojson::object>()["#RBs"].get<picojson::object>();
        for (auto numrbs = numrbs_o.begin (); numrbs != numrbs_o.end (); numrbs++)
        {
            uint32_t num = std::stoi(numrbs->first);
            //std::cout << num << std::endl;

            auto numerology_o = numrbs->second.get<picojson::object>()["NUMEROLOGY"].get<picojson::object>();
            for (auto numerology = numerology_o.begin (); numerology != numerology_o.end (); numerology++)
            {
                auto numerology_i = std::stoi(numerology->first);
                //std::cout << numerology_i << std::endl;

                //uint32_t num = std::stoi(numrbs->first);
                //std::cout << num << std::endl;

                double tbs = std::stod(numerology->second.to_str());
                prb5gSize.insert({{(uint8_t)mcs_i, (uint8_t)numerology_i}, tbs});
            }
        }

    }
    prbDataLoaded = true;
}

LteAmc::LteAmc ()
{
}


LteAmc::~LteAmc ()
{ 
}

TypeId
LteAmc::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::LteAmc")
  .SetParent<Object> ()
  .SetGroupName("Lte")
  .AddConstructor<LteAmc> ()
  .AddAttribute ("Ber",
                 "The requested BER in assigning MCS (default is 0.00005).",
                 DoubleValue (0.00005),
                 MakeDoubleAccessor (&LteAmc::m_ber),
                 MakeDoubleChecker<double> ())
  .AddAttribute ("AmcModel",
                "AMC model used to assign CQI",
                 EnumValue (LteAmc::MiesmErrorModel),
                 MakeEnumAccessor (&LteAmc::m_amcModel),
                 MakeEnumChecker (LteAmc::MiErrorModel, "Vienna",
                                  LteAmc::PiroEW2010, "PiroEW2010", LteAmc::MiesmErrorModel, "RANGE"))
  .AddAttribute ("Numerology",
                 "5GRANGE Numerology",
                 UintegerValue (0),
                 MakeUintegerAccessor (&LteAmc::m_numerology),
                 MakeUintegerChecker<uint16_t> ())
  .AddAttribute ("ChannelModel",
                 "5GRANGE Channel Model",
                 StringValue("CDL_A"),
                 MakeStringAccessor (&LteAmc::m_channelModel),
                 MakeStringChecker ());
  return tid;
}


int
LteAmc::GetCqiFromSpectralEfficiency (double s)
{
  NS_LOG_FUNCTION (s);
  NS_ASSERT_MSG (s >= 0.0, "negative spectral efficiency = " << s);
  int cqi = 0;
  while ((cqi < 15) && (SpectralEfficiencyForCqi[cqi + 1] < s))
    {
      ++cqi;
    }
  NS_LOG_LOGIC ("cqi = " << cqi);
  return cqi;
}


int
LteAmc::GetMcsFromCqi (int cqi)
{
  NS_LOG_FUNCTION (cqi);
  NS_ASSERT_MSG (cqi >= 0 && cqi <= 15, "CQI must be in [0..15] = " << cqi);
  double spectralEfficiency = SpectralEfficiencyForCqi[cqi];
  int mcs = 0;
  while ((mcs < 26) && (SpectralEfficiencyForMcs[mcs + 1] <= spectralEfficiency))
    {
      ++mcs;
    }
  NS_LOG_LOGIC ("mcs = " << mcs);
  return mcs;
}

int
LteAmc::GetDlTbSizeFromMcs (int mcs, int nprb)
{
  NS_LOG_FUNCTION (mcs);

  NS_ASSERT_MSG (mcs < 27, "MCS=" << mcs);
  NS_ASSERT_MSG (nprb < 133, "NPRB=" << nprb);

  if (!prbDataLoaded)
      LoadPrbData ();
  std::tuple<uint8_t, uint8_t> key{(uint8_t)mcs, (uint8_t)m_numerology};
  return prb5gSize[key]*nprb;
}

int
LteAmc::GetUlTbSizeFromMcs (int mcs, int nprb)
{
  NS_LOG_FUNCTION (mcs);

  NS_ASSERT_MSG (mcs < 27, "MCS=" << mcs);
  NS_ASSERT_MSG (nprb < 133, "NPRB=" << nprb);

  if (!prbDataLoaded)
      LoadPrbData ();
  std::tuple<uint8_t, uint8_t> key{(uint8_t)mcs, (uint8_t)m_numerology};
  return prb5gSize[key]*nprb;
}


double
LteAmc::GetSpectralEfficiencyFromCqi (int cqi)
{
  NS_LOG_FUNCTION (cqi);
  NS_ASSERT_MSG (cqi >= 0 && cqi <= 15, "CQI must be in [0..15] = " << cqi);
  NS_LOG_LOGIC ("Spectral efficiency = " << SpectralEfficiencyForCqi[cqi]);
  return SpectralEfficiencyForCqi[cqi];
}


std::vector<int>
LteAmc::CreateCqiFeedbacks (const SpectrumValue& sinr, uint8_t rbgSize)
{
  NS_LOG_FUNCTION (this);

  std::vector<int> cqi;
  cqi.reserve(sinr.ConstValuesEnd()-sinr.ConstValuesBegin());
  Values::const_iterator it;
  
  if (m_amcModel == PiroEW2010)
    {

      for (it = sinr.ConstValuesBegin (); it != sinr.ConstValuesEnd (); it++)
        {
          double sinr_ = (*it);
          if (sinr_ == 0.0)
            {
              cqi.push_back (-1); // SINR == 0 (linear units) means no signal in this RB
            }
          else
            {
              /*
              * Compute the spectral efficiency from the SINR
              *                                        SINR
              * spectralEfficiency = log2 (1 + -------------------- )
              *                                    -ln(5*BER)/1.5
              * NB: SINR must be expressed in linear units
              */

              double s = log2 ( 1 + ( sinr_ / ( (-std::log (5.0 * m_ber )) / 1.5) ));

              int cqi_ = GetCqiFromSpectralEfficiency (s);

              NS_LOG_LOGIC (" PRB =" << cqi.size ()
                                    << ", sinr = " << sinr_
                                    << " (=" << 10 * std::log10 (sinr_) << " dB)"
                                    << ", spectral efficiency =" << s
                                    << ", CQI = " << cqi_ << ", BER = " << m_ber);

              cqi.push_back (cqi_);
            }
        }
    }
  else if (m_amcModel == MiErrorModel  || m_amcModel == MiesmErrorModel)
    {
      NS_LOG_DEBUG (this << " AMC-VIENNA RBG size " << (uint16_t)rbgSize);
      NS_ASSERT_MSG (rbgSize > 0, " LteAmc-Vienna: RBG size must be greater than 0");
      std::vector <int> rbgMap;
      rbgMap.reserve(sinr.ConstValuesEnd()-sinr.ConstValuesBegin());
      int rbId = 0;
      double speed = 0; //todo: calculate speed
      //Make sure things are initialized before trying to run parallel stuff
      {
        HarqProcessInfoList_t harqInfoList;
        switch(m_amcModel)
        {
            case MiErrorModel:
                LteMiErrorModel::GetTbDecodificationStats (sinr, rbgMap, (uint16_t)GetDlTbSizeFromMcs (0, rbgSize) / 8, 0, harqInfoList);
                break;
            case MiesmErrorModel:
                if (!LteMiesmErrorModel::errorDataLoaded)
                    LteMiesmErrorModel::GetTbDecodificationStats (sinr, rbgMap, (uint16_t)GetDlTbSizeFromMcs (0, rbgSize) / 8, 0, harqInfoList, m_numerology, m_channelModel, speed);
                break;
            default:
                break;
        }
      }
      for (it = sinr.ConstValuesBegin (); it != sinr.ConstValuesEnd (); it++)
      {
        rbgMap.push_back (rbId++);
        if ((rbId % rbgSize == 0)||((it+1)==sinr.ConstValuesEnd ()))
         {
            TbStats_t tbStats;
            TbStats_t tbStatsVector[27];

            for (uint8_t mcs = 0; mcs <= 26; mcs++)
            {
                HarqProcessInfoList_t harqInfoList;
                if (m_amcModel == MiErrorModel)
                    tbStatsVector[mcs] = LteMiErrorModel::GetTbDecodificationStats (sinr, rbgMap, (uint16_t)GetDlTbSizeFromMcs (mcs, rbgSize) / 8, mcs, harqInfoList);
                else
                    tbStatsVector[mcs] = LteMiesmErrorModel::GetTbDecodificationStats (sinr, rbgMap, (uint16_t)GetDlTbSizeFromMcs (mcs, rbgSize) / 8, mcs, harqInfoList, m_numerology, m_channelModel, speed);
            }

            uint8_t mcs = 0;
            while (mcs <= 26)
            {
              if (tbStatsVector[mcs].tbler > 0.1) break;
              mcs++;
            }
            if (mcs > 0)
            {
                mcs--;
            }
            tbStats = tbStatsVector[mcs];
            NS_LOG_DEBUG (this << "\t RBG " << rbId << " MCS " << (uint16_t)mcs << " TBLER " << tbStats.tbler);
            int rbgCqi = 0;
            if ((tbStats.tbler > 0.1)&&(mcs==0))
              {
                rbgCqi = 0; // any MCS can guarantee the 10 % of BER
              }
            else if (mcs == 26)
              {
                rbgCqi = 15; // all MCSs can guarantee the 10 % of BER
              }
            else
              {
                double s = SpectralEfficiencyForMcs[mcs];
                rbgCqi = 0;
                while ((rbgCqi < 15) && (SpectralEfficiencyForCqi[rbgCqi + 1] < s))
                {
                  ++rbgCqi;
                }
              }
            //std::cout << this << "\t rbId " << rbId << "\t MCS " << (uint16_t)mcs << "-> CQI " << rbgCqi << std::endl;// std::cout > CQI_trace.txt
            NS_LOG_DEBUG (this << "\t MCS " << (uint16_t)mcs << "-> CQI " << rbgCqi);
            // fill the cqi vector (per RB basis)
            for (uint8_t j = 0; j < rbgSize; j++)
              {
                cqi.push_back (rbgCqi);
              }
            rbgMap.clear ();
         }
        
      }
      
    }

  return cqi;
}

uint16_t LteAmc::GetNumerology () const
{
    return m_numerology;
}
void LteAmc::SetChannelModel (std::string chan)
{
    m_channelModel = chan;
}
std::string LteAmc::GetChannelModel () const
{
    return m_channelModel;
}
void LteAmc::SetNumerology (uint16_t num)
{
    m_numerology = num;
}

} // namespace ns3
