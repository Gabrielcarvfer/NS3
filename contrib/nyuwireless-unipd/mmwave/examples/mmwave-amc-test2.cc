 /* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
 /*
 *   Copyright (c) 2011 Centre Tecnologic de Telecomunicacions de Catalunya (CTTC)
 *   Copyright (c) 2015, NYU WIRELESS, Tandon School of Engineering, New York University
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License version 2 as
 *   published by the Free Software Foundation;
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *   Author: Marco Miozzo <marco.miozzo@cttc.es>
 *           Nicola Baldo  <nbaldo@cttc.es>
 *
 *   Modified by: Marco Mezzavilla < mezzavilla@nyu.edu>
 *        	 	  Sourjya Dutta <sdutta@nyu.edu>
 *        	 	  Russell Ford <russell.ford@nyu.edu>
 *        		  Menglei Zhang <menglei@nyu.edu>
 */


#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/config-store.h"
#include "ns3/mmwave-helper.h"
#include <ns3/buildings-helper.h>
#include "ns3/global-route-manager.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/log.h"
#include "ns3/mmwave-propagation-loss-model.h"

using namespace ns3;

double updateInterval = 2000.0;  // in ms
double increment = 0.5; // increment by x dB
double lossMin = 100.0;
double lossMax = 145.0;

void updateLoss (double loss, Ptr<MmWavePropagationLossModel> model)
{
//  std::cout << "************* distance changing to " << dist << " *************" << std::endl;
//  Ptr<MobilityModel> mobModel = ue->GetObject<MobilityModel> ();
//  mobModel->SetPosition (Vector (dist, 0.0, 0.0));
	model->SetLossFixedDb (loss);
  std::cout << "************* Path loss changing to " << loss << " *************" << std::endl;
  if (loss >= lossMax)
  {
  	return;
  }
	Simulator::Schedule (MilliSeconds(updateInterval), &updateLoss, loss+increment, model);
}

int 
main (int argc, char *argv[])
{
  /* Information regarding the traces generated:
   *
   * 1. UE_1_SINR.txt : Gives the SINR for each sub-band
   * 	Subframe no.  | Slot No. | Sub-band  | SINR (db)
   *
   * 2. UE_1_Tb_size.txt : Allocated transport block size
   * 	Time (micro-sec)  |  Tb-size in bytes
   * */

	LogComponentEnable ("MmWaveSpectrumPhy", LOG_LEVEL_DEBUG);
//	LogComponentEnable ("MmWaveBeamforming", LOG_LEVEL_DEBUG);
//	LogComponentEnable ("MmWaveUePhy", LOG_LEVEL_DEBUG);
//	LogComponentEnable ("MmWaveEnbPhy", LOG_LEVEL_DEBUG);
//	LogComponentEnable ("MmWaveFlexTtiMacScheduler", LOG_LEVEL_DEBUG);
	LogComponentEnable ("MmWavePhyRxTrace", LOG_LEVEL_DEBUG);
	//LogComponentEnable ("LteRlcUm", LOG_LEVEL_LOGIC);
	//LogComponentEnable ("MmWaveUeMac", LOG_LEVEL_LOGIC);
	//LogComponentEnable ("UdpClient", LOG_LEVEL_INFO);
	//LogComponentEnable ("PacketSink", LOG_LEVEL_INFO);
	//LogComponentEnable("PropagationLossModel",LOG_LEVEL_ALL);

	uint16_t numEnb = 1;
	uint16_t numUe = 1;

	double simTime = 1.0;
	bool harqEnabled = true;
	bool rlcAmEnabled = true;
	int mcs = -1;
	std::string channelState = "n";
	bool smallScale = true;
	double speed = 16;
	double dist = 100.0;
	// Command line arguments
	CommandLine cmd;
	cmd.AddValue("numEnb", "Number of eNBs", numEnb);
	cmd.AddValue("numUe", "Number of UEs per eNB", numUe);
	cmd.AddValue("simTime", "Total duration of the simulation [s])", simTime);
	cmd.AddValue("harq", "Enable Hybrid ARQ", harqEnabled);
	cmd.AddValue("mcs", "Fixed DL MCS", mcs);
	cmd.AddValue("channelState", "Channel state 'l'=LOS, 'n'=NLOS, 'a'=all", channelState);
	cmd.AddValue("lossMin", "Initial distance", lossMin);
	cmd.AddValue("lossMax", "Final distance", lossMax);
	cmd.AddValue("increment", "Path loss increment", increment);
	cmd.AddValue("updateInterval", "Period after which distance is updated", updateInterval);
	cmd.AddValue("smallScale", "Enable small scale fading", smallScale);
	cmd.AddValue("speed", "Constant speed", speed);

	cmd.AddValue("rlcAm", "Enable RLC-AM", rlcAmEnabled);
	cmd.Parse(argc, argv);

	if (lossMin >= lossMax)
	{
		lossMin = lossMax - 1;
	}

	simTime = ((lossMax - lossMin) / increment) * (updateInterval/1000.0);

	if (mcs >= 0 && mcs < 29)
	{
		Config::SetDefault ("ns3::MmWaveFlexTtiMacScheduler::FixedMcsDl", BooleanValue(true));
		Config::SetDefault ("ns3::MmWaveFlexTtiMacScheduler::McsDefaultDl", UintegerValue(mcs));
		Config::SetDefault ("ns3::MmWaveFlexTtiMacScheduler::FixedMcsUl", BooleanValue(true));
		Config::SetDefault ("ns3::MmWaveFlexTtiMacScheduler::McsDefaultUl", UintegerValue(mcs));
	}

	//Config::SetDefault ("ns3::MmWaveAmc::AmcModel", EnumValue (MmWaveAmc::PiroEW2010));
	Config::SetDefault ("ns3::MmWaveAmc::Ber", DoubleValue (0.01));
	Config::SetDefault ("ns3::MmWaveFlexTtiMacScheduler::HarqEnabled", BooleanValue(harqEnabled));
	Config::SetDefault ("ns3::MmWaveFlexTtiMacScheduler::DlSchedOnly", BooleanValue(false));
	Config::SetDefault ("ns3::MmWaveFlexTtiMacScheduler::UlSchedOnly", BooleanValue(true));
	Config::SetDefault ("ns3::MmWaveBeamforming::LongTermUpdatePeriod", TimeValue (Seconds (2*simTime)));
	Config::SetDefault ("ns3::LteEnbRrc::SystemInformationPeriodicity", TimeValue (MilliSeconds (1.0)));
	Config::SetDefault ("ns3::MmWaveBeamforming::SmallScaleFading", BooleanValue (smallScale));
	Config::SetDefault ("ns3::MmWaveBeamforming::FixSpeed", BooleanValue (true));
	Config::SetDefault ("ns3::MmWaveBeamforming::UeSpeed", DoubleValue (speed));
	Config::SetDefault ("ns3::MmWavePropagationLossModel::ChannelStates", StringValue (channelState));
	Config::SetDefault ("ns3::MmWavePropagationLossModel::FixedLossTst", BooleanValue (true));
	Config::SetDefault ("ns3::MmWavePropagationLossModel::LossFixedDb", DoubleValue (100.0));
	Config::SetDefault ("ns3::MmWaveHelper::RlcAmEnabled", BooleanValue(rlcAmEnabled));
	Config::SetDefault ("ns3::LteRlcAm::ReportBufferStatusTimer", TimeValue(MicroSeconds(100.0)));

  Ptr<MmWaveHelper> mmwHelper = CreateObject<MmWaveHelper> ();

  mmwHelper->Initialize();
  mmwHelper->SetHarqEnabled (harqEnabled);
  Ptr<MmWavePropagationLossModel> lossModel = mmwHelper->GetPathLossModel ()->GetObject<MmWavePropagationLossModel> ();

  /* A configuration example.
   * mmwHelper->GetPhyMacConfigurable ()->SetAttribute("SymbolPerSlot", UintegerValue(30)); */

  NodeContainer enbNodes;
  NodeContainer ueNodes;
  enbNodes.Create (numEnb);
  ueNodes.Create (numUe);

  Ptr<ListPositionAllocator> enbPositionAlloc = CreateObject<ListPositionAllocator> ();
  enbPositionAlloc->Add (Vector (0.0, 0.0, 0.0));

  MobilityHelper enbmobility;
  enbmobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  enbmobility.SetPositionAllocator(enbPositionAlloc);
  enbmobility.Install (enbNodes);
  BuildingsHelper::Install (enbNodes);

  MobilityHelper uemobility;
  Ptr<ListPositionAllocator> uePositionAlloc = CreateObject<ListPositionAllocator> ();
  uePositionAlloc->Add (Vector (dist, 0.0, 0.0));

  Simulator::Schedule (MilliSeconds(0), &updateLoss, lossMin, lossModel);

  uemobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  uemobility.SetPositionAllocator(uePositionAlloc);
  uemobility.Install (ueNodes);
  BuildingsHelper::Install (ueNodes);

  NetDeviceContainer enbNetDev = mmwHelper->InstallEnbDevice (enbNodes);
  NetDeviceContainer ueNetDev = mmwHelper->InstallUeDevice (ueNodes);

  mmwHelper->AttachToClosestEnb (ueNetDev, enbNetDev);
  mmwHelper->EnableTraces();

  // Activate a data radio bearer
  enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE;
  EpsBearer bearer (q);
  mmwHelper->ActivateDataRadioBearer (ueNetDev, bearer);

  Simulator::Stop (Seconds (simTime));
	NS_LOG_UNCOND ("Simulation running for " << simTime << " seconds");
  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}


