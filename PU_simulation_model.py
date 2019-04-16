import json
import random

class PU_Model():
    num_PU = 0
    PUs = {}
    def __init__(self, coordinate_tuple, transmission_power, channel, duty_cycle, period):
        self.dictio = {}
        self.dictio["position"]           = coordinate_tuple
        self.dictio["transmission_power"] = transmission_power
        self.dictio["channel"]            = channel
        self.dictio["duty_cycle"]         = duty_cycle
        self.dictio["period"]             = period
        self.dictio["num"]                = PU_Model.num_PU

        PU_Model.PUs[PU_Model.num_PU] = self.dictio
        PU_Model.num_PU += 1
        return

    @staticmethod
    def to_json():
        outputBuffer = json.dumps(PU_Model.PUs, indent=4)#make json readable by indenting it
        return outputBuffer

def generateRandomPUs(
                      numPUs         = 4,           #
                      xRange         = (0, 100e3),  # m
                      yRange         = (0, 100e3),  # m
                      zRange         = (0, 0.1),    # m
                      txPowerRange   = (0, 60),     # dBm
                      numChannels    = 4,           #
                      dutyCycleRange = (0.1, 0.2),  # percentage of period to transmit and precision
                      txPeriodRange  = (1, 5)       # period between Txs
                      ):

    for pu in range(numPUs):
        x              = random.uniform(*xRange)
        y              = random.uniform(*yRange)
        z              = random.uniform(*zRange)
        txPower        = random.uniform(*txPowerRange)
        channel        = random.randrange(0, numChannels-1)
        dutyCycle      = random.uniform(*dutyCycleRange)
        txPeriod       = random.uniform(*txPeriodRange)

        PU_Model((x, y, z), txPower, channel, dutyCycle, txPeriod)

if __name__ == "__main__":
    numPUs = 4

    generateRandomPUs()

    #PUs = []
    #               (  X       Y       Z     dBW  #channel  duty_cycle  period)
    #PUs += [PU_Model((00.0e3, 00.0e3, 00.0e3), 20,        0,        0.1,      5)]
    #PUs += [PU_Model((50.0e3, 00.0e3, 00.0e3), 20,        0,        0.1,      5)]
    #PUs += [PU_Model((50.0e3, 50.0e3, 00.0e3), 20,        0,        0.1,      5)]
    #PUs += [PU_Model((50.0e3, 50.0e3, 00.0e3), 20,        0,        0.1,      5)]

    with open("PU_geo_database.json","w") as file:
        file.write(PU_Model.to_json())
