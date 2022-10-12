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

enum MeasurementType
{
    INTEGER,
    REAL,
    NONE
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
    std::vector<MeasurementStruct> measurements; // Measured value
};
void to_json(Json& j, const PeriodicMeasurementStruct& p) {
    std::vector<Json> measurementsJson;
    for (auto& measurement: p.measurements)
    {
        Json measurementJson;
        to_json(measurementJson, measurement);
        measurementsJson.push_back(measurementJson);
    }
    j = Json{ {"timestamp", p.timestamp}, {"measurements", measurementsJson}};
}
void from_json(const Json& j, PeriodicMeasurementStruct& p)
{
    j.at("timestamp").get_to(p.timestamp);
    std::vector<Json> measurementsJson;
    j.at("measurements").get_to(measurementsJson);
    for (auto& measurementJson: measurementsJson)
    {
        MeasurementStruct measurement;
        from_json(measurementJson, measurement);
        p.measurements.push_back(measurement);
    }
}

struct PeriodicReportStruct
{
  uint32_t period_ms;
  EventId eventId;
  std::string subscriberEndpoint;
  SystemWallClockTimestamp collectionStartTime;
  std::vector<PeriodicMeasurementStruct> measurements;
};

enum FeatureImplemented
{
    NOTIMPLEMENTED = 0,
    IMPLEMENTED
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

  // Default endpoints for KPM measurement and control
  void RegisterDefaultEndpoints();
  void SubscribeToDefaultEndpoints(const E2AP& e2NodeToSubscribeTo);
//private:
  void SendPayload(Json payload);
  void PeriodicReport(std::string subscriber_endpoint, uint32_t period_ms, std::string subscribed_endpoint);
  std::map<std::string, PeriodicReportStruct> m_endpointPeriodicityAndBuffer;
  std::map<std::string, std::map<std::string, std::deque<PeriodicMeasurementStruct>>> m_kpmToEndpointStorage;
   const std::map<std::string, std::tuple<enum MeasurementType, std::string, enum FeatureImplemented>> m_defaultEndpointsKpmTypeAndUnit = {
      // Measurements defined in ORAN WG3 E2SM KPM v02.02
      {"DRB.PdcpSduVolumeDL_Filter", {INTEGER, "Mbit", NOTIMPLEMENTED}},
      {"DRB.PdcpSduVolumeUL_Filter", {INTEGER, "Mbit", NOTIMPLEMENTED}},
      {"QosFlow.PdcpPduVolumeDL_Filter", {INTEGER, "Mbit", NOTIMPLEMENTED}},
      {"QosFlow.PdcpPduVolumeUL_Filter", {INTEGER, "Mbit", NOTIMPLEMENTED}},
      {"QosFlow.PdcpSduVolumeDL_Filter", {INTEGER, "Mbit", NOTIMPLEMENTED}},
      {"QosFlow.PdcpSduVolumeUL_Filter", {INTEGER, "Mbit", NOTIMPLEMENTED}},
      {"DRB.PdcpSduVolumeX2DL_Filter", {INTEGER, "Mbit", NOTIMPLEMENTED}},
      {"DRB.PdcpSduVolumeX2UL_Filter", {INTEGER, "Mbit", NOTIMPLEMENTED}},
      {"DRB.F1uPdcpSduVolumeDL.Qos", {INTEGER, "Mbit", NOTIMPLEMENTED}},
      {"DRB.X2uPdcpSduVolumeDL.Qos", {INTEGER, "Mbit", NOTIMPLEMENTED}},
      {"DRB.F1uPdcpSduVolumeUL.Qos", {INTEGER, "Mbit", NOTIMPLEMENTED}},
      {"DRB.X2uPdcpSduVolumeUL.Qos", {INTEGER, "Mbit", NOTIMPLEMENTED}},
      {"QF.SessionTimeUE", {INTEGER, "s", NOTIMPLEMENTED}},
      {"QF.SessionTimeUE.Qos", {INTEGER, "s", NOTIMPLEMENTED}},
      {"QF.SessionTimeUE", {INTEGER, "s", NOTIMPLEMENTED}},
      {"QF.SessionTimeUE", {INTEGER, "s", NOTIMPLEMENTED}},
      {"ERAB.SessionTimeUE", {INTEGER, "s", NOTIMPLEMENTED}},
      {"ERAB.SessionTimeQCI.QCI", {INTEGER, "s", NOTIMPLEMENTED}},
      {"DRB.IPThpUL.QCI", {REAL, "Kbit", NOTIMPLEMENTED}},
      // NR
      {"DRB.PdcpSduVolumeXnDL_Filter", {INTEGER, "Mbit", NOTIMPLEMENTED}},
      {"DRB.PdcpSduVolumeXnUL_Filter", {INTEGER, "Mbit", NOTIMPLEMENTED}},
      {"DRB.XnuPdcpSduVolumeDL.Qos", {INTEGER, "Mbit", NOTIMPLEMENTED}},
      {"DRB.XnuPdcpSduVolumeUL.Qos", {INTEGER, "Mbit", NOTIMPLEMENTED}},
      {"QF.SessionTimeUE.5QI", {INTEGER, "s", NOTIMPLEMENTED}},
      {"QF.SessionTimeUE.SNSSAI", {INTEGER, "s", NOTIMPLEMENTED}},

      // Measurements defined in 3GPP TS 32.425 version 14.1.0 Release 14
      // 4.1-
      // Act = Active
      // Alloc = Allocation
      // AOA = Angle of arrival
      // Att = Attempt
      // Conn = Connection
      // Ded = Dedicated
      // EE = Energy Efficiency
      // Err = Error
      // Estab = Establish(ment)
      // Fail = Fail(ed/ure)
      // Ho = Handover
      // Inc = Incoming
      // Out = Outgoing
      // Nbr = Number
      // Prep = Prepar(e/ation)
      // Succ = Success

      // 4 Measurements related to eNodeB, donor eNodeB and relay node
      // 4.1 RRC Connection Related Measurements
      // 4.1.1 RRC Connection Establishment
      {"RRC.ConnEstabAtt.Cause", {INTEGER, "", NOTIMPLEMENTED}},
      {"RRC.ConnEstabSucc.Cause", {INTEGER, "", NOTIMPLEMENTED}},
      {"RRC.ConnEstabFail.Cause", {INTEGER, "", NOTIMPLEMENTED}},
      {"RRC.ConnEstabFaileNBCause.Congestion", {INTEGER, "", NOTIMPLEMENTED}},
      {"RRC.ConnEstabFaileNBCause.Unspecified", {INTEGER, "", NOTIMPLEMENTED}},
      {"RRC.ConnEstabFaileNBCause.EnergySaving", {INTEGER, "", NOTIMPLEMENTED}},
      // 4.1.2 RRC Connection Re-Establishment
      {"RRC.ConnReEstabAtt.Cause", {INTEGER, "", NOTIMPLEMENTED}},
      {"RRC.ConnReEstabSucc.Cause", {INTEGER, "", NOTIMPLEMENTED}},
      {"RRC.ConnReEstabFail.Cause", {INTEGER, "", NOTIMPLEMENTED}},
      // 4.1.3 RRC Connection Number
      {"RRC.ConnMean", {INTEGER, "", NOTIMPLEMENTED}},
      {"RRC.ConnMax", {INTEGER, "", NOTIMPLEMENTED}},
      // 4.1.4 RRC Connection Setup Time
      {"RRC.ConnEstabTimeMean.Cause", {INTEGER, "", NOTIMPLEMENTED}},
      {"RRC.ConnEstabTimeMax.Cause", {INTEGER, "", NOTIMPLEMENTED}},
      // 4.1.5 UE Context Release
      {"UECNTX.RelReq.Cause", {INTEGER, "", NOTIMPLEMENTED}},
      {"UECNTX.RelSuccNbr", {INTEGER, "", NOTIMPLEMENTED}},
      {"RRCConn.Setup.TimeBin", {INTEGER, "", NOTIMPLEMENTED}},
      // 4.2 E-RAB Measurements
      // 4.2.1 E-RAB Setup
      {"ERAB.EstabInitAttNbr.QCI", {INTEGER, "", NOTIMPLEMENTED}},
      {"ERAB.EstabInitSuccNbr.QCI", {INTEGER, "", NOTIMPLEMENTED}},
      {"ERAB.EstabInitFailNbr.Cause", {INTEGER, "", NOTIMPLEMENTED}},
      {"ERAB.EstabAddAttNbr.QCI", {INTEGER, "", NOTIMPLEMENTED}},
      {"ERAB.EstabAddSuccNbr.QCI", {INTEGER, "", NOTIMPLEMENTED}},
      {"ERAB.EstabAddFailNbr.Cause", {INTEGER, "", NOTIMPLEMENTED}},
      {"ERAB.EstabTimeMean.QCI", {INTEGER, "", NOTIMPLEMENTED}},
      {"ERAB.EstabTimeMax.QCI", {INTEGER, "", NOTIMPLEMENTED}},
      {"ERAB.EstabIncHoAttNbr.QCI", {INTEGER, "", NOTIMPLEMENTED}},
      {"ERAB.EstabIncHoSuccNbr.QCI", {INTEGER, "", NOTIMPLEMENTED}},
      // 4.2.2 E-RAB Release
      {"ERAB.RelEnbNbr.QCI", {INTEGER, "", NOTIMPLEMENTED}},
      {"ERAB.RelEnbNbr.Cause", {INTEGER, "", NOTIMPLEMENTED}},
      {"ERAB.RelAttrNbr.QCI", {INTEGER, "", NOTIMPLEMENTED}},
      {"ERAB.RelSuccNbr.QCI", {INTEGER, "", NOTIMPLEMENTED}},
      {"ERAB.RelFailNbr.Cause", {INTEGER, "", NOTIMPLEMENTED}},
      {"ERAB.RelActNbr.QCI", {INTEGER, "", NOTIMPLEMENTED}},
      // 4.2.3 E-RAB Modification
      {"ERAB.ModQosAttNbr.QCI", {INTEGER, "", NOTIMPLEMENTED}},
      {"ERAB.ModQosSuccNbr.QCI", {INTEGER, "", NOTIMPLEMENTED}},
      {"ERAB.ModQosFailNbr.Cause", {INTEGER, "", NOTIMPLEMENTED}},
      // 4.2.4 E-RAB Activity
      // 4.2.5 E-RAB Number
      // 4.3 Handover Related Measurements
      // 4.3.1 Intra-RAT Handovers
      // 4.3.1.1 Intra-eNB/RN Handover Related Measurements
      // 4.3.1.2 Inter-eNB Handover Related Measurements
      // 4.3.1.3 Handover Measurements On Neighbour Cell Basis
      // 4.3.1.4 Intra/Inter-frequency Handover Related Measurements
      // 4.3.1.5 Handover Related Measurements for DRX/non-DRX
      // 4.3.1.6 Handover To Cells Outside The RN Related Measurements
      // 4.3.1.7 Handover Triggering Measurements
      // 4.3.2 Inter-RAT Handovers
      // 4.4 Cell Level Radio Bearer QoS Related Measurements
      // 4.4.1 Cell PDCP SDU Bit-rate
      // 4.4.2 Active UEs
      // 4.4.3 Packet Delay And Drop Rate
      // 4.4.4 Packet Loss Rate
      // 4.4.5 IP Latency Measurements
      // 4.4.6 IP Throughput Measurements
      // 4.4.7 PDCP Data Volume Measurements
      // 4.5 Radio Resource Utilization Related Measurements
      // 4.5.1 DL PRB Usage For Traffic
      // 4.5.2 UL PRB Usage For Traffic
      // 4.5.3 DL Total PRB Usage
      // 4.5.4 UL Total PRB Usage
      // 4.5.5 RACH Usage
      // 4.5.6 Cell Unavailable Time
      // 4.5.7 TB Related Measurements
      // 4.5.8 Power Utilization Measurements
      // 4.5.9 PRB Full Utilisation
      // 4.6 UE-associated Logical S1-Connection Related Measurements
      // 4.6.1 UE-associated Logical S1-Connection Establishment
      // 4.7 Paging Related Measurements
      // 4.7.1 Paging Performance
      // 4.8 Measurements Related To Equipment Resources
      // 4.8.1 eNodeB/RN processor usage
      // 4.9 Common LAs of overlapping RATs Coverage
      // 4.9.1 Number of Incoming IRAT Mobility Events per LA
      // 4.10 RF Measurements
      // 4.10.1 CQI Distribution
      // 4.10.1.1 Wideband CQI Distribution
      // 4.10.1.2 Average sub-band CQI
      // 4.10.2 Timing Advance Distribution
      // 4.11 SCell Scheduling Related Measurements in CA
      // 4.11.1 Attempted PUCCH Allocations For SCell Scheduling In Carrier Aggregation
      // 4.11.2 Successful PUCCH Allocations For SCell Scheduling In Carrier Aggregation
      // 4.11.3 Failed PUCCH Allocations for SCell Scheduling In Carrier Aggregation
      // 5 Measurements Related To Relay Node
      // 6 Measurements Related To Measurement Report
      // 6.1 RSRP Related Measurements
      // 6.2 RSRQ Related Measurements
      // 6.3 UE Power Headroom Related Measurements
      // 6.4 UE Rx-Tx Time Difference Related Measurements
      // 6.5 AOA Related Measurements

  };
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
