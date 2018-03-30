
#include "CognitiveRadioServer.h"

using namespace ns3;

CognitiveRadioServer::CognitiveRadioServer()
        : m_socket(0),
          m_peer(),
          m_sendEvent(),
          myNode(NULL),
          m_running(false)
{

}

CognitiveRadioServer::~CognitiveRadioServer()
{
    m_socket = 0;
}

void
CognitiveRadioServer::Setup(Ptr<Socket> socket, Address address, Ptr<Node> myNode) {
    this->m_socket = socket;
    this->m_peer = address;
    this->myNode = myNode;
}

void
CognitiveRadioServer::StartApplication(void) {
    m_running = true;
    m_socket->Bind();
    m_socket->Connect(m_peer);
    //SendPacket ();
}

void
CognitiveRadioServer::StopApplication(void) {
    m_running = false;

    if (m_sendEvent.IsRunning()) {
        Simulator::Cancel(m_sendEvent);
    }

    if (m_socket) {
        m_socket->Close();
    }
}

void
CognitiveRadioServer::SendPacket(Time now, Time delay) {
    /*
    LteSpectrumPhy::State a;

    Ptr<NetDevice> net_dev = this->myNode->GetDevice(0);
    Ptr<LteUeNetDevice> lte_ue_net_dev = net_dev->GetObject<LteUeNetDevice>();
    Ptr<LteUePhy> lte_ue_phy = lte_ue_net_dev->GetPhy();

    Ptr<LteSpectrumPhy> uplink, downlink;
    uplink = lte_ue_phy->GetUlSpectrumPhy();
    downlink = lte_ue_phy->GetDlSpectrumPhy();
    */
    std::stringstream msg;
    /*
    msg << downlink->GetState();
    msg << uplink->GetState();
     */
    //msg << channel_state;
    msg << now;
    msg << delay;
    Ptr<Packet> packet = Create<Packet>((const uint8_t *) msg.str().c_str(), msg.str().size());
    m_socket->Send(packet);
    //ScheduleTx ();
}

void
CognitiveRadioServer::ScheduleTx(void) {
    if (m_running) {
        Time tNext(Seconds(0.1));
        //m_sendEvent = Simulator::Schedule (tNext, &CognitiveRadioServer::SendPacket, this);
    }
}
