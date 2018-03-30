//
// Created by gabri on 26/03/2018.
//

#ifndef NS3_CUSTOMAPP_H
#define NS3_CUSTOMAPP_H

#include "ns3/address.h"
#include "ns3/application.h"
#include "ns3/event-id.h"
#include "ns3/ptr.h"
#include "ns3/traced-callback.h"

#include "ns3/socket.h"
#include "ns3/simulator.h"
#include "ns3/socket-factory.h"

namespace ns3 {

    class Address;
    class Socket;

//Início da aplicação customizada simples
    class CognitiveRadioClient : public Application
    {
        public:

            CognitiveRadioClient();

            virtual ~CognitiveRadioClient();

            void Setup(Ptr<Socket> socket, Address address, Ptr<Node> myNode);

            void SendPacket(Time now, Time delay);

        private:
            virtual void StartApplication(void);

            virtual void StopApplication(void);

            void ScheduleTx(void);

            Ptr<Socket> m_socket;
            Address m_peer;
            EventId m_sendEvent;
            Ptr<Node> myNode;
            bool m_running;
    };



}
#endif //NS3_CUSTOMAPP_H
