#include "json-traffic-injector-application.h"


JsonTrafficInjectorApplication::JsonTrafficInjectorApplication ()
  : m_socket (nullptr),
    m_peer (), 
    m_packetSizes (0),
    m_nPackets (0), 
    m_sendEvent (), 
    m_running (false), 
    m_packetsSent (0),
    m_currentTime (0),
    m_tcp (false)
{
}

JsonTrafficInjectorApplication::~JsonTrafficInjectorApplication()
{
  m_socket = nullptr;
}

void
JsonTrafficInjectorApplication::Setup (const ns3::Address &address,
                                       uint16_t port,
                                       std::vector<uint32_t> packetSizes,
                                       std::vector<float> timeToSend,
                                       bool tcp)
{
  m_peer = address;
  m_peer_port = port;
  m_packetSizes = packetSizes;
  m_timeToSend = timeToSend;
  m_currentTime = rand() % timeToSend.size();
  m_currentPacketSize = 0;
  m_tcp = tcp;
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
  if (m_socket == 0)
  {
      ns3::TypeId tid;
      if (m_tcp)
        tid = ns3::TypeId::LookupByName ("ns3::TcpSocketFactory");
      else
        tid = ns3::TypeId::LookupByName ("ns3::UdpSocketFactory") ;

      m_socket = ns3::Socket::CreateSocket (GetNode (), tid);
      if (ns3::Ipv4Address::IsMatchingType(m_peer) == true)
      {
          m_socket->Bind();
          m_socket->Connect (ns3::InetSocketAddress (ns3::Ipv4Address::ConvertFrom(m_peer), m_peer_port));
      }
      else if (ns3::Ipv6Address::IsMatchingType(m_peer) == true)
      {
          m_socket->Bind6();
          m_socket->Connect (ns3::Inet6SocketAddress (ns3::Ipv6Address::ConvertFrom(m_peer), m_peer_port));
      }
  }

  m_socket->SetRecvCallback (ns3::MakeCallback (&JsonTrafficInjectorApplication::ReceivePacket, this));

  ScheduleTx ();
}

void 
JsonTrafficInjectorApplication::StopApplication ()
{
  m_running = false;

    while (m_sendEvent.size() > 0)
    {
        ns3::EventId event = m_sendEvent.front();
        m_sendEvent.pop_front();
        if (event.IsRunning ())
        {
            ns3::Simulator::Cancel (event);
        }
    }

  if (m_socket)
    {
      m_socket->Close ();
    }
}

void 
JsonTrafficInjectorApplication::SendPacket (uint64_t packetSize)
{
  ns3::Ptr<ns3::Packet> packet = ns3::Create<ns3::Packet> (packetSize);
  m_socket->Send (packet);
  m_sendEvent.pop_front();
}

void 
JsonTrafficInjectorApplication::ScheduleTx ()
{
  if (m_running)
  {
    // Get time to transmit the next packet and packet size
    //std::cout << "Scheduling next message to: " << m_timeToSend.at(m_currentTime) << std::endl;
    ns3::Time tNext (ns3::Seconds (m_timeToSend.at(m_currentTime)));
    uint64_t packetSize = m_packetSizes.at(m_currentPacketSize);

    if (m_sendEvent.size()>0)
        m_sendEvent.pop_front();

    // If we have an UDP application, we need to fragment the packet to prevent issues
    if (!m_tcp)
    {
        unsigned maxFragmentSizeBytes = 64000;
        uint16_t remBytes = packetSize % maxFragmentSizeBytes;
        unsigned nPackets = packetSize / maxFragmentSizeBytes;
        for (unsigned i = 0; i < nPackets; i++)
            m_sendEvent.push_back(ns3::Simulator::Schedule(tNext, &JsonTrafficInjectorApplication::SendPacket, this, maxFragmentSizeBytes));

        if (remBytes > 0)
            m_sendEvent.push_back(ns3::Simulator::Schedule(tNext, &JsonTrafficInjectorApplication::SendPacket, this, remBytes));
    }
    else
    {
        m_sendEvent.push_back(ns3::Simulator::Schedule(tNext, &JsonTrafficInjectorApplication::SendPacket, this, packetSize));
    }

    // Schedule next transmission event
    m_sendEvent.push_back(ns3::Simulator::Schedule(tNext, &JsonTrafficInjectorApplication::ScheduleTx, this));

    // Increment offsets
    m_currentTime++;
    m_currentPacketSize++;
  }

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