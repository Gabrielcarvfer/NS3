import json
import random
from decimal import Decimal
import os

# Small selection of fusion algorithms, as we already have a ton of other different parameters to change
fusionAlgorithms = {
         6: "MRG_OR",
         7: "MRG_AND",
         11: "MRG_2_OF_N",
         12: "MRG_3_OF_N",
         13: "MRG_4_OF_N",
}


class SimulationParameters():
    def __init__(self,
                 PU_models,
                 UE_models,
                 eNB_model,
                 traffic_profile_model,
                 simulation_time,
                 fusion_algorithm = fusionAlgorithms[6],
                 propagation_model = "ns3::RANGE5GPropagationLossModel",
                 enableDSA = False,
                 SNRSensing = False,
                 attackers_per_channel = 0,
                 markov_detection = False,
                 harmonic_detection = False,
                 useErrorModel = True,
                 usePerfectChannel = False,
                 useHarq = False,
                 useIdealRrc = True,
                 useCdlPathLoss = False,
                 forceMaxMcsSched = False,
                 kval = 0.0,
                 numAntennas = 1,
                 mimoMode = 0,
                 channel_bandwidth = 24,  # converted into number of RBS inside the simulation program
                 freqBand = 100,  # converted into frequency ranges inside the simulation program
                 cdlType = "CDL_D"):

        self.dictio = {"SimulationParameters": {}}

        #Original settings
        self.dictio["SimulationParameters"]["ts"] = simulation_time
        self.dictio["SimulationParameters"]["bw"] = channel_bandwidth
        self.dictio["SimulationParameters"]["propagationModel"] = propagation_model
        self.dictio["PU"]  = PU_models
        self.dictio["eNB"] = eNB_model
        self.dictio["UE"]  = UE_models

        # COLAB settings
        self.dictio["SimulationParameters"]["fusionAlgorithm"] = fusion_algorithm
        self.dictio["SimulationParameters"]["fusionAlgorithmName"] = fusionAlgorithms[fusion_algorithm]
        self.dictio["SimulationParameters"]["enableDSA"] = enableDSA
        self.dictio["SimulationParameters"]["SNRSensing"] = SNRSensing #if false, distance-based detection curves will be loaded

        # MHM settings
        self.dictio["SimulationParameters"]["attackers_per_channel"] = attackers_per_channel
        self.dictio["SimulationParameters"]["markov_detection"]   = markov_detection
        self.dictio["SimulationParameters"]["harmonic_detection"] = harmonic_detection

        # LTE/5G-RANGE channel model settings
        self.dictio["SimulationParameters"]["useErrorModel"]     = useErrorModel
        self.dictio["SimulationParameters"]["usePerfectChannel"] = usePerfectChannel
        self.dictio["SimulationParameters"]["useHarq"]           = useHarq
        self.dictio["SimulationParameters"]["useIdealRrc"]       = useIdealRrc
        self.dictio["SimulationParameters"]["useCdlPathLoss"]    = useCdlPathLoss
        self.dictio["SimulationParameters"]["forceMaxMcsSched"]  = forceMaxMcsSched
        self.dictio["SimulationParameters"]["kval"]              = kval
        self.dictio["SimulationParameters"]["numAntennas"]       = numAntennas
        self.dictio["SimulationParameters"]["mimoMode"]          = mimoMode
        self.dictio["SimulationParameters"]["freqBand"]          = freqBand
        self.dictio["SimulationParameters"]["cdlType"]           = cdlType

        # EROS generated traffic profile to inject into applications
        self.dictio["SimulationParameters"]["traffic_profile_model"] = traffic_profile_model

    def to_json(self):
        outputbuffer = json.dumps(self.dictio, indent=4)
        return outputbuffer


class UE_Model():
    num_UE = 0
    UEs = {}
    def __init__(self, coordinate_tuple, transmission_power, antenna_gain):
        self.dictio = {}
        self.dictio["num"]      = UE_Model.num_UE
        self.dictio["position"] = coordinate_tuple
        self.dictio["tx_power"] = transmission_power
        self.dictio["gain"]     = antenna_gain

        UE_Model.UEs[UE_Model.num_UE] = self.dictio
        UE_Model.num_UE += 1


class eNB_Model():
    num_eNB = 0
    eNBs = {}

    def __init__(self, coordinate_tuple, transmission_power, antenna_gain):
        self.dictio = {}
        self.dictio["num"]      = eNB_Model.num_eNB
        self.dictio["position"] = coordinate_tuple
        self.dictio["tx_power"] = transmission_power
        self.dictio["gain"]     = antenna_gain

        eNB_Model.eNBs[eNB_Model.num_eNB] = self.dictio
        eNB_Model.num_eNB += 1

class PU_Model():
    num_PU = 0
    PUs = {}
    def __init__(self, coordinate_tuple, transmission_power, duty_cycle, period, channel):
        self.dictio = {}
        self.dictio["position"]   = coordinate_tuple
        self.dictio["tx_power"]   = transmission_power
        self.dictio["duty_cycle"] = duty_cycle
        self.dictio["period"]     = period
        self.dictio["num"]        = PU_Model.num_PU
        self.dictio["channel"]    = channel

        PU_Model.PUs[PU_Model.num_PU] = self.dictio
        PU_Model.num_PU += 1
        return

    @staticmethod
    def to_json():
        outputBuffer = json.dumps(PU_Model.PUs, indent=4) #make json readable by indenting it
        return outputBuffer

def generateRandomPUs(
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


def distanceFromCenter(x,y,z):
    return ((x-50e3)**2 + (y-50e3)**2 + (z)**2)**0.5

def generatePosition(xRange, yRange, zRange):
    if len(xRange) == 1:
        xRange = xRange[0]
    if len(yRange) == 1:
        yRange = yRange[0]
    if len(zRange) == 1:
        zRange = zRange[0]

    x = round(random.uniform(xRange[0], xRange[1]), 2)
    y = round(random.uniform(yRange[0], yRange[1]), 2)
    z = round(random.uniform(zRange[0], zRange[1]), 2)

    i = 0
    while distanceFromCenter(x, y, z) > 50e3:
        if i == 0:
            x = round(random.uniform(xRange[0], xRange[1]), 2)
        elif i == 1:
            y = round(random.uniform(xRange[0], xRange[1]), 2)
        else:
            z = round(random.uniform(zRange[0], zRange[1]), 2)
        i = (i+1) % 3

    return (x, y, z)

def generateScenario(baseFolder, numUEs=100, clusters=False):
    xRange = (10e3, 90e3),  # m
    yRange = (10e3, 90e3),  # m
    zRange = (   0,  0.1),  # m

    generateRandomPUs(numPUs=4, txPowerRange=(30, 40), txPeriodRange=(1, 5), xRange=xRange, yRange=yRange, zRange=zRange)

    ueTxPower      = 25 #dBm
    ueAntennaGain  = 9  #dBi
    eNBTxPower     = 53 #dBm
    eNBAntennaGain = 9  #dBi
    propagationModel = "ns3::RANGE5GPropagationLossModel"#"ns3::FriisPropagationLossModel"#

    if not clusters:
        for ue in range(numUEs):
            UE_Model(generatePosition(xRange, yRange, zRange), ueTxPower, ueAntennaGain)
    else:
        totalUEs = 0

        while totalUEs < numUEs:
            div = 5 if (numUEs - totalUEs) > 10 else 2
            ues = random.randint(0, int((numUEs+1)/div))
            clusterPosition = generatePosition(xRange, yRange, zRange)
            clusterxRange = (clusterPosition[0]-5e3, clusterPosition[0]+5e3)
            clusteryRange = (clusterPosition[1]-5e3, clusterPosition[1]+5e3)
            for ue in range(ues):
                UE_Model(generatePosition(clusterxRange, clusteryRange, zRange), ueTxPower, ueAntennaGain)
                totalUEs += 1
                if totalUEs == numUEs:
                    break
    #for enb in range(numENBs):
    eNB_Model((50e3, 50e3, 0), eNBTxPower, eNBAntennaGain)

    sim = SimulationParameters(10, 1, propagationModel, PU_Model.PUs, UE_Model.UEs, eNB_Model.eNBs)

    for fusionAlgorithm in [6, 7, 10, 11, 12, 13]:
        sim.dictio["SimulationParameters"]["fusionAlgorithm"] = fusionAlgorithm
        sim.dictio["SimulationParameters"]["fusionAlgorithmName"] = fusionAlgorithms[fusionAlgorithm]

        simFolder = baseFolder+fusionAlgorithms[fusionAlgorithm]+"\\"

        if os.path.exists(simFolder) and not os.path.exists(simFolder+"sensing.png"):
            import shutil
            shutil.rmtree(simFolder, ignore_errors=True)

        if not os.path.exists(simFolder):
            os.mkdir(simFolder)

        simFile = simFolder+"simulationParameters.json"

        if not os.path.exists(simFile):
            with open(simFile, "w") as file:
                file.write(sim.to_json())

    #Clean classes as processes may be recycled
    PU_Model.PUs = {}
    PU_Model.num_PU = 0
    eNB_Model.eNBs = {}
    eNB_Model.num_eNB = 0
    UE_Model.UEs = {}
    UE_Model.num_UE = 0

def generateScenarios(baseFolder, clusters=False):
    if not os.path.exists(baseFolder):
        os.mkdir(baseFolder)

    #Create json file for simulation
    for numUEs in [10, 20, 50, 100]:
        numUesFolder = baseFolder+"ues_"+str(numUEs) + os.sep
        if not os.path.exists(numUesFolder):
            os.mkdir(numUesFolder)
        generateScenario(numUesFolder, numUEs=numUEs, clusters=clusters)

def runScenario(baseFolder, harmonicOption, markovOption, fusionAlgorithm, numUes, attackersOption):
    #Move python to the target folder
    os.chdir(baseFolder)

    #Launch a process to run the simulation at the same json folder
    import subprocess

    #Run simulation
    if not os.path.exists("./sensing_list.txt"):
        executablePath = "/mnt/e/tools/source/NS3/build/bin/collaborative_sensing_demonstration_json_%sMarkov_%sHarmonic_%sAttackers" % ("__" if harmonicOption else "no", "__" if markovOption else "no", attackersOption)
        #response = subprocess.run("bash -c /mnt/e/tools/source/NS3/build/bin/collaborative_sensing_demonstration_json")
        response = subprocess.run("bash -c " + executablePath)

        #Generate the results plot figure and save to the simulation output folder (doesnt work for random numbers of UEs)
        #response = subprocess.run("python E:\\tools\\source\\NS3\\plot_main.py")
        pass
    pass


if __name__ == "__main__":
    import multiprocessing
    import subprocess
    import shutil
    #Select if you want to generate new simulation scenarios or run manually created ones
    createAndRunScenarios = True

    baseDir = "E:\\tools\\source\\sims\\"
    resultsDict = {"scenario":{}}
    if createAndRunScenarios:
        #Prepare and run n simulations
        with multiprocessing.Pool(processes=14) as pool:

            for i in range(0, 10):
                # Prepare the simulationParameter json files for all simulations
                generateScenarios(baseDir+str(i)+os.sep, clusters=True)

                #Run simulation if the scenario exists
                if (os.path.exists(baseDir+str(i))):

                    argList = []
                    scenPath = baseDir+str(i)+os.sep
                    # Run simulation with a few fusion algorithms
                    for harmonicOption in [False, True]:
                        for markovOption in [False, True]:
                            harmonicMarkovOptionPath = scenPath+"%sHarmonic_%sMarkov" % ("" if harmonicOption else "no", "" if markovOption else "no")+os.sep
                            if (not os.path.exists(harmonicMarkovOptionPath)):
                                os.mkdir(harmonicMarkovOptionPath)
                            for fusionAlgorithm in [6, 7, 11, 12]:
                                for numUes in [10, 20, 50, 100]:
                                    for attackersOption in ["no", "01", "02", "05", "10"]:
                                        path = harmonicMarkovOptionPath+"ues_"+str(numUes)+"_"+attackersOption+"Attackers"+os.sep
                                        if (not os.path.exists(path)):
                                            os.mkdir(path)
                                        fusionPath = path+fusionAlgorithms[fusionAlgorithm]
                                        if (not os.path.exists(fusionPath)):
                                            os.mkdir(fusionPath)
                                        shutil.copy(scenPath+"ues_"+str(numUes)+os.sep+fusionAlgorithms[fusionAlgorithm]+os.sep+"simulationParameters.json", fusionPath)
                                        argList += [[fusionPath, harmonicOption, markovOption, fusionAlgorithm, numUes, attackersOption]]

                    for numUes in [10, 20, 50, 100]:
                        path = scenPath+"ues_"+str(numUes)+os.sep+fusionAlgorithms[6]
                        subprocess.run("python plot_network_topology.py %s" % path)

                    # Run simulations in parallel
                    pool.starmap(runScenario, argList)



                #Extract results
                import re
                regexBitsPerUe = "of (.*?) bits"
                regexBitsPerUeC = re.compile(regexBitsPerUe)
                regexRaw = "From (.*) fusions, (.*) were false positive and (.*) were false negative"
                regexRawC = re.compile(regexRaw)
                regexFalse = ".* of (.*) subframes"
                regexFalseC = re.compile(regexFalse)

                scenPath = baseDir+str(i)+os.sep
                # Run simulation with a few fusion algorithms
                resultsDict["scenario"][i] = {"harmonic":{}}
                for harmonicOption in [False, True]:
                    resultsDict["scenario"][i]["harmonic"][harmonicOption] = {"markov":{}}
                    for markovOption in [False, True]:
                        resultsDict["scenario"][i]["harmonic"][harmonicOption]["markov"][markovOption] = {"attackers":{}}
                        harmonicMarkovOptionPath = scenPath+"%sHarmonic_%sMarkov" % ("" if harmonicOption else "no", "" if markovOption else "no")+os.sep
                        for attackersOption in ["no", "01", "02", "05", "10"]:
                            resultsDict["scenario"][i]["harmonic"][harmonicOption]["markov"][markovOption]["attackers"][attackersOption] = {"fusion":{}}
                            for fusionAlgorithm in [6, 7, 11, 12]:
                                 resultsDict["scenario"][i]["harmonic"][harmonicOption]["markov"][markovOption]["attackers"][attackersOption]["fusion"][fusionAlgorithm] = {"numUes":{}}
                                 for numUes in [10, 20, 50, 100]:
                                     resultsDict["scenario"][i]["harmonic"][harmonicOption]["markov"][markovOption]["attackers"][attackersOption]["fusion"][fusionAlgorithm]["numUes"][numUes] = {"channel":{}}

                                     sensingListFile = harmonicMarkovOptionPath+"ues_"+str(numUes)+"_"+attackersOption+"Attackers"+os.sep+fusionAlgorithms[fusionAlgorithm]+os.sep+"sensing_list.txt"

                                     with open(sensingListFile, "r") as f:
                                         lines = f.readlines()
                                         lines = lines[2:] #Skip first two lines

                                         prevLine = 0
                                         for channel in range(4):
                                             channelLines = lines[:4]
                                             lines = lines[4:]

                                             #Extract numbers from e.g. From 9976 fusions, 89 were false positive and 1360 were false negative.
                                             ans = regexBitsPerUeC.search(channelLines[0]).groups()
                                             avgBitsPerUe = float(ans[0])
                                             ans = regexRawC.search(channelLines[1]).groups()
                                             fusions, falsePositives, falseNegatives = int(ans[0]), int(ans[1]), int(ans[2])
                                             framesThatCouldBeFalsePositives = int(regexFalseC.search(channelLines[2]).groups()[0])
                                             framesThatCouldBeFalseNegatives = int(regexFalseC.search(channelLines[3]).groups()[0])

                                             result = {
                                                 "avgBitsPerUe"       : avgBitsPerUe,
                                                 "totalFusions"       : fusions,
                                                 "totalFalsePositives": falsePositives,
                                                 "totalFalseNegatives": falseNegatives,
                                                 "framesPuWasInactive": framesThatCouldBeFalsePositives,
                                                 "framesPuWasActive"  : framesThatCouldBeFalseNegatives
                                             }
                                             resultsDict["scenario"][i]["harmonic"][harmonicOption]["markov"][markovOption]["attackers"][attackersOption]["fusion"][fusionAlgorithm]["numUes"][numUes]["channel"][channel] = result
                                             lines = lines[1:] #Skip empty line between channels

        with open(baseDir+"results.json", "w") as f:
            import json
            json.dump(resultsDict, f, indent=2)
            pass
    else:
        simulationScenarios = os.listdir(baseDir)
        #print (simulationScenarios)

        for scenario in simulationScenarios:
            scenarioDict = {}
            argList = []

            #Load base scenario
            with open(baseDir+scenario+"\\simulationParameters.json", "r") as file:
                scenarioDict = json.load(file)

            #Save a new copy for each fusion
            for fusionAlgorithm in [1, 6, 10, 11, 12, 13]:
                scenarioDict["SimulationParameters"]["fusionAlgorithm"] = fusionAlgorithm
                scenarioDict["SimulationParameters"]["fusionAlgorithmName"] = fusionAlgorithms[fusionAlgorithm]

                simFolder = baseDir + scenario + "\\" + fusionAlgorithms[fusionAlgorithm] + "\\"
                argList += [[simFolder]]

                if os.path.exists(simFolder) and not os.path.exists(simFolder + "sensing.png"):
                    import shutil

                    shutil.rmtree(simFolder, ignore_errors=True)

                if not os.path.exists(simFolder):
                    os.mkdir(simFolder)

                simFile = simFolder + "simulationParameters.json"

                if not os.path.exists(simFile):
                    with open(simFile, "w") as file:
                        file.write(json.dumps(scenarioDict, indent=4))

            #Run simulation
            with multiprocessing.Pool(processes=4) as pool:
                pool.starmap(runScenario, argList)

        #Replicate a single base scenario (simulationParameters.json) with all fusion


    pass
