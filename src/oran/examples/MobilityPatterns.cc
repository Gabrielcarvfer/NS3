// Copyright (c) 2024 Centre Tecnologic de Telecomunicacions de Catalunya (CTTC)
//
// SPDX-License-Identifier: GPL-2.0-only

#include "MobilityPatterns.h"

#include <ns3/fatal-error.h>

#include <algorithm>
#include <cmath>
#include <iostream>

double
GetCoordValue(PatternCoordinates& coordinates, bool min = true, bool x = true)
{
    auto compare = [x](auto a, auto b) { return x ? a.first < b.first : a.second < b.second; };
    std::pair<double, double> ret;
    if (min)
        ret = *std::min_element(coordinates.begin(), coordinates.end(), compare);
    else
        ret = *std::max_element(coordinates.begin(), coordinates.end(), compare);
    return x ? ret.first : ret.second;
}

static const auto patterns = std::vector<std::function<PatternCoordinates(uint32_t, BoundingBox)>>{
    MobilityPatterns::GetMobilityPatternUpwardsTriangle,
    MobilityPatterns::GetMobilityPatternDownwardsTriangle,
    MobilityPatterns::GetMobilityPatternHourglass,
    MobilityPatterns::GetMobilityPatternSquare,
    MobilityPatterns::GetMobilityPatternDiamond,
    MobilityPatterns::GetMobilityPatternX1Period,
    MobilityPatterns::GetMobilityPatternX2Period,
    MobilityPatterns::GetMobilityPatternX3Period,
};

PatternCoordinates
MobilityPatterns::GetMobilityPatternCoordinates(uint32_t steps,
                                                BoundingBox box,
                                                MobilityPatterns::PATTERN_ENUM number)
{
    PatternCoordinates coordinates;
    switch (number)
    {
    case MobilityPatterns::UPWARDS_TRIANGLE:
    case MobilityPatterns::DOWNWARDS_TRIANGLE:
    case MobilityPatterns::HOURGLASS:
    case MobilityPatterns::SQUARE:
    case MobilityPatterns::DIAMOND:
    case MobilityPatterns::X1PERIOD:
    case MobilityPatterns::X2PERIOD:
    case MobilityPatterns::X3PERIOD:
        coordinates = patterns[number](steps, box);
    default:
        break;
    }
    return coordinates;
}

PatternCoordinates
MobilityPatterns::GetMobilityPatternUpwardsTriangle(uint32_t steps, BoundingBox box)
{
    PatternCoordinates coordinates(steps, {0.0, 0.0});
    double side = box.GetShortestLength();

    coordinates[0].first = box.xMin;
    coordinates[0].second = box.yMin;
    double cos60 = cos(M_PI / 3);
    double sin60 = sin(M_PI / 3);
    double step_size = 3 * side / steps;
    int steps_per_side = steps / 3;
    /*
      0 /\ 1
       /  \
       ----
         2
     */
    for (uint32_t step = 1; step < steps; step++)
    {
        switch ((int)(step / steps_per_side))
        {
        case 0:
            coordinates[step].first = coordinates[step - 1].first + step_size * cos60;
            coordinates[step].second = coordinates[step - 1].second + step_size * sin60;
            break;
        case 1:
            coordinates[step].first = coordinates[step - 1].first + step_size * cos60;
            coordinates[step].second = coordinates[step - 1].second - step_size * sin60;
            break;
        case 2:
            coordinates[step].first = coordinates[step - 1].first - step_size;
            coordinates[step].second = coordinates[step - 1].second;
            break;
        default:
            NS_FATAL_ERROR("Incorrect case");
        }
    }
    return coordinates;
}

PatternCoordinates
MobilityPatterns::GetMobilityPatternDownwardsTriangle(uint32_t steps, BoundingBox box)
{
    /*
     * Create upwards triangle
     *  0 /\ 1
     *   /  \
     *   ----
     *     2
     */
    auto coordinates = GetMobilityPatternUpwardsTriangle(steps, box);
    /*
     * Rotate triangle horizontally
     * 1 /\ 0
     *  /  \
     *  ----
     *   2
     */
    std::reverse(coordinates.begin(), coordinates.end());
    /*
     * Rotate triangle vertically
     *   2
     *  ----
     *  \  /
     * 1 \/ 0
     */
    std::transform(coordinates.begin(), coordinates.end(), coordinates.begin(), [box](auto a) {
        a.second = box.yMax - a.second;
        return a;
    });
    return coordinates;
}

PatternCoordinates
MobilityPatterns::GetMobilityPatternHourglass(uint32_t steps, BoundingBox box)
{
    PatternCoordinates coordinates(steps, {0.0, 0.0});
    double cos60 = cos(M_PI / 3);
    double sin60 = sin(M_PI / 3);
    double side = box.GetShortestLength() * (1 / sin60) / 2;

    coordinates[0].first = box.xMin + (box.GetXLength() - side) / 2;
    coordinates[0].second = box.yMin;
    double step_size = 6 * side / steps;
    int steps_per_side = steps / 6;
    for (uint32_t step = 1; step < steps; step++)
    {
        switch ((int)(step / steps_per_side))
        {
        case 0:
            coordinates[step].first = coordinates[step - 1].first + step_size;
            coordinates[step].second = coordinates[step - 1].second;
            break;
        case 1:
        case 2:
            coordinates[step].first = coordinates[step - 1].first - step_size * cos60;
            coordinates[step].second = coordinates[step - 1].second + step_size * sin60;
            break;
        case 3:
            coordinates[step].first = coordinates[step - 1].first + step_size;
            coordinates[step].second = coordinates[step - 1].second;
            break;
        case 4:
        case 5:
            coordinates[step].first = coordinates[step - 1].first - step_size * cos60;
            coordinates[step].second = coordinates[step - 1].second - step_size * sin60;
            break;
        default:
            NS_FATAL_ERROR("Incorrect case");
        }
    }

    return coordinates;
}

PatternCoordinates
MobilityPatterns::GetMobilityPatternSquare(uint32_t steps, BoundingBox box)
{
    PatternCoordinates coordinates(steps, {0.0, 0.0});
    coordinates[0].first = box.xMin;
    coordinates[0].second = box.yMin;
    double side = box.GetShortestLength();
    double step_size = 4 * side / steps;
    int steps_per_side = steps / 4;
    /*
     *       1
     *    +-----+
     *    |     |
     *  0 |     | 2
     *    +-----+
     *       3
     */
    for (uint32_t step = 1; step < steps; step++)
    {
        switch ((int)(step / steps_per_side))
        {
        case 0:
            coordinates[step].first = coordinates[step - 1].first;
            coordinates[step].second = coordinates[step - 1].second + step_size;
            break;
        case 1:
            coordinates[step].first = coordinates[step - 1].first + step_size;
            coordinates[step].second = coordinates[step - 1].second;
            break;
        case 2:
            coordinates[step].first = coordinates[step - 1].first;
            coordinates[step].second = coordinates[step - 1].second - step_size;
            break;
        case 3:
            coordinates[step].first = coordinates[step - 1].first - step_size;
            coordinates[step].second = coordinates[step - 1].second;
            break;
        default:
            NS_FATAL_ERROR("Incorrect case");
        }
    }
    return coordinates;
}

PatternCoordinates
MobilityPatterns::GetMobilityPatternDiamond(uint32_t steps, BoundingBox box)
{
    PatternCoordinates coordinates(steps, {0.0, 0.0});
    double cos60 = cos(M_PI / 3);
    double sin60 = sin(M_PI / 3);
    double side = box.GetShortestLength() * (1 / sin60) / 2;

    coordinates[0].first = (box.xMax - box.xMin) / 2;
    coordinates[0].second = 0;
    double step_size = 4 * side / steps;
    int steps_per_side = steps / 4;
    for (uint32_t step = 1; step < steps; step++)
    {
        switch ((int)(step / steps_per_side))
        {
        case 0:
            coordinates[step].first = coordinates[step - 1].first - step_size * cos60;
            coordinates[step].second = coordinates[step - 1].second + step_size * sin60;
            break;
        case 1:
            coordinates[step].first = coordinates[step - 1].first + step_size * cos60;
            coordinates[step].second = coordinates[step - 1].second + step_size * sin60;
            break;
        case 2:
            coordinates[step].first = coordinates[step - 1].first + step_size * cos60;
            coordinates[step].second = coordinates[step - 1].second - step_size * sin60;
            break;
        case 3:
            coordinates[step].first = coordinates[step - 1].first - step_size * cos60;
            coordinates[step].second = coordinates[step - 1].second - step_size * sin60;
            break;
        default:
            NS_FATAL_ERROR("Incorrect case");
        }
    }
    return coordinates;
}

PatternCoordinates
GetMobilityPatternNPeriods(uint32_t steps, BoundingBox box, uint16_t periods = 2)
{
    PatternCoordinates coordinates(steps, {0.0, 0.0});

    double period_per_trip = periods / 2.0;
    int steps_per_trip = steps / 2;
    double angle_per_step = period_per_trip * 2 * M_PI / steps_per_trip;

    // Left-to-right trip
    for (auto step = 1; step < steps_per_trip; step++)
    {
        coordinates[step].first = coordinates[step - 1].first + abs(sin(step * angle_per_step));
        coordinates[step].second = coordinates[step - 1].second + cos(step * angle_per_step);
    }
    // Right-to-left trip
    for (auto step = steps_per_trip; step < steps_per_trip * 2; step++)
    {
        coordinates[step].first = coordinates[step - 1].first - abs(sin(step * angle_per_step));
        coordinates[step].second = coordinates[step - 1].second + cos(step * angle_per_step);
    }
    // Figure out maximum dimensions of the figure and rescale to fit the bounding box
    double yMax = GetCoordValue(coordinates, false, false);
    double yMin = GetCoordValue(coordinates, true, false);
    double xMax = GetCoordValue(coordinates, false, true);
    std::transform(coordinates.begin(),
                   coordinates.end(),
                   coordinates.begin(),
                   [box, xMax](auto a) {
                       a.first = a.first * box.xMax / xMax;
                       return a;
                   });
    std::transform(coordinates.begin(),
                   coordinates.end(),
                   coordinates.begin(),
                   [box, yMin, yMax](auto a) {
                       a.second = (a.second - yMin) * box.xMax / (yMax - yMin);
                       return a;
                   });
    return coordinates;
}

PatternCoordinates
MobilityPatterns::GetMobilityPatternX1Period(uint32_t steps, BoundingBox box)
{
    return GetMobilityPatternNPeriods(steps, box, 1);
}

PatternCoordinates
MobilityPatterns::GetMobilityPatternX2Period(uint32_t steps, BoundingBox box)
{
    return GetMobilityPatternNPeriods(steps, box, 2);
}

PatternCoordinates
MobilityPatterns::GetMobilityPatternX3Period(uint32_t steps, BoundingBox box)
{
    return GetMobilityPatternNPeriods(steps, box, 3);
}

void
MobilityPatterns::Test()
{
    int steps = 120;
    auto boundaries = BoundingBox(0, 100, 0, 100);
    auto filename = "mobility_patterns.json";
    auto os = std::ofstream(filename);
    while (!os.is_open())
    {
        os.open(filename);
    }
    os << "{\n";
    os << "  \"mobilityPatterns\" : [\n";
    for (size_t i = 0; i < patterns.size(); i++)
    {
        os << "    {\n";
        auto coordinates = patterns[i](steps, boundaries);
        os << "      \"x\" : [";
        for (size_t j = 0; j < coordinates.size(); j++)
        {
            os << coordinates[j].first;
            if (j != coordinates.size() - 1)
                os << ",";
        }
        os << "],\n";
        os << "      \"y\" : [";
        for (size_t j = 0; j < coordinates.size(); j++)
        {
            os << coordinates[j].second;
            if (j != coordinates.size() - 1)
                os << ",";
        }
        os << "]\n";
        os << "    }";
        if (i != patterns.size() - 1)
            os << ",";
        os << "\n";
    }
    os << "  ]\n";
    os << "}\n";
    os.close();
}
