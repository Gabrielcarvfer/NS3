
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

#include <cstdlib>
#include <ns3/ap-wifi-mac.h>

#include "ap-wifi-mac.h"
#include "ns3/log.h"
#include "ns3/simulator.h"
#include "ns3/string.h"
#include "ns3/pointer.h"
#include "ns3/mac-low.h"
#include "ns3/mac-tx-middle.h"

namespace ns3 {

    NS_LOG_COMPONENT_DEFINE ("ApWifiMac");

    NS_OBJECT_ENSURE_REGISTERED (ApWifiMac);

    TypeId
    ApWifiMac::GetTypeId (void)
    {
        static TypeId tid = TypeId ("ns3::ApWifiMac")
                .SetParent<RegularWifiMac> ()
                .SetGroupName ("Wifi")
                .AddConstructor<ApWifiMac> ()
                .AddAttribute ("BeaconInterval",
                               "Delay between two beacons",
                               TimeValue (MicroSeconds (102400)),
                               MakeTimeAccessor (&ApWifiMac::GetBeaconInterval,
                                                 &ApWifiMac::SetBeaconInterval),
                               MakeTimeChecker ())
                .AddAttribute ("BeaconJitter",
                               "A uniform random variable to cause the initial beacon starting time (after simulation time 0) "
                                       "to be distributed between 0 and the BeaconInterval.",
                               StringValue ("ns3::UniformRandomVariable"),
                               MakePointerAccessor (&ApWifiMac::m_beaconJitter),
                               MakePointerChecker<UniformRandomVariable> ())
                .AddAttribute ("EnableBeaconJitter",
                               "If beacons are enabled, whether to jitter the initial send event.",
                               BooleanValue (true),
                               MakeBooleanAccessor (&ApWifiMac::m_enableBeaconJitter),
                               MakeBooleanChecker ())
                .AddAttribute ("BeaconGeneration",
                               "Whether or not beacons are generated.",
                               BooleanValue (true),
                               MakeBooleanAccessor (&ApWifiMac::SetBeaconGeneration,
                                                    &ApWifiMac::GetBeaconGeneration),
                               MakeBooleanChecker ())
                .AddAttribute ("MaxBeaconInterval",
                               "MaxDelay between two beacons",
                               TimeValue (MicroSeconds (102400)),
                               MakeTimeAccessor (&ApWifiMac::GetMaxBeaconInterval,
                                                 &ApWifiMac::SetMaxBeaconInterval),
                               MakeTimeChecker ())
                .AddAttribute ("MinBeaconInterval",
                               "MinDelay between two beacons",
                               TimeValue (MicroSeconds (102400)),
                               MakeTimeAccessor (&ApWifiMac::GetMinBeaconInterval,
                                                 &ApWifiMac::SetMinBeaconInterval),
                               MakeTimeChecker ())
                .AddAttribute ("EnableNonErpProtection", "Whether or not protection mechanism should be used when non-ERP STAs are present within the BSS."
                                       "This parameter is only used when ERP is supported by the AP.",
                               BooleanValue (true),
                               MakeBooleanAccessor (&ApWifiMac::m_enableNonErpProtection),
                               MakeBooleanChecker ())
                .AddAttribute ("RifsMode", "If non-HT STAs are detected, whether to force RIFS to be disabled within the BSS."
                                       "This parameter is only used when HT is supported by the AP.",
                               BooleanValue (true),
                               MakeBooleanAccessor (&ApWifiMac::m_disableRifs),
                               MakeBooleanChecker ())
                .AddAttribute ("EnableDynamicBeacon", "If set as true, the beacon interval is adjusted based on STA distances",
                               BooleanValue(true),
                               MakeBooleanAccessor(&ApWifiMac::dynamicBeaconEnabled),
                               MakeBooleanChecker())
                .AddAttribute ("DynamicBeaconAdjustment", "If set as true, trickle beacon interval is enabled. Otherwise, dynamic",
                               BooleanValue(true),
                               MakeBooleanAccessor(&ApWifiMac::trickleEnabled),
                               MakeBooleanChecker())
                .AddAttribute ("ScanInterval", "Interval between motility scans (ms)",
                               UintegerValue(10),
                               MakeUintegerAccessor(&ApWifiMac::scan_interval),
                               MakeUintegerChecker<uint>())
                .AddAttribute ("InterestRadius", "Percentile of radius that is going to be checked for movement",
                               DoubleValue(0.75),
                               MakeDoubleAccessor(&ApWifiMac::interest_radius),
                               MakeDoubleChecker<double>())
        ;
        return tid;
    }

    ApWifiMac::ApWifiMac ()
            //: m_enableBeaconGeneration (false)
    {
        NS_LOG_FUNCTION (this);
        m_beaconDca = CreateObject<DcaTxop> ();
        m_beaconDca->SetAifsn (1);
        m_beaconDca->SetMinCw (0);
        m_beaconDca->SetMaxCw (0);
        m_beaconDca->SetLow (m_low);
        m_low->SetRegisterSampleCallback(MakeCallback(&ApWifiMac::RegisterSample, this));

        scan_interval = 10;
        m_low->ap = true;
        average_sta_distance_deviation = 0.0;
        average_sta_distance = 0.0;
        min_known_distance = 10000000.0;
        max_known_distance = 0.0;

        m_beaconDca->SetManager (m_dcfManager);
        m_beaconDca->SetTxMiddle (m_txMiddle);
        m_enableBeaconGeneration = false;
        samples.clear();

        //samples = std::map<Mac48Address, STA_samples>();

        //Let the lower layers know that we are acting as an AP.
        SetTypeOfStation (AP);
    }

    ApWifiMac::~ApWifiMac ()
    {
        NS_LOG_FUNCTION (this);
        m_staList.clear ();
        m_nonErpStations.clear ();
        m_nonHtStations.clear ();
        m_staAtRange.clear();
        samples.clear();
        Simulator::Cancel(m_motilityIntervalEvent);
        Simulator::Cancel(m_TrickleIntervalEvent);
        Simulator::Cancel(m_beaconEvent);


    }

    void
    ApWifiMac::DoDispose ()
    {
        NS_LOG_FUNCTION (this);
        m_beaconDca->Dispose ();
        m_beaconDca = 0;
        m_enableBeaconGeneration = false;
        m_beaconEvent.Cancel ();
        RegularWifiMac::DoDispose ();
    }

    void
    ApWifiMac::SetAddress (Mac48Address address)
    {
        NS_LOG_FUNCTION (this << address);
        //As an AP, our MAC address is also the BSSID. Hence we are
        //overriding this function and setting both in our parent class.
        RegularWifiMac::SetAddress (address);
        RegularWifiMac::SetBssid (address);
    }

    void
    ApWifiMac::SetBeaconGeneration (bool enable)
    {
        NS_LOG_FUNCTION (this << enable);
        if (!enable)
        {
            m_beaconEvent.Cancel ();
        }
        else if (enable && !m_enableBeaconGeneration)
        {
            m_beaconEvent = Simulator::ScheduleNow (&ApWifiMac::SendOneBeacon, this);
        }
        m_enableBeaconGeneration = enable;
    }

    bool
    ApWifiMac::GetBeaconGeneration (void) const
    {
        NS_LOG_FUNCTION (this);
        return m_enableBeaconGeneration;
    }

    Time
    ApWifiMac::GetBeaconInterval (void) const
    {
        NS_LOG_FUNCTION (this);
        return m_beaconInterval;
    }

    Time
    ApWifiMac::GetMaxBeaconInterval (void) const
    {
        NS_LOG_FUNCTION (this);
        return m_maxBeaconInterval;
    }

    Time
    ApWifiMac::GetMinBeaconInterval (void) const
    {
        NS_LOG_FUNCTION (this);
        return m_minBeaconInterval;
    }
    

    void
    ApWifiMac::SetWifiRemoteStationManager (const Ptr<WifiRemoteStationManager> stationManager)
    {
        NS_LOG_FUNCTION (this << stationManager);
        m_beaconDca->SetWifiRemoteStationManager (stationManager);
        RegularWifiMac::SetWifiRemoteStationManager (stationManager);
    }

    void
    ApWifiMac::SetLinkUpCallback (Callback<void> linkUp)
    {
        NS_LOG_FUNCTION (this << &linkUp);
        RegularWifiMac::SetLinkUpCallback (linkUp);

        //The approach taken here is that, from the point of view of an AP,
        //the link is always up, so we immediately invoke the callback if
        //one is set
        linkUp ();
    }

    void
    ApWifiMac::SetBeaconInterval (Time interval)
    {
        NS_LOG_FUNCTION (this << interval);
        if ((interval.GetMicroSeconds () % 1024) != 0)
        {
            NS_LOG_WARN ("beacon interval should be multiple of 1024us (802.11 time unit), see IEEE Std. 802.11-2012");
        }
        m_beaconInterval = interval;
    }
    void
    ApWifiMac::SetMaxBeaconInterval (Time interval)
    {
        NS_LOG_FUNCTION (this << interval);
        if ((interval.GetMicroSeconds () % 1024) != 0)
        {
            NS_LOG_WARN ("beacon interval should be multiple of 1024us (802.11 time unit), see IEEE Std. 802.11-2012");
        }
        m_maxBeaconInterval = interval;
    }

    void
    ApWifiMac::SetMinBeaconInterval (Time interval)
    {
        NS_LOG_FUNCTION (this << interval);
        if ((interval.GetMicroSeconds () % 1024) != 0)
        {
            NS_LOG_WARN ("beacon interval should be multiple of 1024us (802.11 time unit), see IEEE Std. 802.11-2012");
        }
        m_minBeaconInterval = interval;
    }
    
    void
    ApWifiMac::StartBeaconing (void)
    {
        NS_LOG_FUNCTION (this);
        SendOneBeacon ();
    }

    int64_t
    ApWifiMac::AssignStreams (int64_t stream)
    {
        NS_LOG_FUNCTION (this << stream);
        m_beaconJitter->SetStream (stream);
        return 1;
    }

    bool
    ApWifiMac::GetShortSlotTimeEnabled (void) const
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
    ApWifiMac::GetShortPreambleEnabled (void) const
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

    bool
    ApWifiMac::IsNonGfHtStasPresent (void) const
    {
        bool isNonGfHtStasPresent = false;
        for (std::list<Mac48Address>::const_iterator i = m_staList.begin (); i != m_staList.end (); i++)
        {
            if (m_stationManager->GetGreenfieldSupported (*i) == false)
            {
                isNonGfHtStasPresent = true;
                break;
            }
        }
        m_stationManager->SetUseGreenfieldProtection (isNonGfHtStasPresent);
        return isNonGfHtStasPresent;
    }

    uint8_t
    ApWifiMac::GetVhtOperationalChannelWidth (void) const
    {
        uint8_t channelWidth = m_phy->GetChannelWidth ();
        for (std::list<Mac48Address>::const_iterator i = m_staList.begin (); i != m_staList.end (); i++)
        {
            if (m_stationManager->GetVhtSupported (*i))
            {
                if (m_stationManager->GetChannelWidthSupported (*i) < channelWidth)
                {
                    channelWidth = m_stationManager->GetChannelWidthSupported (*i);
                }
            }
        }
        return channelWidth;
    }

    void
    ApWifiMac::ForwardDown (Ptr<const Packet> packet, Mac48Address from,
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
    ApWifiMac::ForwardDown (Ptr<const Packet> packet, Mac48Address from,
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

        if (m_htSupported || m_vhtSupported || m_heSupported)
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
    ApWifiMac::Enqueue (Ptr<const Packet> packet, Mac48Address to, Mac48Address from)
    {
        NS_LOG_FUNCTION (this << packet << to << from);
        if (to.IsBroadcast () || m_stationManager->IsAssociated (to))
        {
            ForwardDown (packet, from, to);
        }
        else
        {
            NotifyTxDrop (packet);
        }
    }

    void
    ApWifiMac::Enqueue (Ptr<const Packet> packet, Mac48Address to)
    {
        NS_LOG_FUNCTION (this << packet << to);
        //We're sending this packet with a from address that is our own. We
        //get that address from the lower MAC and make use of the
        //from-spoofing Enqueue() method to avoid duplicated code.
        Enqueue (packet, to, m_low->GetAddress ());
    }

    bool
    ApWifiMac::SupportsSendFrom (void) const
    {
        NS_LOG_FUNCTION (this);
        return true;
    }

    SupportedRates
    ApWifiMac::GetSupportedRates (void) const
    {
        NS_LOG_FUNCTION (this);
        SupportedRates rates;
        //If it is an HT-AP or VHT-AP or HE-AP, then add the BSSMembershipSelectorSet
        //The standard says that the BSSMembershipSelectorSet
        //must have its MSB set to 1 (must be treated as a Basic Rate)
        //Also the standard mentioned that at least 1 element should be included in the SupportedRates the rest can be in the ExtendedSupportedRates
        if (m_htSupported || m_vhtSupported || m_heSupported)
        {
            for (uint32_t i = 0; i < m_phy->GetNBssMembershipSelectors (); i++)
            {
                rates.AddBssMembershipSelectorRate (m_phy->GetBssMembershipSelector (i));
            }
        }
        //
        //Send the set of supported rates and make sure that we indicate
        //the Basic Rate set in this set of supported rates.
        for (uint32_t i = 0; i < m_phy->GetNModes (); i++)
        {
            WifiMode mode = m_phy->GetMode (i);
            uint64_t modeDataRate = mode.GetDataRate (m_phy->GetChannelWidth ());
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
            uint64_t modeDataRate = mode.GetDataRate (m_phy->GetChannelWidth ());
            NS_LOG_DEBUG ("Setting basic rate " << mode.GetUniqueName ());
            rates.SetBasicRate (modeDataRate);
        }

        return rates;
    }

    DsssParameterSet
    ApWifiMac::GetDsssParameterSet (void) const
    {
        NS_LOG_FUNCTION (this);
        DsssParameterSet dsssParameters;
        if (m_dsssSupported)
        {
            dsssParameters.SetDsssSupported (1);
            dsssParameters.SetCurrentChannel (m_phy->GetChannelNumber ());
        }
        return dsssParameters;
    }

    CapabilityInformation
    ApWifiMac::GetCapabilities (void) const
    {
        NS_LOG_FUNCTION (this);
        CapabilityInformation capabilities;
        capabilities.SetShortPreamble (GetShortPreambleEnabled ());
        capabilities.SetShortSlotTime (GetShortSlotTimeEnabled ());
        return capabilities;
    }

    ErpInformation
    ApWifiMac::GetErpInformation (void) const
    {
        NS_LOG_FUNCTION (this);
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
    ApWifiMac::GetEdcaParameterSet (void) const
    {
        NS_LOG_FUNCTION (this);
        EdcaParameterSet edcaParameters;
        if (m_qosSupported)
        {
            edcaParameters.SetQosSupported (1);
            Ptr<EdcaTxopN> edca;
            Time txopLimit;

            edca = m_edca.find (AC_BE)->second;
            txopLimit = edca->GetTxopLimit ();
            edcaParameters.SetBeAci (0);
            edcaParameters.SetBeCWmin (edca->GetMinCw ());
            edcaParameters.SetBeCWmax (edca->GetMaxCw ());
            edcaParameters.SetBeAifsn (edca->GetAifsn ());
            edcaParameters.SetBeTXOPLimit (txopLimit.GetMicroSeconds () / 32);

            edca = m_edca.find (AC_BK)->second;
            txopLimit = edca->GetTxopLimit ();
            edcaParameters.SetBkAci (1);
            edcaParameters.SetBkCWmin (edca->GetMinCw ());
            edcaParameters.SetBkCWmax (edca->GetMaxCw ());
            edcaParameters.SetBkAifsn (edca->GetAifsn ());
            edcaParameters.SetBkTXOPLimit (txopLimit.GetMicroSeconds () / 32);

            edca = m_edca.find (AC_VI)->second;
            txopLimit = edca->GetTxopLimit ();
            edcaParameters.SetViAci (2);
            edcaParameters.SetViCWmin (edca->GetMinCw ());
            edcaParameters.SetViCWmax (edca->GetMaxCw ());
            edcaParameters.SetViAifsn (edca->GetAifsn ());
            edcaParameters.SetViTXOPLimit (txopLimit.GetMicroSeconds () / 32);

            edca = m_edca.find (AC_VO)->second;
            txopLimit = edca->GetTxopLimit ();
            edcaParameters.SetVoAci (3);
            edcaParameters.SetVoCWmin (edca->GetMinCw ());
            edcaParameters.SetVoCWmax (edca->GetMaxCw ());
            edcaParameters.SetVoAifsn (edca->GetAifsn ());
            edcaParameters.SetVoTXOPLimit (txopLimit.GetMicroSeconds () / 32);
        }
        return edcaParameters;
    }

    HtOperation
    ApWifiMac::GetHtOperation (void) const
    {
        NS_LOG_FUNCTION (this);
        HtOperation operation;
        if (m_htSupported)
        {
            operation.SetHtSupported (1);
            operation.SetRifsMode (GetRifsMode ());
            operation.SetNonGfHtStasPresent (IsNonGfHtStasPresent ());
            if (m_nonHtStations.empty ())
            {
                operation.SetHtProtection (NO_PROTECTION);
            }
            else
            {
                operation.SetHtProtection (MIXED_MODE_PROTECTION);
            }
        }
        return operation;
    }

    VhtOperation
    ApWifiMac::GetVhtOperation (void) const
    {
        NS_LOG_FUNCTION (this);
        VhtOperation operation;
        if (m_vhtSupported)
        {
            operation.SetVhtSupported (1);
            uint8_t channelWidth = GetVhtOperationalChannelWidth ();
            if (channelWidth == 160)
            {
                operation.SetChannelWidth (2);
            }
            else if (channelWidth == 80)
            {
                operation.SetChannelWidth (1);
            }
            else
            {
                operation.SetChannelWidth (0);
            }
            for (uint8_t nss = 1; nss <= 8; nss++)
            {
                uint8_t maxMcs;
                if (nss <= m_phy->GetMaxSupportedRxSpatialStreams ())
                {
                    maxMcs = 9; //TBD: hardcode to 9 for now since we assume all MCS values are supported
                }
                else
                {
                    maxMcs = 0;
                }
                operation.SetMaxVhtMcsPerNss (nss, maxMcs);
            }

        }
        return operation;
    }

    void
    ApWifiMac::SendProbeResp (Mac48Address to)
    {
        NS_LOG_FUNCTION (this << to);
        WifiMacHeader hdr;
        hdr.SetProbeResp ();
        hdr.SetAddr1 (to);
        hdr.SetAddr2 (GetAddress ());
        hdr.SetAddr3 (GetAddress ());
        hdr.SetDsNotFrom ();
        hdr.SetDsNotTo ();
        hdr.SetNoOrder ();
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
        if (m_htSupported || m_vhtSupported || m_heSupported)
        {
            probe.SetHtCapabilities (GetHtCapabilities ());
            probe.SetHtOperation (GetHtOperation ());
        }
        if (m_vhtSupported || m_heSupported)
        {
            probe.SetVhtCapabilities (GetVhtCapabilities ());
            probe.SetVhtOperation (GetVhtOperation ());
        }
        if (m_heSupported)
        {
            probe.SetHeCapabilities (GetHeCapabilities ());
        }
        packet->AddHeader (probe);

        //The standard is not clear on the correct queue for management
        //frames if we are a QoS AP. The approach taken here is to always
        //use the DCF for these regardless of whether we have a QoS
        //association or not.
        m_dca->Queue (packet, hdr);
    }

    void
    ApWifiMac::SendAssocResp (Mac48Address to, bool success)
    {
        NS_LOG_FUNCTION (this << to << success);
        WifiMacHeader hdr;
        hdr.SetAssocResp ();
        hdr.SetAddr1 (to);
        hdr.SetAddr2 (GetAddress ());
        hdr.SetAddr3 (GetAddress ());
        hdr.SetDsNotFrom ();
        hdr.SetDsNotTo ();
        hdr.SetNoOrder ();
        Ptr<Packet> packet = Create<Packet> ();
        MgtAssocResponseHeader assoc;
        StatusCode code;
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
        if (m_htSupported || m_vhtSupported || m_heSupported)
        {
            assoc.SetHtCapabilities (GetHtCapabilities ());
            assoc.SetHtOperation (GetHtOperation ());
        }
        if (m_vhtSupported || m_heSupported)
        {
            assoc.SetVhtCapabilities (GetVhtCapabilities ());
            assoc.SetVhtOperation (GetVhtOperation ());
        }
        if (m_heSupported)
        {
            assoc.SetHeCapabilities (GetHeCapabilities ());
        }
        packet->AddHeader (assoc);

        //The standard is not clear on the correct queue for management
        //frames if we are a QoS AP. The approach taken here is to always
        //use the DCF for these regardless of whether we have a QoS
        //association or not.
        m_dca->Queue (packet, hdr);
    }

    void
    ApWifiMac::SendOneBeacon (void) {
        NS_LOG_FUNCTION (this);
        WifiMacHeader hdr;
        hdr.SetBeacon();
        hdr.SetAddr1(Mac48Address::GetBroadcast());
        hdr.SetAddr2(this->GetAddress());
        hdr.SetAddr3(this->GetAddress());
        hdr.SetDsNotFrom();
        hdr.SetDsNotTo();
        hdr.SetNoOrder();
        Ptr<Packet> packet = Create<Packet>();
        MgtBeaconHeader beacon;
        beacon.SetSsid(GetSsid());
        beacon.SetSupportedRates(GetSupportedRates());
        beacon.SetBeaconIntervalUs(m_beaconInterval.GetMicroSeconds());
        beacon.SetCapabilities(GetCapabilities());
        m_stationManager->SetShortPreambleEnabled(GetShortPreambleEnabled());
        m_stationManager->SetShortSlotTimeEnabled(GetShortSlotTimeEnabled());
        if (m_dsssSupported) {
            beacon.SetDsssParameterSet(GetDsssParameterSet());
        }
        if (m_erpSupported) {
            beacon.SetErpInformation(GetErpInformation());
        }
        if (m_qosSupported) {
            beacon.SetEdcaParameterSet(GetEdcaParameterSet());
        }
        if (m_htSupported || m_vhtSupported) {
            beacon.SetHtCapabilities(GetHtCapabilities());
            beacon.SetHtOperation(GetHtOperation());
        }
        if (m_vhtSupported || m_heSupported) {
            beacon.SetVhtCapabilities(GetVhtCapabilities());
            beacon.SetVhtOperation(GetVhtOperation());
        }
        if (m_heSupported) {
            beacon.SetHeCapabilities(GetHeCapabilities());
        }
        packet->AddHeader(beacon);

        //The beacon has it's own special queue, so we load it in there
        m_beaconDca->Queue(packet, hdr);

        //std::cout << Simulator::Now()<< " " <<this->GetAddress() << " BeaconInterval: "<< m_beaconInterval<< std::endl;
        if (dynamicBeaconEnabled)
        {
            m_activeNetwork = false;

            switch (beaconAdjustType)
            {
                case (DYNAMIC_BEACON):
                    {
                        double tempInt = m_beaconInterval.GetInteger() * 2;
                        m_beaconInterval =
                            tempInt < m_maxBeaconInterval.GetInteger() ? NanoSeconds(tempInt) : m_maxBeaconInterval;

                    }
                    break;
                case (TRICKLE_BEACON):
                    break;
                default:
                    break;
            }
        }
        m_beaconEvent = Simulator::Schedule(m_beaconInterval, &ApWifiMac::SendOneBeacon, this);


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
    ApWifiMac::TxOk (const WifiMacHeader &hdr)
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
    ApWifiMac::TxFailed (const WifiMacHeader &hdr)
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

    void
    ApWifiMac::Receive (Ptr<Packet> packet, const WifiMacHeader *hdr)
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
                        if (!rates.IsSupportedRate (mode.GetDataRate (m_phy->GetChannelWidth ())))
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
                        if (htcapabilities.IsSupportedMcs (0))
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
                    if (m_heSupported)
                    {
                        //check whether the HE STA supports all MCSs in Basic MCS Set
                        HeCapabilities hecapabilities = assocReq.GetHeCapabilities ();
                        if (hecapabilities.GetSupportedMcsAndNss () != 0)
                        {
                            for (uint32_t i = 0; i < m_stationManager->GetNBasicMcs (); i++)
                            {
                                WifiMode mcs = m_stationManager->GetBasicMcs (i);
                                if (!hecapabilities.IsSupportedTxMcs (mcs.GetMcsValue ()))
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
                            if (rates.IsSupportedRate (mode.GetDataRate (m_phy->GetChannelWidth ())))
                            {
                                m_stationManager->AddSupportedMode (from, mode);
                            }
                        }
                        if (m_htSupported)
                        {
                            HtCapabilities htCapabilities = assocReq.GetHtCapabilities ();
                            if (htCapabilities.IsSupportedMcs (0))
                            {
                                m_stationManager->AddStationHtCapabilities (from, htCapabilities);
                                for (uint32_t j = 0; j < m_phy->GetNMcs (); j++)
                                {
                                    WifiMode mcs = m_phy->GetMcs (j);
                                    if (mcs.GetModulationClass () == WIFI_MOD_CLASS_HT && htCapabilities.IsSupportedMcs (mcs.GetMcsValue ()))
                                    {
                                        m_stationManager->AddSupportedMcs (from, mcs);
                                    }
                                }
                            }
                        }
                        if (m_vhtSupported)
                        {
                            VhtCapabilities vhtCapabilities = assocReq.GetVhtCapabilities ();
                            //we will always fill in RxHighestSupportedLgiDataRate field at TX, so this can be used to check whether it supports VHT
                            if (vhtCapabilities.GetRxHighestSupportedLgiDataRate () > 0)
                            {
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
                        }
                        if (m_heSupported)
                        {
                            HeCapabilities heCapabilities = assocReq.GetHeCapabilities ();
                            //todo: once we support non constant rate managers, we should add checks here whether HE is supported by the peer
                            m_stationManager->AddStationHeCapabilities (from, heCapabilities);
                            for (uint32_t i = 0; i < m_phy->GetNMcs (); i++)
                            {
                                WifiMode mcs = m_phy->GetMcs (i);
                                if (mcs.GetModulationClass () == WIFI_MOD_CLASS_HE && heCapabilities.IsSupportedTxMcs (mcs.GetMcsValue ()))
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
                    for (std::list<Mac48Address>::const_iterator i = m_staList.begin (); i != m_staList.end (); i++)
                    {
                        if ((*i) == from)
                        {
                            m_staList.erase (i);
                            break;
                        }
                    }
                    for (std::list<Mac48Address>::const_iterator j = m_nonErpStations.begin (); j != m_nonErpStations.end (); j++)
                    {
                        if ((*j) == from)
                        {
                            m_nonErpStations.erase (j);
                            break;
                        }
                    }
                    for (std::list<Mac48Address>::const_iterator j = m_nonHtStations.begin (); j != m_nonHtStations.end (); j++)
                    {
                        if ((*j) == from)
                        {
                            m_nonHtStations.erase (j);
                            break;
                        }
                    }
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
    ApWifiMac::DeaggregateAmsduAndForward (Ptr<Packet> aggregatedPacket,
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
    ApWifiMac::DoInitialize (void) {
        NS_LOG_FUNCTION (this);
        m_beaconDca->Initialize();
        m_beaconEvent.Cancel();
        if (m_enableBeaconGeneration) {
            if (m_enableBeaconJitter) {
                int64_t jitter = m_beaconJitter->GetValue(0, m_beaconInterval.GetMicroSeconds());
                NS_LOG_DEBUG ("Scheduling initial beacon for access point " << GetAddress() << " at time " << jitter
                                                                            << " microseconds");
                m_beaconEvent = Simulator::Schedule(MicroSeconds(jitter), &ApWifiMac::SendOneBeacon, this);
            } else {
                NS_LOG_DEBUG ("Scheduling initial beacon for access point " << GetAddress() << " at time 0");
                m_beaconEvent = Simulator::ScheduleNow(&ApWifiMac::SendOneBeacon, this);
            }
        }
        RegularWifiMac::DoInitialize();
        if (dynamicBeaconEnabled)
        {

            m_motilityIntervalEvent = Simulator::Schedule(MilliSeconds(scan_interval), &ApWifiMac::Motility, this);

        }
        if (dynamicBeaconEnabled && !trickleEnabled)
            beaconAdjustType = DYNAMIC_BEACON;
        if (trickleEnabled)
            beaconAdjustType = TRICKLE_BEACON;
        if (dynamicBeaconEnabled && beaconAdjustType == TRICKLE_BEACON)
            m_TrickleIntervalEvent = Simulator::Schedule(MilliSeconds(scan_interval), &ApWifiMac::Trickle, this);
    }

    bool
    ApWifiMac::GetUseNonErpProtection (void) const
    {
        bool useProtection = !m_nonErpStations.empty () && m_enableNonErpProtection;
        m_stationManager->SetUseNonErpProtection (useProtection);
        return useProtection;
    }

    bool
    ApWifiMac::GetRifsMode (void) const
    {
        bool rifsMode = false;
        if (m_htSupported && !m_vhtSupported) //RIFS mode is forbidden for VHT
        {
            if (m_nonHtStations.empty () || !m_disableRifs)
            {
                rifsMode = true;
            }
        }
        if (GetRifsSupported () && rifsMode)
        {
            m_stationManager->SetRifsPermitted (true);
        }
        else
        {
            m_stationManager->SetRifsPermitted (false);
        }
        return rifsMode;
    }



//Stuff for RSSI distance measurement
    double calculate_distance_RSSI(double rssi, double txpower)
    {
        //double dist = (10, (txpower - rssi) / (10 * 2));
        double dist = pow(10.0, (-20*log10(2400.0+(5000.0/1000.0)) - rssi + 27.55)/20);
        //if (std::isless(dist, 0.0001) || std::isgreater(dist, 1000))
        //    dist = 0.0;

        return dist;
    }


    void ApWifiMac::RegisterSample(Mac48Address from, double rssi, double txpower, Time timestamp)
    {
        //Collect STAs at range
        if (m_staAtRange.find(from) == m_staAtRange.end())
        {
            m_staAtRange.emplace(from, true);
        }

        if (!dynamicBeaconEnabled && beaconAdjustType==TRICKLE_BEACON)
        {
            bool registered = false;

            for (auto sta: m_staAtRange)
            {

                for (auto registeredSta: m_staList)
                {
                    registered = sta.first == registeredSta;
                    if (registered)
                        break;
                }
                if (registered)
                    break;
            }

            if (!registered)
            {
                 Time t = Simulator::GetDelayLeft(m_TrickleIntervalEvent);

                 m_beaconInterval = NanoSeconds(m_beaconInterval.GetInteger()/2);
                 m_beaconInterval = m_beaconInterval > m_minBeaconInterval ? m_beaconInterval : m_minBeaconInterval;

                 if ((t.GetInteger() - m_trickleBeaconInterval/2) >= 0)
                 {
                     m_activeNetwork = true;

                     Trickle();
                     Simulator::Cancel(m_beaconEvent);
                     m_beaconEvent = Simulator::Schedule(m_beaconInterval.GetInteger() < t.GetInteger() ?
                                                         m_beaconInterval : t, &ApWifiMac::SendOneBeacon, this);
                 }

                //std::cout << m_beaconInterval << std::endl;

            }
        }

        //Create STA info structure
        if (samples.find(from) == samples.end())
        {
            samples.emplace(from, STA_samples());
        }

        //Measure distance based on RSSI
        distance_sample sample = distance_sample(rssi, txpower, timestamp);

        if (sample.distance < 350.0)
        {
            (samples.at(from)).distance_samples.emplace_front(sample);

            if (max_known_distance < sample.distance)
                max_known_distance = sample.distance;

            //std::cout << GetAddress() << " : distance " << sample.distance << " max " << max_known_distance<< std::endl;
        }
        //if (samples.at(from).distance_samples.size() >=10) {
        //    //Cancel previous motility run and register new one to execute now
        //    Motility();
        //    Simulator::Cancel(m_beaconEvent);
        //    m_motilityIntervalEvent = Simulator::Schedule(MilliSeconds(scan_interval), &ApWifiMac::Motility, this);
        //}
    }
    double calculateSD(std::list<double> samples, double average)
    {
        double standardDeviation = 0.0;

        for(auto sample : samples)
            standardDeviation += pow(sample - average, 2);

        standardDeviation = sqrt(standardDeviation / samples.size());
        return standardDeviation;
    }

    bool ApWifiMac::Motility()
    {
        Time scan_interval_time = Time(MilliSeconds(scan_interval));
        m_motilityIntervalEvent = Simulator::Schedule(MilliSeconds(scan_interval), &ApWifiMac::Motility, this);

        //Skip execution if there are no collected samples
        if (samples.empty())
        {
            return false;
        }

        bool moved = false;
        average_sta_distance = 0.0;

        //For each station at range process collected samples
        for (auto sta: m_staAtRange)
        {
            samples.at(sta.first).moving = false;
            distance_samples_list * distance_samp = &samples.at(sta.first).distance_samples;
            distance_registry_list * distance_reg = &samples.at(sta.first).distance_registry;
            speed_registry_list * speed_reg = &samples.at(sta.first).speed_registry;
            
            //Analyze  measurements and calculate average distance plus standard error
            if (!distance_samp->empty())
            {
                //Calculate average speed and standard error
                distance_reg->emplace_front(distance_samp);
                speed_reg->emplace_front(samples.at(sta.first).distance_registry);
                distance_samp->clear();

                double diff = std::abs(distance_reg->begin()->average_distance - std::next(distance_reg->begin())->average_distance);
                samples.at(sta.first).moving = diff > std::max(speed_reg->begin()->standard_deviation, std::next(speed_reg->begin())->standard_deviation);
            }
            //If there are no collected samples in the interval, estimate movement
            /*else
            {
                distance_registry reg = distance_registry(
                (distance_reg->begin()->average_distance+speed_reg->begin()->average_speed*scan_interval)/scan_interval,
                distance_reg->begin()->standard_deviation,
                MilliSeconds(scan_interval));
                distance_reg->emplace_front(reg);
                speed_reg->emplace_front(samples.at(sta.first).distance_registry);
                samples.at(sta.first).moving =
                        std::abs(speed_reg->begin()->average_speed)
                        > std::abs(speed_reg->begin()->standard_deviation);

            }*/

            //Calculate average STA distance
            average_sta_distance += distance_reg->begin()->average_distance;
            if (distance_reg->begin()->standard_deviation > average_sta_distance_deviation)
                average_sta_distance_deviation = distance_reg->begin()->standard_deviation;

            if (distance_reg->size() < 2)
                continue;

            //Clean old registries to free memory and improve simulation speed
            //for (auto it : *distance_reg)
            //    std::cout << "dist " << it.average_distance<<std::endl;
            if (distance_reg->size() > 2)
            {
                auto it = distance_reg->begin();
                std::advance(it, 2);
                distance_reg->erase(it, distance_reg->end());
            }
            if (speed_reg->size() > 2)
            {
                auto it = speed_reg->begin();
                std::advance(it, 2);
                speed_reg->erase(it, speed_reg->end());
            }

        }

        average_sta_distance /= this->samples.size();

        Mac48Address approachSta, movAwaySta;
        bool changedApproach = false, changedMoving = false;

        //For each station, find Stas approaching or moving away from AP
        for (auto sta: m_staAtRange)
        {
            if(samples.at(sta.first).moving)
            {
                distance_registry_list * distance_reg = &samples.at(sta.first).distance_registry;
                speed_registry_list * speed_reg = &samples.at(sta.first).speed_registry;
                
                double distance = distance_reg->begin()->average_distance;
                double speed =  speed_reg->begin()->average_speed;

                double diffdistance = distance - std::next(distance_reg->begin())->average_distance;

                double error = std::max(distance_reg->begin()->standard_deviation, std::next(distance_reg->begin())->standard_deviation);
                bool registered = false;

                for (auto registeredSta: m_staList)
                {
                    registered = sta.first == registeredSta;
                    if (registered)
                        break;
                }

                //std::cout << "distance " << distance << "  diffdistance " << diffdistance << std::endl;
                //STA moving away from AP
                if ((diffdistance - error ) > 0.0
                    && distance >= max_known_distance*interest_radius
                    //&& registered
                    )
                {
                    if (!changedMoving)
                    {
                        movAwaySta = sta.first;
                        changedMoving = true;
                    }
                    else
                    {
                        if (distance_reg->begin()->average_distance
                                > samples.at(movAwaySta).distance_registry.begin()->average_distance)
                            movAwaySta = sta.first;
                    }
                }

                //STA approaching the AP
                if (!registered
                    && (diffdistance + error ) < 0.0
                    && distance >= max_known_distance*interest_radius)
                    //&& distance >= average_sta_distance
                    //&& distance >= (max_known_distance+average_sta_distance)/2
                    //&& speed <= 0.0)
                {
                    //std::cout << "distance " << distance << " avg_dist " << average_sta_distance << " maxDist"<<max_known_distance<< std::endl;
                    if (!changedApproach)
                    {
                        approachSta = sta.first;
                        changedApproach = true;
                    }
                    else
                    {
                        if (distance_reg->begin()->average_distance
                            < samples.at(approachSta).distance_registry.begin()->average_distance)
                            approachSta = sta.first;
                    }
                }
            }
        }

        if (changedApproach | changedMoving)
        {
            m_activeNetwork = true;
            m_beaconInterval = NanoSeconds(m_beaconInterval.GetInteger()/2);
            m_beaconInterval = m_beaconInterval > m_minBeaconInterval ? m_beaconInterval : m_minBeaconInterval;

            //Cancel previous beacon and register new one
            switch(beaconAdjustType)
            {
                case (DYNAMIC_BEACON):
                    {
                        Time t = Simulator::GetDelayLeft(m_beaconEvent);
                        Simulator::Cancel(m_beaconEvent);
                        m_beaconEvent = Simulator::Schedule(m_beaconInterval.GetInteger() < t.GetInteger() ?
                                                        m_beaconInterval : t, &ApWifiMac::SendOneBeacon, this);
                    }
                    break;
                case (TRICKLE_BEACON):
                    {
                        Time t = Simulator::GetDelayLeft(m_TrickleIntervalEvent);

                        if ((t.GetInteger() - m_trickleBeaconInterval/2) >= 0)
                        {
                            Trickle();
                            Simulator::Cancel(m_beaconEvent);
                            m_beaconEvent = Simulator::Schedule(m_beaconInterval.GetInteger() < t.GetInteger() ?
                                                                m_beaconInterval : t, &ApWifiMac::SendOneBeacon, this);
                        }
                    }
                    break;
            }
        }
    }

    bool ApWifiMac::Trickle()
    {
        if (!m_activeNetwork)
        {
            long int tempInt = m_beaconInterval.GetInteger() * 2;
            m_beaconInterval = tempInt < m_maxBeaconInterval.GetInteger() ? NanoSeconds(tempInt) : m_maxBeaconInterval;
        }
        else
        {
            m_beaconInterval =  m_minBeaconInterval;
        }
        m_trickleBeaconInterval = m_beaconInterval;
        Simulator::Cancel(m_TrickleIntervalEvent);
        m_TrickleIntervalEvent = Simulator::Schedule(
                NanoSeconds(m_beaconInterval.GetInteger() / 2 + (rand() % (m_beaconInterval.GetInteger() / 2))),
                &ApWifiMac::Trickle,
                this);
        return true;
    }

    distance_sample::distance_sample(double rssi, double txpower, Time timestamp)
        : distance(0),
          timestamp(Time(MilliSeconds(0)))
    {
        this->distance = calculate_distance_RSSI(rssi, txpower);
        this->timestamp = timestamp;
        //if (txpower > 0.0)
        //std::cout<< "rssi" << rssi << std::endl;
    }

    distance_sample::~distance_sample()
    {

    }

    distance_registry::distance_registry(double average_distance, double standard_deviation, Time measurement_interval)
        : average_distance(0.0),
          standard_deviation(0.0),
          measurement_interval(Time(MilliSeconds(0)))
    {
        this->average_distance = average_distance;
        this->standard_deviation = standard_deviation;
        this->measurement_interval = measurement_interval;
    }

    distance_registry::~distance_registry()
    {

    }

    distance_registry::distance_registry(distance_samples_list *distance_samples) {
        std::list<double> distances_list;
        double distance_sum = 0.0;
        unsigned num_samples = 0;
        average_distance = 0;
        standard_deviation = 0;
        measurement_interval = Time(NanoSeconds(1));

        for (auto sample: *distance_samples) {
            distances_list.emplace_front(sample.distance);
            distance_sum += sample.distance;
            num_samples++;
        }

        if (!distance_samples->empty()) {
            average_distance = distance_sum / num_samples;
            standard_deviation = calculateSD(distances_list, average_distance);
            measurement_interval = distance_samples->begin()->timestamp - distance_samples->end()->timestamp;
            //std::cout << "average distance "<<this->average_distance << "    standard error  "<< standard_deviation<<std::endl;

        }
    }

    speed_registry::speed_registry(distance_registry_list registries)
    {
        distance_registry current_registry = *registries.begin();
        distance_registry previous_registry = *(std::next(registries.begin()));

        measurement_interval = current_registry.measurement_interval - previous_registry.measurement_interval;
        average_speed = (current_registry.average_distance - previous_registry.average_distance)/this->measurement_interval.GetSeconds();
        standard_deviation = current_registry.standard_deviation > previous_registry.standard_deviation
                                   ? current_registry.standard_deviation : previous_registry.standard_deviation;
        if (std::isnan(average_speed) || std::isinf(average_speed) || average_speed < 0.0001)
            average_speed = 0.0;
        //std::cout << "average speed "<<this->average_speed<<std::endl;

    }


} //namespace ns3
