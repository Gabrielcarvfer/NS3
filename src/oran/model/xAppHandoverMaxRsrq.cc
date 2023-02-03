#include "xAppHandoverMaxRsrq.h"

#include "ns3/E2AP.h"
#include "ns3/core-module.h"

#include <algorithm>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("xAppHandoverMaxRsrq");

xAppHandoverMaxRsrq::xAppHandoverMaxRsrq(bool initiateHandovers)
    : xAppHandover(),
      m_initiateHandovers(initiateHandovers)
{
    NS_LOG_FUNCTION(this);
    Config::Connect("/NodeList/*/DeviceList/*/LteEnbRrc/HandoverEndOk",
                    MakeCallback(&xAppHandoverMaxRsrq::HandoverSucceeded, this));
    Config::Connect("/NodeList/*/DeviceList/*/LteEnbRrc/ConnectionEstablished",
                    MakeCallback(&xAppHandoverMaxRsrq::ConnectionEstablished, this));
    if (m_initiateHandovers)
    {
        Simulator::Schedule(Seconds(1), &xAppHandoverMaxRsrq::PeriodicHandoverCheck, this);
    }
};

uint16_t
xAppHandoverMaxRsrq::ChooseTargetCellId(uint16_t rnti)
{
    NS_LOG_FUNCTION(this);

    E2AP* ric = (E2AP*)static_cast<const E2AP*>(E2AP::RetrieveInstanceWithEndpoint("/E2Node/0"));
    std::map<uint16_t, uint16_t> rntis;
    std::array<std::string, 4> kpmMetrics = {//"/KPM/HO.SrcCellQual.RSRP",
                                             "/KPM/HO.SrcCellQual.RSRQ",
                                             //"/KPM/HO.TrgtCellQual.RSRP",
                                             "/KPM/HO.TrgtCellQual.RSRQ"};

    std::map<uint16_t, double> rsrq_measurements;

    // Collate data into an armadillo matrix for processing
    for (auto kpmMetric : kpmMetrics)
    {
        auto metricMap = ric->QueryKpmMetric(kpmMetric);

        if (metricMap.size() == 0)
        {
            continue;
        }

        for (auto& e2nodeMeasurements : metricMap)
        {
            std::string mostRecentTimestamp("");
            for (auto& measurementDeque : e2nodeMeasurements.second)
            {
                if (mostRecentTimestamp == "")
                {
                    mostRecentTimestamp = measurementDeque.timestamp;
                }
                if (mostRecentTimestamp != measurementDeque.timestamp)
                {
                    // Skip old measurements
                    continue;
                }
                if (rnti != measurementDeque.measurements["RNTI"])
                {
                    // Skip rntis that do not match the requesting rnti
                    continue;
                }
                if (kpmMetric == "/KPM/HO.SrcCellQual.RSRQ")
                {
                    uint16_t cellId = measurementDeque.measurements["CELLID"];
                    cellId++;
                    if (rsrq_measurements.find(cellId) == rsrq_measurements.end())
                    {
                        rsrq_measurements[cellId] = measurementDeque.measurements["VALUE"];
                    }
                }
                else
                {
                    uint16_t cellId = measurementDeque.measurements["TARGET"];
                    if (rsrq_measurements.find(cellId) == rsrq_measurements.end())
                    {
                        rsrq_measurements[cellId] = measurementDeque.measurements["VALUE"];
                    }
                }
            }
        }
    }

    if (rsrq_measurements.size() == 0 || m_rntiInHandover.find(rnti) != m_rntiInHandover.end())
    {
        return std::numeric_limits<uint16_t>::max();
    }

    // Search max rsrp
    auto pos_maxrsrp = std::max_element(
        rsrq_measurements.begin(),
        rsrq_measurements.end(),
        [](const std::pair<uint16_t, double>& p1, const std::pair<uint16_t, double>& p2) {
            return p1.second < p2.second;
        });

    std::cout << "rnti: " << rnti << ", max: " << pos_maxrsrp->second
              << ", cellId: " << pos_maxrsrp->first << std::endl;
    return pos_maxrsrp->first;
}

void
xAppHandoverMaxRsrq::PeriodicHandoverCheck()
{
    NS_LOG_FUNCTION(this);

    E2AP* ric = (E2AP*)static_cast<const E2AP*>(xApp::RetrieveInstanceWithEndpoint("/E2Node/0"));

    // Command handovers
    for (auto [rnti, imsiAndConnectedCell] : m_rntiToImsiAndCellid)
    {
        // Skip UEs in handover
        if (m_rntiInHandover.find(rnti) != m_rntiInHandover.end())
            continue;

        // Choose new target cell id
        uint16_t newCellId = ChooseTargetCellId(rnti);

        // Skip rntis that are already in the target cell id
        if (newCellId == imsiAndConnectedCell.second ||
            newCellId == std::numeric_limits<uint16_t>::max())
            continue;

        // Spoof RIC CONTROL REQUEST with source eNB endpoint (where the UE is currently connected)
        std::string spoofed_src_endpoint =
            "/E2Node/" + std::to_string(imsiAndConnectedCell.second) + "/";
        ric->E2SmRcSendHandoverControlRequest(rnti, newCellId, spoofed_src_endpoint);
    }
    Simulator::Schedule(Seconds(1), &xAppHandoverMaxRsrq::PeriodicHandoverCheck, this);
}

void
xAppHandoverMaxRsrq::HandoverDecision(Json& payload)
{
    NS_LOG_FUNCTION(this);

    // Check if we are not receiving invalid payloads
    if (E2AP::RetrieveInstanceWithEndpoint(GetRootEndpoint())->GetNode() !=
        E2AP::RetrieveInstanceWithEndpoint("/E2Node/0")->GetNode())
    {
        NS_ABORT_MSG("Trying to run a xApp on a E2Node is a no-no");
    }
    // Read inputs from the json
    uint16_t requestingRnti = payload["RNTI"];
    uint16_t requestedTargetCellId = payload["Target Primary Cell ID"];

    // Do the processing
    uint16_t decidedTargetCellId = requestedTargetCellId;

    // Returns the chosen cellId or std::numeric_limits<uint16_t>::max() to reject the request
    decidedTargetCellId = ChooseTargetCellId(requestingRnti);

    // Check if cell is the one already connected
    for (auto& [rnti, imsiAndCellId] : m_rntiToImsiAndCellid)
    {
        if (rnti == requestingRnti)
        {
            if (imsiAndCellId.second == decidedTargetCellId)
            {
                decidedTargetCellId = std::numeric_limits<uint16_t>::max();
            }
        }
        else
        {
            continue;
        }
    }

    if (decidedTargetCellId != std::numeric_limits<uint16_t>::max())
    {
        m_rntiInHandover.emplace(requestingRnti, 0);
    }

    // Then write the outputs to the json
    payload["Target Primary Cell ID"] = decidedTargetCellId;
}

void
xAppHandoverMaxRsrq::HandoverStarted(std::string context,
                                     uint64_t imsi,
                                     uint16_t cellid,
                                     uint16_t rnti,
                                     uint16_t targetCellId)
{
    m_rntiInHandover.at(rnti) = imsi;
}

void
xAppHandoverMaxRsrq::HandoverSucceeded(std::string context,
                                       uint64_t imsi,
                                       uint16_t cellid,
                                       uint16_t rnti)
{
    m_rntiToImsiAndCellid[rnti] = std::make_pair(imsi, cellid);
    for (auto [key, value] : m_rntiInHandover)
    {
        if (value == imsi)
        {
            m_rntiInHandover.erase(m_rntiInHandover.find(key));
            break;
        }
    }
}

void
xAppHandoverMaxRsrq::ConnectionEstablished(std::string context,
                                           uint64_t imsi,
                                           uint16_t cellid,
                                           uint16_t rnti)
{
    m_rntiToImsiAndCellid[rnti] = std::make_pair(imsi, cellid);
    for (auto [key, value] : m_rntiInHandover)
    {
        if (value == imsi)
        {
            m_rntiInHandover.erase(m_rntiInHandover.find(key));
            break;
        }
    }
}
