//
// Created by Gabriel Ferreira (@gabrielcarvfer) on 27/10/22.
//

#include "E2SM-KPM-indication-types.h"

void
E2AP::PeriodicReport(std::string subscriber_endpoint,
                     uint32_t period_ms,
                     std::string subscribed_endpoint)
{
    NS_LOG_FUNCTION(this << subscriber_endpoint << period_ms << subscribed_endpoint);

    auto it = m_endpointPeriodicityAndBuffer.find(subscribed_endpoint);
    NS_ASSERT_MSG(it != m_endpointPeriodicityAndBuffer.end(),
                  "Endpoint " + subscribed_endpoint + " to report periodically was not found");

    NS_LOG_FUNCTION(this << subscribed_endpoint
                         << "#measurements=" + std::to_string(it->second.measurements.size()));

    // Send report
    Json RIC_INDICATION_MESSAGE;
    RIC_INDICATION_MESSAGE["DEST_ENDPOINT"] = subscriber_endpoint;
    RIC_INDICATION_MESSAGE["PAYLOAD"]["SERVICE_MODEL"] = E2SM_KPM;
    RIC_INDICATION_MESSAGE["PAYLOAD"]["TYPE"] = RIC_INDICATION;
    RIC_INDICATION_MESSAGE["PAYLOAD"]["COLLECTION START TIME"] = it->second.collectionStartTime;
    RIC_INDICATION_MESSAGE["PAYLOAD"]["MESSAGE"];
    RIC_INDICATION_MESSAGE["PAYLOAD"]["MESSAGE"]["TYPE"] =
        KPM_INDICATION_FORMAT_1; // todo: complement format fields, this is super non-conformant
    RIC_INDICATION_MESSAGE["PAYLOAD"]["MESSAGE"]["RAN FUNCTION"] = subscribed_endpoint;
    RIC_INDICATION_MESSAGE["PAYLOAD"]["MESSAGE"]["MEASUREMENTS"] = it->second.measurements;
    SendPayload(RIC_INDICATION_MESSAGE);

    // Reschedule report event
    EventId event = Simulator::Schedule(MilliSeconds(period_ms),
                                        &E2AP::PeriodicReport,
                                        this,
                                        subscriber_endpoint,
                                        period_ms,
                                        subscribed_endpoint);
    it->second.eventId = event;
    it->second.measurements.clear();
    it->second.collectionStartTime = SystemWallClockTimestamp().ToString();
}

void
E2AP::HandleE2SmKpmIndicationPayload(std::string& src_endpoint,
                                     std::string& dest_endpoint,
                                     Json& payload)
{
    NS_LOG_FUNCTION(this);

    enum KPM_INDICATION_FORMATS format = payload["MESSAGE"]["TYPE"];
    switch (format)
    {
    case KPM_INDICATION_FORMAT_1: {
        std::string ts = payload["COLLECTION START TIME"];
        std::string subscribed_endpoint = payload["MESSAGE"]["RAN FUNCTION"];
        std::string kpm =
            getSubEndpoint(src_endpoint,
                           subscribed_endpoint); // Remove endpointRoot from full KPM endpoint

        // Retrieve measurements from message
        NS_ASSERT(payload["MESSAGE"].contains("MEASUREMENTS"));
        std::vector<PeriodicMeasurementStruct> measurements = payload["MESSAGE"]["MEASUREMENTS"];

        // Exit early if the message contains no measurements from the previous period
        if (measurements.empty())
            return;
        // Retrieve database storage location (and create it if it doesn't exist)
        auto kpmIt = m_kpmToEndpointStorage.find(kpm);
        if (kpmIt == m_kpmToEndpointStorage.end())
        {
            m_kpmToEndpointStorage.emplace(
                kpm,
                std::map<std::string, std::deque<PeriodicMeasurementStruct>>{});
            kpmIt = m_kpmToEndpointStorage.find(kpm);
        }
        auto measuringE2NodeIt = kpmIt->second.find(src_endpoint);
        if (measuringE2NodeIt == kpmIt->second.end())
        {
            kpmIt->second.emplace(src_endpoint, std::deque<PeriodicMeasurementStruct>{});
            measuringE2NodeIt = kpmIt->second.find(src_endpoint);
        }

        // Insert new measurements in age order (newest to oldest)
        auto existingMeasurementsIt = measuringE2NodeIt->second.begin();
        for (auto newMeasurementIt = measurements.begin(); newMeasurementIt != measurements.end();
             newMeasurementIt++)
        {
            // If this is the end of the list of existing measurements,
            // there is nothing for us to do in this loop
            if (existingMeasurementsIt == measuringE2NodeIt->second.end())
                break;

            // If this isn't the end, we check if the new timestamp is bigger than
            // the existing one, if it is, insert the new measurement and remove it
            // from the list of the new measurements
            std::cout << newMeasurementIt->timestamp << ' ' << existingMeasurementsIt->timestamp
                      << std::endl;
            if (newMeasurementIt->timestamp >= existingMeasurementsIt->timestamp)
            {
                measuringE2NodeIt->second.insert(existingMeasurementsIt, *newMeasurementIt);
                measurements.erase(newMeasurementIt);
                // Instead of jumping to the next existing measurement,
                // we try again in case of duplicate timestamps
                continue;
            }
            existingMeasurementsIt++;
        }

        // If there is still a measurement that hasn't been copied, copy them one in one move
        std::move(begin(measurements), end(measurements), back_inserter(measuringE2NodeIt->second));

        // for(auto& i: measuringE2NodeIt->second)
        //   std::cout << i.timestamp << std::endl;
        // std::cout << "=============" << std::endl;
        //  todo: notify endpoint (e.g. xapps) that fresh data is available
    }
    break;
    case KPM_INDICATION_FORMAT_2:
    case KPM_INDICATION_FORMAT_3:
    default:
        NS_ABORT_MSG("Unsupported KPM indication format");
    }
}
