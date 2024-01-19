#include "xAppHandoverMaliciousPositioning.h"

#include "ns3/E2AP.h"
#include "ns3/core-module.h"
#include "ns3/lte-enb-net-device.h"
#include "ns3/mobility-model.h"

#include <algorithm>

using namespace ns3;
using namespace oran;

NS_LOG_COMPONENT_DEFINE("xAppHandoverMaliciousPositioning");

xAppHandoverMaliciousPositioning::xAppHandoverMaliciousPositioning(bool useRnti)
    : xAppHandover(),
      m_useRnti(useRnti)
{
    NS_LOG_FUNCTION(this);

    /* Retrieve position of eNBs/gNBs
     *
     * While someone will definitely complain that I only can do this in a simulation,
     * the reality of it is that base station locations are not a secret in any way.
     *
     * In fact, there are publicly accessible databases/maps with the location of many stations.
     *
     * You can also go in person and make the measurements by yourself using a phone and its GPS.
     */

    // Search nodes with LteEnbNetDevice installed
    for (unsigned nodeId = 0; nodeId < NodeList::GetNNodes(); nodeId++)
    {
        auto node = NodeList::GetNode(nodeId);
        for (unsigned deviceId = 0; deviceId < node->GetNDevices(); deviceId++)
        {
            auto lteEnbNetDevice = node->GetDevice(deviceId)->GetObject<LteEnbNetDevice>();
            if (!lteEnbNetDevice)
                continue;
            auto mobilityModel = node->GetObject<MobilityModel>();
            if (!mobilityModel)
                NS_FATAL_ERROR("And it was at this moment, that he knew he f**kd up...");
            m_eNbPositions[lteEnbNetDevice->GetCellId()] = mobilityModel->GetPosition();
        }

    }
    Simulator::Schedule(Seconds(1), &xAppHandoverMaliciousPositioning::PeriodicPositioning, this);
};

std::map<uint16_t, double>
xAppHandoverMaliciousPositioning::GetRntiRsrqMeasurements(uint16_t rnti)
{
    NS_LOG_FUNCTION(this);

    E2AP* ric = (E2AP*)static_cast<const E2AP*>(E2AP::RetrieveInstanceWithEndpoint("/E2Node/0"));
    std::map<uint16_t, uint16_t> rntis;
    std::array<std::string, 4> kpmMetrics = {"/KPM/HO.SrcCellQual.RSRP",
                                             //"/KPM/HO.SrcCellQual.RSRQ",
                                             "/KPM/HO.TrgtCellQual.RSRP",
                                             //"/KPM/HO.TrgtCellQual.RSRQ"
                                            };

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
                if (kpmMetric == "/KPM/HO.SrcCellQual.RSRP")
                {
                    uint16_t cellId = measurementDeque.measurements["CELLID"];
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

    return rsrq_measurements;
}

Vector3D
xAppHandoverMaliciousPositioning::Multilateration(std::map<uint16_t, double>& measurements)
{
    Vector3D position;

    switch(measurements.size())
    {
        case 3:
            {
                // Trilateration
                auto it = measurements.begin();
                // Collect measured power (dBm) and position of respective cells
                auto Pa = it->second;
                Vector3D A = m_eNbPositions.at((it++)->first);

                auto Pb = it->second;
                Vector3D B = m_eNbPositions.at((it++)->first);

                auto Pc = it->second;
                Vector3D C = m_eNbPositions.at((it++)->first);

                // Estimate distance based on RSRP<->distance measurements
                // Look at distance.xlsx file, which contains post-processed results
                // from logging added to lte-enb-rrc.cc in the same commit
                auto dA = 205023*exp(-0.114 * Pa);
                auto dB = 205023*exp(-0.114 * Pb);
                auto dC = 205023*exp(-0.114 * Pc);

                // Calculate intermediate steps
                auto E = 2 * (-A.x + B.x);
                auto F = 2 * (-A.y + B.y);
                auto G = pow(dA, 2) - pow(dB, 2) - pow(A.x, 2) + pow(B.x, 2) - pow(A.y, 2) + pow(B.y, 2);
                auto H = 2 * (-B.x + C.x);
                auto I = 2 * (-B.y + C.y);
                auto J = pow(dB, 2) - pow(dC, 2) - pow(B.x, 2) + pow(C.x, 2) - pow(B.y, 2) + pow(C.y, 2);

                position.x = (G * I - J * F) / (I * E - F * H);
                position.y = (G * H - E * J) / (F * H - E * I);
            }
            break;
        case 2:
            {
                // Bilateration
                auto it = measurements.begin();
                // Collect measured power (dBm) and position of respective cells
                auto Pa = it->second;
                Vector3D A = m_eNbPositions.at((it++)->first);

                auto Pb = it->second;
                Vector3D B = m_eNbPositions.at((it++)->first);

                // Estimate distance based on RSRP<->distance measurements
                // Look at distance.xlsx file, which contains post-processed results
                // from logging added to lte-enb-rrc.cc in the same commit
                auto dA = 205023*exp(-0.114 * Pa);
                auto dB = 205023*exp(-0.114 * Pb);

                // Equations from Bilateration: An Attack-Resistant Localization
                // Algorithm of Wireless Sensor Network
                auto m = 0.5*((pow(A.x,2)-pow(B.x,2))+(pow(A.y,2)-pow(B.y,2))-(pow(dA,2)-pow(dB,2)))/(A.y-B.y);
                auto n = -(A.x-B.x)/(A.y-B.y);

                // We can have two candidate solutions, but they can be complex, which we need to discard
                position.x = -(m*n-n*A.y-A.x)/(1+pow(n, 2));
                auto plusminus = 2*(n*A.x+m)*A.y-pow(A.y,2)-pow(n,2)*pow(A.x,2)-2*m*n*A.x-pow(m,2)+(1+pow(n,2))*pow(dA,2);
                if (plusminus < 0)
                    plusminus = -plusminus;
                plusminus = sqrt(plusminus)/(1+pow(n, 2));

                position.x += plusminus;
                position.y = m+n*position.x;
                // Discard candidate coordinate if it is bogus
                if (isnan(position.x) || isnan(position.y))
                    position = Vector3D();
            }
            break;
        default:
            //NS_FATAL_ERROR("Not enought RSRP measurements for multilateration");
            break;
    }
    return position;
}

Vector3D
xAppHandoverMaliciousPositioning::GradientDescent(std::map<uint16_t, double>& measurements)
{
    // Guess a random initial position for the UE
    Vector3D position = {(float)rand()*10000/(float)(RAND_MAX), (float)rand()*10000/(float)(RAND_MAX), 0};

    auto iteration_error = [&measurements, &position, this]() {
        double error = 0;
        for (auto&& [cellId, power] : measurements)
        {
            if (measurements.find(cellId) == measurements.end())
            {
                continue;
            }

            // We don't actually know the distance between it and the eNBs, but
            // we do know the measurement values are proportional to the distance,
            // assuming the same radio configuration (antenna type, elevation,
            // topology, sensitivity) and parameters of transmission (power, frequency)

            double distance = CalculateDistance(position, m_eNbPositions[cellId]);
            error += distance / measurements[cellId];
        }
        return error;
    };

    double learning_rate = 0.2;
    auto errorOld = iteration_error();
    int maxTries = 100000;
    while(--maxTries)
    {
        errorOld = iteration_error();
        position.x += errorOld*learning_rate;
        position.y += errorOld*learning_rate;
        auto errorNew = iteration_error();
        if (abs(errorOld - errorNew) < abs(0.001*errorOld))
            break;
        if (errorNew > errorOld)
        {
            position.x -= 2*errorOld*learning_rate;
            position.y -= 2*errorOld*learning_rate;
        }
    }

    return position;
}

void
xAppHandoverMaliciousPositioning::PeriodicPositioning()
{
    NS_LOG_FUNCTION(this);

    // Use positioning techniques to locate UEs
    // Notice: rnti can be legitimate or random
    for (auto rnti: m_rntiList)
    {
        auto measurements = GetRntiRsrqMeasurements(rnti);
        if (measurements.empty())
            continue;
        auto estimated_position = Multilateration(measurements);
        //auto estimated_position = GradientDescent(measurements);
        //if (estimated_position.GetLength())
        //    continue;
        std::cout << estimated_position << std::endl;
    }

    // Re-schedule this function
    Simulator::Schedule(Seconds(1), &xAppHandoverMaliciousPositioning::PeriodicPositioning, this);
}

void
xAppHandoverMaliciousPositioning::HandoverDecision(Json& payload)
{
    NS_LOG_FUNCTION(this);
    // only collect RNTI from request
    m_rntiList.push_back(payload["RNTI"]);

    // does nothing on purpose
}
