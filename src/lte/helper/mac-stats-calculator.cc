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
 * Modified by: Danilo Abrignani <danilo.abrignani@unibo.it> (Carrier Aggregation - GSoC 2015)
 *              Biljana Bojovic <biljana.bojovic@cttc.es> (Carrier Aggregation) 
 */

#include "mac-stats-calculator.h"
#include "ns3/string.h"
#include <ns3/simulator.h>
#include <ns3/log.h>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("MacStatsCalculator");

NS_OBJECT_ENSURE_REGISTERED (MacStatsCalculator);

MacStatsCalculator::MacStatsCalculator ()
  : m_dlFirstWrite (true),
    m_ulFirstWrite (true)
{
  NS_LOG_FUNCTION (this);

}

MacStatsCalculator::~MacStatsCalculator ()
{
  NS_LOG_FUNCTION (this);
  outFileDl.close();
  outFileUl.close();
}

TypeId
MacStatsCalculator::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::MacStatsCalculator")
    .SetParent<LteStatsCalculator> ()
    .SetGroupName("Lte")
    .AddConstructor<MacStatsCalculator> ()
    .AddAttribute ("DlOutputFilename",
                   "Name of the file where the downlink results will be saved.",
                   StringValue ("DlMacStats.txt"),
                   MakeStringAccessor (&MacStatsCalculator::SetDlOutputFilename),
                   MakeStringChecker ())
    .AddAttribute ("UlOutputFilename",
                   "Name of the file where the uplink results will be saved.",
                   StringValue ("UlMacStats.txt"),
                   MakeStringAccessor (&MacStatsCalculator::SetUlOutputFilename),
                   MakeStringChecker ())
  ;
  return tid;
}

void
MacStatsCalculator::SetUlOutputFilename (std::string outputFilename)
{
  LteStatsCalculator::SetUlOutputFilename (outputFilename);

  if(outFileUl.is_open())
      outFileUl.close();

  outFileUl.open (GetUlOutputFilename ().c_str ());
  if (!outFileUl.is_open ())
  {
      NS_LOG_ERROR ("Can't open file " << GetUlOutputFilename ().c_str ());
      return;
  }

  m_ulFirstWrite = true;
}

std::string
MacStatsCalculator::GetUlOutputFilename (void)
{
  return LteStatsCalculator::GetUlOutputFilename ();
}

void
MacStatsCalculator::SetDlOutputFilename (std::string outputFilename)
{
  LteStatsCalculator::SetDlOutputFilename (outputFilename);

  if(outFileDl.is_open())
      outFileDl.close();

  outFileDl.open (GetDlOutputFilename ().c_str ());
  if (!outFileDl.is_open ())
  {
      NS_LOG_ERROR ("Can't open file " << GetDlOutputFilename ().c_str ());
      return;
  }

  m_dlFirstWrite = true;
}

std::string
MacStatsCalculator::GetDlOutputFilename (void)
{
  return LteStatsCalculator::GetDlOutputFilename ();
}

void
MacStatsCalculator::DlScheduling (uint16_t cellId, uint64_t imsi, DlSchedulingCallbackInfo dlSchedulingCallbackInfo)
{
  NS_LOG_FUNCTION (this << cellId << imsi << dlSchedulingCallbackInfo.frameNo << dlSchedulingCallbackInfo.subframeNo <<
		  dlSchedulingCallbackInfo.rnti << (uint32_t) dlSchedulingCallbackInfo.mcsTb1 << dlSchedulingCallbackInfo.sizeTb1 << (uint32_t) dlSchedulingCallbackInfo.mcsTb2 << dlSchedulingCallbackInfo.sizeTb2);
  NS_LOG_INFO ("Write DL Mac Stats in " << GetDlOutputFilename ().c_str ());

  if ( m_dlFirstWrite == true )
  {
    m_dlFirstWrite = false;
    outFileDl << "% time\tcellId\tIMSI\tframe\tsframe\tRNTI\tmcsTb1\tsizeTb1\tmcsTb2\tsizeTb2\tccId";
    outFileDl << "\n"; //std::endl; //endl forces flush and blocks main thread, which severely impacts performance
  }

  outFileDl << Simulator::Now ().GetNanoSeconds () / (double) 1e9 << "\t";
  outFileDl << (uint32_t) cellId << "\t";
  outFileDl << imsi << "\t";
  outFileDl << dlSchedulingCallbackInfo.frameNo << "\t";
  outFileDl << dlSchedulingCallbackInfo.subframeNo << "\t";
  outFileDl << dlSchedulingCallbackInfo.rnti << "\t";
  outFileDl << (uint32_t) dlSchedulingCallbackInfo.mcsTb1 << "\t";
  outFileDl << dlSchedulingCallbackInfo.sizeTb1 << "\t";
  outFileDl << (uint32_t) dlSchedulingCallbackInfo.mcsTb2 << "\t";
  outFileDl << dlSchedulingCallbackInfo.sizeTb2 << "\t";
  outFileDl << (uint32_t) dlSchedulingCallbackInfo.componentCarrierId << "\n"; //std::endl; //endl forces flush and blocks main thread, which severely impacts performance
}

void
MacStatsCalculator::UlScheduling (uint16_t cellId, uint64_t imsi, uint32_t frameNo,
                                  uint32_t subframeNo, uint16_t rnti,uint8_t mcsTb, uint16_t size, uint8_t componentCarrierId)
{
  NS_LOG_FUNCTION (this << cellId << imsi << frameNo << subframeNo << rnti << (uint32_t) mcsTb << size);
  NS_LOG_INFO ("Write UL Mac Stats in " << GetUlOutputFilename ().c_str ());

  if ( m_ulFirstWrite == true )
  {
      m_ulFirstWrite = false;
      outFileUl << "% time\tcellId\tIMSI\tframe\tsframe\tRNTI\tmcs\tsize\tccId";
      outFileUl << "\n"; //std::endl; //endl forces flush and blocks main thread, which severely impacts performance
  }

  outFileUl << Simulator::Now ().GetNanoSeconds () / (double) 1e9 << "\t";
  outFileUl << (uint32_t) cellId << "\t";
  outFileUl << imsi << "\t";
  outFileUl << frameNo << "\t";
  outFileUl << subframeNo << "\t";
  outFileUl << rnti << "\t";
  outFileUl << (uint32_t) mcsTb << "\t";
  outFileUl << size << "\t";
  outFileUl << (uint32_t) componentCarrierId << "\n"; //std::endl; //endl forces flush and blocks main thread, which severely impacts performance
}

void
MacStatsCalculator::DlSchedulingCallback (Ptr<MacStatsCalculator> macStats, std::string path, DlSchedulingCallbackInfo dlSchedulingCallbackInfo)
{
  NS_LOG_FUNCTION (macStats << path);
  uint64_t imsi = 0;
  std::ostringstream pathAndRnti;
  std::string pathEnb  = path.substr (0, path.find ("/ComponentCarrierMap"));
  pathAndRnti << pathEnb << "/LteEnbRrc/UeMap/" << dlSchedulingCallbackInfo.rnti;
  if (macStats->ExistsImsiPath (pathAndRnti.str ()) == true)
    {
      imsi = macStats->GetImsiPath (pathAndRnti.str ());
    }
  else
    {
      imsi = FindImsiFromEnbRlcPath (pathAndRnti.str ());
      macStats->SetImsiPath (pathAndRnti.str (), imsi);
    }
  uint16_t cellId = 0;
  if (macStats->ExistsCellIdPath (pathAndRnti.str ()) == true)
    {
      cellId = macStats->GetCellIdPath (pathAndRnti.str ());
    }
  else
    {
      cellId = FindCellIdFromEnbRlcPath (pathAndRnti.str ());
      macStats->SetCellIdPath (pathAndRnti.str (), cellId);
    }

  macStats->DlScheduling (cellId, imsi, dlSchedulingCallbackInfo);
}

void
MacStatsCalculator::UlSchedulingCallback (Ptr<MacStatsCalculator> macStats, std::string path,
                      uint32_t frameNo, uint32_t subframeNo, uint16_t rnti,
                      uint8_t mcs, uint16_t size, uint8_t componentCarrierId)
{
  NS_LOG_FUNCTION (macStats << path);

  uint64_t imsi = 0;
  std::ostringstream pathAndRnti;
  std::string pathEnb  = path.substr (0, path.find ("/ComponentCarrierMap"));
  pathAndRnti << pathEnb << "/LteEnbRrc/UeMap/" << rnti;
  if (macStats->ExistsImsiPath (pathAndRnti.str ()) == true)
    {
      imsi = macStats->GetImsiPath (pathAndRnti.str ());
    }
  else
    {
      imsi = FindImsiFromEnbRlcPath (pathAndRnti.str ());
      macStats->SetImsiPath (pathAndRnti.str (), imsi);
    }
  uint16_t cellId = 0;
  if (macStats->ExistsCellIdPath (pathAndRnti.str ()) == true)
    {
      cellId = macStats->GetCellIdPath (pathAndRnti.str ());
    }
  else
    {
      cellId = FindCellIdFromEnbRlcPath (pathAndRnti.str ());
      macStats->SetCellIdPath (pathAndRnti.str (), cellId);
    }

  macStats->UlScheduling (cellId, imsi, frameNo, subframeNo, rnti, mcs, size, componentCarrierId);
}


} // namespace ns3
