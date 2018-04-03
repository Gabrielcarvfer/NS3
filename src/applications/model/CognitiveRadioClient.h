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

    /*
     * \brief A Cognitive Radio Client. Sends a packet containing when channel starts to be occupied, the delay and the duration of transmission
     */
//Início da aplicação customizada simples
    class CognitiveRadioClient : public Application
    {
        public:
            /*
             * \brief Get the Type ID
             * \return Object Type ID
             */
            static TypeId GetTypeId(void);

            /*
             * \brief Empty constructor
             */
            CognitiveRadioClient();

            /*
             * \brief Destructor
             */
            virtual ~CognitiveRadioClient();

            /*
             *  \brief Used to initialize variables of an instance
             */
            void Setup(Ptr<Socket> socket, Address address, Ptr<Node> myNode);

            /*
             * \brief Sends the packet
             */
            void SendPacket(Time now, Time delay, Time duration);

        private:
            virtual void StartApplication(void);

            virtual void StopApplication(void);

            void ScheduleTx(void);

            Ptr<Socket> m_socket; // Socket
            Address m_peer; // Peer Address
            EventId m_sendEvent; // Event to send the next packet
            Ptr<Node> myNode; //Node which uses the app, not used for now as we have it's address
            bool m_running; //Is running?
    };



}
#endif //NS3_CUSTOMAPP_H
