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

#ifndef FESTIVE_ALGORITHM_H
#define FESTIVE_ALGORITHM_H

#include "tcp-stream-adaptation-algorithm.h"

namespace ns3 {

/**
 * \ingroup tcpStream
 * \brief Implementation of the Festive adaptation algorithm
 */
class FestiveAlgorithm : public AdaptationAlgorithm
{
public:
  FestiveAlgorithm (  const videoData &videoData,
                      const playbackData & playbackData,
                      const bufferData & bufferData,
                      const throughputData & throughput);

  algorithmReply GetNextRep (const int64_t segmentCounter, int64_t clientId);

private:
  const int64_t m_targetBuf;
  const int64_t m_delta;
  const double m_alpha;
  const int64_t m_highestRepIndex;
  const double m_thrptThrsh;
  std::vector<int> m_smooth;
};

} // namespace ns3
#endif /* FESTIVE_ALGORITHM_H */