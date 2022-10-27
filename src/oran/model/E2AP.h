//
// Created by gabriel on 29/09/22.
//

#ifndef NS3_E2AP_H
#define NS3_E2AP_H

#include "PubSubInfra.h"
#include "ns3/system-wall-clock-timestamp.h"
#include "ORAN-3GPP-measurements.h"

namespace ns3 {

// O-RAN WG3 E2SM KPM v02.00.03
enum RIC_EVENT_TRIGGER_FORMATS
{
  EVENT_TRIGGER_PERIODIC = 1 // Period field is given in milliseconds
};

// O-RAN WG3 ES2M KPM v02.00.03
enum KPM_INDICATION_FORMATS
{
  KPM_INDICATION_FORMAT_1 = 1,
  KPM_INDICATION_FORMAT_2,
  KPM_INDICATION_FORMAT_3
};


union MeasurementUnion
{
    int64_t integer;
    double real;
    uint64_t uinteger;
    void * none;
};
struct MeasurementStruct
{
    enum MeasurementType type;
    uint32_t measurementTimeOffset;
    union MeasurementUnion measurement;
};
void to_json(Json& j, const MeasurementStruct& p) {
    j = Json{ {"type", p.type}, {"measurementTimeOffset", p.measurementTimeOffset}, {"measurement", p.measurement.uinteger} };
}
void from_json(const Json& j, MeasurementStruct& p) {
    j.at("type").get_to(p.type);
    j.at("measurementTimeOffset").get_to(p.measurementTimeOffset);
    j.at("measurement").get_to(p.measurement.uinteger);
}

struct PeriodicMeasurementStruct
{
    std::string timestamp; // Timestamp from start of measurements
    std::vector<Json> measurements; // Measured value
};
void to_json(Json& j, const PeriodicMeasurementStruct& p) {
    j = Json{ {"timestamp", p.timestamp}, {"measurements", p.measurements}};
}
void from_json(const Json& j, PeriodicMeasurementStruct& p)
{
    j.at("timestamp").get_to(p.timestamp);
    j.at("measurements").get_to(p.measurements);
}

struct PeriodicReportStruct
{
  uint32_t period_ms;
  EventId eventId;
  std::string subscriberEndpoint;
  SystemWallClockTimestamp collectionStartTime;
  std::vector<PeriodicMeasurementStruct> measurements;
};




class E2AP : public PubSubInfra
{
public:
  E2AP () : PubSubInfra ("E2Node"){};
  ~E2AP (){};
  void HandlePayload (std::string src_endpoint, std::string dest_endpoint, Json payload);
  void RegisterEndpoint(std::string endpoint);
  void UpdateEndpoint(std::string old_endpoint, std::string new_endpoint);
  void RemoveEndpoint(std::string endpoint);
  void SubscribeToEndpoint (std::string endpoint);
  void SubscribeToEndpointPeriodic (std::string endpoint, uint32_t periodicity_ms);
  void UnsubscribeToEndpoint (std::string endpoint);
  void PublishToSubEndpointSubscribers(std::string endpoint, Json json);
  void PublishToEndpointSubscribers(std::string complete_endpoint, Json json);
  // Default endpoints for KPM measurement and control
  void RegisterDefaultEndpoints();
  void SubscribeToDefaultEndpoints(const E2AP& e2NodeToSubscribeTo);
//private:
  void SendPayload(Json payload);
  void PeriodicReport(std::string subscriber_endpoint, uint32_t period_ms, std::string subscribed_endpoint);
  void HandleIndicationPayload(std::string& src_endpoint, std::string& dest_endpoint, Json& payload);
  std::map<std::string, PeriodicReportStruct> m_endpointPeriodicityAndBuffer;
  std::map<std::string, std::map<std::string, std::deque<PeriodicMeasurementStruct>>> m_kpmToEndpointStorage;
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

}
#endif //NS3_E2AP_H
