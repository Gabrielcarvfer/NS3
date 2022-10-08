//
// Created by gabriel on 29/09/22.
//

#ifndef NS3_E2AP_H
#define NS3_E2AP_H

#include "PubSubInfra.h"
#include "ns3/system-wall-clock-timestamp.h"

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

struct PeriodicReportStruct
{
  uint32_t period_ms;
  EventId eventId;
  std::string subscriberEndpoint;
  SystemWallClockTimestamp collectionStartTime;
  std::vector<uint32_t> measurementTimeOffset{};  // Time offset in ms since the measurements started
  std::vector<double> measurementValues{}; // Measured value
};

struct PeriodicMeasurementStruct
{
  std::string timestamp; // Timestamp from start of measurements
  std::vector<uint32_t> measurementTimeOffset{};  // Time offset in ms since the measurements started
  std::vector<double> measurementValues{}; // Measured value
};

class E2AP : public PubSubInfra
{
public:
  E2AP () : PubSubInfra ("E2Node"){};
  ~E2AP (){};
  void HandlePayload (std::string endpoint, Json payload);
  void RegisterEndpoint(std::string endpoint);
  void UpdateEndpoint(std::string old_endpoint, std::string new_endpoint);
  void RemoveEndpoint(std::string endpoint);
  void SubscribeToEndpoint (std::string endpoint);
  void SubscribeToEndpointPeriodic (std::string endpoint, uint32_t periodicity_ms);
  void UnsubscribeToEndpoint (std::string endpoint);
//private:
  void SendPayload(Json payload);
  void PeriodicReport(std::string subscriber_endpoint, uint32_t period_ms, std::string subscribed_endpoint);
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
