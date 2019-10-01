#ifndef JSON_TRAFFIC_INJECTOR_APPLICATION_H
#define JSON_TRAFFIC_INJECTOR_APPLICATION_H

#include "ns3/core-module.h"
#include "ns3/applications-module.h"

class JsonTrafficInjectorApplication : public ns3::Application
{
public:

    JsonTrafficInjectorApplication ();
  ~JsonTrafficInjectorApplication() override ;

  void Setup (const ns3::Ptr<ns3::Socket> &socket, const ns3::Address &address, uint16_t port, uint32_t packetSize, uint32_t nPackets, std::vector<float> &timeToSend);
  void Start();
private:
  void StartApplication () override;
  void StopApplication () override ;


  void ScheduleTx ();
  void SendPacket ();

  std::vector<float> m_timeToSend;
  ns3::Ptr<ns3::Socket>     m_socket;
  ns3::Address         m_peer;
  uint16_t m_peer_port;
  uint32_t        m_packetSize;
  uint32_t        m_nPackets;
  ns3::EventId         m_sendEvent;
  bool            m_running;
  uint32_t        m_packetsSent;
  uint8_t         m_currentTime;
};

#endif //JSON_TRAFFIC_INJECTOR_APPLICATION_H