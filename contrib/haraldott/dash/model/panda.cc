/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright 2016 Technische Universitaet Berlin
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
 */

#include "panda.h"


namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("PandaAlgorithm");

NS_OBJECT_ENSURE_REGISTERED (PandaAlgorithm);

PandaAlgorithm::PandaAlgorithm (  const videoData &videoData,
                                  const playbackData & playbackData,
                                  const bufferData & bufferData,
                                  const throughputData & throughput) :
  AdaptationAlgorithm (videoData, playbackData, bufferData, throughput),
  m_kappa (0.28),
  m_omega (0.3),
  m_alpha (0.2),
  m_beta (0.2),
  m_epsilon (0.15),
  m_bMin (26),
  m_highestRepIndex (videoData.averageBitrate.size () - 1)
{
  NS_LOG_INFO (this);
  NS_ASSERT_MSG (m_highestRepIndex >= 0, "The highest quality representation index should be => 0");
}

algorithmReply
PandaAlgorithm::GetNextRep (const int64_t segmentCounter, int64_t clientId)
{
  const int64_t timeNow = Simulator::Now ().GetMicroSeconds ();
  int64_t delay = 0;
  if (segmentCounter == 0)
    {
      m_lastVideoIndex = 0;
      m_lastBuffer = (m_videoData.segmentDuration) / 1e6;
      m_lastTargetInterrequestTime = 0;

      algorithmReply answer;
      answer.nextRepIndex = 0;
      answer.nextDownloadDelay = 0;
      answer.decisionTime = timeNow;
      answer.decisionCase = 0;
      answer.delayDecisionCase = 0;
      return answer;
    }

  // estimate the bandwidth share
  double throughputMeasured = ((double)(m_videoData.averageBitrate.at (m_lastVideoIndex) * (m_videoData.segmentDuration / 1e6) )
                               / (double)((m_throughput.transmissionEnd.back () - m_throughput.transmissionRequested.back ()) / 1e6)) / 1e6;

  if (segmentCounter == 1)
    {
      m_lastBandwidthShare = throughputMeasured;
      m_lastSmoothBandwidthShare = m_lastBandwidthShare;
    }

  double actualInterrequestTime;
  if (timeNow - m_throughput.transmissionRequested.back () > m_lastTargetInterrequestTime * 1e6 )
    {
      actualInterrequestTime = (timeNow - m_throughput.transmissionRequested.back ()) / 1e6;
    }
  else
    {
      actualInterrequestTime = m_lastTargetInterrequestTime;
    }

  double bandwidthShare = (m_kappa * (m_omega - std::max (0.0, m_lastBandwidthShare - throughputMeasured + m_omega)))
    * actualInterrequestTime + m_lastBandwidthShare;
  if (bandwidthShare < 0)
    {
      bandwidthShare = 0;
    }
  m_lastBandwidthShare = bandwidthShare;

  double smoothBandwidthShare;
  smoothBandwidthShare = ((-m_alpha
                           * (m_lastSmoothBandwidthShare - bandwidthShare))
                          * actualInterrequestTime)
    + m_lastSmoothBandwidthShare;

  m_lastSmoothBandwidthShare = smoothBandwidthShare;

  double deltaUp = m_omega + m_epsilon * smoothBandwidthShare;
  double deltaDown = m_omega;
  int rUp = FindLargest (smoothBandwidthShare, segmentCounter - 1, deltaUp);
  int rDown = FindLargest (smoothBandwidthShare, segmentCounter - 1, deltaDown);


  int videoIndex;
  if ((m_videoData.averageBitrate.at (m_lastVideoIndex))
      < (m_videoData.averageBitrate.at (rUp)))
    {
      videoIndex = rUp;
    }
  else if ((m_videoData.averageBitrate.at (rUp))
           <= (m_videoData.averageBitrate.at (m_lastVideoIndex))
           && (m_videoData.averageBitrate.at (m_lastVideoIndex))
           <= (m_videoData.averageBitrate.at (rDown)))
    {
      videoIndex = m_lastVideoIndex;
    }
  else
    {
      videoIndex = rDown;
    }
  m_lastVideoIndex = videoIndex;

  // schedule next download request

  double targetInterrequestTime = std::max (0.0, ((double) ((m_videoData.averageBitrate.at (videoIndex) * (m_videoData.segmentDuration / 1e6)) / 1e6)
                                                  / smoothBandwidthShare) + m_beta * (m_lastBuffer - m_bMin));

  if (m_throughput.transmissionEnd.back () - m_throughput.transmissionRequested.back () < m_lastTargetInterrequestTime * 1e6)
    {
      delay = 1e6 * m_lastTargetInterrequestTime - (m_throughput.transmissionEnd.back () - m_throughput.transmissionRequested.back ());
    }
  else
    {
      delay = 0;
    }

  m_lastTargetInterrequestTime = targetInterrequestTime;

  m_lastBuffer = (m_bufferData.bufferLevelNew.back () - (timeNow - m_throughput.transmissionEnd.back ())) / 1e6;

  algorithmReply answer;
  answer.nextRepIndex = videoIndex;
  answer.nextDownloadDelay = delay;
  answer.decisionTime = timeNow;
  answer.decisionCase = 0;
  answer.delayDecisionCase = 0;
  return answer;
}

int
PandaAlgorithm::FindLargest (const double smoothBandwidthShare, const int64_t segmentCounter, const double delta)
{
  int64_t largestBitrateIndex = 0;
  for (int i = 0; i <= m_highestRepIndex; i++)
    {
      int64_t currentBitrate =  m_videoData.averageBitrate.at (i) / 1e6;
      if (currentBitrate <= (smoothBandwidthShare - delta))
        {
          largestBitrateIndex = i;
        }
    }
  return largestBitrateIndex;
}

} // namespace ns3