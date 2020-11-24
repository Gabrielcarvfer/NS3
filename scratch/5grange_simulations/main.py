import os
import shutil
import multiprocessing
from enum import Enum
import json
import glob
import lzma
import pickle
import numpy
import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter
import scipy.stats as st

from simulation_model.simulation_scenario_generation import generate_scenarios
from simulation_execution.execute_simulation import execute_simulation


class freqBands(Enum):
    MHz850 = 5
    MHz713 = 12
    MHz525 = 101
    MHz240 = 100

class mimoModes(Enum):
    SISO = 0
    TxDiversity = 1
    SpatialMultiplexing = 2

class simulationCase(Enum):
    VOIP_BASE_SCENARIO            = 1<<0,
    WEB_BASE_SCENARIO             = 1<<1,
    STREAMING_BASE_SCENARIO       = 1<<2,
    VIDEOCONFERENCE_BASE_SCENARIO = 1<<3,
    BACKHAUL_BASE_SCENARIO        = 1<<4,
    IOT_BASE_SCENARIO             = 1<<5,

def setup_simulations(createAndRunScenarios):
    resultsDict = {"scenario": {}}
    numBatches = 25
    numUEs_and_applications = [# core scenarios
        [  2, [simulationCase.VOIP_BASE_SCENARIO, ]],  # two ues talking to each other
        [  3, [simulationCase.WEB_BASE_SCENARIO, ]],   # three ues connecting to the internet
        [ 20, [simulationCase.VOIP_BASE_SCENARIO,  simulationCase.WEB_BASE_SCENARIO]],  # 30%/70% of ues for voip/web
        [ 50, [simulationCase.VOIP_BASE_SCENARIO,  simulationCase.WEB_BASE_SCENARIO]],  # 30%/70% of ues for voip/web
        [100, [simulationCase.VOIP_BASE_SCENARIO,  simulationCase.WEB_BASE_SCENARIO]],  # 30%/70% of ues for voip/web
        [ 20, [simulationCase.VOIP_BASE_SCENARIO,  simulationCase.WEB_BASE_SCENARIO, simulationCase.STREAMING_BASE_SCENARIO]],  # 30%/70%/10% of ues for voip/web/video
        [ 50, [simulationCase.VOIP_BASE_SCENARIO,  simulationCase.WEB_BASE_SCENARIO, simulationCase.STREAMING_BASE_SCENARIO]],  # 30%/70%/10% of ues for voip/web/video
        [100, [simulationCase.VOIP_BASE_SCENARIO,  simulationCase.WEB_BASE_SCENARIO, simulationCase.STREAMING_BASE_SCENARIO]],  # 30%/70%/10% of ues for voip/web/video
        # e-health,  scenarios
        [  2, [simulationCase.VIDEOCONFERENCE_BASE_SCENARIO, ]],  # two ues talking to each other
        [ 20, [simulationCase.VOIP_BASE_SCENARIO, simulationCase.WEB_BASE_SCENARIO, simulationCase.VIDEOCONFERENCE_BASE_SCENARIO]],  # 30%/70%/5% of ues for voip/web/telemedicine
        [ 50, [simulationCase.VOIP_BASE_SCENARIO, simulationCase.WEB_BASE_SCENARIO, simulationCase.VIDEOCONFERENCE_BASE_SCENARIO]],  # 30%/70%/5% of ues for voip/web/telemedicine
        [100, [simulationCase.VOIP_BASE_SCENARIO, simulationCase.WEB_BASE_SCENARIO, simulationCase.VIDEOCONFERENCE_BASE_SCENARIO]],  # 30%/70%/5% of ues for voip/web/telemedicine
        # iot scenarios
        [ 27, [simulationCase.IOT_BASE_SCENARIO, ]],  # 26 of ues acting as sinks for 100 rural IOT sensors each (a.k.a. traffic of 25k IOT), forwarding data to an aggregator UE
        # backhaul scenario
        [  1, [simulationCase.BACKHAUL_BASE_SCENARIO, ]],
    ]  # 2, 5, 10, 20, 50, 100

    # I'm dumb and worn off. This should be enough
    for i in range(len(numUEs_and_applications)):
        caseApplicationSum = 0
        for app in numUEs_and_applications[i][1]:
            caseApplicationSum += app.value[0]
        # Replace list of scenarios with a bitmap
        numUEs_and_applications[i][1] = caseApplicationSum

    numerology_and_numUEs_threshold = [(0, 0), ]  # (2, 20), (3, 50)]
    dynamic_spectrum_access = [False, True, ]
    if createAndRunScenarios:
        # Copy injected traffic files to baseDir (where the 5g_range_demonstration_json executable is)
        if not os.path.exists("videoconf_workload0_100s.json"):
            print("Make sure to unzip injected_workloads.7z")
            exit(-1)

            shutil.copy("voip_workload0_100s.json", baseDir)
            shutil.copy("web_workload0_100s.json", baseDir)
            shutil.copy("stream_workload0_9mbps_100s.json", baseDir)
            shutil.copy("backhaul_dl_workload0_10s.json", baseDir)
            shutil.copy("backhaul_ul_workload0_10s.json", baseDir)
            shutil.copy("iot_workload0_100s_100nodes.json", baseDir)
            shutil.copy("iot_workload0_100s_300nodes.json", baseDir)
            interleave_videconf_traffic()
            shutil.copy("videoconf_workload0_100s.json", baseDir)

        for (numUes, applications) in numUEs_and_applications:
            for batch in range(numBatches):
                for use_dsa in dynamic_spectrum_access:
                    for numerology, numUesThreshold in numerology_and_numUEs_threshold:
                        if numUes >= numUesThreshold:
                            # Prepare the simulationParameter json files for all simulations
                            generate_scenarios(baseDir,
                                               batch,
                                               numUes,
                                               numerologies=[numerology, ],
                                               ueSpeeds=[0, ],  # 10, 50, 100],
                                               clusteredUes=[False, ],  # True],
                                               dynamicSpectrumAccess=[use_dsa, ],  # True],
                                               markovOptions=[False, True, ],  # True],
                                               harmonicOptions=[False, ],  # True], # not working with attackers
                                               fusionAlgs=[6, ],  # 7, 11, 12, 13],
                                               attackerOptions=[0, ],  # 1, 2, 5],
                                               frequencyBandOptions=[freqBands.MHz713, ],  # 101, 5, 7],
                                               mimoOptions=[mimoModes.TxDiversity, ],  # 0, 1, 2]
                                               simulationCase=applications
                                               )

    # Easier than trying to figure out all directories for the individual simulations is to use glob
    # to find all json files with simulation parameters and pass the list for parallel execution
    simulationParameterFilesList = glob.glob(baseDir+os.sep+"**"+os.sep+"simulationParameters.json", recursive=True)

    thread_parameters = []
    for scenarioJson in simulationParameterFilesList:
        # Before executing anything, we check if the outputs file has been processed for that given scenario
        simulation_path = os.path.dirname(scenarioJson)

        # Run simulation if necessary and try to extract results into a single output file
        #execute_simulation(simulation_path, baseDir)  # run simulations individually
        thread_parameters.append((simulation_path, baseDir))

    # Dispatch simulations
    p = multiprocessing.Pool(processes=12)  # run simulations in parallel
    results = p.starmap(func=execute_simulation, iterable=sorted(thread_parameters, reverse=True))

    # When all simulations have finished, load up their results and apply some statistics/plots
    # Result files were pickled and compressed

def load_raw_results(baseDir):
    # We then proceed by searching for simulationParameters.json and simulationResults.pickle.lzma
    simulationParameterFilesList = glob.glob(baseDir+os.sep+"**"+os.sep+"simulationParameters.json", recursive=True)

    all_simulation_results = {}
    # To avoid reprocessing this, we dump all raw results to a compressed pickle
    raw_results_file = "raw_results.pickle.lzma"
    if not os.path.exists(raw_results_file):
        for scenarioJson in simulationParameterFilesList:
            # load each pair of parameters and results
            simulation_parameters = None
            with open(scenarioJson, "r") as file:
                simulation_parameters = json.load(file)
            simulation_results = None
            with lzma.open(os.path.dirname(scenarioJson) + os.sep + "simulationResults.pickle.lzma", "rb") as file:
                simulation_results = pickle.load(file)

            scenarioJson = scenarioJson[len(baseDir):]  # remove path to basedir to clean things up
            all_simulation_results[scenarioJson] = [simulation_parameters, simulation_results]

        with lzma.open(raw_results_file, "wb") as file:
            pickle.dump(all_simulation_results, file)
    else:
        with lzma.open(raw_results_file, "rb") as file:
            all_simulation_results = pickle.load(file)

    return all_simulation_results


def interleave_videconf_traffic():
    # We don't have a model for videoconferences, so we cheat by interleaving voip + video streaming (we assume 480p at 2Mbps)
    for duration in [100, ]:
        interleaved_traffic = None
        input_traffics = []

        # The interleaving process starts by zipping time_between_packets of all traffics
        for inputFileName in ["stream_workload0_2mbps_%ds.json" % duration, "voip_workload0_%ds.json" % duration]:
            with open(inputFileName, "r") as inputFile:
                traffic = json.load(inputFile)
                if type(traffic["packet_size"]) == list:
                    input_traffics.append(list(zip(traffic["time_between_packets"], traffic["packet_size"])))
                    interleaved_traffic = traffic  # just to get the output file structure
                else:
                    input_traffics.append(list(zip(traffic["time_between_packets"], [traffic["packet_size"]]*len(traffic["time_between_packets"]))))
        del traffic, inputFile

        # We then replace relative times with absolute times to make merging easier
        interleaved_packets = []
        for traffic in input_traffics:
            accumulated_time_of_traffic = 0.0
            for time_between_packets, packet_size in traffic:
                accumulated_time_of_traffic += time_between_packets
                interleaved_packets.append([accumulated_time_of_traffic, packet_size])
        del input_traffics, traffic, accumulated_time_of_traffic, time_between_packets, packet_size

        # Merging is done, now we sort everything
        interleaved_packets.sort()

        # Then we bring back to time_between_packets format by subtracting time of the previous packet from the next one
        # We do this in reverse order to make things easier
        i = len(interleaved_packets)-1
        while i > 1:
            interleaved_packets[i][0] -= interleaved_packets[i-1][0]
            i -= 1

        # We split time_between_packets and packet_size and save into output structure
        interleaved_traffic["time_between_packets"], interleaved_traffic["packet_size"] = list(zip(*interleaved_packets))
        del interleaved_packets

        # Save interleaved traffic
        with open("videoconf_workload0_%ds.json" % duration, "w") as output:
            json.dump(interleaved_traffic, output, indent=4)
        del interleaved_traffic

if __name__ == "__main__":
    multiprocessing.freeze_support()

    # Select if you want to generate new simulation scenarios or run manually created ones
    createAndRunScenarios = True


    # Output folder
    baseDir = os.path.abspath("../../build/bin/")

    # You're supposed to run this script inside the scratch/5grange_simulations folder
    cwd = os.path.abspath(os.getcwd())  # do not touch this


    # Generate the jsons specifying the simulation scenarios
    setup_simulations(createAndRunScenarios)

    all_simulation_results = load_raw_results(baseDir)  # path to parameters, [parameterscontent, resultscontents]

    # After loading the pairs, we sort the items to get the simulations without CSS, with CSS and with CSS with Markov technique in order
    simulation_list = list(sorted(all_simulation_results.keys()))

    # this is sorted by number of UEs, simulation case, batch number and DSA
    compiled_simulation_results = {"case": {}}

    # now we need to group different batch results with each other to calculate error margins
    for simulation in simulation_list:
        simulation_keys = simulation.split("/")[1:-1]
        current_simulation_results = all_simulation_results[simulation][1]

        # ideally we would create a level for each key, but my deadline is killing me
        # We do one for the simulation case (ues + applications)
        if simulation_keys[0] not in compiled_simulation_results["case"]:
            compiled_simulation_results["case"][simulation_keys[0]] = {"dsa": {}}

        # Then another for DSA cases (0 = dsa off, 1 dsa on, 2 dsa on + markov
        dsa_key = 0 if simulation_keys[7] == "dsa_False" else 1
        if "markov_True" in simulation_keys[8]:
            dsa_key += 1
        if dsa_key not in compiled_simulation_results["case"][simulation_keys[0]]["dsa"]:
            compiled_simulation_results["case"][simulation_keys[0]]["dsa"][dsa_key] = {"sensing": None, "flow_per_batch": None}

        # Aggregate batch results of spectrum sensing
        if dsa_key > 0:
            if not compiled_simulation_results["case"][simulation_keys[0]]["dsa"][dsa_key]["sensing"]:
                compiled_simulation_results["case"][simulation_keys[0]]["dsa"][dsa_key]["sensing"] = current_simulation_results["collaborative_spectrum_sensing_results"]
                for channel in compiled_simulation_results["case"][simulation_keys[0]]["dsa"][dsa_key]["sensing"]["channel"]:
                    for key in compiled_simulation_results["case"][simulation_keys[0]]["dsa"][dsa_key]["sensing"]["channel"][channel]:
                        compiled_simulation_results["case"][simulation_keys[0]]["dsa"][dsa_key]["sensing"]["channel"][channel][key] = [compiled_simulation_results["case"][simulation_keys[0]]["dsa"][dsa_key]["sensing"]["channel"][channel][key], ]
            else:
                for channel in current_simulation_results["collaborative_spectrum_sensing_results"]["channel"]:
                    for key in current_simulation_results["collaborative_spectrum_sensing_results"]["channel"][channel]:
                        compiled_simulation_results["case"][simulation_keys[0]]["dsa"][dsa_key]["sensing"]["channel"][channel][key].append(current_simulation_results["collaborative_spectrum_sensing_results"]["channel"][channel][key])

        # too complex to aggregate just yet
        if not compiled_simulation_results["case"][simulation_keys[0]]["dsa"][dsa_key]["flow_per_batch"]:
            compiled_simulation_results["case"][simulation_keys[0]]["dsa"][dsa_key]["flow_per_batch"] = {0: current_simulation_results["flow_statistics"]}
        else:
            num_batches_loaded = len(compiled_simulation_results["case"][simulation_keys[0]]["dsa"][dsa_key]["flow_per_batch"])
            compiled_simulation_results["case"][simulation_keys[0]]["dsa"][dsa_key]["flow_per_batch"][num_batches_loaded] = current_simulation_results["flow_statistics"]
            del num_batches_loaded
        del current_simulation_results

    # At this point it is safe to delete the raw results
    del all_simulation_results, simulation_list

    # Now we check if the KPIs for the different applications were met
    # Ideally this would be done in extract_network_performance_metrics, but whatever
    from simulation_results.extract_network_performance_metrics import ApplicationPorts, application_KPIs

    def ns_timestamp_to_float(timestampo):
        timestampo = timestampo[1:-2]
        return float(timestampo)

    usedAppsDict = {}
    def fraction (possible, actual):
        return actual/possible

    for simulation_case_key in compiled_simulation_results["case"]:
        usedAppsDict[simulation_case_key] = set()
        for dsa in compiled_simulation_results["case"][simulation_case_key]["dsa"]:
            if dsa == 0:
                compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]['sensing'] = {'status':{"falseNegatives": [0],
                                                                                                             "falsePositives": [0],
                                                                                                             "reportedFramesPerUe": [0]
                                                                                                             }
                                                                                                   }
            else:
                compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]['sensing']['status'] = {"falseNegatives": [],
                                                                                                            "falsePositives": [],
                                                                                                            "reportedFramesPerUe": []
                                                                                                            }
                for channel in compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]['sensing']['channel']:
                    falseNegativesFraction = list(map(fraction,
                                                      compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]['sensing']['channel'][channel]["frames_pu_was_active"],
                                                      compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]['sensing']['channel'][channel]["total_false_negatives"]
                                                      ))
                    falsePositivesFraction = list(map(fraction,
                                                     compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]['sensing']['channel'][channel]["frames_pu_was_inactive"],
                                                     compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]['sensing']['channel'][channel]["total_false_positives"]
                                                     ))
                    reportedFramesFraction = list(map(fraction,
                                                     compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]['sensing']['channel'][channel]["total_fusions"],
                                                     compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]['sensing']['channel'][channel]["avg_bits_per_ue"]
                                                     ))
                    compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]['sensing']['status']["falseNegatives"].extend(falseNegativesFraction)
                    compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]['sensing']['status']["falsePositives"].extend(falsePositivesFraction)
                    compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]['sensing']['status']["reportedFramesPerUe"].extend(reportedFramesFraction)
                del falseNegativesFraction, falsePositivesFraction, reportedFramesFraction

            for batch in compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"]:
                for port in compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"]:
                    compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["appStatus"] = {
                        "dl_throughput_kbps": [],
                        "ul_throughput_kbps": [],
                        "lost_packets": [],
                        "lost_packets_pct": [],
                        "delay_n_mean_std": [],
                        "jitter_n_mean_std": [],
                        "passed_kpi": [],
                        "failed_kpi": [],
                        "agg_dl_throughput_kbps": [],
                        "agg_ul_throughput_kbps": [],
                    }
                    agg_dl_throughput_kbps = 0
                    agg_ul_throughput_kbps = 0
                    status = None
                    for flow in compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["flows"]:
                        metadata = compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["flows"][flow]["metadata"]
                        status = compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["flows"][flow]["status"]

                        # Calculate individual performance of UE application
                        #duration = (ns_timestamp_to_float(status["@timeLastRxPacket"]) - ns_timestamp_to_float(status["@timeFirstRxPacket"]))
                        duration = 10  # duration / 1e9
                        dl_throughput_kbps = 0
                        ul_throughput_kbps = int(status["@rxBytes"])*8/(duration*1024) if duration > 0 else 0

                        # Traffic coming out of an UE
                        if metadata["@sourceAddress"][0] == '7' and metadata['@sourceAddress'][-1] != '1':
                            # Traffic going towards a remote host
                            if metadata["@destinationAddress"][0] != '7':
                                agg_ul_throughput_kbps += ul_throughput_kbps
                                agg_dl_throughput_kbps += dl_throughput_kbps
                            #Traffic going towards a different UE (count uplink twice as part of the downlink)
                            else:
                                agg_ul_throughput_kbps += ul_throughput_kbps
                                agg_dl_throughput_kbps += ul_throughput_kbps
                        # Traffic coming out of a remote host
                        if metadata["@sourceAddress"][0] == '1':
                            agg_dl_throughput_kbps += ul_throughput_kbps
                            agg_ul_throughput_kbps += dl_throughput_kbps


                        lost_packets = int(status["@lostPackets"])
                        lost_packets_pct = int(status["@lostPackets"])/int(status["@txPackets"])
                        delay_histogram = []
                        if "bin" in status["delayHistogram"]:
                            for entry in status["delayHistogram"]["bin"]:
                                try:
                                    delay_histogram.extend([float(entry["@start"])]*int(entry["@count"]))
                                except TypeError:
                                    continue
                        jitter_histogram = []
                        if "bin" in status["jitterHistogram"]:
                            for entry in status["jitterHistogram"]["bin"]:
                                try:
                                    jitter_histogram.extend([float(entry["@start"])]*int(entry["@count"]))
                                except TypeError:
                                    continue

                        # Check if individual application of UE meets or exceeds the KPIs established for the application
                        passed = True

                        #if dl_throughput_kbps < application_KPIs[port]["dl_throughput_kbps"]:
                        #    passed = False
                        #if ul_throughput_kbps < application_KPIs[port]["ul_throughput_kbps"]:
                        #    passed = False
                        if lost_packets_pct > application_KPIs[port]["lost_packet_ratio"]:
                            passed = False

                        delayMean   = 0
                        delayStdDev = 0
                        if len(delay_histogram) > 0:
                            delayMean = numpy.mean(delay_histogram)
                            delayStdDev = numpy.std(delay_histogram)
                            # mean + 1.5*sigma = >90% reliable
                            # mean + 2*sigma = >99% reliable
                            # mean + 2.5*sigma = >99.9% reliable
                            if delayMean+2.5*delayStdDev > application_KPIs[port]["latency"]:
                                passed = False

                        jitterMean   = 0
                        jitterStdDev = 0
                        if len(jitter_histogram) > 0:
                            jitterMean = numpy.mean(jitter_histogram)
                            jitterStdDev = numpy.std(jitter_histogram)
                            if jitterMean+2.5*jitterStdDev > application_KPIs[port]["latency"]:
                                passed = False

                        if passed:
                            compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["appStatus"]["passed_kpi"].append(flow)
                        else:
                            compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["appStatus"]["failed_kpi"].append(flow)

                        # Aggregate application performance of multiple UEs to get overall picture for the simulation
                        compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["appStatus"]["dl_throughput_kbps"].append(dl_throughput_kbps)
                        compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["appStatus"]["ul_throughput_kbps"].append(ul_throughput_kbps)
                        compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["appStatus"]["lost_packets"].append(lost_packets)
                        compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["appStatus"]["lost_packets_pct"].append(lost_packets_pct)
                        compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["appStatus"]["delay_n_mean_std"].append((delay_histogram, delayMean, delayStdDev))
                        compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["appStatus"]["jitter_n_mean_std"].append((jitter_histogram, jitterMean, jitterStdDev))
                        #print()
                        del duration, dl_throughput_kbps, ul_throughput_kbps


                    # Store complete traffic for application
                    if agg_dl_throughput_kbps > 0 or agg_ul_throughput_kbps > 0:
                        usedAppsDict[simulation_case_key].add(port)
                    compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["appStatus"]["agg_dl_throughput_kbps"] = agg_dl_throughput_kbps
                    compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["appStatus"]["agg_ul_throughput_kbps"] = agg_ul_throughput_kbps
                    del status, agg_dl_throughput_kbps, agg_ul_throughput_kbps

                    # end of flor for
                # end of port for
            # end of batch for
        # end of dsa for

        compiled_simulation_results["case"][simulation_case_key]["appStatusPerPort"] = {"port": {}}
        for port in [port.value[0] for port in ApplicationPorts]:
            compiled_simulation_results["case"][simulation_case_key]["appStatusPerPort"]["port"][port] = {
                "agg_dl_throughput_kbps": [],
                "agg_ul_throughput_kbps": [],
                "appStatusPerDsa": {"dsa": {}}
            }
            for dsa in compiled_simulation_results["case"][simulation_case_key]["dsa"]:

                # Now we traverse the results by ports to aggregate results of different batches
                compiled_simulation_results["case"][simulation_case_key]["appStatusPerPort"]["port"][port]["appStatusPerDsa"]["dsa"][dsa] = {
                    "agg_dl_throughput_kbps": [],
                    "agg_ul_throughput_kbps": [],
                }


                for batch in compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"]:
                    compiled_simulation_results["case"][simulation_case_key]["appStatusPerPort"]["port"][port]["appStatusPerDsa"]["dsa"][dsa]["agg_dl_throughput_kbps"].append(compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["appStatus"]["agg_dl_throughput_kbps"])
                    compiled_simulation_results["case"][simulation_case_key]["appStatusPerPort"]["port"][port]["appStatusPerDsa"]["dsa"][dsa]["agg_ul_throughput_kbps"].append(compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["appStatus"]["agg_ul_throughput_kbps"])
                # end for batch
            # end for dsa
        # end for port

        output_csv_table = {}
        output_csv_table["apps"] = {}
        output_csv_table["generic"] = {}
        output_csv_table["generic"]["False Positives"] = []
        output_csv_table["generic"]["False Negatives"] = []
        output_csv_table["generic"]["Reported Subframes per UE"] = []

        for (port, appName) in [(port.value[0], port.name[:-10].capitalize()) for port in ApplicationPorts]:
            k = 0
            # Skip application if no data is available
            if port not in usedAppsDict[simulation_case_key]:
                continue

            output_csv_table["apps"][appName] = {
                "Aggregate Throughput DL (kbps)": [],
                "Aggregate Throughput UL (kbps)": [],
                "Packet Loss": [],
                "Delay (s)": [],
                "Jitter (s)": [],
            }



        # Time to plot aggregate throughput boxplots for the applications of each application (column) for each scenario
        fig, axes = plt.subplots(nrows=len(usedAppsDict[simulation_case_key]), ncols=2*1, figsize=(15, 6*len(usedAppsDict[simulation_case_key])), sharey=True, sharex=True, squeeze=False)
        import matplotlib.pyplot as plt
        i = 0
        dsa_labels = ["                      Without\n                        PUs",
                      "                      With PUs\n",
                      "                      With PUs\n                    +  MHM"]
        # Set y label on the central row
        for (port, appName) in [(port.value[0], port.name[:-10].capitalize()) for port in ApplicationPorts]:
            k = 0
            # Skip application if no data is available
            if port not in usedAppsDict[simulation_case_key]:
                continue

            # Each application occupies two columns (downlink and uplink) and 3 rows (without DSA/PUs, with DSA/PUs + OR fusion, with DSA/PUs + Markov+OR)
            for dsa in list(compiled_simulation_results["case"][simulation_case_key]["dsa"].keys())[:1]:
                dsa_dl_column = k
                dsa_ul_column = dsa_dl_column+1

                # Set column labels on top
                axes[i][dsa_dl_column].set_xlabel('%s\nDL' % dsa_labels[dsa])
                axes[i][dsa_dl_column].xaxis.set_label_position('top')
                axes[i][dsa_ul_column].set_xlabel('UL')
                axes[i][dsa_ul_column].xaxis.set_label_position('top')

                axes[i][0].set_ylabel("     %s\n Aggregate Throughput (kbps)" % appName)


                # Plot boxplots with results
                dl = compiled_simulation_results["case"][simulation_case_key]["appStatusPerPort"]["port"][port]["appStatusPerDsa"]["dsa"][dsa]["agg_dl_throughput_kbps"]
                ul = compiled_simulation_results["case"][simulation_case_key]["appStatusPerPort"]["port"][port]["appStatusPerDsa"]["dsa"][dsa]["agg_ul_throughput_kbps"]
                axes[i][dsa_dl_column].boxplot(dl)
                axes[i][dsa_ul_column].boxplot(ul)

                dl_mean = numpy.mean(dl)
                dl_inferiorlimit = st.t.interval(0.95, len(dl)-1, loc=dl_mean, scale=st.sem(dl))[0]
                ul_mean = numpy.mean(ul)
                ul_inferiorlimit = st.t.interval(0.95, len(ul)-1, loc=ul_mean, scale=st.sem(ul))[0]
                output_csv_table["apps"][appName]["Aggregate Throughput DL (kbps)"].extend([dl_mean, dl_mean-dl_inferiorlimit])
                output_csv_table["apps"][appName]["Aggregate Throughput UL (kbps)"].extend([ul_mean, ul_mean-ul_inferiorlimit])

                del dl_mean, dl_inferiorlimit, ul_mean, ul_inferiorlimit, dl, ul

                if dsa_dl_column != 0:
                    plt.setp(axes[i][dsa_dl_column].get_yticklabels(), visible=False)
                plt.setp(axes[i][dsa_ul_column].get_yticklabels(), visible=False)

                axes[i][dsa_dl_column].grid(b=True, which='major', color='#999999', linestyle='-')
                axes[i][dsa_ul_column].grid(b=True, which='major', color='#999999', linestyle='-')
                del dl, ul,

                axes[i][dsa_dl_column].set_yticks([x for x in range(25000, 100000, 25000)])
                axes[i][dsa_ul_column].set_yticks([x for x in range(25000, 100000, 25000)])

                # Next columns
                k += 2
            # Next row
            i += 1
        fig.tight_layout(pad=3.0)
        plt.xticks([], [])
        #plt.show()
        fig.savefig("perf_per_app_%s.png" % simulation_case_key)
        plt.clf()
        # End of aggregate throughput boxplots


        # Time to plot kpis boxplots for the applications of each application (column) for each scenario
        for metric in ["lostPackets", "delay", "jitter"]:
            fig, axes = plt.subplots(nrows=len(usedAppsDict[simulation_case_key]), ncols=3, figsize=(12, 6*len(usedAppsDict[simulation_case_key])), sharex=True, squeeze=False)
            i = 0
            dsa_labels = ["Without PUs\n",
                          "With PUs\n",
                          "With PUs\n +  MHM"]
            # Set y label on the central row
            for (port, appName) in [(port.value[0], port.name[:-10].capitalize()) for port in ApplicationPorts]:
                k = 0
                # Skip application if no data is available
                if port not in usedAppsDict[simulation_case_key]:
                    continue

                # Each application occupies two columns (downlink and uplink) and 3 rows (without DSA/PUs, with DSA/PUs + OR fusion, with DSA/PUs + Markov+OR)
                for dsa in compiled_simulation_results["case"][simulation_case_key]["dsa"]:
                    lost_packets = []
                    delay_hist_agg = []
                    jitter_hist_agg = []
                    for batch in compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"]:
                        if metric == "lostPackets":

                            lost_packets.extend(compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["appStatus"]["lost_packets_pct"])
                        elif metric == "delay":
                            for (_, mean, std) in compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["appStatus"]["delay_n_mean_std"]:
                                delay_hist_agg.extend([max(mean-2*std, 0.001), max(mean, 0.001), max(mean+2*std, 0.001)])
                                del _, mean, std
                        else:
                            for (_, mean, std) in compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["appStatus"]["jitter_n_mean_std"]:
                                jitter_hist_agg.extend([max(mean-2*std, 0.001), max(mean, 0.001), max(mean+2*std, 0.001)])
                            del _, mean, std
                    del batch

                    if metric == "lostPackets":
                        loss_mean = numpy.mean(lost_packets)
                        loss_inferiorlimit = st.t.interval(0.95, len(lost_packets)-1, loc=loss_mean, scale=st.sem(lost_packets))[0]
                        output_csv_table["apps"][appName]["Packet Loss"].extend([loss_mean, loss_mean-loss_inferiorlimit])
                        del loss_mean, loss_inferiorlimit,
                    elif metric == "delay":
                        delay_mean = numpy.mean(delay_hist_agg)
                        delay_inferiorlimit = st.t.interval(0.95, len(delay_hist_agg)-1, loc=delay_mean, scale=st.sem(delay_hist_agg))[0]
                        output_csv_table["apps"][appName]["Delay (s)"].extend([delay_mean, delay_mean-delay_inferiorlimit])
                        del delay_mean, delay_inferiorlimit
                    else:
                        jitter_mean = numpy.mean(jitter_hist_agg)
                        jitter_inferiorlimit = st.t.interval(0.95, len(jitter_hist_agg)-1, loc=jitter_mean, scale=st.sem(jitter_hist_agg))[0]
                        output_csv_table["apps"][appName]["Jitter (s)"].extend([jitter_mean, jitter_mean-jitter_inferiorlimit])
                        del jitter_mean, jitter_inferiorlimit

                    packet_loss_column = k
                    delay_column = k
                    jitter_column = k
                    axes[i][0].set_ylabel("     %s\n" % appName)

                    # Set column labels on top
                    if metric == "lostPackets":
                        if i == 0:
                            axes[i][packet_loss_column].set_xlabel('%s\n\nPacket Loss\n' % dsa_labels[dsa])
                            axes[i][packet_loss_column].xaxis.set_label_position('top')
                        # Link Y axis of same metrics
                        axes[i][0].get_shared_y_axes().join(axes[i][0], axes[i][packet_loss_column])
                        # Plot boxplots with results
                        axes[i][packet_loss_column].boxplot(lost_packets)
                        axes[i][packet_loss_column].grid(b=True, which='major', color='#999999', linestyle='-')
                    elif metric == "delay":
                        if i == 0:
                            axes[i][delay_column].set_xlabel('%s\n\nDelay (s)\n' % dsa_labels[dsa])
                            axes[i][delay_column].xaxis.set_label_position('top')
                        # Link Y axis of same metrics
                        axes[i][1].get_shared_y_axes().join(axes[i][1], axes[i][delay_column])
                        # Plot boxplots with results
                        axes[i][delay_column].boxplot(delay_hist_agg)
                        axes[i][delay_column].grid(b=True, which='major', color='#999999', linestyle='-')
                        axes[i][delay_column].set_yscale("log")
                        axes[i][delay_column].set_yticks([1/(10**x) for x in range(-3, 2)])
                    else:
                        if i == 0:
                            axes[i][jitter_column].set_xlabel('%s\n\nJitter (s)\n' % dsa_labels[dsa])
                            axes[i][jitter_column].xaxis.set_label_position('top')
                        # Link Y axis of same metrics
                        axes[i][2].get_shared_y_axes().join(axes[i][2], axes[i][jitter_column])
                        # Plot boxplots with results
                        axes[i][jitter_column].boxplot(jitter_hist_agg)
                        axes[i][jitter_column].grid(b=True, which='major', color='#999999', linestyle='-')
                        axes[i][jitter_column].set_yscale("log")
                    # Next columns
                    k += 1
                # Next row
                i += 1
            if metric != "lostPackets":
                for i in range(len(usedAppsDict[simulation_case_key])):
                    for k in range(len(compiled_simulation_results["case"][simulation_case_key]["dsa"])):
                        axes[i][k].yaxis.set_major_formatter(FormatStrFormatter('%.3f'))
                        axes[i][k].set_ylim([0.0001, 100.0])
                        axes[i][k].set_yticks([0.001, 0.01, 0.1, 1.0, 10.0])

            del packet_loss_column, delay_column, jitter_column, i, k, lost_packets, delay_hist_agg, jitter_hist_agg
            fig.tight_layout(pad=2.0)
            plt.xticks([], [])
            #plt.show()
            fig.savefig("kpi_per_app_%s_%s.png" % (metric, simulation_case_key))
            plt.clf()
        # End of kpis boxplots


        # Time to plot aggregate throughput boxplots for the applications of each application (column) for each scenario
        fig, axes = plt.subplots(nrows=1, ncols=2*3, figsize=(15, 8), sharex=True, sharey=True, squeeze=False)
        i = 0
        k = 0
        dsa_labels = ["Without PUs",
                      "With PUs\n",
                      "With PUs + MHM\n"]

        output_csv_table["generic"]["False Positives"].extend([0, 0])
        output_csv_table["generic"]["False Negatives"].extend([0, 0])
        output_csv_table["generic"]["Reported Subframes per UE"].extend([0, 0])

        # Each application occupies two columns (downlink and uplink) and 3 rows (without DSA/PUs, with DSA/PUs + OR fusion, with DSA/PUs + Markov+OR)
        for dsa in list(compiled_simulation_results["case"][simulation_case_key]["dsa"].keys())[1:]:
            dsa_falsePositive_column = k
            dsa_falseNegative_column = k+1
            dsa_reportedFrames_column = k+2

            # Set column labels on top
            axes[i][dsa_falsePositive_column].set_xlabel('False\nPositives', fontsize=14)
            axes[i][dsa_falsePositive_column].xaxis.set_label_position('top')
            axes[i][dsa_falseNegative_column].set_xlabel('%s\nFalse\nNegatives' % dsa_labels[dsa], fontsize=14)
            axes[i][dsa_falseNegative_column].xaxis.set_label_position('top')
            axes[i][dsa_reportedFrames_column].set_xlabel('Reported subframes\n per UE', fontsize=14)
            axes[i][dsa_reportedFrames_column].xaxis.set_label_position('top')

            axes[i][0].set_ylabel("Fraction")
            axes[i][0].set_ylim([-0.01, 1.01])
            axes[i][0].set_yticks([x/5 for x in range(6)])

            fp = compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]['sensing']['status']["falsePositives"]
            fn = compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]['sensing']['status']["falseNegatives"]
            rf = compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]['sensing']['status']["reportedFramesPerUe"]

            fp_mean = numpy.mean(fp)
            fp_inferiorlimit = st.t.interval(0.95, len(fp)-1, loc=fp_mean, scale=st.sem(fp))[0]
            fp_inferiorlimit = fp_mean-fp_inferiorlimit
            fp_inferiorlimit = 0 if numpy.isnan(fp_inferiorlimit) else fp_inferiorlimit

            fn_mean = numpy.mean(fn)
            fn_inferiorlimit = st.t.interval(0.95, len(fn)-1, loc=fn_mean, scale=st.sem(fn))[0]
            fn_inferiorlimit = fn_mean-fn_inferiorlimit
            fn_inferiorlimit = 0 if numpy.isnan(fn_inferiorlimit) else fn_inferiorlimit

            rf_mean = numpy.mean(rf)
            rf_inferiorlimit = st.t.interval(0.95, len(rf)-1, loc=rf_mean, scale=st.sem(rf))[0]
            rf_inferiorlimit = rf_mean-rf_inferiorlimit
            rf_inferiorlimit = 0 if numpy.isnan(rf_inferiorlimit) else rf_inferiorlimit

            output_csv_table["generic"]["False Positives"].extend([fp_mean, fp_inferiorlimit])
            output_csv_table["generic"]["False Negatives"].extend([fn_mean, fn_inferiorlimit])
            output_csv_table["generic"]["Reported Subframes per UE"].extend([rf_mean, rf_mean-rf_inferiorlimit])
            del fp_mean, fp_inferiorlimit, fn_mean, fn_inferiorlimit, rf_mean, rf_inferiorlimit

            # Plot boxplots with results
            axes[i][dsa_falsePositive_column].boxplot(fp)
            axes[i][dsa_falseNegative_column].boxplot(fn)
            axes[i][dsa_reportedFrames_column].boxplot(rf)



            if dsa_falsePositive_column != 0:
                plt.setp(axes[i][dsa_falsePositive_column].get_yticklabels(), visible=False)
            plt.setp(axes[i][dsa_falseNegative_column].get_yticklabels(), visible=False)
            plt.setp(axes[i][dsa_reportedFrames_column].get_yticklabels(), visible=False)

            axes[i][dsa_falsePositive_column].grid(b=True, which='major', color='#999999', linestyle='-')
            axes[i][dsa_falseNegative_column].grid(b=True, which='major', color='#999999', linestyle='-')
            axes[i][dsa_reportedFrames_column].grid(b=True, which='major', color='#999999', linestyle='-')
            # Next columns
            k += 3
        # Next row
        i += 1
        fig.tight_layout(pad=2.0)
        plt.xticks([], [])
        #plt.show()
        fig.savefig("sensing_per_scenario_%s.png" % simulation_case_key)
        plt.clf()

        with open("results_table_per_scenario_%s.csv" % simulation_case_key, "w") as f:
            lines = []
            lines.append("Sensing Results,Without PUs,With PUs,With PUs + MHM,\n")

            for metric in output_csv_table["generic"]:
                lines.append(u"%s,%f\u00B1%f,%f\u00B1%f,%f\u00B1%f,\n" % (metric, *output_csv_table["generic"][metric]))

            lines.append(",,,,\n")
            lines.append(",,,,\n")

            for appName in output_csv_table["apps"]:
                lines.append("%s,Without PUs,With PUs,With PUs + MHM,\n" % appName)
                for metric in output_csv_table["apps"][appName]:
                    lines.append(u"%s,%f\u00B1%f,%f\u00B1%f,%f\u00B1%f,\n" % (metric, *output_csv_table["apps"][appName][metric]))
                lines.append(",,,,\n")
            f.writelines(lines)

        del output_csv_table
        # End of collaborative spectrum sensing boxplots
    # end of simulation_case for
    print()
    pass
