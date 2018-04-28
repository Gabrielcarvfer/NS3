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
 * Author: Nicola Baldo <nbaldo@cttc.es> (re-wrote from scratch this helper)
 *         Giuseppe Piro <g.piro@poliba.it> (parts of the PHY & channel  creation & configuration copied from the GSoC 2011 code)
 * Modified by: Danilo Abrignani <danilo.abrignani@unibo.it> (Carrier Aggregation - GSoC 2015)
 *              Biljana Bojovic <biljana.bojovic@cttc.es> (Carrier Aggregation) 
 */

#include "lte-helper.h"
//#include "wireshark_epan_dissectors_packet-mac-lte.h"
#include <ns3/string.h>
#include <ns3/log.h>
#include <ns3/abort.h>
#include <ns3/pointer.h>
#include <ns3/lte-enb-rrc.h>
#include <ns3/epc-ue-nas.h>
#include <ns3/epc-enb-application.h>
#include <ns3/lte-ue-rrc.h>
#include <ns3/lte-ue-mac.h>
#include <ns3/lte-enb-mac.h>
#include <ns3/lte-enb-net-device.h>
#include <ns3/lte-enb-phy.h>
#include <ns3/lte-ue-phy.h>
#include <ns3/lte-spectrum-phy.h>
#include <ns3/lte-chunk-processor.h>
#include <ns3/multi-model-spectrum-channel.h>
#include <ns3/friis-spectrum-propagation-loss.h>
#include <ns3/trace-fading-loss-model.h>
#include <ns3/isotropic-antenna-model.h>
#include <ns3/lte-ue-net-device.h>
#include <ns3/ff-mac-scheduler.h>
#include <ns3/lte-ffr-algorithm.h>
#include <ns3/lte-handover-algorithm.h>
#include <ns3/lte-enb-component-carrier-manager.h>
#include <ns3/lte-ue-component-carrier-manager.h>
#include <ns3/lte-anr.h>
#include <ns3/lte-rlc.h>
#include <ns3/lte-rlc-um.h>
#include <ns3/lte-rlc-am.h>
#include <ns3/epc-enb-s1-sap.h>
#include <ns3/lte-rrc-protocol-ideal.h>
#include <ns3/lte-rrc-protocol-real.h>
#include <ns3/mac-stats-calculator.h>
#include <ns3/phy-stats-calculator.h>
#include <ns3/phy-tx-stats-calculator.h>
#include <ns3/phy-rx-stats-calculator.h>
#include <ns3/epc-helper.h>
#include <iostream>
#include <ns3/buildings-propagation-loss-model.h>
#include <ns3/lte-spectrum-value-helper.h>
#include <ns3/epc-x2.h>
#include <ns3/object-map.h>
#include <ns3/object-factory.h>
#include <ns3/network-module.h>
#include <ns3/callback.h>
#include <ns3/config.h>

namespace ns3 {

    /**
 * ASCII trace Phy transmit sink with context
 * \param stream the output stream
 * \param context the context name
 * \param p the packet
 * \param txLevel the transmit power level
 */
 /*
    static void
    AsciiPhyTransmitSinkWithContext (
            Ptr<OutputStreamWrapper> stream,
            std::string context,
            Ptr<const Packet> p,
            uint8_t txLevel)
    {
        NS_LOG_FUNCTION (stream << context << p << txLevel);
        *stream->GetStream () << "t " << Simulator::Now ().GetSeconds () << " " << context << " " << *p << std::endl;
    }
*/
/**
 * ASCII trace Phy transmit sink without context
 * \param stream the output stream
 * \param p the packet
 * \param txLevel the transmit power level
 */
 /*
    static void
    AsciiPhyTransmitSinkWithoutContext (
            Ptr<OutputStreamWrapper> stream,
            Ptr<const Packet> p,
            uint8_t txLevel)
    {
        NS_LOG_FUNCTION (stream << p  << txLevel);
        *stream->GetStream () << "t " << Simulator::Now ().GetSeconds () << " " << *p << std::endl;
    }
*/
/**
 * ASCII trace Phy receive sink with context
 * \param stream the output stream
 * \param context the context name
 * \param p the packet
 * \param snr the SNR
 */
 /*
    static void
    AsciiPhyReceiveSinkWithContext (
            Ptr<OutputStreamWrapper> stream,
            std::string context,
            Ptr<const Packet> p,
            double snr)
    {
        NS_LOG_FUNCTION (stream << context << p << snr);
        *stream->GetStream () << "r " << Simulator::Now ().GetSeconds () << " " << context << " " << *p << std::endl;
    }
*/
/**
 * ASCII trace Phy receive sink without context
 * \param stream the output stream
 * \param p the packet
 * \param snr the SNR
 */
 /*
    static void
    AsciiPhyReceiveSinkWithoutContext (
            Ptr<OutputStreamWrapper> stream,
            Ptr<const Packet> p,
            double snr)
    {
        NS_LOG_FUNCTION (stream << p << snr);
        *stream->GetStream () << "r " << Simulator::Now ().GetSeconds () << " " << *p << std::endl;
    }
*/
    NS_LOG_COMPONENT_DEFINE ("LteHelper");

    NS_OBJECT_ENSURE_REGISTERED (LteHelper);

    LteHelper::LteHelper(void)
            : m_fadingStreamsAssigned(false),
              m_imsiCounter(0),
              m_cellIdCounter{1} {
        NS_LOG_FUNCTION (this);
        m_enbNetDeviceFactory.SetTypeId(LteEnbNetDevice::GetTypeId());
        m_enbAntennaModelFactory.SetTypeId(IsotropicAntennaModel::GetTypeId());
        m_ueNetDeviceFactory.SetTypeId(LteUeNetDevice::GetTypeId());
        m_ueAntennaModelFactory.SetTypeId(IsotropicAntennaModel::GetTypeId());
        m_channelFactory.SetTypeId(MultiModelSpectrumChannel::GetTypeId());
    }

    void
    LteHelper::DoInitialize(void) {
        NS_LOG_FUNCTION (this);
        ChannelModelInitialization();
        m_phyStats = CreateObject<PhyStatsCalculator>();
        m_phyTxStats = CreateObject<PhyTxStatsCalculator>();
        m_phyRxStats = CreateObject<PhyRxStatsCalculator>();
        m_macStats = CreateObject<MacStatsCalculator>();
        Object::DoInitialize();

    }

    LteHelper::~LteHelper(void) {
        NS_LOG_FUNCTION (this);
    }

    TypeId LteHelper::GetTypeId(void) {
        static TypeId
                tid =
                TypeId("ns3::LteHelper")
                        .SetParent<Object>()
                        .AddConstructor<LteHelper>()
                        .AddAttribute("Scheduler",
                                      "The type of scheduler to be used for eNBs. "
                                      "The allowed values for this attributes are the type names "
                                      "of any class inheriting from ns3::FfMacScheduler.",
                                      StringValue("ns3::PfFfMacScheduler"),
                                      MakeStringAccessor(&LteHelper::SetSchedulerType,
                                                         &LteHelper::GetSchedulerType),
                                      MakeStringChecker())
                        .AddAttribute("FfrAlgorithm",
                                      "The type of FFR algorithm to be used for eNBs. "
                                      "The allowed values for this attributes are the type names "
                                      "of any class inheriting from ns3::LteFfrAlgorithm.",
                                      StringValue("ns3::LteFrNoOpAlgorithm"),
                                      MakeStringAccessor(&LteHelper::SetFfrAlgorithmType,
                                                         &LteHelper::GetFfrAlgorithmType),
                                      MakeStringChecker())
                        .AddAttribute("HandoverAlgorithm",
                                      "The type of handover algorithm to be used for eNBs. "
                                      "The allowed values for this attributes are the type names "
                                      "of any class inheriting from ns3::LteHandoverAlgorithm.",
                                      StringValue("ns3::NoOpHandoverAlgorithm"),
                                      MakeStringAccessor(&LteHelper::SetHandoverAlgorithmType,
                                                         &LteHelper::GetHandoverAlgorithmType),
                                      MakeStringChecker())
                        .AddAttribute("PathlossModel",
                                      "The type of pathloss model to be used. "
                                      "The allowed values for this attributes are the type names "
                                      "of any class inheriting from ns3::PropagationLossModel.",
                                      TypeIdValue(FriisPropagationLossModel::GetTypeId()),
                                      MakeTypeIdAccessor(&LteHelper::SetPathlossModelType),
                                      MakeTypeIdChecker())
                        .AddAttribute("FadingModel",
                                      "The type of fading model to be used."
                                      "The allowed values for this attributes are the type names "
                                      "of any class inheriting from ns3::SpectrumPropagationLossModel."
                                      "If the type is set to an empty string, no fading model is used.",
                                      StringValue(""),
                                      MakeStringAccessor(&LteHelper::SetFadingModel),
                                      MakeStringChecker())
                        .AddAttribute("UseIdealRrc",
                                      "If true, LteRrcProtocolIdeal will be used for RRC signaling. "
                                      "If false, LteRrcProtocolReal will be used.",
                                      BooleanValue(true),
                                      MakeBooleanAccessor(&LteHelper::m_useIdealRrc),
                                      MakeBooleanChecker())
                        .AddAttribute("AnrEnabled",
                                      "Activate or deactivate Automatic Neighbour Relation function",
                                      BooleanValue(true),
                                      MakeBooleanAccessor(&LteHelper::m_isAnrEnabled),
                                      MakeBooleanChecker())
                        .AddAttribute("UsePdschForCqiGeneration",
                                      "If true, DL-CQI will be calculated from PDCCH as signal and PDSCH as interference "
                                      "If false, DL-CQI will be calculated from PDCCH as signal and PDCCH as interference  ",
                                      BooleanValue(true),
                                      MakeBooleanAccessor(&LteHelper::m_usePdschForCqiGeneration),
                                      MakeBooleanChecker())
                        .AddAttribute("EnbComponentCarrierManager",
                                      "The type of Component Carrier Manager to be used for eNBs. "
                                      "The allowed values for this attributes are the type names "
                                      "of any class inheriting ns3::LteEnbComponentCarrierManager.",
                                      StringValue("ns3::NoOpComponentCarrierManager"),
                                      MakeStringAccessor(&LteHelper::SetEnbComponentCarrierManagerType,
                                                         &LteHelper::GetEnbComponentCarrierManagerType),
                                      MakeStringChecker())
                        .AddAttribute("UeComponentCarrierManager",
                                      "The type of Component Carrier Manager to be used for UEs. "
                                      "The allowed values for this attributes are the type names "
                                      "of any class inheriting ns3::LteUeComponentCarrierManager.",
                                      StringValue("ns3::SimpleUeComponentCarrierManager"),
                                      MakeStringAccessor(&LteHelper::SetUeComponentCarrierManagerType,
                                                         &LteHelper::GetUeComponentCarrierManagerType),
                                      MakeStringChecker())
                        .AddAttribute("UseCa",
                                      "If true, Carrier Aggregation feature is enabled and a valid Component Carrier Map is expected."
                                      "If false, single carrier simulation.",
                                      BooleanValue(false),
                                      MakeBooleanAccessor(&LteHelper::m_useCa),
                                      MakeBooleanChecker())
                        .AddAttribute("NumberOfComponentCarriers",
                                      "Set the number of Component carrier to use "
                                      "If it is more than one and m_useCa is false, it will raise an error ",
                                      UintegerValue(1),
                                      MakeUintegerAccessor(&LteHelper::m_noOfCcs),
                                      MakeUintegerChecker<uint16_t>(MIN_NO_CC, MAX_NO_CC));
        return tid;
    }

    void
    LteHelper::DoDispose() {
        NS_LOG_FUNCTION (this);
        m_downlinkChannel = 0;
        m_uplinkChannel = 0;
        m_componentCarrierPhyParams.clear();
        Object::DoDispose();
    }

    Ptr<SpectrumChannel>
    LteHelper::GetUplinkSpectrumChannel(void) const {
        return m_uplinkChannel;
    }

    Ptr<SpectrumChannel>
    LteHelper::GetDownlinkSpectrumChannel(void) const {
        return m_downlinkChannel;
    }

    void
    LteHelper::ChannelModelInitialization(void) {
        // Channel Object (i.e. Ptr<SpectrumChannel>) are within a vector
        // PathLossModel Objects are vectors --> in InstallSingleEnb we will set the frequency
        NS_LOG_FUNCTION (this << m_noOfCcs);

        m_downlinkChannel = m_channelFactory.Create<SpectrumChannel>();
        m_uplinkChannel = m_channelFactory.Create<SpectrumChannel>();

        m_downlinkPathlossModel = m_pathlossModelFactory.Create();
        Ptr<SpectrumPropagationLossModel> dlSplm = m_downlinkPathlossModel->GetObject<SpectrumPropagationLossModel>();
        if (dlSplm != 0) {
            NS_LOG_LOGIC (this << " using a SpectrumPropagationLossModel in DL");
            m_downlinkChannel->AddSpectrumPropagationLossModel(dlSplm);
        } else {
            NS_LOG_LOGIC (this << " using a PropagationLossModel in DL");
            Ptr<PropagationLossModel> dlPlm = m_downlinkPathlossModel->GetObject<PropagationLossModel>();
            NS_ASSERT_MSG (dlPlm != 0, " " << m_downlinkPathlossModel
                                           << " is neither PropagationLossModel nor SpectrumPropagationLossModel");
            m_downlinkChannel->AddPropagationLossModel(dlPlm);
        }

        m_uplinkPathlossModel = m_pathlossModelFactory.Create();
        Ptr<SpectrumPropagationLossModel> ulSplm = m_uplinkPathlossModel->GetObject<SpectrumPropagationLossModel>();
        if (ulSplm != 0) {
            NS_LOG_LOGIC (this << " using a SpectrumPropagationLossModel in UL");
            m_uplinkChannel->AddSpectrumPropagationLossModel(ulSplm);
        } else {
            NS_LOG_LOGIC (this << " using a PropagationLossModel in UL");
            Ptr<PropagationLossModel> ulPlm = m_uplinkPathlossModel->GetObject<PropagationLossModel>();
            NS_ASSERT_MSG (ulPlm != 0, " " << m_uplinkPathlossModel
                                           << " is neither PropagationLossModel nor SpectrumPropagationLossModel");
            m_uplinkChannel->AddPropagationLossModel(ulPlm);
        }
        if (!m_fadingModelType.empty()) {
            m_fadingModule = m_fadingModelFactory.Create<SpectrumPropagationLossModel>();
            m_fadingModule->Initialize();
            m_downlinkChannel->AddSpectrumPropagationLossModel(m_fadingModule);
            m_uplinkChannel->AddSpectrumPropagationLossModel(m_fadingModule);
        }
    }

    void
    LteHelper::SetEpcHelper(Ptr<EpcHelper> h) {
        NS_LOG_FUNCTION (this << h);
        m_epcHelper = h;
    }

    void
    LteHelper::SetSchedulerType(std::string type) {
        NS_LOG_FUNCTION (this << type);
        m_schedulerFactory = ObjectFactory();
        m_schedulerFactory.SetTypeId(type);
    }

    std::string
    LteHelper::GetSchedulerType() const {
        return m_schedulerFactory.GetTypeId().GetName();
    }

    void
    LteHelper::SetSchedulerAttribute(std::string n, const AttributeValue &v) {
        NS_LOG_FUNCTION (this << n);
        m_schedulerFactory.Set(n, v);
    }

    std::string
    LteHelper::GetFfrAlgorithmType() const {
        return m_ffrAlgorithmFactory.GetTypeId().GetName();
    }

    void
    LteHelper::SetFfrAlgorithmType(std::string type) {
        NS_LOG_FUNCTION (this << type);
        m_ffrAlgorithmFactory = ObjectFactory();
        m_ffrAlgorithmFactory.SetTypeId(type);
    }

    void
    LteHelper::SetFfrAlgorithmAttribute(std::string n, const AttributeValue &v) {
        NS_LOG_FUNCTION (this << n);
        m_ffrAlgorithmFactory.Set(n, v);
    }

    std::string
    LteHelper::GetHandoverAlgorithmType() const {
        return m_handoverAlgorithmFactory.GetTypeId().GetName();
    }

    void
    LteHelper::SetHandoverAlgorithmType(std::string type) {
        NS_LOG_FUNCTION (this << type);
        m_handoverAlgorithmFactory = ObjectFactory();
        m_handoverAlgorithmFactory.SetTypeId(type);
    }

    void
    LteHelper::SetHandoverAlgorithmAttribute(std::string n, const AttributeValue &v) {
        NS_LOG_FUNCTION (this << n);
        m_handoverAlgorithmFactory.Set(n, v);
    }


    std::string
    LteHelper::GetEnbComponentCarrierManagerType() const {
        return m_enbComponentCarrierManagerFactory.GetTypeId().GetName();
    }

    void
    LteHelper::SetEnbComponentCarrierManagerType(std::string type) {
        NS_LOG_FUNCTION (this << type);
        m_enbComponentCarrierManagerFactory = ObjectFactory();
        m_enbComponentCarrierManagerFactory.SetTypeId(type);
    }

    void
    LteHelper::SetEnbComponentCarrierManagerAttribute(std::string n, const AttributeValue &v) {
        NS_LOG_FUNCTION (this << n);
        m_enbComponentCarrierManagerFactory.Set(n, v);
    }

    std::string
    LteHelper::GetUeComponentCarrierManagerType() const {
        return m_ueComponentCarrierManagerFactory.GetTypeId().GetName();
    }

    void
    LteHelper::SetUeComponentCarrierManagerType(std::string type) {
        NS_LOG_FUNCTION (this << type);
        m_ueComponentCarrierManagerFactory = ObjectFactory();
        m_ueComponentCarrierManagerFactory.SetTypeId(type);
    }

    void
    LteHelper::SetUeComponentCarrierManagerAttribute(std::string n, const AttributeValue &v) {
        NS_LOG_FUNCTION (this << n);
        m_ueComponentCarrierManagerFactory.Set(n, v);
    }

    void
    LteHelper::SetPathlossModelType(TypeId type) {
        NS_LOG_FUNCTION (this << type);
        m_pathlossModelFactory = ObjectFactory();
        m_pathlossModelFactory.SetTypeId(type);
    }

    void
    LteHelper::SetPathlossModelAttribute(std::string n, const AttributeValue &v) {
        NS_LOG_FUNCTION (this << n);
        m_pathlossModelFactory.Set(n, v);
    }

    void
    LteHelper::SetEnbDeviceAttribute(std::string n, const AttributeValue &v) {
        NS_LOG_FUNCTION (this);
        m_enbNetDeviceFactory.Set(n, v);
    }


    void
    LteHelper::SetEnbAntennaModelType(std::string type) {
        NS_LOG_FUNCTION (this);
        m_enbAntennaModelFactory.SetTypeId(type);
    }

    void
    LteHelper::SetEnbAntennaModelAttribute(std::string n, const AttributeValue &v) {
        NS_LOG_FUNCTION (this);
        m_enbAntennaModelFactory.Set(n, v);
    }

    void
    LteHelper::SetUeDeviceAttribute(std::string n, const AttributeValue &v) {
        NS_LOG_FUNCTION (this);
        m_ueNetDeviceFactory.Set(n, v);
    }

    void
    LteHelper::SetUeAntennaModelType(std::string type) {
        NS_LOG_FUNCTION (this);
        m_ueAntennaModelFactory.SetTypeId(type);
    }

    void
    LteHelper::SetUeAntennaModelAttribute(std::string n, const AttributeValue &v) {
        NS_LOG_FUNCTION (this);
        m_ueAntennaModelFactory.Set(n, v);
    }

    void
    LteHelper::SetFadingModel(std::string type) {
        NS_LOG_FUNCTION (this << type);
        m_fadingModelType = type;
        if (!type.empty()) {
            m_fadingModelFactory = ObjectFactory();
            m_fadingModelFactory.SetTypeId(type);
        }
    }

    void
    LteHelper::SetFadingModelAttribute(std::string n, const AttributeValue &v) {
        m_fadingModelFactory.Set(n, v);
    }

    void
    LteHelper::SetSpectrumChannelType(std::string type) {
        NS_LOG_FUNCTION (this << type);
        m_channelFactory.SetTypeId(type);
    }

    void
    LteHelper::SetSpectrumChannelAttribute(std::string n, const AttributeValue &v) {
        m_channelFactory.Set(n, v);
    }

    void
    LteHelper::SetCcPhyParams(std::map<uint8_t, ComponentCarrier> ccMapParams) {
        NS_LOG_FUNCTION (this);
        m_componentCarrierPhyParams = ccMapParams;
    }

    NetDeviceContainer
    LteHelper::InstallEnbDevice(NodeContainer c) {
        NS_LOG_FUNCTION (this);
        Initialize();  // will run DoInitialize () if necessary
        NetDeviceContainer devices;
        for (NodeContainer::Iterator i = c.Begin(); i != c.End(); ++i) {
            Ptr<Node> node = *i;
            Ptr<NetDevice> device = InstallSingleEnbDevice(node);
            devices.Add(device);
        }
        return devices;
    }

    NetDeviceContainer
    LteHelper::InstallUeDevice(NodeContainer c) {
        NS_LOG_FUNCTION (this);
        NetDeviceContainer devices;
        for (NodeContainer::Iterator i = c.Begin(); i != c.End(); ++i) {
            Ptr<Node> node = *i;
            Ptr<NetDevice> device = InstallSingleUeDevice(node);
            devices.Add(device);
        }
        return devices;
    }


NetDeviceContainer
LteHelper::InstallEnbDevice (NodeContainer c)
{
  NS_LOG_FUNCTION (this);
  Initialize ();  // will run DoInitialize () if necessary
  NetDeviceContainer devices;
  for (NodeContainer::Iterator i = c.Begin (); i != c.End (); ++i)
    {
      Ptr<Node> node = *i;
      Ptr<NetDevice> device = InstallSingleEnbDevice (node);
      devices.Add (device);
    }
  return devices;
}

        if (m_componentCarrierPhyParams.size() == 0) {
            DoComponentCarrierConfigure(dev->GetUlEarfcn(), dev->GetDlEarfcn(), dev->GetUlBandwidth(),
                                        dev->GetDlBandwidth());
        }

        NS_ASSERT_MSG(m_componentCarrierPhyParams.size() != 0, "Cannot create enb ccm map.");
        // create component carrier map for this eNb device
        std::map<uint8_t, Ptr<ComponentCarrierEnb> > ccMap;
        for (std::map<uint8_t, ComponentCarrier>::iterator it = m_componentCarrierPhyParams.begin();
             it != m_componentCarrierPhyParams.end(); ++it) {
            Ptr<ComponentCarrierEnb> cc = CreateObject<ComponentCarrierEnb>();
            cc->SetUlBandwidth(it->second.GetUlBandwidth());
            cc->SetDlBandwidth(it->second.GetDlBandwidth());
            cc->SetDlEarfcn(it->second.GetDlEarfcn());
            cc->SetUlEarfcn(it->second.GetUlEarfcn());
            cc->SetAsPrimary(it->second.IsPrimary());
            NS_ABORT_MSG_IF (m_cellIdCounter == 65535, "max num cells exceeded");
            cc->SetCellId(m_cellIdCounter++);
            ccMap[it->first] = cc;
        }
        NS_ABORT_MSG_IF (m_useCa && ccMap.size() < 2,
                         "You have to either specify carriers or disable carrier aggregation");
        NS_ASSERT (ccMap.size() == m_noOfCcs);

Ptr<NetDevice>
LteHelper::InstallSingleEnbDevice (Ptr<Node> n)
{
  NS_LOG_FUNCTION (this << n);
  uint16_t cellId = m_cellIdCounter; // \todo Remove, eNB has no cell ID

            Ptr<LteHarqPhy> harq = Create<LteHarqPhy>();
            dlPhy->SetHarqPhyModule(harq);
            ulPhy->SetHarqPhyModule(harq);
            phy->SetHarqPhyModule(harq);

  NS_ABORT_MSG_IF (m_componentCarrierPhyParams.size() != 0, "CC map is not clean");
  DoComponentCarrierConfigure (dev->GetUlEarfcn (), dev->GetDlEarfcn (),
                               dev->GetUlBandwidth (), dev->GetDlBandwidth ());
  NS_ABORT_MSG_IF (m_componentCarrierPhyParams.size() != m_noOfCcs,
                   "CC map size (" << m_componentCarrierPhyParams.size () <<
                   ") must be equal to number of carriers (" <<
                   m_noOfCcs << ")");

  // create component carrier map for this eNb device
  std::map<uint8_t,Ptr<ComponentCarrierEnb> > ccMap;
  for (std::map<uint8_t, ComponentCarrier >::iterator it = m_componentCarrierPhyParams.begin ();
       it != m_componentCarrierPhyParams.end ();
       ++it)
    {
      Ptr <ComponentCarrierEnb> cc = CreateObject<ComponentCarrierEnb> ();
      cc->SetUlBandwidth (it->second.GetUlBandwidth ());
      cc->SetDlBandwidth (it->second.GetDlBandwidth ());
      cc->SetDlEarfcn (it->second.GetDlEarfcn ());
      cc->SetUlEarfcn (it->second.GetUlEarfcn ());
      cc->SetAsPrimary (it->second.IsPrimary ());
      NS_ABORT_MSG_IF (m_cellIdCounter == 65535, "max num cells exceeded");
      cc->SetCellId (m_cellIdCounter++);
      ccMap [it->first] =  cc;
    }
  // CC map is not needed anymore
  m_componentCarrierPhyParams.clear ();

  NS_ABORT_MSG_IF (m_useCa && ccMap.size()<2, "You have to either specify carriers or disable carrier aggregation");
  NS_ASSERT (ccMap.size () == m_noOfCcs);

            Ptr<LteChunkProcessor> pInterf = Create<LteChunkProcessor>();
            pInterf->AddCallback(MakeCallback(&LteEnbPhy::ReportInterference, phy));
            ulPhy->AddInterferenceDataChunkProcessor(pInterf);   // for interference power tracing

            dlPhy->SetChannel(m_downlinkChannel);
            ulPhy->SetChannel(m_uplinkChannel);

            Ptr<MobilityModel> mm = n->GetObject<MobilityModel>();
            NS_ASSERT_MSG (mm, "MobilityModel needs to be set on node before calling LteHelper::InstallEnbDevice ()");
            dlPhy->SetMobility(mm);
            ulPhy->SetMobility(mm);

            Ptr<AntennaModel> antenna = (m_enbAntennaModelFactory.Create())->GetObject<AntennaModel>();
            NS_ASSERT_MSG (antenna, "error in creating the AntennaModel object");
            dlPhy->SetAntenna(antenna);
            ulPhy->SetAntenna(antenna);

            Ptr<LteEnbMac> mac = CreateObject<LteEnbMac>();
            Ptr<FfMacScheduler> sched = m_schedulerFactory.Create<FfMacScheduler>();
            Ptr<LteFfrAlgorithm> ffrAlgorithm = m_ffrAlgorithmFactory.Create<LteFfrAlgorithm>();
            it->second->SetMac(mac);
            it->second->SetFfMacScheduler(sched);
            it->second->SetFfrAlgorithm(ffrAlgorithm);

            it->second->SetPhy(phy);

        }

        Ptr<LteEnbRrc> rrc = CreateObject<LteEnbRrc>();
        Ptr<LteEnbComponentCarrierManager> ccmEnbManager = m_enbComponentCarrierManagerFactory.Create<LteEnbComponentCarrierManager>();
        rrc->ConfigureCarriers(ccMap);

        //ComponentCarrierManager SAP
        rrc->SetLteCcmRrcSapProvider(ccmEnbManager->GetLteCcmRrcSapProvider());
        ccmEnbManager->SetLteCcmRrcSapUser(rrc->GetLteCcmRrcSapUser());
        ccmEnbManager->SetNumberOfComponentCarriers(m_noOfCcs);
        ccmEnbManager->SetRrc(rrc);

        if (m_useIdealRrc) {
            Ptr<LteEnbRrcProtocolIdeal> rrcProtocol = CreateObject<LteEnbRrcProtocolIdeal>();
            rrcProtocol->SetLteEnbRrcSapProvider(rrc->GetLteEnbRrcSapProvider());
            rrc->SetLteEnbRrcSapUser(rrcProtocol->GetLteEnbRrcSapUser());
            rrc->AggregateObject(rrcProtocol);
            rrcProtocol->SetCellId(cellId);
        } else {
            Ptr<LteEnbRrcProtocolReal> rrcProtocol = CreateObject<LteEnbRrcProtocolReal>();
            rrcProtocol->SetLteEnbRrcSapProvider(rrc->GetLteEnbRrcSapProvider());
            rrc->SetLteEnbRrcSapUser(rrcProtocol->GetLteEnbRrcSapUser());
            rrc->AggregateObject(rrcProtocol);
            rrcProtocol->SetCellId(cellId);
        }

        if (m_epcHelper != 0) {
            EnumValue epsBearerToRlcMapping;
            rrc->GetAttribute("EpsBearerToRlcMapping", epsBearerToRlcMapping);
            // it does not make sense to use RLC/SM when also using the EPC
            if (epsBearerToRlcMapping.Get() == LteEnbRrc::RLC_SM_ALWAYS) {
                rrc->SetAttribute("EpsBearerToRlcMapping", EnumValue(LteEnbRrc::RLC_UM_ALWAYS));
            }
        }

        rrc->SetLteHandoverManagementSapProvider(handoverAlgorithm->GetLteHandoverManagementSapProvider());
        handoverAlgorithm->SetLteHandoverManagementSapUser(rrc->GetLteHandoverManagementSapUser());

        // This RRC attribute is used to connect each new RLC instance with the MAC layer
        // (for function such as TransmitPdu, ReportBufferStatusReport).
        // Since in this new architecture, the component carrier manager acts a proxy, it
        // will have its own LteMacSapProvider interface, RLC will see it as through original MAC
        // interface LteMacSapProvider, but the function call will go now through LteEnbComponentCarrierManager
        // instance that needs to implement functions of this interface, and its task will be to
        // forward these calls to the specific MAC of some of the instances of component carriers. This
        // decision will depend on the specific implementation of the component carrier manager.
        rrc->SetLteMacSapProvider(ccmEnbManager->GetLteMacSapProvider());

        bool ccmTest;
        for (std::map<uint8_t, Ptr<ComponentCarrierEnb> >::iterator it = ccMap.begin(); it != ccMap.end(); ++it) {
            it->second->GetPhy()->SetLteEnbCphySapUser(rrc->GetLteEnbCphySapUser(it->first));
            rrc->SetLteEnbCphySapProvider(it->second->GetPhy()->GetLteEnbCphySapProvider(), it->first);

            rrc->SetLteEnbCmacSapProvider(it->second->GetMac()->GetLteEnbCmacSapProvider(), it->first);
            it->second->GetMac()->SetLteEnbCmacSapUser(rrc->GetLteEnbCmacSapUser(it->first));

            it->second->GetPhy()->SetComponentCarrierId(it->first);
            it->second->GetMac()->SetComponentCarrierId(it->first);
            //FFR SAP
            it->second->GetFfMacScheduler()->SetLteFfrSapProvider(
                    it->second->GetFfrAlgorithm()->GetLteFfrSapProvider());
            it->second->GetFfrAlgorithm()->SetLteFfrSapUser(it->second->GetFfMacScheduler()->GetLteFfrSapUser());
            rrc->SetLteFfrRrcSapProvider(it->second->GetFfrAlgorithm()->GetLteFfrRrcSapProvider(), it->first);
            it->second->GetFfrAlgorithm()->SetLteFfrRrcSapUser(rrc->GetLteFfrRrcSapUser(it->first));
            //FFR SAP END

            // PHY <--> MAC SAP
            it->second->GetPhy()->SetLteEnbPhySapUser(it->second->GetMac()->GetLteEnbPhySapUser());
            it->second->GetMac()->SetLteEnbPhySapProvider(it->second->GetPhy()->GetLteEnbPhySapProvider());
            // PHY <--> MAC SAP END

            //Scheduler SAP
            it->second->GetMac()->SetFfMacSchedSapProvider(it->second->GetFfMacScheduler()->GetFfMacSchedSapProvider());
            it->second->GetMac()->SetFfMacCschedSapProvider(
                    it->second->GetFfMacScheduler()->GetFfMacCschedSapProvider());

            it->second->GetFfMacScheduler()->SetFfMacSchedSapUser(it->second->GetMac()->GetFfMacSchedSapUser());
            it->second->GetFfMacScheduler()->SetFfMacCschedSapUser(it->second->GetMac()->GetFfMacCschedSapUser());
            // Scheduler SAP END

            it->second->GetMac()->SetLteCcmMacSapUser(ccmEnbManager->GetLteCcmMacSapUser());
            ccmEnbManager->SetCcmMacSapProviders(it->first, it->second->GetMac()->GetLteCcmMacSapProvider());

            // insert the pointer to the LteMacSapProvider interface of the MAC layer of the specific component carrier
            ccmTest = ccmEnbManager->SetMacSapProvider(it->first, it->second->GetMac()->GetLteMacSapProvider());

            if (ccmTest == false) {
                NS_FATAL_ERROR ("Error in SetComponentCarrierMacSapProviders");
            }
        }


        dev->SetNode(n);
        dev->SetAttribute("CellId", UintegerValue(cellId));
        dev->SetAttribute("LteEnbComponentCarrierManager", PointerValue(ccmEnbManager));
        dev->SetCcMap(ccMap);
        std::map<uint8_t, Ptr<ComponentCarrierEnb> >::iterator it = ccMap.begin();
        dev->SetAttribute("LteEnbRrc", PointerValue(rrc));
        dev->SetAttribute("LteHandoverAlgorithm", PointerValue(handoverAlgorithm));
        dev->SetAttribute("LteFfrAlgorithm", PointerValue(it->second->GetFfrAlgorithm()));

        if (m_isAnrEnabled) {
            Ptr<LteAnr> anr = CreateObject<LteAnr>(cellId);
            rrc->SetLteAnrSapProvider(anr->GetLteAnrSapProvider());
            anr->SetLteAnrSapUser(rrc->GetLteAnrSapUser());
            dev->SetAttribute("LteAnr", PointerValue(anr));
        }

        for (it = ccMap.begin(); it != ccMap.end(); ++it) {
            Ptr<LteEnbPhy> ccPhy = it->second->GetPhy();
            ccPhy->SetDevice(dev);
            ccPhy->GetUlSpectrumPhy()->SetDevice(dev);
            ccPhy->GetDlSpectrumPhy()->SetDevice(dev);
            ccPhy->GetUlSpectrumPhy()->SetLtePhyRxDataEndOkCallback(MakeCallback(&LteEnbPhy::PhyPduReceived, ccPhy));
            ccPhy->GetUlSpectrumPhy()->SetLtePhyRxCtrlEndOkCallback(
                    MakeCallback(&LteEnbPhy::ReceiveLteControlMessageList, ccPhy));
            ccPhy->GetUlSpectrumPhy()->SetLtePhyUlHarqFeedbackCallback(
                    MakeCallback(&LteEnbPhy::ReceiveLteUlHarqFeedback, ccPhy));
            NS_LOG_LOGIC ("set the propagation model frequencies");
            double dlFreq = LteSpectrumValueHelper::GetCarrierFrequency(it->second->m_dlEarfcn);
            NS_LOG_LOGIC ("DL freq: " << dlFreq);
            bool dlFreqOk = m_downlinkPathlossModel->SetAttributeFailSafe("Frequency", DoubleValue(dlFreq));
            if (!dlFreqOk) {
                NS_LOG_WARN ("DL propagation model does not have a Frequency attribute");
            }

            double ulFreq = LteSpectrumValueHelper::GetCarrierFrequency(it->second->m_ulEarfcn);

            NS_LOG_LOGIC ("UL freq: " << ulFreq);
            bool ulFreqOk = m_uplinkPathlossModel->SetAttributeFailSafe("Frequency", DoubleValue(ulFreq));
            if (!ulFreqOk) {
                NS_LOG_WARN ("UL propagation model does not have a Frequency attribute");
            }
        }  //end for
        rrc->SetForwardUpCallback(MakeCallback(&LteEnbNetDevice::Receive, dev));
        dev->Initialize();
        n->AddDevice(dev);

        for (it = ccMap.begin(); it != ccMap.end(); ++it) {
            m_uplinkChannel->AddRx(it->second->GetPhy()->GetUlSpectrumPhy());
        }

        if (m_epcHelper != 0) {
            NS_LOG_INFO ("adding this eNB to the EPC");
            m_epcHelper->AddEnb(n, dev, dev->GetCellId());
            Ptr<EpcEnbApplication> enbApp = n->GetApplication(0)->GetObject<EpcEnbApplication>();
            NS_ASSERT_MSG (enbApp != 0, "cannot retrieve EpcEnbApplication");

            // S1 SAPs
            rrc->SetS1SapProvider(enbApp->GetS1SapProvider());
            enbApp->SetS1SapUser(rrc->GetS1SapUser());

            // X2 SAPs
            Ptr<EpcX2> x2 = n->GetObject<EpcX2>();
            x2->SetEpcX2SapUser(rrc->GetEpcX2SapUser());
            rrc->SetEpcX2SapProvider(x2->GetEpcX2SapProvider());
        }

        return dev;
    }

    Ptr<NetDevice>
    LteHelper::InstallSingleUeDevice(Ptr<Node> n) {
        NS_LOG_FUNCTION (this);

        NS_ABORT_MSG_IF (m_componentCarrierPhyParams.size() == 0 && m_useCa,
                         "If CA is enabled, before call this method you need to install Enbs --> InstallEnbDevice()");

        Ptr<LteUeNetDevice> dev = m_ueNetDeviceFactory.Create<LteUeNetDevice>();
        std::map<uint8_t, Ptr<ComponentCarrierUe> > ueCcMap;

        for (std::map<uint8_t, ComponentCarrier>::iterator it = m_componentCarrierPhyParams.begin();
             it != m_componentCarrierPhyParams.end(); ++it) {
            Ptr<ComponentCarrierUe> cc = CreateObject<ComponentCarrierUe>();
            cc->SetUlBandwidth(it->second.GetUlBandwidth());
            cc->SetDlBandwidth(it->second.GetDlBandwidth());
            cc->SetDlEarfcn(it->second.GetDlEarfcn());
            cc->SetUlEarfcn(it->second.GetUlEarfcn());
            cc->SetAsPrimary(it->second.IsPrimary());
            Ptr<LteUeMac> mac = CreateObject<LteUeMac>();
            cc->SetMac(mac);
            // cc->GetPhy ()->Initialize (); // it is initialized within the LteUeNetDevice::DoInitialize ()
            ueCcMap.insert(std::pair<uint8_t, Ptr<ComponentCarrierUe> >(it->first, cc));
        }

        for (std::map<uint8_t, Ptr<ComponentCarrierUe> >::iterator it = ueCcMap.begin(); it != ueCcMap.end(); ++it) {
            Ptr<LteSpectrumPhy> dlPhy = CreateObject<LteSpectrumPhy>();
            Ptr<LteSpectrumPhy> ulPhy = CreateObject<LteSpectrumPhy>();

            Ptr<LteUePhy> phy = CreateObject<LteUePhy>(dlPhy, ulPhy);

            Ptr<LteHarqPhy> harq = Create<LteHarqPhy>();
            dlPhy->SetHarqPhyModule(harq);
            ulPhy->SetHarqPhyModule(harq);
            phy->SetHarqPhyModule(harq);

            Ptr<LteChunkProcessor> pRs = Create<LteChunkProcessor>();
            pRs->AddCallback(MakeCallback(&LteUePhy::ReportRsReceivedPower, phy));
            dlPhy->AddRsPowerChunkProcessor(pRs);

            Ptr<LteChunkProcessor> pInterf = Create<LteChunkProcessor>();
            pInterf->AddCallback(MakeCallback(&LteUePhy::ReportInterference, phy));
            dlPhy->AddInterferenceCtrlChunkProcessor(pInterf);   // for RSRQ evaluation of UE Measurements

            Ptr<LteChunkProcessor> pCtrl = Create<LteChunkProcessor>();
            pCtrl->AddCallback(MakeCallback(&LteSpectrumPhy::UpdateSinrPerceived, dlPhy));
            dlPhy->AddCtrlSinrChunkProcessor(pCtrl);

            Ptr<LteChunkProcessor> pData = Create<LteChunkProcessor>();
            pData->AddCallback(MakeCallback(&LteSpectrumPhy::UpdateSinrPerceived, dlPhy));
            dlPhy->AddDataSinrChunkProcessor(pData);

            if (m_usePdschForCqiGeneration) {
                // CQI calculation based on PDCCH for signal and PDSCH for interference
                pCtrl->AddCallback(MakeCallback(&LteUePhy::GenerateMixedCqiReport, phy));
                Ptr<LteChunkProcessor> pDataInterf = Create<LteChunkProcessor>();
                pDataInterf->AddCallback(MakeCallback(&LteUePhy::ReportDataInterference, phy));
                dlPhy->AddInterferenceDataChunkProcessor(pDataInterf);
            } else {
                // CQI calculation based on PDCCH for both signal and interference
                pCtrl->AddCallback(MakeCallback(&LteUePhy::GenerateCtrlCqiReport, phy));
            }

            dlPhy->SetChannel(m_downlinkChannel);
            ulPhy->SetChannel(m_uplinkChannel);

            Ptr<MobilityModel> mm = n->GetObject<MobilityModel>();
            NS_ASSERT_MSG (mm, "MobilityModel needs to be set on node before calling LteHelper::InstallUeDevice ()");
            dlPhy->SetMobility(mm);
            ulPhy->SetMobility(mm);

            Ptr<AntennaModel> antenna = (m_ueAntennaModelFactory.Create())->GetObject<AntennaModel>();
            NS_ASSERT_MSG (antenna, "error in creating the AntennaModel object");
            dlPhy->SetAntenna(antenna);
            ulPhy->SetAntenna(antenna);

            it->second->SetPhy(phy);
        }
        Ptr<LteUeComponentCarrierManager> ccmUe = m_ueComponentCarrierManagerFactory.Create<LteUeComponentCarrierManager>();
        ccmUe->SetNumberOfComponentCarriers(m_noOfCcs);

        Ptr<LteUeRrc> rrc = CreateObject<LteUeRrc>();
        rrc->m_numberOfComponentCarriers = m_noOfCcs;
        // run intializeSap to create the proper number of sap provider/users
        rrc->InitializeSap();
        rrc->SetLteMacSapProvider(ccmUe->GetLteMacSapProvider());
        // setting ComponentCarrierManager SAP
        rrc->SetLteCcmRrcSapProvider(ccmUe->GetLteCcmRrcSapProvider());
        ccmUe->SetLteCcmRrcSapUser(rrc->GetLteCcmRrcSapUser());

        if (m_useIdealRrc) {
            Ptr<LteUeRrcProtocolIdeal> rrcProtocol = CreateObject<LteUeRrcProtocolIdeal>();
            rrcProtocol->SetUeRrc(rrc);
            rrc->AggregateObject(rrcProtocol);
            rrcProtocol->SetLteUeRrcSapProvider(rrc->GetLteUeRrcSapProvider());
            rrc->SetLteUeRrcSapUser(rrcProtocol->GetLteUeRrcSapUser());
        } else {
            Ptr<LteUeRrcProtocolReal> rrcProtocol = CreateObject<LteUeRrcProtocolReal>();
            rrcProtocol->SetUeRrc(rrc);
            rrc->AggregateObject(rrcProtocol);
            rrcProtocol->SetLteUeRrcSapProvider(rrc->GetLteUeRrcSapProvider());
            rrc->SetLteUeRrcSapUser(rrcProtocol->GetLteUeRrcSapUser());
        }

        if (m_epcHelper != 0) {
            rrc->SetUseRlcSm(false);
        }
        Ptr<EpcUeNas> nas = CreateObject<EpcUeNas>();

        nas->SetAsSapProvider(rrc->GetAsSapProvider());
        rrc->SetAsSapUser(nas->GetAsSapUser());

        for (std::map<uint8_t, Ptr<ComponentCarrierUe> >::iterator it = ueCcMap.begin(); it != ueCcMap.end(); ++it) {
            rrc->SetLteUeCmacSapProvider(it->second->GetMac()->GetLteUeCmacSapProvider(), it->first);
            it->second->GetMac()->SetLteUeCmacSapUser(rrc->GetLteUeCmacSapUser(it->first));
            it->second->GetMac()->SetComponentCarrierId(it->first);

            it->second->GetPhy()->SetLteUeCphySapUser(rrc->GetLteUeCphySapUser(it->first));
            rrc->SetLteUeCphySapProvider(it->second->GetPhy()->GetLteUeCphySapProvider(), it->first);
            it->second->GetPhy()->SetComponentCarrierId(it->first);

            it->second->GetPhy()->SetLteUePhySapUser(it->second->GetMac()->GetLteUePhySapUser());
            it->second->GetMac()->SetLteUePhySapProvider(it->second->GetPhy()->GetLteUePhySapProvider());

            bool ccmTest = ccmUe->SetComponentCarrierMacSapProviders(it->first,
                                                                     it->second->GetMac()->GetLteMacSapProvider());

            if (ccmTest == false) {
                NS_FATAL_ERROR ("Error in SetComponentCarrierMacSapProviders");
            }
        }

        NS_ABORT_MSG_IF (m_imsiCounter >= 0xFFFFFFFF, "max num UEs exceeded");
        uint64_t imsi = ++m_imsiCounter;


        dev->SetNode(n);
        dev->SetAttribute("Imsi", UintegerValue(imsi));
        dev->SetCcMap(ueCcMap);
        dev->SetAttribute("LteUeRrc", PointerValue(rrc));
        dev->SetAttribute("EpcUeNas", PointerValue(nas));
        dev->SetAttribute("LteUeComponentCarrierManager", PointerValue(ccmUe));

        for (std::map<uint8_t, Ptr<ComponentCarrierUe> >::iterator it = ueCcMap.begin(); it != ueCcMap.end(); ++it) {
            Ptr<LteUePhy> ccPhy = it->second->GetPhy();
            ccPhy->SetDevice(dev);
            ccPhy->GetUlSpectrumPhy()->SetDevice(dev);
            ccPhy->GetDlSpectrumPhy()->SetDevice(dev);
            ccPhy->GetDlSpectrumPhy()->SetLtePhyRxDataEndOkCallback(MakeCallback(&LteUePhy::PhyPduReceived, ccPhy));
            ccPhy->GetDlSpectrumPhy()->SetLtePhyRxCtrlEndOkCallback(
                    MakeCallback(&LteUePhy::ReceiveLteControlMessageList, ccPhy));
            ccPhy->GetDlSpectrumPhy()->SetLtePhyRxPssCallback(MakeCallback(&LteUePhy::ReceivePss, ccPhy));
            ccPhy->GetDlSpectrumPhy()->SetLtePhyDlHarqFeedbackCallback(
                    MakeCallback(&LteUePhy::ReceiveLteDlHarqFeedback, ccPhy));
        }

        nas->SetDevice(dev);

        n->AddDevice(dev);

        nas->SetForwardUpCallback(MakeCallback(&LteUeNetDevice::Receive, dev));

        if (m_epcHelper != 0) {
            m_epcHelper->AddUe(dev, dev->GetImsi());
        }

        dev->Initialize();

        return dev;
    }


    void
    LteHelper::Attach(NetDeviceContainer ueDevices) {
        NS_LOG_FUNCTION (this);
        for (NetDeviceContainer::Iterator i = ueDevices.Begin(); i != ueDevices.End(); ++i) {
            Attach(*i);
        }
    }

  Ptr<LteUeNetDevice> dev = m_ueNetDeviceFactory.Create<LteUeNetDevice> ();

  // Initialize the component carriers with default values in order to initialize MACs and PHYs
  // of each component carrier. These values must be updated once the UE is attached to the
  // eNB and receives RRC Connection Reconfiguration message. In case of primary carrier or
  // a single carrier, these values will be updated once the UE will receive SIB2 and MIB.
  NS_ABORT_MSG_IF (m_componentCarrierPhyParams.size() != 0, "CC map is not clean");
  DoComponentCarrierConfigure (dev->GetDlEarfcn () + 18000, dev->GetDlEarfcn (), 25, 25);
  NS_ABORT_MSG_IF (m_componentCarrierPhyParams.size() != m_noOfCcs,
                   "CC map size (" << m_componentCarrierPhyParams.size () <<
                   ") must be equal to number of carriers (" <<
                   m_noOfCcs << ")");

  std::map<uint8_t, Ptr<ComponentCarrierUe> > ueCcMap;

  for (std::map< uint8_t, ComponentCarrier >::iterator it = m_componentCarrierPhyParams.begin();
       it != m_componentCarrierPhyParams.end();
       ++it)
    {
      Ptr <ComponentCarrierUe> cc = CreateObject<ComponentCarrierUe> ();
      cc->SetUlBandwidth (it->second.GetUlBandwidth ());
      cc->SetDlBandwidth (it->second.GetDlBandwidth ());
      cc->SetDlEarfcn (it->second.GetDlEarfcn ());
      cc->SetUlEarfcn (it->second.GetUlEarfcn ());
      cc->SetAsPrimary (it->second.IsPrimary ());
      Ptr<LteUeMac> mac = CreateObject<LteUeMac> ();
      cc->SetMac (mac);
      // cc->GetPhy ()->Initialize (); // it is initialized within the LteUeNetDevice::DoInitialize ()
      ueCcMap.insert (std::pair<uint8_t, Ptr<ComponentCarrierUe> > (it->first, cc));
    }
  // CC map is not needed anymore
  m_componentCarrierPhyParams.clear ();

    void
    LteHelper::Attach(NetDeviceContainer ueDevices, Ptr<NetDevice> enbDevice) {
        NS_LOG_FUNCTION (this);
        for (NetDeviceContainer::Iterator i = ueDevices.Begin(); i != ueDevices.End(); ++i) {
            Attach(*i, enbDevice);
        }
    }

    void
    LteHelper::Attach(Ptr<NetDevice> ueDevice, Ptr<NetDevice> enbDevice) {
        NS_LOG_FUNCTION (this);
        //enbRrc->SetCellId (enbDevice->GetObject<LteEnbNetDevice> ()->GetCellId ());

        Ptr<LteUeNetDevice> ueLteDevice = ueDevice->GetObject<LteUeNetDevice>();
        Ptr<LteEnbNetDevice> enbLteDevice = enbDevice->GetObject<LteEnbNetDevice>();

        Ptr<EpcUeNas> ueNas = ueLteDevice->GetNas();
        ueNas->Connect(enbLteDevice->GetCellId(), enbLteDevice->GetDlEarfcn());

        if (m_epcHelper != 0) {
            // activate default EPS bearer
            m_epcHelper->ActivateEpsBearer(ueDevice, ueLteDevice->GetImsi(), EpcTft::Default(),
                                           EpsBearer(EpsBearer::NGBR_VIDEO_TCP_DEFAULT));
        }

        // tricks needed for the simplified LTE-only simulations
        if (m_epcHelper == 0) {
            ueDevice->GetObject<LteUeNetDevice>()->SetTargetEnb(enbDevice->GetObject<LteEnbNetDevice>());
        }
    }

    void
    LteHelper::AttachToClosestEnb(NetDeviceContainer ueDevices, NetDeviceContainer enbDevices) {
        NS_LOG_FUNCTION (this);
        for (NetDeviceContainer::Iterator i = ueDevices.Begin(); i != ueDevices.End(); ++i) {
            AttachToClosestEnb(*i, enbDevices);
        }
    }

    void
    LteHelper::AttachToClosestEnb(Ptr<NetDevice> ueDevice, NetDeviceContainer enbDevices) {
        NS_LOG_FUNCTION (this);
        NS_ASSERT_MSG (enbDevices.GetN() > 0, "empty enb device container");
        Vector uepos = ueDevice->GetNode()->GetObject<MobilityModel>()->GetPosition();
        double minDistance = std::numeric_limits<double>::infinity();
        Ptr<NetDevice> closestEnbDevice;
        for (NetDeviceContainer::Iterator i = enbDevices.Begin(); i != enbDevices.End(); ++i) {
            Vector enbpos = (*i)->GetNode()->GetObject<MobilityModel>()->GetPosition();
            double distance = CalculateDistance(uepos, enbpos);
            if (distance < minDistance) {
                minDistance = distance;
                closestEnbDevice = *i;
            }
        }
        NS_ASSERT (closestEnbDevice != 0);
        Attach(ueDevice, closestEnbDevice);
    }

    uint8_t
    LteHelper::ActivateDedicatedEpsBearer(NetDeviceContainer ueDevices, EpsBearer bearer, Ptr<EpcTft> tft) {
        NS_LOG_FUNCTION (this);
        for (NetDeviceContainer::Iterator i = ueDevices.Begin(); i != ueDevices.End(); ++i) {
            uint8_t bearerId = ActivateDedicatedEpsBearer(*i, bearer, tft);
            return bearerId;
        }
        return 0;
    }


    uint8_t
    LteHelper::ActivateDedicatedEpsBearer(Ptr<NetDevice> ueDevice, EpsBearer bearer, Ptr<EpcTft> tft) {
        NS_LOG_FUNCTION (this);

        NS_ASSERT_MSG (m_epcHelper != 0, "dedicated EPS bearers cannot be set up when the EPC is not used");

        uint64_t imsi = ueDevice->GetObject<LteUeNetDevice>()->GetImsi();
        uint8_t bearerId = m_epcHelper->ActivateEpsBearer(ueDevice, imsi, tft, bearer);
        return bearerId;
    }

/**
 * \ingroup lte
 *
 * DrbActivatior allows user to activate bearers for UEs
 * when EPC is not used. Activation function is hooked to
 * the Enb RRC Connection Estabilished trace source. When
 * UE change its RRC state to CONNECTED_NORMALLY, activation
 * function is called and bearer is activated.
*/
    class DrbActivator : public SimpleRefCount<DrbActivator> {
    public:
        /**
        * DrbActivator Constructor
        *
        * \param ueDevice the UeNetDevice for which bearer will be activated
        * \param bearer the bearer configuration
        */
        DrbActivator(Ptr<NetDevice> ueDevice, EpsBearer bearer);

        /**
         * Function hooked to the Enb RRC Connection Established trace source
         * Fired upon successful RRC connection establishment.
         *
         * \param a DrbActivator object
         * \param context
         * \param imsi
         * \param cellId
         * \param rnti
         */
        static void
        ActivateCallback(Ptr<DrbActivator> a, std::string context, uint64_t imsi, uint16_t cellId, uint16_t rnti);

        /**
         * Procedure firstly checks if bearer was not activated, if IMSI
         * from trace source equals configured one and if UE is really
         * in RRC connected state. If all requirements are met, it performs
         * bearer activation.
         *
         * \param imsi
         * \param cellId
         * \param rnti
         */
        void ActivateDrb(uint64_t imsi, uint16_t cellId, uint16_t rnti);

    private:
        /**
         * Bearer can be activated only once. This value stores state of
         * bearer. Initially is set to false and changed to true during
         * bearer activation.
         */
        bool m_active;
        /**
         * UeNetDevice for which bearer will be activated
         */
        Ptr<NetDevice> m_ueDevice;
        /**
         * Configuration of bearer which will be activated
         */
        EpsBearer m_bearer;
        /**
         * imsi the unique UE identifier
         */
        uint64_t m_imsi;
    };

    DrbActivator::DrbActivator(Ptr<NetDevice> ueDevice, EpsBearer bearer)
            : m_active(false),
              m_ueDevice(ueDevice),
              m_bearer(bearer),
              m_imsi(m_ueDevice->GetObject<LteUeNetDevice>()->GetImsi()) {
    }

    void
    DrbActivator::ActivateCallback(Ptr<DrbActivator> a, std::string context, uint64_t imsi, uint16_t cellId,
                                   uint16_t rnti) {
        NS_LOG_FUNCTION (a << context << imsi << cellId << rnti);
        a->ActivateDrb(imsi, cellId, rnti);
    }

    void
    DrbActivator::ActivateDrb(uint64_t imsi, uint16_t cellId, uint16_t rnti) {
        NS_LOG_FUNCTION (this << imsi << cellId << rnti << m_active);
        if ((!m_active) && (imsi == m_imsi)) {
            Ptr<LteUeRrc> ueRrc = m_ueDevice->GetObject<LteUeNetDevice>()->GetRrc();
            NS_ASSERT (ueRrc->GetState() == LteUeRrc::CONNECTED_NORMALLY);
            uint16_t rnti = ueRrc->GetRnti();
            Ptr<LteEnbNetDevice> enbLteDevice = m_ueDevice->GetObject<LteUeNetDevice>()->GetTargetEnb();
            Ptr<LteEnbRrc> enbRrc = enbLteDevice->GetObject<LteEnbNetDevice>()->GetRrc();
            NS_ASSERT (ueRrc->GetCellId() == enbLteDevice->GetCellId());
            Ptr<UeManager> ueManager = enbRrc->GetUeManager(rnti);
            NS_ASSERT (ueManager->GetState() == UeManager::CONNECTED_NORMALLY
                       || ueManager->GetState() == UeManager::CONNECTION_RECONFIGURATION);
            EpcEnbS1SapUser::DataRadioBearerSetupRequestParameters params;
            params.rnti = rnti;
            params.bearer = m_bearer;
            params.bearerId = 0;
            params.gtpTeid = 0; // don't care
            enbRrc->GetS1SapUser()->DataRadioBearerSetupRequest(params);
            m_active = true;
        }
    }


      it->second->GetPhy ()->SetLteUeCphySapUser (rrc->GetLteUeCphySapUser (it->first));
      rrc->SetLteUeCphySapProvider (it->second->GetPhy ()->GetLteUeCphySapProvider (), it->first);
      it->second->GetPhy ()->SetComponentCarrierId (it->first);
      it->second->GetPhy ()->SetLteUePhySapUser (it->second->GetMac ()->GetLteUePhySapUser ());
      it->second->GetMac ()->SetLteUePhySapProvider (it->second->GetPhy ()->GetLteUePhySapProvider ());

      bool ccmTest = ccmUe->SetComponentCarrierMacSapProviders (it->first, it->second->GetMac ()->GetLteMacSapProvider());

        // Normally it is the EPC that takes care of activating DRBs
        // when the UE gets connected. When the EPC is not used, we achieve
        // the same behavior by hooking a dedicated DRB activation function
        // to the Enb RRC Connection Established trace source


        Ptr<LteEnbNetDevice> enbLteDevice = ueDevice->GetObject<LteUeNetDevice>()->GetTargetEnb();

        std::ostringstream path;
        path << "/NodeList/" << enbLteDevice->GetNode()->GetId()
             << "/DeviceList/" << enbLteDevice->GetIfIndex()
             << "/LteEnbRrc/ConnectionEstablished";
        Ptr<DrbActivator> arg = Create<DrbActivator>(ueDevice, bearer);
        Config::Connect(path.str(), MakeBoundCallback(&DrbActivator::ActivateCallback, arg));
    }

    void
    LteHelper::AddX2Interface(NodeContainer enbNodes) {
        NS_LOG_FUNCTION (this);

        NS_ASSERT_MSG (m_epcHelper != 0, "X2 interfaces cannot be set up when the EPC is not used");

        for (NodeContainer::Iterator i = enbNodes.Begin(); i != enbNodes.End(); ++i) {
            for (NodeContainer::Iterator j = i + 1; j != enbNodes.End(); ++j) {
                AddX2Interface(*i, *j);
            }
        }
    }

    void
    LteHelper::AddX2Interface(Ptr<Node> enbNode1, Ptr<Node> enbNode2) {
        NS_LOG_FUNCTION (this);
        NS_LOG_INFO ("setting up the X2 interface");

        m_epcHelper->AddX2Interface(enbNode1, enbNode2);
    }

  dev->SetNode (n);
  dev->SetAttribute ("Imsi", UintegerValue (imsi));
  dev->SetCcMap (ueCcMap);
  dev->SetAttribute ("LteUeRrc", PointerValue (rrc));
  dev->SetAttribute ("EpcUeNas", PointerValue (nas));
  dev->SetAttribute ("LteUeComponentCarrierManager", PointerValue (ccmUe));
  // \todo The UE identifier should be dynamically set by the EPC
  // when the default PDP context is created. This is a simplification.
  dev->SetAddress (Mac64Address::Allocate ());

    void
    LteHelper::HandoverRequest(Time hoTime, Ptr<NetDevice> ueDev, Ptr<NetDevice> sourceEnbDev, uint16_t targetCellId) {
        NS_LOG_FUNCTION (this << ueDev << sourceEnbDev << targetCellId);
        NS_ASSERT_MSG (m_epcHelper,
                       "Handover requires the use of the EPC - did you forget to call LteHelper::SetEpcHelper () ?");
        Simulator::Schedule(hoTime, &LteHelper::DoHandoverRequest, this, ueDev, sourceEnbDev, targetCellId);
    }

    void
    LteHelper::DoHandoverRequest(Ptr<NetDevice> ueDev, Ptr<NetDevice> sourceEnbDev, uint16_t targetCellId) {
        NS_LOG_FUNCTION (this << ueDev << sourceEnbDev << targetCellId);

        Ptr<LteEnbRrc> sourceRrc = sourceEnbDev->GetObject<LteEnbNetDevice>()->GetRrc();
        uint16_t rnti = ueDev->GetObject<LteUeNetDevice>()->GetRrc()->GetRnti();
        sourceRrc->SendHandoverRequest(rnti, targetCellId);
    }

    void
    LteHelper::DeActivateDedicatedEpsBearer(Ptr<NetDevice> ueDevice, Ptr<NetDevice> enbDevice, uint8_t bearerId) {
        NS_LOG_FUNCTION (this << ueDevice << bearerId);
        NS_ASSERT_MSG (m_epcHelper != 0, "Dedicated EPS bearers cannot be de-activated when the EPC is not used");
        NS_ASSERT_MSG (bearerId != 1, "Default bearer cannot be de-activated until and unless and UE is released");

        DoDeActivateDedicatedEpsBearer(ueDevice, enbDevice, bearerId);
    }

    void
    LteHelper::DoDeActivateDedicatedEpsBearer(Ptr<NetDevice> ueDevice, Ptr<NetDevice> enbDevice, uint8_t bearerId) {
        NS_LOG_FUNCTION (this << ueDevice << bearerId);

        //Extract IMSI and rnti
        uint64_t imsi = ueDevice->GetObject<LteUeNetDevice>()->GetImsi();
        uint16_t rnti = ueDevice->GetObject<LteUeNetDevice>()->GetRrc()->GetRnti();


        Ptr<LteEnbRrc> enbRrc = enbDevice->GetObject<LteEnbNetDevice>()->GetRrc();

        enbRrc->DoSendReleaseDataRadioBearer(imsi, rnti, bearerId);
    }

    void
    LteHelper::DoComponentCarrierConfigure(uint32_t ulEarfcn, uint32_t dlEarfcn, uint8_t ulbw, uint8_t dlbw) {
        NS_ASSERT_MSG (m_componentCarrierPhyParams.size() == 0, "Cc map already exists.");
        Ptr<CcHelper> ccHelper = CreateObject<CcHelper>();
        ccHelper->SetNumberOfComponentCarriers(m_noOfCcs);
        ccHelper->SetUlEarfcn(ulEarfcn);
        ccHelper->SetDlEarfcn(dlEarfcn);
        ccHelper->SetDlBandwidth(dlbw);
        ccHelper->SetUlBandwidth(ulbw);
        m_componentCarrierPhyParams = ccHelper->EquallySpacedCcs();
        m_componentCarrierPhyParams.at(0).SetAsPrimary(true);
    }

    void
    LteHelper::ActivateDataRadioBearer(NetDeviceContainer ueDevices, EpsBearer bearer) {
        NS_LOG_FUNCTION (this);
        for (NetDeviceContainer::Iterator i = ueDevices.Begin(); i != ueDevices.End(); ++i) {
            ActivateDataRadioBearer(*i, bearer);
        }
    }

    void
    LteHelper::EnableLogComponents(void) {
        LogComponentEnable("LteHelper", LOG_LEVEL_ALL);
        LogComponentEnable("LteEnbRrc", LOG_LEVEL_ALL);
        LogComponentEnable("LteUeRrc", LOG_LEVEL_ALL);
        LogComponentEnable("LteEnbMac", LOG_LEVEL_ALL);
        LogComponentEnable("LteUeMac", LOG_LEVEL_ALL);
        LogComponentEnable("LteRlc", LOG_LEVEL_ALL);
        LogComponentEnable("LteRlcUm", LOG_LEVEL_ALL);
        LogComponentEnable("LteRlcAm", LOG_LEVEL_ALL);
        LogComponentEnable("RrFfMacScheduler", LOG_LEVEL_ALL);
        LogComponentEnable("PfFfMacScheduler", LOG_LEVEL_ALL);

        LogComponentEnable("LtePhy", LOG_LEVEL_ALL);
        LogComponentEnable("LteEnbPhy", LOG_LEVEL_ALL);
        LogComponentEnable("LteUePhy", LOG_LEVEL_ALL);
        LogComponentEnable("LteSpectrumValueHelper", LOG_LEVEL_ALL);
        LogComponentEnable("LteSpectrumPhy", LOG_LEVEL_ALL);
        LogComponentEnable("LteInterference", LOG_LEVEL_ALL);
        LogComponentEnable("LteChunkProcessor", LOG_LEVEL_ALL);

        std::string propModelStr = m_pathlossModelFactory.GetTypeId().GetName().erase(0, 5).c_str();
        LogComponentEnable("LteNetDevice", LOG_LEVEL_ALL);
        LogComponentEnable("LteUeNetDevice", LOG_LEVEL_ALL);
        LogComponentEnable("LteEnbNetDevice", LOG_LEVEL_ALL);

        LogComponentEnable("RadioBearerStatsCalculator", LOG_LEVEL_ALL);
        LogComponentEnable("LteStatsCalculator", LOG_LEVEL_ALL);
        LogComponentEnable("MacStatsCalculator", LOG_LEVEL_ALL);
        LogComponentEnable("PhyTxStatsCalculator", LOG_LEVEL_ALL);
        LogComponentEnable("PhyRxStatsCalculator", LOG_LEVEL_ALL);
        LogComponentEnable("PhyStatsCalculator", LOG_LEVEL_ALL);


    }

    void
    LteHelper::EnableTraces(void) {
        EnablePhyTraces();
        EnableMacTraces();
        EnableRlcTraces();
        EnablePdcpTraces();
    }

    void
    LteHelper::EnableRlcTraces(void) {
        NS_ASSERT_MSG (m_rlcStats == 0, "please make sure that LteHelper::EnableRlcTraces is called at most once");
        m_rlcStats = CreateObject<RadioBearerStatsCalculator>("RLC");
        m_radioBearerStatsConnector.EnableRlcStats(m_rlcStats);
    }

    int64_t
    LteHelper::AssignStreams(NetDeviceContainer c, int64_t stream) {
        int64_t currentStream = stream;
        if ((m_fadingModule != 0) && (m_fadingStreamsAssigned == false)) {
            Ptr<TraceFadingLossModel> tflm = m_fadingModule->GetObject<TraceFadingLossModel>();
            if (tflm != 0) {
                currentStream += tflm->AssignStreams(currentStream);
                m_fadingStreamsAssigned = true;
            }
        }
        Ptr<NetDevice> netDevice;
        for (NetDeviceContainer::Iterator i = c.Begin(); i != c.End(); ++i) {
            netDevice = (*i);
            Ptr<LteEnbNetDevice> lteEnb = DynamicCast<LteEnbNetDevice>(netDevice);
            if (lteEnb) {
                std::map<uint8_t, Ptr<ComponentCarrierEnb> > tmpMap = lteEnb->GetCcMap();
                std::map<uint8_t, Ptr<ComponentCarrierEnb> >::iterator it;
                it = tmpMap.begin();
                Ptr<LteSpectrumPhy> dlPhy = it->second->GetPhy()->GetDownlinkSpectrumPhy();
                Ptr<LteSpectrumPhy> ulPhy = it->second->GetPhy()->GetUplinkSpectrumPhy();
                currentStream += dlPhy->AssignStreams(currentStream);
                currentStream += ulPhy->AssignStreams(currentStream);
            }
            Ptr<LteUeNetDevice> lteUe = DynamicCast<LteUeNetDevice>(netDevice);
            if (lteUe) {
                std::map<uint8_t, Ptr<ComponentCarrierUe> > tmpMap = lteUe->GetCcMap();
                std::map<uint8_t, Ptr<ComponentCarrierUe> >::iterator it;
                it = tmpMap.begin();
                Ptr<LteSpectrumPhy> dlPhy = it->second->GetPhy()->GetDownlinkSpectrumPhy();
                Ptr<LteSpectrumPhy> ulPhy = it->second->GetPhy()->GetUplinkSpectrumPhy();
                Ptr<LteUeMac> ueMac = lteUe->GetMac();
                currentStream += dlPhy->AssignStreams(currentStream);
                currentStream += ulPhy->AssignStreams(currentStream);
                currentStream += ueMac->AssignStreams(currentStream);
            }
        }
        return (currentStream - stream);
    }


    void
    LteHelper::EnablePhyTraces(void) {
        EnableDlPhyTraces();
        EnableUlPhyTraces();
        EnableDlTxPhyTraces();
        EnableUlTxPhyTraces();
        EnableDlRxPhyTraces();
        EnableUlRxPhyTraces();
    }

    void
    LteHelper::EnableDlTxPhyTraces(void) {
        Config::Connect("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbPhy/DlPhyTransmission",
                        MakeBoundCallback(&PhyTxStatsCalculator::DlPhyTransmissionCallback, m_phyTxStats));
    }

    void
    LteHelper::EnableUlTxPhyTraces(void) {
        Config::Connect("/NodeList/*/DeviceList/*/ComponentCarrierMapUe/*/LteUePhy/UlPhyTransmission",
                        MakeBoundCallback(&PhyTxStatsCalculator::UlPhyTransmissionCallback, m_phyTxStats));
    }

    void
    LteHelper::EnableDlRxPhyTraces(void) {
        Config::Connect("/NodeList/*/DeviceList/*/ComponentCarrierMapUe/*/LteUePhy/DlSpectrumPhy/DlPhyReception",
                        MakeBoundCallback(&PhyRxStatsCalculator::DlPhyReceptionCallback, m_phyRxStats));
    }

    void
    LteHelper::EnableUlRxPhyTraces(void) {
        Config::Connect("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbPhy/UlSpectrumPhy/UlPhyReception",
                        MakeBoundCallback(&PhyRxStatsCalculator::UlPhyReceptionCallback, m_phyRxStats));
    }


    void
    LteHelper::EnableMacTraces(void) {
        EnableDlMacTraces();
        EnableUlMacTraces();
    }


    void
    LteHelper::EnableDlMacTraces(void) {
        NS_LOG_FUNCTION_NOARGS ();
        Config::Connect("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbMac/DlScheduling",
                        MakeBoundCallback(&MacStatsCalculator::DlSchedulingCallback, m_macStats));
    }

    void
    LteHelper::EnableUlMacTraces(void) {
        NS_LOG_FUNCTION_NOARGS ();
        Config::Connect("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbMac/UlScheduling",
                        MakeBoundCallback(&MacStatsCalculator::UlSchedulingCallback, m_macStats));
    }

    void
    LteHelper::EnableDlPhyTraces(void) {
        NS_LOG_FUNCTION_NOARGS ();
        Config::Connect("/NodeList/*/DeviceList/*/ComponentCarrierMapUe/*/LteUePhy/ReportCurrentCellRsrpSinr",
                        MakeBoundCallback(&PhyStatsCalculator::ReportCurrentCellRsrpSinrCallback, m_phyStats));
    }

    void
    LteHelper::EnableUlPhyTraces(void) {
        NS_LOG_FUNCTION_NOARGS ();
        Config::Connect("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbPhy/ReportUeSinr",
                        MakeBoundCallback(&PhyStatsCalculator::ReportUeSinr, m_phyStats));
        Config::Connect("/NodeList/*/DeviceList/*/ComponentCarrierMap/*/LteEnbPhy/ReportInterference",
                        MakeBoundCallback(&PhyStatsCalculator::ReportInterference, m_phyStats));

    }

    Ptr<RadioBearerStatsCalculator>
    LteHelper::GetRlcStats(void) {
        return m_rlcStats;
    }

    void
    LteHelper::EnablePdcpTraces(void) {
        NS_ASSERT_MSG (m_pdcpStats == 0, "please make sure that LteHelper::EnablePdcpTraces is called at most once");
        m_pdcpStats = CreateObject<RadioBearerStatsCalculator>("PDCP");
        m_radioBearerStatsConnector.EnablePdcpStats(m_pdcpStats);
    }

    Ptr<RadioBearerStatsCalculator>
    LteHelper::GetPdcpStats(void) {
        return m_pdcpStats;
    }

    /*PcapHelper::DataLinkType
    LteHelper::GetPcapDataLinkType(void) const {

        return PcapHelper::DLT_LTE;
    }

    void
    LteHelper::EnablePcapInternal(std::string prefix, Ptr<NetDevice> nd, bool promiscuous, bool explicitFilename) {
        //All of the Pcap enable functions vector through here including the ones
        //that are wandering through all of devices on perhaps all of the nodes in
        //the system. We can only deal with devices of type WifiNetDevice.
        Ptr<LteNetDevice> device = nd->GetObject<LteNetDevice>();
        if (device == 0) {
            NS_LOG_INFO ("LteHelper::EnablePcapInternal(): Device " << &device << " not of type ns3::LteNetDevice");
            return;
        }

        Ptr<LtePhy> phy = device->GetNode()->GetObject<LtePhy>();
        NS_ABORT_MSG_IF (phy == 0, "LteHelper::EnablePcapInternal(): Phy layer in LteNetDevice must be set");

        PcapHelper pcapHelper;

        std::string filename;
        if (explicitFilename) {
            filename = prefix;
        } else {
            filename = pcapHelper.GetFilenameFromDevice(prefix, device);
        }

        Ptr<PcapFileWrapper> file = pcapHelper.CreateFile(filename, std::ios::out, m_pcapDlt);

        phy->TraceConnectWithoutContext("MonitorSnifferTx", MakeBoundCallback(&LteHelper::PcapSniffTxEvent, file));
        phy->TraceConnectWithoutContext("MonitorSnifferRx", MakeBoundCallback(&LteHelper::PcapSniffRxEvent, file));
    }*/
/*
    void
    LteHelper::EnableAsciiInternal(
            Ptr<OutputStreamWrapper> stream,
            std::string prefix,
            Ptr<NetDevice> nd,
            bool explicitFilename) {
        //All of the ascii enable functions vector through here including the ones
        //that are wandering through all of devices on perhaps all of the nodes in
        //the system. We can only deal with devices of type WifiNetDevice.
        Ptr<LteNetDevice> device = nd->GetObject<LteNetDevice>();
        if (device == 0) {
            NS_LOG_INFO ("LteHelper::EnableAsciiInternal(): Device " << device << " not of type ns3::LteNetDevice");
            return;
        }

        //Our trace sinks are going to use packet printing, so we have to make sure
        //that is turned on.
        Packet::EnablePrinting();

        uint32_t nodeid = nd->GetNode()->GetId();
        uint32_t deviceid = nd->GetIfIndex();
        std::ostringstream oss;

        //If we are not provided an OutputStreamWrapper, we are expected to create
        //one using the usual trace filename conventions and write our traces
        //without a context since there will be one file per context and therefore
        //the context would be redundant.
        if (stream == 0) {
            //Set up an output stream object to deal with private ofstream copy
            //constructor and lifetime issues. Let the helper decide the actual
            //name of the file given the prefix.
            AsciiTraceHelper asciiTraceHelper;

            std::string filename;
            if (explicitFilename) {
                filename = prefix;
            } else {
                filename = asciiTraceHelper.GetFilenameFromDevice(prefix, device);
            }

            Ptr<OutputStreamWrapper> theStream = asciiTraceHelper.CreateFileStream(filename);
            //We could go poking through the phy and the state looking for the
            //correct trace source, but we can let Config deal with that with
            //some search cost.  Since this is presumably happening at topology
            //creation time, it doesn't seem much of a price to pay.
            oss.str("");
            oss << "/NodeList/" << nodeid << "/DeviceList/" << deviceid << "/$ns3::LteNetDevice/Phy/State/RxOk";
            Config::ConnectWithoutContext(oss.str(), MakeBoundCallback(&AsciiPhyReceiveSinkWithoutContext, theStream));

            oss.str("");
            oss << "/NodeList/" << nodeid << "/DeviceList/" << deviceid << "/$ns3::LteNetDevice/Phy/State/Tx";
            Config::ConnectWithoutContext(oss.str(), MakeBoundCallback(&AsciiPhyTransmitSinkWithoutContext, theStream));

            return;
        }

        //If we are provided an OutputStreamWrapper, we are expected to use it, and
        //to provide a context. We are free to come up with our own context if we
        //want, and use the AsciiTraceHelper Hook*WithContext functions, but for
        //compatibility and simplicity, we just use Config::Connect and let it deal
        //with coming up with a context.
        oss.str("");
        oss << "/NodeList/" << nodeid << "/DeviceList/" << deviceid << "/$ns3::LteNetDevice/Phy/State/RxOk";
        Config::Connect(oss.str(), MakeBoundCallback(&AsciiPhyReceiveSinkWithContext, stream));

        oss.str("");
        oss << "/NodeList/" << nodeid << "/DeviceList/" << deviceid << "/$ns3::LteNetDevice/Phy/State/Tx";
        Config::Connect(oss.str(), MakeBoundCallback(&AsciiPhyTransmitSinkWithContext, stream));
    }
*/

/*
    void
    LteHelper::PcapSniffTxEvent (
            Ptr<PcapFileWrapper> file,
            Ptr<const Packet>    packet,
            uint16_t             channelFreqMhz)
    {
        /*
        unsigned char g_PDUBuffer[16000];
        unsigned int  g_PDUOffset;
        unsigned char g_frameBuffer[16000];
        unsigned int  g_frameOffset;

        guint8 radioType = FDD_RADIO, direction = DIRECTION_DOWNLINK, rntiType = C_RNTI;
        guint16 rnti, ueid, subframeNumber;
        guint8 isPredefinedData, retx, crcStatus;

        Ptr<Packet> p = packet->Copy ();

        ssize_t bytesSent;
        g_frameOffset = 0;
        unsigned short tmp16;

void
LteHelper::DoComponentCarrierConfigure (uint32_t ulEarfcn, uint32_t dlEarfcn, uint8_t ulbw, uint8_t dlbw)
{
  NS_LOG_FUNCTION (this << ulEarfcn << dlEarfcn << ulbw << dlbw);

  NS_ABORT_MSG_IF (m_componentCarrierPhyParams.size() != 0, "CC map is not clean");
  Ptr<CcHelper> ccHelper = CreateObject<CcHelper> ();
  ccHelper->SetNumberOfComponentCarriers (m_noOfCcs);
  ccHelper->SetUlEarfcn (ulEarfcn);
  ccHelper->SetDlEarfcn (dlEarfcn);
  ccHelper->SetDlBandwidth (dlbw);
  ccHelper->SetUlBandwidth (ulbw);
  m_componentCarrierPhyParams = ccHelper->EquallySpacedCcs ();
  m_componentCarrierPhyParams.at (0).SetAsPrimary (true);
}

        // Fixed start to each frame (allowing heuristic dissector to work)
        // Not NULL terminated
        memcpy(g_frameBuffer+g_frameOffset, MAC_LTE_START_STRING,
               strlen(MAC_LTE_START_STRING));
        g_frameOffset += strlen(MAC_LTE_START_STRING);

void
LteHelper::EnableLogComponents (void)
{
  LogComponentEnableAll (LOG_PREFIX_TIME);
  LogComponentEnableAll (LOG_PREFIX_FUNC);
  LogComponentEnableAll (LOG_PREFIX_NODE);
  // Model directory
  LogComponentEnable ("A2A4RsrqHandoverAlgorithm", LOG_LEVEL_ALL);
  LogComponentEnable ("A3RsrpHandoverAlgorithm", LOG_LEVEL_ALL);
  LogComponentEnable ("Asn1Header", LOG_LEVEL_ALL);
  LogComponentEnable ("ComponentCarrier", LOG_LEVEL_ALL);
  LogComponentEnable ("ComponentCarrierEnb", LOG_LEVEL_ALL);
  LogComponentEnable ("ComponentCarrierUe", LOG_LEVEL_ALL);
  LogComponentEnable ("CqaFfMacScheduler", LOG_LEVEL_ALL);
  LogComponentEnable ("EpcEnbApplication", LOG_LEVEL_ALL);
  LogComponentEnable ("EpcMme", LOG_LEVEL_ALL);
  LogComponentEnable ("EpcSgwPgwApplication", LOG_LEVEL_ALL);
  LogComponentEnable ("EpcTft", LOG_LEVEL_ALL);
  LogComponentEnable ("EpcTftClassifier", LOG_LEVEL_ALL);
  LogComponentEnable ("EpcUeNas", LOG_LEVEL_ALL);
  LogComponentEnable ("EpcX2", LOG_LEVEL_ALL);
  LogComponentEnable ("EpcX2Header", LOG_LEVEL_ALL);
  LogComponentEnable ("FdBetFfMacScheduler", LOG_LEVEL_ALL);
  LogComponentEnable ("FdMtFfMacScheduler", LOG_LEVEL_ALL);
  LogComponentEnable ("FdTbfqFfMacScheduler", LOG_LEVEL_ALL);
  LogComponentEnable ("FfMacScheduler", LOG_LEVEL_ALL);
  LogComponentEnable ("GtpuHeader", LOG_LEVEL_ALL);
  LogComponentEnable ("LteAmc", LOG_LEVEL_ALL);
  LogComponentEnable ("LteAnr", LOG_LEVEL_ALL);
  LogComponentEnable ("LteChunkProcessor", LOG_LEVEL_ALL);
  LogComponentEnable ("LteCommon", LOG_LEVEL_ALL);
  LogComponentEnable ("LteControlMessage", LOG_LEVEL_ALL);
  LogComponentEnable ("LteEnbComponentCarrierManager", LOG_LEVEL_ALL);
  LogComponentEnable ("LteEnbMac", LOG_LEVEL_ALL);
  LogComponentEnable ("LteEnbNetDevice", LOG_LEVEL_ALL);
  LogComponentEnable ("LteEnbPhy", LOG_LEVEL_ALL);
  LogComponentEnable ("LteEnbRrc", LOG_LEVEL_ALL);
  LogComponentEnable ("LteFfrAlgorithm", LOG_LEVEL_ALL);
  LogComponentEnable ("LteFfrDistributedAlgorithm", LOG_LEVEL_ALL);
  LogComponentEnable ("LteFfrEnhancedAlgorithm", LOG_LEVEL_ALL);
  LogComponentEnable ("LteFfrSoftAlgorithm", LOG_LEVEL_ALL);
  LogComponentEnable ("LteFrHardAlgorithm", LOG_LEVEL_ALL);
  LogComponentEnable ("LteFrNoOpAlgorithm", LOG_LEVEL_ALL);
  LogComponentEnable ("LteFrSoftAlgorithm", LOG_LEVEL_ALL);
  LogComponentEnable ("LteFrStrictAlgorithm", LOG_LEVEL_ALL);
  LogComponentEnable ("LteHandoverAlgorithm", LOG_LEVEL_ALL);
  LogComponentEnable ("LteHarqPhy", LOG_LEVEL_ALL);
  LogComponentEnable ("LteInterference", LOG_LEVEL_ALL);
  LogComponentEnable ("LteMiErrorModel", LOG_LEVEL_ALL);
  LogComponentEnable ("LteNetDevice", LOG_LEVEL_ALL);
  LogComponentEnable ("LtePdcp", LOG_LEVEL_ALL);
  LogComponentEnable ("LtePdcpHeader", LOG_LEVEL_ALL);
  LogComponentEnable ("LtePhy", LOG_LEVEL_ALL);
  LogComponentEnable ("LteRlc", LOG_LEVEL_ALL);
  LogComponentEnable ("LteRlcAm", LOG_LEVEL_ALL);
  LogComponentEnable ("LteRlcAmHeader", LOG_LEVEL_ALL);
  LogComponentEnable ("LteRlcHeader", LOG_LEVEL_ALL);
  LogComponentEnable ("LteRlcTm", LOG_LEVEL_ALL);
  LogComponentEnable ("LteRlcUm", LOG_LEVEL_ALL);
  LogComponentEnable ("LteRrcProtocolIdeal", LOG_LEVEL_ALL);
  LogComponentEnable ("LteRrcProtocolReal", LOG_LEVEL_ALL);
  LogComponentEnable ("LteSpectrumPhy", LOG_LEVEL_ALL);
  LogComponentEnable ("LteSpectrumSignalParameters", LOG_LEVEL_ALL);
  LogComponentEnable ("LteSpectrumValueHelper", LOG_LEVEL_ALL);
  LogComponentEnable ("LteUeComponentCarrierManager", LOG_LEVEL_ALL);
  LogComponentEnable ("LteUeMac", LOG_LEVEL_ALL);
  LogComponentEnable ("LteUeNetDevice", LOG_LEVEL_ALL);
  LogComponentEnable ("LteUePhy", LOG_LEVEL_ALL);
  LogComponentEnable ("LteUePowerControl", LOG_LEVEL_ALL);
  LogComponentEnable ("LteUeRrc", LOG_LEVEL_ALL);
  LogComponentEnable ("LteVendorSpecificParameters", LOG_LEVEL_ALL);
  LogComponentEnable ("NoOpComponentCarrierManager", LOG_LEVEL_ALL);
  LogComponentEnable ("NoOpHandoverAlgorithm", LOG_LEVEL_ALL);
  LogComponentEnable ("PfFfMacScheduler", LOG_LEVEL_ALL);
  LogComponentEnable ("PssFfMacScheduler", LOG_LEVEL_ALL);
  LogComponentEnable ("RemSpectrumPhy", LOG_LEVEL_ALL);
  LogComponentEnable ("RrcHeader", LOG_LEVEL_ALL);
  LogComponentEnable ("RrFfMacScheduler", LOG_LEVEL_ALL);
  LogComponentEnable ("SimpleUeComponentCarrierManager", LOG_LEVEL_ALL);
  LogComponentEnable ("TdBetFfMacScheduler", LOG_LEVEL_ALL);
  LogComponentEnable ("TdMtFfMacScheduler", LOG_LEVEL_ALL);
  LogComponentEnable ("TdTbfqFfMacScheduler", LOG_LEVEL_ALL);
  LogComponentEnable ("TraceFadingLossModel", LOG_LEVEL_ALL);
  LogComponentEnable ("TtaFfMacScheduler", LOG_LEVEL_ALL);
  // Helper directory
  LogComponentEnable ("CcHelper", LOG_LEVEL_ALL);
  LogComponentEnable ("EmuEpcHelper", LOG_LEVEL_ALL);
  LogComponentEnable ("EpcHelper", LOG_LEVEL_ALL);
  LogComponentEnable ("LteGlobalPathlossDatabase", LOG_LEVEL_ALL);
  LogComponentEnable ("LteHelper", LOG_LEVEL_ALL);
  LogComponentEnable ("LteHexGridEnbTopologyHelper", LOG_LEVEL_ALL);
  LogComponentEnable ("LteStatsCalculator", LOG_LEVEL_ALL);
  LogComponentEnable ("MacStatsCalculator", LOG_LEVEL_ALL);
  LogComponentEnable ("PhyRxStatsCalculator", LOG_LEVEL_ALL);
  LogComponentEnable ("PhyStatsCalculator", LOG_LEVEL_ALL);
  LogComponentEnable ("PhyTxStatsCalculator", LOG_LEVEL_ALL);
  LogComponentEnable ("PointToPointEpcHelper", LOG_LEVEL_ALL);
  LogComponentEnable ("RadioBearerStatsCalculator", LOG_LEVEL_ALL);
  LogComponentEnable ("RadioBearerStatsConnector", LOG_LEVEL_ALL);
  LogComponentEnable ("RadioEnvironmentMapHelper", LOG_LEVEL_ALL);
}

        // Subframe number
        g_frameBuffer[g_frameOffset++] = MAC_LTE_SUBFRAME_TAG;
        tmp16 = htons(ueid);
        memcpy(g_frameBuffer+g_frameOffset, &tmp16, 2);
        g_frameOffset += 2;

        g_frameBuffer[g_frameOffset++] = MAC_LTE_CRC_STATUS_TAG;
        g_frameBuffer[g_frameOffset++] = crcStatus;



        // For these optional fields, no need to encode if value is default
        if (!isPredefinedData) {
            g_frameBuffer[g_frameOffset++] = MAC_LTE_PREDFINED_DATA_TAG;
            g_frameBuffer[g_frameOffset++] = isPredefinedData;
        }

        if (retx != 0) {
            g_frameBuffer[g_frameOffset++] = MAC_LTE_RETX_TAG;
            g_frameBuffer[g_frameOffset++] = retx;
        }



        // Now write the MAC PDU
        g_frameBuffer[g_frameOffset++] = MAC_LTE_PAYLOAD_TAG;

        // Append actual PDU
        memcpy(g_frameBuffer+g_frameOffset, g_PDUBuffer, g_PDUOffset);
        g_frameOffset += g_PDUOffset;
        p->AddHeader (header);
        file->Write (Simulator::Now (), p);
        return;
        */
/*
    }

    void
    LteHelper::PcapSniffRxEvent (
            Ptr<PcapFileWrapper>  file,
            Ptr<const Packet>     packet,
            uint16_t              channelFreqMhz,
            float        signalNoise)
    {
        /*
        uint32_t dlt = file->GetDataLinkType ();
        //WifiPreamble preamble = txVector.GetPreambleType ();

        switch (dlt)
        {
            case PcapHelper::DLT_IEEE802_11:
                file->Write (Simulator::Now (), packet);
                return;
            case PcapHelper::DLT_PRISM_HEADER:
            {
                NS_FATAL_ERROR ("PcapSniffRxEvent(): DLT_PRISM_HEADER not implemented");
                return;
            }
            case PcapHelper::DLT_IEEE802_11_RADIO:
            {
                Ptr<Packet> p = packet->Copy ();
                RadiotapHeader header;
                uint8_t frameFlags = RadiotapHeader::FRAME_FLAG_NONE;
                header.SetTsft (Simulator::Now ().GetMicroSeconds ());

                //Our capture includes the FCS, so we set the flag to say so.
                frameFlags |= RadiotapHeader::FRAME_FLAG_FCS_INCLUDED;

                if (preamble == WIFI_PREAMBLE_SHORT)
                {
                    frameFlags |= RadiotapHeader::FRAME_FLAG_SHORT_PREAMBLE;
                }

                if (txVector.GetGuardInterval () == 400)
                {
                    frameFlags |= RadiotapHeader::FRAME_FLAG_SHORT_GUARD;
                }

                header.SetFrameFlags (frameFlags);

                uint32_t rate;
                if (txVector.GetMode ().GetModulationClass () == WIFI_MOD_CLASS_HT || txVector.GetMode ().GetModulationClass () == WIFI_MOD_CLASS_VHT || txVector.GetMode ().GetModulationClass () == WIFI_MOD_CLASS_HE)
                {
                    rate = 128 + txVector.GetMode ().GetMcsValue ();
                }
                else
                {
                    rate = txVector.GetMode ().GetDataRate (txVector.GetChannelWidth (), txVector.GetGuardInterval (), 1) * txVector.GetNss () / 500000;
                }
                header.SetRate (rate);

                uint16_t channelFlags = 0;
                switch (rate)
                {
                    case 2:  //1Mbps
                    case 4:  //2Mbps
                    case 10: //5Mbps
                    case 22: //11Mbps
                        channelFlags |= RadiotapHeader::CHANNEL_FLAG_CCK;
                        break;

                    default:
                        channelFlags |= RadiotapHeader::CHANNEL_FLAG_OFDM;
                        break;
                }

                if (channelFreqMhz < 2500)
                {
                    channelFlags |= RadiotapHeader::CHANNEL_FLAG_SPECTRUM_2GHZ;
                }
                else
                {
                    channelFlags |= RadiotapHeader::CHANNEL_FLAG_SPECTRUM_5GHZ;
                }

                header.SetChannelFrequencyAndFlags (channelFreqMhz, channelFlags);

                header.SetAntennaSignalPower (signalNoise.signal);
                header.SetAntennaNoisePower (signalNoise.noise);

                if (preamble == WIFI_PREAMBLE_HT_MF || preamble == WIFI_PREAMBLE_HT_GF || preamble == WIFI_PREAMBLE_NONE)
                {
                    uint8_t mcsRate = 0;
                    uint8_t mcsKnown = RadiotapHeader::MCS_KNOWN_NONE;
                    uint8_t mcsFlags = RadiotapHeader::MCS_FLAGS_NONE;

                    mcsKnown |= RadiotapHeader::MCS_KNOWN_INDEX;
                    mcsRate = rate - 128;

                    mcsKnown |= RadiotapHeader::MCS_KNOWN_BANDWIDTH;
                    if (txVector.GetChannelWidth () == 40)
                    {
                        mcsFlags |= RadiotapHeader::MCS_FLAGS_BANDWIDTH_40;
                    }

                    mcsKnown |= RadiotapHeader::MCS_KNOWN_GUARD_INTERVAL;
                    if (txVector.GetGuardInterval () == 400)
                    {
                        mcsFlags |= RadiotapHeader::MCS_FLAGS_GUARD_INTERVAL;
                    }

                    mcsKnown |= RadiotapHeader::MCS_KNOWN_HT_FORMAT;
                    if (preamble == WIFI_PREAMBLE_HT_GF)
                    {
                        mcsFlags |= RadiotapHeader::MCS_FLAGS_HT_GREENFIELD;
                    }

                    mcsKnown |= RadiotapHeader::MCS_KNOWN_NESS;
                    if (txVector.GetNess () & 0x01) //bit 1
                    {
                        mcsFlags |= RadiotapHeader::MCS_FLAGS_NESS_BIT_0;
                    }
                    if (txVector.GetNess () & 0x02) //bit 2
                    {
                        mcsKnown |= RadiotapHeader::MCS_KNOWN_NESS_BIT_1;
                    }

                    mcsKnown |= RadiotapHeader::MCS_KNOWN_FEC_TYPE; //only BCC is currently supported

                    mcsKnown |= RadiotapHeader::MCS_KNOWN_STBC;
                    if (txVector.IsStbc ())
                    {
                        mcsFlags |= RadiotapHeader::MCS_FLAGS_STBC_STREAMS;
                    }

                    header.SetMcsFields (mcsKnown, mcsFlags, mcsRate);
                }

                if (txVector.IsAggregation ())
                {
                    uint16_t ampduStatusFlags = RadiotapHeader::A_MPDU_STATUS_NONE;
                    ampduStatusFlags |= RadiotapHeader::A_MPDU_STATUS_DELIMITER_CRC_KNOWN;
                    ampduStatusFlags |= RadiotapHeader::A_MPDU_STATUS_LAST_KNOWN;
                    // For PCAP file, MPDU Delimiter and Padding should be removed by the MAC Driver
                    AmpduSubframeHeader hdr;
                    uint32_t extractedLength;
                    p->RemoveHeader (hdr);
                    extractedLength = hdr.GetLength ();
                    p = p->CreateFragment (0, static_cast<uint32_t> (extractedLength));
                    if (aMpdu.type == LAST_MPDU_IN_AGGREGATE || (hdr.GetEof () == true && hdr.GetLength () > 0))
                    {
                        ampduStatusFlags |= RadiotapHeader::A_MPDU_STATUS_LAST;
                    }
                    header.SetAmpduStatus (aMpdu.mpduRefNumber, ampduStatusFlags, hdr.GetCrc ());
                }

                if (preamble == WIFI_PREAMBLE_VHT)
                {
                    uint16_t vhtKnown = RadiotapHeader::VHT_KNOWN_NONE;
                    uint8_t vhtFlags = RadiotapHeader::VHT_FLAGS_NONE;
                    uint8_t vhtBandwidth = 0;
                    uint8_t vhtMcsNss[4] = {0,0,0,0};
                    uint8_t vhtCoding = 0;
                    uint8_t vhtGroupId = 0;
                    uint16_t vhtPartialAid = 0;

                    vhtKnown |= RadiotapHeader::VHT_KNOWN_STBC;
                    if (txVector.IsStbc ())
                    {
                        vhtFlags |= RadiotapHeader::VHT_FLAGS_STBC;
                    }

                    vhtKnown |= RadiotapHeader::VHT_KNOWN_GUARD_INTERVAL;
                    if (txVector.GetGuardInterval () == 400)
                    {
                        vhtFlags |= RadiotapHeader::VHT_FLAGS_GUARD_INTERVAL;
                    }

                    vhtKnown |= RadiotapHeader::VHT_KNOWN_BEAMFORMED; //Beamforming is currently not supported

                    vhtKnown |= RadiotapHeader::VHT_KNOWN_BANDWIDTH;
                    //not all bandwidth values are currently supported
                    if (txVector.GetChannelWidth () == 40)
                    {
                        vhtBandwidth = 1;
                    }
                    else if (txVector.GetChannelWidth () == 80)
                    {
                        vhtBandwidth = 4;
                    }
                    else if (txVector.GetChannelWidth () == 160)
                    {
                        vhtBandwidth = 11;
                    }

                    //only SU PPDUs are currently supported
                    vhtMcsNss[0] |= (txVector.GetNss () & 0x0f);
                    vhtMcsNss[0] |= (((rate - 128) << 4) & 0xf0);

                    header.SetVhtFields (vhtKnown, vhtFlags, vhtBandwidth, vhtMcsNss, vhtCoding, vhtGroupId, vhtPartialAid);
                }

                p->AddHeader (header);
                file->Write (Simulator::Now (), p);
                return;
            }
            default:
                NS_ABORT_MSG ("PcapSniffRxEvent(): Unexpected data link type " << dlt);
        }
        /
    }*/
} // namespace ns3
