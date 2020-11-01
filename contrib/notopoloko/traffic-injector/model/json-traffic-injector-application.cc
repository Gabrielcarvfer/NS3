#include "json-traffic-injector-application.h"


JsonTrafficInjectorApplication::JsonTrafficInjectorApplication ()
  : m_socket (nullptr),
    m_peer (), 
    m_packetSizes (0),
    m_nPackets (0), 
    m_sendEvent (), 
    m_running (false), 
    m_packetsSent (0),
    m_currentTime (0)
{
}

JsonTrafficInjectorApplication::~JsonTrafficInjectorApplication()
{
  m_socket = nullptr;
}

void
JsonTrafficInjectorApplication::Setup (const ns3::Address &address,
                                       uint16_t port,
                                       std::vector<uint16_t> packetSizes,
                                       uint32_t nPackets,
                                       std::vector<float> &timeToSend)
{
  m_peer = address;
  m_peer_port = port;
  m_packetSizes = packetSizes;
  m_nPackets = nPackets;
  m_timeToSend = timeToSend;
  m_currentTime = 0;
  m_currentPacketSize = 0;
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
      ns3::TypeId tid = ns3::TypeId::LookupByName ("ns3::TcpSocketFactory");
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

  if (m_sendEvent.IsRunning ())
    {
      ns3::Simulator::Cancel (m_sendEvent);
    }

  if (m_socket)
    {
      m_socket->Close ();
    }
}

void 
JsonTrafficInjectorApplication::SendPacket ()
{
  ns3::Ptr<ns3::Packet> packet = ns3::Create<ns3::Packet> (m_packetSizes.at(m_currentPacketSize));
  m_currentPacketSize = (m_currentPacketSize+1) % m_packetSizes.size();
  m_socket->Send (packet);

  if (++m_packetsSent < m_nPackets)
    {
      ScheduleTx ();
    }
}

void 
JsonTrafficInjectorApplication::ScheduleTx ()
{
  if (m_running)
  {
    // Time tNext (Seconds (m_packetSize * 8 / static_cast<double> (m_dataRate.GetBitRate ())));
    // std::cout << "Scheduling next message to: " << m_timeToSend.at(m_currentTime) << std::endl;
    ns3::Time tNext (ns3::Seconds (m_timeToSend.at(m_currentTime)));
    m_currentTime++;
    m_sendEvent = ns3::Simulator::Schedule (tNext, &JsonTrafficInjectorApplication::SendPacket, this);
  }

  //Repeats undefinitely
  if (m_currentTime == m_timeToSend.size())
  {
      m_currentTime = 0;
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