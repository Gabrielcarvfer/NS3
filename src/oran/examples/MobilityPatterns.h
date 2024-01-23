// Copyright (c) 2024 Centre Tecnologic de Telecomunicacions de Catalunya (CTTC)
//
// SPDX-License-Identifier: GPL-2.0-only

#ifndef NS3_MOBILITYPATTERNS_H
#define NS3_MOBILITYPATTERNS_H

#include <vector>

class BoundingBox
{
  public:
    BoundingBox(double xMin, double xMax, double yMin, double yMax)
        : xMin(xMin),
          xMax(xMax),
          yMin(yMin),
          yMax(yMax){};

    constexpr double GetXLength()
    {
        return xMax - xMin;
    }

    constexpr double GetYLength()
    {
        return yMax - yMin;
    }

    constexpr double GetShortestLength()
    {
        return std::min(GetXLength(), GetYLength());
    }

    double xMin;
    double xMax;
    double yMin;
    double yMax;
};

using PatternCoordinates = std::vector<std::pair<double, double>>;

class MobilityPatterns
{
  public:
    enum PATTERN_ENUM : uint16_t
    {
        UPWARDS_TRIANGLE = 0,
        DOWNWARDS_TRIANGLE,
        HOURGLASS,
        SQUARE,
        DIAMOND,
        X1PERIOD,
        X2PERIOD,
        X3PERIOD,
        NUM_PATTERNS
    };

    static PatternCoordinates GetMobilityPatternCoordinates(uint32_t steps,
                                                            BoundingBox box,
                                                            MobilityPatterns::PATTERN_ENUM number);
    static PatternCoordinates GetMobilityPatternUpwardsTriangle(uint32_t steps, BoundingBox box);
    static PatternCoordinates GetMobilityPatternDownwardsTriangle(uint32_t steps, BoundingBox box);
    static PatternCoordinates GetMobilityPatternHourglass(uint32_t steps, BoundingBox box);
    static PatternCoordinates GetMobilityPatternSquare(uint32_t steps, BoundingBox box);
    static PatternCoordinates GetMobilityPatternDiamond(uint32_t steps, BoundingBox box);
    static PatternCoordinates GetMobilityPatternX1Period(uint32_t steps, BoundingBox box);
    static PatternCoordinates GetMobilityPatternX2Period(uint32_t steps, BoundingBox box);
    static PatternCoordinates GetMobilityPatternX3Period(uint32_t steps, BoundingBox box);
    static void Test();
};

#endif // NS3_MOBILITYPATTERNS_H
