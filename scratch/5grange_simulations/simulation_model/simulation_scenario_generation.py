import random
import os
import json

from .pu_model import PU_Model
from .enb_model import eNB_Model
from .ue_model import UE_Model
from .simulation_topology import generatePosition
from .simulation_parameters import SimulationParameters, fusionAlgorithms, mimoSchemes
from .plot_simulation_topology import plot_simulation_topology

def generate_random_pus(
        numPUs         = 4,           #
        xRange         = (0, 100e3),  # m
        yRange         = (0, 100e3),  # m
        zRange         = (0,   0.1),  # m
        txPowerRange   = (30,   40),  # dBm
        dutyCycleRange = (0.1, 0.4),  # percentage of period to transmit and precision
        txPeriodRange  = (1, 5),      # period between Txs
):

    for pu in range(numPUs):
        txPower           = round( random.uniform(*txPowerRange)    , 2)
        dutyCycle         = round( random.uniform(*dutyCycleRange)  , 2)
        txPeriod          = round( random.uniform(*txPeriodRange)   , 2)
        channel           = pu % numPUs
        PU_Model(generatePosition(xRange, yRange, zRange), txPower, dutyCycle, txPeriod, channel)

def generate_scenario(ueSpeed=0, numUEs=100, clusters=False): #todo: equidistantes
    xRange = (0, 100e3),  # m
    yRange = (0, 100e3),  # m
    zRange = (0,   0.1),  # m

    generate_random_pus(numPUs=4, txPowerRange=(30, 40), txPeriodRange=(1, 3), xRange=xRange, yRange=yRange, zRange=zRange)

    ueTxPower      = 23   #dBm
    ueAntennaGain  = 9    #dBi
    eNBTxPower     = 40.8 #dBm
    eNBAntennaGain = 9    #dBi

    if not clusters:
        for ue in range(numUEs):
            UE_Model(generatePosition(xRange, yRange, zRange), ueTxPower, ueAntennaGain, speed=ueSpeed)
    else:
        totalUEs = 0

        while totalUEs < numUEs:
            div = 5 if (numUEs - totalUEs) > 10 else 2
            ues = random.randint(0, int((numUEs+1)/div))
            clusterPosition = generatePosition(xRange, yRange, zRange)
            clusterxRange = (clusterPosition[0]-5e3, clusterPosition[0]+5e3)
            clusteryRange = (clusterPosition[1]-5e3, clusterPosition[1]+5e3)
            for ue in range(ues):
                UE_Model(generatePosition(clusterxRange, clusteryRange, zRange), ueTxPower, ueAntennaGain, speed=ueSpeed)
                totalUEs += 1
                if totalUEs == numUEs:
                    break

    eNB_Model((50e3, 50e3, 0), eNBTxPower, eNBAntennaGain)

    sim = SimulationParameters(PU_Model.PUs, UE_Model.UEs, eNB_Model.eNBs)

    return sim.dictio


def generate_scenarios(baseFolder,
                      batch,
                      numUEs,
                      ueSpeeds,
                      clusteredUes,
                      dynamicSpectrumAccess,
                      markovOptions,
                      harmonicOptions,
                      fusionAlgs,
                      attackerOptions,
                      frequencyBandOptions,
                      mimoOptions):

    # Create base folder if it doesnt exist
    if not os.path.exists(baseFolder):
        os.mkdir(baseFolder)

    # Create batch folder if it doesnt exist
    batchFolder = baseFolder+os.sep+"batch_"+str(batch)
    if not os.path.exists(batchFolder):
        os.mkdir(batchFolder)

    # Create folders for clustered and randomly distributed UEs
    for clustersOption in clusteredUes:
        clusteredUesBatchFolder = batchFolder+os.sep+"clusteredUes_"+str(clustersOption)
        if not os.path.exists(clusteredUesBatchFolder):
            os.mkdir(clusteredUesBatchFolder)

        baseSimulationJsonPath = clusteredUesBatchFolder+os.sep+"baseSimulationParameters.json"

        #If process was interrupted, continue generating from previos base simulation
        if os.path.exists(baseSimulationJsonPath):
            with open(baseSimulationJsonPath, "r") as f:
                simulationScenario = json.load(f)

        # Otherwise generate a new base scenario that will be replicated with different settings
        else:
            simulationScenario = generate_scenario(numUEs=numUEs, clusters=clustersOption)
            with open(baseSimulationJsonPath, "w") as f:
                json.dump(simulationScenario, f, indent=4)

        # Plot topologies if they haven't been plotted yet
        if False in [os.path.exists(clusteredUesBatchFolder+os.sep+"topology_with_pu.png"),
                     os.path.exists(clusteredUesBatchFolder+os.sep+"topology_without_pu.png")]:
            plot_simulation_topology(clusteredUesBatchFolder, simulationScenario)

        # Create folder for different frequency bands
        for freqBand in frequencyBandOptions:
            freqBandFolder = clusteredUesBatchFolder+os.sep+"freqBand_"+str(freqBand)
            if not os.path.exists(freqBandFolder):
                os.mkdir(freqBandFolder)

            # Create folder for different mimo options
            for mimoMode in mimoOptions:
                mimoModeFolder = freqBandFolder+os.sep+"mimo_"+mimoSchemes[mimoMode]
                if not os.path.exists(mimoModeFolder):
                    os.mkdir(mimoModeFolder)

                for ueSpeed in ueSpeeds:
                    speedFolder = mimoModeFolder+os.sep+"speed_"+str(ueSpeed)
                    if not os.path.exists(speedFolder):
                        os.mkdir(speedFolder)

                    # Create folders for scenarios with and without dynamic spectrum access
                    for dynamicSpectrumAccessOption in dynamicSpectrumAccess:
                        dsaFolder = speedFolder+os.sep+"dsa_"+str(dynamicSpectrumAccessOption)
                        if not os.path.exists(dsaFolder):
                            os.mkdir(dsaFolder)

                        if not dynamicSpectrumAccess:
                            # Ideal scenario, we remove PUs and disable DSA/MHM/etc
                            for channelModel in ["D3.1", "CDL_D", "CDL_A"]:
                                channelModelFolder = dsaFolder+os.sep+"channelModel_"+channelModel
                                if not os.path.exists(channelModelFolder):
                                    os.mkdir(channelModelFolder)
                                # Replace appropriate settings in base scenario and dump to json inside the folder
                                simulationScenario["SimulationParameters"]["fusionAlgorithm"] = fusionAlgorithm
                                simulationScenario["SimulationParameters"]["fusionAlgorithmName"] = fusionAlgorithms[fusionAlgorithm]
                                simulationScenario["SimulationParameters"]["enableDSA"] = False
                                simulationScenario["SimulationParameters"]["attackers_per_channel"] = 0
                                simulationScenario["SimulationParameters"]["markov_detection"]   = False
                                simulationScenario["SimulationParameters"]["harmonic_detection"] = False
                                simulationScenario["SimulationParameters"]["useCdlPathLoss"]    = channelModel in ["CDL_D", "CDL_A"]
                                simulationScenario["SimulationParameters"]["cdlType"]           = channelModel if channelModel == "CDL_A" else "CDL_D"
                                simulationScenario["SimulationParameters"]["mimoMode"]          = mimoMode
                                simulationScenario["SimulationParameters"]["freqBand"]          = freqBand

                                for ue in simulationScenario["UE"]:
                                    simulationScenario["UE"][ue]["speed"] = ueSpeed

                                # Check if output file already exists to skip rewriting it
                                SimulationJsonPath = channelModelFolder+os.sep+"simulationParameters.json"
                                if not os.path.exists(SimulationJsonPath):
                                    with open(SimulationJsonPath, "w") as f:
                                        json.dump(simulationScenario, f, indent=4)
                        else:
                            # Create folders for scenarios with different MHM settings
                            for markovOption, harmonicOption in zip(markovOptions, harmonicOptions):
                                mhmFolder = dsaFolder+os.sep+"markov_"+str(markovOption)+"_harmonic_"+str(harmonicOption)
                                if not os.path.exists(mhmFolder):
                                    os.mkdir(mhmFolder)

                                # Create folders for different number of attackers
                                for numAttackers in attackerOptions:
                                    if numUEs <= numAttackers:
                                        continue

                                    attackersFolder = mhmFolder+os.sep+"attackers_"+str(numAttackers)
                                    if not os.path.exists(attackersFolder):
                                        os.mkdir(attackersFolder)

                                    # Create folder for different fusion algorithms
                                    for fusionAlgorithm in fusionAlgs:
                                        fusionAlgorithmFolder = attackersFolder+os.sep+"fusion_"+fusionAlgorithms[fusionAlgorithm]
                                        if not os.path.exists(fusionAlgorithmFolder):
                                            os.mkdir(fusionAlgorithmFolder)

                                            for channelModel in ["D3.1", "CDL_D", "CDL_A"]:
                                                channelModelFolder = fusionAlgorithmFolder+os.sep+"channelModel_"+channelModel
                                                if not os.path.exists(channelModelFolder):
                                                    os.mkdir(channelModelFolder)

                                                # Replace appropriate settings in base scenario and dump to json inside the folder
                                                simulationScenario["SimulationParameters"]["fusionAlgorithm"] = fusionAlgorithm
                                                simulationScenario["SimulationParameters"]["fusionAlgorithmName"] = fusionAlgorithms[fusionAlgorithm]
                                                simulationScenario["SimulationParameters"]["enableDSA"] = True
                                                simulationScenario["SimulationParameters"]["attackers_per_channel"] = numAttackers
                                                simulationScenario["SimulationParameters"]["markov_detection"]   = markovOption
                                                simulationScenario["SimulationParameters"]["harmonic_detection"] = harmonicOption
                                                simulationScenario["SimulationParameters"]["useCdlPathLoss"]    = channelModel in ["CDL_D", "CDL_A"]
                                                simulationScenario["SimulationParameters"]["cdlType"]           = channelModel if channelModel == "CDL_A" else "CDL_D"
                                                simulationScenario["SimulationParameters"]["mimoMode"]          = mimoMode
                                                simulationScenario["SimulationParameters"]["freqBand"]          = freqBand

                                                for ue in simulationScenario["UE"]:
                                                    simulationScenario["UE"][ue]["speed"] = ueSpeed

                                                SimulationJsonPath = channelModelFolder+os.sep+"simulationParameters.json"
                                                if not os.path.exists(SimulationJsonPath):
                                                    with open(SimulationJsonPath, "w") as f:
                                                        json.dump(simulationScenario, f, indent=4)
