#include "xAppHandoverMaliciousPositioning.h"

#include "ns3/E2AP.h"
#include "ns3/core-module.h"
#include "ns3/lte-enb-net-device.h"
#include "ns3/lte-ue-net-device.h"
#include "ns3/lte-ue-rrc.h"
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

    Config::Connect("/NodeList/*/DeviceList/*/LteEnbRrc/HandoverEndOk",
                   MakeCallback(&xAppHandoverMaliciousPositioning::HandoverSucceeded, this));
    Config::Connect("/NodeList/*/DeviceList/*/LteEnbRrc/ConnectionEstablished",
                    MakeCallback(&xAppHandoverMaliciousPositioning::ConnectionEstablished, this));
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

xAppHandoverMaliciousPositioning::~xAppHandoverMaliciousPositioning()
{
    // Dump file with tracking output (nodeId can only be used in results analysis,
    // not during the simulation, otherwise it would be cheating)
    std::ofstream ofs("malicious-tracking.csv");
    ofs << "Time (ms),rnti,nodeId,x,y,z\n";
    for (auto& [time, rnti, nodeId, coord] : m_rntiNodeTracking)
    {
        ofs << time.GetMilliSeconds() << "," << rnti << "," << nodeId << "," << coord.x << ","
            << coord.y << "," << coord.z << "\n";
    }
    ofs << std::endl;
    ofs.close();
}

std::map<uint16_t, double>
xAppHandoverMaliciousPositioning::GetRntiRsrqMeasurements(uint16_t rnti, Time gracePeriod)
{
    NS_LOG_FUNCTION(this);

    E2AP* ric = (E2AP*)static_cast<const E2AP*>(E2AP::RetrieveInstanceWithEndpoint("/E2Node/0"));
    std::array<std::string, 4> kpmMetrics = {
        "/KPM/HO.SrcCellQual.RSRP",
        //"/KPM/HO.SrcCellQual.RSRQ",
        "/KPM/HO.TrgtCellQual.RSRP",
        //"/KPM/HO.TrgtCellQual.RSRQ"
    };

    std::map<uint16_t, double> rsrq_measurements;

    // Collate data into an armadillo matrix for processing
    for (auto kpmMetric : kpmMetrics)
    {
        auto metricMap = ric->QueryLatestKpmMetricForRnti(kpmMetric, rnti, gracePeriod);

        if (metricMap.size() == 0)
        {
            continue;
        }

        for (auto& e2nodeMeasurements : metricMap)
        {
            for (auto& measurementDeque : e2nodeMeasurements.second)
            {
                auto key = kpmMetric == "/KPM/HO.SrcCellQual.RSRP" ? "CELLID" : "TARGET";
                uint16_t cellId = measurementDeque.measurements[key];
                if (rsrq_measurements.find(cellId) == rsrq_measurements.end())
                {
                    rsrq_measurements[cellId] = measurementDeque.measurements["VALUE"];
                }
                else
                {
                    rsrq_measurements[cellId] *= 0.8;
                    rsrq_measurements[cellId] += 0.2*(double)measurementDeque.measurements["VALUE"];
                }
            }
        }
    }

    return rsrq_measurements;
}

double estimate_distance_from_power(double P)
{
    return (-500+14000*exp(-P/20));
}

Vector3D
xAppHandoverMaliciousPositioning::Multilateration(std::map<uint16_t, double>& measurements)
{
    Vector3D position;
    if (measurements.size() < 3)
        return Vector3D();
    //switch (measurements.size())
    //{
    //case 3: {
    // Trilateration
    auto it = measurements.begin();
    // Collect measured power (dBm) and position of respective cells
    auto Pa = it->second;
    Vector3D A = m_eNbPositions.at((it++)->first);

    auto Pb = it->second;
    Vector3D B = m_eNbPositions.at((it++)->first);

    auto Pc = it->second;
    Vector3D C = m_eNbPositions.at((it++)->first);

    // Search for a measurement of an unaligned station, or abort the trilateration
    while((A.x == B.x && B.x == C.x) || (A.y == B.y && B.y == C.y))
    {
        if (it == measurements.end())
            return Vector3D();
        Pc = it->second;
        C = m_eNbPositions.at((it++)->first);
    }

    // Estimate distance based on RSRP<->distance measurements
    // Look at distance.xlsx file, which contains post-processed results
    // from logging added to lte-enb-rrc.cc in the same commit
    auto dA = estimate_distance_from_power(Pa);
    auto dB = estimate_distance_from_power(Pb);
    auto dC = estimate_distance_from_power(Pc);

    // Calculate intermediate steps
    auto E = 2 * (-A.x + B.x);
    auto F = 2 * (-A.y + B.y);
    auto G = dA*dA - dB*dB - A.x*A.x + B.x*B.x - A.y*A.y + B.y*B.y;
    auto H = 2 * (-B.x + C.x);
    auto I = 2 * (-B.y + C.y);
    auto J = dB*dB - dC*dC - B.x*B.x + C.x*C.x - B.y*B.y + C.y*C.y;

    // Prevent zeros
    //E = (E == 0)   ? 1 : E;
    //I = (I == 0)   ? 1 : I;
    auto DX = I * E - F * H;
    //DX = (DX == 0) ? 1 : DX;
    auto DY = F * H - E * I;
    //DY = (DY == 0) ? 1 : DX;

    // Calculate trilaterated coordinate
    position.x = (G * I - J * F) / DX;
    position.y = (G * H - E * J) / DY;
    //std::cout << position.x << " " << position.y << std::endl;
    //}
    //break;
    /*case 2:
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
            auto m =
       0.5*((pow(A.x,2)-pow(B.x,2))+(pow(A.y,2)-pow(B.y,2))-(pow(dA,2)-pow(dB,2)))/(A.y-B.y); auto n
       = -(A.x-B.x)/(A.y-B.y);

            // We can have two candidate solutions, but they can be complex, which we need to
       discard position.x = -(m*n-n*A.y-A.x)/(1+pow(n, 2)); auto plusminus =
       2*(n*A.x+m)*A.y-pow(A.y,2)-pow(n,2)*pow(A.x,2)-2*m*n*A.x-pow(m,2)+(1+pow(n,2))*pow(dA,2); if
       (plusminus < 0) plusminus = -plusminus; plusminus = sqrt(plusminus)/(1+pow(n, 2));

            position.x += plusminus;
            position.y = m+n*position.x;
            // Discard candidate coordinate if it is bogus
            if (isnan(position.x) || isnan(position.y))
                position = Vector3D();
        }
        break;*/
    //default:
    //    // NS_FATAL_ERROR("Not enought RSRP measurements for multilateration");
    //    break;
    //}
    return position;
}

double calculate_error (Vector3D a, Vector3D b, double rsrp)
{
    // We don't actually know the distance between it and the eNBs, but
    // we do know the measurement values are proportional to the distance,
    // assuming the same radio configuration (antenna type, elevation,
    // topology, sensitivity) and parameters of transmission (power, frequency)
    double distance = CalculateDistance(a, b);
    std::cout << distance << "," << rsrp << std::endl;
    double estimated_distance = estimate_distance_from_power(rsrp);
    // Squared error
    double error = pow(distance - estimated_distance, 2);
    return error;
};
auto iteration_error (Vector3D position,std::map<uint16_t, double>& measurements,
        std::map<uint16_t, ns3::Vector3D>& enbPositions) {
    double error = 0;
    for (auto&& [cellId, power] : measurements)
    {
        error += calculate_error(position, enbPositions[cellId], power);
    }
    return error;
};
std::vector<double> calculate_errors (Vector3D position,
                                      std::map<uint16_t, double>& measurements,
                                      std::map<uint16_t, ns3::Vector3D>& enbPositions)
{
    std::vector<double> errors;
    for (auto&& [cellId, power] : measurements)
    {
        auto error = calculate_error(position, enbPositions[cellId], power);
        //std::cout << "cellid " << cellId
        //          << " error " << error
        //          << std::endl;
        errors.push_back(error);
    }
    return errors;
};

auto always_better = [](std::vector<double>& errorOld, std::vector<double>& errorNew){
    bool alwaysBetter = true;
    for (unsigned i = 0; i < errorNew.size(); i++)
    {
        if (errorNew[i] > errorOld[i])
        {
            alwaysBetter = false;
            break;
        }
    }
    return alwaysBetter;
};

//auto searchIt = [&rntiNode,
//                 &calculate_errors,
//                 &always_better]
//                 (Vector3D newPos,
//                  std::vector<double> errorOld)
//                 ->std::optional<std::pair<Vector3D, std::vector<double>>>
//{
//    std::cout << "node " << rntiNode->GetId()
//              << " real position " << rntiNode->GetObject<MobilityModel>()->GetPosition()
//              << " estimated position " << newPos << std::endl;
//    auto errorNew = calculate_errors(newPos);
//    if (always_better(errorOld, errorNew))
//    {
//        return std::pair<Vector3D, std::vector<double>>(newPos, errorNew);
//    }
//    return {};
//};
auto recursiveSearch (double lx, double ly, double ux, double uy,
                          Vector3D bestPosition,
                          std::vector<double> bestError,
                          int depth,
                          std::map<uint16_t, double>& measurements,
                          std::map<uint16_t, ns3::Vector3D>& enbPositions)
        ->std::pair<Vector3D, std::vector<double>>
{
    // If reached maximum depth, pick up whatever we have and transform it into a position
    if (depth == 0)
    {
        Vector3D newPos{(ux+lx)/2, (uy+ly)/2, 0.0};
        auto errorNew = calculate_errors(newPos, measurements, enbPositions);
        return {newPos, errorNew};
    }

    // Divide search space into 4 sectors and search them individually recursively
    //  2 3
    //  0 1

    std::pair<Vector3D, std::vector<double>> ans;
    ans = {bestPosition, bestError};
    for (auto sector = 0; sector < 4; sector++)
    {
        std::pair<Vector3D, std::vector<double>> temp;
        double tlx,tly,tux,tuy;
        switch(sector)
        {
            case 0:
                tlx = lx, tly = ly, tux = ux/2, tuy = uy/2;
                break;
            case 1:
                tlx = ux/2, tly = ly, tux = ux, tuy = uy/2;
                break;
            case 2:
                tlx = lx, tly = uy/2, tux = ux/2, tuy = uy;
                break;
            case 3:
                tlx = ux/2, tly = uy/2, tux = ux, tuy = uy;
                break;
            default:
                NS_ABORT_MSG("Invalid sector");
        }
        // Before embarking on a very expensive recursive search, check extremes of each sector.
        // If all of them fail, discard the entire quadrant.
        //if (iteration_error(ans.first, measurements, enbPositions) < iteration_error({tlx,tly,0.0}, measurements, enbPositions)
        // && iteration_error(ans.first, measurements, enbPositions) < iteration_error({tlx,tuy,0.0}, measurements, enbPositions)
        // && iteration_error(ans.first, measurements, enbPositions) < iteration_error({tux,tly,0.0}, measurements, enbPositions)
        // && iteration_error(ans.first, measurements, enbPositions) < iteration_error({tux,tuy,0.0}, measurements, enbPositions)
        //) {
        //    continue;
        //}else{
            temp = recursiveSearch(tlx, tly, tux, tuy, ans.first, ans.second, depth - 1, measurements, enbPositions);
            if (//iteration_error(ans.first, measurements, enbPositions) > iteration_error(temp.first, measurements, enbPositions)
                //||
                always_better(ans.second, temp.second))
            {
                ans = temp;
                //std::cout << ans.first << std::endl;
                //std::cout << "taken " << temp.first << " error " << iteration_error(temp.first, measurements, enbPositions) << std::endl;
            }
        //}
    }
    return ans;
}

Vector3D
xAppHandoverMaliciousPositioning::QuadrantSearch(std::map<uint16_t, double>& measurements, Ptr<Node> rntiNode)
{
    // Guess a random initial position for the UE
    Vector3D position = {0, 0, 0};
    auto errorOld = calculate_errors(position, measurements, m_eNbPositions);
    int depth = 10;
    auto ans = recursiveSearch(0.0, 0.0, 10000.0, 10000.0, position, errorOld, depth, measurements, m_eNbPositions);
    //std::cout << "node " << rntiNode->GetId()
    //          << ", real position " << rntiNode->GetObject<MobilityModel>()->GetPosition()
    //          << ", estimated position " << ans.first
    //          << ", 1st closest enb " <<  measurements.rbegin()->first
    //          << " rsrp " << measurements.rbegin()->second
    //          << ", 2nd closest enb " <<  (++measurements.rbegin())->first
    //          << " rsrp " << (++measurements.rbegin())->second
    //          << ", 3rd closest enb " <<  (++++measurements.rbegin())->first
    //          << " rsrp " << (++++measurements.rbegin())->second
    //          << std::endl;
    return ans.first;
}

Vector3D recursiveSearchGrad (int lx, int ly, int ux, int uy,
                      Vector3D bestPos,
                      std::map<uint16_t, double>& measurements,
                      std::map<uint16_t, ns3::Vector3D>& enbPositions)
{
    // Stop condition is when bounds are small
    if ((ux-lx <= 10 && uy-ly <= 10)) {
        return bestPos;
    }

    // Generate 10000 coordinates within our grid search space
    std::vector<std::pair<Vector3D,double>> samples;
    samples.push_back({bestPos, iteration_error(bestPos, measurements, enbPositions)});

    int SAMPLES = 100;
    for(int i = 0; i < SAMPLES; i++)
    {
        for(int j = 0; j < SAMPLES; j++)
        {
            samples.push_back({{(double)(i*(ux-lx)/SAMPLES)+lx, (double)(j*(uy-ly)/SAMPLES)+ly, 0.0}, 0.0});
            samples.rbegin()->second = iteration_error(samples.rbegin()->first, measurements, enbPositions);
        }
    }

    // Order by error
    std::sort(samples.begin(), samples.end(), [](auto a, auto b)->bool{
        return a.second < b.second;
    });

    // Check in which side or quadrant do the smallest 10% falls on
    std::array<int, 4> quadrantCount{0};
    for (int i = 0; i < 100; i++)
    {
        unsigned short quad = 0;
        if (samples[i].first.x > (ux+lx)/2)
            quad |= 0b010;
        if (samples[i].first.y > (uy+ly)/2)
            quad |= 0b001;
        quadrantCount[quad]++;

        //std::cout << "sample " << i
        //          << "\tcoord " << samples[i].first
        //          << "\terror " << samples[i].second
        //          << std::endl;
    }

    auto bestQuadrant = -1;
    auto bestQuadrantCount = 0;
    for (int i = 0; i < 4; i++)
    {
        if (quadrantCount[i] > bestQuadrantCount)
        {
            bestQuadrantCount = quadrantCount[i];
            bestQuadrant = i;
        }
    }

    // Instead of completely dropping other quadrants, we are going to cut them in half
    int tlx=lx, tly=ly, tux=ux, tuy=uy;
    switch(bestQuadrant)
    {
        case 0:
            tux -= (ux-lx)/5;
            tuy -= (uy-ly)/5;
            break;
        case 1:
            tlx += (ux-lx)/5;
            tuy -= (uy-ly)/5;
            break;
        case 2:
            tux -= (ux-lx)/5;
            tly += (uy-ly)/5;
            break;
        case 3:
            tlx += (ux-lx)/5;
            tly += (uy-ly)/5;
            break;
        default:
            NS_FATAL_ERROR("It hasn't happened yet");
    }
    // std::cout << tlx << "\t"
    //           << tly << "\t"
    //           << tux << "\t"
    //           << tuy << "\t"
    //           << "best so far " << samples[0].first
    //           << " error " << samples[0].second
    //           << std::endl;

    // Refine search
    return recursiveSearchGrad(tlx, tly, tux, tuy, samples[0].first, measurements, enbPositions);
}
Vector3D
xAppHandoverMaliciousPositioning::GradientDescent(std::map<uint16_t, double>& measurements, Ptr<Node> rntiNode)
{
    // Guess a random initial position for the UE
    Vector3D position = {0, 0, 0};
    auto errorOld = calculate_errors(position, measurements, m_eNbPositions);
    auto ans = recursiveSearchGrad(0, 0, 2500, 2500, position, measurements, m_eNbPositions);
    //std::cout << "node " << rntiNode->GetId()
    //          << ", real position " << rntiNode->GetObject<MobilityModel>()->GetPosition()
    //          << ", estimated position " << ans
    //          << ", 1st closest enb " <<  measurements.rbegin()->first
    //          << " rsrp " << measurements.rbegin()->second
    //          << ", 2nd closest enb " <<  (++measurements.rbegin())->first
    //          << " rsrp " << (++measurements.rbegin())->second
    //          << ", 3rd closest enb " <<  (++++measurements.rbegin())->first
    //          << " rsrp " << (++++measurements.rbegin())->second
    //          << std::endl;
    return ans;
}

std::map<uint16_t, Ptr<Node>> g_rntiToNodeMap;

Ptr <Node> find_nodeid_with_rnti(uint16_t rnti) {
    Ptr <Node> rntiNode;
    // Check the cache to save up on search time
    if (g_rntiToNodeMap.find(rnti) != g_rntiToNodeMap.end()) {
        rntiNode = g_rntiToNodeMap[rnti];
        bool nodeIsValid = true;
        // Check node devices to double-check if the rnti is still valid
        for (unsigned deviceId = 0; deviceId < rntiNode->GetNDevices(); deviceId++) {
            auto lteUeNetDevice = rntiNode->GetDevice(deviceId)->GetObject<LteUeNetDevice>();
            if (!lteUeNetDevice)
                continue;
            if (lteUeNetDevice->GetRrc()->GetRnti() != rnti) {
                nodeIsValid = false;
                break;
            }
        }
        // Delete entry in case the rnti changed, or return in case it didn't
        if (!nodeIsValid)
            g_rntiToNodeMap.erase(rnti);
        else
            return g_rntiToNodeMap[rnti];
    }
    // Perform an exhaustive search for the node with the rnti
    for (unsigned nodeId = 0; nodeId < NodeList::GetNNodes(); nodeId++) {
        Ptr <Node> n = NodeList::GetNode(nodeId);
        for (unsigned deviceId = 0; deviceId < n->GetNDevices(); deviceId++) {
            auto lteUeNetDevice = n->GetDevice(deviceId)->GetObject<LteUeNetDevice>();
            if (!lteUeNetDevice)
                continue;
            if (lteUeNetDevice->GetRrc()->GetRnti() != rnti)
                continue;
            auto mobilityModel = n->GetObject<MobilityModel>();
            if (!mobilityModel)
                NS_FATAL_ERROR("And it was at this moment, that he knew he f**kd up...");
            g_rntiToNodeMap[rnti] = n;
            return n;
        }
    }
    return Ptr<Node>();
}

void
xAppHandoverMaliciousPositioning::PeriodicPositioning()
{
    NS_LOG_FUNCTION(this);
    // Use positioning techniques to locate UEs
    // Notice: rnti can be legitimate or random
    E2AP* ric = (E2AP*)static_cast<const E2AP*>(E2AP::RetrieveInstanceWithEndpoint("/E2Node/0"));

    auto src = ric->QueryLatestRntisForKpmMetric("/KPM/HO.SrcCellQual.RSRP");
    auto trgt= ric->QueryLatestRntisForKpmMetric("/KPM/HO.TrgtCellQual.RSRP");
    src.merge(trgt);
    for (auto rnti: src)
    {
        auto node = find_nodeid_with_rnti(rnti);
        if (!node)
        {
            // RNTI changed
            continue;
        }

        auto measurements = GetRntiRsrqMeasurements(rnti);
        if (measurements.empty())
            continue;

        //auto estimated_position = Multilateration(measurements);
        //auto estimated_position = QuadrantSearch(measurements, node);
        auto estimated_position = GradientDescent(measurements, node);
        // if (estimated_position.GetLength())
        //     continue;
        if (estimated_position != Vector3D())
        {
            m_rntiNodeTracking.push_back(
                {Simulator::Now(), rnti, node->GetId(), estimated_position});
            //std::cout << rnti << "," <<estimated_position << std::endl;
        }
    }

    // Re-schedule this function
    Simulator::Schedule(MilliSeconds(100), &xAppHandoverMaliciousPositioning::PeriodicPositioning, this);
}

void
xAppHandoverMaliciousPositioning::HandoverDecision(Json& payload)
{
    NS_LOG_FUNCTION(this);
    uint16_t rnti = payload["RNTI"];
    // only collect RNTI from request
    if (m_rntiSet.find(rnti) == m_rntiSet.end())
    {
        m_rntiSet.emplace(rnti);
    }
    // does nothing on purpose
    auto node = find_nodeid_with_rnti(rnti);
    //std::cout << Simulator::Now().GetMilliSeconds() << " HOAuth node " <<  (node ? std::to_string(node->GetId()) : "??") << " rnti " << std::to_string(rnti) << std::endl;
}

void
xAppHandoverMaliciousPositioning::HandoverSucceeded(std::string context,
                                       uint64_t imsi,
                                       uint16_t cellid,
                                       uint16_t rnti)
{
    //std::cout << Simulator::Now().GetMilliSeconds() << " HOSuc node " <<  std::to_string(find_nodeid_with_rnti(rnti)->GetId()) << " rnti " << std::to_string(rnti) << std::endl;
}

void
xAppHandoverMaliciousPositioning::ConnectionEstablished(std::string context,
                                           uint64_t imsi,
                                           uint16_t cellid,
                                           uint16_t rnti)
{
    //std::cout << Simulator::Now().GetMilliSeconds() << " ConnEstab node " <<  std::to_string(find_nodeid_with_rnti(rnti)->GetId()) << " rnti " << std::to_string(rnti) << std::endl;
}
