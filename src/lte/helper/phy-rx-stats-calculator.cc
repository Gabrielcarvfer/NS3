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
 * modified by: Marco Miozzo <mmiozzo@cttc.es>
 *        Convert MacStatsCalculator in PhyRxStatsCalculator
 */

#include "phy-rx-stats-calculator.h"
#include "ns3/string.h"
#include <ns3/simulator.h>
#include <ns3/log.h>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("PhyRxStatsCalculator");

NS_OBJECT_ENSURE_REGISTERED (PhyRxStatsCalculator);

PhyRxStatsCalculator::PhyRxStatsCalculator ()
  : m_dlRxFirstWrite (true),
    m_ulRxFirstWrite (true)
{
  NS_LOG_FUNCTION (this);

}

PhyRxStatsCalculator::~PhyRxStatsCalculator ()
{
  NS_LOG_FUNCTION (this);
  outFileDlRx.close();
  outFileUlRx.close();
}

TypeId
PhyRxStatsCalculator::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::PhyRxStatsCalculator")
    .SetParent<LteStatsCalculator> ()
    .SetGroupName("Lte")
    .AddConstructor<PhyRxStatsCalculator> ()
    .AddAttribute ("DlRxOutputFilename",
                   "Name of the file where the downlink results will be saved.",
                   StringValue ("DlRxPhyStats.txt"),
                   MakeStringAccessor (&PhyRxStatsCalculator::SetDlRxOutputFilename),
                   MakeStringChecker ())
    .AddAttribute ("UlRxOutputFilename",
                   "Name of the file where the uplink results will be saved.",
                   StringValue ("UlRxPhyStats.txt"),
                   MakeStringAccessor (&PhyRxStatsCalculator::SetUlRxOutputFilename),
                   MakeStringChecker ())
  ;
  return tid;
}

void
PhyRxStatsCalculator::SetUlRxOutputFilename (std::string outputFilename)
{
  LteStatsCalculator::SetUlOutputFilename (outputFilename);

  if(outFileUlRx.is_open())
      outFileUlRx.close();

  outFileUlRx.open (GetUlOutputFilename ().c_str ());
  if (!outFileUlRx.is_open ())
  {
      NS_LOG_ERROR ("Can't open file " << GetUlOutputFilename ().c_str ());
      return;
  }

  m_ulRxFirstWrite = true;
}

std::string
PhyRxStatsCalculator::GetUlRxOutputFilename (void)
{
  return LteStatsCalculator::GetUlOutputFilename ();
}

void
PhyRxStatsCalculator::SetDlRxOutputFilename (std::string outputFilename)
{
  LteStatsCalculator::SetDlOutputFilename (outputFilename);

  if(outFileDlRx.is_open())
      outFileDlRx.close();

  outFileDlRx.open (GetDlOutputFilename ().c_str ());
  if (!outFileDlRx.is_open ())
  {
      NS_LOG_ERROR ("Can't open file " << GetDlOutputFilename ().c_str ());
      return;
  }

  m_dlRxFirstWrite = true;
}

std::string
PhyRxStatsCalculator::GetDlRxOutputFilename (void)
{
  return LteStatsCalculator::GetDlOutputFilename ();
}

void
PhyRxStatsCalculator::DlPhyReception (PhyReceptionStatParameters params)
{
  NS_LOG_FUNCTION (this << params.m_cellId << params.m_imsi << params.m_timestamp << params.m_rnti << params.m_layer << params.m_mcs << params.m_size << params.m_rv << params.m_ndi << params.m_correctness);
  NS_LOG_INFO ("Write DL Rx Phy Stats in " << GetDlRxOutputFilename ().c_str ());

  if ( m_dlRxFirstWrite == true )
  {
    m_dlRxFirstWrite = false;
    outFileDlRx << "% time\tcellId\tIMSI\tRNTI\ttxMode\tlayer\tmcs\tsize\trv\tndi\tcorrect\tccId";
    outFileDlRx << "\n"; //std::endl; //endl forces flush and blocks main thread, which severely impacts performance
  }

//   outFileDlRx << Simulator::Now ().GetNanoSeconds () / (double) 1e9 << "\t";
  outFileDlRx << params.m_timestamp << "\t";
  outFileDlRx << (uint32_t) params.m_cellId << "\t";
  outFileDlRx << params.m_imsi << "\t";
  outFileDlRx << params.m_rnti << "\t";
  outFileDlRx << (uint32_t) params.m_txMode << "\t";
  outFileDlRx << (uint32_t) params.m_layer << "\t";
  outFileDlRx << (uint32_t) params.m_mcs << "\t";
  outFileDlRx << params.m_size << "\t";
  outFileDlRx << (uint32_t) params.m_rv << "\t";
  outFileDlRx << (uint32_t) params.m_ndi << "\t";
  outFileDlRx << (uint32_t) params.m_correctness << "\t";
  outFileDlRx << (uint32_t) params.m_ccId << "\n"; //std::endl; //endl forces flush and blocks main thread, which severely impacts performance
}

void
PhyRxStatsCalculator::UlPhyReception (PhyReceptionStatParameters params)
{
  NS_LOG_FUNCTION (this << params.m_cellId << params.m_imsi << params.m_timestamp << params.m_rnti << params.m_layer << params.m_mcs << params.m_size << params.m_rv << params.m_ndi << params.m_correctness);
  NS_LOG_INFO ("Write UL Rx Phy Stats in " << GetUlRxOutputFilename ().c_str ());

  if ( m_ulRxFirstWrite == true )
  {
    m_ulRxFirstWrite = false;
    outFileUlRx << "% time\tcellId\tIMSI\tRNTI\tlayer\tmcs\tsize\trv\tndi\tcorrect\tccId";
    outFileUlRx << "\n"; //std::endl; //endl forces flush and blocks main thread, which severely impacts performance
  }

//   outFileUlRx << Simulator::Now ().GetNanoSeconds () / (double) 1e9 << "\t";
  outFileUlRx << params.m_timestamp << "\t";
  outFileUlRx << (uint32_t) params.m_cellId << "\t";
  outFileUlRx << params.m_imsi << "\t";
  outFileUlRx << params.m_rnti << "\t";
  outFileUlRx << (uint32_t) params.m_layer << "\t";
  outFileUlRx << (uint32_t) params.m_mcs << "\t";
  outFileUlRx << params.m_size << "\t";
  outFileUlRx << (uint32_t) params.m_rv << "\t";
  outFileUlRx << (uint32_t) params.m_ndi << "\t";
  outFileUlRx << (uint32_t) params.m_correctness << "\t";
  outFileUlRx << (uint32_t) params.m_ccId <<"\n"; //std::endl; //endl forces flush and blocks main thread, which severely impacts performance
}

void
PhyRxStatsCalculator::DlPhyReceptionCallback (Ptr<PhyRxStatsCalculator> phyRxStats,
                      std::string path, PhyReceptionStatParameters params)
{
  NS_LOG_FUNCTION (phyRxStats << path);
  uint64_t imsi = 0;
  std::ostringstream pathAndRnti;
  pathAndRnti << path << "/" << params.m_rnti;
  std::string pathUePhy  = path.substr (0, path.find ("/ComponentCarrierMapUe"));
  if (phyRxStats->ExistsImsiPath (pathAndRnti.str ()) == true)
    {
      imsi = phyRxStats->GetImsiPath (pathAndRnti.str ());
    }
  else
    {
      imsi = FindImsiFromLteNetDevice (pathUePhy);
      phyRxStats->SetImsiPath (pathAndRnti.str (), imsi);
    }

  params.m_imsi = imsi;
  phyRxStats->DlPhyReception (params);
}

void
PhyRxStatsCalculator::UlPhyReceptionCallback (Ptr<PhyRxStatsCalculator> phyRxStats,
                      std::string path, PhyReceptionStatParameters params)
{
  NS_LOG_FUNCTION (phyRxStats << path);
  uint64_t imsi = 0;
  std::ostringstream pathAndRnti;
  std::string pathEnb  = path.substr (0, path.find ("/ComponentCarrierMap"));
  pathAndRnti << pathEnb << "/LteEnbRrc/UeMap/" << params.m_rnti;
  if (phyRxStats->ExistsImsiPath (pathAndRnti.str ()) == true)
    {
      imsi = phyRxStats->GetImsiPath (pathAndRnti.str ());
    }
  else
    {
      imsi = FindImsiFromEnbRlcPath (pathAndRnti.str ());
      phyRxStats->SetImsiPath (pathAndRnti.str (), imsi);
    }

  params.m_imsi = imsi;
  phyRxStats->UlPhyReception (params);
}

} // namespace ns3
