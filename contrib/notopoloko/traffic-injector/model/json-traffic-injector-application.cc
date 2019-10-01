#include "json-traffic-injector-application.h"

using namespace ns3;

JsonTrafficInjectorApplication::JsonTrafficInjectorApplication ()
  : m_socket (nullptr),
    m_peer (), 
    m_packetSize (0), 
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
JsonTrafficInjectorApplication::Setup (const ns3::Ptr<ns3::Socket> &socket, const ns3::Address &address, uint16_t port, uint32_t packetSize, uint32_t nPackets, std::vector<float> &timeToSend)
{
  m_socket = socket;
  m_peer = address;
  m_peer_port = port;
  m_packetSize = packetSize;
  m_nPackets = nPackets;
  m_timeToSend = timeToSend;
  m_currentTime = 0;
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
  int a = m_socket->Bind ();
    Ipv4Address ipv4 = Ipv4Address::ConvertFrom (m_peer);
    InetSocketAddress inetSocket = InetSocketAddress (ipv4,
                                                      m_peer_port);
  int b = m_socket->Connect (inetSocket);

  if (a == -1 || b == -1){
    std::cout << "Unable to Connect";
    return;
  }

  SendPacket ();
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
  ns3::Ptr<ns3::Packet> packet = ns3::Create<ns3::Packet> (m_packetSize);
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
    ns3::Time tNext (ns3::Minutes (m_timeToSend.at(m_currentTime)));
    m_currentTime++;
    m_sendEvent = ns3::Simulator::Schedule (tNext, &JsonTrafficInjectorApplication::SendPacket, this);
  }
  if (m_currentTime == m_timeToSend.size())
  {
    NS_LOG_UNCOND( std::string("End of transmission at: ") << ns3::Simulator::Now ().GetSeconds ());
    StopApplication();
  }
  

}