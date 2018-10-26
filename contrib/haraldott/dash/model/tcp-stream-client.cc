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
#include "ns3/log.h"
#include "ns3/ipv4-address.h"
#include "ns3/ipv6-address.h"
#include "ns3/nstime.h"
#include "ns3/inet-socket-address.h"
#include "ns3/inet6-socket-address.h"
#include "ns3/socket.h"
#include "ns3/simulator.h"
#include "ns3/socket-factory.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"
#include "ns3/trace-source-accessor.h"
#include "tcp-stream-client.h"
#include <math.h>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>
#include "ns3/global-value.h"
#include <ns3/core-module.h>
#include "tcp-stream-server.h"
#include <unistd.h>
#include <iterator>
#include <numeric>
#include <iomanip>
#include <ctime>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstring>
#include <errno.h>

namespace ns3 {

template <typename T>
std::string ToString (T val)
{
  std::stringstream stream;
  stream << val;
  return stream.str ();
}

NS_LOG_COMPONENT_DEFINE ("TcpStreamClientApplication");

NS_OBJECT_ENSURE_REGISTERED (TcpStreamClient);

void
TcpStreamClient::Controller (controllerEvent event)
{
  NS_LOG_FUNCTION (this);
  if (state == initial)
    {
      RequestRepIndex ();
      state = downloading;
      Send (m_videoData.segmentSize.at (m_currentRepIndex).at (m_segmentCounter));
      return;
    }

  if (state == downloading)
    {
      PlaybackHandle ();
      if (m_currentPlaybackIndex <= m_lastSegmentIndex)
        {
          /*  e_d  */
          m_segmentCounter++;
          RequestRepIndex ();
          state = downloadingPlaying;
          Send (m_videoData.segmentSize.at (m_currentRepIndex).at (m_segmentCounter));
        }
      else
        {
          /*  e_df  */
          state = playing;
        }
      controllerEvent ev = playbackFinished;
      // std::cerr << "Client " << m_clientId << " " << Simulator::Now ().GetSeconds () << "\n";
      Simulator::Schedule (MicroSeconds (m_videoData.segmentDuration), &TcpStreamClient::Controller, this, ev);
      return;
    }


  else if (state == downloadingPlaying)
    {
      if (event == downloadFinished)
        {
          if (m_segmentCounter < m_lastSegmentIndex)
            {
              m_segmentCounter++;
              RequestRepIndex ();
            }

          if (m_bDelay > 0 && m_segmentCounter <= m_lastSegmentIndex)
            {
              /*  e_dirs */
              state = playing;
              controllerEvent ev = irdFinished;
              Simulator::Schedule (MicroSeconds (m_bDelay), &TcpStreamClient::Controller, this, ev);
            }
          else if (m_segmentCounter == m_lastSegmentIndex)
            {
              /*  e_df  */
              state = playing;
            }
          else
            {
              /*  e_d  */
              Send (m_videoData.segmentSize.at (m_currentRepIndex).at (m_segmentCounter));
            }
        }
      else if (event == playbackFinished)
        {
          if (!PlaybackHandle ())
            {
              /*  e_pb  */
              controllerEvent ev = playbackFinished;
              // std::cerr << "FIRST CASE. Client " << m_clientId << " " << Simulator::Now ().GetSeconds () << "\n";
              Simulator::Schedule (MicroSeconds (m_videoData.segmentDuration), &TcpStreamClient::Controller, this, ev);
            }
          else
            {
              /*  e_pu  */
              state = downloading;
            }
        }
      return;
    }


  else if (state == playing)
    {
      if (event == irdFinished)
        {
          /*  e_irc  */
          state = downloadingPlaying;
          Send (m_videoData.segmentSize.at (m_currentRepIndex).at (m_segmentCounter));
        }
      else if (event == playbackFinished && m_currentPlaybackIndex < m_lastSegmentIndex)
        {
          /*  e_pb  */
          // std::cerr << "SECOND CASE. Client " << m_clientId << " " << Simulator::Now ().GetSeconds () << "\n";
          PlaybackHandle ();
          controllerEvent ev = playbackFinished;
          Simulator::Schedule (MicroSeconds (m_videoData.segmentDuration), &TcpStreamClient::Controller, this, ev);
        }
      else if (event == playbackFinished && m_currentPlaybackIndex == m_lastSegmentIndex)
        {
          PlaybackHandle ();
          /*  e_pf  */
          state = terminal;
          StopApplication ();
        }
      return;
    }
}

TypeId
TcpStreamClient::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::TcpStreamClient")
    .SetParent<Application> ()
    .SetGroupName ("Applications")
    .AddConstructor<TcpStreamClient> ()
    .AddAttribute ("RemoteAddress",
                   "The destination Address of the outbound packets",
                   AddressValue (),
                   MakeAddressAccessor (&TcpStreamClient::m_peerAddress),
                   MakeAddressChecker ())
    .AddAttribute ("RemotePort",
                   "The destination port of the outbound packets",
                   UintegerValue (0),
                   MakeUintegerAccessor (&TcpStreamClient::m_peerPort),
                   MakeUintegerChecker<uint16_t> ())
    .AddAttribute ("SegmentDuration",
                   "The duration of a segment in nanoseconds",
                   UintegerValue (2000000),
                   MakeUintegerAccessor (&TcpStreamClient::m_segmentDuration),
                   MakeUintegerChecker<uint64_t> ())
    .AddAttribute ("SegmentSizeFilePath",
                   "The relative path (from ns-3.x directory) to the file containing the segment sizes in bytes",
                   StringValue ("bitrates.txt"),
                   MakeStringAccessor (&TcpStreamClient::m_segmentSizeFilePath),
                   MakeStringChecker ())
    .AddAttribute ("SimulationId",
                   "The ID of the current simulation, for logging purposes",
                   UintegerValue (0),
                   MakeUintegerAccessor (&TcpStreamClient::m_simulationId),
                   MakeUintegerChecker<uint32_t> ())
    .AddAttribute ("NumberOfClients",
                   "The total number of clients for this simulation, for logging purposes",
                   UintegerValue (1),
                   MakeUintegerAccessor (&TcpStreamClient::m_numberOfClients),
                   MakeUintegerChecker<uint16_t> ())
    .AddAttribute ("ClientId",
                   "The ID of the this client object, for logging purposes",
                   UintegerValue (0),
                   MakeUintegerAccessor (&TcpStreamClient::m_clientId),
                   MakeUintegerChecker<uint32_t> ())
  ;
  return tid;
}

TcpStreamClient::TcpStreamClient ()
{
  NS_LOG_FUNCTION (this);
  m_socket = 0;
  m_data = 0;
  m_dataSize = 0;
  state = initial;

  m_currentRepIndex = 0;
  m_segmentCounter = 0;
  m_bDelay = 0;
  m_bytesReceived = 0;
  m_segmentsInBuffer = 0;
  m_bufferUnderrun = false;
  m_currentPlaybackIndex = 0;

}

void
TcpStreamClient::Initialise (std::string algorithm, uint16_t clientId)
{
  NS_LOG_FUNCTION (this);

  m_videoData.segmentDuration = m_segmentDuration;
  if (ReadInBitrateValues (ToString (m_segmentSizeFilePath)) == -1)
    {
      NS_LOG_ERROR ("Opening test bitrate file failed. Terminating.\n");
      Simulator::Stop ();
      Simulator::Destroy ();
    }

  m_lastSegmentIndex = (int64_t) m_videoData.segmentSize.at (0).size () - 1;
  m_highestRepIndex = m_videoData.averageBitrate.size () - 1;
  if (algorithm == "tobasco")
    {
      algo = new TobascoAlgorithm (m_videoData, m_playbackData, m_bufferData, m_throughput);
    }
  else if (algorithm == "panda")
    {
      algo = new PandaAlgorithm (m_videoData, m_playbackData, m_bufferData, m_throughput);
    }
  else if (algorithm == "festive")
    {
      algo = new FestiveAlgorithm (m_videoData, m_playbackData, m_bufferData, m_throughput);
    }
  else
    {
      NS_LOG_ERROR ("Invalid algorithm name entered. Terminating.");
      StopApplication ();
      Simulator::Stop ();
      Simulator::Destroy ();
    }

  m_algoName = algorithm;

  InitializeLogFiles (ToString (m_simulationId), ToString (m_clientId), ToString (m_numberOfClients));

}

TcpStreamClient::~TcpStreamClient ()
{
  NS_LOG_FUNCTION (this);
  m_socket = 0;

  delete algo;
  algo = NULL;
  delete [] m_data;
  m_data = 0;
  m_dataSize = 0;
}

void
TcpStreamClient::RequestRepIndex ()
{
  NS_LOG_FUNCTION (this);
  algorithmReply answer;

  answer = algo->GetNextRep ( m_segmentCounter, m_clientId );
  m_currentRepIndex = answer.nextRepIndex;
  NS_ASSERT_MSG (answer.nextRepIndex <= m_highestRepIndex, "The algorithm returned a representation index that's higher than the maximum");

  m_playbackData.playbackIndex.push_back (answer.nextRepIndex);
  m_bDelay = answer.nextDownloadDelay;
  // std::cerr << m_segmentCounter << "\n";
  LogAdaptation (answer);
}

template <typename T>
void
TcpStreamClient::Send (T & message)
{
  NS_LOG_FUNCTION (this);
  PreparePacket (message);
  Ptr<Packet> p;
  p = Create<Packet> (m_data, m_dataSize);
  m_downloadRequestSent = Simulator::Now ().GetMicroSeconds ();
  m_socket->Send (p);
}

void
TcpStreamClient::HandleRead (Ptr<Socket> socket)
{
  NS_LOG_FUNCTION (this << socket);
  Ptr<Packet> packet;
  if (m_bytesReceived == 0)
    {
      m_transmissionStartReceivingSegment = Simulator::Now ().GetMicroSeconds ();
    }
  uint32_t packetSize;
  while ( (packet = socket->Recv ()) )
    {
      packetSize = packet->GetSize ();
      LogThroughput (packetSize);
      m_bytesReceived += packetSize;
      if (m_bytesReceived == m_videoData.segmentSize.at (m_currentRepIndex).at (m_segmentCounter))
        {
          SegmentReceivedHandle ();
        }
    }
}

int
TcpStreamClient::ReadInBitrateValues (std::string segmentSizeFile)
{
  NS_LOG_FUNCTION (this);
  std::ifstream myfile;
  myfile.open (segmentSizeFile.c_str ());
  if (!myfile)
    {
      return -1;
    }
  std::string temp;
  int64_t averageByteSizeTemp = 0;
  while (std::getline (myfile, temp))
    {
      if (temp.empty ())
        {
          break;
        }
      std::istringstream buffer (temp);
      std::vector<int64_t> line ((std::istream_iterator<int64_t> (buffer)),
                                 std::istream_iterator<int64_t>());
      m_videoData.segmentSize.push_back (line);
      averageByteSizeTemp = (int64_t) std::accumulate ( line.begin (), line.end (), 0.0) / line.size ();
      m_videoData.averageBitrate.push_back ((8.0 * averageByteSizeTemp) / (m_videoData.segmentDuration / 1000000.0));
    }
  NS_ASSERT_MSG (!m_videoData.segmentSize.empty (), "No segment sizes read from file.");
  return 1;
}

void
TcpStreamClient::SegmentReceivedHandle ()
{
  NS_LOG_FUNCTION (this);
  m_transmissionEndReceivingSegment = Simulator::Now ().GetMicroSeconds ();


  m_bufferData.timeNow.push_back (m_transmissionEndReceivingSegment);
  if (m_segmentCounter > 0)
    { //if a buffer underrun is encountered, the old buffer level will be set to 0, because the buffer can not be negative
      m_bufferData.bufferLevelOld.push_back (std::max (m_bufferData.bufferLevelNew.back () -
                                                       (m_transmissionEndReceivingSegment - m_throughput.transmissionEnd.back ()), (int64_t)0));
    }
  else //first segment
    {
      m_bufferData.bufferLevelOld.push_back (0);
    }
  m_bufferData.bufferLevelNew.push_back (m_bufferData.bufferLevelOld.back () + m_videoData.segmentDuration);

  m_throughput.bytesReceived.push_back (m_videoData.segmentSize.at (m_currentRepIndex).at (m_segmentCounter));
  m_throughput.transmissionStart.push_back (m_transmissionStartReceivingSegment);
  m_throughput.transmissionRequested.push_back (m_downloadRequestSent);
  m_throughput.transmissionEnd.push_back (m_transmissionEndReceivingSegment);

  LogDownload ();

  LogBuffer ();

  m_segmentsInBuffer++;
  m_bytesReceived = 0;
  if (m_segmentCounter == m_lastSegmentIndex)
    {
      m_bDelay = 0;
    }

  controllerEvent event = downloadFinished;
  Controller (event);

}

bool
TcpStreamClient::PlaybackHandle ()
{
  NS_LOG_FUNCTION (this);
  int64_t timeNow = Simulator::Now ().GetMicroSeconds ();
  // if we got called and there are no segments left in the buffer, there is a buffer underrun
  if (m_segmentsInBuffer == 0 && m_currentPlaybackIndex < m_lastSegmentIndex && !m_bufferUnderrun)
    {
      m_bufferUnderrun = true;
      bufferUnderrunLog << std::setfill (' ') << std::setw (26) << timeNow / (double)1000000 << " ";
      bufferUnderrunLog.flush ();
      return true;
    }
  else if (m_segmentsInBuffer > 0)
    {
      if (m_bufferUnderrun)
        {
          m_bufferUnderrun = false;
          bufferUnderrunLog << std::setfill (' ') << std::setw (13) << timeNow / (double)1000000 << "\n";
          bufferUnderrunLog.flush ();
        }
      m_playbackData.playbackStart.push_back (timeNow);
      LogPlayback ();
      m_segmentsInBuffer--;
      m_currentPlaybackIndex++;
      return false;
    }

  return true;
}

void
TcpStreamClient::SetRemote (Address ip, uint16_t port)
{
  NS_LOG_FUNCTION (this << ip << port);
  m_peerAddress = ip;
  m_peerPort = port;
}

void
TcpStreamClient::SetRemote (Ipv4Address ip, uint16_t port)
{
  NS_LOG_FUNCTION (this << ip << port);
  m_peerAddress = Address (ip);
  m_peerPort = port;
}

void
TcpStreamClient::SetRemote (Ipv6Address ip, uint16_t port)
{
  NS_LOG_FUNCTION (this << ip << port);
  m_peerAddress = Address (ip);
  m_peerPort = port;
}

void
TcpStreamClient::DoDispose (void)
{
  NS_LOG_FUNCTION (this);
  Application::DoDispose ();
}

void
TcpStreamClient::StartApplication (void)
{
  NS_LOG_FUNCTION (this);
  if (m_socket == 0)
    {
      TypeId tid = TypeId::LookupByName ("ns3::TcpSocketFactory");
      m_socket = Socket::CreateSocket (GetNode (), tid);
      if (Ipv4Address::IsMatchingType (m_peerAddress) == true)
        {
          m_socket->Connect (InetSocketAddress (Ipv4Address::ConvertFrom (m_peerAddress), m_peerPort));
        }
      else if (Ipv6Address::IsMatchingType (m_peerAddress) == true)
        {
          m_socket->Connect (Inet6SocketAddress (Ipv6Address::ConvertFrom (m_peerAddress), m_peerPort));
        }
      m_socket->SetConnectCallback (
        MakeCallback (&TcpStreamClient::ConnectionSucceeded, this),
        MakeCallback (&TcpStreamClient::ConnectionFailed, this));
      m_socket->SetRecvCallback (MakeCallback (&TcpStreamClient::HandleRead, this));
    }
}

void
TcpStreamClient::StopApplication ()
{
  NS_LOG_FUNCTION (this);

  if (m_socket != 0)
    {
      m_socket->Close ();
      m_socket->SetRecvCallback (MakeNullCallback<void, Ptr<Socket> > ());
      m_socket = 0;
    }
  downloadLog.close ();
  playbackLog.close ();
  adaptationLog.close ();
  bufferLog.close ();
  throughputLog.close ();
  bufferUnderrunLog.close ();
}


template <typename T>
void
TcpStreamClient::PreparePacket (T & message)
{
  NS_LOG_FUNCTION (this << message);
  std::ostringstream ss;
  ss << message;
  ss.str ();
  uint32_t dataSize = ss.str ().size () + 1;

  if (dataSize != m_dataSize)
    {
      delete [] m_data;
      m_data = new uint8_t [dataSize];
      m_dataSize = dataSize;
    }
  memcpy (m_data, ss.str ().c_str (), dataSize);
}

void
TcpStreamClient::ConnectionSucceeded (Ptr<Socket> socket)
{
  NS_LOG_FUNCTION (this << socket);
  NS_LOG_LOGIC ("Tcp Stream Client connection succeeded");
  controllerEvent event = init;
  Controller (event);
}

void
TcpStreamClient::ConnectionFailed (Ptr<Socket> socket)
{
  NS_LOG_FUNCTION (this << socket);
  NS_LOG_LOGIC ("Tcp Stream Client connection failed");
}

void
TcpStreamClient::LogThroughput (uint32_t packetSize)
{
  NS_LOG_FUNCTION (this);
  throughputLog << std::setfill (' ') << std::setw (13) << Simulator::Now ().GetMicroSeconds ()  / (double) 1000000 << " "
                << std::setfill (' ') << std::setw (13) << packetSize << "\n";
  throughputLog.flush ();
}

void
TcpStreamClient::LogDownload ()
{
  NS_LOG_FUNCTION (this);
  downloadLog << std::setfill (' ') << std::setw (13) << m_segmentCounter << " "
              << std::setfill (' ') << std::setw (21) << m_downloadRequestSent / (double)1000000 << " "
              << std::setfill (' ') << std::setw (14) << m_transmissionStartReceivingSegment / (double)1000000 << " "
              << std::setfill (' ') << std::setw (12) << m_transmissionEndReceivingSegment / (double)1000000 << " "
              << std::setfill (' ') << std::setw (12) << m_videoData.segmentSize.at (m_currentRepIndex).at (m_segmentCounter) << " "
              << std::setfill (' ') << std::setw (12) << "Y\n";
  downloadLog.flush ();
}

void
TcpStreamClient::LogBuffer ()
{
  NS_LOG_FUNCTION (this);
  bufferLog << std::setfill (' ') << std::setw (13) << m_transmissionEndReceivingSegment / (double)1000000 << " "
            << std::setfill (' ') << std::setw (13) << m_bufferData.bufferLevelOld.back () / (double)1000000 << "\n"
            << std::setfill (' ') << std::setw (13) << m_transmissionEndReceivingSegment / (double)1000000 << " "
            << std::setfill (' ') << std::setw (13) << m_bufferData.bufferLevelNew.back () / (double)1000000 << "\n";
  bufferLog.flush ();
}

void
TcpStreamClient::LogAdaptation (algorithmReply answer)
{
  NS_LOG_FUNCTION (this);
  adaptationLog << std::setfill (' ') << std::setw (13) << m_segmentCounter << " "
                << std::setfill (' ') << std::setw (9) << m_currentRepIndex << " "
                << std::setfill (' ') << std::setw (22) << answer.decisionTime / (double)1000000 << " "
                << std::setfill (' ') << std::setw (4) << answer.decisionCase << " "
                << std::setfill (' ') << std::setw (9) << answer.delayDecisionCase << "\n";
  adaptationLog.flush ();
}

void
TcpStreamClient::LogPlayback ()
{
  NS_LOG_FUNCTION (this);
  playbackLog << std::setfill (' ') << std::setw (13) << m_currentPlaybackIndex << " "
              << std::setfill (' ') << std::setw (14) << Simulator::Now ().GetMicroSeconds ()  / (double)1000000 << " "
              << std::setfill (' ') << std::setw (13) << m_playbackData.playbackIndex.at (m_currentPlaybackIndex) << "\n";
  playbackLog.flush ();
}

void
TcpStreamClient::InitializeLogFiles (std::string simulationId, std::string clientId, std::string numberOfClients)
{
  NS_LOG_FUNCTION (this);

  std::string dLog = "mylogs/" + m_algoName + "/" +  numberOfClients  + "/sim" + simulationId + "_" + "cl" + clientId + "_"  + "downloadLog.txt";
  downloadLog.open (dLog.c_str ());
  downloadLog << "Segment_Index Download_Request_Sent Download_Start Download_End Segment_Size Download_OK\n";
  downloadLog.flush ();

  std::string pLog = "mylogs/" + m_algoName + "/" +  numberOfClients  + "/sim" + simulationId + "_" + "cl" + clientId + "_"  + "playbackLog.txt";
  playbackLog.open (pLog.c_str ());
  playbackLog << "Segment_Index Playback_Start Quality_Level\n";
  playbackLog.flush ();

  std::string aLog = "mylogs/" + m_algoName + "/" +  numberOfClients  + "/sim" + simulationId + "_" + "cl" + clientId + "_"  + "adaptationLog.txt";
  adaptationLog.open (aLog.c_str ());
  adaptationLog << "Segment_Index Rep_Level Decision_Point_Of_Time Case DelayCase\n";
  adaptationLog.flush ();

  std::string bLog = "mylogs/" + m_algoName + "/" +  numberOfClients  + "/sim" + simulationId + "_" + "cl" + clientId + "_"  + "bufferLog.txt";
  bufferLog.open (bLog.c_str ());
  bufferLog << "     Time_Now  Buffer_Level \n";
  bufferLog.flush ();

  std::string tLog = "mylogs/" + m_algoName + "/" +  numberOfClients  + "/sim" + simulationId + "_" + "cl" + clientId + "_"  + "throughputLog.txt";
  throughputLog.open (tLog.c_str ());
  throughputLog << "     Time_Now Bytes Received \n";
  throughputLog.flush ();

  std::string buLog = "mylogs/" + m_algoName + "/" +  numberOfClients  + "/sim" + simulationId + "_" + "cl" + clientId + "_"  + "bufferUnderrunLog.txt";
  bufferUnderrunLog.open (buLog.c_str ());
  bufferUnderrunLog << ("Buffer_Underrun_Started_At         Until \n");
  bufferUnderrunLog.flush ();
}

} // Namespace ns3
