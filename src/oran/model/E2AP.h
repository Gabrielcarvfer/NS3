//
// Created by gabriel on 29/09/22.
//

#ifndef NS3_E2AP_H
#define NS3_E2AP_H

#include "E2SM-KPM-measurements.h"
#include "ORAN-message-types.h"
#include "PubSubInfra.h"

#include "ns3/lte-enb-rrc.h"
#include "ns3/system-wall-clock-timestamp.h"

#include <optional>

/**
 * \file
 * \ingroup oran
 * ns3:E2AP declaration.
 */

namespace ns3
{

// O-RAN WG3 E2SM KPM v02.00.03
/**
 * \ingroup oran
 *
 * \brief Enumeration of event trigger formats
 */
enum RIC_EVENT_TRIGGER_FORMATS
{
    EVENT_TRIGGER_PERIODIC = 1 // Period field is given in milliseconds
};

/**
 * \ingroup oran
 *
 * \brief Enumeration of E2 Service Models (E2SM)
 */
enum E2_SERVICE_MODELS
{
    E2SM_RC = 1,
    E2SM_KPM,
    E2SM_NI
};

/**
 * \ingroup oran
 *
 * \brief Implementation of the E2AP (E2 Node Application Protocol).
 *
 * This class implements the packaging/unpackaging of E2SM (E2 Node Service Models),
 * routing the different service/message types to the appropriate E2SM handler,
 * plus publisher/subscriber relationships between usual E2 Nodes (eNB, gNB) and the
 * E2T (E2 Termination, which is part of the RIC).
 */
class E2AP : public PubSubInfra
{
  public:
    /**
     * \brief Creates the E2AP object, which is an specialization of the PubSubInfra object
     */
    E2AP()
        : PubSubInfra("E2Node"),
          m_rrc(nullptr){};
    ~E2AP() override{};
    /**
     * \brief Handle an incoming json payload sent from src_endpoint to dest_endpoint.
     * \param [in] src_endpoint The source endpoint.
     * \param [in] dest_endpoint The destination endpoint.
     * \param [in] payload Json object with the payload to be handled.
     */
    void HandlePayload(std::string src_endpoint, std::string dest_endpoint, Json payload) override;
    /**
     * \brief Register a service endpoint to the E2AP object.
     * \param [in] endpoint The service endpoint (e.g. /E2Node/id/service).
     */
    void RegisterEndpoint(std::string endpoint) override;
    /**
     * \brief Update a service endpoint to the E2AP object.
     * \param [in] old_endpoint The service endpoint (e.g. /E2Node/id/old_service_endpoint).
     * \param [in] new_endpoint The service endpoint (e.g. /E2Node/id/new_service_endpoint).
     */
    void UpdateEndpoint(std::string old_endpoint, std::string new_endpoint);
    /**
     * \brief Remove a service endpoint of the E2AP object.
     * \param [in] endpoint The service endpoint (e.g. /E2Node/id/service_endpoint_to_remove).
     */
    void RemoveEndpoint(std::string endpoint) override;
    /**
     * \brief Subscribe E2AP to multicasts from a given endpoint
     * \param [in] endpoint The service endpoint being subscribed.
     */
    void SubscribeToEndpoint(std::string endpoint) override;
    /**
     * \brief Subscribe E2AP to multicasts from a given endpoint with
     * a interval trigger with a given periodicity
     * \param [in] endpoint The service endpoint being subscribed.
     * \param [in] periodicity_ms The periodicity to receive the
     * multicasts from the subscribed endpoint.
     */
    void SubscribeToEndpointPeriodic(std::string endpoint, uint32_t periodicity_ms);
    /**
     * \brief Unsubscribe E2AP from a given service endpoint.
     * \param [in] endpoint The service endpoint being unsubscribed.
     */
    void UnsubscribeToEndpoint(std::string endpoint);
    /**
     * \brief Publish json payload to all subscribers of a given endpoint
     * \param [in] endpoint The service endpoint being broadcasted to.
     * \param [in] json The payload to broadcast to subscribers.
     */
    void PublishToEndpointSubscribers(std::string endpoint, Json json) override;
    // Default endpoints for KPM measurement and control
    /**
     * \brief Register endpoints for all KPMs collected.
     */
    void RegisterDefaultEndpoints();
    /**
     * \brief Subscribe to all KPM endpoints of a target E2AP.
     *        Used by the RIC to collect KPM of E2 nodes.
     * \param [in] e2NodeToSubscribeTo The E2Node to be subscribed to.
     */
    void SubscribeToDefaultEndpoints(const E2AP& e2NodeToSubscribeTo);
    /**
     * \brief Get pointer to RRC from the respective E2Node.
     * \return Pointer to LteEnbRrc.
     */
    Ptr<LteEnbRrc> GetRrc();

    /**
     * \brief Query KPM storage for metric
     * \param metric KPM metric to retrieve
     * \return map addressed by E2 Node endpoints with a measurements deque as value
     */
    const std::map<std::string, std::deque<PeriodicMeasurementStruct>> QueryKpmMetric(
        std::string metric) const;

  private:
    /**
     * \brief Send a Json payload.
     * \param [in] payload Json payload with a destination address in DEST_ENDPOINT.
     */
    void SendPayload(Json payload);
    /**
     * \brief Periodically report to subscribers of the endpoint.
     * \param [in] subscriber_endpoint The subscribed endpoint.
     * \param [in] period_ms Report periodicity.
     * \param [in] subscribed_endpoint The subscriber endpoint.
     */
    void PeriodicReport(std::string subscriber_endpoint,
                        uint32_t period_ms,
                        std::string subscribed_endpoint);
    /**
     * \brief Handle indication payloads (routes to the different E2SM handlers)
     * \param [in] src_endpoint The source endpoint.
     * \param [in] dest_endpoint The destination endpoint.
     * \param [in] payload The indication payload.
     */
    void HandleIndicationPayload(std::string& src_endpoint,
                                 std::string& dest_endpoint,
                                 Json& payload);
    /**
     * \brief Handle RAN-Control E2 Service Model (E2SM-RC) indication
     *        payloads (routes to the different E2SM handlers)
     * \param [in] src_endpoint The source endpoint.
     * \param [in] dest_endpoint The destination endpoint.
     * \param [in] payload The indication payload.
     */
    void HandleE2SmRcIndicationPayload(std::string& src_endpoint,
                                       std::string& dest_endpoint,
                                       Json& payload);
    /**
     * \brief Handle RAN-Control E2 Service Model (E2SM-RC) control request
     *        payloads (routes to the different E2SM handlers)
     * \param [in] src_endpoint The source endpoint.
     * \param [in] dest_endpoint The destination endpoint.
     * \param [in] payload The control request payload.
     */
    void HandleE2SmRcControlRequest(std::string& src_endpoint,
                                    std::string& dest_endpoint,
                                    Json& payload);
    /**
     * \brief Handle Key Performance Metrics E2 Service Model (E2SM-KPM) indication
     *        payloads (routes to the different E2SM handlers)
     * \param [in] src_endpoint The source endpoint.
     * \param [in] dest_endpoint The destination endpoint.
     * \param [in] payload The indication payload.
     */
    void HandleE2SmKpmIndicationPayload(std::string& src_endpoint,
                                        std::string& dest_endpoint,
                                        Json& payload);
    // temporarily
  public:
    /**
     * \brief Send handover order to the target E2Node
     * \param [in] rnti The UE identifier.
     * \param [in] targetCell The destination E2 Node that will receive the handed UE.
     *                        Set to std::numeric_limits<uint16_t>::max() to reject the handover.
     * \param [in] destination_endpoint The endpoint of the E2 Node performing the handover.
     * \param [in] xAppDelayNs The real-world delay of an xApp decision making.
     */
    void E2SmRcSendHandoverControl(uint16_t rnti,
                                   uint16_t targetCell,
                                   std::string& destination_endpoint,
                                   double xAppDelayNs);
    /**
     * \brief Request the confirmation to a handover of an UE to a given target cell.
     *        The RIC can deny that request or reform the target cell decision.
     * \param [in] rnti The UE identifier.
     * \param [in] targetCell The destination E2 Node that will receive the handed UE
     * \param [in] src_endpoint The endpoint of the E2 Node requesting the handover.
     */
    void E2SmRcSendHandoverControlRequest(uint16_t rnti,
                                          uint16_t targetCell,
                                          std::string src_endpoint = "");

  private:
    /**
     * \brief Short-term storage of subscribed messages sent after
     * their specified periodicity has passed
     */
    std::map<std::string, PeriodicReportStruct> m_endpointPeriodicityAndBuffer;
    /**
     * \brief Long-term storage for KPMs (key of the first map) received
     *       of a given endpoint (key of the second map)
     */
    std::map<std::string, std::map<std::string, std::deque<PeriodicMeasurementStruct>>>
        m_kpmToEndpointStorage;
    /**
     * \brief Short-term storage of pending requests per endpoint and rnti.
     *        Used to control which requests can timeout.
     */
    std::map<std::string, std::map<uint16_t, Json>> m_pendingRequestsPerRnti;
    /**
     * \brief Pointer to the E2Node RRC. Used to forward control orders.
     */
    Ptr<LteEnbRrc> m_rrc;

  public:
    /**
     * \brief Send a E2SM RC Handover Control order
     * \param [in] rnti UE to handover.
     * \param [in] cellId destination cell ID.
     * \param [in] rrc RRC of the source cell ID.
     * \return optional return (empty means no response, value indicates the target cell ID decided
     * by the RIC)
     */
    std::optional<uint16_t> E2SmRcHandoverControl(uint16_t rnti, uint16_t cellId, LteEnbRrc& rrc);
};

// O-RAN WG3 E2SM RC v01.02 7.3.1
/**
 * \ingroup oran
 *
 * \brief Enumeration of event trigger definition styles
 */
enum RIC_EVENT_TRIGGER_DEFINITION_STYLES
{
    MESSAGE_EVENT = 1,
    CALL_PROCESS_BREAKPOINT,
    E2_NODE_INFORMATION_CHANGE,
    UE_INFORMATION_CHANGE,
    ON_DEMAND
};

} // namespace ns3
#endif // NS3_E2AP_H
