import os
import shutil
import multiprocessing
from enum import Enum
import json
from functools import reduce

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

if __name__ == "__main__":
    multiprocessing.freeze_support()

    # Select if you want to generate new simulation scenarios or run manually created ones
    createAndRunScenarios = True

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
    shutil.copy("videoconf_workload0_100s.json", baseDir)

    def caseValue(case):
        print(case)
        return case.value[0]

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

    numerology_and_numUEs_threshold = [(0, 0), (2, 20), (3, 50)]
    dynamic_spectrum_access = [False, True, ]

    # Generate the jsons specifying the simulation scenarios
    if createAndRunScenarios:
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
                                          markovOptions=[use_dsa, ],  # True],
                                          harmonicOptions=[False, ],  # True], # not working with attackers
                                          fusionAlgs=[6, ],  # 7, 11, 12, 13],
                                          attackerOptions=[0, ],  # 1, 2, 5],
                                          frequencyBandOptions=[freqBands.MHz713, ],  # 101, 5, 7],
                                          mimoOptions=[mimoModes.TxDiversity, ],  # 0, 1, 2]
                                          simulationCase=applications
                                          )

        # Easier than trying to figure out all directories for the individual simulations is to use glob
        # to find all json files with simulation parameters and pass the list for parallel execution
        import glob
        simulationParameterFilesList = glob.glob(baseDir+os.sep+"**"+os.sep+"simulationParameters.json", recursive=True)

        thread_parameters = []
        for scenarioJson in simulationParameterFilesList:
            # Before executing anything, we check if the outputs file has been processed for that given scenario
            simulation_path = os.path.dirname(scenarioJson)

            # Run simulation if necessary and try to extract results into a single output file
            execute_simulation(simulation_path, baseDir)  # run simulations individually
            #thread_parameters.append((simulation_path, baseDir))

        # Dispatch simulations
        p = multiprocessing.Pool(processes=8)  # run simulations in parallel
        results = p.starmap(func=execute_simulation, iterable=thread_parameters)



    # When all simulations have finished, load up their results and apply some statistics/plots
    # Result files were pickled and compressed

    pass
