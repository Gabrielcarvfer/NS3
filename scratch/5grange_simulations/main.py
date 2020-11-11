import os
import shutil
import multiprocessing
from enum import Enum
import json
import glob
import lzma
import pickle
import statistics

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

def setup_simulations():
    resultsDict = {"scenario": {}}
    numBatches = 10
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
    p = multiprocessing.Pool(processes=14)  # run simulations in parallel
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
    createAndRunScenarios = False

    # Output folder
    baseDir = os.path.abspath("../../build/bin/")

    # You're supposed to run this script inside the scratch/5grange_simulations folder
    cwd = os.path.abspath(os.getcwd())  # do not touch this

    # Copy injected traffic files to baseDir (where the 5g_range_demonstration_json executable is)
    shutil.copy("voip_workload0_100s.json", baseDir)
    shutil.copy("web_workload0_100s.json", baseDir)
    shutil.copy("stream_workload0_9mbps_100s.json", baseDir)
    shutil.copy("backhaul_dl_workload0_100s.json", baseDir)
    shutil.copy("backhaul_ul_workload0_100s.json", baseDir)
    shutil.copy("iot_workload0_100s_100nodes.json", baseDir)
    shutil.copy("iot_workload0_100s_300nodes.json", baseDir)
    interleave_videconf_traffic()
    shutil.copy("videoconf_workload0_100s.json", baseDir)

    # Generate the jsons specifying the simulation scenarios
    if createAndRunScenarios:
        setup_simulations()

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

    # At this point it is safe to delete the raw results
    del all_simulation_results, current_simulation_results, simulation_list, num_batches_loaded

    # Now we check if the KPIs for the different applications were met
    # Ideally this would be done in extract_network_performance_metrics, but whatever
    from simulation_results.extract_network_performance_metrics import ApplicationPorts, application_KPIs

    def ns_timestamp_to_float(timestampo):
        timestampo = timestampo[1:-2]
        return float(timestampo)

    for simulation_case_key in compiled_simulation_results["case"]:
        for dsa in compiled_simulation_results["case"][simulation_case_key]["dsa"]:
            for batch in compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"]:
                for port in compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"]:
                    compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["appStatus"] = {
                        "dl_throughput_kbps": [],
                        "ul_throughput_kbps": [],
                        "lost_packets": [],
                        "lost_packets_pct": [],
                        "delay_histogram": [],
                        "jitter_histogram": [],
                        "passed_kpi": [],
                        "failed_kpi": [],
                        "agg_dl_throughput_kbps": [],
                        "agg_ul_throughput_kbps": [],
                    }
                    agg_dl_throughput_kbps = 0
                    agg_ul_throughput_kbps = 0
                    for flow in compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["flows"]:
                        metadata = compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["flows"][flow]["metadata"]
                        status = compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["flows"][flow]["status"]

                        # Calculate individual performance of UE application
                        duration = (ns_timestamp_to_float(status["@timeLastRxPacket"]) - ns_timestamp_to_float(status["@timeFirstRxPacket"]))
                        duration = duration / 1e9
                        if duration > 0:
                            dl_throughput_kbps = int(status["@rxBytes"])*8/(duration*1024)
                            ul_throughput_kbps = int(status["@txBytes"])*8/(duration*1024)
                        else:
                            dl_throughput_kbps = 0
                            ul_throughput_kbps = 0

                        # Traffic coming out of an UE
                        if metadata["@sourceAddress"][0] == '7' and metadata['@sourceAddress'][-1] != '1':
                            agg_dl_throughput_kbps += dl_throughput_kbps
                            agg_ul_throughput_kbps += ul_throughput_kbps
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

                        if dl_throughput_kbps < application_KPIs[port]["dl_throughput_kbps"]:
                            passed = False
                        if ul_throughput_kbps < application_KPIs[port]["ul_throughput_kbps"]:
                            passed = False
                        if lost_packets_pct > application_KPIs[port]["lost_packet_ratio"]:
                            passed = False

                        if len(delay_histogram) > 0:
                            delayMean = statistics.mean(delay_histogram)
                            delayStdDev = statistics.stdev(delay_histogram)
                            if delayMean+3*delayStdDev > application_KPIs[port]["latency"]:
                                passed = False

                        if len(jitter_histogram) > 0:
                            jitterMean = statistics.mean(jitter_histogram)
                            jitterStdDev = statistics.stdev(jitter_histogram)
                            if jitterMean+3*jitterStdDev > application_KPIs[port]["latency"]:
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
                        compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["appStatus"]["delay_histogram"].append(delay_histogram)
                        compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["appStatus"]["jitter_histogram"].append(jitter_histogram)
                        #print()

                    # Store complete traffic for application
                    agg_dl_throughput_kbps /= 2  # traffic was counted twice
                    agg_ul_throughput_kbps /= 2
                    compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["appStatus"]["agg_dl_throughput_kbps"] = agg_dl_throughput_kbps
                    compiled_simulation_results["case"][simulation_case_key]["dsa"][dsa]["flow_per_batch"][batch]["applicationPort"][port]["appStatus"]["agg_ul_throughput_kbps"] = agg_ul_throughput_kbps
                    #print()

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

        # Time to plot boxplots for the applications of each application (column) for each scenario
        import matplotlib.pyplot as plt
        fig, axes = plt.subplots(nrows=3, ncols=2*len(ApplicationPorts), figsize=(24, 6), sharex=True, sharey=True)
        i = 0

        dsa_labels = ["Without\n PUs", "Throughput (kbps)\nWith\n PUs", "With PUs \n+ Markov"]
        # Set y label on the central row
        for (port, appName) in [(port.value[0], port.name[:-10].capitalize()) for port in ApplicationPorts]:
            # Each application occupies two columns (downlink and uplink) and 3 rows (without DSA/PUs, with DSA/PUs + OR fusion, with DSA/PUs + Markov+OR)
            for dsa in compiled_simulation_results["case"][simulation_case_key]["dsa"]:
                if dsa == 0:
                    # Set column labels on top
                    axes[dsa][i].set_xlabel('              %s\nDL' % appName)
                    axes[dsa][i].xaxis.set_label_position('top')
                    axes[dsa][i+1].set_xlabel('UL')
                    axes[dsa][i+1].xaxis.set_label_position('top')

                axes[dsa][0].set_ylabel(dsa_labels[dsa])

                # Plot boxplots with results
                axes[dsa][i].boxplot(compiled_simulation_results["case"][simulation_case_key]["appStatusPerPort"]["port"][port]["appStatusPerDsa"]["dsa"][dsa]["agg_dl_throughput_kbps"])
                axes[dsa][i+1].boxplot(compiled_simulation_results["case"][simulation_case_key]["appStatusPerPort"]["port"][port]["appStatusPerDsa"]["dsa"][dsa]["agg_ul_throughput_kbps"])


            # Skip to the next two columns
            i += 2

        fig.tight_layout(pad=3.0)
        plt.xticks([], [])
        plt.show()
        fig.savefig("perf_per_app_%s.png" % simulation_case_key)
        print()
    # end of simulation_case for
    print()
    pass
