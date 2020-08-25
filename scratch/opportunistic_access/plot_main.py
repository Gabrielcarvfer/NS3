#!/usr/bin/python3

#Primary script for plotting sensing results of the test_scratch simulation (collaborative_sensing.png is an example)

from plot_pu_detection import plot_pu_detection_by_ues
from plot_schedulerInputVSOutput import plot_scheduler_input_n_output
from plot_pu_transmission import plot_pu_transmission
from mpl_toolkits.mplot3d import Axes3D

import matplotlib.pyplot as plt
import os


def plot_collaborative_sensing_data(baseFolder = "../../build/bin"):
	#Plot figure with 4 subplots sharing the x-axis
    fig, axisRows = plt.subplots(nrows=3, ncols=4, sharex="all", sharey="row", figsize=(16,9))

    #For each PU
    for col in range(4):
        colRows = [axisRows[row][col] for row in range(3)]

        #Set channel name
        colRows[0].set_title(label="PU in channel %d" % col)

        #Plot PU PSD (dBW/Hz) measured by a spectrumAnalyzer
        plot_pu_transmission(axs=[colRows[0]], fileName="spectrum-analyzer-output-" + str(17+col) + "-0.tr", baseFolder=baseFolder, col=col)

        #Plot PU detection by UEs and Average SINR
        plot_pu_detection_by_ues(ax2=colRows[1], subchannel=True, col=col, baseFolder=baseFolder)

        #Plot eNB scheduler input and output
        # white: unallocated RBG and PU was not detected
        # red  : unallocated RBG, PU was detected previously by one or more UE(s)
        # blue :   allocated RBG, PU was not detected/reported yet
        plot_scheduler_input_n_output(ax1=colRows[2], subchannel=True, col=col, baseFolder=baseFolder)

    fig.align_labels()
    plt.tight_layout()
    #plt.show(block=False)
    fig.savefig(baseFolder + "sensing.png")
    pass


if __name__ == "__main__":
    baseFolder = os.getcwd()
    if os.path.basename(baseFolder) in ["NS3"]:
        baseFolder = "./build/bin/"
    baseFolder += "\\"
    plot_collaborative_sensing_data(baseFolder=baseFolder)
    pass