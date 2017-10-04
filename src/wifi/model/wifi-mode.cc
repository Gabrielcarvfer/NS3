/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2005,2006,2007 INRIA
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
 * Authors: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 *          Sébastien Deronne <sebastien.deronne@gmail.com>
 */

#include "wifi-mode.h"
#include "wifi-tx-vector.h"
#include "ns3/simulator.h"
#include "ns3/assert.h"
#include "ns3/log.h"
#include <cmath>

namespace ns3 {

/**
 * Check if the two WifiModes are identical.
 *
 * \param a WifiMode
 * \param b WifiMode
 *
 * \return true if the two WifiModes are identical,
 *         false otherwise
 */
bool operator == (const WifiMode &a, const WifiMode &b)
{
  return a.GetUid () == b.GetUid ();
}
/**
 * Serialize WifiMode to ostream (human-readable).
 *
 * \param os std::ostream
 * \param mode
 *
 * \return std::ostream
 */
std::ostream & operator << (std::ostream & os, const WifiMode &mode)
{
  os << mode.GetUniqueName ();
  return os;
}
/**
 * Serialize WifiMode from istream (human-readable).
 *
 * \param is std::istream
 * \param mode
 *
 * \return std::istream
 */
std::istream & operator >> (std::istream &is, WifiMode &mode)
{
  std::string str;
  is >> str;
  mode = WifiModeFactory::GetFactory ()->Search (str);
  return is;
}

uint64_t
WifiMode::GetPhyRate (uint32_t channelWidth, bool isShortGuardInterval, uint8_t nss) const
{
  //TODO: nss > 4 not supported yet
  NS_ASSERT (nss <= 4);
  uint32_t dataRate, phyRate;
  dataRate = GetDataRate (channelWidth, isShortGuardInterval, nss);
  switch (GetCodeRate ())
    {
    case WIFI_CODE_RATE_5_6:
      phyRate = dataRate * 6 / 5;
      break;
    case WIFI_CODE_RATE_3_4:
      phyRate = dataRate * 4 / 3;
      break;
    case WIFI_CODE_RATE_2_3:
      phyRate = dataRate * 3 / 2;
      break;
    case WIFI_CODE_RATE_1_2:
      phyRate = dataRate * 2 / 1;
      break;
    case WIFI_CODE_RATE_UNDEFINED:
    default:
      phyRate = dataRate;
      break;
    }
  return phyRate;
}

uint64_t
WifiMode::GetPhyRate (WifiTxVector txVector) const
{
  return GetPhyRate (txVector.GetChannelWidth (), txVector.IsShortGuardInterval (), txVector.GetNss ());
}

uint64_t
WifiMode::GetDataRate (uint32_t channelWidth, bool isShortGuardInterval, uint8_t nss) const
{
  //TODO: nss > 4 not supported yet
  NS_ASSERT (nss <= 4);
  struct WifiModeFactory::WifiModeItem *item = WifiModeFactory::GetFactory ()->Get (m_uid);
  uint64_t dataRate = 0;
  uint32_t usableSubCarriers = 0;
  double symbolRate = 0;
  double codingRate = 0;
  uint32_t numberOfBitsPerSubcarrier = log2 (GetConstellationSize ());
  if (item->modClass == WIFI_MOD_CLASS_DSSS)
    {
      dataRate = ((11000000 / 11) * numberOfBitsPerSubcarrier);
    }
  else if (item->modClass == WIFI_MOD_CLASS_HR_DSSS)
    {
      dataRate = ((11000000 / 8) * numberOfBitsPerSubcarrier);
    }
  else if (item->modClass == WIFI_MOD_CLASS_OFDM || item->modClass == WIFI_MOD_CLASS_ERP_OFDM)
    {
      usableSubCarriers = 48;
      switch (channelWidth)
        {
        case 20:
        default:
          symbolRate = (1 / 4.0) * 1e6;
          break;
        case 10:
          symbolRate = (1 / 8.0) * 1e6;
          break;
        case 5:
          symbolRate = (1 / 16.0) * 1e6;
          break;
        }

      switch (GetCodeRate ())
        {
        case WIFI_CODE_RATE_3_4:
          codingRate = (3.0 / 4.0);
          break;
        case WIFI_CODE_RATE_2_3:
          codingRate = (2.0 / 3.0);
          break;
        case WIFI_CODE_RATE_1_2:
          codingRate = (1.0 / 2.0);
          break;
        case WIFI_CODE_RATE_UNDEFINED:
        default:
          NS_FATAL_ERROR ("trying to get datarate for a mcs without any coding rate defined");
          break;
        }

      dataRate = lrint (ceil (symbolRate * usableSubCarriers * numberOfBitsPerSubcarrier * codingRate));
    }
  else if (item->modClass == WIFI_MOD_CLASS_HT || item->modClass == WIFI_MOD_CLASS_VHT)
    {
      if (item->modClass == WIFI_MOD_CLASS_VHT && item->mcsValue == 9 && nss != 3)
        {
          NS_ASSERT_MSG (channelWidth != 20, "VHT MCS 9 forbidden at 20 MHz (only allowed when NSS = 3)");
        }
      if (item->modClass == WIFI_MOD_CLASS_VHT && item->mcsValue == 6 && nss == 3)
        {
          NS_ASSERT_MSG (channelWidth != 80, "VHT MCS 6 forbidden at 80 MHz when NSS = 3");
        }

      if (!isShortGuardInterval)
        {
          symbolRate = (1 / 4.0) * 1e6;
        }
      else
        {
          symbolRate = (1 / 3.6) * 1e6;
        }

      switch (channelWidth)
        {
        case 20:
        default:
          usableSubCarriers = 52;
          break;
        case 40:
          usableSubCarriers = 108;
          break;
        case 80:
          usableSubCarriers = 234;
          break;
        case 160:
          usableSubCarriers = 468;
          break;
        }

      switch (GetCodeRate ())
        {
        case WIFI_CODE_RATE_5_6:
          codingRate = (5.0 / 6.0);
          break;
        case WIFI_CODE_RATE_3_4:
          codingRate = (3.0 / 4.0);
          break;
        case WIFI_CODE_RATE_2_3:
          codingRate = (2.0 / 3.0);
          break;
        case WIFI_CODE_RATE_1_2:
          codingRate = (1.0 / 2.0);
          break;
        case WIFI_CODE_RATE_UNDEFINED:
        default:
          NS_FATAL_ERROR ("trying to get datarate for a mcs without any coding rate defined with nss: " << (uint16_t) nss);
          break;
        }

      dataRate = lrint (ceil (symbolRate * usableSubCarriers * numberOfBitsPerSubcarrier * codingRate));
    }
  else
    {
      NS_ASSERT ("undefined datarate for the modulation class!");
    }
  dataRate *= nss; // number of spatial streams
  return dataRate;
}

uint64_t
WifiMode::GetDataRate (WifiTxVector txVector) const
{
  return GetDataRate (txVector.GetChannelWidth (), txVector.IsShortGuardInterval (), txVector.GetNss ());
}

enum WifiCodeRate
WifiMode::GetCodeRate (void) const
{
  struct WifiModeFactory::WifiModeItem *item = WifiModeFactory::GetFactory ()->Get (m_uid);
  if (item->modClass == WIFI_MOD_CLASS_HT)
    {
      switch (item->mcsValue % 8)
        {
        case 0:
        case 1:
        case 3:
          return WIFI_CODE_RATE_1_2;
        case 2:
        case 4:
        case 6:
          return WIFI_CODE_RATE_3_4;
        case 5:
          return WIFI_CODE_RATE_2_3;
        case 7:
          return WIFI_CODE_RATE_5_6;
        default:
          return WIFI_CODE_RATE_UNDEFINED;
        }
    }
  else if (item->modClass == WIFI_MOD_CLASS_VHT)
    {
      switch (item->mcsValue)
        {
        case 0:
        case 1:
        case 3:
          return WIFI_CODE_RATE_1_2;
        case 2:
        case 4:
        case 6:
        case 8:
          return WIFI_CODE_RATE_3_4;
        case 5:
          return WIFI_CODE_RATE_2_3;
        case 7:
        case 9:
          return WIFI_CODE_RATE_5_6;
        default:
          return WIFI_CODE_RATE_UNDEFINED;
        }
    }
  else
    {
      return item->codingRate;
    }
}

uint16_t
WifiMode::GetConstellationSize (void) const
{
  struct WifiModeFactory::WifiModeItem *item = WifiModeFactory::GetFactory ()->Get (m_uid);
  if (item->modClass == WIFI_MOD_CLASS_HT)
    {
      switch (item->mcsValue % 8)
        {
        case 0:
          return 2;
        case 1:
        case 2:
          return 4;
        case 3:
        case 4:
          return 16;
        case 5:
        case 6:
        case 7:
          return 64;
        default:
          return 0;
        }
    }
  else if (item->modClass == WIFI_MOD_CLASS_VHT)
    {
      switch (item->mcsValue)
        {
        case 0:
          return 2;
        case 1:
        case 2:
          return 4;
        case 3:
        case 4:
          return 16;
        case 5:
        case 6:
        case 7:
          return 64;
        case 8:
        case 9:
          return 256;
        default:
          return 0;
        }
    }
  else
    {
      return item->constellationSize;
    }
}

std::string
WifiMode::GetUniqueName (void) const
{
  //needed for ostream printing of the invalid mode
  struct WifiModeFactory::WifiModeItem *item = WifiModeFactory::GetFactory ()->Get (m_uid);
  return item->uniqueUid;
}

bool
WifiMode::IsMandatory (void) const
{
  struct WifiModeFactory::WifiModeItem *item = WifiModeFactory::GetFactory ()->Get (m_uid);
  return item->isMandatory;
}

uint8_t
WifiMode::GetMcsValue (void) const
{
  struct WifiModeFactory::WifiModeItem *item = WifiModeFactory::GetFactory ()->Get (m_uid);
  if (item->modClass == WIFI_MOD_CLASS_HT || item->modClass == WIFI_MOD_CLASS_VHT)
    {
      return item->mcsValue;
    }
  else
    {
      //We should not go here!
      NS_ASSERT (false);
      return 0;
    }
}

uint32_t
WifiMode::GetUid (void) const
{
  return m_uid;
}

enum WifiModulationClass
WifiMode::GetModulationClass () const
{
  struct WifiModeFactory::WifiModeItem *item = WifiModeFactory::GetFactory ()->Get (m_uid);
  return item->modClass;
}

uint64_t
WifiMode::GetNonHtReferenceRate (void) const
{
  uint64_t dataRate;
  struct WifiModeFactory::WifiModeItem *item = WifiModeFactory::GetFactory ()->Get (m_uid);
  if (item->modClass == WIFI_MOD_CLASS_HT || item->modClass == WIFI_MOD_CLASS_VHT)
    {
      WifiCodeRate codeRate = GetCodeRate();
      switch(GetConstellationSize())
        {
        case 2:
          if (codeRate == WIFI_CODE_RATE_1_2)
            dataRate = 6000000;
          else if (codeRate == WIFI_CODE_RATE_3_4)
            dataRate = 9000000;
          else
            NS_FATAL_ERROR ("Trying to get reference rate for a MCS with wrong combination of coding rate and modulation");
          break;
        case 4:
          if (codeRate == WIFI_CODE_RATE_1_2)
            dataRate = 12000000;
          else if (codeRate == WIFI_CODE_RATE_3_4)
            dataRate = 18000000;
          else
            NS_FATAL_ERROR ("Trying to get reference rate for a MCS with wrong combination of coding rate and modulation");
          break;
        case 16:
          if (codeRate == WIFI_CODE_RATE_1_2)
            dataRate = 24000000;
          else if (codeRate == WIFI_CODE_RATE_3_4)
            dataRate = 36000000;
          else
            NS_FATAL_ERROR ("Trying to get reference rate for a MCS with wrong combination of coding rate and modulation");
          break;
        case 64:
          if (codeRate == WIFI_CODE_RATE_1_2 || codeRate == WIFI_CODE_RATE_2_3)
            dataRate = 48000000;
          else if (codeRate == WIFI_CODE_RATE_3_4 || codeRate == WIFI_CODE_RATE_5_6)
            dataRate = 54000000;
          else
            NS_FATAL_ERROR ("Trying to get reference rate for a MCS with wrong combination of coding rate and modulation");
          break;
        case 256:
          if (codeRate == WIFI_CODE_RATE_3_4 || codeRate == WIFI_CODE_RATE_5_6)
            dataRate = 54000000;
          else
            NS_FATAL_ERROR ("Trying to get reference rate for a MCS with wrong combination of coding rate and modulation");
          break;
        default:
            NS_FATAL_ERROR ("Wrong constellation size");
        }
    }
  else
    {
      NS_FATAL_ERROR ("Trying to get reference rate for a non-HT rate");
    }
  return dataRate;
}

bool
WifiMode::IsHigherCodeRate (WifiMode mode) const
{
  WifiCodeRate codeRate = mode.GetCodeRate ();
  switch (GetCodeRate ())
    {
    case WIFI_CODE_RATE_1_2:
      return false; //This is the smallest code rate.
    case WIFI_CODE_RATE_2_3:
      return (codeRate == WIFI_CODE_RATE_1_2);
    case WIFI_CODE_RATE_3_4:
      return (codeRate == WIFI_CODE_RATE_1_2 || codeRate == WIFI_CODE_RATE_2_3);
    case WIFI_CODE_RATE_5_6:
      return (codeRate == WIFI_CODE_RATE_1_2 || codeRate == WIFI_CODE_RATE_2_3 || codeRate == WIFI_CODE_RATE_3_4);
    default:
      NS_FATAL_ERROR ("Wifi Code Rate not defined");
      return false;
    }
}

bool
WifiMode::IsHigherDataRate (WifiMode mode) const
{
  struct WifiModeFactory::WifiModeItem *item = WifiModeFactory::GetFactory ()->Get (m_uid);
  switch(item->modClass)
    {
    case WIFI_MOD_CLASS_DSSS:
      if (mode.GetModulationClass () == WIFI_MOD_CLASS_DSSS)
        {
          return (GetConstellationSize () > mode.GetConstellationSize ());
        }
      else
        {
          return false;
        }
    case WIFI_MOD_CLASS_HR_DSSS:
      if (mode.GetModulationClass () == WIFI_MOD_CLASS_DSSS)
        {
          return true;
        }
      else
        {
          return (GetConstellationSize () > mode.GetConstellationSize ());
        }
    case WIFI_MOD_CLASS_ERP_OFDM:
    case WIFI_MOD_CLASS_OFDM:
    case WIFI_MOD_CLASS_HT:
    case WIFI_MOD_CLASS_VHT:
      if (mode.GetModulationClass () == WIFI_MOD_CLASS_DSSS)
        {
          return true;
        }
      else if (mode.GetModulationClass () == WIFI_MOD_CLASS_HR_DSSS)
        {
          return (mode.GetConstellationSize () > GetConstellationSize ());
        }
      else
        {
          if (GetConstellationSize () > mode.GetConstellationSize ())
            {
              return true;
            }
          else if (GetConstellationSize () == mode.GetConstellationSize ())
            {
              return IsHigherCodeRate (mode);
            }
          else
            {
              return false;
            }
        }
    default:
      NS_FATAL_ERROR ("Modulation class not defined");
      return false;
    }
}

WifiMode::WifiMode ()
  : m_uid (0)
{
}

WifiMode::WifiMode (uint32_t uid)
  : m_uid (uid)
{
}

WifiMode::WifiMode (std::string name)
{
  *this = WifiModeFactory::GetFactory ()->Search (name);
}

ATTRIBUTE_HELPER_CPP (WifiMode);

WifiModeFactory::WifiModeFactory ()
{
}

WifiMode
WifiModeFactory::CreateWifiMode (std::string uniqueName,
                                 enum WifiModulationClass modClass,
                                 bool isMandatory,
                                 enum WifiCodeRate codingRate,
                                 uint16_t constellationSize)
{
  WifiModeFactory *factory = GetFactory ();
  uint32_t uid = factory->AllocateUid (uniqueName);
  WifiModeItem *item = factory->Get (uid);
  item->uniqueUid = uniqueName;
  item->modClass = modClass;
  //The modulation class for this WifiMode must be valid.
  NS_ASSERT (modClass != WIFI_MOD_CLASS_UNKNOWN);
  item->codingRate = codingRate;

  //Check for compatibility between modulation class and coding
  //rate. If modulation class is DSSS then coding rate must be
  //undefined, and vice versa. I could have done this with an
  //assertion, but it seems better to always give the error (i.e.,
  //not only in non-optimised builds) and the cycles that extra test
  //here costs are only suffered at simulation setup.
  if ((codingRate == WIFI_CODE_RATE_UNDEFINED) && modClass != WIFI_MOD_CLASS_DSSS && modClass != WIFI_MOD_CLASS_HR_DSSS)
    {
      NS_FATAL_ERROR ("Error in creation of WifiMode named " << uniqueName << std::endl
                                                             << "Code rate must be WIFI_CODE_RATE_UNDEFINED iff Modulation Class is WIFI_MOD_CLASS_DSSS or WIFI_MOD_CLASS_HR_DSSS");
    }

  item->constellationSize = constellationSize;
  item->isMandatory = isMandatory;

  NS_ASSERT (modClass != WIFI_MOD_CLASS_HT && modClass != WIFI_MOD_CLASS_VHT);
  //fill unused mcs item with a dummy value
  item->mcsValue = 0;

  return WifiMode (uid);
}

WifiMode
WifiModeFactory::CreateWifiMcs (std::string uniqueName,
                                uint8_t mcsValue,
                                enum WifiModulationClass modClass)
{
  WifiModeFactory *factory = GetFactory ();
  uint32_t uid = factory->AllocateUid (uniqueName);
  WifiModeItem *item = factory->Get (uid);
  item->uniqueUid = uniqueName;
  item->modClass = modClass;

  //The modulation class must be either HT or VHT
  NS_ASSERT (modClass == WIFI_MOD_CLASS_HT || modClass == WIFI_MOD_CLASS_VHT);

  item->mcsValue = mcsValue;
  //fill unused items with dummy values
  item->constellationSize = 0;
  item->codingRate = WIFI_CODE_RATE_UNDEFINED;
  item->isMandatory = false;

  return WifiMode (uid);
}

WifiMode
WifiModeFactory::Search (std::string name)
{
  WifiModeItemList::const_iterator i;
  uint32_t j = 0;
  for (i = m_itemList.begin (); i != m_itemList.end (); i++)
    {
      if (i->uniqueUid == name)
        {
          return WifiMode (j);
        }
      j++;
    }

  //If we get here then a matching WifiMode was not found above. This
  //is a fatal problem, but we try to be helpful by displaying the
  //list of WifiModes that are supported.
  NS_LOG_UNCOND ("Could not find match for WifiMode named \""
                 << name << "\". Valid options are:");
  for (i = m_itemList.begin (); i != m_itemList.end (); i++)
    {
      NS_LOG_UNCOND ("  " << i->uniqueUid);
    }
  //Empty fatal error to die. We've already unconditionally logged
  //the helpful information.
  NS_FATAL_ERROR ("");

  //This next line is unreachable because of the fatal error
  //immediately above, and that is fortunate, because we have no idea
  //what is in WifiMode (0), but we do know it is not what our caller
  //has requested by name. It's here only because it's the safest
  //thing that'll give valid code.
  return WifiMode (0);
}

uint32_t
WifiModeFactory::AllocateUid (std::string uniqueUid)
{
  uint32_t j = 0;
  for (WifiModeItemList::const_iterator i = m_itemList.begin ();
       i != m_itemList.end (); i++)
    {
      if (i->uniqueUid == uniqueUid)
        {
          return j;
        }
      j++;
    }
  uint32_t uid = m_itemList.size ();
  m_itemList.push_back (WifiModeItem ());
  return uid;
}

struct WifiModeFactory::WifiModeItem *
WifiModeFactory::Get (uint32_t uid)
{
  NS_ASSERT (uid < m_itemList.size ());
  return &m_itemList[uid];
}

WifiModeFactory *
WifiModeFactory::GetFactory (void)
{
  static bool isFirstTime = true;
  static WifiModeFactory factory;
  if (isFirstTime)
    {
      uint32_t uid = factory.AllocateUid ("Invalid-WifiMode");
      WifiModeItem *item = factory.Get (uid);
      item->uniqueUid = "Invalid-WifiMode";
      item->modClass = WIFI_MOD_CLASS_UNKNOWN;
      item->constellationSize = 0;
      item->codingRate = WIFI_CODE_RATE_UNDEFINED;
      item->isMandatory = false;
      item->mcsValue = 0;
      isFirstTime = false;
    }
  return &factory;
}

} //namespace ns3
