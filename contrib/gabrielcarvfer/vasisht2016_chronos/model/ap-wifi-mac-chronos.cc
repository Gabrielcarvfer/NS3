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
 *
 * Modified by: Gabriel Ferreira <gabrielcarvfer@gmail.com>
 */

#include "ap-wifi-mac-chronos.h"
#include "ns3/log.h"
#include "ns3/simulator.h"
#include "ns3/string.h"
#include "ns3/pointer.h"
#include "ns3/mac-low.h"
#include "ns3/mac-tx-middle.h"
#include <cmath>

#define AT(x,y) at(std::pair<unsigned,unsigned>((x),(y)))
#define LIGHT_SPEED 299792458.0
namespace ns3 {

    NS_LOG_COMPONENT_DEFINE ("ApWifiMacChronos");

    NS_OBJECT_ENSURE_REGISTERED (ApWifiMacChronos);

    TypeId
    ApWifiMacChronos::GetTypeId (void)
    {
        static TypeId tid = TypeId ("ns3::ApWifiMacChronos")
                .SetParent<RegularWifiMac> ()
                .SetGroupName ("Wifi")
                .AddConstructor<ApWifiMacChronos> ()
                .AddAttribute ("BeaconInterval",
                               "Delay between two beacons",
                               TimeValue (MicroSeconds (102400)),
                               MakeTimeAccessor (&ApWifiMacChronos::GetBeaconInterval,
                                                 &ApWifiMacChronos::SetBeaconInterval),
                               MakeTimeChecker ())
                .AddAttribute ("MaxBeaconInterval",
                               "MaxDelay between two beacons",
                               TimeValue (MicroSeconds (102400)),
                               MakeTimeAccessor (&ApWifiMacChronos::GetMaxBeaconInterval,
                                                 &ApWifiMacChronos::SetMaxBeaconInterval),
                               MakeTimeChecker ())
                .AddAttribute ("MinBeaconInterval",
                               "MinDelay between two beacons",
                               TimeValue (MicroSeconds (102400)),
                               MakeTimeAccessor (&ApWifiMacChronos::GetMinBeaconInterval,
                                                 &ApWifiMacChronos::SetMinBeaconInterval),
                               MakeTimeChecker ())
                .AddAttribute ("BeaconJitter",
                               "A uniform random variable to cause the initial beacon starting time (after simulation time 0) "
                                       "to be distributed between 0 and the BeaconInterval.",
                               StringValue ("ns3::UniformRandomVariable"),
                               MakePointerAccessor (&ApWifiMacChronos::m_beaconJitter),
                               MakePointerChecker<UniformRandomVariable> ())
                .AddAttribute ("EnableBeaconJitter",
                               "If beacons are enabled, whether to jitter the initial send event.",
                               BooleanValue (true),
                               MakeBooleanAccessor (&ApWifiMacChronos::m_enableBeaconJitter),
                               MakeBooleanChecker ())
                .AddAttribute ("BeaconGeneration",
                               "Whether or not beacons are generated.",
                               BooleanValue (true),
                               MakeBooleanAccessor (&ApWifiMacChronos::SetBeaconGeneration,
                                                    &ApWifiMacChronos::GetBeaconGeneration),
                               MakeBooleanChecker ())
                .AddAttribute ("EnableNonErpProtection", "Whether or not protection mechanism should be used when non-ERP STAs are present within the BSS."
                                       "This parameter is only used when ERP is supported by the AP.",
                               BooleanValue (true),
                               MakeBooleanAccessor (&ApWifiMacChronos::m_enableNonErpProtection),
                               MakeBooleanChecker ())
                .AddAttribute ("RifsMode", "If non-HT STAs are detected, whether to force RIFS to be disabled within the BSS."
                                       "This parameter is only used when HT is supported by the AP.",
                               BooleanValue (true),
                               MakeBooleanAccessor (&ApWifiMacChronos::m_disableRifs),
                               MakeBooleanChecker ())
        ;
        return tid;
    }

    ApWifiMacChronos::ApWifiMacChronos ()
            : m_enableBeaconGeneration (false)
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
    }

    ApWifiMacChronos::~ApWifiMacChronos ()
    {
        NS_LOG_FUNCTION (this);
        m_staList.clear ();
        m_nonErpStations.clear ();
        m_nonHtStations.clear ();
    }

    void
    ApWifiMacChronos::DoDispose ()
    {
        NS_LOG_FUNCTION (this);
        m_beaconDca->Dispose ();
        m_beaconDca = 0;
        m_enableBeaconGeneration = false;
        m_beaconEvent.Cancel ();
        RegularWifiMac::DoDispose ();
    }

    void
    ApWifiMacChronos::SetAddress (Mac48Address address)
    {
        NS_LOG_FUNCTION (this << address);
        //As an AP, our MAC address is also the BSSID. Hence we are
        //overriding this function and setting both in our parent class.
        RegularWifiMac::SetAddress (address);
        RegularWifiMac::SetBssid (address);
    }

    void
    ApWifiMacChronos::SetBeaconGeneration (bool enable)
    {
        NS_LOG_FUNCTION (this << enable);
        if (!enable)
        {
            m_beaconEvent.Cancel ();
        }
        else if (enable && !m_enableBeaconGeneration)
        {
            m_beaconEvent = Simulator::ScheduleNow (&ApWifiMacChronos::SendOneBeacon, this);
        }
        m_enableBeaconGeneration = enable;
    }

    bool
    ApWifiMacChronos::GetBeaconGeneration (void) const
    {
        NS_LOG_FUNCTION (this);
        return m_enableBeaconGeneration;
    }

    Time
    ApWifiMacChronos::GetBeaconInterval (void) const
    {
        NS_LOG_FUNCTION (this);
        return m_beaconInterval;
    }

    Time
    ApWifiMacChronos::GetMaxBeaconInterval (void) const
    {
        NS_LOG_FUNCTION (this);
        return m_maxBeaconInterval;
    }

    Time
    ApWifiMacChronos::GetMinBeaconInterval (void) const
    {
        NS_LOG_FUNCTION (this);
        return m_minBeaconInterval;
    }

    void
    ApWifiMacChronos::SetWifiRemoteStationManager (const Ptr<WifiRemoteStationManager> stationManager)
    {
        NS_LOG_FUNCTION (this << stationManager);
        m_beaconDca->SetWifiRemoteStationManager (stationManager);
        RegularWifiMac::SetWifiRemoteStationManager (stationManager);
    }

    void
    ApWifiMacChronos::SetLinkUpCallback (Callback<void> linkUp)
    {
        NS_LOG_FUNCTION (this << &linkUp);
        RegularWifiMac::SetLinkUpCallback (linkUp);

        //The approach taken here is that, from the point of view of an AP,
        //the link is always up, so we immediately invoke the callback if
        //one is set
        linkUp ();
    }

    void
    ApWifiMacChronos::SetBeaconInterval (Time interval)
    {
        NS_LOG_FUNCTION (this << interval);
        if ((interval.GetMicroSeconds () % 1024) != 0)
        {
            NS_LOG_WARN ("beacon interval should be multiple of 1024us (802.11 time unit), see IEEE Std. 802.11-2012");
        }
        m_beaconInterval = interval;
    }

    void
    ApWifiMacChronos::SetMaxBeaconInterval (Time interval)
    {
        NS_LOG_FUNCTION (this << interval);
        if ((interval.GetMicroSeconds () % 1024) != 0)
        {
            NS_LOG_WARN ("beacon interval should be multiple of 1024us (802.11 time unit), see IEEE Std. 802.11-2012");
        }
        m_maxBeaconInterval = interval;
    }

    void
    ApWifiMacChronos::SetMinBeaconInterval (Time interval)
    {
        NS_LOG_FUNCTION (this << interval);
        if ((interval.GetMicroSeconds () % 1024) != 0)
        {
            NS_LOG_WARN ("beacon interval should be multiple of 1024us (802.11 time unit), see IEEE Std. 802.11-2012");
        }
        m_minBeaconInterval = interval;
    }

    void
    ApWifiMacChronos::StartBeaconing (void)
    {
        NS_LOG_FUNCTION (this);
        SendOneBeacon ();
    }

    int64_t
    ApWifiMacChronos::AssignStreams (int64_t stream)
    {
        NS_LOG_FUNCTION (this << stream);
        m_beaconJitter->SetStream (stream);
        return 1;
    }

    bool
    ApWifiMacChronos::GetShortSlotTimeEnabled (void) const
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
    ApWifiMacChronos::GetShortPreambleEnabled (void) const
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
    ApWifiMacChronos::IsNonGfHtStasPresent (void) const
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
    ApWifiMacChronos::GetVhtOperationalChannelWidth (void) const
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
    ApWifiMacChronos::ForwardDown (Ptr<const Packet> packet, Mac48Address from,
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
    ApWifiMacChronos::ForwardDown (Ptr<const Packet> packet, Mac48Address from,
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
    ApWifiMacChronos::Enqueue (Ptr<const Packet> packet, Mac48Address to, Mac48Address from)
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
    ApWifiMacChronos::Enqueue (Ptr<const Packet> packet, Mac48Address to)
    {
        NS_LOG_FUNCTION (this << packet << to);
        //We're sending this packet with a from address that is our own. We
        //get that address from the lower MAC and make use of the
        //from-spoofing Enqueue() method to avoid duplicated code.
        Enqueue (packet, to, m_low->GetAddress ());
    }

    bool
    ApWifiMacChronos::SupportsSendFrom (void) const
    {
        NS_LOG_FUNCTION (this);
        return true;
    }

    SupportedRates
    ApWifiMacChronos::GetSupportedRates (void) const
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
    ApWifiMacChronos::GetDsssParameterSet (void) const
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
    ApWifiMacChronos::GetCapabilities (void) const
    {
        NS_LOG_FUNCTION (this);
        CapabilityInformation capabilities;
        capabilities.SetShortPreamble (GetShortPreambleEnabled ());
        capabilities.SetShortSlotTime (GetShortSlotTimeEnabled ());
        return capabilities;
    }

    ErpInformation
    ApWifiMacChronos::GetErpInformation (void) const
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
    ApWifiMacChronos::GetEdcaParameterSet (void) const
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
    ApWifiMacChronos::GetHtOperation (void) const
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
    ApWifiMacChronos::GetVhtOperation (void) const
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
    ApWifiMacChronos::SendProbeResp (Mac48Address to)
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
    ApWifiMacChronos::SendAssocResp (Mac48Address to, bool success)
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
            ChronosLocationData data;
            //todo: find number of sta antennas and allocate before emplacing to structure
            chronosLocationData.emplace(to, data);
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
    ApWifiMacChronos::SendOneBeacon (void)
    {
        NS_LOG_FUNCTION (this);
        WifiMacHeader hdr;
        hdr.SetBeacon ();
        hdr.SetAddr1 (Mac48Address::GetBroadcast ());
        hdr.SetAddr2 (GetAddress ());
        hdr.SetAddr3 (GetAddress ());
        hdr.SetDsNotFrom ();
        hdr.SetDsNotTo ();
        hdr.SetNoOrder ();
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
            beacon.SetHtOperation (GetHtOperation ());
        }
        if (m_vhtSupported || m_heSupported)
        {
            beacon.SetVhtCapabilities (GetVhtCapabilities ());
            beacon.SetVhtOperation (GetVhtOperation ());
        }
        if (m_heSupported)
        {
            beacon.SetHeCapabilities (GetHeCapabilities ());
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

        m_beaconEvent = Simulator::Schedule (m_beaconInterval, &ApWifiMacChronos::SendOneBeacon, this);

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
    ApWifiMacChronos::TxOk (const WifiMacHeader &hdr)
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
    ApWifiMacChronos::TxFailed (const WifiMacHeader &hdr)
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
    ApWifiMacChronos::Receive (Ptr<Packet> packet, const WifiMacHeader *hdr)
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
    ApWifiMacChronos::DeaggregateAmsduAndForward (Ptr<Packet> aggregatedPacket,
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
    ApWifiMacChronos::DoInitialize (void)
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
                m_beaconEvent = Simulator::Schedule (MicroSeconds (jitter), &ApWifiMacChronos::SendOneBeacon, this);
            }
            else
            {
                NS_LOG_DEBUG ("Scheduling initial beacon for access point " << GetAddress () << " at time 0");
                m_beaconEvent = Simulator::ScheduleNow (&ApWifiMacChronos::SendOneBeacon, this);
            }
        }

        RegularWifiMac::DoInitialize ();

        //Schedule Chronos AP protocol
        unsigned num_antennas = GetWifiPhy()->GetNumberOfAntennas();
        for (int i = 0; i < num_antennas; i++)
        {
            for (int j = i+1; j < num_antennas; j++)
            {
                antenna_data_t data = {-1,i,j};
                ap_antennas_distances.push_back(data);
            }
        }
        Simulator::Schedule(MilliSeconds(84), &ApWifiMacChronos::ChronosTracking, this);
    }

    bool
    ApWifiMacChronos::GetUseNonErpProtection (void) const
    {
        bool useProtection = !m_nonErpStations.empty () && m_enableNonErpProtection;
        m_stationManager->SetUseNonErpProtection (useProtection);
        return useProtection;
    }

    bool
    ApWifiMacChronos::GetRifsMode (void) const
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

    int gcd(int a, int b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }

    float least_common_multiple(std::vector<float> values)
    {
        float lcm = values[0];
        for (int i = 1; i< values.size(); i++)
        {
            lcm = lcm / gcd(lcm, values[i]) * values[i];
        }
        return lcm;
    }

    float calculate_time_of_flight(float phase, float freq)
    {
        return (float)(fmod(-phase/(2*M_PI*freq), (1/freq)));
    }


    float ApWifiMacChronos::euclidian_distance(float a[2], float b[2])
    {
        double c;
        c = sqrt( pow(a[0]-b[0],2) + pow(a[1]-b[1],2) );
        return (float)c;
    }

    void ApWifiMacChronos::calculate_location(ChronosLocationData* sta_antennas,
                                              std::vector<antenna_data_t> *ap_antennas,
                                              float *coordinates)
    {
        float A, B, C, min_error, prev_min_error, err;
        int min_i, min_j, prev_min_i, prev_min_j;

        //Find two pairs or antennas between AP and STA with minimal distances
        for (int i = 0; i < sta_antennas->antenna_pairs.size(); i++)
        {
            for (int j = 0; j < ap_antennas->size(); j++)
            {
                //Minimize error in distance between antennas and calculated distance
                //todo:err = euclidian_distance(ap_antennas[j], sta_antennas[i]) - sta_antennas->antenna_pairs.AT(i,j).distance;
                if (err < min_error)
                {
                    prev_min_error = min_error;
                    prev_min_i = min_i;
                    prev_min_j = min_j;
                    min_error = err;
                    min_i = i;
                    min_j = j;
                }
            }
        }

        //We can calculate x,y coordinates for STA now
        //The prev_min is the hipotenuse, the min is the longest cathetus, the shortest cathetus is the distance between
        //   antennas (either from AP ou STA, but that can be checked comparing min_i and prev_min_i (STA antenna indexes))

        //min and prev_min are between same STA antenna and multiple AP antennas
        //        d_min
        //        ____
        //  l_sta |   | l_ap
        //	       \  |
        //          \ |
        //           \|
        //   d_prev_min

        if (min_i == prev_min_i)
        {
            A = sta_antennas->antenna_pairs.AT(min_i,min_j).distance;
            //todo:B = euclidian_distance(ap_antennas[min_j], ap_antennas[prev_min_j]);
            C = sta_antennas->antenna_pairs.AT(prev_min_i,prev_min_j).distance;
        }

            //min and prev_min are between same AP antenna and multiple STA antennas
            //        d_min
            //        ____
            //        |   | l_ap
            //	l_sta |  /
            //        | /
            //        |/
            //         d_prev_min
        else if(min_j == prev_min_j)
        {
            A = sta_antennas->antenna_pairs.AT(min_i,min_j).distance;
            //todo:B = euclidian_distance(ap_antennas[min_i], ap_antennas[prev_min_i]);
            C = sta_antennas->antenna_pairs.AT(prev_min_i,prev_min_j).distance;
        }

            //min and prev_min are between two different pairs on antennas between AP and STA, forming a trapezoid shape
            //             d_min
            //        _____________
            //	l_sta |            \  l_ap
            //        |             \
        //        ---------------\
        //           d_prev_min
        else
        {
            //we choose to discard the d_prev_min and its associated antenna, and trace a hipotenuse
            // linking the sta_min to ap_prev_min (hipotenuse = l_ap + d_min - 1) then calculate
            A = sta_antennas->antenna_pairs.AT(min_i,min_j).distance;
            //todo:B = euclidian_distance(ap_antennas[min_j], ap_antennas[prev_min_j]);
            C = B + A - 1; // biggest hipotenuse that fits triangle inequality

        }

        //Compute angles between STA and AP antennas, and then relative coordinates of STA
        float cos_theta = (float)(pow(B,2)+pow(C,2)-pow(A,2)/(2*B*C));
        float sin_theta = (float)(sin(acos(cos_theta)));
        coordinates[0] = sta_antennas->antenna_pairs.AT(min_i,min_j).distance * cos_theta;
        coordinates[1] = sta_antennas->antenna_pairs.AT(min_i,min_j).distance * sin_theta;
    }

    void ApWifiMacChronos::ChronosTracking()
    {

        std::vector<float> wifi_bands = std::vector<float>({2.414, 2.561, 2.1231});
        float lcm_bands = least_common_multiple(wifi_bands);

        //For each STA, calculate time-of-flight between each of AP and STA antennas
        auto sta = m_staList.begin();
        ChronosLocationData sta_antennas = chronosLocationData.at(*sta);

        for (int i = 0; i < m_staList.size() && sta != m_staList.end(); i++, std::advance(sta,1))
        {
            sta_antennas = chronosLocationData.at(*sta);
            //For each AP antenna
            for (int j = 0; j < ap_antennas_distances.size(); j++)
            {
                //For each STA antenna
                for (int k = 0; k < sta_antennas.antenna_pairs.size(); k++)
                {
                    std::vector<float> phase_array;
                    std::vector<float> tau_array;

                    //Hop through each band with AP and collect phase data from channel
                    for (int l = 0; l < wifi_bands.size(); l++)
                    {

                        //todo:send_next_frequency_to_hop(wifi_bands[l], *sta);
                        //todo:wait_ack(*sta);
                        GetWifiPhy()->SetFrequency((uint16_t)(wifi_bands[l]*1000000));
                        //todo:timed_wait(*sta); //in case of timeout, reset to previous band
                        //todo:phase_array.push_back(collect_CSI_data(*sta));
                        tau_array.push_back(calculate_time_of_flight(phase_array[l],wifi_bands[l]));
                    }
                    sta_antennas.antenna_pairs.AT(k,j).distance
                            = (float)(calculate_time_of_flight(least_common_multiple(tau_array),lcm_bands)*LIGHT_SPEED);

                    //Save smallest distance as distance between AP and STA
                    if (sta_antennas.antenna_pairs.AT(k,j).distance < sta_antennas.distance)
                    {
                        sta_antennas.distance = sta_antennas.antenna_pairs.AT(k,j).distance;
                    }
                }
            }
            //The position of STA can be calculated after that
            calculate_location(&sta_antennas, &ap_antennas_distances, &sta_antennas.coordinates[0]);
        }
    }
} //namespace ns3



