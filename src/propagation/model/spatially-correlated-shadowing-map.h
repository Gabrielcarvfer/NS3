//
// Created by Gabriel Ferreira (@gabrielcarvfer) on 9/30/2020.
//

#ifndef NS3_SPATIALLY_CORRELATED_SHADOWING_MAP_H
#define NS3_SPATIALLY_CORRELATED_SHADOWING_MAP_H

#include <map>
#include <tuple>
#include "ns3/core-module.h"

namespace ns3
{
    class SpatiallyCorrelatedShadowingMap
    {
        public:
            SpatiallyCorrelatedShadowingMap(float mu, float sigma, int cell_length);
            static float get_coordinate_shadowing(Vector3D);
        private:
            static float m_mu;
            static float m_sigma;
            static int m_cell_length;
            static SpatiallyCorrelatedShadowingMap * m_instance;
            static Ptr<NormalRandomVariable> m_normalGen;
            static int m_currentRun;
    public:
        static std::map<std::vector<int>, std::tuple<bool, float, float>> m_shadowingMap;
    };
}


#endif //NS3_SPATIALLY_CORRELATED_SHADOWING_MAP_H


