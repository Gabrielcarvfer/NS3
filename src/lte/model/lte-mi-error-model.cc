/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
* Copyright (c) 2011 SIGNET LAB. Department of Information Engineering (DEI), University of Padua
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
*      Marco Mezzavilla <mezzavil@dei.unipd.it>
*      Giovanni Tomasi <tomasigv@gmail.com>
* Original Work Acknowldegments:
*      This work was supported by the MEDIEVAL (MultiMEDia transport
*      for mobIlE Video AppLications) project, which is a
*      medium-scale focused research project (STREP) of the 7th
*      Framework Programme (FP7)
*
* Subsequent integration in LENA and extension done by:
*      Marco Miozzo <marco.miozzo@cttc.es>
*/ 

#include <list>
#include <vector>
#include <ns3/log.h>
#include <ns3/pointer.h>
#include <stdint.h>
#include <cmath>
#include "stdlib.h"
#include <ns3/lte-mi-error-model.h>

#include "./BLER/json_loader.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("LteMiErrorModel");


  /// global table of the effective code rates (ECR)s that have BLER performance curves
  static std::vector<double> BlerCurvesEcrMap;

  /// Table codifing standard MCSs ECR to available ECRs
  static std::vector<uint8_t> McsEcrBlerTableMapping;

  /// Table of ECR of the standard MCSs
  static std::vector<double> McsEcrTable;

#if 0 // currently unused
  // Table with ECRs obtained with retransmissions with BLER curves
  static std::vector<double> HarqRetxEcr;
#endif
 
  /** PCFICH-PDCCH Error model based on 3GPP R4-081920 "LTE PDCCH/PCFICH
   *  Demodulation Performance Results with Implementation Margin" 
   *  X axis */
  static std::vector<double> PdcchPcfichBlerCurveXaxis;
  
  /** PCFICH-PDCCH Error model based on 3GPP R4-081920 "LTE PDCCH/PCFICH
   *  Demodulation Performance Results with Implementation Margin" 
   *  Y axis */
  static std::vector<double> PdcchPcfichBlerCurveYaxis;
  
#if 0 // currently unused
  static std::vector<const int> * TbsIndex;
#endif
  
/// as K column of table 5.1.3-3 of TS 36,212
static std::vector<uint16_t> cbSizeTable;

/// MI size table  
static std::vector<uint16_t> cbMiSizeTable;

/// MI map QPSK
static std::vector<double> MI_map_qpsk;

/// MI map QPSK axis
static std::vector<double> MI_map_qpsk_axis;

/// MI map QPSK 16QAM
static std::vector<double> MI_map_16qam;

/// MI map 16QAM axis
static std::vector<double> MI_map_16qam_axis;

/// MI map 64QAM
static std::vector<double> MI_map_64qam;

/// MI map 64QAM axis
static std::vector<double> MI_map_64qam_axis;

/// BECR table
static std::vector< std::vector<double> > bEcrTable;

/// CECR table  
static  std::vector< std::vector<double> > cEcrTable;




bool LteMiErrorModel::errorDataLoaded = false;



void LteMiErrorModel::LoadErrorData()
{

    picojson::object o = load_json("../../src/lte/model/BLER/errorData.min.json");

    {
        auto temp = o["BlerCurvesEcrMap"].get<picojson::array>();
        for (auto it = temp.begin(); it != temp.end(); it++)
            BlerCurvesEcrMap.push_back(it->get<double>());
    }
    {
        auto temp = o["McsEcrBlerTableMapping"].get<picojson::array>();
        for (auto it = temp.begin(); it != temp.end(); it++)
            McsEcrBlerTableMapping.push_back((uint8_t)it->get<double>());
    }
    {
        auto temp = o["McsEcrTable"].get<picojson::array>();
        for (auto it = temp.begin(); it != temp.end(); it++)
            McsEcrTable.push_back(it->get<double>());
    }
    {
        auto temp = o["PdcchPcfichBlerCurveXaxis"].get<picojson::array>();
        for (auto it = temp.begin(); it != temp.end(); it++)
            PdcchPcfichBlerCurveXaxis.push_back(it->get<double>());
    }
    {
        auto temp = o["PdcchPcfichBlerCurveYaxis"].get<picojson::array>();
        for (auto it = temp.begin(); it != temp.end(); it++)
            PdcchPcfichBlerCurveYaxis.push_back(it->get<double>());
    }
    {
        auto temp = o["cbSizeTable"].get<picojson::array>();
        for (auto it = temp.begin(); it != temp.end(); it++)
            cbSizeTable.push_back((uint16_t)it->get<double>());
    }
    {
        auto temp = o["cbMiSizeTable"].get<picojson::array>();
        for (auto it = temp.begin(); it != temp.end(); it++)
            cbMiSizeTable.push_back((uint16_t)it->get<double>());
    }
    {
        auto temp = o["MI_map_qpsk"].get<picojson::array>();
        for (auto it = temp.begin(); it != temp.end(); it++)
            MI_map_qpsk.push_back(it->get<double>());
    }
    {
        auto temp = o["MI_map_qpsk_axis"].get<picojson::array>();
        for (auto it = temp.begin(); it != temp.end(); it++)
            MI_map_qpsk_axis.push_back(it->get<double>());
    }
    {
        auto temp = o["MI_map_16qam"].get<picojson::array>();
        for (auto it = temp.begin(); it != temp.end(); it++)
            MI_map_16qam.push_back(it->get<double>());
    }
    {
        auto temp = o["MI_map_16qam_axis"].get<picojson::array>();
        for (auto it = temp.begin(); it != temp.end(); it++)
            MI_map_16qam_axis.push_back(it->get<double>());
    }
    {
        auto temp = o["MI_map_64qam"].get<picojson::array>();
        for (auto it = temp.begin(); it != temp.end(); it++)
            MI_map_64qam.push_back(it->get<double>());
    }
    {
        auto temp = o["MI_map_64qam_axis"].get<picojson::array>();
        for (auto it = temp.begin(); it != temp.end(); it++)
            MI_map_64qam_axis.push_back(it->get<double>());
    }
    {
        auto temp = o["MI_map_64qam_axis"].get<picojson::array>();
        for (auto it = temp.begin(); it != temp.end(); it++)
            MI_map_64qam_axis.push_back(it->get<double>());
    }
    {
        auto temp = o["bEcrTable"].get<picojson::array>();
        for (auto it = temp.begin(); it != temp.end(); it++)
        {
            std::vector<double> temp3;
            auto temp2 = it->get<picojson::array>();
            for (auto it2 = temp2.begin(); it2 != temp2.end(); it2++)
                temp3.push_back(it2->get<double>());
            bEcrTable.push_back(temp3);
        }
    }
    {
        auto temp = o["cEcrTable"].get<picojson::array>();
        for (auto it = temp.begin(); it != temp.end(); it++)
        {
            std::vector<double> temp3;
            auto temp2 = it->get<picojson::array>();
            for (auto it2 = temp2.begin(); it2 != temp2.end(); it2++)
                temp3.push_back(it2->get<double>());
            cEcrTable.push_back(temp3);
        }
    }

#if 0 // currently unused
    {
        auto temp = o["HarqRetxEcr"].get<picojson::array>();
        for (auto it = temp.begin(); it != temp.end(); it++)
            HarqRetxEcr.push_back(it->get<double>());
    }
    {
        auto temp = o["TbsIndex"].get<picojson::array>();
        for (auto it = temp.begin(); it != temp.end(); it++)
            TbsIndex.push_back((int)it->get<double>());
    }
#endif
    errorDataLoaded = true;

}

double 
LteMiErrorModel::Mib (const SpectrumValue& sinr, const std::vector<int>& map, uint8_t mcs)
{
  NS_LOG_FUNCTION (sinr << &map << (uint32_t) mcs);

  if (!errorDataLoaded)
      LoadErrorData();

  double MI;
  double MIsum = 0.0;
  SpectrumValue sinrCopy = sinr;
  
  for (uint32_t i = 0; i < map.size (); i++)
    {
      double sinrLin = sinrCopy[map.at (i)];
      if (mcs <= MI_QPSK_MAX_ID) // QPSK
        {

          if (sinrLin > MI_map_qpsk_axis[MI_map_qpsk.size()-1])
            {
              MI = 1;
            }
          else 
            { 
              // since the values in MI_map_qpsk_axis are uniformly spaced, we have
              // index = ((sinrLin - value[0]) / (value[SIZE-1] - value[0])) * (SIZE-1)
              // the scaling coefficient is always the same, so we use a static const
              // to speed up the calculation
              static const double scalingCoeffQpsk = 
                (MI_map_qpsk.size() - 1) / (MI_map_qpsk_axis[MI_map_qpsk.size()-1] - MI_map_qpsk_axis[0]);
              double sinrIndexDouble = (sinrLin -  MI_map_qpsk_axis[0]) * scalingCoeffQpsk + 1;
              uint32_t sinrIndex = std::max(0.0, std::floor (sinrIndexDouble));
              NS_ASSERT_MSG (sinrIndex < MI_map_qpsk.size(), "MI map out of data");
              MI = MI_map_qpsk[sinrIndex];
            }
        }
      else
        {
          if (mcs > MI_QPSK_MAX_ID && mcs <= MI_16QAM_MAX_ID )	// 16-QAM
            {
              if (sinrLin > MI_map_16qam_axis[MI_map_16qam.size()-1])
                {
                  MI = 1;
                }
              else 
                {
                  // since the values in MI_map_16QAM_axis are uniformly spaced, we have
                  // index = ((sinrLin - value[0]) / (value[SIZE-1] - value[0])) * (SIZE-1)
                  // the scaling coefficient is always the same, so we use a static const
                  // to speed up the calculation
                  static const double scalingCoeff16qam = 
                    (MI_map_16qam.size() - 1) / (MI_map_16qam_axis[MI_map_16qam.size()-1] - MI_map_16qam_axis[0]);
                  double sinrIndexDouble = (sinrLin -  MI_map_16qam_axis[0]) * scalingCoeff16qam + 1;
                  uint32_t sinrIndex = std::max(0.0, std::floor (sinrIndexDouble));
                  NS_ASSERT_MSG (sinrIndex < MI_map_16qam.size(), "MI map out of data");
                  MI = MI_map_16qam[sinrIndex];
                }
            }
          else // 64-QAM
            {
              if (sinrLin > MI_map_64qam_axis[MI_map_64qam.size()-1])
                {
                  MI = 1;
                }
              else
                {
                  // since the values in MI_map_64QAM_axis are uniformly spaced, we have
                  // index = ((sinrLin - value[0]) / (value[SIZE-1] - value[0])) * (SIZE-1)
                  // the scaling coefficient is always the same, so we use a static const
                  // to speed up the calculation
                  static const double scalingCoeff64qam = 
                    (MI_map_64qam.size() - 1) / (MI_map_64qam_axis[MI_map_64qam.size()-1] - MI_map_64qam_axis[0]);
                  double sinrIndexDouble = (sinrLin -  MI_map_64qam_axis[0]) * scalingCoeff64qam + 1;
                  uint32_t sinrIndex = std::max(0.0, std::floor (sinrIndexDouble));
                  NS_ASSERT_MSG (sinrIndex < MI_map_64qam.size(), "MI map out of data");
                  MI = MI_map_64qam[sinrIndex];
                }
            }
        }
      NS_LOG_LOGIC (" RB " << map.at (i) << "Minimum SNR = " << 10 * std::log10 (sinrLin) << " dB, " << sinrLin << " V, MCS = " << (uint16_t)mcs << ", MI = " << MI);
      MIsum += MI;
    }
  MI = MIsum / map.size ();
  NS_LOG_LOGIC (" MI = " << MI);
  return MI;
}


double 
LteMiErrorModel::MappingMiBler (double mib, uint8_t ecrId, uint16_t cbSize)
{
  NS_LOG_FUNCTION (mib << (uint32_t) ecrId << (uint32_t) cbSize);
  double b = 0;
  double c = 0;

  NS_ASSERT_MSG (ecrId <= MI_64QAM_BLER_MAX_ID, "ECR out of range [0..37]: " << (uint16_t) ecrId);
  int cbIndex = 1;
  while ((cbIndex < 9)&&(cbMiSizeTable[cbIndex]<= cbSize))
    {
      cbIndex++;
    }
  cbIndex--;
  NS_LOG_LOGIC (" ECRid " << (uint16_t)ecrId << " ECR " << BlerCurvesEcrMap[ecrId] << " CB size " << cbSize << " CB size curve " << cbMiSizeTable[cbIndex]);

  b = bEcrTable[cbIndex][ecrId];
  if (b<0.0)
    {
      //take the lowest CB size including this CB for removing CB size
      //quatization errors
      int i = cbIndex;
      while ((i<9)&&(b<0))
        {
          b = bEcrTable[i++][ecrId];
        }
    }
  c = cEcrTable[cbIndex][ecrId];
  if (c<0.0)
    {
      //take the lowest CB size including this CB for removing CB size
      //quatization errors
      int i = cbIndex;
      while ((i<9)&&(c<0))
        {
          c = cEcrTable[i++][ecrId];
        }
    }
  // see IEEE802.16m EMD formula 55 of section 4.3.2.1
  double bler = 0.5*( 1 - erf((mib-b)/(sqrt(2)*c)) );
  NS_LOG_LOGIC ("MIB: " << mib << " BLER:" << bler << " b:" << b << " c:" << c);
  return bler;
}



double
LteMiErrorModel::GetPcfichPdcchError (const SpectrumValue& sinr)
{
  NS_LOG_FUNCTION (sinr);
  if (!errorDataLoaded)
      LoadErrorData();

  double MI;
  double MIsum = 0.0;
  SpectrumValue sinrCopy = sinr;
  Values::iterator sinrIt = sinrCopy.ValuesBegin ();
  uint16_t rb = 0;
  NS_ASSERT (sinrIt!=sinrCopy.ValuesEnd ());
  while (sinrIt!=sinrCopy.ValuesEnd ())
    {
      double sinrLin = *sinrIt;
      if (sinrLin > MI_map_qpsk_axis[MI_map_qpsk.size()-1])
        {
          MI = 1;
        }
      else 
        { 
          // since the values in MI_map_qpsk_axis are uniformly spaced, we have
          // index = ((sinrLin - value[0]) / (value[SIZE-1] - value[0])) * (SIZE-1)
              // the scaling coefficient is always the same, so we use a static const
              // to speed up the calculation
          static const double scalingCoeffQpsk = 
            (MI_map_qpsk.size() - 1) / (MI_map_qpsk_axis[MI_map_qpsk.size()-1] - MI_map_qpsk_axis[0]);
          double sinrIndexDouble = (sinrLin -  MI_map_qpsk_axis[0]) * scalingCoeffQpsk + 1;
          uint32_t sinrIndex = std::max(0.0, std::floor (sinrIndexDouble));
          NS_ASSERT_MSG (sinrIndex < MI_map_qpsk.size(), "MI map out of data");
          MI = MI_map_qpsk[sinrIndex];
        }
      MIsum += MI;
      sinrIt++;
      rb++;
    }
  MI = MIsum / rb;
  // return to the effective SINR value
  int j = 0;
  double esinr = 0.0;
  while ((j<MI_map_qpsk.size())&&(MI_map_qpsk[j] < MI))
    {
      j++;
    }
  if (MI > MI_map_qpsk[MI_map_qpsk.size()-1])
    {
      esinr = MI_map_qpsk_axis[MI_map_qpsk.size()-1];
    }
  else 
    {
      NS_ASSERT_MSG (j<MI_map_qpsk.size(), "MI map out of data");
      // take the closest value (when possible)  
      if (j>0)
        {
          if ((MI_map_qpsk[j]-MI)<(MI-MI_map_qpsk[j-1]))
            {
              esinr = MI_map_qpsk_axis[j];
            }
          else
            {
              esinr = MI_map_qpsk_axis[j-1];
            }
        }
      else
        {
          esinr = MI_map_qpsk_axis[0];
        }
    }

  double esirnDb = 10*log10 (esinr); 
//   NS_LOG_DEBUG ("Effective SINR " << esirnDb << " max " << 10*log10 (MI_map_qpsk [MI_map_qpsk.size()-1]));
  uint16_t i = 0;
  double errorRate = 0.0;
  while ((i<PdcchPcfichBlerCurveYaxis.size())&&(PdcchPcfichBlerCurveXaxis[i] < esirnDb))
    {
      i++;
    }
  if (esirnDb > PdcchPcfichBlerCurveXaxis[PdcchPcfichBlerCurveYaxis.size()-1])
    {
      errorRate = 0.0;
    }
  else 
    {
      NS_ASSERT_MSG (i<PdcchPcfichBlerCurveYaxis.size(), "PDCCH-PCFICH map out of data");
      errorRate = PdcchPcfichBlerCurveYaxis[i];
    }  
  
  return (errorRate);
}




TbStats_t
LteMiErrorModel::GetTbDecodificationStats (const SpectrumValue& sinr, const std::vector<int>& map, uint16_t size, uint8_t mcs, HarqProcessInfoList_t miHistory)
{
  NS_LOG_FUNCTION (sinr << &map << (uint32_t) size << (uint32_t) mcs);

  double tbMi = Mib(sinr, map, mcs);
  double MI = 0.0;
  double Reff = 0.0;
  NS_ASSERT (mcs < 29);
  if (miHistory.size ()>0)
    {
      // evaluate R_eff and MI_eff
      uint16_t codeBitsSum = 0;
      double miSum = 0.0;
      for (uint16_t i = 0; i < miHistory.size (); i++)
        {
          NS_LOG_DEBUG (" Sum MI " << miHistory.at (i).m_mi << " Ci " << miHistory.at (i).m_codeBits);
          codeBitsSum += miHistory.at (i).m_codeBits;
          miSum += (miHistory.at (i).m_mi*miHistory.at (i).m_codeBits);
        }
      codeBitsSum += (((double)size*8.0) / McsEcrTable [mcs]);
      miSum += (tbMi*(((double)size*8.0) / McsEcrTable [mcs]));
      Reff = miHistory.at (0).m_infoBits / (double)codeBitsSum; // information bits are the size of the first TB
      MI = miSum / (double)codeBitsSum;      
    }
  else
    {
      MI = tbMi;
    }
  NS_LOG_DEBUG (" MI " << MI << " Reff " << Reff << " HARQ " << miHistory.size ());
  // estimate CB size (according to sec 5.1.2 of TS 36.212)
  uint16_t Z = 6144; // max size of a codeblock (including CRC)
  uint32_t B = size * 8;
//   B = 1234;
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
  // first segmentation: K+ = minimum K in table such that C * K >= B1
//   uint i = 0;
//   while (B1 > cbSizeTable[i] * C)
//     {
// //       NS_LOG_INFO (" K+ " << cbSizeTable[i] << " means " << cbSizeTable[i] * C);
//       i++;
//     }
//   uint16_t KplusId = i;
//   Kplus = cbSizeTable[i];

  // implement a modified binary search
  int min = 0;
  int max = 187;
  int mid = 0;
  do
    {
      mid = (min+max) / 2;
      if (B1 > cbSizeTable[mid]*C)
        {
          if (B1 < cbSizeTable[mid+1]*C)
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
          if (B1 > cbSizeTable[mid-1]*C)
            {
              break;
            }
          else
            {
              max = mid - 1;
            }
        }
  } while ((cbSizeTable[mid]*C != B1) && (min < max));
  // adjust binary search to the largest integer value of K containing B1
  if (B1 > cbSizeTable[mid]*C)
    {
      mid ++;
    }

  uint16_t KplusId = mid;
  Kplus = cbSizeTable[mid];


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
      Kminus = cbSizeTable[ KplusId > 1 ? KplusId - 1 : 0];
      deltaK = Kplus - Kminus;
      Cminus = floor ((((double) C * Kplus) - (double)B1) / (double)deltaK);
      Cplus = C - Cminus;
    }
  NS_LOG_INFO ("--------------------LteMiErrorModel: TB size of " << B << " needs of " << B1 << " bits reparted in " << C << " CBs as "<< Cplus << " block(s) of " << Kplus << " and " << Cminus << " of " << Kminus);

  double errorRate = 1.0;
  uint8_t ecrId = 0;
  if (miHistory.size ()==0)
    {
      // first tx -> get ECR from MCS
      ecrId = McsEcrBlerTableMapping[mcs];
      NS_LOG_DEBUG ("NO HARQ MCS " << (uint16_t)mcs << " ECR id " << (uint16_t)ecrId);
    }
  else
    {
      NS_LOG_DEBUG ("HARQ block no. " << miHistory.size ());
      // harq retx -> get closest ECR to Reff from available ones
      if (mcs <= MI_QPSK_MAX_ID)
        {
          // Modulation order 2
          uint8_t i = MI_QPSK_MAX_ID;
          while ((BlerCurvesEcrMap[i]>Reff)&&(i>0))
            {
              i--;
            }
          ecrId = i;
        }
      else if (mcs <= MI_16QAM_MAX_ID)
        {
          // Modulation order 4
          uint8_t i = MI_16QAM_MAX_ID;
          while ((BlerCurvesEcrMap[i]>Reff)&&(i>MI_QPSK_MAX_ID + 1))
            {
              i--;
            }
          ecrId = i;
        }
      else
        {
          // Modulation order 6
          uint8_t i = MI_64QAM_MAX_ID;
          while ((BlerCurvesEcrMap[i]>Reff)&&(i>MI_16QAM_MAX_ID + 1))
            {
              i--;
            }
          ecrId = i;
        }
      NS_LOG_DEBUG ("HARQ ECR " << (uint16_t)ecrId);
    }

  if (C!=1)
    {
      double cbler = MappingMiBler (MI, ecrId, Kplus);
      errorRate *= pow (1.0 - cbler, Cplus);
      cbler = MappingMiBler (MI, ecrId, Kminus);
      errorRate *= pow (1.0 - cbler, Cminus);
      errorRate = 1.0 - errorRate;
    }
  else
    {
      errorRate = MappingMiBler (MI, ecrId, Kplus);
    }

  NS_LOG_LOGIC (" Error rate " << errorRate);
  TbStats_t ret;
  ret.tbler = errorRate;
  ret.mi = tbMi;
  return ret;
}


  

} // namespace ns3

