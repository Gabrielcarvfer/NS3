#include "json-traffic-injector-application.h"


JsonTrafficInjectorApplication::JsonTrafficInjectorApplication ()
  : m_socket (),
    m_peer (), 
    m_packetSizes (0),
    m_nPackets (0), 
    m_sendEvent (), 
    m_running (false), 
    m_packetsSent (0),
    m_currentTime (0),
    m_tcp (false),
    m_portsToSpreadTraffic (1)
{
}

JsonTrafficInjectorApplication::~JsonTrafficInjectorApplication()
{
}

void
JsonTrafficInjectorApplication::Setup (const ns3::Address &address,
                                       uint16_t port,
                                       std::vector<uint32_t> packetSizes,
                                       std::vector<float> timeToSend,
                                       bool tcp,
                                       uint16_t portsToSpreadTraffic)
{
  m_peer = address;
  m_peer_port = port;
  m_packetSizes = packetSizes;
  m_timeToSend = timeToSend;
  m_currentTime = rand() % timeToSend.size();
  m_currentPacketSize = 0;
  m_tcp = tcp;
  m_portsToSpreadTraffic = portsToSpreadTraffic;
  m_currentPort = 0;
}
void
JsonTrafficInjectorApplication::Start()
{
    this->StartApplication();
}

void
JsonTrafficInjectorApplication::StartApplication ()
{
  m_running = true;
  m_packetsSent = 0;
  m_recvBack = 0;
  m_bytesRecvBack = 0;
  if (m_socket.empty())
  {
      ns3::TypeId tid;
      if (m_tcp)
        tid = ns3::TypeId::LookupByName ("ns3::TcpSocketFactory");
      else
        tid = ns3::TypeId::LookupByName ("ns3::UdpSocketFactory") ;

      for (uint16_t i = 0; i < m_portsToSpreadTraffic; i++)
      {

          m_socket.push_back(ns3::Socket::CreateSocket (GetNode (), tid));
          if (ns3::Ipv4Address::IsMatchingType(m_peer) == true)
          {
              m_socket[i]->Bind();
              m_socket[i]->Connect (ns3::InetSocketAddress (ns3::Ipv4Address::ConvertFrom(m_peer), m_peer_port+i));
          }
          else if (ns3::Ipv6Address::IsMatchingType(m_peer) == true)
          {
              m_socket[i]->Bind6();
              m_socket[i]->Connect (ns3::Inet6SocketAddress (ns3::Ipv6Address::ConvertFrom(m_peer), m_peer_port+i));
          }
          m_socket[i]->SetRecvCallback (ns3::MakeCallback (&JsonTrafficInjectorApplication::ReceivePacket, this));
      }
  }

  ScheduleTx ();
}

void 
JsonTrafficInjectorApplication::StopApplication ()
{
  m_running = false;
  if (m_sendEvent.IsRunning ())
  {
      ns3::Simulator::Cancel (m_sendEvent);
  }
  for (uint16_t i = 0; i < m_portsToSpreadTraffic; i++)
  {
      if (m_socket[i])
      {
          m_socket[i]->Close();
      }
  }
}

void 
JsonTrafficInjectorApplication::SendPacket (uint64_t packetSize)
{
  ns3::Ptr<ns3::Packet> packet = ns3::Create<ns3::Packet> (packetSize);
  m_socket[m_currentPort]->Send (packet);
  m_currentPort = (m_currentPort+1) % m_socket.size();
}

void 
JsonTrafficInjectorApplication::ScheduleTx ()
{
  if (!m_running)
      return;

  // Get time to transmit the next packet and packet size
  //std::cout << "Scheduling next message to: " << m_timeToSend.at(m_currentTime) << std::endl;
  ns3::Time tNext (ns3::Seconds (m_timeToSend.at(m_currentTime)));
  uint64_t packetSize = m_packetSizes.at(m_currentPacketSize);

  // If we have an UDP application, we need to fragment the packet to prevent issues
  if (!m_tcp)
  {
      const unsigned maxFragmentSizeBytes = 1400;
      uint16_t remBytes = packetSize % maxFragmentSizeBytes;
      unsigned nPackets = packetSize / maxFragmentSizeBytes;
      for (unsigned i = 0; i < nPackets; i++)
          ns3::Simulator::Schedule(tNext, &JsonTrafficInjectorApplication::SendPacket, this, maxFragmentSizeBytes);
      if (remBytes > 0)
          ns3::Simulator::Schedule(tNext, &JsonTrafficInjectorApplication::SendPacket, this, remBytes);
  }
  else
  {
      ns3::Simulator::Schedule(tNext, &JsonTrafficInjectorApplication::SendPacket, this, packetSize);
  }

  // Schedule next transmission event
  m_sendEvent = ns3::Simulator::Schedule(tNext, &JsonTrafficInjectorApplication::ScheduleTx, this);

  // Increment offsets
  m_currentTime++;
  m_currentPacketSize++;

  //Repeats undefinitely
  if (m_currentTime >= m_timeToSend.size())
  {
      m_currentTime = 0;
  }
  if (m_currentPacketSize >= m_packetSizes.size())
  {
      m_currentPacketSize = 0;
  }




  //todo:create a better way to stop
  //if (m_currentTime == m_timeToSend.size())
  //{
  //  NS_LOG_UNCOND( std::string("End of transmission at: ") << ns3::Simulator::Now ().GetSeconds ());
  //  StopApplication();
  //}
  

}

void
JsonTrafficInjectorApplication::ReceivePacket (ns3::Ptr<ns3::Socket> socket)
{
    ns3::Ptr<ns3::Packet> packet;
    ns3::Address from;
    while ((packet = socket->RecvFrom (from)))
    {
        // don't check if data returned is the same data sent earlier
        m_recvBack++;
        m_bytesRecvBack += packet->GetSize ();
    }

}