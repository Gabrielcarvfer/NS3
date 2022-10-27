//
// Created by Gabriel Ferreira (@gabrielcarvfer) on 27/10/22.
//

#include "E2SM-KPM-measurements.h"

namespace ns3
{

    void to_json (Json &j, const MeasurementStruct &p)
    {
      j = Json{{"type",                  p.type},
               {"measurementTimeOffset", p.measurementTimeOffset},
               {"measurement",           p.measurement.uinteger}};
    }
    void from_json (const Json &j, MeasurementStruct &p)
    {
      j.at ("type").get_to (p.type);
      j.at ("measurementTimeOffset").get_to (p.measurementTimeOffset);
      j.at ("measurement").get_to (p.measurement.uinteger);
    }

    void to_json (Json &j, const PeriodicMeasurementStruct &p)
    {
      j = Json{{"timestamp",    p.timestamp},
               {"measurements", p.measurements}};
    }
    void from_json (const Json &j, PeriodicMeasurementStruct &p)
    {
      j.at ("timestamp").get_to (p.timestamp);
      j.at ("measurements").get_to (p.measurements);
    }
}