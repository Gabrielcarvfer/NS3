#!/usr/bin/python3
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import math
import decimal


def plot_pu_transmission(standalone_plot=False, ax1=None):
    bufferFileIn = ""

    with open("./build/bin/spectrum-analyzer-output-9-0.tr", 'r') as file:
        bufferFileIn = file.readlines()

    plt.ioff()

    #Read each line contains timestamp frequency and psd
    timestampDict = {}
    freqs = {}
    for line in bufferFileIn:
        if len(line) is 1:#skip empty lines
            continue

        lineContents = line.split()
        timestamp = float(lineContents[0])
        freq      = float(lineContents[1])
        psd       = float(lineContents[2])

        if timestamp not in timestampDict:
            timestampDict[timestamp] = {}

        if freq not in timestampDict[timestamp]:
            timestampDict[timestamp][freq] = psd

        if freq not in freqs:
        	freqs[freq] = 0

        pass


    ax = None
    if standalone_plot:
        fig = plt.figure()
        #ax  = fig.add_subplot(111, projection='3d')
        ax = Axes3D(fig)
    else:
        if ax1 is None:
            exit(-1)
        else:
            ax = ax1


    orderedTimestamps = list(sorted(timestampDict.keys()))
    orderedTimestampsMs = [x*1000 for x in orderedTimestamps] # seconds to milliseconds

    #Labels in english
    #ax.set_xlabel('Time (ms)', )
    #ax.set_ylabel('Measured PSD(dBW/Hz)')

    #Labels in portuguese
    ax.set_xlabel('Tempo (ms)', )
    ax.set_ylabel('Potência (dBW)')

    ax.tick_params('y')
    yticks = [-float(x) for x in range(75, 100, 5)]

    msList = [float(x) for x in range(20000)]#5k ms = 5s = simulation time

    #for freq in list(timestampDict.values[0].values()):
    for freq in list(freqs.keys()):
        psd_list = []

        #To fill or not to fill empty timestamps with background noise or interpolate?
        #for ms in msList:
        #    if ms in orderedTimestampsMs:
        #        psd_val = timestampDict[timestamp][freq]
        #        psd_val_adjusted = 10*math.log10(psd_val) #PSD (dBW/Hz)
        #        psd_list += [psd_val_adjusted]
        #    else:
        #        psd_list += [-100.0] #background noise
        #    pass

        #ax.plot(msList, psd_list)

        for timestamp in orderedTimestamps:
            psd_val = timestampDict[timestamp][freq]
            psd_val_adjusted = 10*math.log10(psd_val) #PSD (dBW/Hz)
            psd_list += [float(round(decimal.Decimal(psd_val_adjusted.__repr__()),2))]

        ax.plot(orderedTimestampsMs, psd_list, zs=freq, label="%f" %freq)
        #ax.legend()
        plt.show(block=False)
        pass
    pass


if __name__ == "__main__":
    plot_pu_transmission(standalone_plot=True)
    input()
    pass