import json
import random
from decimal import Decimal


class PU_Model():
    num_PU = 0
    PUs = {}
    def __init__(self, coordinate_tuple, transmission_power, bandwidth, carrier_frequency, duty_cycle, period):
        self.dictio = {}
        self.dictio["position"]           = coordinate_tuple
        self.dictio["transmission_power"] = transmission_power
        self.dictio["bw"]                 = bandwidth
        self.dictio["fc"]                 = carrier_frequency
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
                      numSubChannels = 4,           #
                      dutyCycleRange = (0.1, 0.2),  # percentage of period to transmit and precision
                      txPeriodRange  = (1, 5)       # period between Txs
                      ):

    base_carrier_frequency = 2.200e9
    carrier_frequency = base_carrier_frequency + 0.010e9
    channel_bandwidth = 0.020e9
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
        x                 = round( random.uniform(*xRange)          , 2)
        y                 = round( random.uniform(*yRange)          , 2)
        z                 = round( random.uniform(*zRange)          , 2)
        txPower           = round( random.uniform(*txPowerRange)    , 2)
        dutyCycle         = round( random.uniform(*dutyCycleRange)  , 2)
        txPeriod          = round( random.uniform(*txPeriodRange)   , 2)

        channel           = random.randrange(0, numSubChannels-1)
        carrier_frequency = round( subchannel_carrier_freq[channel]["freq"] , 2)
        bandwidth         = round( subchannel_carrier_freq[channel]["bw"]   , 2)

        PU_Model((x, y, z), txPower, bandwidth, carrier_frequency, dutyCycle, txPeriod)

if __name__ == "__main__":
    numPUs = 4

    generateRandomPUs()

    #PUs = []
    #               (  X       Y       Z     dBW  #channel  duty_cycle  period)
    #PUs += [PU_Model((00.0e3, 00.0e3, 00.0e3), 20,        0,        0.1,      5)]
    #PUs += [PU_Model((50.0e3, 00.0e3, 00.0e3), 20,        0,        0.1,      5)]
    #PUs += [PU_Model((50.0e3, 50.0e3, 00.0e3), 20,        0,        0.1,      5)]
    #PUs += [PU_Model((50.0e3, 50.0e3, 00.0e3), 20,        0,        0.1,      5)]

    with open("PU_geo_database.json", "w") as file:
        file.write(PU_Model.to_json())
