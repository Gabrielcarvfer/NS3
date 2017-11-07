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



#ifndef SRC_MMWAVE_MODEL_MMWAVE_PHY_H_
#define SRC_MMWAVE_MODEL_MMWAVE_PHY_H_

#include <ns3/spectrum-value.h>
#include <ns3/mobility-model.h>
#include <ns3/packet.h>
#include <ns3/nstime.h>
#include <ns3/spectrum-phy.h>
#include <ns3/spectrum-channel.h>
#include <ns3/spectrum-signal-parameters.h>
#include <ns3/spectrum-interference.h>
#include <ns3/generic-phy.h>
#include <ns3/antenna-array-model.h>
#include "mmwave-phy-mac-common.h"
#include "mmwave-spectrum-phy.h"
#include "mmwave-net-device.h"
#include "mmwave-phy-sap.h"
#include <string>
#include <map>

namespace ns3 {

class MmWaveNetDevice;
class MmWaveControlMessage;

class MmWavePhy : public Object
{
public:
	MmWavePhy();

	MmWavePhy(Ptr<MmWaveSpectrumPhy> dlChannelPhy, Ptr<MmWaveSpectrumPhy> ulChannelPhy);

	virtual ~MmWavePhy ();

	static TypeId GetTypeId (void);

	void SetDevice (Ptr<MmWaveNetDevice> d);

	Ptr<MmWaveNetDevice> GetDevice ();

	void SetChannel (Ptr<SpectrumChannel> c);

	/**
	 * \brief Compute the TX Power Spectral Density
	 * \return a pointer to a newly allocated SpectrumValue representing the TX Power Spectral Density in W/Hz for each Resource Block
	 */
	virtual Ptr<SpectrumValue> CreateTxPowerSpectralDensity () = 0;

	void DoDispose ();

	virtual void DoInitialize (void);

	/**
	 * \returns transmission time interval
	 */
	double GetTti (void) const;

	void DoSetCellId (uint16_t cellId);


	void SetNoiseFigure (double nf);
	double GetNoiseFigure (void) const;

	void SetControlMessage (Ptr<MmWaveControlMessage> m);
	std::list<Ptr<MmWaveControlMessage> > GetControlMessages (void);

	virtual void SetMacPdu (Ptr<Packet> pb);

	virtual void SendRachPreamble (uint32_t PreambleId, uint32_t Rnti);


//	virtual Ptr<PacketBurst> GetPacketBurst (void);
	virtual Ptr<PacketBurst> GetPacketBurst (SfnSf);

	void SetConfigurationParameters (Ptr<MmWavePhyMacCommon> ptrConfig);
	Ptr<MmWavePhyMacCommon> GetConfigurationParameters (void) const;

	MmWavePhySapProvider* GetPhySapProvider ();
//	void SetPhySapUser (MmWavePhySapUser* ptr);

	void UpdateCurrentAllocationAndSchedule (uint32_t frame, uint32_t sf);

	SfAllocInfo GetSfAllocInfo (uint8_t subframeNum);
	void SetDlSfAllocInfo (SfAllocInfo sfAllocInfo);
	void SetUlSfAllocInfo (SfAllocInfo sfAllocInfo);

protected:
	Ptr<MmWaveNetDevice> m_netDevice;

	Ptr<MmWaveSpectrumPhy> m_spectrumPhy;
	Ptr<MmWaveSpectrumPhy> m_downlinkSpectrumPhy;
	Ptr<MmWaveSpectrumPhy> m_uplinkSpectrumPhy;

	double m_txPower;
	double m_noiseFigure;

	uint16_t m_cellId;

	Ptr<MmWavePhyMacCommon> m_phyMacConfig;

	std::map<uint32_t, Ptr<PacketBurst> > m_packetBurstMap;
	std::vector< std::list<Ptr<MmWaveControlMessage> > > m_controlMessageQueue;

	TddSlotTypeList m_currTddMap;
//	std::list<SfAllocInfo> m_sfAllocInfoList;
	SfAllocInfo m_currSfAllocInfo;

	std::vector <SfAllocInfo> m_sfAllocInfo;		// maps subframe num to allocation info

	uint16_t m_frameNum;
	uint8_t	m_sfNum;
	uint8_t	m_slotNum;

	Time m_ctrlPeriod;
	Time m_dataPeriod;

	std::map <uint32_t,TddSlotTypeList> m_tddPatternForSlotMap;

	std::map <uint32_t,SfAllocInfo> m_slotAllocInfoMap;

	MmWavePhySapProvider* m_phySapProvider;

	uint32_t m_raPreambleId;

	bool m_sfAllocInfoUpdated;

private:
};

}


#endif /* SRC_MMWAVE_MODEL_MMWAVE_PHY_H_ */
