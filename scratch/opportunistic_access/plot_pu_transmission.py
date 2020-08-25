#!/usr/bin/python3
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import math
import decimal


def plot_pu_transmission(standalone_plot=False, axs=None, fileName=None, baseFolder="../../build/bin/", col=-1):
    bufferFileIn = ""
    if fileName is None:
        fileName = "spectrum-analyzer-output-17-0.tr"

    with open(baseFolder + fileName, 'r') as file:
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
        fig, ax = plt.subplots(nrows=4, sharex=True, sharey=True)
        #ax = Axes3D(fig)
    else:
        if axs is None:
            exit(-1)
        else:
            ax = axs


    orderedTimestamps = list(sorted(timestampDict.keys()))
    orderedTimestampsMs = [x*1000 for x in orderedTimestamps] # seconds to milliseconds

    msList = [float(x) for x in range(20000)]#5k ms = 5s = simulation time

    i = 0
    freq_list = list(freqs.keys())[1:5]
    if col != -1:
    	freq_list = [freq_list[col]]
    	
    for freq in freq_list:

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
            psd_val = 3.98107e-18 if psd_val < 3.98107e-18 else psd_val #if smaller than -174 dBm (noise floor)
            psd_val_adjusted = 10*math.log10(psd_val) #PSD (dBW/Hz)
            psd_list += [round(psd_val_adjusted,2)]


        ax[i].set_ylabel('PSD CH-%d (dBW/Hz)' % (i if col == -1 else col))
        if i != 0:
            ax[i].set_ylabel('PSD CH-%d' % i)

        #Labels in english
        ax[i].set_xlabel('Time (ms)')

        #Labels in portuguese
        #ax[i].set_xlabel('Tempo (ms)')

        ax[i].tick_params('y')
        #yticks = [float(x) for x in range(-20, 100, 20)]
        #ax[i].set_yticks(yticks)

        #ax.plot(orderedTimestampsMs, psd_list, zs=freq, label="%f" %freq)
        ax[i].plot(orderedTimestampsMs, psd_list, label="%f" %freq)
        #ax.legend()
        i+=1
        if(standalone_plot):
            plt.show(block=False)
        pass
    #plt.tight_layout()
    pass


if __name__ == "__main__":
    plot_pu_transmission(standalone_plot=True, fileName="spectrum-analyzer-output-14-0.tr")
    input()
    pass