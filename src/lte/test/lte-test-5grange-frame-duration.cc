/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2019 Luis Pacheco
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
 * Author: Luis Pacheco <luisbelem@gmail.com>
 *
 */
#include <ns3/simulator.h>
#include <ns3/log.h>
#include <ns3/callback.h>
#include <ns3/config.h>
#include <ns3/string.h>
#include <ns3/double.h>
#include <ns3/enum.h>
#include <ns3/boolean.h>
#include <ns3/pointer.h>
#include "ns3/ff-mac-scheduler.h"
#include "ns3/mobility-helper.h"
#include "ns3/lte-helper.h"

#include "lte-ffr-simple.h"
#include "ns3/lte-rrc-sap.h"

#include "lte-test-5grange-frame-duration.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("Lte5grangeFrameDurationTest");

void
LteTestDlSchedulingCallback (Lte5grangeFrameDurationTestCase *testcase, std::string path, DlSchedulingCallbackInfo dlInfo)
{
  testcase->DlScheduling (dlInfo);
  testcase->lastSubFrame = Simulator::Now();
}

/**
 * TestSuite
 */

Lte5grangeFrameDurationTestSuite::Lte5grangeFrameDurationTestSuite ()
    : TestSuite ("lte-5grange-frame-duration", SYSTEM)
{
  //LogComponentEnable ("Lte5grangeFrameDurationTest", LOG_LEVEL_ALL);
  NS_LOG_INFO ("Creating Lte5grangeFrameDurationTestSuite");

  AddTestCase (new Lte5grangeFrameDurationTestCase ("Lte5grangeFrameDurationTestCase", 4600), TestCase::QUICK);

}

static Lte5grangeFrameDurationTestSuite lte5grangeFrameDurationTestSuite;


Lte5grangeFrameDurationTestCase::Lte5grangeFrameDurationTestCase (std::string name, uint64_t subFrameDur)
  : TestCase (name), lastSubFrame(Simulator::Now()), subFrameDuration(subFrameDur)
{
  NS_LOG_INFO ("Creating Lte5grangeFrameDurationTestCase");
}

Lte5grangeFrameDurationTestCase::~Lte5grangeFrameDurationTestCase ()
{
}

void
Lte5grangeFrameDurationTestCase::DlScheduling (DlSchedulingCallbackInfo dlInfo)
{
  //need to allow for RRC connection establishment + CQI feedback reception
  if (Simulator::Now () > MilliSeconds (161))
    {
      uint64_t diff = Simulator::Now ().GetMicroSeconds () - this->lastSubFrame.GetMicroSeconds ();
      NS_LOG_INFO("time: " << Simulator::Now () << " last sub: " << this->lastSubFrame  << " diff: " << diff << " frameNo: " << (uint32_t)dlInfo.frameNo << " subframeNo: " << (uint32_t)dlInfo.subframeNo);
      NS_TEST_ASSERT_MSG_EQ (diff, subFrameDuration, "Wrong Sub Frame Duration");
    }
}

void
Lte5grangeFrameDurationTestCase::DoRun (void)
{
  NS_LOG_INFO ("Lte5grangeFrameDurationTestCase");

  Config::Reset ();
  Config::SetDefault ("ns3::LteHelper::UseIdealRrc", BooleanValue (true));
  Config::SetDefault ("ns3::LteHelper::UsePdschForCqiGeneration", BooleanValue (true));

  Config::SetDefault ("ns3::LteSpectrumPhy::CtrlErrorModelEnabled", BooleanValue (true));
  Config::SetDefault ("ns3::LteSpectrumPhy::DataErrorModelEnabled", BooleanValue (true));

  Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();

  // Create Nodes: eNodeB and UE
  NodeContainer enbNodes;
  NodeContainer ueNodes1;
  enbNodes.Create (1);
  ueNodes1.Create (1);
  NodeContainer allNodes = NodeContainer ( enbNodes, ueNodes1);

  /*
   * The topology is the following:
   *
   *  eNB1                          UE1
   *    |                            |
   *    x -------------------------- x
   *                  500 m
   *
   */

  Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
  positionAlloc->Add (Vector (0.0, 0.0, 0.0));   // eNB1
  positionAlloc->Add (Vector (500.0, 0.0, 0.0));  // UE1
  MobilityHelper mobility;
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.SetPositionAllocator (positionAlloc);
  mobility.Install (allNodes);

  // Create Devices and install them in the Nodes (eNB and UE)
  NetDeviceContainer enbDev;
  NetDeviceContainer ueDevs1;
  lteHelper->SetSchedulerType ("ns3::PfFfMacScheduler");
  lteHelper->SetSchedulerAttribute ("UlCqiFilter", EnumValue (FfMacScheduler::PUSCH_UL_CQI));

  lteHelper->SetFfrAlgorithmType ("ns3::LteFrHardAlgorithm");

  /*lteHelper->SetFfrAlgorithmAttribute ("DlSubBandOffset", UintegerValue (0));
  lteHelper->SetFfrAlgorithmAttribute ("DlSubBandwidth", UintegerValue (12));
  lteHelper->SetFfrAlgorithmAttribute ("UlSubBandOffset", UintegerValue (0));
  lteHelper->SetFfrAlgorithmAttribute ("UlSubBandwidth", UintegerValue (25));*/
  enbDev = lteHelper->InstallEnbDevice (enbNodes.Get (0));

  ueDevs1 = lteHelper->InstallUeDevice (ueNodes1);

  // Attach a UE to a eNB
  lteHelper->Attach (ueDevs1, enbDev.Get (0));

  // Activate an EPS bearer
  enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE;
  EpsBearer bearer (q);
  lteHelper->ActivateDataRadioBearer (ueDevs1, bearer);

  //lteHelper->EnableTraces ();


  Config::Connect ("/NodeList/0/DeviceList/0/ComponentCarrierMap/*/LteEnbMac/DlScheduling",
                   MakeBoundCallback (&LteTestDlSchedulingCallback, this));

  //Config::Connect ("/NodeList/0/DeviceList/0/ComponentCarrierMap/*/LteEnbMac/UlScheduling",
  //                 MakeBoundCallback (&LteTestUlSchedulingCallback, this));

  //Config::Connect ("/NodeList/1/DeviceList/0/ComponentCarrierMap/*/LteEnbMac/DlScheduling",
   //                MakeBoundCallback (&LteTestDlSchedulingCallback, this));

  //Config::Connect ("/NodeList/1/DeviceList/0/ComponentCarrierMap/*/LteEnbMac/UlScheduling",
  //                 MakeBoundCallback (&LteTestUlSchedulingCallback, this));

  Simulator::Stop (Seconds (3));
  Simulator::Run ();

  Simulator::Destroy ();
}
