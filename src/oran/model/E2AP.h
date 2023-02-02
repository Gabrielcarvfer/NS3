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

namespace ns3
{

// O-RAN WG3 E2SM KPM v02.00.03
enum RIC_EVENT_TRIGGER_FORMATS
{
    EVENT_TRIGGER_PERIODIC = 1 // Period field is given in milliseconds
};

enum E2_SERVICE_MODELS
{
    E2SM_RC = 1,
    E2SM_KPM,
    E2SM_NI
};

class E2AP : public PubSubInfra
{
  public:
    E2AP()
        : PubSubInfra("E2Node"),
          m_rrc(nullptr){};
    ~E2AP() override{};
    void HandlePayload(std::string src_endpoint, std::string dest_endpoint, Json payload) override;
    void RegisterEndpoint(std::string endpoint) override;
    void UpdateEndpoint(std::string old_endpoint, std::string new_endpoint);
    void RemoveEndpoint(std::string endpoint) override;
    void SubscribeToEndpoint(std::string endpoint) override;
    void SubscribeToEndpointPeriodic(std::string endpoint, uint32_t periodicity_ms);
    void UnsubscribeToEndpoint(std::string endpoint);
    void PublishToSubEndpointSubscribers(std::string endpoint, Json json);
    void PublishToEndpointSubscribers(std::string complete_endpoint, Json json) override;
    // Default endpoints for KPM measurement and control
    void RegisterDefaultEndpoints();
    void SubscribeToDefaultEndpoints(const E2AP& e2NodeToSubscribeTo);
    Ptr<LteEnbRrc> GetRrc();
    // private:
    void SendPayload(Json payload);
    void PeriodicReport(std::string subscriber_endpoint,
                        uint32_t period_ms,
                        std::string subscribed_endpoint);
    void HandleIndicationPayload(std::string& src_endpoint,
                                 std::string& dest_endpoint,
                                 Json& payload);
    void HandleE2SmRcIndicationPayload(std::string& src_endpoint,
                                       std::string& dest_endpoint,
                                       Json& payload);
    void HandleE2SmRcControlRequest(std::string& src_endpoint,
                                    std::string& dest_endpoint,
                                    Json& payload);
    void HandleE2SmKpmIndicationPayload(std::string& src_endpoint,
                                        std::string& dest_endpoint,
                                        Json& payload);
    void E2SmRcSendHandoverControl(uint16_t rnti,
                                   uint16_t targetCell,
                                   std::string& destination_endpoint,
                                   double xAppDelayNs);
    void E2SmRcSendHandoverControlRequest(uint16_t rnti,
                                          uint16_t targetCell,
                                          std::string src_endpoint = "");
    std::map<std::string, PeriodicReportStruct> m_endpointPeriodicityAndBuffer;
    std::map<std::string, std::map<std::string, std::deque<PeriodicMeasurementStruct>>>
        m_kpmToEndpointStorage;
    std::map<std::string, std::map<uint16_t, Json>> m_pendingRequestsPerRnti;
    Ptr<LteEnbRrc> m_rrc;

  public:
    std::optional<uint16_t> E2SmRcHandoverControl(uint16_t rnti, uint16_t cellId, LteEnbRrc& rrc);
};

// O-RAN WG3 E2SM RC v01.02 7.3.1
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
