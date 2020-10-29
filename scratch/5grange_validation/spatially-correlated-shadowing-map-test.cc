//
// Created by Gabriel Ferreira (@gabrielcarvfer) on 9/30/2020.
//

#include "ns3/spatially-correlated-shadowing-map.h"
#include <iostream>

using namespace ns3;

int main()
{
    ns3::RngSeedManager::SetSeed(1);
    ns3::RngSeedManager::SetRun(1);
    SpatiallyCorrelatedShadowingMap(0, 18*4.47, 110);//6*sigma to 3x3x3 exponential cell correlation, 12*sigma to 5x5x5, 18/50*sigma to 9x9x9

    double shadowing = 0;

    for (int x = 0; x < 6000; x+=37)
        for (int y = 0; y < 6000; y+=37)
            for (int z = 0; z < 100; z+=37)
                shadowing = SpatiallyCorrelatedShadowingMap::get_coordinate_shadowing(Vector3D(x, y, z));
    std::cout << "{ \"shadowMap\" : [" << std::endl;
    int i = SpatiallyCorrelatedShadowingMap::m_shadowingMap.size();
    for (auto entry: SpatiallyCorrelatedShadowingMap::m_shadowingMap) // shadowingMap must be public to do this
    {
        std::cout << "{\"x\":"<< entry.first[0] << ",\"y\":" << entry.first[1] << ",\"z\":" << entry.first[2] << ",\"shadowing\":" << (std::isnan(std::get<2>(entry.second)) ? 0.0 : std::get<2>(entry.second)) << ",\"shadowingOg\":" << (std::isnan(std::get<1>(entry.second)) ? 0.0 : std::get<1>(entry.second))  << "}";
        if (i > 1)
            std::cout << ",\n";
        i--;
    }
    std::cout << "]\n}" << std::endl;
    return 0;
}