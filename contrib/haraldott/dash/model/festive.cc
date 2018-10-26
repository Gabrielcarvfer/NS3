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

#include "festive.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("FestiveAlgorithm");

NS_OBJECT_ENSURE_REGISTERED (FestiveAlgorithm);

FestiveAlgorithm::FestiveAlgorithm (  const videoData &videoData,
                                      const playbackData & playbackData,
                                      const bufferData & bufferData,
                                      const throughputData & throughput) :
  AdaptationAlgorithm (videoData, playbackData, bufferData, throughput),
  m_targetBuf (30000000),
  m_delta (m_videoData.segmentDuration),
  m_alpha (12.0),
  m_highestRepIndex (videoData.averageBitrate.size () - 1),
  m_thrptThrsh (0.85)
{
  NS_LOG_INFO (this);
  m_smooth.push_back (5);  // after how many steps switch up is possible
  m_smooth.push_back (1);  // switch up by how many representatations at once
  NS_ASSERT_MSG (m_highestRepIndex >= 0, "The highest quality representation index should be => 0");
}

algorithmReply
FestiveAlgorithm::GetNextRep (const int64_t segmentCounter, int64_t clientId)
{
  int64_t timeNow = Simulator::Now ().GetMicroSeconds ();
  bool decisionMade = false;
  algorithmReply answer;
  answer.decisionTime = timeNow;
  answer.nextDownloadDelay = 0;
  answer.delayDecisionCase = 0;

  if (segmentCounter == 0)
    {
      answer.nextRepIndex = 0;
      answer.decisionCase = 0;
      return answer;
    }
  int64_t bufferNow = m_bufferData.bufferLevelNew.back () - (timeNow - m_throughput.transmissionEnd.back ());

  // not enough completed requests, select nextRepIndex
  if (m_throughput.transmissionEnd.size () < 20)
    {
      answer.nextRepIndex = 0;
      answer.decisionCase = 1;
      return answer;
    }

  // compute throughput estimation
  std::vector<double> thrptEstimationTmp;
  for (unsigned sd = m_playbackData.playbackIndex.size (); sd-- > 0; )
    {
      if (m_throughput.bytesReceived.at (sd) == 0)
        {
          continue;
        }
      else
        {
          thrptEstimationTmp.push_back ((8.0 * m_throughput.bytesReceived.at (sd))
                                        / ((double)((m_throughput.transmissionEnd.at (sd) - m_throughput.transmissionRequested.at (sd)) / 1000000.0)));
        }
      if (thrptEstimationTmp.size () == 20)
        {
          break;
        }
    }
  // calculate harmonic mean of values in thrptEstimationTmp
  double harmonicMeanDenominator = 0;
  for (uint i = 0; i < thrptEstimationTmp.size (); i++)
    {
      harmonicMeanDenominator += 1 / (thrptEstimationTmp.at (i));
    }
  double thrptEstimation = thrptEstimationTmp.size () / harmonicMeanDenominator;

  // compute b_delay
  int64_t lowerBound = m_targetBuf - m_delta;
  int64_t upperBound = m_targetBuf + m_delta;
  int64_t randBuf = (int64_t) lowerBound + ( std::rand () % ( upperBound - (lowerBound) + 1 ) );
  if (bufferNow > randBuf)
    {
      answer.nextDownloadDelay = bufferNow - randBuf;
      answer.delayDecisionCase = 1;
    }

  // select reference bit rate
  int64_t currentRepIndex = m_playbackData.playbackIndex.back ();
  int64_t refIndex = currentRepIndex;

  // decide if we need to decrease
  if (currentRepIndex > 0
      && m_videoData.averageBitrate.at (currentRepIndex) > thrptEstimation * m_thrptThrsh)
    {
      refIndex = currentRepIndex - 1;
      answer.decisionCase = 1;
      decisionMade = true;
    }

  // decide if we need to increase
  assert (m_smooth.at (0) > 0);
  assert (m_smooth.at (1) == 1);
  if (currentRepIndex < m_highestRepIndex && !decisionMade)
    {
      int count = 0;
      for (unsigned _sd = m_playbackData.playbackIndex.size () - 1; _sd-- > 0; )
        {
          if (currentRepIndex == m_playbackData.playbackIndex.at (_sd))
            {
              count++;
              if (count >= m_smooth.at (0))
                {
                  break;
                }
            }
          else
            {
              break;
            }
        }
      if (count >= m_smooth.at (0)
          && (double) m_videoData.averageBitrate.at (currentRepIndex + 1) <= thrptEstimation)
        {
          refIndex = currentRepIndex + 1;
          answer.decisionCase = 1;
          decisionMade = true;
        }
    }

  // neither did we increase nor decrease, so we stay at the same rep index
  if (!decisionMade)
    {
      answer.nextRepIndex = currentRepIndex;
      answer.decisionCase = 3;
      return answer;
    }

  // compute number of bit rate switches in the last 20 seconds
  int64_t numberOfSwitches = 0;
  std::vector<int64_t> foundIndices;
  for (unsigned _sd = m_playbackData.playbackStart.size () - 1; _sd-- > 0; )
    {
      if (m_playbackData.playbackStart.at (_sd) < timeNow)
        {
          break;
        }
      else if (currentRepIndex != m_playbackData.playbackIndex.at (_sd))
        {
          if (std::find (foundIndices.begin (), foundIndices.end (), currentRepIndex) != foundIndices.end ())
            {
              continue;
            }
          numberOfSwitches++;
          foundIndices.push_back (currentRepIndex);
        }
    }
  double scoreEfficiencyCurrent = std::abs ((double)m_videoData.averageBitrate.at (currentRepIndex)
                                            / double(std::min (thrptEstimation, (double)m_videoData.averageBitrate.at (refIndex))) - 1.0);

  double scoreEfficiencyRef = std::abs ((double)m_videoData.averageBitrate.at (refIndex)
                                        / double(std::min (thrptEstimation, (double)m_videoData.averageBitrate.at (refIndex))) - 1.0);

  double scoreStabilityCurrent = pow (2.0, (double)numberOfSwitches);
  double scoreStabilityRef = pow (2.0, ((double)numberOfSwitches)) + 1.0;

  if ((scoreStabilityCurrent + m_alpha * scoreEfficiencyCurrent) < scoreStabilityRef + m_alpha * scoreEfficiencyRef)
    {
      answer.nextRepIndex = currentRepIndex;
      answer.decisionCase = 4;
      return answer;
    }
  else
    {
      answer.nextRepIndex = refIndex;
      return answer;
    }

}
} // namespace ns3