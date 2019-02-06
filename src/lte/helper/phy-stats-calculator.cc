/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011 Centre Tecnologic de Telecomunicacions de Catalunya (CTTC)
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
 * Author: Jaume Nin <jnin@cttc.es>
 *         Danilo Abrignani <danilo.abrignani@unibo.it> (Modification due to new Architecture - Carrier Aggregation - GSoC 2015)
 */

#include "phy-stats-calculator.h"
#include "ns3/string.h"
#include <ns3/simulator.h>
#include <ns3/log.h>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("PhyStatsCalculator");

NS_OBJECT_ENSURE_REGISTERED (PhyStatsCalculator);

PhyStatsCalculator::PhyStatsCalculator ()
  :  m_RsrpSinrFirstWrite (true),
    m_UeSinrFirstWrite (true),
    m_InterferenceFirstWrite (true)
{
  NS_LOG_FUNCTION (this);

}

PhyStatsCalculator::~PhyStatsCalculator ()
{
  NS_LOG_FUNCTION (this);
  outFileUeSinr.close();
  outFileRsrpSinr.close();
  outFileInterference.close();
}

TypeId
PhyStatsCalculator::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PhyStatsCalculator")
    .SetParent<LteStatsCalculator> ()
    .SetGroupName("Lte")
    .AddConstructor<PhyStatsCalculator> ()
    .AddAttribute ("DlRsrpSinrFilename",
                   "Name of the file where the RSRP/SINR statistics will be saved.",
                   StringValue ("DlRsrpSinrStats.txt"),
                   MakeStringAccessor (&PhyStatsCalculator::SetCurrentCellRsrpSinrFilename),
                   MakeStringChecker ())
    .AddAttribute ("UlSinrFilename",
                   "Name of the file where the UE SINR statistics will be saved.",
                   StringValue ("UlSinrStats.txt"),
                   MakeStringAccessor (&PhyStatsCalculator::SetUeSinrFilename),
                   MakeStringChecker ())
    .AddAttribute ("UlInterferenceFilename",
                   "Name of the file where the interference statistics will be saved.",
                   StringValue ("UlInterferenceStats.txt"),
                   MakeStringAccessor (&PhyStatsCalculator::SetInterferenceFilename),
                   MakeStringChecker ())
  ;
  return tid;
}

void
PhyStatsCalculator::SetCurrentCellRsrpSinrFilename (std::string filename)
{
  m_RsrpSinrFilename = filename;

  if(outFileRsrpSinr.is_open())
      outFileRsrpSinr.close();

  outFileRsrpSinr.open (GetCurrentCellRsrpSinrFilename ().c_str ());
  if (!outFileRsrpSinr.is_open ())
  {
      NS_LOG_ERROR ("Can't open file " << GetCurrentCellRsrpSinrFilename ().c_str ());
      return;
  }

  m_RsrpSinrFirstWrite = true;
}

std::string
PhyStatsCalculator::GetCurrentCellRsrpSinrFilename (void)
{
  return m_RsrpSinrFilename;
}

void
PhyStatsCalculator::SetUeSinrFilename (std::string filename)
{
  m_ueSinrFilename = filename;

  if(outFileUeSinr.is_open())
      outFileUeSinr.close();

  outFileUeSinr.open (GetUeSinrFilename ().c_str ());
  if (!outFileUeSinr.is_open ())
  {
      NS_LOG_ERROR ("Can't open file " << GetUeSinrFilename ().c_str ());
      return;
  }

  m_UeSinrFirstWrite = true;
}

std::string
PhyStatsCalculator::GetUeSinrFilename (void)
{
  return m_ueSinrFilename;
}

void
PhyStatsCalculator::SetInterferenceFilename (std::string filename)
{
  m_interferenceFilename = filename;

  if(outFileInterference.is_open())
      outFileInterference.close();

  outFileInterference.open (GetInterferenceFilename ().c_str ());
  if (!outFileInterference.is_open ())
  {
      NS_LOG_ERROR ("Can't open file " << GetInterferenceFilename ().c_str ());
      return;
  }

  m_InterferenceFirstWrite = true;
}

std::string
PhyStatsCalculator::GetInterferenceFilename (void)
{
  return m_interferenceFilename;
}



void
PhyStatsCalculator::ReportCurrentCellRsrpSinr (uint16_t cellId, uint64_t imsi, uint16_t rnti,
                                               double rsrp, double sinr, uint8_t componentCarrierId)
{
  NS_LOG_FUNCTION (this << cellId <<  imsi << rnti  << rsrp << sinr);
  NS_LOG_INFO ("Write RSRP/SINR Phy Stats in " << GetCurrentCellRsrpSinrFilename ().c_str ());

  if ( m_RsrpSinrFirstWrite == true )
  {
    m_RsrpSinrFirstWrite = false;
    outFileRsrpSinr << "% time\tcellId\tIMSI\tRNTI\trsrp\tsinr\tComponentCarrierId";
    outFileRsrpSinr << "\n"; //std::endl; //endl forces flush and blocks main thread, which is stupid
  }
  outFileRsrpSinr << Simulator::Now ().GetNanoSeconds () / (double) 1e9 << "\t";
  outFileRsrpSinr << cellId << "\t";
  outFileRsrpSinr << imsi << "\t";
  outFileRsrpSinr << rnti << "\t";
  outFileRsrpSinr << rsrp << "\t";
  outFileRsrpSinr << sinr << "\t";
  outFileRsrpSinr << (uint32_t)componentCarrierId << "\n"; //std::endl; //endl forces flush and blocks main thread, which is stupid
}

void
PhyStatsCalculator::ReportUeSinr (uint16_t cellId, uint64_t imsi, uint16_t rnti,  double sinrLinear, uint8_t componentCarrierId)
{
  NS_LOG_FUNCTION (this << cellId <<  imsi << rnti  << sinrLinear);
  NS_LOG_INFO ("Write SINR Linear Phy Stats in " << GetUeSinrFilename ().c_str ());

  if ( m_UeSinrFirstWrite == true )
  {
    m_UeSinrFirstWrite = false;
    outFileUeSinr << "% time\tcellId\tIMSI\tRNTI\tsinrLinear\tcomponentCarrierId";
    outFileUeSinr << "\n"; //std::endl; //endl forces flush and blocks main thread, which is stupid
  }
  outFileUeSinr << Simulator::Now ().GetNanoSeconds () / (double) 1e9 << "\t";
  outFileUeSinr << cellId << "\t";
  outFileUeSinr << imsi << "\t";
  outFileUeSinr << rnti << "\t";
  outFileUeSinr << sinrLinear << "\t";
  outFileUeSinr << (uint32_t)componentCarrierId << "\n"; //std::endl; //endl forces flush and blocks main thread, which is stupid
}

void
PhyStatsCalculator::ReportInterference (uint16_t cellId, Ptr<SpectrumValue> interference)
{
  NS_LOG_FUNCTION (this << cellId <<  interference);
  NS_LOG_INFO ("Write Interference Phy Stats in " << GetInterferenceFilename ().c_str ());

  if ( m_InterferenceFirstWrite == true )
  {
    m_InterferenceFirstWrite = false;
    outFileInterference << "% time\tcellId\tInterference";
    outFileInterference << "\n"; //std::endl; //endl forces flush and blocks main thread, which is stupid
  }

  outFileInterference << Simulator::Now ().GetNanoSeconds () / (double) 1e9 << "\t";
  outFileInterference << cellId << "\t";
  outFileInterference << *interference;
}


void
PhyStatsCalculator::ReportCurrentCellRsrpSinrCallback (Ptr<PhyStatsCalculator> phyStats,
                      std::string path, uint16_t cellId, uint16_t rnti,
                      double rsrp, double sinr, uint8_t componentCarrierId)
{
  NS_LOG_FUNCTION (phyStats << path);
  uint64_t imsi = 0;
  std::string pathUePhy  = path.substr (0, path.find ("/ComponentCarrierMapUe"));
  if (phyStats->ExistsImsiPath (pathUePhy) == true)
    {
      imsi = phyStats->GetImsiPath (pathUePhy);
    }
  else
    {
      imsi = FindImsiFromLteNetDevice (pathUePhy);
      phyStats->SetImsiPath (pathUePhy, imsi);
    }

  phyStats->ReportCurrentCellRsrpSinr (cellId, imsi, rnti, rsrp, sinr, componentCarrierId);
}

void
PhyStatsCalculator::ReportUeSinr (Ptr<PhyStatsCalculator> phyStats, std::string path,
                                  uint16_t cellId, uint16_t rnti, double sinrLinear, uint8_t componentCarrierId)
{
  NS_LOG_FUNCTION (phyStats << path);

  uint64_t imsi = 0;
  std::ostringstream pathAndRnti;
  pathAndRnti << path << "/" << rnti;
  std::string pathEnbMac  = path.substr (0, path.find ("/ComponentCarrierMap"));
  pathEnbMac += "/LteEnbMac/DlScheduling";
  if (phyStats->ExistsImsiPath (pathAndRnti.str ()) == true)
    {
      imsi = phyStats->GetImsiPath (pathAndRnti.str ());
    }
  else
    {
      imsi = FindImsiFromEnbMac (pathEnbMac, rnti);
      phyStats->SetImsiPath (pathAndRnti.str (), imsi);
    }

  phyStats->ReportUeSinr (cellId, imsi, rnti, sinrLinear, componentCarrierId);
}

void
PhyStatsCalculator::ReportInterference (Ptr<PhyStatsCalculator> phyStats, std::string path,
                    uint16_t cellId, Ptr<SpectrumValue> interference)
{
  NS_LOG_FUNCTION (phyStats << path);
  phyStats->ReportInterference (cellId, interference);
}


} // namespace ns3
