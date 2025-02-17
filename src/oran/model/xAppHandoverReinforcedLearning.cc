#include "xAppHandoverReinforcedLearning.h"

#include "ns3/matrix-array.h"
#include "pybind11/numpy.h"
#include "pybind11/pybind11.h"

#include "ns3/E2AP.h"
#include "ns3/core-module.h"

#include <algorithm>
#include <pybind11/embed.h>

#include <deque>

#include <filesystem>
#define PYBIND11_DETAILED_ERROR_MESSAGES
namespace py = pybind11;
using namespace ns3;
using namespace oran;

py::scoped_interpreter* g_interpreter = nullptr;
py::module_ pyhrl;
NS_LOG_COMPONENT_DEFINE("xAppHandoverReinforcedLearning");

xAppHandoverReinforcedLearning::xAppHandoverReinforcedLearning(bool initiateHandovers)
    : xAppHandover(),
      m_initiateHandovers(initiateHandovers)
{
    NS_LOG_FUNCTION(this);
    Config::Connect("/NodeList/*/DeviceList/*/LteEnbRrc/HandoverEndOk",
                    MakeCallback(&xAppHandoverReinforcedLearning::HandoverSucceeded, this));
    Config::Connect("/NodeList/*/DeviceList/*/LteEnbRrc/ConnectionEstablished",
                    MakeCallback(&xAppHandoverReinforcedLearning::ConnectionEstablished, this));
    if (m_initiateHandovers)
    {
        Simulator::Schedule(Seconds(1), &xAppHandoverReinforcedLearning::PeriodicHandoverCheck, this);
    }
};
uint16_t
xAppHandoverReinforcedLearning::ChooseTargetCellId(uint16_t rnti)
{
    NS_LOG_FUNCTION(this);

    const int metric_buffer_len = 16;
    uint16_t srcCellId;
    uint64_t imsi; 
    E2AP* ric = (E2AP*)static_cast<const E2AP*>(E2AP::RetrieveInstanceWithEndpoint("/E2Node/0"));
    std::map<uint16_t, uint16_t> rntis;
    std::array<std::string, 4> kpmMetrics = {"/KPM/HO.SrcCellQual.RSRP",
                                             //"/KPM/HO.SrcCellQual.RSRQ",
                                             "/KPM/HO.TrgtCellQual.RSRP",
                                             //"/KPM/HO.TrgtCellQual.RSRQ"
					     };
	
    if (!g_interpreter)
    {
        g_interpreter = new py::scoped_interpreter{};
        pyhrl = py::module_::import("HandoverRL");
        std::filesystem::path cwd = std::filesystem::current_path();
        pyhrl.attr("init_module")
        (   metric_buffer_len, 2,
            (cwd / "src/oran/model/target5.pth").string(),  //load_path
            (cwd / "src/oran/model/target.pth").string()  // save_path
            );
    }

    //rsrp mas n vou mudar em todos os lugares agr n
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
		imsi = measurementDeque.measurements["IMSI"];
		
                if (kpmMetric == "/KPM/HO.SrcCellQual.RSRP")
                {
                    uint16_t cellId = measurementDeque.measurements["CELLID"];
		    srcCellId = cellId;
		    //cellId++;
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
    
    auto it = rsrq_measurements.find(1);
    float t0_metric = it != rsrq_measurements.end() ? static_cast<float>(it->second)  : 0.0;
    it = rsrq_measurements.find(2);
    float t1_metric = it != rsrq_measurements.end() ? static_cast<float>(it->second)  : 0.0;
    //training
    auto make_handover = pyhrl.attr("train_step")(t0_metric, t1_metric, srcCellId-1, imsi).cast<uint16_t>();
    //testing
    //auto make_handover = pyhrl.attr("handover_decision")(t0_metric, t1_metric, srcCellId-1, imsi).cast<uint16_t>();

    return make_handover ? (srcCellId ^ 3) : srcCellId;
    
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
xAppHandoverReinforcedLearning::PeriodicHandoverCheck()
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
    Simulator::Schedule(Seconds(1), &xAppHandoverReinforcedLearning::PeriodicHandoverCheck, this);
}

void
xAppHandoverReinforcedLearning::HandoverDecision(Json& payload)
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
    for (auto& [rnti, imsiAndCellId] : m_rntiToImsiAndCellid){
        if (rnti == requestingRnti){
            if (imsiAndCellId.second == decidedTargetCellId){
                decidedTargetCellId = std::numeric_limits<uint16_t>::max();
            }
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
xAppHandoverReinforcedLearning::HandoverStarted(std::string context,
                                     uint64_t imsi,
                                     uint16_t cellid,
                                     uint16_t rnti,
                                     uint16_t targetCellId)
{
    m_rntiInHandover.at(rnti) = imsi;
    std::cout<<"\n\nHandover started for imsi: "<<imsi<<"\n\n";
}

void
xAppHandoverReinforcedLearning::HandoverSucceeded(std::string context,
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
xAppHandoverReinforcedLearning::ConnectionEstablished(std::string context,
                                           uint64_t imsi,
                                           uint16_t cellid,
                                           uint16_t rnti)
{
    std::cout<<"\n\nConnectionEstablished\n"<<std::endl;
    for (auto [key, value] : m_rntiInHandover)
    {
        if (value == imsi)
        {
	    m_rntiHandoverFailed.insert(rnti);
	    m_rntiInHandover.erase(m_rntiInHandover.find(key));
            break;
        }
    }
    for (auto [key, value] : m_rntiToImsiAndCellid)
    {
        if (value.first == imsi)
        {
	    m_rntiToImsiAndCellid.erase(m_rntiToImsiAndCellid.find(key));
            break;
        }
    }
    m_rntiToImsiAndCellid[rnti] = std::make_pair(imsi, cellid);
}


