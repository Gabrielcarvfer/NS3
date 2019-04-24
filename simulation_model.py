import json
import random
from decimal import Decimal
import os


class SimulationParameters():
    def __init__(self, simulation_time, base_carrier_frequency, channel_bandwidth, fusion_algorithm, propagation_model, PU_models, UE_models, eNB_model):
        self.dictio = {}
        self.dictio["SimulationParameters"] = {}
        self.dictio["SimulationParameters"]["ts"] = simulation_time
        self.dictio["SimulationParameters"]["fc"] = base_carrier_frequency
        self.dictio["SimulationParameters"]["bw"] = channel_bandwidth
        self.dictio["SimulationParameters"]["fusionAlgorithm"] = fusion_algorithm
        self.dictio["SimulationParameters"]["propagationModel"] = propagation_model
        self.dictio["PU"]  = PU_models
        self.dictio["eNB"] = eNB_model
        self.dictio["UE"]  = UE_models

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
    def __init__(self, coordinate_tuple, transmission_power, bandwidth, carrier_frequency, duty_cycle, period):
        self.dictio = {}
        self.dictio["position"]   = coordinate_tuple
        self.dictio["tx_power"]   = transmission_power
        self.dictio["bw"]         = bandwidth
        self.dictio["fc"]         = carrier_frequency
        self.dictio["duty_cycle"] = duty_cycle
        self.dictio["period"]     = period
        self.dictio["num"]        = PU_Model.num_PU

        PU_Model.PUs[PU_Model.num_PU] = self.dictio
        PU_Model.num_PU += 1
        return

    @staticmethod
    def to_json():
        outputBuffer = json.dumps(PU_Model.PUs, indent=4)#make json readable by indenting it
        return outputBuffer

def generateRandomPUs(
                      numPUs         = 4,           #
                      xRange         = (0, 50e3),  # m
                      yRange         = (0, 50e3),  # m
                      zRange         = (0, 0.1),    # m
                      txPowerRange   = (0, 60),     # dBm
                      numSubChannels = 4,           #
                      dutyCycleRange = (0.1, 0.2),  # percentage of period to transmit and precision
                      txPeriodRange  = (1, 5),      # period between Txs
                      central_frequency = 869e6,
                      bandwidth         = 20e6
                      ):

    carrier_frequency = central_frequency
    channel_bandwidth = bandwidth
    uniformly_spaced_channels = True

    subchannel_carrier_freq = {}
    if uniformly_spaced_channels:
        subchannel_bandwidth = channel_bandwidth/numSubChannels
        low_freq_channel = carrier_frequency - (channel_bandwidth / 2)

        for channel in range(numSubChannels):
            subchannel_carrier_freq[channel] = {"freq": low_freq_channel + (subchannel_bandwidth / 2), "bw": subchannel_bandwidth}
            low_freq_channel += subchannel_bandwidth
    else:
        for channel in range(numSubChannels):
            freq = random.uniform(carrier_frequency-(channel_bandwidth/2), carrier_frequency+(channel_bandwidth/2))
            bw   = random.uniform(0.0, channel_bandwidth)


            while round(freq+(bw/2),2) > round(carrier_frequency+(channel_bandwidth/2),2) or\
                    round(freq-(bw/2),2) < round(carrier_frequency-(channel_bandwidth/2),2):
                fhSub = freq + (bw/2)
                fhCh  = carrier_frequency+(channel_bandwidth/2)
                if fhSub > fhCh:
                    bw -= (fhSub-fhCh)
                    bw = bw if bw>0 else -bw

                flSub = freq - (bw/2)
                flCh  = carrier_frequency-(channel_bandwidth/2)
                if flSub < flCh:
                    bw += (flSub-fhCh)
                    bw = bw if bw>0 else -bw

            subchannel_carrier_freq[channel] = {"freq": freq, "bw": bw}

    for pu in range(numPUs):
        txPower           = round( random.uniform(*txPowerRange)    , 2)
        dutyCycle         = round( random.uniform(*dutyCycleRange)  , 2)
        txPeriod          = round( random.uniform(*txPeriodRange)   , 2)

        channel           = random.randrange(0, numSubChannels-1)
        carrier_frequency = round( subchannel_carrier_freq[channel]["freq"] , 2)
        bandwidth         = round( subchannel_carrier_freq[channel]["bw"]   , 2)

        PU_Model(generatePosition(xRange, yRange, zRange), txPower, bandwidth, carrier_frequency, dutyCycle, txPeriod)

def generatePosition(xRange, yRange, zRange):
    x = round(random.uniform(xRange[0][0],xRange[0][1]), 2)
    y = round(random.uniform(yRange[0][0],yRange[0][1]), 2)
    z = round(random.uniform(zRange[0][0],zRange[0][1]), 2)
    return (x,y,z)

def generateScenario(baseFolder):
    xRange = (0, 100e3),  # m
    yRange = (0, 100e3),  # m
    zRange = (0,   0.1),  # m

    generateRandomPUs(numPUs=4, central_frequency=869e6, bandwidth=20e6, txPowerRange=(40, 60), txPeriodRange=(1, 3), xRange=xRange, yRange=yRange, zRange=zRange)

    numUEs = 10
    numENBs = 1

    ueTxPower      = 10 #dBm
    ueAntennaGain  = 0  #dBi
    eNBTxPower     = 53 #dBM
    eNBAntennaGain = 9  #dBi
    propagationModel = "ns3::FriisPropagationLossModel"

    for ue in range(numUEs):
        UE_Model(generatePosition(xRange, yRange, zRange), ueTxPower, ueAntennaGain)

    #for enb in range(numENBs):
    eNB_Model((50e3, 50e3, 0), eNBTxPower, eNBAntennaGain)

    fusionAlgorithm = random.randrange(1, 15)
    while fusionAlgorithm in [5, 14]:
        fusionAlgorithm = random.randrange(1, 15)

    sim = SimulationParameters(10, 869e6, 20e6, fusionAlgorithm, propagationModel, PU_Model.PUs, UE_Model.UEs, eNB_Model.eNBs)

    with open(baseFolder + "simulationParameters.json", "w") as file:
        file.write(sim.to_json())

def generateAndRunScenario(baseFolder):
    if not os.path.exists(baseFolder):
        os.mkdir(baseFolder)

    #Create json file for simulation
    generateScenario(baseFolder)

    #Move python to the target folder
    os.chdir(baseFolder)

    #Launch a process to run the simulation at the same json folder
    import subprocess

    #Run simulation
    response = subprocess.run("bash -c /mnt/f/tools/source/NS3/build/bin/collaborative_sensing_demonstration")

    #Generate the results plot figure and save to the simulation output folder
    response = subprocess.run("python F:\\tools\\source\\NS3\\main.py")


if __name__ == "__main__":
    import multiprocessing

    baseDir = "F:\\sims\\"
    with multiprocessing.Pool(processes=1) as pool:
        argList = []
        for i in range(2):
            argList += [[baseDir+str(i)+"\\"]]
        #print(argList)
        pool.starmap(generateAndRunScenario, argList)

    pass