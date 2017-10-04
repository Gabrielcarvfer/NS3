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
 * Author: Giuseppe Piro  <g.piro@poliba.it>
 *         Marco Miozzo <mmiozzo@cttc.es>
 */


#ifndef TRACE_FADING_LOSS_MODEL_H
#define TRACE_FADING_LOSS_MODEL_H


#include <ns3/object.h>
#include <ns3/spectrum-propagation-loss-model.h>
#include <map>
#include "ns3/random-variable-stream.h"
#include <ns3/nstime.h>

namespace ns3 {


class MobilityModel;


/**
 * \ingroup lte
 *
 * \brief fading loss model based on precalculated fading traces
 */
class TraceFadingLossModel : public SpectrumPropagationLossModel
{
public:
  TraceFadingLossModel ();
  virtual ~TraceFadingLossModel ();

  static TypeId GetTypeId ();
  
  virtual void DoInitialize (void);

  /**
   * \brief The couple of mobility mnode that form a fading channel realization
   */
  typedef std::pair<Ptr<const MobilityModel>, Ptr<const MobilityModel> > ChannelRealizationId_t;

 /**
  * Assign a fixed random variable stream number to the random variables
  * used by this model.  Return the number of streams (possibly zero) that
  * have been assigned.
  *
  * \param stream first stream index to use
  * \return the number of stream indices assigned by this model
  */
  int64_t AssignStreams (int64_t stream);

  
private:
  /**
   * \param txPsd set of values vs frequency representing the
   *              transmission power. See SpectrumChannel for details.
   * \param a sender mobility
   * \param b receiver mobility
   * \return set of values vs frequency representing the received
   *         power in the same units used for the txPsd parameter.
   */
  Ptr<SpectrumValue> DoCalcRxPowerSpectralDensity (Ptr<const SpectrumValue> txPsd,
                                                   Ptr<const MobilityModel> a,
                                                   Ptr<const MobilityModel> b) const;
                                                   
  /**
  * \brief Get the value for a particular sub channel and a given speed
  * \param subChannel the sub channel for which a value is requested
  * \param speed the relative speed of the two devices
  * \return the loss for a particular sub channel
  */
  double GetValue (int subChannel, double speed);
  
  void SetTraceFileName (std::string fileName);
  void SetTraceLength (Time t);
  
  void LoadTrace ();


   
  mutable std::map <ChannelRealizationId_t, int > m_windowOffsetsMap;
  
  mutable std::map <ChannelRealizationId_t, Ptr<UniformRandomVariable> > m_startVariableMap;
  
  /**
   * Vector with fading samples in time domain (for a fixed RB)
   */
  typedef std::vector<double> FadingTraceSample;
  /**
   * Vector collecting the time fading traces in the frequency domain (per RB)
   */
  typedef std::vector<FadingTraceSample> FadingTrace;


  
  std::string m_traceFile;
  
  FadingTrace m_fadingTrace;

  
  Time m_traceLength;
  uint32_t m_samplesNum;
  Time m_windowSize;
  uint8_t m_rbNum;
  mutable Time m_lastWindowUpdate;
  uint8_t m_timeGranularity;
  mutable uint64_t m_currentStream;
  mutable uint64_t m_lastStream;
  uint64_t m_streamSetSize;
  mutable bool m_streamsAssigned;
  
};



} // namespace ns3

#endif /* TRACE_FADING_LOSS_MODEL_H */
