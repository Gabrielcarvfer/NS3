/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2006, 2009 INRIA
 * Copyright (c) 2009 MIRKO BANCHI
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
 *          Mirko Banchi <mk.banchi@gmail.com>
 */

#include "ap-wifi-mac-beac.h"
#include "ns3/assert.h"
#include "ns3/log.h"
#include "ns3/simulator.h"
#include "ns3/string.h"
#include "ns3/pointer.h"
#include "ns3/boolean.h"
#include "wifi-phy.h"
#include "dcf-manager.h"
#include "mac-rx-middle.h"
#include "mac-tx-middle.h"
#include "mgt-headers.h"
#include "mac-low.h"
#include "amsdu-subframe-header.h"
#include "msdu-aggregator.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("ApWifiMacBeac");

NS_OBJECT_ENSURE_REGISTERED (ApWifiMacBeac);

TypeId
ApWifiMacBeac::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::ApWifiMacBeac")
    .SetParent<RegularWifiMac> ()
    .SetGroupName ("Wifi")
    .AddConstructor<ApWifiMacBeac> ()
    .AddAttribute ("BeaconInterval",
                   "Delay between two beacons",
                   TimeValue (MicroSeconds (102400)),
                   MakeTimeAccessor (&ApWifiMacBeac::GetBeaconInterval,
                                     &ApWifiMacBeac::SetBeaconInterval),
                   MakeTimeChecker ())
    .AddAttribute ("MaxBeaconInterval",
                   "MaxDelay between two beacons",
                   TimeValue (MicroSeconds (102400)),
                   MakeTimeAccessor (&ApWifiMacBeac::GetMaxBeaconInterval,
                                     &ApWifiMacBeac::SetMaxBeaconInterval),
                   MakeTimeChecker ())
    .AddAttribute ("MinBeaconInterval",
                   "MinDelay between two beacons",
                   TimeValue (MicroSeconds (102400)),
                   MakeTimeAccessor (&ApWifiMacBeac::GetMinBeaconInterval,
                                     &ApWifiMacBeac::SetMinBeaconInterval),
                   MakeTimeChecker ())
    .AddAttribute ("BeaconJitter",
                   "A uniform random variable to cause the initial beacon starting time (after simulation time 0) "
                   "to be distributed between 0 and the BeaconInterval.",
                   StringValue ("ns3::UniformRandomVariable"),
                   MakePointerAccessor (&ApWifiMacBeac::m_beaconJitter),
                   MakePointerChecker<UniformRandomVariable> ())
    .AddAttribute ("EnableBeaconJitter",
                   "If beacons are enabled, whether to jitter the initial send event.",
                   BooleanValue (false),
                   MakeBooleanAccessor (&ApWifiMacBeac::m_enableBeaconJitter),
                   MakeBooleanChecker ())
    .AddAttribute ("BeaconGeneration",
                   "Whether or not beacons are generated.",
                   BooleanValue (true),
                   MakeBooleanAccessor (&ApWifiMacBeac::SetBeaconGeneration,
                                        &ApWifiMacBeac::GetBeaconGeneration),
                   MakeBooleanChecker ())
    .AddAttribute ("EnableNonErpProtection", "Whether or not protection mechanism should be used when non-ERP STAs are present within the BSS."
                   "This parameter is only used when ERP is supported by the AP.",
                   BooleanValue (true),
                   MakeBooleanAccessor (&ApWifiMacBeac::m_enableNonErpProtection),
                   MakeBooleanChecker ())
  ;
  return tid;
}

ApWifiMacBeac::ApWifiMacBeac ()
{
  NS_LOG_FUNCTION (this);
  m_beaconDca = CreateObject<DcaTxop> ();
  m_beaconDca->SetAifsn (1);
  m_beaconDca->SetMinCw (0);
  m_beaconDca->SetMaxCw (0);
  m_beaconDca->SetLow (m_low);
  m_beaconDca->SetManager (m_dcfManager);
  m_beaconDca->SetTxMiddle (m_txMiddle);

  //Let the lower layers know that we are acting as an AP.
  SetTypeOfStation (AP);

  m_enableBeaconGeneration = false;
}

ApWifiMacBeac::~ApWifiMacBeac ()
{
  NS_LOG_FUNCTION (this);
  m_staList.clear();
  m_nonErpStations.clear ();
  m_nonHtStations.clear ();
}

void
ApWifiMacBeac::DoDispose ()
{
  NS_LOG_FUNCTION (this);
  m_beaconDca = 0;
  m_enableBeaconGeneration = false;
  m_beaconEvent.Cancel ();
  RegularWifiMac::DoDispose ();
}

void
ApWifiMacBeac::SetAddress (Mac48Address address)
{
  NS_LOG_FUNCTION (this << address);
  //As an AP, our MAC address is also the BSSID. Hence we are
  //overriding this function and setting both in our parent class.
  RegularWifiMac::SetAddress (address);
  RegularWifiMac::SetBssid (address);
}

void
ApWifiMacBeac::SetBeaconGeneration (bool enable)
{
  NS_LOG_FUNCTION (this << enable);
  if (!enable)
    {
      m_beaconEvent.Cancel ();
    }
  else if (enable && !m_enableBeaconGeneration)
    {
      m_beaconEvent = Simulator::ScheduleNow (&ApWifiMacBeac::SendOneBeacon, this);
    }
  m_enableBeaconGeneration = enable;
}

bool
ApWifiMacBeac::GetBeaconGeneration (void) const
{
  NS_LOG_FUNCTION (this);
  return m_enableBeaconGeneration;
}

Time
ApWifiMacBeac::GetBeaconInterval (void) const
{
  NS_LOG_FUNCTION (this);
  return m_beaconInterval;
}

Time
ApWifiMacBeac::GetMinBeaconInterval (void) const
{
  NS_LOG_FUNCTION (this);
  return m_maxBeaconInterval;
}

Time
ApWifiMacBeac::GetMaxBeaconInterval (void) const
{
  NS_LOG_FUNCTION (this);
  return m_minBeaconInterval;
}

void
ApWifiMacBeac::SetWifiRemoteStationManager (Ptr<WifiRemoteStationManager> stationManager)
{
  NS_LOG_FUNCTION (this << stationManager);
  m_beaconDca->SetWifiRemoteStationManager (stationManager);
  RegularWifiMac::SetWifiRemoteStationManager (stationManager);
}

void
ApWifiMacBeac::SetLinkUpCallback (Callback<void> linkUp)
{
  NS_LOG_FUNCTION (this << &linkUp);
  RegularWifiMac::SetLinkUpCallback (linkUp);

  //The approach taken here is that, from the point of view of an AP,
  //the link is always up, so we immediately invoke the callback if
  //one is set
  linkUp ();
}

void
ApWifiMacBeac::SetBeaconInterval (Time interval)
{
  NS_LOG_FUNCTION (this << interval);
  if ((interval.GetMicroSeconds () % 1024) != 0)
    {
      NS_LOG_WARN ("beacon interval should be multiple of 1024us (802.11 time unit), see IEEE Std. 802.11-2012");
    }
  m_beaconInterval = interval;
}

void
ApWifiMacBeac::SetMaxBeaconInterval (Time interval)
{
  NS_LOG_FUNCTION (this << interval);
  if ((interval.GetMicroSeconds () % 1024) != 0)
    {
      NS_LOG_WARN ("beacon interval should be multiple of 1024us (802.11 time unit), see IEEE Std. 802.11-2012");
    }
  m_maxBeaconInterval = interval;
}

void
ApWifiMacBeac::SetMinBeaconInterval (Time interval)
{
  NS_LOG_FUNCTION (this << interval);
  if ((interval.GetMicroSeconds () % 1024) != 0)
    {
      NS_LOG_WARN ("beacon interval should be multiple of 1024us (802.11 time unit), see IEEE Std. 802.11-2012");
    }
  m_minBeaconInterval = interval;
}

void
ApWifiMacBeac::StartBeaconing (void)
{
  NS_LOG_FUNCTION (this);
  SendOneBeacon ();
}

int64_t
ApWifiMacBeac::AssignStreams (int64_t stream)
{
  NS_LOG_FUNCTION (this << stream);
  m_beaconJitter->SetStream (stream);
  return 1;
}

bool
ApWifiMacBeac::GetShortSlotTimeEnabled (void) const
{
  if (m_nonErpStations.size () != 0)
    {
      return false;
    }
  if (m_erpSupported == true && GetShortSlotTimeSupported () == true)
    {
      for (std::list<Mac48Address>::const_iterator i = m_staList.begin (); i != m_staList.end (); i++)
      {
        if (m_stationManager->GetShortSlotTimeSupported (*i) == false)
          {
            return false;
          }
      }
      return true;
    }
  return false;
}

bool
ApWifiMacBeac::GetShortPreambleEnabled (void) const
{
  if (m_erpSupported || m_phy->GetShortPlcpPreambleSupported ())
    {
      for (std::list<Mac48Address>::const_iterator i = m_nonErpStations.begin (); i != m_nonErpStations.end (); i++)
      {
        if (m_stationManager->GetShortPreambleSupported (*i) == false)
          {
            return false;
          }
      }
      return true;
    }
  return false;
}

void
ApWifiMacBeac::ForwardDown (Ptr<const Packet> packet, Mac48Address from,
                        Mac48Address to)
{
  NS_LOG_FUNCTION (this << packet << from << to);
  //If we are not a QoS AP then we definitely want to use AC_BE to
  //transmit the packet. A TID of zero will map to AC_BE (through \c
  //QosUtilsMapTidToAc()), so we use that as our default here.
  uint8_t tid = 0;

  //If we are a QoS AP then we attempt to get a TID for this packet
  if (m_qosSupported)
    {
      tid = QosUtilsGetTidForPacket (packet);
      //Any value greater than 7 is invalid and likely indicates that
      //the packet had no QoS tag, so we revert to zero, which'll
      //mean that AC_BE is used.
      if (tid > 7)
        {
          tid = 0;
        }
    }

  ForwardDown (packet, from, to, tid);
}

void
ApWifiMacBeac::ForwardDown (Ptr<const Packet> packet, Mac48Address from,
                        Mac48Address to, uint8_t tid)
{
  NS_LOG_FUNCTION (this << packet << from << to << static_cast<uint32_t> (tid));
  WifiMacHeader hdr;

  //For now, an AP that supports QoS does not support non-QoS
  //associations, and vice versa. In future the AP model should
  //support simultaneously associated QoS and non-QoS STAs, at which
  //point there will need to be per-association QoS state maintained
  //by the association state machine, and consulted here.
  if (m_qosSupported)
    {
      hdr.SetType (WIFI_MAC_QOSDATA);
      hdr.SetQosAckPolicy (WifiMacHeader::NORMAL_ACK);
      hdr.SetQosNoEosp ();
      hdr.SetQosNoAmsdu ();
      //Transmission of multiple frames in the same Polled TXOP is not supported for now
      hdr.SetQosTxopLimit (0);
      //Fill in the QoS control field in the MAC header
      hdr.SetQosTid (tid);
    }
  else
    {
      hdr.SetTypeData ();
    }

  if (m_htSupported || m_vhtSupported)
    {
      hdr.SetNoOrder ();
    }
  hdr.SetAddr1 (to);
  hdr.SetAddr2 (GetAddress ());
  hdr.SetAddr3 (from);
  hdr.SetDsFrom ();
  hdr.SetDsNotTo ();

  if (m_qosSupported)
    {
      //Sanity check that the TID is valid
      NS_ASSERT (tid < 8);
      m_edca[QosUtilsMapTidToAc (tid)]->Queue (packet, hdr);
    }
  else
    {
      m_dca->Queue (packet, hdr);
    }
}

void
ApWifiMacBeac::Enqueue (Ptr<const Packet> packet, Mac48Address to, Mac48Address from)
{
  NS_LOG_FUNCTION (this << packet << to << from);
  if (to.IsBroadcast () || m_stationManager->IsAssociated (to))
    {
      ForwardDown (packet, from, to);
    }
}

void
ApWifiMacBeac::Enqueue (Ptr<const Packet> packet, Mac48Address to)
{
  NS_LOG_FUNCTION (this << packet << to);
  //We're sending this packet with a from address that is our own. We
  //get that address from the lower MAC and make use of the
  //from-spoofing Enqueue() method to avoid duplicated code.
  Enqueue (packet, to, m_low->GetAddress ());
}

bool
ApWifiMacBeac::SupportsSendFrom (void) const
{
  NS_LOG_FUNCTION (this);
  return true;
}

SupportedRates
ApWifiMacBeac::GetSupportedRates (void) const
{
  NS_LOG_FUNCTION (this);
  SupportedRates rates;
  //If it is an HT-AP or VHT-AP, then add the BSSMembershipSelectorSet
  //The standard says that the BSSMembershipSelectorSet
  //must have its MSB set to 1 (must be treated as a Basic Rate)
  //Also the standard mentioned that at least 1 element should be included in the SupportedRates the rest can be in the ExtendedSupportedRates
  if (m_htSupported || m_vhtSupported)
    {
      for (uint32_t i = 0; i < m_phy->GetNBssMembershipSelectors (); i++)
        {
          rates.AddBssMembershipSelectorRate (m_phy->GetBssMembershipSelector (i));
        }
    }
  // 
  uint8_t nss = 1;  // Number of spatial streams is 1 for non-MIMO modes
  //Send the set of supported rates and make sure that we indicate
  //the Basic Rate set in this set of supported rates.
  for (uint32_t i = 0; i < m_phy->GetNModes (); i++)
    {
      WifiMode mode = m_phy->GetMode (i);
      uint64_t modeDataRate = mode.GetDataRate (m_phy->GetChannelWidth (), false, nss);
      NS_LOG_DEBUG ("Adding supported rate of " << modeDataRate);
      rates.AddSupportedRate (modeDataRate);
      //Add rates that are part of the BSSBasicRateSet (manufacturer dependent!)
      //here we choose to add the mandatory rates to the BSSBasicRateSet,
      //except for 802.11b where we assume that only the non HR-DSSS rates are part of the BSSBasicRateSet
      if (mode.IsMandatory () && (mode.GetModulationClass () != WIFI_MOD_CLASS_HR_DSSS))
        {
          NS_LOG_DEBUG ("Adding basic mode " << mode.GetUniqueName ());
          m_stationManager->AddBasicMode (mode);
        }
    }
  //set the basic rates
  for (uint32_t j = 0; j < m_stationManager->GetNBasicModes (); j++)
    {
      WifiMode mode = m_stationManager->GetBasicMode (j);
      uint64_t modeDataRate = mode.GetDataRate (m_phy->GetChannelWidth (), false, nss);
      NS_LOG_DEBUG ("Setting basic rate " << mode.GetUniqueName ());
      rates.SetBasicRate (modeDataRate);
    }

  return rates;
}

DsssParameterSet
ApWifiMacBeac::GetDsssParameterSet (void) const
{
  DsssParameterSet dsssParameters;
  if (m_dsssSupported)
    {
      dsssParameters.SetDsssSupported (1);
      dsssParameters.SetCurrentChannel (m_phy->GetChannelNumber ());
    }
  return dsssParameters;
}

CapabilityInformation
ApWifiMacBeac::GetCapabilities (void) const
{
  CapabilityInformation capabilities;
  capabilities.SetShortPreamble (GetShortPreambleEnabled ());
  capabilities.SetShortSlotTime (GetShortSlotTimeEnabled ());
  return capabilities;
}

ErpInformation
ApWifiMacBeac::GetErpInformation (void) const
{
  ErpInformation information;
  information.SetErpSupported (1);
  if (m_erpSupported)
    {
      information.SetNonErpPresent (!m_nonErpStations.empty ());
      information.SetUseProtection (GetUseNonErpProtection ());
      if (GetShortPreambleEnabled ())
        {
          information.SetBarkerPreambleMode (0);
        }
      else
        {
          information.SetBarkerPreambleMode (1);
        }
    }
  return information;
}

EdcaParameterSet
ApWifiMacBeac::GetEdcaParameterSet (void) const
{
  EdcaParameterSet edcaParameters;
  edcaParameters.SetQosSupported (1);
  if (m_qosSupported)
    {
      Ptr<EdcaTxopN> edca;
      Time txopLimit;

      edca = m_edca.find (AC_BE)->second;
      txopLimit = edca->GetTxopLimit ();
      edcaParameters.SetBeAci(0);
      edcaParameters.SetBeCWmin(edca->GetMinCw ());
      edcaParameters.SetBeCWmax(edca->GetMaxCw ());
      edcaParameters.SetBeAifsn(edca->GetAifsn ());
      edcaParameters.SetBeTXOPLimit(txopLimit.GetMicroSeconds () / 32);
      
      edca = m_edca.find (AC_BK)->second;
      txopLimit = edca->GetTxopLimit ();
      edcaParameters.SetBkAci(1);
      edcaParameters.SetBkCWmin(edca->GetMinCw ());
      edcaParameters.SetBkCWmax(edca->GetMaxCw ());
      edcaParameters.SetBkAifsn(edca->GetAifsn ());
      edcaParameters.SetBkTXOPLimit(txopLimit.GetMicroSeconds () / 32);
      
      edca = m_edca.find (AC_VI)->second;
      txopLimit = edca->GetTxopLimit ();
      edcaParameters.SetViAci(2);
      edcaParameters.SetViCWmin(edca->GetMinCw ());
      edcaParameters.SetViCWmax(edca->GetMaxCw ());
      edcaParameters.SetViAifsn(edca->GetAifsn ());
      edcaParameters.SetViTXOPLimit(txopLimit.GetMicroSeconds () / 32);
      
      edca = m_edca.find (AC_VO)->second;
      txopLimit = edca->GetTxopLimit ();
      edcaParameters.SetVoAci(3);
      edcaParameters.SetVoCWmin(edca->GetMinCw ());
      edcaParameters.SetVoCWmax(edca->GetMaxCw ());
      edcaParameters.SetVoAifsn(edca->GetAifsn ());
      edcaParameters.SetVoTXOPLimit(txopLimit.GetMicroSeconds () / 32);
    }
  return edcaParameters;
}

HtOperations
ApWifiMacBeac::GetHtOperations (void) const
{
  HtOperations operations;
  operations.SetHtSupported (1);
  if (m_htSupported)
    {
      if (!m_nonHtStations.empty ())
        {
          operations.SetHtProtection (MIXED_MODE_PROTECTION);
        }
      else
        {
          operations.SetHtProtection (NO_PROTECTION);
        }
    }
  return operations;
}

void
ApWifiMacBeac::SendProbeResp (Mac48Address to)
{
  NS_LOG_FUNCTION (this << to);
  WifiMacHeader hdr;
  hdr.SetProbeResp ();
  hdr.SetAddr1 (to);
  hdr.SetAddr2 (GetAddress ());
  hdr.SetAddr3 (GetAddress ());
  hdr.SetDsNotFrom ();
  hdr.SetDsNotTo ();
  Ptr<Packet> packet = Create<Packet> ();
  MgtProbeResponseHeader probe;
  probe.SetSsid (GetSsid ());
  probe.SetSupportedRates (GetSupportedRates ());
  probe.SetBeaconIntervalUs (m_beaconInterval.GetMicroSeconds ());
  probe.SetCapabilities (GetCapabilities ());
  m_stationManager->SetShortPreambleEnabled (GetShortPreambleEnabled ());
  m_stationManager->SetShortSlotTimeEnabled (GetShortSlotTimeEnabled ());
  if (m_dsssSupported)
    {
      probe.SetDsssParameterSet (GetDsssParameterSet ());
    }
  if (m_erpSupported)
    {
      probe.SetErpInformation (GetErpInformation ());
    }
  if (m_qosSupported)
    {
      probe.SetEdcaParameterSet (GetEdcaParameterSet ());
    }
  if (m_htSupported || m_vhtSupported)
    {
      probe.SetHtCapabilities (GetHtCapabilities ());
      probe.SetHtOperations (GetHtOperations ());
      hdr.SetNoOrder ();
    }
  if (m_vhtSupported)
    {
      probe.SetVhtCapabilities (GetVhtCapabilities ());
    }
  packet->AddHeader (probe);

  //The standard is not clear on the correct queue for management
  //frames if we are a QoS AP. The approach taken here is to always
  //use the DCF for these regardless of whether we have a QoS
  //association or not.
  m_dca->Queue (packet, hdr);
}

void
ApWifiMacBeac::SendAssocResp (Mac48Address to, bool success)
{
  NS_LOG_FUNCTION (this << to << success);
  WifiMacHeader hdr;
  hdr.SetAssocResp ();
  hdr.SetAddr1 (to);
  hdr.SetAddr2 (GetAddress ());
  hdr.SetAddr3 (GetAddress ());
  hdr.SetDsNotFrom ();
  hdr.SetDsNotTo ();
  Ptr<Packet> packet = Create<Packet> ();
  MgtAssocResponseHeader assoc;
  StatusCode code;

  m_activeNetwork++;
  if (success)
    {
      code.SetSuccess ();
      m_staList.push_back (to);
    }
  else
    {
      code.SetFailure ();
    }
  assoc.SetSupportedRates (GetSupportedRates ());
  assoc.SetStatusCode (code);
  assoc.SetCapabilities (GetCapabilities ());
  if (m_erpSupported)
    {
      assoc.SetErpInformation (GetErpInformation ());
    }
  if (m_qosSupported)
    {
      assoc.SetEdcaParameterSet (GetEdcaParameterSet ());
    }
  if (m_htSupported || m_vhtSupported)
    {
      assoc.SetHtCapabilities (GetHtCapabilities ());
      assoc.SetHtOperations (GetHtOperations ());
      hdr.SetNoOrder ();
    }
  if (m_vhtSupported)
    {
      assoc.SetVhtCapabilities (GetVhtCapabilities ());
    }
  packet->AddHeader (assoc);

  //The standard is not clear on the correct queue for management
  //frames if we are a QoS AP. The approach taken here is to always
  //use the DCF for these regardless of whether we have a QoS
  //association or not.
  m_dca->Queue (packet, hdr);
}

void
ApWifiMacBeac::SendOneBeacon (void)
{
  NS_LOG_FUNCTION (this);
  WifiMacHeader hdr;
  hdr.SetBeacon ();
  hdr.SetAddr1 (Mac48Address::GetBroadcast ());
  hdr.SetAddr2 (GetAddress ());
  hdr.SetAddr3 (GetAddress ());
  hdr.SetDsNotFrom ();
  hdr.SetDsNotTo ();
  Ptr<Packet> packet = Create<Packet> ();
  MgtBeaconHeader beacon;
  beacon.SetSsid (GetSsid ());
  beacon.SetSupportedRates (GetSupportedRates ());
  beacon.SetBeaconIntervalUs (m_beaconInterval.GetMicroSeconds ());
  beacon.SetCapabilities (GetCapabilities ());
  m_stationManager->SetShortPreambleEnabled (GetShortPreambleEnabled ());
  m_stationManager->SetShortSlotTimeEnabled (GetShortSlotTimeEnabled ());
  if (m_dsssSupported)
    {
      beacon.SetDsssParameterSet (GetDsssParameterSet ());
    }
  if (m_erpSupported)
    {
      beacon.SetErpInformation (GetErpInformation ());
    }
  if (m_qosSupported)
    {
      beacon.SetEdcaParameterSet (GetEdcaParameterSet ());
    }
  if (m_htSupported || m_vhtSupported)
    {
      beacon.SetHtCapabilities (GetHtCapabilities ());
      beacon.SetHtOperations (GetHtOperations ());
      hdr.SetNoOrder ();
    }
  if (m_vhtSupported)
    {
      beacon.SetVhtCapabilities (GetVhtCapabilities ());
    }
  packet->AddHeader (beacon);

  //The beacon has it's own special queue, so we load it in there
  m_beaconDca->Queue (packet, hdr);

  //Increase the beacon interval if the network is inactive
  if ( (m_activeNetwork <= m_activeNetworkPrevious) && (m_beaconInterval <= m_maxBeaconInterval) )
    m_beaconInterval = (m_beaconInterval+m_maxBeaconInterval)/2;

  //Reduce the beacon interval if the network is active
  if ( (m_activeNetwork > m_activeNetworkPrevious) && (m_beaconInterval >= m_minBeaconInterval) )
    m_beaconInterval = (m_beaconInterval+m_minBeaconInterval)/2;
  
  //Update beacon based on network activity (people joining the network and/or moving around)
  std::cout << m_beaconInterval << " activeNetwork ="<< m_activeNetwork << std::endl;

  //Save mobility count for later use and reset motility counter
  m_activeNetworkPrevious = m_activeNetwork;
  m_activeNetwork = 0;

  m_beaconEvent = Simulator::Schedule (m_beaconInterval, &ApWifiMacBeac::SendOneBeacon, this);
  
  //If a STA that does not support Short Slot Time associates,
  //the AP shall use long slot time beginning at the first Beacon
  //subsequent to the association of the long slot time STA.
  if (m_erpSupported)
    {
    if (GetShortSlotTimeEnabled () == true)
      {
        //Enable short slot time
        SetSlot (MicroSeconds (9));
      }
    else
      {
        //Disable short slot time
        SetSlot (MicroSeconds (20));
      }
    }
}

void
ApWifiMacBeac::TxOk (const WifiMacHeader &hdr)
{
  NS_LOG_FUNCTION (this);
  RegularWifiMac::TxOk (hdr);

  if (hdr.IsAssocResp ()
      && m_stationManager->IsWaitAssocTxOk (hdr.GetAddr1 ()))
    {
      NS_LOG_DEBUG ("associated with sta=" << hdr.GetAddr1 ());
      m_stationManager->RecordGotAssocTxOk (hdr.GetAddr1 ());
    }
}

void
ApWifiMacBeac::TxFailed (const WifiMacHeader &hdr)
{
  NS_LOG_FUNCTION (this);
  RegularWifiMac::TxFailed (hdr);

  if (hdr.IsAssocResp ()
      && m_stationManager->IsWaitAssocTxOk (hdr.GetAddr1 ()))
    {
      NS_LOG_DEBUG ("assoc failed with sta=" << hdr.GetAddr1 ());
      m_stationManager->RecordGotAssocTxFailed (hdr.GetAddr1 ());
    }
}

inline void eraseMac48Address(std::list<Mac48Address> list, Mac48Address val)
{
  for (std::list<Mac48Address>::iterator j = list.begin (); j != list.end (); j++)
  {
    if ((*j) == val)
    {
      list.erase (j);
      break;
    }
  }
}

void
ApWifiMacBeac::Receive (Ptr<Packet> packet, const WifiMacHeader *hdr)
{
  NS_LOG_FUNCTION (this << packet << hdr);

  Mac48Address from = hdr->GetAddr2 ();

  if (hdr->IsData ())
    {
      Mac48Address bssid = hdr->GetAddr1 ();
      if (!hdr->IsFromDs ()
          && hdr->IsToDs ()
          && bssid == GetAddress ()
          && m_stationManager->IsAssociated (from))
        {
          Mac48Address to = hdr->GetAddr3 ();
          if (to == GetAddress ())
            {
              NS_LOG_DEBUG ("frame for me from=" << from);
              if (hdr->IsQosData ())
                {
                  if (hdr->IsQosAmsdu ())
                    {
                      NS_LOG_DEBUG ("Received A-MSDU from=" << from << ", size=" << packet->GetSize ());
                      DeaggregateAmsduAndForward (packet, hdr);
                      packet = 0;
                    }
                  else
                    {
                      ForwardUp (packet, from, bssid);
                    }
                }
              else
                {
                  ForwardUp (packet, from, bssid);
                }
            }
          else if (to.IsGroup ()
                   || m_stationManager->IsAssociated (to))
            {
              NS_LOG_DEBUG ("forwarding frame from=" << from << ", to=" << to);
              Ptr<Packet> copy = packet->Copy ();

              //If the frame we are forwarding is of type QoS Data,
              //then we need to preserve the UP in the QoS control
              //header...
              if (hdr->IsQosData ())
                {
                  ForwardDown (packet, from, to, hdr->GetQosTid ());
                }
              else
                {
                  ForwardDown (packet, from, to);
                }
              ForwardUp (copy, from, to);
            }
          else
            {
              ForwardUp (packet, from, to);
            }
        }
      else if (hdr->IsFromDs ()
               && hdr->IsToDs ())
        {
          //this is an AP-to-AP frame
          //we ignore for now.
          NotifyRxDrop (packet);
        }
      else
        {
          //we can ignore these frames since
          //they are not targeted at the AP
          NotifyRxDrop (packet);
        }
      return;
    }
  else if (hdr->IsMgt ())
    {
      if (hdr->IsProbeReq ())
        {
          NS_ASSERT (hdr->GetAddr1 ().IsBroadcast ());
          SendProbeResp (from);
          return;
        }
      else if (hdr->GetAddr1 () == GetAddress ())
        {
          if (hdr->IsAssocReq ())
            {
              //first, verify that the the station's supported
              //rate set is compatible with our Basic Rate set
              MgtAssocRequestHeader assocReq;
              packet->RemoveHeader (assocReq);
              CapabilityInformation capabilities = assocReq.GetCapabilities ();
              m_stationManager->AddSupportedPlcpPreamble (from, capabilities.IsShortPreamble ());
              SupportedRates rates = assocReq.GetSupportedRates ();
              bool problem = false;
              bool isHtStation = false;
              bool isOfdmStation = false;
              bool isErpStation = false;
              bool isDsssStation = false;
              for (uint32_t i = 0; i < m_stationManager->GetNBasicModes (); i++)
                {
                  WifiMode mode = m_stationManager->GetBasicMode (i);
                  uint8_t nss = 1; // Assume 1 spatial stream in basic mode
                  if (!rates.IsSupportedRate (mode.GetDataRate (m_phy->GetChannelWidth (), false, nss)))
                    {
                      if ((mode.GetModulationClass () == WIFI_MOD_CLASS_DSSS) || (mode.GetModulationClass () == WIFI_MOD_CLASS_HR_DSSS))
                        {
                          isDsssStation = false;
                        }
                      else if (mode.GetModulationClass () == WIFI_MOD_CLASS_ERP_OFDM)
                        {
                          isErpStation = false;
                        }
                      else if (mode.GetModulationClass () == WIFI_MOD_CLASS_OFDM)
                        {
                          isOfdmStation = false;
                        }
                      if (isDsssStation == false && isErpStation == false && isOfdmStation == false)
                        {
                          problem = true;
                          break;
                        }
                    }
                  else
                    {
                      if ((mode.GetModulationClass () == WIFI_MOD_CLASS_DSSS) || (mode.GetModulationClass () == WIFI_MOD_CLASS_HR_DSSS))
                        {
                          isDsssStation = true;
                        }
                      else if (mode.GetModulationClass () == WIFI_MOD_CLASS_ERP_OFDM)
                        {
                          isErpStation = true;
                        }
                      else if (mode.GetModulationClass () == WIFI_MOD_CLASS_OFDM)
                        {
                          isOfdmStation = true;
                        }
                    }
                }
              m_stationManager->AddSupportedErpSlotTime (from, capabilities.IsShortSlotTime () && isErpStation);
              if (m_htSupported)
                {
                  //check whether the HT STA supports all MCSs in Basic MCS Set
                  HtCapabilities htcapabilities = assocReq.GetHtCapabilities ();
                  if (htcapabilities.GetHtCapabilitiesInfo () != 0)
                    {
                      isHtStation = true;
                      for (uint32_t i = 0; i < m_stationManager->GetNBasicMcs (); i++)
                        {
                          WifiMode mcs = m_stationManager->GetBasicMcs (i);
                          if (!htcapabilities.IsSupportedMcs (mcs.GetMcsValue ()))
                            {
                              problem = true;
                              break;
                            }
                        }
                    }
                }
              if (m_vhtSupported)
                {
                  //check whether the VHT STA supports all MCSs in Basic MCS Set
                  VhtCapabilities vhtcapabilities = assocReq.GetVhtCapabilities ();
                  if (vhtcapabilities.GetVhtCapabilitiesInfo () != 0)
                    {
                      for (uint32_t i = 0; i < m_stationManager->GetNBasicMcs (); i++)
                        {
                          WifiMode mcs = m_stationManager->GetBasicMcs (i);
                          if (!vhtcapabilities.IsSupportedTxMcs (mcs.GetMcsValue ()))
                            {
                              problem = true;
                              break;
                            }
                        }
                    }
                }
              if (problem)
                {
                  //One of the Basic Rate set mode is not
                  //supported by the station. So, we return an assoc
                  //response with an error status.
                  SendAssocResp (hdr->GetAddr2 (), false);
                }
              else
                {
                  //station supports all rates in Basic Rate Set.
                  //record all its supported modes in its associated WifiRemoteStation
                  for (uint32_t j = 0; j < m_phy->GetNModes (); j++)
                    {
                      WifiMode mode = m_phy->GetMode (j);
                      uint8_t nss = 1; // Assume 1 spatial stream in basic mode
                      if (rates.IsSupportedRate (mode.GetDataRate (m_phy->GetChannelWidth (), false, nss)))
                        {
                          m_stationManager->AddSupportedMode (from, mode);
                        }
                    }
                  if (m_htSupported)
                    {
                      HtCapabilities htcapabilities = assocReq.GetHtCapabilities ();
                      m_stationManager->AddStationHtCapabilities (from, htcapabilities);
                      for (uint32_t j = 0; j < m_phy->GetNMcs (); j++)
                        {
                          WifiMode mcs = m_phy->GetMcs (j);
                          if (mcs.GetModulationClass () == WIFI_MOD_CLASS_HT && htcapabilities.IsSupportedMcs (mcs.GetMcsValue ()))
                            {
                              m_stationManager->AddSupportedMcs (from, mcs);
                            }
                        }
                    }
                  if (m_vhtSupported)
                    {
                      VhtCapabilities vhtCapabilities = assocReq.GetVhtCapabilities ();
                      m_stationManager->AddStationVhtCapabilities (from, vhtCapabilities);
                      for (uint32_t i = 0; i < m_phy->GetNMcs (); i++)
                        {
                          WifiMode mcs = m_phy->GetMcs (i);
                          if (mcs.GetModulationClass () == WIFI_MOD_CLASS_VHT && vhtCapabilities.IsSupportedTxMcs (mcs.GetMcsValue ()))
                            {
                              m_stationManager->AddSupportedMcs (hdr->GetAddr2 (), mcs);
                              //here should add a control to add basic MCS when it is implemented
                            }
                        }
                    }
                  m_stationManager->RecordWaitAssocTxOk (from);
                  if (!isHtStation)
                    {
                      m_nonHtStations.push_back (hdr->GetAddr2 ());
                    }
                  if (!isErpStation && isDsssStation)
                    {
                      m_nonErpStations.push_back (hdr->GetAddr2 ());
                    }
                  // send assoc response with success status.
                  SendAssocResp (hdr->GetAddr2 (), true);
                }
              return;
            }
          else if (hdr->IsDisassociation ())
            {
              m_stationManager->RecordDisassociated (from);
              eraseMac48Address(m_staList, from);
              eraseMac48Address(m_nonErpStations, from);
              eraseMac48Address(m_nonHtStations, from);
              return;
            }
        }
    }

  //Invoke the receive handler of our parent class to deal with any
  //other frames. Specifically, this will handle Block Ack-related
  //Management Action frames.
  RegularWifiMac::Receive (packet, hdr);
}


void
ApWifiMacBeac::DeaggregateAmsduAndForward (Ptr<Packet> aggregatedPacket,
                                       const WifiMacHeader *hdr)
{
  NS_LOG_FUNCTION (this << aggregatedPacket << hdr);
  MsduAggregator::DeaggregatedMsdus packets =
    MsduAggregator::Deaggregate (aggregatedPacket);

  for (MsduAggregator::DeaggregatedMsdusCI i = packets.begin ();
       i != packets.end (); ++i)
    {
      if ((*i).second.GetDestinationAddr () == GetAddress ())
        {
          ForwardUp ((*i).first, (*i).second.GetSourceAddr (),
                     (*i).second.GetDestinationAddr ());
        }
      else
        {
          Mac48Address from = (*i).second.GetSourceAddr ();
          Mac48Address to = (*i).second.GetDestinationAddr ();
          NS_LOG_DEBUG ("forwarding QoS frame from=" << from << ", to=" << to);
          ForwardDown ((*i).first, from, to, hdr->GetQosTid ());
        }
    }
}

void
ApWifiMacBeac::DoInitialize (void)
{
  NS_LOG_FUNCTION (this);
  m_beaconDca->Initialize ();
  m_beaconEvent.Cancel ();
  m_activeNetwork = false;
  if (m_enableBeaconGeneration)
    {
      if (m_enableBeaconJitter)
        {
          int64_t jitter = m_beaconJitter->GetValue (0, m_beaconInterval.GetMicroSeconds ());
          NS_LOG_DEBUG ("Scheduling initial beacon for access point " << GetAddress () << " at time " << jitter << " microseconds");
          m_beaconEvent = Simulator::Schedule (MicroSeconds (jitter), &ApWifiMacBeac::SendOneBeacon, this);
        }
      else
        {
          NS_LOG_DEBUG ("Scheduling initial beacon for access point " << GetAddress () << " at time 0");
          m_beaconEvent = Simulator::ScheduleNow (&ApWifiMacBeac::SendOneBeacon, this);
        }
    }
  RegularWifiMac::DoInitialize ();
}

bool
ApWifiMacBeac::GetUseNonErpProtection (void) const
{
  bool useProtection = !m_nonErpStations.empty () && m_enableNonErpProtection;
  m_stationManager->SetUseNonErpProtection (useProtection);
  return useProtection;
}

} //namespace ns3
