---
layout: page
title: ns3-ORAN
permalink: /ns3_ORAN/
---

## What is it?
ns3-ORAN is a straightforward implementation of the [Open-RAN](https://orandownloadsweb.azurewebsites.net/specifications) 
focusing on ease-of-use and development speed of xApps and integration with the ns-3 simulator. 

Not to be confused with [ns3-o-ran-e2](https://github.com/o-ran-sc/sim-ns3-o-ran-e2), 
which is developed by the folks from Northeastern University and is interoperable with the O-RAN Software Community RIC.

It has enough functionality to develop more E2 Service Models for Key-Performance Metrics (KPM) and RAN Control (RC). 
The currently included KPMs are the ones specified by the 3GPP as the necessary information for the Handover Control,
which is also implemented as a E2SM RC service.

## How to cite?
Paper under peer review.

## How to install?
The first step is cloning the [NS3.37-oran](https://github.com/Gabrielcarvfer/NS3/tree/NS3.37-oran).

As in the installation instructions for the 
[Quick-Start section of the ns-3 documentation](https://www.nsnam.org/docs/release/3.37/tutorial/html/quick-start.html#prerequisites), 
before proceeding you will need at least g++, ninja, cmake.

To build some features, you will also need to install [MlPack](https://www.mlpack.org/).

After downloading and installing these tools, 
configure ns-3 normally then run the example you want,
for example, `HandoverXappsScenario`.
```
./ns3 configure --enable-examples
./ns3 build
./ns3 run HandoverXappsScenario
```

## How to use?
An example is provided in the src/oran/example folder (`HandoverXappsScenario.cc`).

This example runs a simulation with different strategies of handover triggering (when to evaluate a handover decision)
and handover decision (to which cell the UE should be handed-over).

You can specify which simulation scenario you want to run:
- Scenario 0: 3GPP standard handover (triggering + decision)
- O-RAN handovers:
  - Scenario 1: standard 3GPP triggering + RIC bypass (forwarding the eNB decision back to itself)
  - Scenario 2: standard 3GPP triggering + RIC xApp using a K-Means policy for handover decision
  - Scenario 3: RIC xApp using a K-Means policy for handover triggering and decision
  - Scenario 4: standard 3GPP triggering + RIC xApp using a MaxRsrq policy for handover decision
  - Scenario 5: RIC xApp using a MaxRsrq policy for handover triggering and decision

### Simulation scenarios

#### Scenario 0

In the scenario 0, we have the standard handover, where the associated eNB will
decide which target cell it will hand the UE over. The triggering and decision can be done via
the A2A4 or A3 policies implemented in the ns-3 simulator, which are based on standard events
A2, A3 and A4, based on received power and SINR measurements from nearby cells, all defined by 3GPP.

The handover command can go through the X2 interface (connecting to the target eNB) or 
S1 interface (connecting to the MME), depending on the access network layout. 

The sequence diagram is very simple.

[![](https://mermaid.ink/img/pako:eNo1UD1rAzEM_StC83VIRg-BlGbIkAz52AzF2LqcIbYuOrmlhPz3-hxOGp7E09fTEz0HQoMTPQplT1_R3cQlm6EaHT9XH5tNhbWBszpR0IFgcDnwDwmMwp5CEYKepVHXHfxGHeB0vOxr8t2wF06NneeB8hKvbV4cO0wkycVQb3nO2y3WqkQWTQ3v8Taoxe5NpCjCsvXKMs187-4T2fyqQ1xRPv9lj0alUIdlDE4XUWhaZYcUYu09vJW3B7z-AbcNWOw?type=png)](https://mermaid.live/edit#pako:eNo1UD1rAzEM_StC83VIRg-BlGbIkAz52AzF2LqcIbYuOrmlhPz3-hxOGp7E09fTEz0HQoMTPQplT1_R3cQlm6EaHT9XH5tNhbWBszpR0IFgcDnwDwmMwp5CEYKepVHXHfxGHeB0vOxr8t2wF06NneeB8hKvbV4cO0wkycVQb3nO2y3WqkQWTQ3v8Taoxe5NpCjCsvXKMs187-4T2fyqQ1xRPv9lj0alUIdlDE4XUWhaZYcUYu09vJW3B7z-AbcNWOw)

#### Scenarios 1, 2 and 4 

These scenarios have the handovers triggered by the eNBs, but the decisions are intermediated by the RIC.

In the scenario 1, the RIC only accepts the suggested decision made by the eNB, sending back a control request
that only really forwards back the decision. This is done when there is no xApp associated with a given service,
in this case the (unconditional) Handover Control service.

In the scenarios 2 and 4, the RIC forwards the suggested decision to the associated handover xApps, which
reform the suggestion made by the source eNB. The handover xApps can also reject the handover control request,
interrupting the process and keeping the UE connected to the source eNB for longer.

All of these cases are shown in the following sequence diagram.

[![](https://mermaid.ink/img/pako:eNrdVd9v2jAQ_ldOeaYP6yMalSjJ1EglbCFMmoQ0GecI3hI7sw0MVf3fd5cf0CKhUu1lWpCIY3_3-e67O_spkCbHYBg4_LVFLTFUorCiWmqgB5P7Dzd3d2k8GUJmVVGgdfAgdG52aMGhzpUuQMDHlb2LbsefgZAQJ2E8GWfxLOHpCp0TBYI02gulW7zlzZyH6HY-vUknjEuTLB4tou_8br6ZSTu0Hub-UCJkhxpHk1mSRJMsCmE6CyP6u48f4-wb0HyWzh7ZsDOKyTcpvDIa4nD0ME7C2dco7YGQRl8W0TxrwxQl4degDfwe1zV5Vyjn0WJOrhLZTkkEirU2SnuQoixXQv5sTfkhV3uRxlJi7R0LB25LernGg7Wx4DcIXtgCiQLL8tycpT7ZM5gVs6Y8iqVOEV1Q_iy4i_KfM7-RhkkHf18eequxvJSEnj9EqRxhRm30XemVDjkp4v05aQVlsyF8MnYvbN4I2ofrTffpaiTndthusVOimz9u9ZqXUX2i57T3K1JmM1R6p7xyVaX4g7Z4K58nm_N6uM4eVoe_LYl_rRTawE_CNOVwXXdcVvPK7vr_1HzZWI2aOu-6jAft0NR8aFLJk9BvCLQXDkRDST1CajGc9nvB394b9LqlVqFTzzeYTX9z1NZIzLcWjyfjIoK98htgeaCTCdbWVM0q8_Vty6SvnOdfMAgqtJVQOV1lT7y8DAhc4TIY0rBUxcYvg0G7UClrjSX5jHW8vhYl9-0zkYitN_ODlsHQ2y0Ogm2dC9_ficGwQQ4CzBXZTtuLs7k_n_8A53ZiQQ?type=png)](https://mermaid.live/edit#pako:eNrdVd9v2jAQ_ldOeaYP6yMalSjJ1EglbCFMmoQ0GecI3hI7sw0MVf3fd5cf0CKhUu1lWpCIY3_3-e67O_spkCbHYBg4_LVFLTFUorCiWmqgB5P7Dzd3d2k8GUJmVVGgdfAgdG52aMGhzpUuQMDHlb2LbsefgZAQJ2E8GWfxLOHpCp0TBYI02gulW7zlzZyH6HY-vUknjEuTLB4tou_8br6ZSTu0Hub-UCJkhxpHk1mSRJMsCmE6CyP6u48f4-wb0HyWzh7ZsDOKyTcpvDIa4nD0ME7C2dco7YGQRl8W0TxrwxQl4degDfwe1zV5Vyjn0WJOrhLZTkkEirU2SnuQoixXQv5sTfkhV3uRxlJi7R0LB25LernGg7Wx4DcIXtgCiQLL8tycpT7ZM5gVs6Y8iqVOEV1Q_iy4i_KfM7-RhkkHf18eequxvJSEnj9EqRxhRm30XemVDjkp4v05aQVlsyF8MnYvbN4I2ofrTffpaiTndthusVOimz9u9ZqXUX2i57T3K1JmM1R6p7xyVaX4g7Z4K58nm_N6uM4eVoe_LYl_rRTawE_CNOVwXXdcVvPK7vr_1HzZWI2aOu-6jAft0NR8aFLJk9BvCLQXDkRDST1CajGc9nvB394b9LqlVqFTzzeYTX9z1NZIzLcWjyfjIoK98htgeaCTCdbWVM0q8_Vty6SvnOdfMAgqtJVQOV1lT7y8DAhc4TIY0rBUxcYvg0G7UClrjSX5jHW8vhYl9-0zkYitN_ODlsHQ2y0Ogm2dC9_ficGwQQ4CzBXZTtuLs7k_n_8A53ZiQQ)

#### Scenarios 3 and 5

In the scenarios 3 and 5, the handover xApps periodically checks for the reported KPMs and decide
by itself when to trigger a handover from one cell to another. When that happens,
the control request is sent by the RIC to the source cell, for it to initiate the handover process.
For that to work, we need to disable the handover triggering algorithm in the eNB, making it
completely clueless regarding the handover necessity.

These cases are shown in the following sequence diagram.

[![](https://mermaid.ink/img/pako:eNqtkkFP8zAMhv-KlfM4sGMFk_ptlagEHXQdp0oopF4b0cbFSfmYEP-dJNVAAokTySFObb9-3PhNKGpQJMLi84RG4UbLluVQG_CrJxphNsN6TcfxbLUKRwK3yJoarWTfH0F1qJ7gQHzxyCvopGnoBRloHIndZLTTaH_olPk6gYp12yJbuDol_deuAwmKjGPqgQOYdaBNKOY0GRjQWtkihGLZMr0FrwR5scnXaZVvi_A5ZEtttGnBdfgpki13N2flOkSURZVf7rOHcIb7VVpstvdZCettUZXbayizu322q76wfRVPjcW_8wRSpXB0Nor_Qvp4BIv-6jFkxP7J_a3c38DHGC--QaWtB7mceb96CV3MzSwT2DnJLpb6fLmRSWEzMcYHpUP07rOIHh_oOwEcmIYYFaTB0clezkX9X6jNvMVCDMiD1I2fu7fgroUPHrAWiTd73XauFovZMWhm4lQ5Yhv8B9lbrM27F5GTo93RKJE4nnAhprGR7jTAIomRC4GN9rk385THYX__AGMR-Jo?type=png)](https://mermaid.live/edit#pako:eNqtkkFP8zAMhv-KlfM4sGMFk_ptlagEHXQdp0oopF4b0cbFSfmYEP-dJNVAAokTySFObb9-3PhNKGpQJMLi84RG4UbLluVQG_CrJxphNsN6TcfxbLUKRwK3yJoarWTfH0F1qJ7gQHzxyCvopGnoBRloHIndZLTTaH_olPk6gYp12yJbuDol_deuAwmKjGPqgQOYdaBNKOY0GRjQWtkihGLZMr0FrwR5scnXaZVvi_A5ZEtttGnBdfgpki13N2flOkSURZVf7rOHcIb7VVpstvdZCettUZXbayizu322q76wfRVPjcW_8wRSpXB0Nor_Qvp4BIv-6jFkxP7J_a3c38DHGC--QaWtB7mceb96CV3MzSwT2DnJLpb6fLmRSWEzMcYHpUP07rOIHh_oOwEcmIYYFaTB0clezkX9X6jNvMVCDMiD1I2fu7fgroUPHrAWiTd73XauFovZMWhm4lQ5Yhv8B9lbrM27F5GTo93RKJE4nnAhprGR7jTAIomRC4GN9rk385THYX__AGMR-Jo)


### I've run the example, now what?

You should have a .csv file in the directory, containing a list of handover-related events tracked.

```
Time (ns),IMSI,SrcCellId,RNTI,TrgtCellId,Type,
20214285,1,1,1,1,CONNECTION_ESTABLISHED_UE,
20214285,2,1,4,1,CONNECTION_ESTABLISHED_UE,
20214285,3,1,3,1,CONNECTION_ESTABLISHED_UE,
20214285,5,1,2,1,CONNECTION_ESTABLISHED_UE,
20214285,1,1,1,1,CONNECTION_ESTABLISHED_ENB,
20214285,2,1,4,1,CONNECTION_ESTABLISHED_ENB,
20214285,3,1,3,1,CONNECTION_ESTABLISHED_ENB,
20214285,5,1,2,1,CONNECTION_ESTABLISHED_ENB,
25214285,4,1,6,1,CONNECTION_ESTABLISHED_UE,
25214285,6,1,5,1,CONNECTION_ESTABLISHED_UE,
25214285,4,1,6,1,CONNECTION_ESTABLISHED_ENB,
25214285,6,1,5,1,CONNECTION_ESTABLISHED_ENB,
24680001161,4,1,6,2,HANDOVER_START_ENB,
24680001161,4,1,6,2,HANDOVER_START_UE,
24684214285,4,2,1,2,HANDOVER_OK_UE,
24684214484,4,2,1,2,HANDOVER_OK_ENB,
33000001161,6,1,5,2,HANDOVER_START_ENB,
33000001161,6,1,5,2,HANDOVER_START_UE,
33004214285,6,2,2,2,HANDOVER_OK_UE,
33004214484,6,2,2,2,HANDOVER_OK_ENB,
49680001161,3,1,3,2,HANDOVER_START_ENB,
49680001161,3,1,3,2,HANDOVER_START_UE,
49684214285,3,2,3,2,HANDOVER_OK_UE,
49684214484,3,2,3,2,HANDOVER_OK_ENB,
66160001161,4,2,1,3,HANDOVER_START_ENB,
66160001161,4,2,1,3,HANDOVER_START_UE,
66164214285,4,3,1,3,HANDOVER_OK_UE,
66164214484,4,3,1,3,HANDOVER_OK_ENB,
98120001161,6,2,2,3,HANDOVER_START_ENB,
```

We can aggregate these results from a bunch of different simulations using the same strategies,
and get some statistical confidence and margins of errors.

After that, we can consolidate all of these results into a single spreadsheet comparing the
handover performance in the different scenarios.

There is a script for that, that will also launch the examples (HandoverScenarioCompanion.py).

In the end, we should have some stats for the handover.

![](/NS3/img/oran/handoverScenarioStats.png)


## How to implement new services?

### How to implement new Key Performance Metric (E2SM KPM) services?

First go to `src/oran/model/E2SM-KPM-measurements.h` and mark your KPM as `IMPLEMENTED`.

This will result in eNB publishing that KPM endpoint during the `E2AP::RegisterDefaultEndpoints ()`
call. This will also result in the RIC (`/E2Node/0/`) subscribing to that registered endpoint
during the `SubscribeToDefaultEndpoints` call. The subscription will ensure the RIC receives 
said KPM periodically and stores it for later use by the RIC itself or its xApps.

KPMs are stored in the RIC and can be queried with the following code block:

```
E2AP* ric = (E2AP*)static_cast<const E2AP*>(xApp::RetrieveInstanceWithEndpoint("/E2Node/0"));
auto metricMap = ric->QueryKpmMetric(kpmMetric); // e.g. /KPM/HO.SrcCellQual.RSRQ

// Skip if no measurements
if (metricMap.size() == 0)
{
    return;
}

for (auto& e2nodeMeasurements : metricMap)
{
   // Measurements pack
   // e2NodeMeasurements.first the measuring endpoint (e.g. /E2Node/2)
   // e2NodeMeasurements.second is deque of PeriodicMeasurementStruct
   for (auto& entry : e2nodeMeasurements.second)
   {
     // Individual measurements 
     entry.timestamp is a wallclock timestamp
     entry.entry is a Json object containing the measurements
     // The parameters of said measurements are defined by 3GPP
     // for the /KPM/Ho.SrcCellQual.RSRQ we have
     auto rnti = entry.measurements["RNTI"];
     auto primaryCellID = entry.measurements["CELLID"];
     auto rsrq = entry.measurements["VALUE"];
   }
}
```

To publish the new KPMs, you need to find the spot where KPM is collected in the 3GPP architecture
and create a block similar to the one below, used to collect these metrics.

The metrics collected for the handover are collected in `src/lte/model/lte-enb-rrc.cc`,
more specifically in the `UeManager::RecvMeasurementReport`.

```
// Retrieve node associated to the current eNB
auto node = m_rrc->GetNode();
// Retrieve the E2AP application
if (node->GetNApplications() > 1)
{
    auto app = node->GetApplication(1);
    Ptr<oran::E2AP> e2ap = DynamicCast<oran::E2AP>(app);
    // If the application exists, publish the measurements to 
    // the subscribers of the endpoint
    if (e2ap)
    {
        Json json;
        json["MEASID"] = msg.measResults.measId;
        json["RNTI"] = m_rnti;
        json["CELLID"] = m_sourceCellId; // starts counting from 1
        json["VALUE"] = msg.measResults.measResultPCell.rsrpResult;
        e2ap->PublishToEndpointSubscribers("/KPM/HO.SrcCellQual.RSRP", json);
        json["VALUE"] = msg.measResults.measResultPCell.rsrqResult;
        e2ap->PublishToEndpointSubscribers("/KPM/HO.SrcCellQual.RSRQ", json);
        for (auto& cell : msg.measResults.measResultListEutra)
        {
            if (cell.haveRsrpResult)
            {
                json["VALUE"] = cell.rsrpResult;
                json["TARGET"] = cell.physCellId; // starts counting from 1
                e2ap->PublishToEndpointSubscribers("/KPM/HO.TrgtCellQual.RSRP", json);
            }
            if (cell.haveRsrqResult)
            {
                json["VALUE"] = cell.rsrqResult;
                json["TARGET"] = cell.physCellId; // starts counting from 1
                e2ap->PublishToEndpointSubscribers("/KPM/HO.TrgtCellQual.RSRQ", json);
            }
        }
    }
}
```

The `PublishToEndpointSubscribers` won't actually send the information right away, 
but will buffer those measurements in `E2AP::m_endpointPeriodicityAndBuffer`,
which is flushed periodically according to the subscriber periodicity requirements.

### How to implement new RAN Control (E2SM RC) services?

To implement new services, you need a new xApp. And creating a new xApp is
pretty easy.

Let's look at the xAppHandover example.

```
// The new xApp should inherit the xApp class, which will connect it to the RIC
xAppHandover::xAppHandover()
    : xApp()
{
    // Service endpoints callbacks are registered here. HO is the unconditional handover.
    RegisterEndpointCallback(
        "/Action/HO",
        std::bind(&xAppHandover::HandoverDecision, this, std::placeholders::_1));
}

xAppHandover::~xAppHandover()
{
    // Remember to add this to remove the callback when the object is destroyed,
    // if you plan on changing handlers during the runtime
    RemoveEndpointCallback("/Action/HO");
}

// The function that actually implements the xApp policy
// It receives a json payload and modifies it to output any decisions
// So always pass a reference or pointer
void
xAppHandover::HandoverDecision(Json& payload)
{
    NS_LOG_FUNCTION(this);

    // Check if we are not receiving invalid payloads
    if (xApp::RetrieveInstanceWithEndpoint(GetRootEndpoint())->GetNode() !=
        xApp::RetrieveInstanceWithEndpoint("/E2Node/0")->GetNode())
    {
        NS_ABORT_MSG("Trying to run a xApp on a E2Node is a no-no");
    }
    // Read inputs from the json
    // uint16_t rnti = payload["RNTI"];
    uint16_t targetCellId = payload["Target Primary Cell ID"];

    // Do the processing
    // todo: implement some fancy logic

    // Then write the outputs to the json
    payload["Target Primary Cell ID"] = targetCellId;
}
```

With the xApp ready, we need to add the proper handler in `src/oran/model/E2SM-RC.cc`.

As an example, let's see the handover handler.

```
case RIC_INSERT_SERVICE_STYLES::CONNECTED_MODE_MOBILITY_CONTROL_REQUEST::
    HANDOVER_CONTROL_REQUEST::VALUE: 
    {
        // RAN parameters from 8.4.4.1
        if (!payload["MESSAGE"].contains("Target Primary Cell ID"))
        {
            // todo: send RIC_CONTROL_FAILURE
            return;
        }
        // UE wants to switch to a different cell
        uint16_t ueToHandover = indicationHeader.contents.format_2.RNTI;
        uint16_t requestedTargetCell = payload["MESSAGE"]["Target Primary Cell ID"];
    
        // Measure time spent on xApp
        auto startTimeXapp = std::chrono::high_resolution_clock::now();
    
        // Set target cell to the requested by default
        uint16_t targetCell = requestedTargetCell;
        
        // If there is a registered xApp handler for this service, retrieve it
        std::function<void(Json&)> handoverHandler = GetEndpointCallback("/Action/HO");
        if (handoverHandler)
        {
            // Prepare the arguments to the handler
            Json temp;
            temp["RNTI"] = ueToHandover;
            temp["Target Primary Cell ID"] = requestedTargetCell;
            // Call the xApp handler callback
            handoverHandler(temp);
            // Recover the decision taken
            targetCell = temp["Target Primary Cell ID"];
        }
        // Measure time spent on xApp
        auto endTimeXapp = std::chrono::high_resolution_clock::now();
        uint64_t nsDelayXapp = std::chrono::duration_cast<std::chrono::nanoseconds>(
                                   endTimeXapp - startTimeXapp)
                                   .count();
    
        // Send CONNECTED_MODE_MOBILITY_CONTROL::HANDOVER_CONTROL
        E2SmRcSendHandoverControl(rnti, targetCell, src_endpoint, nsDelayXapp);
    }
```

Now we need to assemble the E2AP message containing the control request.

```
void
E2AP::E2SmRcSendHandoverControl(uint16_t rnti,
                                uint16_t targetCell,
                                std::string& destination_endpoint,
                                double xAppDelayNs)
{
    // Send CONNECTED_MODE_MOBILITY_CONTROL::HANDOVER_CONTROL
    E2SM_RC_RIC_CONTROL_HEADER hdr;
    hdr.format = ns3::oran::RC_CONTROL_HEADER_FORMAT_1;
    hdr.contents.format_1.RNTI = rnti;
    hdr.contents.format_1.RICControlStyleType =
        RIC_CONTROL_SERVICE_STYLES::CONNECTED_MODE_MOBILITY_CONTROL::VALUE;
    hdr.contents.format_1.ControlActionID =
        RIC_CONTROL_SERVICE_STYLES::CONNECTED_MODE_MOBILITY_CONTROL::HANDOVER_CONTROL::VALUE;
    hdr.contents.format_1.RicDecision =
        targetCell != std::numeric_limits<uint16_t>::max() ? RC_ACCEPT : RC_REJECT;
    Json json_hdr;
    to_json(json_hdr, hdr);

    Json HANDOVER_CONTROL_MSG;
    HANDOVER_CONTROL_MSG["DEST_ENDPOINT"] = destination_endpoint;
    HANDOVER_CONTROL_MSG["PAYLOAD"]["TYPE"] = RIC_CONTROL_REQUEST;
    HANDOVER_CONTROL_MSG["PAYLOAD"]["SERVICE_MODEL"] = E2SM_RC;
    HANDOVER_CONTROL_MSG["PAYLOAD"]["HEADER"] = json_hdr;
    HANDOVER_CONTROL_MSG["PAYLOAD"]["MESSAGE"]["Target Primary Cell ID"] = targetCell;

    // Send indication with control request with delay to account for the xApp processing time
    Simulator::Schedule(NanoSeconds(xAppDelayNs), &E2AP::SendPayload, this, HANDOVER_CONTROL_MSG);
}
```

Now we have all components to receive a RC control request indication and send back a control request response.

But we don't have the code to send the control request indication.

To do that, we need to look where the associated process to the service we want to implement gets initiated.

In the handover case, it is in `src/lte/model/lte-enb-rrc.cc`, more specifically in `LteEnbRrc::DoTriggerHandover`,
where we can add a block to send the control request indication and re-schedule the function to simulate a timer.

```
// As with the KPM part, retrieve the E2AP application
auto node = GetNode();
if (node->GetNApplications() > 1)
{
    auto app = node->GetApplication(1);
    Ptr<oran::E2AP> e2ap = DynamicCast<oran::E2AP>(app);
    if (e2ap)
    {
        // We are going to send a control request indication,
        // until it is answered, we are going to receive an empty answer
        
        // Control returns empty optional if unanswered, or a response
        std::optional<uint16_t> ricTargetCellId =
            e2ap->E2SmRcHandoverControl(rnti, targetCellId, *this);
        if (!ricTargetCellId.has_value())
        {
            // In case there is no response, 
            // reschedule function to wait for the response
            Simulator::Schedule(MilliSeconds(10),
                                &LteEnbRrc::DoTriggerHandover,
                                this,
                                rnti,
                                targetCellId);
            return;
        }
        else
        {
            // Get the response value
            targetCellId = ricTargetCellId.value();

            // Check if the request was cancelled by the RIC (max value)
            if (targetCellId == std::numeric_limits<uint16_t>::max())
            {
                return;
            }
            // Proceed to the handover initialization to 
            // the newly-received target cell, as decided by the RIC
        }
    }
}
// pre-existing code that initiates the handover execution
ueManager->PrepareHandover(targetCellId);
```

With this, we have all the pieces in place for our new xApp implementing a E2SM RC service.

Back to the xApp, we can change the handler to use additional metrics for their decision, 
or use metrics to train machine learning algorithms that implement new policies.

## Video

TODO

## Acknowledgments

This work was partially funded by ANATEL via OpenRAN workgroup scholarships.
