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
 * Author: Marco Miozzo <marco.miozzo@cttc.es>
 *         Nicola Baldo  <nbaldo@cttc.es>
 * Modified by:
 *          Danilo Abrignani <danilo.abrignani@unibo.it> (Carrier Aggregation - GSoC 2015)
 *          Biljana Bojovic <biljana.bojovic@cttc.es> (Carrier Aggregation)
 */


#include <ns3/log.h>
#include <ns3/pointer.h>
#include <ns3/packet.h>
#include <ns3/simulator.h>

#include "lte-amc.h"
#include "lte-control-messages.h"
#include "lte-enb-net-device.h"
#include "lte-ue-net-device.h"
#include <ns3/global-value.h>
#include <ns3/lte-enb-mac.h>
#include <ns3/lte-radio-bearer-tag.h>
#include <ns3/lte-ue-phy.h>

#include "ns3/lte-mac-sap.h"
#include "ns3/lte-enb-cmac-sap.h"
#include <ns3/lte-common.h>
#include <cinttypes>
#include <cstdint>
#include <bitset> //binary bitstream
#include <fstream>



namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("LteEnbMac");

NS_OBJECT_ENSURE_REGISTERED (LteEnbMac);


std::vector<int> LteEnbMac::nonDSAChannels;
#ifdef NS3_PYTORCH
    torch::jit::script::Module LteEnbMac::nn_module;
    int LteEnbMac::nn_width = 800;
    int LteEnbMac::nn_num_slices = 10;
#endif


// //////////////////////////////////////
// member SAP forwarders
// //////////////////////////////////////


/// EnbMacMemberLteEnbCmacSapProvider class
class EnbMacMemberLteEnbCmacSapProvider : public LteEnbCmacSapProvider
{
public:
  /**
   * Constructor
   *
   * \param mac the MAC
   */
  EnbMacMemberLteEnbCmacSapProvider (LteEnbMac* mac);

  // inherited from LteEnbCmacSapProvider
  virtual void ConfigureMac (uint8_t ulBandwidth, uint8_t dlBandwidth);
  virtual void AddUe (uint16_t rnti);
  virtual void RemoveUe (uint16_t rnti);
  virtual void AddLc (LcInfo lcinfo, LteMacSapUser* msu);
  virtual void ReconfigureLc (LcInfo lcinfo);
  virtual void ReleaseLc (uint16_t rnti, uint8_t lcid);
  virtual void UeUpdateConfigurationReq (UeConfig params);
  virtual RachConfig GetRachConfig ();
  virtual AllocateNcRaPreambleReturnValue AllocateNcRaPreamble (uint16_t rnti);


private:
  LteEnbMac* m_mac; ///< the MAC
};


EnbMacMemberLteEnbCmacSapProvider::EnbMacMemberLteEnbCmacSapProvider (LteEnbMac* mac)
  : m_mac (mac)
{
}

void
EnbMacMemberLteEnbCmacSapProvider::ConfigureMac (uint8_t ulBandwidth, uint8_t dlBandwidth)
{
  m_mac->DoConfigureMac (ulBandwidth, dlBandwidth);
}

void
EnbMacMemberLteEnbCmacSapProvider::AddUe (uint16_t rnti)
{
  m_mac->DoAddUe (rnti);
}

void
EnbMacMemberLteEnbCmacSapProvider::RemoveUe (uint16_t rnti)
{
  m_mac->DoRemoveUe (rnti);
}

void
EnbMacMemberLteEnbCmacSapProvider::AddLc (LcInfo lcinfo, LteMacSapUser* msu)
{
  m_mac->DoAddLc (lcinfo, msu);
}

void
EnbMacMemberLteEnbCmacSapProvider::ReconfigureLc (LcInfo lcinfo)
{
  m_mac->DoReconfigureLc (lcinfo);
}

void
EnbMacMemberLteEnbCmacSapProvider::ReleaseLc (uint16_t rnti, uint8_t lcid)
{
  m_mac->DoReleaseLc (rnti, lcid);
}

void
EnbMacMemberLteEnbCmacSapProvider::UeUpdateConfigurationReq (UeConfig params)
{
  m_mac->DoUeUpdateConfigurationReq (params);
}

LteEnbCmacSapProvider::RachConfig
EnbMacMemberLteEnbCmacSapProvider::GetRachConfig ()
{
  return m_mac->DoGetRachConfig ();
}

LteEnbCmacSapProvider::AllocateNcRaPreambleReturnValue
EnbMacMemberLteEnbCmacSapProvider::AllocateNcRaPreamble (uint16_t rnti)
{
  return m_mac->DoAllocateNcRaPreamble (rnti);
}


/// EnbMacMemberFfMacSchedSapUser class
class EnbMacMemberFfMacSchedSapUser : public FfMacSchedSapUser
{
public:
  /**
   * Constructor
   *
   * \param mac the MAC
   */
  EnbMacMemberFfMacSchedSapUser (LteEnbMac* mac);


  virtual void SchedDlConfigInd (const struct SchedDlConfigIndParameters& params);
  virtual void SchedUlConfigInd (const struct SchedUlConfigIndParameters& params);
private:
  LteEnbMac* m_mac; ///< the MAC
};


EnbMacMemberFfMacSchedSapUser::EnbMacMemberFfMacSchedSapUser (LteEnbMac* mac)
  : m_mac (mac)
{
}


void
EnbMacMemberFfMacSchedSapUser::SchedDlConfigInd (const struct SchedDlConfigIndParameters& params)
{
  m_mac->DoSchedDlConfigInd (params);
}



void
EnbMacMemberFfMacSchedSapUser::SchedUlConfigInd (const struct SchedUlConfigIndParameters& params)
{
  m_mac->DoSchedUlConfigInd (params);
}


/// EnbMacMemberFfMacCschedSapUser class
class EnbMacMemberFfMacCschedSapUser : public FfMacCschedSapUser
{
public:
  /**
   * Constructor
   *
   * \param mac the MAC
   */
  EnbMacMemberFfMacCschedSapUser (LteEnbMac* mac);

  virtual void CschedCellConfigCnf (const struct CschedCellConfigCnfParameters& params);
  virtual void CschedUeConfigCnf (const struct CschedUeConfigCnfParameters& params);
  virtual void CschedLcConfigCnf (const struct CschedLcConfigCnfParameters& params);
  virtual void CschedLcReleaseCnf (const struct CschedLcReleaseCnfParameters& params);
  virtual void CschedUeReleaseCnf (const struct CschedUeReleaseCnfParameters& params);
  virtual void CschedUeConfigUpdateInd (const struct CschedUeConfigUpdateIndParameters& params);
  virtual void CschedCellConfigUpdateInd (const struct CschedCellConfigUpdateIndParameters& params);

private:
  LteEnbMac* m_mac; ///< the MAC
};


EnbMacMemberFfMacCschedSapUser::EnbMacMemberFfMacCschedSapUser (LteEnbMac* mac)
  : m_mac (mac)
{
}

void
EnbMacMemberFfMacCschedSapUser::CschedCellConfigCnf (const struct CschedCellConfigCnfParameters& params)
{
  m_mac->DoCschedCellConfigCnf (params);
}

void
EnbMacMemberFfMacCschedSapUser::CschedUeConfigCnf (const struct CschedUeConfigCnfParameters& params)
{
  m_mac->DoCschedUeConfigCnf (params);
}

void
EnbMacMemberFfMacCschedSapUser::CschedLcConfigCnf (const struct CschedLcConfigCnfParameters& params)
{
  m_mac->DoCschedLcConfigCnf (params);
}

void
EnbMacMemberFfMacCschedSapUser::CschedLcReleaseCnf (const struct CschedLcReleaseCnfParameters& params)
{
  m_mac->DoCschedLcReleaseCnf (params);
}

void
EnbMacMemberFfMacCschedSapUser::CschedUeReleaseCnf (const struct CschedUeReleaseCnfParameters& params)
{
  m_mac->DoCschedUeReleaseCnf (params);
}

void
EnbMacMemberFfMacCschedSapUser::CschedUeConfigUpdateInd (const struct CschedUeConfigUpdateIndParameters& params)
{
  m_mac->DoCschedUeConfigUpdateInd (params);
}

void
EnbMacMemberFfMacCschedSapUser::CschedCellConfigUpdateInd (const struct CschedCellConfigUpdateIndParameters& params)
{
  m_mac->DoCschedCellConfigUpdateInd (params);
}



/// ---------- PHY-SAP
class EnbMacMemberLteEnbPhySapUser : public LteEnbPhySapUser
{
public:
  /**
   * Constructor
   *
   * \param mac the MAC
   */
  EnbMacMemberLteEnbPhySapUser (LteEnbMac* mac);

  // inherited from LteEnbPhySapUser
  virtual void ReceivePhyPdu (Ptr<Packet> p);
  virtual void SubframeIndication (uint32_t frameNo, uint32_t subframeNo);
  virtual void ReceiveLteControlMessage (Ptr<LteControlMessage> msg);
  virtual void ReceiveRachPreamble (uint32_t prachId);
  virtual void UlCqiReport (FfMacSchedSapProvider::SchedUlCqiInfoReqParameters ulcqi);
  virtual void UlInfoListElementHarqFeeback (UlInfoListElement_s params);
  virtual void DlInfoListElementHarqFeeback (DlInfoListElement_s params);

private:
  LteEnbMac* m_mac; ///< the MAC
};

EnbMacMemberLteEnbPhySapUser::EnbMacMemberLteEnbPhySapUser (LteEnbMac* mac) : m_mac (mac)
{
}


void
EnbMacMemberLteEnbPhySapUser::ReceivePhyPdu (Ptr<Packet> p)
{
  m_mac->DoReceivePhyPdu (p);
}

void
EnbMacMemberLteEnbPhySapUser::SubframeIndication (uint32_t frameNo, uint32_t subframeNo)
{
  m_mac->DoSubframeIndication (frameNo, subframeNo);
}

void
EnbMacMemberLteEnbPhySapUser::ReceiveLteControlMessage (Ptr<LteControlMessage> msg)
{
  m_mac->DoReceiveLteControlMessage (msg);
}

void
EnbMacMemberLteEnbPhySapUser::ReceiveRachPreamble (uint32_t prachId)
{
  m_mac->DoReceiveRachPreamble (prachId);
}

void
EnbMacMemberLteEnbPhySapUser::UlCqiReport (FfMacSchedSapProvider::SchedUlCqiInfoReqParameters ulcqi)
{
  m_mac->DoUlCqiReport (ulcqi);
}

void
EnbMacMemberLteEnbPhySapUser::UlInfoListElementHarqFeeback (UlInfoListElement_s params)
{
  m_mac->DoUlInfoListElementHarqFeeback (params);
}

void
EnbMacMemberLteEnbPhySapUser::DlInfoListElementHarqFeeback (DlInfoListElement_s params)
{
  m_mac->DoDlInfoListElementHarqFeeback (params);
}


// //////////////////////////////////////
// generic LteEnbMac methods
// //////////////////////////////////////


TypeId
LteEnbMac::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::LteEnbMac")
    .SetParent<Object> ()
    .SetGroupName("Lte")
    .AddConstructor<LteEnbMac> ()
    .AddAttribute ("NumberOfRaPreambles",
                   "how many random access preambles are available for the contention based RACH process",
                   UintegerValue (52),
                   MakeUintegerAccessor (&LteEnbMac::m_numberOfRaPreambles),
                   MakeUintegerChecker<uint8_t> (4, 64))
    .AddAttribute ("PreambleTransMax",
                   "Maximum number of random access preamble transmissions",
                   UintegerValue (50),
                   MakeUintegerAccessor (&LteEnbMac::m_preambleTransMax),
                   MakeUintegerChecker<uint8_t> (3, 200))
    .AddAttribute ("RaResponseWindowSize",
                   "length of the window (in TTIs) for the reception of the random access response (RAR); the resulting RAR timeout is this value + 3 ms",
                   UintegerValue (3),
                   MakeUintegerAccessor (&LteEnbMac::m_raResponseWindowSize),
                   MakeUintegerChecker<uint8_t> (2, 10))
    .AddAttribute ("ConnEstFailCount",
                   "how many time T300 timer can expire on the same cell",
                   UintegerValue (1),
                   MakeUintegerAccessor (&LteEnbMac::m_connEstFailCount),
                   MakeUintegerChecker<uint8_t> (1, 4))
    .AddAttribute("FusionAlgorithm",
                  "Fusion algorithm for the collaborative sensing merge function",
                  UintegerValue(MRG_OR),
                  MakeUintegerAccessor(&LteEnbMac::FusionAlgorithm),
                  MakeUintegerChecker<uint8_t> (1,50))//Increment range if you create new fusion algorithms
    .AddAttribute("SpectrumSensing",
                  "Set if spectrum sensing should be used or not",
                  BooleanValue(false),//true
                  MakeBooleanAccessor(&LteEnbMac::spectrumSensing),
                  MakeBooleanChecker())
    .AddTraceSource ("DlScheduling",
                     "Information regarding DL scheduling.",
                     MakeTraceSourceAccessor (&LteEnbMac::m_dlScheduling),
                     "ns3::LteEnbMac::DlSchedulingTracedCallback")
    .AddTraceSource ("UlScheduling",
                     "Information regarding UL scheduling.",
                     MakeTraceSourceAccessor (&LteEnbMac::m_ulScheduling),
                     "ns3::LteEnbMac::UlSchedulingTracedCallback")
    .AddAttribute ("ComponentCarrierId",
                   "ComponentCarrier Id, needed to reply on the appropriate sap.",
                   UintegerValue (0),
                   MakeUintegerAccessor (&LteEnbMac::m_componentCarrierId),
                   MakeUintegerChecker<uint8_t> (0,4))

  ;

  return tid;
}


LteEnbMac::LteEnbMac ():
m_ccmMacSapUser (0)
{
  NS_LOG_FUNCTION (this);
  m_macSapProvider = new EnbMacMemberLteMacSapProvider<LteEnbMac> (this);
  m_cmacSapProvider = new EnbMacMemberLteEnbCmacSapProvider (this);
  m_schedSapUser = new EnbMacMemberFfMacSchedSapUser (this);
  m_cschedSapUser = new EnbMacMemberFfMacCschedSapUser (this);
  m_enbPhySapUser = new EnbMacMemberLteEnbPhySapUser (this);
  m_ccmMacSapProvider = new MemberLteCcmMacSapProvider<LteEnbMac> (this);

  //if(spectrumSensing)
  //{
      unexpectedChannelAccessBitmap.emplace(0, std::map <uint64_t, std::vector<std::vector<bool>>> ());
      unexpectedChannelAccessBitmap.at(0).emplace(0, std::vector<std::vector<bool>>(4));
      for(auto & channelReg : unexpectedChannelAccessBitmap.at(0).at(0))
          channelReg = std::vector<bool>(3);
#ifdef NS3_PYTORCH

    //Prepare neural network for fusion
      std::string fusion_model = PROJECT_SOURCE_PATH"/scratch/fusion_model.pt";

      LteEnbMac::nn_module = torch::jit::load(fusion_model);

      //Initialize slice
      for (int i = 0; i < nn_num_slices; i++)
          nn_encodedDataSlice.push_back(std::vector<float>(nn_width));

      falseNegativeFile.open("falseNegativeInputs.txt");
#endif
      /*
      //Prepare kalman filter for fusion
      int n = 4; // Number of states
      int m = 80; // Number of measurements
      double dt = 1.0 / 100; // Time step

      Eigen::MatrixXd A(n, n); // System dynamics matrix
      Eigen::MatrixXd C(m, n); // Output matrix
      Eigen::MatrixXd Q(n, n); // Process noise covariance
      Eigen::MatrixXd R(m, m); // Measurement noise covariance
      Eigen::MatrixXd P(n, n); // Estimate error covariance

      // Discrete LTI projectile motion, measuring position only
      A << 1, dt, 0, 0, 0, 1, dt, 0, 0, 0, 1, dt, dt, 0, 0, 1;
      for (int col = 0; col < m; col++)
          for (int row = 0; row < n; row++)
              C(col, row) = 0;

      // Reasonable covariance matrices
      for (int col = 0; col < n; col++)
          for (int row = 0; row < n; row++)
          {
              Q(col, row) = (col == row) ? 0.5 : 0;
              P(col, row) = (col == row) ? 0.1 : 10;
          }
      for (int col = 0; col < n; col++)
          for (int row = 0; row < n; row++)
              R(col, row) = 5;

      //std::cout << "A: \n" << A << std::endl;
      //std::cout << "C: \n" << C << std::endl;
      //std::cout << "Q: \n" << Q << std::endl;
      //std::cout << "R: \n" << R << std::endl;
      //std::cout << "P: \n" << P << std::endl;

      // Construct the filter
      kf = KalmanFilter(dt, A, C, Q, R, P);

      // Best guess of initial states
      Eigen::VectorXd x0(n);
      for (int i = 0; i < n; i++)
          x0(i) = 0.0;
      kf.init(0, x0);
      */
  //}

}


LteEnbMac::~LteEnbMac ()
{
  NS_LOG_FUNCTION (this);
  //print sensing list

  if (spectrumSensing)
  {
#ifdef NS3_PYTORCH
      falseNegativeFile.close();
#endif
      std::ofstream sensing_list_file;
      sensing_list_file.open("sensing_list.txt");

      std::vector<int> puSubframePresence(4);
      std::map<uint16_t, uint64_t> sensingUesAndEventsMap;
      for (auto&&[frame, subframeMap]: channelOccupation)
      {
          //sensing_list_file << "frame " << frame << " reported \n{";
          for (auto&&[subframe, ueMap]: subframeMap)
          {
              std::vector<uint32_t> subframePresence = {0, 0, 0, 0};
              //sensing_list_file << "\n\tsubframe " << subframe << " reported \n\t[";
              for (auto&&[ue, cognitiveReg]: ueMap)
              {
                  //Prepare bitmap for sensed stuff
                  int k = 0;
                  int numRbsPerChannel = (bandwidth / cognitiveReg.UnexpectedAccess_FalseAlarm_FalseNegBitmap.size()) + 1;
                  int i = 0;
                  uint64_t sensedBitmap = 0;

                  for (int k = bandwidth; k > 0; k -= numRbsPerChannel, i++)
                  {
                      if (k < numRbsPerChannel)
                          numRbsPerChannel = k;

                      if (!cognitiveReg.UnexpectedAccess_FalseAlarm_FalseNegBitmap[i][0])
                          continue;

                      uint64_t sensedBitmapChannel = 0;
                      for (int j = 0; j < numRbsPerChannel; j++)
                      {
                          sensedBitmapChannel |= ((uint64_t) 0x01) << j;
                      }
                      sensedBitmap |= (sensedBitmapChannel << (bandwidth - k));

                  }
                  //Print sensedBitmap
                  //sensing_list_file << "\n\t\t UE " << ue;
                  //sensing_list_file << " reported bitmap " << std::bitset<132>(sensedBitmap);
                  //sensing_list_file << " in frame " << cognitiveReg.SensedFrameNo;
                  //sensing_list_file << " and subframe "<< cognitiveReg.SensedSubframeNo;

                  if (sensingUesAndEventsMap.find(ue) == sensingUesAndEventsMap.end())
                      sensingUesAndEventsMap.emplace(ue, 0);
                  sensingUesAndEventsMap.at(ue) += 1;

                  for (int subchannel = 0; subchannel < 4; subchannel++)
                      subframePresence[subchannel] |= cognitiveReg.PU_presence_V[subchannel];
              }

              //sensing_list_file << "\n\t]";
              for (int subchannel = 0; subchannel < 4; subchannel++)
                  if (subframePresence[subchannel] != 0)
                      puSubframePresence[subchannel] += 1;
          }
          //sensing_list_file << "\n}";
      }

      for (auto &&[ue, events]: sensingUesAndEventsMap)
      {
          //sensing_list_file << "\nue " << ue << " reported " << events << " sensing events";
      }


      std::vector<int> totalFusions(4);
      std::vector<int> falseAlarmBitmapReports(4);
      std::vector<int> falseNegativeFusions(4);
      for (auto&&[frame, subframeMap]: unexpectedChannelAccessBitmap)
      {
          for (auto&&[subframe, bitmap]: subframeMap)
          {
              //Bitmap[0] contains the bitmap itself
              //Bitmap[1] contains the false positive bitmap
              //Bitmap[2] contains the false negative bitmap

              int k = 0;
              int numRbsPerChannel = (bandwidth / bitmap.size()) + 1;
              int i = 0;
              uint64_t sensedBitmap = 0;
              for (int k = bandwidth; k > 0; k -= numRbsPerChannel, i++)
              {
                  if (k < numRbsPerChannel)
                      numRbsPerChannel = k;

                  if (!bitmap[i][0])
                      continue;

                  uint64_t sensedBitmapChannel = 0;
                  for (int j = 0; j < numRbsPerChannel; j++)
                  {
                      sensedBitmapChannel |= ((uint64_t) 0x01) << j;
                  }
                  sensedBitmap |= (sensedBitmapChannel << (bandwidth - k));
              }
              //sensing_list_file << "\nframe\t" << frame << "\tsubframe\t" << subframe << "\treported\t" << std::bitset<50>(sensedBitmap);

              for (int subchannel = 0; subchannel < 4; subchannel++)
              {
                  totalFusions[subchannel] += 1;
                  falseAlarmBitmapReports[subchannel] += bitmap[subchannel][1];
                  falseNegativeFusions[subchannel] += bitmap[subchannel][2];
              }
          }
      }

      std::vector<double> averageReportedBits{0.0,0.0,0.0,0.0};

      for (auto &ue : countRequiredBits)
      {
          for(int channel=0; channel < 4; channel ++)
              averageReportedBits[channel] += ue.second[channel];
      }

      for(int channel=0; channel < 4; channel ++)
          averageReportedBits[channel] /= countRequiredBits.size();

      for (int subchannel = 0; subchannel < 4; subchannel++)
      {
          int avgReportedBits = std::isnan(averageReportedBits[subchannel]) ? 0 : averageReportedBits[subchannel];
          sensing_list_file << "\n\nFor subchannel " << subchannel << " average of " << avgReportedBits << " bits per UE transmitted :";
          sensing_list_file << "\nFrom " << totalFusions[subchannel] << " fusions,";
          sensing_list_file << " " << falseAlarmBitmapReports[subchannel] << " were false positive and";
          sensing_list_file << " " << falseNegativeFusions[subchannel] << " were false negative.";

          double falsePositives = 100 * (double) falseAlarmBitmapReports[subchannel] / ((double) totalFusions[subchannel] - (double) puSubframePresence[subchannel]);
          falsePositives = std::isnan(falsePositives) ? 0.0 : falsePositives;
          sensing_list_file << "\nTotal false positives were "
                            << falsePositives << "% ("
                            << (double) falseAlarmBitmapReports[subchannel] << ") of " << ((double) totalFusions[subchannel] - (double) puSubframePresence[subchannel])
                            << " subframes.";

          double falseNegatives = 100 * (double) falseNegativeFusions[subchannel] / (double) puSubframePresence[subchannel];
          falseNegatives = std::isnan(falseNegatives) ? 0.0 : falseNegatives;
          sensing_list_file << "\nTotal false negatives were " << falseNegatives << "% ("
                            << (double) falseNegativeFusions[subchannel] << ") of " << (double) puSubframePresence[subchannel] << " subframes.";
      }
      sensing_list_file << std::endl;

  }
}

void
LteEnbMac::DoDispose ()
{
  NS_LOG_FUNCTION (this);
  m_dlCqiReceived.clear ();
  m_ulCqiReceived.clear ();
  m_ulCeReceived.clear ();
  m_dlInfoListReceived.clear ();
  m_ulInfoListReceived.clear ();
  m_miDlHarqProcessesPackets.clear ();
  delete m_macSapProvider;
  delete m_cmacSapProvider;
  delete m_schedSapUser;
  delete m_cschedSapUser;
  delete m_enbPhySapUser;
  delete m_ccmMacSapProvider;
}

void
LteEnbMac::SetComponentCarrierId (uint8_t index)
{
  m_componentCarrierId = index;
}

void
LteEnbMac::SetFfMacSchedSapProvider (FfMacSchedSapProvider* s)
{
  m_schedSapProvider = s;
}

FfMacSchedSapUser*
LteEnbMac::GetFfMacSchedSapUser (void)
{
  return m_schedSapUser;
}

void
LteEnbMac::SetFfMacCschedSapProvider (FfMacCschedSapProvider* s)
{
  m_cschedSapProvider = s;
}

FfMacCschedSapUser*
LteEnbMac::GetFfMacCschedSapUser (void)
{
  return m_cschedSapUser;
}



void
LteEnbMac::SetLteMacSapUser (LteMacSapUser* s)
{
  m_macSapUser = s;
}

LteMacSapProvider*
LteEnbMac::GetLteMacSapProvider (void)
{
  return m_macSapProvider;
}

void
LteEnbMac::SetLteEnbCmacSapUser (LteEnbCmacSapUser* s)
{
  m_cmacSapUser = s;
}

LteEnbCmacSapProvider*
LteEnbMac::GetLteEnbCmacSapProvider (void)
{
  return m_cmacSapProvider;
}

void
LteEnbMac::SetLteEnbPhySapProvider (LteEnbPhySapProvider* s)
{
  m_enbPhySapProvider = s;
}


LteEnbPhySapUser*
LteEnbMac::GetLteEnbPhySapUser ()
{
  return m_enbPhySapUser;
}

void
LteEnbMac::SetLteCcmMacSapUser (LteCcmMacSapUser* s)
{
  m_ccmMacSapUser = s;
}


LteCcmMacSapProvider*
LteEnbMac::GetLteCcmMacSapProvider ()
{
  return m_ccmMacSapProvider;
}

void
LteEnbMac::DoSubframeIndication (uint32_t frameNo, uint32_t subframeNo)
{
  NS_LOG_FUNCTION (this << " EnbMac - frame " << frameNo << " subframe " << subframeNo);

  // Store current frame / subframe number
  m_frameNo = frameNo;
  m_subframeNo = subframeNo;


  // --- DOWNLINK ---
  // Send Dl-CQI info to the scheduler
  if (m_dlCqiReceived.size () > 0)
  {
    FfMacSchedSapProvider::SchedDlCqiInfoReqParameters dlcqiInfoReq;
    dlcqiInfoReq.m_sfnSf = ((0x3FF & frameNo) << 4) | (0xF & subframeNo);
    dlcqiInfoReq.m_cqiList.insert (dlcqiInfoReq.m_cqiList.begin (), m_dlCqiReceived.begin (), m_dlCqiReceived.end ());
    tempCqi.clear();
    tempCqi.insert(tempCqi.begin(), m_dlCqiReceived.begin(), m_dlCqiReceived.end());
    m_dlCqiReceived.erase (m_dlCqiReceived.begin (), m_dlCqiReceived.end ());
    m_schedSapProvider->SchedDlCqiInfoReq (dlcqiInfoReq);
  }

  //Process DL-CQI entries to reset ACK/NACK counters
  BooleanValue harmonicDetection;
  GlobalValue::GetValueByName("HARMONIC_DETECTION", harmonicDetection);

  if (harmonicDetection && !tempCqi.empty())
  {
      //Update current registries with new info
      for (auto & cqiEntry : tempCqi)
      {
          if(cqiEntry.m_cqiType != ns3::CqiListElement_s::A30)
              continue;
          //A30 CQIs at this point
          std::vector<uint8_t> cqisList;
          for (auto &rbEntry: cqiEntry.m_sbMeasResult.m_higherLayerSelected)
          {
              cqisList.push_back(rbEntry.m_sbCqi.at(0));
          }

          //Create new entry for ue_to_cqi_map
          if(ue_to_cqi_map.find(cqiEntry.m_rnti) == ue_to_cqi_map.end())
          {
              ue_to_cqi_map.insert({cqiEntry.m_rnti, cqisList});
              ue_to_position_map.insert({ue_to_position_map.size(), cqiEntry.m_rnti});
          }
          else
          {
              //Backup previous ue_to_cqi_map
              if (prev_ue_to_cqi_map.find(cqiEntry.m_rnti) == prev_ue_to_cqi_map.end())
                  prev_ue_to_cqi_map.emplace(cqiEntry.m_rnti, ue_to_cqi_map.at(cqiEntry.m_rnti));
              else
                prev_ue_to_cqi_map.at(cqiEntry.m_rnti) = ue_to_cqi_map.at(cqiEntry.m_rnti);

              //Assign new values to ue_to_cqi_map
              ue_to_cqi_map.at(cqiEntry.m_rnti) = cqisList;
          }
      }

      std::vector<int> tempHarmonicCqi{0, 0, 0, 0};
      for (int k = 0; k < 4; k++)
      {
          double harmonicCqi = 0.0;
          for (auto &ueCQI : ue_to_cqi_map)
          {
              harmonicCqi += 1/(double) ueCQI.second[centralRbgIndexPerSubchannel[k]];
          }
          tempHarmonicCqi[k] = (int) (ue_to_cqi_map.size()/harmonicCqi);
      }
      harmonicCqiHistory.push_back(tempHarmonicCqi);
  }

  if(!prev_ue_to_cqi_map.empty() && !ue_to_cqi_map.empty())
  {
      //For each UE/rnti, check if CQI increased/maintained and if the current level of NACKs > 10% of NACKs+ACKs
      for (auto &ueCQI : ue_to_cqi_map)
      {
          //Skip UEs with empty stats
          if(ackNackMapPerUe.find(ueCQI.first) == ackNackMapPerUe.end())
              continue;

          auto acks = ackNackMapPerUe.at(ueCQI.first)[0];
          auto nacks = ackNackMapPerUe.at(ueCQI.first)[1];

          if(prev_ue_to_cqi_map.find(ueCQI.first) == prev_ue_to_cqi_map.end())
              continue;

          //For each resource block
          for(int i = 0; i < 4; i++)
          {
              //If transport block error levels is higher than 10% check how the CQI behaves
              if (nacks*10 > acks+nacks)
              {
                  //If it was kept or increased, mark UE CQI reporting as fraudulent
                  if (ueCQI.second[centralRbgIndexPerSubchannel[i]] > prev_ue_to_cqi_map.at(ueCQI.first)[centralRbgIndexPerSubchannel[i]])
                  {
                      if (fraudulentCqiUEs.find(ueCQI.first) == fraudulentCqiUEs.end())
                      {
                          std::vector<bool> temp{false, false, false, false};
                          temp[i] = true;
                          fraudulentCqiUEs.insert({ueCQI.first, temp});
                      }
                      else
                        fraudulentCqiUEs.at(ueCQI.first)[i] = true;
                  }
                  //If the CQI was decreased, the number of acks will eventually grow bigger than nacks
                  //it = ueCQI.second.end(); // skip to next UE
                  //continue;
              }
              else
              {
                  //When transport block error levels fall to lower than 10%, remove CQI from fraudulent list
                  if(fraudulentCqiUEs.find(ueCQI.first) != fraudulentCqiUEs.end())
                  {
                      fraudulentCqiUEs.at(ueCQI.first)[i] = false;

                      bool empty = true;
                      for (auto val : fraudulentCqiUEs.at(ueCQI.first))
                          empty &= !val;
                      if (empty)
                          fraudulentCqiUEs.erase(ueCQI.first);
                  }

                  //When transport block error levels fall to lower than 10% and CQI increases, reset ack/nack count
                  if (ueCQI.second[centralRbgIndexPerSubchannel[i]] > prev_ue_to_cqi_map.at(ueCQI.first)[centralRbgIndexPerSubchannel[i]])
                  {
                      auto &ackNackReg = ackNackMapPerUe.at(ueCQI.first);
                      ackNackReg[0] = 0;
                      ackNackReg[1] = 0;
                  }
              }
              i++;
          }
      }

  }


  //Proceed to default procedure
  if (!m_receivedRachPreambleCount.empty ())
    {
      // process received RACH preambles and notify the scheduler
      FfMacSchedSapProvider::SchedDlRachInfoReqParameters rachInfoReqParams;
      NS_ASSERT (subframeNo > 0 && subframeNo <= 10); // subframe in 1..10
      for (std::map<uint8_t, uint32_t>::const_iterator it = m_receivedRachPreambleCount.begin ();
           it != m_receivedRachPreambleCount.end ();
           ++it)
        {
          NS_LOG_INFO (this << " preambleId " << (uint32_t) it->first << ": " << it->second << " received");
          NS_ASSERT (it->second != 0);
          if (it->second > 1)
            {
              NS_LOG_INFO ("preambleId " << (uint32_t) it->first << ": collision");
              // in case of collision we assume that no preamble is
              // successfully received, hence no RAR is sent
            }
          else
            {
              uint16_t rnti;
              std::map<uint8_t, NcRaPreambleInfo>::iterator jt = m_allocatedNcRaPreambleMap.find (it->first);
              if (jt != m_allocatedNcRaPreambleMap.end ())
                {
                  rnti = jt->second.rnti;
                  NS_LOG_INFO ("preambleId previously allocated for NC based RA, RNTI =" << (uint32_t) rnti << ", sending RAR");

                }
              else
                {
                  rnti = m_cmacSapUser->AllocateTemporaryCellRnti ();
                  NS_LOG_INFO ("preambleId " << (uint32_t) it->first << ": allocated T-C-RNTI " << (uint32_t) rnti << ", sending RAR");
                }

              RachListElement_s rachLe;
              rachLe.m_rnti = rnti;
              rachLe.m_estimatedSize = 144; // to be confirmed
              rachInfoReqParams.m_rachList.push_back (rachLe);
              m_rapIdRntiMap.insert (std::pair <uint16_t, uint32_t> (rnti, it->first));
            }
        }
      m_schedSapProvider->SchedDlRachInfoReq (rachInfoReqParams);
      m_receivedRachPreambleCount.clear ();
    }

  // Get downlink transmission opportunities
  uint32_t dlSchedFrameNo = m_frameNo;
  uint32_t dlSchedSubframeNo = m_subframeNo;
  //   NS_LOG_DEBUG (this << " sfn " << frameNo << " sbfn " << subframeNo);
  if (dlSchedSubframeNo + m_macChTtiDelay > 10)
    {
      dlSchedFrameNo++;
      dlSchedSubframeNo = (dlSchedSubframeNo + m_macChTtiDelay) % 10;
    }
  else
    {
      dlSchedSubframeNo = dlSchedSubframeNo + m_macChTtiDelay;
    }
  FfMacSchedSapProvider::SchedDlTriggerReqParameters dlparams;
  dlparams.m_sfnSf = ((0x3FF & dlSchedFrameNo) << 4) | (0xF & dlSchedSubframeNo);

  // Forward DL HARQ feebacks collected during last TTI
  if (m_dlInfoListReceived.size () > 0)
    {
      dlparams.m_dlInfoList = m_dlInfoListReceived;
      // empty local buffer
      m_dlInfoListReceived.clear ();
    }

  if (spectrumSensing)
  {
      //Cognitive engine has to check channelOccupation and decide whether to flag or not specific RBs
      bool senseRBs = false;
      dlparams.sensedBitmap = mergeSensingReports(FusionAlgorithm, senseRBs, harmonicDetection);
  }

    //Calls for the scheduler
  m_schedSapProvider->SchedDlTriggerReq (dlparams);


  // --- UPLINK ---
  // Send UL-CQI info to the scheduler
  for (uint16_t i = 0; i < m_ulCqiReceived.size (); i++)
    {
      if (subframeNo > 1)
        {
          m_ulCqiReceived.at (i).m_sfnSf = ((0x3FF & frameNo) << 4) | (0xF & (subframeNo - 1));
        }
      else
        {
          m_ulCqiReceived.at (i).m_sfnSf = ((0x3FF & (frameNo - 1)) << 4) | (0xF & 10);
        }
      m_schedSapProvider->SchedUlCqiInfoReq (m_ulCqiReceived.at (i));
    }
    m_ulCqiReceived.clear ();

  // Send BSR reports to the scheduler
  if (m_ulCeReceived.size () > 0)
    {
      FfMacSchedSapProvider::SchedUlMacCtrlInfoReqParameters ulMacReq;
      ulMacReq.m_sfnSf = ((0x3FF & frameNo) << 4) | (0xF & subframeNo);
      ulMacReq.m_macCeList.insert (ulMacReq.m_macCeList.begin (), m_ulCeReceived.begin (), m_ulCeReceived.end ());
      m_ulCeReceived.erase (m_ulCeReceived.begin (), m_ulCeReceived.end ());
      m_schedSapProvider->SchedUlMacCtrlInfoReq (ulMacReq);
    }


  // Get uplink transmission opportunities
  uint32_t ulSchedFrameNo = m_frameNo;
  uint32_t ulSchedSubframeNo = m_subframeNo;
  //   NS_LOG_DEBUG (this << " sfn " << frameNo << " sbfn " << subframeNo);
  if (ulSchedSubframeNo + (m_macChTtiDelay + UL_PUSCH_TTIS_DELAY) > 10)
    {
      ulSchedFrameNo++;
      ulSchedSubframeNo = (ulSchedSubframeNo + (m_macChTtiDelay + UL_PUSCH_TTIS_DELAY)) % 10;
    }
  else
    {
      ulSchedSubframeNo = ulSchedSubframeNo + (m_macChTtiDelay + UL_PUSCH_TTIS_DELAY);
    }
  FfMacSchedSapProvider::SchedUlTriggerReqParameters ulparams;
  ulparams.m_sfnSf = ((0x3FF & ulSchedFrameNo) << 4) | (0xF & ulSchedSubframeNo);

  // Forward DL HARQ feebacks collected during last TTI
  if (m_ulInfoListReceived.size () > 0)
    {
     ulparams.m_ulInfoList = m_ulInfoListReceived;
      // empty local buffer
      m_ulInfoListReceived.clear ();
    }

  m_schedSapProvider->SchedUlTriggerReq (ulparams);

}


void
LteEnbMac::DoReceiveLteControlMessage  (Ptr<LteControlMessage> msg)
{
  NS_LOG_FUNCTION (this << msg);
  if (msg->GetMessageType () == LteControlMessage::DL_CQI)
    {
      Ptr<DlCqiLteControlMessage> dlcqi = DynamicCast<DlCqiLteControlMessage> (msg);
      ReceiveDlCqiLteControlMessage (dlcqi);
    }
  else if (msg->GetMessageType () == LteControlMessage::BSR)
    {
      Ptr<BsrLteControlMessage> bsr = DynamicCast<BsrLteControlMessage> (msg);
      ReceiveBsrMessage (bsr->GetBsr ());
    }
  else if (msg->GetMessageType () == LteControlMessage::DL_HARQ)
    {
      Ptr<DlHarqFeedbackLteControlMessage> dlharq = DynamicCast<DlHarqFeedbackLteControlMessage> (msg);
      DoDlInfoListElementHarqFeeback (dlharq->GetDlHarqFeedback ());
    }
  else if(msg->GetMessageType () == LteControlMessage::COG)
  {
      Ptr<CognitiveLteControlMessage> cog = DynamicCast<CognitiveLteControlMessage> (msg);
      RecvCognitiveMessageC(cog);//receive through control channel
  }
  else
    {
      NS_LOG_LOGIC (this << " LteControlMessage type " << msg->GetMessageType () << " not recognized");
    }
}

void
LteEnbMac::DoReceiveRachPreamble  (uint8_t rapId)
{
  NS_LOG_FUNCTION (this << (uint32_t) rapId);
  // just record that the preamble has been received; it will be processed later
  ++m_receivedRachPreambleCount[rapId]; // will create entry if not exists
}

void
LteEnbMac::DoUlCqiReport (FfMacSchedSapProvider::SchedUlCqiInfoReqParameters ulcqi)
{
  if (ulcqi.m_ulCqi.m_type == UlCqi_s::PUSCH)
    {
      NS_LOG_DEBUG (this << " eNB rxed an PUSCH UL-CQI");
    }
  else if (ulcqi.m_ulCqi.m_type == UlCqi_s::SRS)
    {
      NS_LOG_DEBUG (this << " eNB rxed an SRS UL-CQI");
    }
  m_ulCqiReceived.push_back (ulcqi);
}


void
LteEnbMac::ReceiveDlCqiLteControlMessage  (Ptr<DlCqiLteControlMessage> msg)
{
  NS_LOG_FUNCTION (this << msg);

  CqiListElement_s dlcqi = msg->GetDlCqi ();
  NS_LOG_LOGIC (this << "Enb Received DL-CQI rnti" << dlcqi.m_rnti);
  NS_ASSERT (dlcqi.m_rnti != 0);
  m_dlCqiReceived.push_back (dlcqi);

}


void
LteEnbMac::ReceiveBsrMessage  (MacCeListElement_s bsr)
{
  NS_LOG_FUNCTION (this);
  m_ccmMacSapUser->UlReceiveMacCe (bsr, m_componentCarrierId);
}

void
LteEnbMac::DoReportMacCeToScheduler (MacCeListElement_s bsr)
{
  NS_LOG_FUNCTION (this);
  NS_LOG_DEBUG (this << " bsr Size " << (uint16_t) m_ulCeReceived.size ());
  //send to LteCcmMacSapUser
  m_ulCeReceived.push_back (bsr); // this to called when LteUlCcmSapProvider::ReportMacCeToScheduler is called
  NS_LOG_DEBUG (this << " bsr Size after push_back " << (uint16_t) m_ulCeReceived.size ());
}


void
LteEnbMac::DoReceivePhyPdu (Ptr<Packet> p)
{
  NS_LOG_FUNCTION (this);
  LteRadioBearerTag tag;
  p->RemovePacketTag (tag);

  // store info of the packet received

//   std::map <uint16_t,UlInfoListElement_s>::iterator it;
//   u_int rnti = tag.GetRnti ();
//  u_int lcid = tag.GetLcid ();
//   it = m_ulInfoListElements.find (tag.GetRnti ());
//   if (it == m_ulInfoListElements.end ())
//     {
//       // new RNTI
//       UlInfoListElement_s ulinfonew;
//       ulinfonew.m_rnti = tag.GetRnti ();
//       // always allocate full size of ulReception vector, initializing all elements to 0
//       ulinfonew.m_ulReception.assign (MAX_LC_LIST+1, 0);
//       // set the element for the current LCID
//       ulinfonew.m_ulReception.at (tag.GetLcid ()) = p->GetSize ();
//       ulinfonew.m_receptionStatus = UlInfoListElement_s::Ok;
//       ulinfonew.m_tpc = 0; // Tx power control not implemented at this stage
//       m_ulInfoListElements.insert (std::pair<uint16_t, UlInfoListElement_s > (tag.GetRnti (), ulinfonew));
//
//     }
//   else
//     {
//       // existing RNTI: we just set the value for the current
//       // LCID. Note that the corresponding element had already been
//       // allocated previously.
//       NS_ASSERT_MSG ((*it).second.m_ulReception.at (tag.GetLcid ()) == 0, "would overwrite previously written ulReception element");
//       (*it).second.m_ulReception.at (tag.GetLcid ()) = p->GetSize ();
//       (*it).second.m_receptionStatus = UlInfoListElement_s::Ok;
//     }



  // forward the packet to the correspondent RLC
  uint16_t rnti = tag.GetRnti ();
  uint8_t lcid = tag.GetLcid ();
  std::map <uint16_t, std::map<uint8_t, LteMacSapUser*> >::iterator rntiIt = m_rlcAttached.find (rnti);
  NS_ASSERT_MSG (rntiIt != m_rlcAttached.end (), "could not find RNTI" << rnti);
  std::map<uint8_t, LteMacSapUser*>::iterator lcidIt = rntiIt->second.find (lcid);
  //NS_ASSERT_MSG (lcidIt != rntiIt->second.end (), "could not find LCID" << lcid);

  LteMacSapUser::ReceivePduParameters rxPduParams;
  rxPduParams.p = p;
  rxPduParams.rnti = rnti;
  rxPduParams.lcid = lcid;

  //Receive PDU only if LCID is found
  if (lcidIt != rntiIt->second.end ())
    {
      (*lcidIt).second->ReceivePdu (rxPduParams);
    }
}



// ////////////////////////////////////////////
// CMAC SAP
// ////////////////////////////////////////////

void
LteEnbMac::DoConfigureMac (uint8_t ulBandwidth, uint8_t dlBandwidth)
{
  NS_LOG_FUNCTION (this << " ulBandwidth=" << (uint16_t) ulBandwidth << " dlBandwidth=" << (uint16_t) dlBandwidth);
  FfMacCschedSapProvider::CschedCellConfigReqParameters params;
  // Configure the subset of parameters used by FfMacScheduler
  params.m_ulBandwidth = ulBandwidth;
  params.m_dlBandwidth = dlBandwidth;
  m_macChTtiDelay = m_enbPhySapProvider->GetMacChTtiDelay ();
  // ...more parameters can be configured
  m_cschedSapProvider->CschedCellConfigReq (params);
  bandwidth = (int)dlBandwidth; //bandwidth is used by the opportunistic access component
}


void
LteEnbMac::DoAddUe (uint16_t rnti)
{

  NS_LOG_FUNCTION (this << " rnti=" << rnti);
  UeRntiMap.emplace(rnti, true);

  std::map<uint8_t, LteMacSapUser*> empty;
  std::pair <std::map <uint16_t, std::map<uint8_t, LteMacSapUser*> >::iterator, bool>
    ret = m_rlcAttached.insert (std::pair <uint16_t,  std::map<uint8_t, LteMacSapUser*> >
                                (rnti, empty));
  NS_ASSERT_MSG (ret.second, "element already present, RNTI already existed");

  FfMacCschedSapProvider::CschedUeConfigReqParameters params;
  params.m_rnti = rnti;
  params.m_transmissionMode = 0; // set to default value (SISO) for avoiding random initialization (valgrind error)

  m_cschedSapProvider->CschedUeConfigReq (params);

  // Create DL transmission HARQ buffers
  std::vector < Ptr<PacketBurst> > dlHarqLayer0pkt;
  dlHarqLayer0pkt.resize (8);
  for (uint8_t i = 0; i < 8; i++)
    {
      Ptr<PacketBurst> pb = CreateObject <PacketBurst> ();
      dlHarqLayer0pkt.at (i) = pb;
    }
  std::vector < Ptr<PacketBurst> > dlHarqLayer1pkt;
  dlHarqLayer1pkt.resize (8);
  for (uint8_t i = 0; i < 8; i++)
    {
      Ptr<PacketBurst> pb = CreateObject <PacketBurst> ();
      dlHarqLayer1pkt.at (i) = pb;
    }
  DlHarqProcessesBuffer_t buf;
  buf.push_back (dlHarqLayer0pkt);
  buf.push_back (dlHarqLayer1pkt);
  m_miDlHarqProcessesPackets.insert (std::pair <uint16_t, DlHarqProcessesBuffer_t> (rnti, buf));
}

void
LteEnbMac::DoRemoveUe (uint16_t rnti)
{
  NS_LOG_FUNCTION (this << " rnti=" << rnti);
  UeRntiMap.erase(rnti);

  FfMacCschedSapProvider::CschedUeReleaseReqParameters params;
  params.m_rnti = rnti;
  m_cschedSapProvider->CschedUeReleaseReq (params);
  m_rlcAttached.erase (rnti);
  m_miDlHarqProcessesPackets.erase (rnti);

  NS_LOG_DEBUG ("start checking for unprocessed preamble for rnti: " << rnti);
  //remove unprocessed preamble received for RACH during handover
  std::map<uint8_t, NcRaPreambleInfo>::iterator jt = m_allocatedNcRaPreambleMap.begin ();
  while (jt != m_allocatedNcRaPreambleMap.end ())
    {
      if (jt->second.rnti == rnti)
        {
          std::map<uint8_t, uint32_t>::const_iterator it = m_receivedRachPreambleCount.find (jt->first);
          if (it != m_receivedRachPreambleCount.end ())
            {
              m_receivedRachPreambleCount.erase (it->first);
            }
          jt = m_allocatedNcRaPreambleMap.erase (jt);
        }
      else
        {
          ++jt;
        }
    }

  std::vector<MacCeListElement_s>::iterator itCeRxd = m_ulCeReceived.begin ();
  while (itCeRxd != m_ulCeReceived.end ())
    {
      if (itCeRxd->m_rnti == rnti)
        {
          itCeRxd = m_ulCeReceived.erase (itCeRxd);
        }
      else
        {
          itCeRxd++;
        }
    }
}

void
LteEnbMac::DoAddLc (LteEnbCmacSapProvider::LcInfo lcinfo, LteMacSapUser* msu)
{
  NS_LOG_FUNCTION (this << lcinfo.rnti << (uint16_t) lcinfo.lcId);

  std::map <LteFlowId_t, LteMacSapUser* >::iterator it;

  LteFlowId_t flow (lcinfo.rnti, lcinfo.lcId);

  std::map <uint16_t, std::map<uint8_t, LteMacSapUser*> >::iterator rntiIt = m_rlcAttached.find (lcinfo.rnti);
  NS_ASSERT_MSG (rntiIt != m_rlcAttached.end (), "RNTI not found");
  std::map<uint8_t, LteMacSapUser*>::iterator lcidIt = rntiIt->second.find (lcinfo.lcId);
  if (lcidIt == rntiIt->second.end ())
    {
      rntiIt->second.insert (std::pair<uint8_t, LteMacSapUser*> (lcinfo.lcId, msu));
    }
  else
    {
      NS_LOG_ERROR ("LC already exists");
    }

  // CCCH (LCID 0) is pre-configured
  // see FF LTE MAC Scheduler
  // Interface Specification v1.11,
  // 4.3.4 logicalChannelConfigListElement
  if (lcinfo.lcId != 0)
    {
      struct FfMacCschedSapProvider::CschedLcConfigReqParameters params;
      params.m_rnti = lcinfo.rnti;
      params.m_reconfigureFlag = false;

      struct LogicalChannelConfigListElement_s lccle;
      lccle.m_logicalChannelIdentity = lcinfo.lcId;
      lccle.m_logicalChannelGroup = lcinfo.lcGroup;
      lccle.m_direction = LogicalChannelConfigListElement_s::DIR_BOTH;
      lccle.m_qosBearerType = lcinfo.isGbr ? LogicalChannelConfigListElement_s::QBT_GBR : LogicalChannelConfigListElement_s::QBT_NON_GBR;
      lccle.m_qci = lcinfo.qci;
      lccle.m_eRabMaximulBitrateUl = lcinfo.mbrUl;
      lccle.m_eRabMaximulBitrateDl = lcinfo.mbrDl;
      lccle.m_eRabGuaranteedBitrateUl = lcinfo.gbrUl;
      lccle.m_eRabGuaranteedBitrateDl = lcinfo.gbrDl;
      params.m_logicalChannelConfigList.push_back (lccle);

      m_cschedSapProvider->CschedLcConfigReq (params);
    }
}

void
LteEnbMac::DoReconfigureLc (LteEnbCmacSapProvider::LcInfo lcinfo)
{
  NS_FATAL_ERROR ("not implemented");
}

void
LteEnbMac::DoReleaseLc (uint16_t rnti, uint8_t lcid)
{
  NS_LOG_FUNCTION (this);

  //Find user based on rnti and then erase lcid stored against the same
  std::map <uint16_t, std::map<uint8_t, LteMacSapUser*> >::iterator rntiIt = m_rlcAttached.find (rnti);
  rntiIt->second.erase (lcid);

  struct FfMacCschedSapProvider::CschedLcReleaseReqParameters params;
  params.m_rnti = rnti;
  params.m_logicalChannelIdentity.push_back (lcid);
  m_cschedSapProvider->CschedLcReleaseReq (params);
}

void
LteEnbMac::DoUeUpdateConfigurationReq (LteEnbCmacSapProvider::UeConfig params)
{
  NS_LOG_FUNCTION (this);

  // propagates to scheduler
  FfMacCschedSapProvider::CschedUeConfigReqParameters req;
  req.m_rnti = params.m_rnti;
  req.m_transmissionMode = params.m_transmissionMode;
  req.m_reconfigureFlag = true;
  m_cschedSapProvider->CschedUeConfigReq (req);
}

LteEnbCmacSapProvider::RachConfig
LteEnbMac::DoGetRachConfig ()
{
  struct LteEnbCmacSapProvider::RachConfig rc;
  rc.numberOfRaPreambles = m_numberOfRaPreambles;
  rc.preambleTransMax = m_preambleTransMax;
  rc.raResponseWindowSize = m_raResponseWindowSize;
  rc.connEstFailCount = m_connEstFailCount;
  return rc;
}

LteEnbCmacSapProvider::AllocateNcRaPreambleReturnValue
LteEnbMac::DoAllocateNcRaPreamble (uint16_t rnti)
{
  bool found = false;
  uint8_t preambleId;
  for (preambleId = m_numberOfRaPreambles; preambleId < 64; ++preambleId)
    {
      std::map<uint8_t, NcRaPreambleInfo>::iterator it = m_allocatedNcRaPreambleMap.find (preambleId);
      /**
       * Allocate preamble only if its free. The non-contention preamble
       * assigned to UE during handover or PDCCH order is valid only until the
       * time duration of the “expiryTime” of the preamble is reached. This
       * timer value is only maintained at the eNodeB and the UE has no way of
       * knowing if this timer has expired. If the UE tries to send the preamble
       * again after the expiryTime and the preamble is re-assigned to another
       * UE, it results in errors. This has been solved by re-assigning the
       * preamble to another UE only if it is not being used (An UE can be using
       * the preamble even after the expiryTime duration).
       */
      if ((it != m_allocatedNcRaPreambleMap.end ()) && (it->second.expiryTime < Simulator::Now ()))
        {
          if (!m_cmacSapUser->IsRandomAccessCompleted (rnti))
            {
              //random access of the UE is not completed,
              //check other preambles
              continue;
            }
        }
      if ((it ==  m_allocatedNcRaPreambleMap.end ())
          || (it->second.expiryTime < Simulator::Now ()))
        {
          found = true;
          NcRaPreambleInfo preambleInfo;
          uint32_t expiryIntervalMs = (uint32_t) m_preambleTransMax * ((uint32_t) m_raResponseWindowSize*SUBFRAME_DURATION + 5);

          preambleInfo.expiryTime = Simulator::Now () + MilliSeconds (expiryIntervalMs);
          preambleInfo.rnti = rnti;
          NS_LOG_INFO ("allocated preamble for NC based RA: preamble " << preambleId << ", RNTI " << preambleInfo.rnti << ", exiryTime " << preambleInfo.expiryTime);
          m_allocatedNcRaPreambleMap[preambleId] = preambleInfo; // create if not exist, update otherwise
          break;
        }
    }
  LteEnbCmacSapProvider::AllocateNcRaPreambleReturnValue ret;
  if (found)
    {
      ret.valid = true;
      ret.raPreambleId = preambleId;
      ret.raPrachMaskIndex = 0;
    }
  else
    {
      ret.valid = false;
      ret.raPreambleId = 0;
      ret.raPrachMaskIndex = 0;
    }
  return ret;
}



// ////////////////////////////////////////////
// MAC SAP
// ////////////////////////////////////////////


void
LteEnbMac::DoTransmitPdu (LteMacSapProvider::TransmitPduParameters params)
{
  NS_LOG_FUNCTION (this);
  LteRadioBearerTag tag (params.rnti, params.lcid, params.layer);
  params.pdu->AddPacketTag (tag);
  params.componentCarrierId = m_componentCarrierId;
  // Store pkt in HARQ buffer
  std::map <uint16_t, DlHarqProcessesBuffer_t>::iterator it =  m_miDlHarqProcessesPackets.find (params.rnti);
  NS_ASSERT (it != m_miDlHarqProcessesPackets.end ());
  NS_LOG_DEBUG (this << " LAYER " << (uint16_t)tag.GetLayer () << " HARQ ID " << (uint16_t)params.harqProcessId);

  //(*it).second.at (params.layer).at (params.harqProcessId) = params.pdu;//->Copy ();
  (*it).second.at (params.layer).at (params.harqProcessId)->AddPacket (params.pdu);
  m_enbPhySapProvider->SendMacPdu (params.pdu);
}

void
LteEnbMac::DoReportBufferStatus (LteMacSapProvider::ReportBufferStatusParameters params)
{
  NS_LOG_FUNCTION (this);
  FfMacSchedSapProvider::SchedDlRlcBufferReqParameters req;
  req.m_rnti = params.rnti;
  req.m_logicalChannelIdentity = params.lcid;
  req.m_rlcTransmissionQueueSize = params.txQueueSize;
  req.m_rlcTransmissionQueueHolDelay = params.txQueueHolDelay;
  req.m_rlcRetransmissionQueueSize = params.retxQueueSize;
  req.m_rlcRetransmissionHolDelay = params.retxQueueHolDelay;
  req.m_rlcStatusPduSize = params.statusPduSize;
  m_schedSapProvider->SchedDlRlcBufferReq (req);
}



// ////////////////////////////////////////////
// SCHED SAP
// ////////////////////////////////////////////



void
LteEnbMac::DoSchedDlConfigInd (FfMacSchedSapUser::SchedDlConfigIndParameters ind)
{
  NS_LOG_FUNCTION (this);
  // Create DL PHY PDU
  Ptr<PacketBurst> pb = CreateObject<PacketBurst> ();
  std::map <LteFlowId_t, LteMacSapUser* >::iterator it;
  LteMacSapUser::TxOpportunityParameters txOpParams;

  for (unsigned int i = 0; i < ind.m_buildDataList.size (); i++)
    {
      for (uint16_t layer = 0; layer < ind.m_buildDataList.at (i).m_dci.m_ndi.size (); layer++)
        {
          if (ind.m_buildDataList.at (i).m_dci.m_ndi.at (layer) == 1)
            {
              // new data -> force emptying correspondent harq pkt buffer
              std::map <uint16_t, DlHarqProcessesBuffer_t>::iterator it = m_miDlHarqProcessesPackets.find (ind.m_buildDataList.at (i).m_rnti);
              NS_ASSERT (it != m_miDlHarqProcessesPackets.end ());
              for (uint16_t lcId = 0; lcId < (*it).second.size (); lcId++)
                {
                  Ptr<PacketBurst> pb = CreateObject <PacketBurst> ();
                  (*it).second.at (lcId).at (ind.m_buildDataList.at (i).m_dci.m_harqProcess) = pb;
                }
            }
        }
      for (unsigned int j = 0; j < ind.m_buildDataList.at (i).m_rlcPduList.size (); j++)
        {
          for (uint16_t k = 0; k < ind.m_buildDataList.at (i).m_rlcPduList.at (j).size (); k++)
            {
              if (ind.m_buildDataList.at (i).m_dci.m_ndi.at (k) == 1)
                {
                  // New Data -> retrieve it from RLC
                  uint16_t rnti = ind.m_buildDataList.at (i).m_rnti;
                  uint8_t lcid = ind.m_buildDataList.at (i).m_rlcPduList.at (j).at (k).m_logicalChannelIdentity;
                  std::map <uint16_t, std::map<uint8_t, LteMacSapUser*> >::iterator rntiIt = m_rlcAttached.find (rnti);
                  NS_ASSERT_MSG (rntiIt != m_rlcAttached.end (), "could not find RNTI" << rnti);
                  std::map<uint8_t, LteMacSapUser*>::iterator lcidIt = rntiIt->second.find (lcid);
                  NS_ASSERT_MSG (lcidIt != rntiIt->second.end (), "could not find LCID" << (uint32_t)lcid<<" carrier id:"<<(uint16_t)m_componentCarrierId);
                  NS_LOG_DEBUG (this << " rnti= " << rnti << " lcid= " << (uint32_t) lcid << " layer= " << k);
                  txOpParams.bytes = ind.m_buildDataList.at (i).m_rlcPduList.at (j).at (k).m_size;
                  txOpParams.layer = k;
                  txOpParams.harqId = ind.m_buildDataList.at (i).m_dci.m_harqProcess;
                  txOpParams.componentCarrierId = m_componentCarrierId;
                  txOpParams.rnti = rnti;
                  txOpParams.lcid = lcid;
                  (*lcidIt).second->NotifyTxOpportunity (txOpParams);
                }
              else
                {
                  if (ind.m_buildDataList.at (i).m_dci.m_tbsSize.at (k) > 0)
                    {
                      // HARQ retransmission -> retrieve TB from HARQ buffer
                      std::map <uint16_t, DlHarqProcessesBuffer_t>::iterator it = m_miDlHarqProcessesPackets.find (ind.m_buildDataList.at (i).m_rnti);
                      NS_ASSERT (it != m_miDlHarqProcessesPackets.end ());
                      Ptr<PacketBurst> pb = (*it).second.at (k).at ( ind.m_buildDataList.at (i).m_dci.m_harqProcess);
                      for (std::list<Ptr<Packet> >::const_iterator j = pb->Begin (); j != pb->End (); ++j)
                        {
                          Ptr<Packet> pkt = (*j)->Copy ();
                          m_enbPhySapProvider->SendMacPdu (pkt);
                        }
                    }
                }
            }
        }
      // send the relative DCI
      Ptr<DlDciLteControlMessage> msg = Create<DlDciLteControlMessage> ();
      msg->SetDci (ind.m_buildDataList.at (i).m_dci);
      m_enbPhySapProvider->SendLteControlMessage (msg);
    }

  // Fire the trace with the DL information
  for (  uint32_t i  = 0; i < ind.m_buildDataList.size (); i++ )
    {
      // Only one TB used
      if (ind.m_buildDataList.at (i).m_dci.m_tbsSize.size () == 1)
        {
          DlSchedulingCallbackInfo dlSchedulingCallbackInfo;
          dlSchedulingCallbackInfo.frameNo = m_frameNo;
          dlSchedulingCallbackInfo.subframeNo = m_subframeNo;
          dlSchedulingCallbackInfo.rnti = ind.m_buildDataList.at (i).m_dci.m_rnti;
          dlSchedulingCallbackInfo.mcsTb1=ind.m_buildDataList.at (i).m_dci.m_mcs.at (0);
          dlSchedulingCallbackInfo.sizeTb1 = ind.m_buildDataList.at (i).m_dci.m_tbsSize.at (0);
          dlSchedulingCallbackInfo.mcsTb2 = 0;
          dlSchedulingCallbackInfo.sizeTb2 = 0;
          dlSchedulingCallbackInfo.componentCarrierId = m_componentCarrierId;
          m_dlScheduling(dlSchedulingCallbackInfo);
        }
      // Two TBs used
      else if (ind.m_buildDataList.at (i).m_dci.m_tbsSize.size () == 2)
        {
          DlSchedulingCallbackInfo dlSchedulingCallbackInfo;
          dlSchedulingCallbackInfo.frameNo = m_frameNo;
          dlSchedulingCallbackInfo.subframeNo = m_subframeNo;
          dlSchedulingCallbackInfo.rnti = ind.m_buildDataList.at (i).m_dci.m_rnti;
          dlSchedulingCallbackInfo.mcsTb1=ind.m_buildDataList.at (i).m_dci.m_mcs.at (0);
          dlSchedulingCallbackInfo.sizeTb1 = ind.m_buildDataList.at (i).m_dci.m_tbsSize.at (0);
          dlSchedulingCallbackInfo.mcsTb2 = ind.m_buildDataList.at (i).m_dci.m_mcs.at (1);
          dlSchedulingCallbackInfo.sizeTb2 = ind.m_buildDataList.at (i).m_dci.m_tbsSize.at (1);
          dlSchedulingCallbackInfo.componentCarrierId = m_componentCarrierId;
          m_dlScheduling(dlSchedulingCallbackInfo);
        }
      else
        {
          NS_FATAL_ERROR ("Found element with more than two transport blocks");
        }
    }

  // Random Access procedure: send RARs
  Ptr<RarLteControlMessage> rarMsg = Create<RarLteControlMessage> ();
  // see TS 36.321 5.1.4;  preambles were sent two frames ago
  // (plus 3GPP counts subframes from 0, not 1)
  uint16_t raRnti;
  if (m_subframeNo < 3)
    {
      raRnti = m_subframeNo + 7; // equivalent to +10-3
    }
  else
    {
      raRnti = m_subframeNo - 3;
    }
  rarMsg->SetRaRnti (raRnti);
  for (unsigned int i = 0; i < ind.m_buildRarList.size (); i++)
    {
      std::map <uint16_t, uint32_t>::iterator itRapId = m_rapIdRntiMap.find (ind.m_buildRarList.at (i).m_rnti);
      if (itRapId == m_rapIdRntiMap.end ())
        {
          NS_FATAL_ERROR ("Unable to find rapId of RNTI " << ind.m_buildRarList.at (i).m_rnti);
        }
      RarLteControlMessage::Rar rar;
      rar.rapId = itRapId->second;
      rar.rarPayload = ind.m_buildRarList.at (i);
      rarMsg->AddRar (rar);
      NS_LOG_INFO (this << " Send RAR message to RNTI " << ind.m_buildRarList.at (i).m_rnti << " rapId " << itRapId->second);
    }
  if (ind.m_buildRarList.size () > 0)
    {
      m_enbPhySapProvider->SendLteControlMessage (rarMsg);
    }
  m_rapIdRntiMap.clear ();
}


void
LteEnbMac::DoSchedUlConfigInd (FfMacSchedSapUser::SchedUlConfigIndParameters ind)
{
  NS_LOG_FUNCTION (this);

  for (unsigned int i = 0; i < ind.m_dciList.size (); i++)
    {
      // send the correspondent ul dci
      Ptr<UlDciLteControlMessage> msg = Create<UlDciLteControlMessage> ();
      msg->SetDci (ind.m_dciList.at (i));
      m_enbPhySapProvider->SendLteControlMessage (msg);
    }

  // Fire the trace with the UL information
  for (  uint32_t i  = 0; i < ind.m_dciList.size (); i++ )
    {
      m_ulScheduling (m_frameNo, m_subframeNo, ind.m_dciList.at (i).m_rnti,
                      ind.m_dciList.at (i).m_mcs, ind.m_dciList.at (i).m_tbSize, m_componentCarrierId);
    }



}




// ////////////////////////////////////////////
// CSCHED SAP
// ////////////////////////////////////////////


void
LteEnbMac::DoCschedCellConfigCnf (FfMacCschedSapUser::CschedCellConfigCnfParameters params)
{
  NS_LOG_FUNCTION (this);
}

void
LteEnbMac::DoCschedUeConfigCnf (FfMacCschedSapUser::CschedUeConfigCnfParameters params)
{
  NS_LOG_FUNCTION (this);
}

void
LteEnbMac::DoCschedLcConfigCnf (FfMacCschedSapUser::CschedLcConfigCnfParameters params)
{
  NS_LOG_FUNCTION (this);
  // Call the CSCHED primitive
  // m_cschedSap->LcConfigCompleted();
}

void
LteEnbMac::DoCschedLcReleaseCnf (FfMacCschedSapUser::CschedLcReleaseCnfParameters params)
{
  NS_LOG_FUNCTION (this);
}

void
LteEnbMac::DoCschedUeReleaseCnf (FfMacCschedSapUser::CschedUeReleaseCnfParameters params)
{
  NS_LOG_FUNCTION (this);
}

void
LteEnbMac::DoCschedUeConfigUpdateInd (FfMacCschedSapUser::CschedUeConfigUpdateIndParameters params)
{
  NS_LOG_FUNCTION (this);
  // propagates to RRC
  LteEnbCmacSapUser::UeConfig ueConfigUpdate;
  ueConfigUpdate.m_rnti = params.m_rnti;
  ueConfigUpdate.m_transmissionMode = params.m_transmissionMode;
  m_cmacSapUser->RrcConfigurationUpdateInd (ueConfigUpdate);
}

void
LteEnbMac::DoCschedCellConfigUpdateInd (FfMacCschedSapUser::CschedCellConfigUpdateIndParameters params)
{
  NS_LOG_FUNCTION (this);
}

void
LteEnbMac::DoUlInfoListElementHarqFeeback (UlInfoListElement_s params)
{
  NS_LOG_FUNCTION (this);
  m_ulInfoListReceived.push_back (params);
}

void
LteEnbMac::DoDlInfoListElementHarqFeeback (DlInfoListElement_s params)
{
  NS_LOG_FUNCTION (this);

  //Count acks and nacks per ue/rnti
  auto ackNackReg = ackNackMapPerUe.find(params.m_rnti);
  if (ackNackReg == ackNackMapPerUe.end())
  {
      std::vector<uint64_t> tmp({0,0});
      ackNackMapPerUe.emplace(params.m_rnti, tmp);
  }

  // Update HARQ buffer
  std::map <uint16_t, DlHarqProcessesBuffer_t>::iterator it =  m_miDlHarqProcessesPackets.find (params.m_rnti);
  NS_ASSERT (it != m_miDlHarqProcessesPackets.end ());
  for (uint8_t layer = 0; layer < params.m_harqStatus.size (); layer++)
    {
      if (params.m_harqStatus.at (layer) == DlInfoListElement_s::ACK)
        {
          // discard buffer
          Ptr<PacketBurst> emptyBuf = CreateObject <PacketBurst> ();
          (*it).second.at (layer).at (params.m_harqProcessId) = emptyBuf;
          NS_LOG_DEBUG (this << " HARQ-ACK UE " << params.m_rnti << " harqId " << (uint16_t)params.m_harqProcessId << " layer " << (uint16_t)layer);
          ackNackMapPerUe.at(params.m_rnti)[0]++;
        }
      else if (params.m_harqStatus.at (layer) == DlInfoListElement_s::NACK)
        {
          NS_LOG_DEBUG (this << " HARQ-NACK UE " << params.m_rnti << " harqId " << (uint16_t)params.m_harqProcessId << " layer " << (uint16_t)layer);
          ackNackMapPerUe.at(params.m_rnti)[1]++;
        }
      else
        {
          NS_FATAL_ERROR (" HARQ functionality not implemented");
        }
    }
  m_dlInfoListReceived.push_back (params);
}


// Receive "cognitive messages" from UEs through the data channel
/*todo: port code to current notification structure
void LteEnbMac::RecvCognitiveMessage(Ptr<Packet> p)
{
    //Receive cognitive radio params
    uint8_t *buffer = new uint8_t[p->GetSize ()];
    int msg_size = p->CopyData(buffer, p->GetSize ());
    std::string ss = std::string(buffer, buffer+p->GetSize());
    //std::cout << ss << std::endl;

    //Alocate variables to manipulate packet
    std::string temp;
    char * ptr;
    size_t pos;
    cognitive_reg reg;

    //We can now parse and use params to do something
    pos = ss.find('\n');
    temp = ss.substr(0,pos);
    reg.OriginAddress = std::strtoimax(temp.c_str(), &ptr, 10);
    ss.erase(0, pos + 1);

    //Parsing to get info from packet
    pos = ss.find('\n');
    reg.SimCurrTime = Time(ss.substr(0,pos));
    ss.erase(0, pos + 1);

    reg.Delay = Simulator::Now()-reg.SimCurrTime;

    pos = ss.find('\n');
    temp = ss.substr(0,pos);
    reg.SensedFrameNo = std::strtoimax(temp.c_str(), &ptr, 10);
    ss.erase(0, pos + 1);

    pos = ss.find('\n');
    temp = ss.substr(0,pos);
    reg.SensedSubframeNo = std::strtoimax(temp.c_str(), &ptr, 10);
    ss.erase(0, pos + 1);

    pos = ss.find('\n');
    temp = ss.substr(0,pos);
    reg.UnexpectedAccessBitmap = std::strtoimax(temp.c_str(), &ptr, 16);
    ss.erase(0, pos + 1);

    //pos = ss.find('\n');
    //reg.TransmissionTime = Time(ss.substr(0,pos));
    //ss.erase(0, pos + 1);

    reg.ReceivedFrameNo = m_frameNo;
    reg.ReceivedSubframeNo = m_subframeNo;

    //Save cognitive reg with times collected and source

    //First create map for frames
    if(channelOccupation.find(reg.ReceivedFrameNo) == channelOccupation.end())
    {
        channelOccupation.emplace(reg.ReceivedFrameNo, std::map <uint64_t, std::map<uint16_t, CognitiveReg> > ());
    }

    //After that, create map for subframes
    if(channelOccupation.at(reg.ReceivedFrameNo).find(reg.ReceivedSubframeNo) == channelOccupation.at(reg.ReceivedFrameNo).end())
    {
        channelOccupation.at(reg.ReceivedFrameNo).emplace(reg.ReceivedSubframeNo, std::map<uint16_t, CognitiveReg> ());
    }

    //Then register UE reports
    channelOccupation.at(reg.ReceivedFrameNo).at(reg.ReceivedSubframeNo).emplace(reg.OriginAddress,reg);

    return;
}
*/

// Receive "cognitive messages" from UEs through the ctrl channel
void LteEnbMac::RecvCognitiveMessageC(Ptr<CognitiveLteControlMessage> p)
{

    CognitiveReg reg;
    reg = p->GetMessage();

    reg.Delay = Simulator::Now()-reg.SimCurrTime;
    reg.ReceivedFrameNo = m_frameNo;
    reg.ReceivedSubframeNo = m_subframeNo;

    //Save cognitive reg with times collected and source

    //First create map for frames
    if(channelOccupation.find(reg.ReceivedFrameNo) == channelOccupation.end())
    {
        channelOccupation.emplace(reg.ReceivedFrameNo, std::map <uint64_t, std::map<uint16_t, CognitiveReg> > ());
    }

    //After that, create map for subframes
    if(channelOccupation.at(reg.ReceivedFrameNo).find(reg.ReceivedSubframeNo) == channelOccupation.at(reg.ReceivedFrameNo).end())
    {
        channelOccupation.at(reg.ReceivedFrameNo).emplace(reg.ReceivedSubframeNo, std::map<uint16_t, CognitiveReg> ());
    }

    //Then register UE reports
    channelOccupation.at(reg.ReceivedFrameNo).at(reg.ReceivedSubframeNo).emplace(reg.OriginAddress,reg);

    //std::cout << std::bitset<64>(reg.UnexpectedAccessBitmap) << std::endl;

    return;
}

bool LteEnbMac::harmonicMeanFraudDetector(uint16_t ueRnti, std::vector<unsigned char> prevCqi, std::vector<unsigned char> latestCqi, std::vector<bool> channelReg, int i)
{
    //2nd check against Byzantine attacks
    //Skip reports from UEs that report sane CQIs but didn't changed when a PU was detected, which indicates the sensing is incorrect
    bool prevSensingExists = prevSensing.find(ueRnti) != prevSensing.end();

    //Create entry if one doesn't exist
    if(markovTrustworthiness.find(ueRnti) == markovTrustworthiness.end())
    {
        std::vector<double> temp{1.0, 1.0, 1.0, 1.0};
        markovTrustworthiness.insert({ueRnti, temp});
    }

    //If result doesnt make sense, decrease trustworthiness
    if (  (    prevSensingExists && !prevSensing.at(ueRnti)[i] && channelReg[0] && prevCqi[centralRbgIndexPerSubchannel[i]] > latestCqi[centralRbgIndexPerSubchannel[i]] )
          || ( prevSensingExists &&  prevSensing.at(ueRnti)[i] && channelReg[0] && prevCqi[centralRbgIndexPerSubchannel[i]] < harmonicCqiHistory.at(harmonicCqiHistory.size()-2)[i] && latestCqi[centralRbgIndexPerSubchannel[i]] > harmonicCqiHistory.at(harmonicCqiHistory.size()-1)[i]+1 )
            )
    {
        markovTrustworthiness.at(ueRnti)[i] *= 0.5;
    }
    else if(     !channelReg[0] && prevCqi[centralRbgIndexPerSubchannel[i]] >= latestCqi[centralRbgIndexPerSubchannel[i]]
                 || ( prevSensingExists && !prevSensing.at(ueRnti)[i] &&  channelReg[0] && prevCqi[centralRbgIndexPerSubchannel[i]] <= latestCqi[centralRbgIndexPerSubchannel[i]]  )
            )
    {
        markovTrustworthiness.at(ueRnti)[i] += 0.01;
        markovTrustworthiness.at(ueRnti)[i] = markovTrustworthiness.at(ueRnti)[i] > 1.0 ? 1.0 : markovTrustworthiness.at(ueRnti)[i];
    }
    else
    {

    }

    bool fraudulent = false;
    if (markovTrustworthiness.at(ueRnti)[i] <= 0.1)
    {
        if (fraudulentSensingUEs.find(ueRnti) == fraudulentSensingUEs.end())
        {
            std::vector<bool> temp{false, false, false, false};
            temp[i] = true;
            fraudulentSensingUEs.insert({ueRnti, temp});

        }
        else
            fraudulentSensingUEs.find(ueRnti)->second[i] = true;
        fraudulent = true;
    }
    else
    {
        if (fraudulentSensingUEs.find(ueRnti) != fraudulentSensingUEs.end())
        {
            auto tempUE = fraudulentSensingUEs.find(ueRnti);
            tempUE->second[i] = false;
            bool empty = true;
            for (auto subchannel: tempUE->second)
                if (subchannel)
                    empty = false;
            if (empty)
                fraudulentSensingUEs.erase(ueRnti);
        }
    }

    //Ignore fakeReportDetection (a.k.a. harmonic mean)
    BooleanValue num;
    GlobalValue::GetValueByName("HARMONIC_DETECTION", num);
    if(!num)
        fraudulent = false; //TODO: find a better way to do that and prevent recompiling
    return fraudulent;
}


//Implements the fusion algorithm for collaborative sensing reports
std::bitset<132> LteEnbMac::mergeSensingReports(mergeAlgorithmEnum alg, bool senseRBs, bool harmonicDetection)
{
    //Proceed to spectrum sensing fusion
    std::vector<std::vector<bool>> fusedResults;
    while (channelOccupation.size() > 0)//just an if with break
    {
        auto frameIt = channelOccupation.rbegin();

        //Check if the frame is the current or the previous
        //effectively discard old sensing reports
        if (!(m_frameNo <= frameIt->first + 1))
            break;//jump out of the if

        //Load the latest frame with registered reports
        if (frameIt->second.size() < 1 && channelOccupation.size() > 1)
        {
            std::next(frameIt, 1);
        }

        auto subframeIt = frameIt->second.rbegin();

        auto numChannels = subframeIt->second.rbegin()->second.UnexpectedAccess_FalseAlarm_FalseNegBitmap.size();

        fusedResults = std::vector<std::vector<bool>> (numChannels);//numChannels
        for (auto &fusedResult: fusedResults)
            fusedResult = std::vector<bool>(3);


        int k = 0;
        int randomSample = true;
        std::stringstream ss;
        switch(alg)
        {

            case MRG_OR:
                {

                    for (auto origAddr : subframeIt->second)
                    {
                        //1st check against Byzantine attacks
                        //Skip reports from UEs that report fraudulent CQIs

                        //auto fraudulentUE = fraudulentCqiUEs.find(origAddr.first);
                        //if (fraudulentUE != fraudulentCqiUEs.end()) //Only makes sense if not subdivided by subchannel
                        //    continue;

                        //Skip reports from UEs that didn't reported their CQI at least twice
                        //if(prev_ue_to_cqi_map.find(origAddr.first) == prev_ue_to_cqi_map.end() || ue_to_cqi_map.find(origAddr.first) == ue_to_cqi_map.end())
                        //    continue;

                        //Check if there is an entry for Cqi per subchannel for the current UE
                        //auto prevCqi   = prev_ue_to_cqi_map.at(origAddr.first);
                        //auto latestCqi = ue_to_cqi_map.at(origAddr.first);

                        //Iterate through UE channel sensing information and fuse
                        int i = 0;
                        int j = 0;
                        for(auto channelReg: origAddr.second.UnexpectedAccess_FalseAlarm_FalseNegBitmap)
                        {
                            bool fraudulent = false;
                            //if (harmonicDetection)
                            //    fraudulent = harmonicMeanFraudDetector(origAddr.first, prevCqi, latestCqi, channelReg, i);

                            if ( !fraudulent )
                            {
                                //Or between sensing results
                                fusedResults[i][0] = fusedResults[i][0] || channelReg[0];
                            }

                           if (prevSensing.find(origAddr.first) == prevSensing.end())
                           {
                               std::vector<bool> temp{false, false, false, false};
                               prevSensing.insert({origAddr.first, temp});
                           }

                            //Count if prevSensing != currSensing
                            if (countRequiredBits.find(origAddr.first) == countRequiredBits.end())
                            {
                                std::vector<uint64_t> temp{0,0,0,0};
                                countRequiredBits.emplace(origAddr.first, temp);
                            }

                            if (channelReg[0] != prevSensing.at(origAddr.first)[i])
                                countRequiredBits.at(origAddr.first)[i]++;

                            //Update prevSensing
                            prevSensing.at(origAddr.first)[i] = channelReg[0];

                            i++;
                        }
                    }
                }
                break;
            case MRG_AND:
                {
                    for (auto &fusedResult: fusedResults)
                    {
                        //Set sensing results to detecting a PU presence
                        fusedResult[0] = true;
                    }

                    for (auto origAddr : subframeIt->second)
                    {
                        auto fraudulentUE = fraudulentCqiUEs.find(origAddr.first);
                        //if (fraudulentUE != fraudulentCqiUEs.end()) //Only makes sense if not subdivided by subchannel
                        //    continue;

                        //Skip reports from UEs that didn't reported their CQI at least twice
                        if(prev_ue_to_cqi_map.find(origAddr.first) == prev_ue_to_cqi_map.end() || ue_to_cqi_map.find(origAddr.first) == ue_to_cqi_map.end())
                            continue;

                        //Check if there is an entry for Cqi per subchannel for the current UE
                        auto prevCqi   = prev_ue_to_cqi_map.at(origAddr.first);
                        auto latestCqi = ue_to_cqi_map.at(origAddr.first);

                        int i = 0;
                        for(auto channelReg: origAddr.second.UnexpectedAccess_FalseAlarm_FalseNegBitmap)
                        {
                            bool fraudulent = false;
                            if (harmonicDetection)
                               fraudulent = harmonicMeanFraudDetector(origAddr.first, prevCqi, latestCqi, channelReg, i);

                            if ( !fraudulent )
                            {
                                //If every UE reported the presence, keep marked as present, else mark as not present
                                fusedResults[i][0] = fusedResults[i][0] && channelReg[0];
                            }

                            if (prevSensing.find(origAddr.first) == prevSensing.end())
                            {
                                std::vector<bool> temp{false, false, false, false};
                                prevSensing.insert({origAddr.first, temp});
                            }

                            if (countRequiredBits.find(origAddr.first) == countRequiredBits.end())
                            {
                                std::vector<uint64_t> temp{0,0,0,0};
                                countRequiredBits.emplace(origAddr.first, temp);
                            }

                            //Count if prevSensing != currSensing
                            if (channelReg[0] != prevSensing.at(origAddr.first)[i])
                                countRequiredBits.at(origAddr.first)[i]++;

                            //Update prevSensing
                            prevSensing.at(origAddr.first)[i] = channelReg[0];

                            i++;
                        }
                    }
                    //Checking for false positives and negatives is made in the end
                }
                break;
            case MRG_XOR:
                {
                    for (auto origAddr : subframeIt->second)
                    {
                        int i = 0;
                        for(auto channelReg: origAddr.second.UnexpectedAccess_FalseAlarm_FalseNegBitmap)
                        {
                            fusedResults[i][0] = fusedResults[i][0] ^ channelReg[0];
                            i++;
                        }
                    }
                    //Checking for false positives and negatives is made in the end
                }
                break;
            case MRG_XNOR:
                {
                    for (auto origAddr : subframeIt->second)
                    {
                        int i = 0;
                        for(auto channelReg: origAddr.second.UnexpectedAccess_FalseAlarm_FalseNegBitmap)
                        {
                            fusedResults[i][0] = !(fusedResults[i][0] ^ channelReg[0]);
                            i++;
                        }
                    }
                    //Checking for false positives and negatives is made in the end
                }
                break;
            case MRG_MONTECARLOFUSION://todo
                {

                    //Collect montecarlo samples (equivalent to line 2 of Monte Carlo Fusion algorithm)
                    std::vector<std::vector<bool>> monteCarloSamples;
                    for (auto origAddr : subframeIt->second)
                    {
                        auto ueRnti = origAddr.first;
                        std::vector<bool> samples;

                        int i = 0;
                        for(auto channelReg: origAddr.second.UnexpectedAccess_FalseAlarm_FalseNegBitmap)
                        {
                            samples.push_back(channelReg[0]);
                            i++;
                        }
                        monteCarloSamples.push_back(samples);
                    }

                    //Calculate averages and deviation
                    std::vector<float> averages;
                    for (int i = 0; i < monteCarloSamples.at(0).size(); i++)
                    {
                        int sum = 0;
                        for (int j = 0; j < monteCarloSamples.size(); j++)
                            sum += monteCarloSamples[j][i] ? 1 : 0;
                        averages.push_back(sum/monteCarloSamples.size());
                    }

                    float C = monteCarloSamples.size(); // number of UEs and samples
                    float T = 1;

                    //For each channel
                    for(int i = 0; i < monteCarloSamples.at(0).size(); i++)
                    {
                        //Calculate the monte carlo fused solution based on a gaussian distribution
                        float x = averages.at(i);
                        float y = exp(-C*pow(y-x,2)/(2*T));
                    }
                    //Checking for false positives and negatives is made in the end
                }
                break;
            case MRG_AVG:
                {
                    std::vector<float> avgs{0,0,0,0};
                    for (auto origAddr : subframeIt->second)
                    {
                        auto ueRnti = origAddr.first;

                        int i = 0;
                        for(auto channelReg: origAddr.second.UnexpectedAccess_FalseAlarm_FalseNegBitmap)
                        {
                            avgs[i] += channelReg[0];
                            i++;
                        }
                    }

                    if (subframeIt->second.size() > 0)
                        for(int i = 0; i < 4; i++)
                        {
                            avgs[i] /= subframeIt->second.size();
                            fusedResults[i][0] = avgs[i] > 0.05 ? true : false;
                            std::cout << Simulator::Now() << " i " << i << " avg " << avgs[i] << " fusedResults " << fusedResults[i][0] << std::endl;
                        }
                }
                break;
#ifdef NS3_PYTORCH
            case MRG_NN:
                {

                    //Prepare A30 cqi list
                    for (auto & cqiEntry : tempCqi)
                    {
                        if(cqiEntry.m_cqiType != ns3::CqiListElement_s::A30)
                            continue;
                        //A30 CQIs at this point
                        std::vector<uint8_t> cqisList;
                        for (auto &rbEntry: cqiEntry.m_sbMeasResult.m_higherLayerSelected)
                        {
                            cqisList.push_back(rbEntry.m_sbCqi.at(0));
                        }
                        if(ue_to_cqi_map.find(cqiEntry.m_rnti) == ue_to_cqi_map.end())
                        {
                            ue_to_cqi_map.insert({cqiEntry.m_rnti, cqisList});
                            ue_to_position_map.insert({ue_to_position_map.size(), cqiEntry.m_rnti});
                        }
                        else
                            ue_to_cqi_map.at(cqiEntry.m_rnti) = cqisList;
                    }

                    //Prepare P10 cqi list
                    //for (auto & cqiEntry : tempCqi)
                    //{
                    //    if(cqiEntry.m_cqiType == ns3::CqiListElement_s::A30)
                    //        continue;
                    //    //P10 CQIs at this point
                    //    if(ue_to_cqi_map.find(cqiEntry.m_rnti) == ue_to_cqi_map.end())
                    //        ue_to_cqi_map.insert({cqiEntry.m_rnti, cqiEntry.m_wbCqi.at(0)});
                    //    else
                    //        ue_to_cqi_map.at(cqiEntry.m_rnti) = cqiEntry.m_wbCqi.at(0);
                    //}

                    //if there is no CQI data available, revert to OR
                    if (ue_to_cqi_map.empty())
                    {
                        for (auto origAddr : subframeIt->second)
                        {
                            int i = 0;
                            for(auto channelReg: origAddr.second.UnexpectedAccess_FalseAlarm_FalseNegBitmap)
                            {
                                //Or between sensing results
                                fusedResults[i][0] = fusedResults[i][0] || channelReg[0];
                                i++;
                            }
                        }
                        break;
                    }


                    //Prepare the nn input
                    std::vector<float> encodedData;
                    std::vector<bool> pu_pres(4);
                    //for (auto &ue : subframeIt->second)
                    //std::stringstream ss;
                    for (auto &ue_position_to_rnti: ue_to_position_map)
                    {
                        auto uePosition = ue_position_to_rnti.first;
                        auto ueRnti = ue_position_to_rnti.second;
                        //ss << "(" << uePosition << "," << ueRnti << "), ";

                        //If the UE hasn't sent a CQI info, fill its entries
                        //if(subframeIt->second.find(ueRnti) == subframeIt->second.end())
                        //{
                        //    for (int i = 0; i < numChannels*2; i++)
                        //        encodedData.push_back(0);
                        //    continue;
                        //}

                        auto ue = subframeIt->second.at(ueRnti);

                        if (ue_to_cqi_map.find(ueRnti) == ue_to_cqi_map.end())
                            continue;

                        int i = 0;
                        int j = 0;
                        for (auto channelReg : ue.UnexpectedAccess_FalseAlarm_FalseNegBitmap)
                        {
                            encodedData.push_back(channelReg[0]);
                            encodedData.push_back(ue_to_cqi_map.at(ueRnti).at(i)/15.0);
                            pu_pres.at(j) = pu_pres.at(j) || ue.PU_presence_V.at(j);
                            i += bandwidth/4;
                            j++;
                            //if (encodedData.back() != 1.0 && encodedData.back() != 0.0)
                            //    std::cout << " bang " << Simulator::Now().GetSeconds() << std::endl;
                        }
                    }
                    //std::cout << "len: " << encodedData.size() << "; " << ss.str() << std::endl;
                    //Insert padding
                    int padding_length = nn_width - (int) encodedData.size();
                    for (int i = 0; i < padding_length; i++)
                        encodedData.push_back(0.0);
                    std::stringstream ss1;
                    //std::stringstream ss;
                    for (auto num : encodedData)
                        ss1 << num << " ";
                    ss1 << pu_pres;
                    std::cout << Simulator::Now() << " : " << ss1.str() << std::endl;
                    ss << ss1.str();
                    //Remove older entry and insert the newer one
                    //nn_encodedDataSlice.clear();
                    nn_encodedDataSlice.erase(nn_encodedDataSlice.begin());
                    nn_encodedDataSlice.push_back(encodedData);
                    //std::stringstream ss;
                    //std::vector<float> encodedTensor;
                    //for (auto slice: nn_encodedDataSlice)
                    //{
                    //    encodedTensor.insert(std::end(encodedTensor), std::begin(slice), std::end(slice));
                    //
                    //    //for (auto num : slice)
                    //    //    ss << num << " ";
                    //    //ss << "\n";
                    //}
                    //std::cout << ss.str() << std::endl;

                    //Rebuild entry tensor
                    torch::Tensor k;
                    k = torch::from_blob(nn_encodedDataSlice.data(),{1, 10, nn_width});
                    k = k.toType(torch::kFloat);
                    //std::cout << "sizes " << k.sizes() << std::endl;

                    //Assemble nn input in an IValue
                    std::vector<torch::jit::IValue> inputs;
                    inputs.push_back(k);

                    //Feed the nn
                    torch::Tensor output = nn_module.forward(inputs).toTensor();

                    //Decode the nn output
                    //std::cout << "sizes " << output.sizes() << std::endl;
                    //std::cout << "values " << output[9].sizes() << std::endl;
                    //std::cout << "argmax " << output[0][9].argmax().item<int>() << std::endl;// << "val " << output[9].max().item<float>() << std::endl;
                    //std::cout << output.sizes() << std::endl;
                    std::vector<bool> vec;
                    float notdetected, detected;
                    for (int i = 0; i<8-1; i+=2)
                    {
                        notdetected = output[0][9][i].item<float>();
                        detected = output[0][9][i + 1].item<float>();
                        if (isnan(notdetected) || isnan(detected))
                            vec.push_back(false);
                        else
                            vec.push_back( notdetected < detected );
                    }

                    //uint16_t nn_output = output[9].argmax().item<int>() % 16;
                    int i = 0;
                    for(auto & channelReg : fusedResults)
                    {
                        fusedResults[i][0] = vec[i];//nn_output % 2;
                        //if (fusedResults[i][0])
                        //    std::cout << "bing bing bing" << std::endl;
                        //nn_output /= 2;
                        i++;
                    }
                    //Checking for false positives and negatives is made in the end
                }
                break;
#endif
            /*
            case MRG_KALMAN:
                {
                    //Prepare A30 cqi list
                    for (auto & cqiEntry : tempCqi)
                    {
                        if(cqiEntry.m_cqiType != ns3::CqiListElement_s::A30)
                            continue;
                        //A30 CQIs at this point
                        std::vector<uint8_t> cqisList;
                        for (auto &rbEntry: cqiEntry.m_sbMeasResult.m_higherLayerSelected)
                        {
                            cqisList.push_back(rbEntry.m_sbCqi.at(0));
                        }
                        if(ue_to_cqi_map.find(cqiEntry.m_rnti) == ue_to_cqi_map.end())
                            ue_to_cqi_map.insert({cqiEntry.m_rnti, cqisList});
                        else
                            ue_to_cqi_map.at(cqiEntry.m_rnti) = cqisList;
                    }

                    //Prepare P10 cqi list
                    //for (auto & cqiEntry : tempCqi)
                    //{
                    //    if(cqiEntry.m_cqiType == ns3::CqiListElement_s::A30)
                    //        continue;
                    //    //P10 CQIs at this point
                    //    if(ue_to_cqi_map.find(cqiEntry.m_rnti) == ue_to_cqi_map.end())
                    //        ue_to_cqi_map.insert({cqiEntry.m_rnti, cqiEntry.m_wbCqi.at(0)});
                    //    else
                    //        ue_to_cqi_map.at(cqiEntry.m_rnti) = cqiEntry.m_wbCqi.at(0);
                    //}

                    //Prepare the nn input
                    std::vector<float> encodedData;
                    for (auto &ue : subframeIt->second)
                    {
                        auto ueRnti = ue.first;

                        if (ue_to_cqi_map.find(ueRnti) == ue_to_cqi_map.end())
                            continue;

                        int i = 0;
                        for (auto channelReg : ue.second.UnexpectedAccess_FalseAlarm_FalseNegBitmap)
                        {
                            encodedData.push_back(channelReg[0]);
                            encodedData.push_back(ue_to_cqi_map.at(ueRnti).at(i)/15);
                            i += bandwidth/4;
                        }
                    }

                    Eigen::VectorXd y(encodedData.size());

                    int i = 0;
                    for(auto data : encodedData)
                    {
                        y(i) = data;
                        i++;
                    }

                    kf.update(y);
                    auto kfstate = kf.state();//.transpose();
                    std::vector<double> fusion(kfstate.data(), kfstate.data()+kfstate.rows()*kfstate.cols());
                    double maxval = -100000;
                    int maxindex = 0;

                    i = 0;
                    for (auto element: fusion)
                    {
                        if(element > maxval)
                        {
                            maxval = element;
                            maxindex = i;
                        }
                        i++;
                    }

                    i=0;
                    for(auto & channelReg : fusedResults)
                    {
                        fusedResults[i][0] = maxindex % 2;
                        maxindex /= 2;
                        i++;
                    }

                    //Checking for false positives and negatives is made in the end
                }
                break;
            */
            case MRG_1_OF_N: if (k == 0) {k = 1; randomSample = false;}
            case MRG_2_OF_N: if (k == 0) {k = 2; randomSample = false;}
            case MRG_3_OF_N: if (k == 0) {k = 3; randomSample = false;}
            case MRG_4_OF_N: if (k == 0) {k = 4; randomSample = false;}
            case MRG_1_OF_N_RAND: if (k == 0) {k = 1; randomSample = true;}
            case MRG_2_OF_N_RAND: if (k == 0) {k = 2; randomSample = true;}
            case MRG_3_OF_N_RAND: if (k == 0) {k = 3; randomSample = true;}
            case MRG_4_OF_N_RAND: if (k == 0) {k = 4; randomSample = true;}
            case MRG_K_OF_N:
                {
                    std::vector<int> kConfirmed     (numChannels);

                    int numUEs = UeRntiMap.size();

                    //Get size of population to be sampled(N)
                    int n = numUEs;

                    //Select (N) random UEs into a population
                    std::map<int,bool> ueOffsetsPopulation;
                    while(ueOffsetsPopulation.size() < n)
                    {
                        ueOffsetsPopulation.emplace(rand() % numUEs, true);
                    }

                    //Select (K) random UEs to sample in the previous population
                    std::map<int,bool> ueOffsetsSamples;
                    while(ueOffsetsSamples.size() < (randomSample ? k : n))
                    {
                        ueOffsetsSamples.emplace(rand() % n, true);
                    }

                    //Merge their reports
                    for (auto offset : ueOffsetsSamples)
                    {
                        //Get sampled population iterator and advance to the sampled UE
                        auto uePopulation = ueOffsetsPopulation.begin();
                        std::advance(uePopulation, offset.first);

                        //Get global population (RNTI) and advance to the sampled UE
                        auto ueRnti = UeRntiMap.begin();
                        std::advance(ueRnti,uePopulation->first);
                        //std::cout << "RNTI " << ueRnti->first << std::endl;
                        //Check if the UE with the current RNTI reported something
                        if (subframeIt->second.find(ueRnti->first) != subframeIt->second.end())
                        {

                            auto fraudulentUE = fraudulentCqiUEs.find(ueRnti->first);
                            //if (fraudulentUE != fraudulentCqiUEs.end()) //Only makes sense if not subdivided by subchannel
                            //    continue;

                            //Skip reports from UEs that didn't reported their CQI at least twice
                            if(prev_ue_to_cqi_map.find(ueRnti->first) == prev_ue_to_cqi_map.end() || ue_to_cqi_map.find(ueRnti->first) == ue_to_cqi_map.end())
                                continue;

                            //Check if there is an entry for Cqi per subchannel for the current UE
                            auto prevCqi   = prev_ue_to_cqi_map.at(ueRnti->first);
                            auto latestCqi = ue_to_cqi_map.at(ueRnti->first);

                            int i = 0;
                            for(auto channelReg: subframeIt->second.at(ueRnti->first).UnexpectedAccess_FalseAlarm_FalseNegBitmap)
                            {
                                bool fraudulent = harmonicMeanFraudDetector(ueRnti->first, prevCqi, latestCqi, channelReg, i);

                                if ( !fraudulent )
                                {
                                    //If every UE reported the presence, keep marked as present, else mark as not present
                                    kConfirmed[i] += channelReg[0] ? 1 : 0;
                                }


                                if (prevSensing.find(ueRnti->first) == prevSensing.end())
                                {
                                    std::vector<bool> temp{false, false, false, false};
                                    prevSensing.insert({ueRnti->first, temp});
                                }

                                if (countRequiredBits.find(ueRnti->first) == countRequiredBits.end())
                                {
                                    std::vector<uint64_t> temp{0,0,0,0};
                                    countRequiredBits.emplace(ueRnti->first, temp);
                                }

                                //Count if prevSensing != currSensing
                                if (channelReg[0] != prevSensing.at(ueRnti->first)[i])
                                    countRequiredBits.at(ueRnti->first)[i]++;

                                //Update prevSensing
                                prevSensing.at(ueRnti->first)[i] = channelReg[0];

                                i++;
                            }
                        }
                    }

                    //std::cout << std::endl;

                    for(int i=0; i < numChannels; i++)
                    {
                        fusedResults[i][0] = kConfirmed[i] >= k;
                    }
                    //Checking for false positives and negatives is made in the end
                }
                break;
            case MRG_MULTIFRAME_OR:     if (k == 0) k = 1;
            case MRG_MULTIFRAME_2_OF_N: if (k == 0) k = 2;
            case MRG_MULTIFRAME_3_OF_N: if (k == 0) k = 3;
            case MRG_MULTIFRAME_4_OF_N: if (k == 0) k = 4;
            case MRG_MULTIFRAME_K_OF_N:
            default:
                {

                    k = 1;
                    int frameOffset = 0;
                    int subframeOffset = 0;

                    if (m_subframeNo <3)
                    {
                        frameOffset = 1;
                        subframeOffset = 5;
                    }

                    for (; frameIt != channelOccupation.rend() && frameIt->first >= (m_frameNo - frameOffset); frameIt++)//m_frameNo-1 is much more agressive
                    {
                        auto subframeIt = frameIt->second.begin();
                        std::advance(subframeIt,subframeOffset);

                        std::vector<int> kConfirmed     (numChannels);

                        for ( ; subframeIt != frameIt->second.end(); subframeIt++)
                        {
                            for (auto origAddr : subframeIt->second)
                            {
                                int i = 0;
                                for(auto channelReg: subframeIt->second.at(origAddr.first).UnexpectedAccess_FalseAlarm_FalseNegBitmap)
                                {
                                    kConfirmed[i] += channelReg[0] ? 1 : 0;
                                    i++;
                                }
                            }
                        }


                        for(int i=0; i < numChannels; i++)
                        {
                            fusedResults[i][0] = kConfirmed[i] >= k;
                        }
                    }
                }
                break;
        }


        int falseNegativeCount = 0;
        //Check for false positives and false negatives
        for (auto &ueReg : subframeIt->second)
        {
            //Verify if results are false positives or false negatives
            int i = 0;
            for(auto channelReg: ueReg.second.UnexpectedAccess_FalseAlarm_FalseNegBitmap)
            {


                //Or between sensing results
                if(fusedResults[i][0] != ueReg.second.PU_presence_V[i])
                {
                    if(fusedResults[i][0])
                    {
                        //False positive
                        fusedResults[i][1] = true;
                    }
                    else
                    {
                        //False negative
                        fusedResults[i][2] = true;
                        falseNegativeCount++;
                    }
                }
                i++;
            }
        }

#ifdef NS3_PYTORCH
        //Dump nn input that failed to produce the correct output
        if (falseNegativeCount != 0)
        {
            falseNegativeFile << Simulator::Now() << " : " << ss.str() << std::endl;
        }
#endif
        ss.clear();
        break;//out of if
    }

    std::bitset<132> sensedBitmap{};

    //No entries to fuse
    if(fusedResults.empty())
        return sensedBitmap;

    //First create map for sensed frames
    unexpectedChannelAccessBitmap.emplace(m_frameNo, std::map <uint64_t, std::vector<std::vector<bool>> > ());

    //After that, create map for sensed subframes
    unexpectedChannelAccessBitmap.at(m_frameNo).emplace(m_subframeNo, fusedResults);


    //Create bitmap to feed the scheduler
    int numRbsPerChannel = bandwidth/fusedResults.size();
    int i = 0;

    for (unsigned c = 0; c < fusedResults.size(); c++)
    {
        if(!fusedResults[c][0])
            continue;
        for (unsigned k = c*numRbsPerChannel; k < (c+1)*numRbsPerChannel; k++)
        {
            sensedBitmap[k] = fusedResults[c][0];
            //std::cout << "k=" << k << " sensedBitmap " << std::bitset<50>(sensedBitmap)  << std::endl;
        }
    }

    return sensedBitmap;
}


} // namespace ns3
