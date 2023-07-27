#include "xAppHandoverMlpackKmeans.h"

#include "ns3/E2AP.h"
#include "ns3/core-module.h"

#include <mlpack/core.hpp>
#include <mlpack/methods/kmeans/allow_empty_clusters.hpp>
#include <mlpack/methods/kmeans/kmeans.hpp>
#include <mlpack/prereqs.hpp>

using namespace ns3;
using namespace oran;

NS_LOG_COMPONENT_DEFINE("xAppHandoverMlpackKmeans");

xAppHandoverMlpackKmeans::xAppHandoverMlpackKmeans(bool kmeansEmptyPolicy,
                                                   float clusteringPeriodicitySec,
                                                   bool initiateHandovers)
    : xAppHandover(),
      m_kmeansKeepEmptyPolicy(kmeansEmptyPolicy),
      m_clusteringPeriodicitySec(clusteringPeriodicitySec),
      m_initiateHandovers(initiateHandovers)
{
    NS_LOG_FUNCTION(this);

    Config::Connect("/NodeList/*/DeviceList/*/LteEnbRrc/HandoverEndOk",
                    MakeCallback(&xAppHandoverMlpackKmeans::HandoverSucceeded, this));
    Config::Connect("/NodeList/*/DeviceList/*/LteEnbRrc/HandoverStart",
                    MakeCallback(&xAppHandoverMlpackKmeans::HandoverStarted, this));
    Config::Connect("/NodeList/*/DeviceList/*/LteUeRrc/HandoverEndError",
                    MakeCallback(&xAppHandoverMlpackKmeans::HandoverFailed, this));
    Config::Connect("/NodeList/*/DeviceList/*/LteEnbRrc/ConnectionEstablished",
                    MakeCallback(&xAppHandoverMlpackKmeans::ConnectionEstablished, this));
    Simulator::Schedule(Seconds(m_clusteringPeriodicitySec),
                        &xAppHandoverMlpackKmeans::PeriodicClustering,
                        this);
};

void
xAppHandoverMlpackKmeans::PeriodicClustering()
{
    NS_LOG_FUNCTION(this);

    E2AP* ric = (E2AP*)static_cast<const E2AP*>(xApp::RetrieveInstanceWithEndpoint("/E2Node/0"));
    std::map<uint16_t, uint16_t> rntis;
    std::array<std::string, 4> kpmMetrics = {//"/KPM/HO.SrcCellQual.RSRP",
                                             "/KPM/HO.SrcCellQual.RSRQ",
                                             //"/KPM/HO.TrgtCellQual.RSRP",
                                             "/KPM/HO.TrgtCellQual.RSRQ"};
    std::map<uint16_t, uint16_t> cells;
    uint16_t i_rnti = 0;
    uint16_t i_cell = 0;
    // Count the number of eNodeBs/E2Nodes and the number of UEs/RNTIs
    for (auto kpmMetric : kpmMetrics)
    {
        auto metricMap = ric->QueryKpmMetric(kpmMetric);

        if (metricMap.size() == 0)
        {
            continue;
        }

        for (auto& e2nodeMeasurements : metricMap)

        {
            std::string cellIdStr(e2nodeMeasurements.first.begin() +
                                      e2nodeMeasurements.first.find_last_of("/") + 1,
                                  e2nodeMeasurements.first.end());
            uint16_t cellId = std::atoi(cellIdStr.c_str());
            if (cells.find(cellId) == cells.end())
            {
                cells[cellId] = i_cell++;
            }
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
                uint16_t rnti = measurementDeque.measurements["RNTI"];
                if (rntis.find(rnti) == rntis.end())
                {
                    rntis[rnti] = i_rnti++;
                }
            }
        }
    }

    // If there is nothing to cluster, end early
    if (rntis.size() == 0 || cells.size() == 0)
    {
        Simulator::Schedule(Seconds(1), &xAppHandoverMlpackKmeans::PeriodicClustering, this);
        return;
    }

    // Rows are cells and columns are UEs
    arma::mat dataset = arma::zeros(cells.size(), rntis.size());
    m_rntiToCurrentCellId.clear();

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
                uint16_t rnti = measurementDeque.measurements["RNTI"];
                uint16_t rnti_offset = rntis.at(rnti);
                if (kpmMetric == "/KPM/HO.SrcCellQual.RSRQ")
                {
                    uint16_t cellId = measurementDeque.measurements["CELLID"];
                    cellId++;
                    if (cells.find(cellId) == cells.end())
                        continue;
                    m_rntiToCurrentCellId[rnti] = cellId;
                    uint16_t cellid_offset = cells.at(cellId);
                    dataset.at(cellid_offset, rnti_offset) = measurementDeque.measurements["VALUE"];
                }
                else
                {
                    uint16_t cellId = measurementDeque.measurements["TARGET"];
                    uint16_t cellid_offset = cells.at(cellId);
                    dataset.at(cellid_offset, rnti_offset) = measurementDeque.measurements["VALUE"];
                }
            }
        }
    }
    // Prepare to run K-means
    arma::Row<size_t> assignments;
    arma::mat centroids;
    if (m_kmeansKeepEmptyPolicy)
    {
        mlpack::KMeans<mlpack::EuclideanDistance,
                mlpack::SampleInitialization,
                mlpack::AllowEmptyClusters,
                mlpack::NaiveKMeans,
                arma::mat>
            k;
        k.Cluster(dataset, cells.size(), assignments, centroids);
    }
    else
    {
        mlpack::KMeans<> k;
        k.Cluster(dataset, cells.size(), assignments, centroids);
    }

    // Print dataset with each column representing measurements from a UE
    std::cout << dataset << std::endl;

    // Print assigned clusters to each UE
    std::cout << assignments << std::endl;
    m_rntiToClusteredCellId.clear();

    // Translate assigned clusters into cellIds
    int i = 0;
    for (auto& rnti : rntis)
    {
        uint16_t cellId = -1;
        for (auto& cell : cells)
        {
            if (cell.second == (uint16_t)assignments.at(i))
            {
                cellId = cell.first;
                break;
            }
        }
        m_rntiToClusteredCellId[rnti.first] = cellId;
        i++;
    }

    if (m_initiateHandovers)
    {
        // Command handovers
        for (auto [rnti, connectedCell] : m_rntiToCurrentCellId)
        {
            // Skip rntis that were not assigned to cluster
            auto rntiToCluster = m_rntiToClusteredCellId.find(rnti);
            if (rntiToCluster == m_rntiToClusteredCellId.end())
                continue;

            // Skip rntis that are already in the target cluster cell id
            if (rntiToCluster->second == connectedCell)
                continue;

            // Skip rntis already in handover
            if (m_imsiInHandover.find(rnti) != m_imsiInHandover.end())
            {
                continue;
            }

            // Spoof RIC CONTROL REQUEST with source eNB endpoint (where the UE is currently
            // connected)
            std::string spoofed_src_endpoint = "/E2Node/" + std::to_string(connectedCell) + "/";
            ric->E2SmRcSendHandoverControlRequest(rnti,
                                                  rntiToCluster->second,
                                                  spoofed_src_endpoint);
        }
    }
    Simulator::Schedule(Seconds(m_clusteringPeriodicitySec),
                        &xAppHandoverMlpackKmeans::PeriodicClustering,
                        this);
}

void
xAppHandoverMlpackKmeans::HandoverDecision(Json& payload)
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

    // Use K-means clustering results
    if (m_rntiToClusteredCellId.find(requestingRnti) != m_rntiToClusteredCellId.end())
        decidedTargetCellId = m_rntiToClusteredCellId.at(requestingRnti);

    // If the result is invalid (same as current cell or unknown), use 0xFFFF to reject the handover
    if (m_rntiToCurrentCellId.find(requestingRnti) == m_rntiToCurrentCellId.end() ||
        decidedTargetCellId == m_rntiToCurrentCellId.at(requestingRnti))
        decidedTargetCellId = std::numeric_limits<uint16_t>::max();

    // Check if it is already in handover
    if (m_imsiInHandover.find(requestingRnti) != m_imsiInHandover.end())
        decidedTargetCellId = std::numeric_limits<uint16_t>::max();

    // If not in handover, mark it with an empty IMSI field
    if (decidedTargetCellId != std::numeric_limits<uint16_t>::max())
        m_imsiInHandover.emplace(requestingRnti, 0);

    // Then write the outputs to the json
    payload["Target Primary Cell ID"] = decidedTargetCellId;
    m_decision_history.push_back({requestingRnti, requestedTargetCellId, decidedTargetCellId});
}

void
xAppHandoverMlpackKmeans::HandoverStarted(std::string context,
                                          uint64_t imsi,
                                          uint16_t cellid,
                                          uint16_t rnti,
                                          uint16_t targetCellId)
{
    // Fix up imsi field set by HandoverDecision
    m_imsiInHandover.emplace(rnti, imsi);
}

void
xAppHandoverMlpackKmeans::HandoverSucceeded(std::string context,
                                            uint64_t imsi,
                                            uint16_t cellid,
                                            uint16_t rnti)
{
    NS_LOG_FUNCTION(this);
    std::cout << "yay" << std::endl; // reward predictor
    exit(0);
    for (auto [key, value] : m_imsiInHandover)
    {
        if (value == imsi)
        {
            m_imsiInHandover.erase(m_imsiInHandover.find(key));
            break;
        }
    }
}

void
xAppHandoverMlpackKmeans::HandoverFailed(std::string context,
                                         uint64_t imsi,
                                         uint16_t cellid,
                                         uint16_t rnti)
{
    NS_LOG_FUNCTION(this);
    std::cout << "nay" << std::endl; // punish predictor
    for (auto [key, value] : m_imsiInHandover)
    {
        if (value == imsi)
        {
            m_imsiInHandover.erase(m_imsiInHandover.find(key));
            break;
        }
    }
}

void
xAppHandoverMlpackKmeans::ConnectionEstablished(std::string context,
                                                uint64_t imsi,
                                                uint16_t cellid,
                                                uint16_t rnti)
{
    for (auto [key, value] : m_imsiInHandover)
    {
        if (value == imsi)
        {
            m_imsiInHandover.erase(m_imsiInHandover.find(key));
            break;
        }
    }
}
