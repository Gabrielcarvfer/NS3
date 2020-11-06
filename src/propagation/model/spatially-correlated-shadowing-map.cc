//
// Created by Gabriel Ferreira (@gabrielcarvfer) on 9/30/2020.
//

#include "spatially-correlated-shadowing-map.h"

namespace ns3 {

    float SpatiallyCorrelatedShadowingMap::m_mu{};
    float SpatiallyCorrelatedShadowingMap::m_sigma{};
    int   SpatiallyCorrelatedShadowingMap::m_cell_length{};
    int   SpatiallyCorrelatedShadowingMap::m_currentRun;
    Ptr<NormalRandomVariable> SpatiallyCorrelatedShadowingMap::m_normalGen = nullptr;
    SpatiallyCorrelatedShadowingMap * SpatiallyCorrelatedShadowingMap::m_instance = nullptr;
    std::map<std::vector<int>, std::tuple<bool, float, float>> SpatiallyCorrelatedShadowingMap::m_shadowingMap;

    SpatiallyCorrelatedShadowingMap::SpatiallyCorrelatedShadowingMap(float mu, float sigma, int cell_length)
    {
        if (m_instance==nullptr)
        {
            m_instance = this;
            m_normalGen = CreateObject<NormalRandomVariable> ();
            m_currentRun = ns3::RngSeedManager::GetRun();
        }
        m_mu = mu;
        m_sigma = sigma;
        m_cell_length = cell_length;
        m_normalGen->SetAttribute("Mean", DoubleValue(m_mu));
        m_normalGen->SetAttribute("Variance", DoubleValue(m_sigma * m_sigma));
    }

    float SpatiallyCorrelatedShadowingMap::get_coordinate_shadowing(Vector3D coordinate)
    {
        //if (m_currentRun >= 0 && m_currentRun < 2)
        //    return -3*m_sigma; // assume best case shadowing scenario
        //if (m_currentRun >= 2 && m_currentRun < 4)
        //    return 3*m_sigma; // assume worst case shadowing scenario

        // The spatially correlated shadowing map is generated on demand based
        //  on the received parameters and position of nodes
        //
        // cell(x,y,z) = coordinate(x//cell_length,
        //                          y//cell_length,
        //                          z//cell_length)
        //
        // Example of a 2D shadowing map
        // Z = node,
        // x = precomputed cells, with shadowing value generated and the mean of neighbors calculated
        // o = surrounding cells, with shadowing value generated,
        //   = non-existing cells
        //
        //        oxo
        //        xZx
        //        oxo            oxo
        //                       xZx
        //                       oxo

        std::vector<int> cellCoord = {(int)coordinate.x/m_cell_length,
                           (int)coordinate.y/m_cell_length,
                           (int)coordinate.z/m_cell_length};

        //Check if coordinate exists in the shadowing map
        auto entry = m_shadowingMap.find(cellCoord);

        //If it does, fast path returns the precomputed value
        if (entry != m_shadowingMap.end())
        {
            //Check if spatially correlated shadowing (mean of current and surrounding cells) has been computed
            if (std::get<0>(entry->second))
            {
                return std::get<2>(entry->second);
            }
            //Cell hasn't been precomputed yet, proceed to slow path
        }

        //If it doesn't, create the coordinate for the cell and surrounding cells
        // 26 surrounding cells
        std::vector<std::vector<int>> surroundingCellCoordinates;
        for(int i = -5; i <= 5; i++)
            for(int j = -5; j <= 5; j++)
                for(int k = -5; k <= 5; k++)
                    surroundingCellCoordinates.push_back({cellCoord[0]+i,cellCoord[1]+j,cellCoord[2]+k});

        //Compute average value of all shadowing samples for slow path
        double avg = 0;
        double denominator = 0;
        for (unsigned i = 0; i < surroundingCellCoordinates.size(); i++)
        {
            //Calculate exponential decay due to distance to the central coordinate
            float distance = sqrt(pow(surroundingCellCoordinates[i][0],2) + pow(surroundingCellCoordinates[i][1],2) + pow(surroundingCellCoordinates[i][2],2));
            double decay = pow(2,-1-distance);
            denominator += decay;

            //Search for surrounding cell entry
            auto surroundingEntry = m_shadowingMap.find(surroundingCellCoordinates[i]);

            //If entry doesn't exist, create one
            if (surroundingEntry == m_shadowingMap.end())
            {
                //Generate a random shadowing sample
                float shadowing = m_normalGen->GetValue();

                //Create an entry indicating the cell was a surrounding cell and not precomputed
                m_shadowingMap.emplace(surroundingCellCoordinates[i], std::tuple<bool, float, float>{false, shadowing, 0.0});
                avg += shadowing*decay;
            }
            //If it exists, just read the shadowing value
            else
            {
                avg += std::get<1>(surroundingEntry->second)*decay;
            }
        }


        //When all surrounding coordinates have been visited, precompute and save the final value
        entry = m_shadowingMap.find(cellCoord);
        avg /= denominator;
        //avg /= surroundingCellCoordinates.size();
        std::get<2>(entry->second) = avg;
        std::get<0>(entry->second) = true;

        //Return the spatially correlated shadowing
        return avg;
    }
}