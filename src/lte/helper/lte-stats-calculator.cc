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
 */

#include "lte-stats-calculator.h"

#include "../../core/model/log.h"
#include "../../core/model/config.h"
#include "../model/lte-enb-rrc.h"
#include "../model/lte-ue-rrc.h"
#include "../model/lte-enb-net-device.h"
#include "../model/lte-ue-net-device.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("LteStatsCalculator");

NS_OBJECT_ENSURE_REGISTERED (LteStatsCalculator);

LteStatsCalculator::LteStatsCalculator ()
  : m_dlOutputFilename (""),
    m_ulOutputFilename ("")
{
  // Nothing to do here

}

LteStatsCalculator::~LteStatsCalculator ()
{
  // Nothing to do here
}


TypeId
LteStatsCalculator::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::LteStatsCalculator")
    .SetParent<Object> ()
    .SetGroupName("Lte")
    .AddConstructor<LteStatsCalculator> ()
  ;
  return tid;
}


void
LteStatsCalculator::SetUlOutputFilename (stdfwd::string outputFilename)
{
  m_ulOutputFilename = outputFilename;
}

stdfwd::string
LteStatsCalculator::GetUlOutputFilename (void)
{
  return m_ulOutputFilename;
}

void
LteStatsCalculator::SetDlOutputFilename (stdfwd::string outputFilename)
{
  m_dlOutputFilename = outputFilename;
}

stdfwd::string
LteStatsCalculator::GetDlOutputFilename (void)
{
  return m_dlOutputFilename;
}


bool
LteStatsCalculator::ExistsImsiPath (stdfwd::string path)
{
  if (m_pathImsiMap.find (path) == m_pathImsiMap.end () )
    {
      return false;
    }
  else
    {
      return true;
    }
}

void
LteStatsCalculator::SetImsiPath (stdfwd::string path, uint64_t imsi)
{
  NS_LOG_FUNCTION (this << path << imsi);
  m_pathImsiMap[path] = imsi;
}

uint64_t
LteStatsCalculator::GetImsiPath (stdfwd::string path)
{
  return m_pathImsiMap.find (path)->second;
}

bool
LteStatsCalculator::ExistsCellIdPath (stdfwd::string path)
{
  if (m_pathCellIdMap.find (path) == m_pathCellIdMap.end () )
    {
      return false;
    }
  else
    {
      return true;
    }
}

void
LteStatsCalculator::SetCellIdPath (stdfwd::string path, uint16_t cellId)
{
  NS_LOG_FUNCTION (this << path << cellId);
  m_pathCellIdMap[path] = cellId;
}

uint16_t
LteStatsCalculator::GetCellIdPath (stdfwd::string path)
{
  return m_pathCellIdMap.find (path)->second;
}


uint64_t
LteStatsCalculator::FindImsiFromEnbRlcPath (stdfwd::string path)
{
  NS_LOG_FUNCTION (path);
  // Sample path input:
  // /NodeList/#NodeId/DeviceList/#DeviceId/LteEnbRrc/UeMap/#C-RNTI/DataRadioBearerMap/#LCID/LteRlc/RxPDU

  // We retrieve the UeManager associated to the C-RNTI and perform the IMSI lookup
  stdfwd::string ueMapPath = path.substr (0, path.find ("/DataRadioBearerMap"));
  Config::MatchContainer match = Config::LookupMatches (ueMapPath);

  if (match.GetN () != 0)
    {
      Ptr<Object> ueInfo = match.Get (0);
      NS_LOG_LOGIC ("FindImsiFromEnbRlcPath: " << path << ", " << ueInfo->GetObject<UeManager> ()->GetImsi ());
      return ueInfo->GetObject<UeManager> ()->GetImsi ();
    }
  else
    {
      NS_FATAL_ERROR ("Lookup " << ueMapPath << " got no matches");
    }
}

uint64_t
LteStatsCalculator::FindImsiFromUePhy (stdfwd::string path)
{
  NS_LOG_FUNCTION (path);
  // Sample path input:
  // /NodeList/#NodeId/DeviceList/#DeviceId/LteUePhy

  // We retrieve the UeInfo associated to the C-RNTI and perform the IMSI lookup
  stdfwd::string ueRlcPath = path.substr (0, path.find ("/LteUePhy"));
  ueRlcPath += "/LteUeRrc";
  Config::MatchContainer match = Config::LookupMatches (ueRlcPath);

  if (match.GetN () != 0)
    {
      Ptr<Object> ueRrc = match.Get (0);
      return ueRrc->GetObject<LteUeRrc> ()->GetImsi ();
    }
  else
    {
      NS_FATAL_ERROR ("Lookup " << ueRlcPath << " got no matches");
    }
  return 0;
}


uint64_t
LteStatsCalculator::FindImsiFromLteNetDevice (stdfwd::string path)
{
  NS_LOG_FUNCTION (path);
  // Sample path input:
  // /NodeList/#NodeId/DeviceList/#DeviceId/

  // We retrieve the Imsi associated to the LteUeNetDevice
  Config::MatchContainer match = Config::LookupMatches (path);

  if (match.GetN () != 0)
    {
      Ptr<Object> ueNetDevice = match.Get (0);
      NS_LOG_LOGIC ("FindImsiFromLteNetDevice: " << path << ", " << ueNetDevice->GetObject<LteUeNetDevice> ()->GetImsi ());
      return ueNetDevice->GetObject<LteUeNetDevice> ()->GetImsi ();
    }
  else
    {
      NS_FATAL_ERROR ("Lookup " << path << " got no matches");
    }
}

uint16_t
LteStatsCalculator::FindCellIdFromEnbRlcPath (stdfwd::string path)
{
  NS_LOG_FUNCTION (path);
  // Sample path input:
  // /NodeList/#NodeId/DeviceList/#DeviceId/LteEnbRrc/UeMap/#C-RNTI/DataRadioBearerMap/#LCID/LteRlc/RxPDU

  // We retrieve the CellId associated to the Enb
  stdfwd::string enbNetDevicePath = path.substr (0, path.find ("/LteEnbRrc"));
  Config::MatchContainer match = Config::LookupMatches (enbNetDevicePath);
  if (match.GetN () != 0)
    {
      Ptr<Object> enbNetDevice = match.Get (0);
      NS_LOG_LOGIC ("FindCellIdFromEnbRlcPath: " << path << ", " << enbNetDevice->GetObject<LteEnbNetDevice> ()->GetCellId ());
      return enbNetDevice->GetObject<LteEnbNetDevice> ()->GetCellId ();
    }
  else
    {
      NS_FATAL_ERROR ("Lookup " << enbNetDevicePath << " got no matches");
    }
}

uint64_t
LteStatsCalculator::FindImsiFromEnbMac (stdfwd::string path, uint16_t rnti)
{
  NS_LOG_FUNCTION (path << rnti);

  // /NodeList/#NodeId/DeviceList/#DeviceId/LteEnbMac/DlScheduling
  std::ostringstream oss;
  stdfwd::string p = path.substr (0, path.find ("/LteEnbMac"));
  oss << rnti;
  p += "/LteEnbRrc/UeMap/" + oss.str ();
  uint64_t imsi = FindImsiFromEnbRlcPath (p);
  NS_LOG_LOGIC ("FindImsiFromEnbMac: " << path << ", " << rnti << ", " << imsi);
  return imsi;
}

uint16_t
LteStatsCalculator::FindCellIdFromEnbMac (stdfwd::string path, uint16_t rnti)
{
  NS_LOG_FUNCTION (path << rnti);
  // /NodeList/#NodeId/DeviceList/#DeviceId/LteEnbMac/DlScheduling
  std::ostringstream oss;
  stdfwd::string p = path.substr (0, path.find ("/LteEnbMac"));
  oss << rnti;
  p += "/LteEnbRrc/UeMap/" + oss.str ();
  uint16_t cellId = FindCellIdFromEnbRlcPath (p);
  NS_LOG_LOGIC ("FindCellIdFromEnbMac: " << path << ", "<< rnti << ", " << cellId);
  return cellId;
}


uint64_t
LteStatsCalculator::FindImsiForEnb (stdfwd::string path, uint16_t rnti)
{
  NS_LOG_FUNCTION (path << rnti);
  uint64_t imsi = 0;
  if (path.find ("/DlPhyTransmission"))
    {
      // /NodeList/0/DeviceList/0/LteEnbPhy/DlPhyTransmission/LteEnbRrc/UeMap/1
      std::ostringstream oss;
      stdfwd::string p = path.substr (0, path.find ("/LteEnbPhy"));
      oss << rnti;
      p += "/LteEnbRrc/UeMap/" + oss.str ();
      imsi = FindImsiFromEnbRlcPath (p);
      NS_LOG_LOGIC ("FindImsiForEnb[Tx]: " << path << ", " << rnti << ", " << imsi);
    }
  else if (path.find ("/UlPhyReception"))
    {
      stdfwd::string p = path.substr (0, path.find ("/LteUePhy"));
      imsi = FindImsiFromLteNetDevice (p);
      NS_LOG_LOGIC ("FindImsiForEnb[Rx]: " << path << ", " << rnti << ", " << imsi);
    }
  return imsi;
}


uint64_t
LteStatsCalculator::FindImsiForUe (stdfwd::string path, uint16_t rnti)
{
  NS_LOG_FUNCTION (path << rnti);
  uint64_t imsi = 0;
  if (path.find ("/UlPhyTransmission"))
    {
      stdfwd::string p = path.substr (0, path.find ("/LteUePhy"));
      imsi = FindImsiFromLteNetDevice (p);
      NS_LOG_LOGIC ("FindImsiForUe[Tx]: " << path << ", " << rnti << ", " << imsi);
    }
  else if (path.find ("/DlPhyReception"))
    {
      // /NodeList/0/DeviceList/0/LteEnbPhy/LteSpectrumPhy
      std::ostringstream oss;
      stdfwd::string p = path.substr (0, path.find ("/LteEnbPhy"));
      oss << rnti;
      p += "/LteEnbRrc/UeMap/" + oss.str ();
      imsi = FindImsiFromEnbRlcPath (p);
      NS_LOG_LOGIC ("FindImsiForUe[Rx]: " << path << ", " << rnti << ", " << imsi);
    }
  return imsi;
}


} // namespace ns3
