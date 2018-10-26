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

#include "tobasco2.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("TobascoAlgorithm");

NS_OBJECT_ENSURE_REGISTERED (TobascoAlgorithm);

TobascoAlgorithm::TobascoAlgorithm (  const videoData &videoData,
                                      const playbackData & playbackData,
                                      const bufferData & bufferData,
                                      const throughputData & throughput) :
  AdaptationAlgorithm (videoData, playbackData, bufferData, throughput),
  m_a1 (0.75),
  m_a2 (0.33),
  m_a3 (0.5),
  m_a4 (0.75),
  m_a5 (0.9),
  m_bMin (5000000),
  m_bLow (20000000),
  m_bHigh (40000000),
  m_bOpt ((int64_t)(0.5 * (m_bLow + m_bHigh))),
  m_deltaBeta (1000000),
  m_deltaTime (10000000),
  m_highestRepIndex (videoData.averageBitrate.size () - 1)
{
  NS_LOG_INFO (this);
  m_runningFastStart = true;
  NS_ASSERT_MSG (m_highestRepIndex >= 0, "The highest quality representation index should be >= 0");
}

algorithmReply
TobascoAlgorithm::GetNextRep ( const int64_t segmentCounter, int64_t clientId)
{
  int64_t decisionCase = 0;
  int64_t delayDecision = 0;
  int64_t nextRepIndex = 0;
  int64_t bDelay = 0;
  // we use timeFactor, to divide the absolute size of a segment that is given in bits with the duration of a
  // segment in seconds, so that we get bitrate per seconds
  double timeFactor = m_videoData.segmentDuration / 1000000;
  const int64_t timeNow = Simulator::Now ().GetMicroSeconds ();
  int64_t bufferNow = 0;
  // for the first segment the algorithm returns the lowest index 0 by definition, so we directly jump to the return part
  if (segmentCounter != 0)
    {
      nextRepIndex = m_lastRepIndex;
      bufferNow = m_bufferData.bufferLevelNew.back () - (timeNow - m_throughput.transmissionEnd.back ());
      double averageSegmentThroughput = AverageSegmentThroughput (timeNow - m_deltaTime, timeNow);
      double nextHighestRepBitrate;
      if (m_lastRepIndex < m_highestRepIndex)
        {
          nextHighestRepBitrate = (8.0 * m_videoData.averageBitrate.at (m_lastRepIndex + 1)) / timeFactor;
        }
      else
        {
          nextHighestRepBitrate = (8.0 * m_videoData.averageBitrate.at (m_lastRepIndex)) / timeFactor;
        }

      if (m_runningFastStart
          && m_lastRepIndex != m_highestRepIndex
          && MinimumBufferLevelObserved ()
          && ((8.0 * m_videoData.averageBitrate.at (m_lastRepIndex)) / timeFactor <= m_a1 * averageSegmentThroughput))
        {
          /* --------- running fast start phase --------- */
          if (bufferNow < m_bMin)
            {
              if (nextHighestRepBitrate <= (m_a2 * averageSegmentThroughput))
                {
                  decisionCase = 1;
                  nextRepIndex = m_lastRepIndex + 1;
                }
            }
          else if (bufferNow < m_bLow)
            {
              if (nextHighestRepBitrate <= (m_a3 * averageSegmentThroughput))
                {
                  decisionCase = 2;
                  nextRepIndex = m_lastRepIndex + 1;
                }
            }
          else
            {
              if (nextHighestRepBitrate <= (m_a4 * averageSegmentThroughput))
                {
                  decisionCase = 3;
                  nextRepIndex = m_lastRepIndex + 1;
                }
              if (bufferNow > m_bHigh)
                {
                  delayDecision = 1;
                  bDelay = m_bHigh - m_videoData.segmentDuration;
                }
            }
        }
      /* --------- /running_fast start phase --------- */
      else
        {
          m_runningFastStart = false;
          if (bufferNow < m_bMin)
            {
              decisionCase = 4;
              nextRepIndex = 0;
            }
          else if (bufferNow < m_bLow)
            {
              double lastSegmentThroughput = (8.0 * m_videoData.segmentSize.at (m_lastRepIndex).at (segmentCounter - 1))
                / ((double)(m_throughput.transmissionEnd.at (segmentCounter - 1) - m_throughput.transmissionStart.at (segmentCounter - 1)) / 1000000.0);

              if ((m_lastRepIndex != 0)
                  && ((8.0 * m_videoData.segmentSize.at (m_lastRepIndex).at (segmentCounter - 1)) / timeFactor >= lastSegmentThroughput))
                {
                  decisionCase = 5;
                  for (int i = m_highestRepIndex; i >= 0; i--)
                    {
                      if ((8.0 * m_videoData.segmentSize.at (i).at (segmentCounter - 1)) / timeFactor >= lastSegmentThroughput)
                        {
                          continue;
                        }
                      else
                        {
                          nextRepIndex = i;
                          break;
                        }
                    }
                  if (nextRepIndex >= m_lastRepIndex)
                    {
                      nextRepIndex = m_lastRepIndex - 1;
                    }
                }
            }
          else if (bufferNow < m_bHigh)
            {
              if ((m_lastRepIndex == m_highestRepIndex)
                  || (nextHighestRepBitrate >= m_a5 * averageSegmentThroughput))
                {
                  delayDecision = 2;
                  bDelay = (int64_t)(std::max (bufferNow - m_videoData.segmentDuration, m_bOpt));
                }
            }
          else
            {
              if ((m_lastRepIndex == m_highestRepIndex)
                  || (nextHighestRepBitrate >= m_a5 * averageSegmentThroughput))
                {
                  delayDecision = 3;
                  bDelay = (int64_t)(std::max (bufferNow - m_videoData.segmentDuration, m_bOpt));
                }
              else
                {
                  decisionCase = 6;
                  nextRepIndex = m_lastRepIndex + 1;
                }
            }
        }
    }

  if (segmentCounter != 0 && delayDecision != 0)
    {
      if (bDelay > bufferNow)
        {
          bDelay = 0;
        }
      else
        {
          bDelay = bufferNow - bDelay;
        }
    }
  m_lastRepIndex = nextRepIndex;
  algorithmReply answer;
  answer.nextRepIndex = nextRepIndex;
  answer.nextDownloadDelay = bDelay;
  answer.decisionTime = timeNow;
  answer.decisionCase = decisionCase;
  answer.delayDecisionCase = delayDecision;
  return answer;
}

bool
TobascoAlgorithm::MinimumBufferLevelObserved ()
{
  if (m_throughput.transmissionEnd.size () < 2)
    {
      return true;
    }
  int64_t lastPackage = m_throughput.transmissionEnd.end ()[-1];
  int64_t secondToLastPackage = m_throughput.transmissionEnd.end ()[-2];

  if (m_deltaBeta < m_videoData.segmentDuration)
    {
      if (lastPackage - secondToLastPackage < m_deltaBeta)
        {
          return true;
        }
      else
        {
          return false;
        }
    }
  else
    {
      if (lastPackage - secondToLastPackage < m_videoData.segmentDuration)
        {
          return true;
        }
      else
        {
          return false;
        }
    }
}

double
TobascoAlgorithm::AverageSegmentThroughput (int64_t t_1, int64_t t_2)
{
  if (t_1 < 0)
    {
      t_1 = 0;
    }
  if (m_throughput.transmissionEnd.size () < 1)
    {
      return 0;
    }


  // First, we have to find the index of the start of the download of the first downloaded segment in
  // the interval [t_1, t_2]
  uint index = 0;
  for (uint i = 0; i <= m_throughput.transmissionEnd.size () - 1; i++)
    {
      if (m_throughput.transmissionEnd.at (i) < t_1)
        {
          continue;
        }
      else
        {
          index = i;
          break;
        }
    }

  double lengthOfInterval;
  double sumThroughput = 0.0;
  double transmissionTime = 0.0;
  if (m_throughput.transmissionRequested.at (index) < t_1)
    {
      lengthOfInterval = m_throughput.transmissionEnd.at (index) - t_1;
      sumThroughput += (m_videoData.averageBitrate.at (m_playbackData.playbackIndex.at (index)) * ((m_throughput.transmissionEnd.at (index) - t_1)
                                                                                                   / (m_throughput.transmissionEnd.at (index) - m_throughput.transmissionRequested.at (index)))) * lengthOfInterval;
      transmissionTime += lengthOfInterval;
      index++;
      if (index >= m_throughput.transmissionEnd.size ())
        {
          return (sumThroughput / (double)transmissionTime);
        }
    }
  // Compute the average download-time of all the fully completed segment downloads during [t_1, t_2].
  while (m_throughput.transmissionEnd.at (index) <= t_2)
    {
      lengthOfInterval = m_throughput.transmissionEnd.at (index) - m_throughput.transmissionRequested.at (index);
      sumThroughput += ((m_videoData.averageBitrate.at (m_playbackData.playbackIndex.at (index)) * m_videoData.segmentDuration)
                        / lengthOfInterval)  * lengthOfInterval;
      transmissionTime += lengthOfInterval;
      index++;
      if (index > m_throughput.transmissionEnd.size () - 1)
        {
          break;
        }
    }
  return (sumThroughput / (double)transmissionTime);

}
} // namespace ns3

