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

#ifndef TCP_STREAM_CLIENT_H
#define TCP_STREAM_CLIENT_H

#include "ns3/application.h"
#include "ns3/event-id.h"
#include "ns3/ptr.h"
#include "ns3/ipv4-address.h"
#include "ns3/traced-callback.h"
#include <iostream>
#include <fstream>
#include "tcp-stream-adaptation-algorithm.h"
#include "tcp-stream-interface.h"
#include "tobasco2.h"
#include "festive.h"
#include "panda.h"


namespace ns3 {

class Socket;
class Packet;

/**
 * \ingroup tcpStream
 * \brief A Tcp Stream client
 *
 * Every segment size request sent is returned by the server and received here.
 */
class TcpStreamClient : public Application
{

public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);
  TcpStreamClient ();
  virtual ~TcpStreamClient ();

  /**
   * \brief Set the adaptation algorithm which this client instance should use.
   *
   * A new adaptation algorithm object is created, by calling a constructor of an existing subclass of
   * AdaptationAlgorithm.
   *
   * \param algorithm the name of the algorithm to use for instantiating an adaptation algorithm object.
   */
  void Initialise (std::string algorithm, uint16_t clientId);

  /**
   * \brief Set the remote address and port
   * \param ip remote IPv4 address
   * \param port remote port
   */
  void SetRemote (Ipv4Address ip, uint16_t port);
  /**
   * \brief Set the remote address and port
   * \param ip remote IPv6 address
   * \param port remote port
   */
  void SetRemote (Ipv6Address ip, uint16_t port);
  /**
   * \brief Set the remote address and port
   * \param ip remote IP address
   * \param port remote port
   */
  void SetRemote (Address ip, uint16_t port);

protected:
  virtual void DoDispose (void);

private:
  /**
   * \brief This enum is used to define the states of the state machine which controls the behaviour of the client.
   */
  enum controllerState
  {
    initial, downloading, downloadingPlaying, playing, terminal
  };
  controllerState state;

  /**
   * \brief This enum is used to define the controller events of the state machine which controls the behaviour of the client.
   */
  enum controllerEvent
  {
    downloadFinished, playbackFinished, irdFinished, init
  };
  AdaptationAlgorithm *algo;

  virtual void StartApplication (void);
  virtual void StopApplication (void);

  /**
   * \brief Finite state machine controlling the client.
   *
   * When a client object is created, it is initiated as follows and finds itself in state initial:
   * - It creates an adaptation algorithm object of the kind specified for this particular simulation.
   * - The reduced version of the MPD, containing the duration of a segment in microseconds and a (n x m) matrix consisting of n representations and m segment sizes, denoted in bytes, is being read in from the file specified at program start.
   * - The log files are being initialised.
   *
   * After these initialisations, which take place at object creation, a TCP connection to the server is initiated and the callbacks for a succeeded connection and for receiving are set. Then, the controller does the transition initial init-> downloading by calling RequestRepIndex (), thus obtaining the next representation level to be downloaded. The client then requests the determined segment size from the server by sending it a string composed of the number of bytes of the segment. After the request is processed by the server, it starts sending the first TCP packet to the client. The receiving of a packet notifies the socket that new data is available to be read, so the aforementioned SetRcvCallback is triggered and the client stars receiving packets. Meanwhile all arrived packets are being logged. This is repeated until the received amount of data matches the requested segment size. Then, the throughput is logged and the receive function calls the controller with the event  downloadFinished.
   * The controller then adds a segment to the buffer and calls the PlaybackHandle() function. Here, the segment buffer is decremented by one segment, thus simulating the beginning of playback. Then, the function returns to the controller, where a timer of m_segmentDuration microseconds is set to call PlaybackHandle() again, after playback of the prior segment is finished. Next, the requests the next segment as described before. Therefore, the controller does the transition downloading downloadfinished-> downloadingPlaying.

   * Now being in state downloadingPlaying, the next possible transitions are
   * - downloadingPlaying downloadFinished-> downloadingPlaying: download of a segment is finished. The download of the next segment is started.
   * - downloadingPlaying playbackFinished-> downloadingPlaying: playback of a segment is finished. The controller calls PlaybackHandle(), which happens through the beforehand set timer; if the number of segments in the buffer is > 0, the segment buffer is decremented by 1, and the timer is set to call PlaybackHandle() in m_segmentDuration microseconds.
   * - downloadingPlaying downloadFinished-> playing: download of a segment is finished. The controller will request the next representation level from the adaptation algorithm. If m_bDelay > 0, the controller delays the download of the next segment by m_bDelay. Streaming session is now performing playback only.
   * - downloadingPlaying playbackFinished-> downloading: playback of a segment is finished. This event is triggered by the beforehand set timer. The controller calls PlaybackHandle(); if the number of segments in the buffer is == 0, a buffer underrun is logged.
   * - downloadingPlaying downloadFinished-> playing: download of the last segment is finished. Playback of the remaining segment(s) in the buffer continues. After finishing playback of all remaining segments in the buffer, playing playbackFinished-> terminal is performed, thus closing the client's socket, the streaming session for this client ends.
   * Assuming that a buffer underrun has just been encountered and the client is currently in state downloading, the client is currently busy downloading the next segment. After the segment is fully downloaded, the controller is notified, PlaybackHandle() is called, thus starting the playback of the just downloaded segment and the transition downloading downloadFinished-> downloadingPlaying is performed. If the just downloaded segment (after the buffer underrun) was the streaming session's last segment, downloading downloadFinished-> playing is performed, the last segment is played and playing playbackFinished-> terminal is performed, as explained before.
   */
  void Controller (controllerEvent action);
  /**
   * Set the data fill of the packet (what is actually sent as data to the server with m_data) to
   * the zero-terminated contents of the T & message string.
   *
   * \param message The amount of bytes the server shall send as a respond.
   */
  template <typename T>
  void PreparePacket (T & message);
  /**
   * \brief Send a packet to the server.
   *
   * Before a packet is sent, PreparePacket( T & message) is called to fill the packet with
   * a string, containig the number of bytes requested from the server.
   */
  template <typename T>
  void Send (T & message);
  /**
   * \brief Handle a packet reception.
   *
   * This function is called by lower layers, triggered by SetRecvCallback.
   * It increments m_bytesReceived by the number of bytes received and calls SegmentReceivedHandle()
   * when m_bytesReceived == size of segment that is expected to be received.
   *
   * \param socket the socket the packet was received to.
   */
  void HandleRead (Ptr<Socket> socket);
  /**
   * \brief triggered by SetConnectCallback if a connection to a host was established.
   */
  void ConnectionSucceeded (Ptr<Socket> socket);
  /**
   * \brief triggered by SetConnectCallback if a connection to a host could not be established.
   */
  void ConnectionFailed (Ptr<Socket> socket);
  /**
   * Called after a segment was completely received from the server, meaning that the received number
   * of bytes == the requested number of bytes. Throughput data and buffer data is logged.
   */
  void SegmentReceivedHandle ();
  /**
   * \brief Read in bitrate values
   *
   * The test bitrate values to be read must be provided in bytes in absolute sizes (not per second!)
   * as a 2x2 matrix, with spaces separating the segment sizes and newlines for every representation level.
   */
  int ReadInBitrateValues (std::string segmentSizeFile);
  /*
   * \brief Controls / simulates playback process
   *
   * Gets called by a timer, when the simulated playback of a segment is finished.
   * If m_segmentsInBuffer > 0, then m_segmentsInBuffer is decremented and m_currentPlaybackIndex
   * is incremented. Also, if there was a buffer underrun before, m_bufferUnderrun is set to false
   * and the end of a buffer underrun is logged. If m_segmentsInBuffer == 0, a buffer underrun is
   * registered by writing the event in the bufferUnderrun logfile and m_bufferUnderrun is set to true.
   *
   * \return true if there is a buffer underrun
   */
  bool PlaybackHandle ();
  /*
   * \brief Request the next representation index from algorithm.
   *
   * The client requests the next representation index by calling algo->GetNextRep (int64_t m_segmentCounter), which is the interface between an adaptation algorithm
   * and a client, specifying the current segment index as an argument.
   * The algorithm returns an algorithmReply struct, the received values are stored in local variables for logging purposes.
   */
  void RequestRepIndex ();
  /*
   * \brief Log segment download information
   *
   * - segment index
   * - point in time when download request was sent to server
   * - point in time when transmission started, i.e. arrival of first packet of the whole segment
   * - point in time when transmission ended, i.e. arrival of last packet of the whole segment
   * - size of current segment in bits
   * - confirmation if segment was downloaded, Y for yes, N for no
   */
  void LogDownload ();
  /*
   * \brief Log buffer level
   *
   * Logging the arrival time of fully downloaded segment and logging the buffer level by
   * adding m_segmentDuration on the buffer level.
   *
   * - point in time when segment fully downloaded
   * - buffer level before segment is added to buffer
   * - point in time when segment fully downloaded
   * - buffer level after segment is added to buffer
   */
  void LogBuffer ();
  /*
   * \brief Log throughput information about single arriving TCP packets
   *
   * - arrival time of packet
   * - size of packet
   */
  void LogThroughput (uint32_t packetSize);
  /*
   * \brief Log information about playback process
   *
   * - index of segment of which playback will start next
   * - point in time when playback of above mentioned segment starts
   */
  void LogPlayback ();
  /*
   * \brief Log information about adaptation algorithm.
   *
   * - current segment index
   * - the point in time when the decision in the algorithm was made which representation to download next
   * - the case in which the decision was made which representation to download next
   * - the case in which the decision was made if the next download should be delayed
   * \param answer containing the answer the adaptation algorithm has provided.
   */
  void LogAdaptation (algorithmReply answer);
  /*
   * \brief Open log output files with streams.
   *
   * The output streams defined in TcpStreamClient are opened,
   * and log files containing the used adaptation algorithm are created for output.
   */
  void InitializeLogFiles (std::string simulationId, std::string clientId, std::string numberOfClients);

  uint32_t m_dataSize; //!< packet payload size
  uint8_t *m_data; //!< packet payload data

  Ptr<Socket> m_socket; //!< Socket
  Address m_peerAddress; //!< Remote peer address
  uint16_t m_peerPort; //!< Remote peer port

  uint16_t m_clientId; //!< The Id of this client, for logging purposes
  uint16_t m_simulationId; //!< The Id of this simulation, for logging purposes
  uint16_t m_numberOfClients; //!< The total number of clients for this simulation, for logging purposes
  std::string m_segmentSizeFilePath; //!< The relative path (from ns-3.x directory) to the file containing the segment sizes in bytes
  std::string m_algoName;//!< Name of the apation algorithm's class which this client will use for the simulation
  bool m_bufferUnderrun; //!< True if there is currently a buffer underrun in the simulated playback
  int64_t m_currentPlaybackIndex; //!< The index of the segment that is currently being played
  int64_t m_segmentsInBuffer; //!< The number of segments that are currently in the buffer
  int64_t m_currentRepIndex; //!< The index of the currently requested segment quality
  int64_t m_lastSegmentIndex;//!< The index of the last segment, i.e. the total number of segments-1
  int64_t m_segmentCounter; //!< The index of the next segment to be downloaded
  int64_t m_transmissionStartReceivingSegment; //!< The point in time in microseconds when the transmission of a segment begins
  int64_t m_transmissionEndReceivingSegment; //!< The point in time in microseconds when the transmission of a segment is finished
  int64_t m_bytesReceived; //!< Counts the amount of received bytes of the current packet
  int64_t m_bDelay;  //!< Minimum buffer level in microseconds of playback when the next download must be started
  int64_t m_highestRepIndex; //!< This is the index of the highest representation
  uint64_t m_segmentDuration; //!< The duration of a segment in microseconds

  std::ofstream adaptationLog; //!< Output stream for logging adaptation information
  std::ofstream downloadLog; //!< Output stream for logging download information
  std::ofstream playbackLog; //!< Output stream for logging playback information
  std::ofstream bufferLog; //!< Output stream for logging buffer course
  std::ofstream throughputLog; //!< Output stream for logging throughput information
  std::ofstream bufferUnderrunLog; //!< Output stream for logging starting and ending of buffer underruns

  uint64_t m_downloadRequestSent; //!< Logging the point in time in microseconds when a download request was sent to the server

  throughputData m_throughput; //!< Tracking the throughput
  bufferData m_bufferData; //!< Keep track of the buffer level
  playbackData m_playbackData; //!< Tracking the simulated playback of segments
  videoData m_videoData; //!< Information about segment sizes, average bitrates of representation levels and segment duration in microseconds

};

} // namespace ns3

#endif /* TCP_STREAM_CLIENT_H */
