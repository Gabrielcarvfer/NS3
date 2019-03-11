#!/usr/bin/python3

#Primary script for plotting sensing results of the test_scratch simulation (collaborative_sensing.png is an example)

from plot_pu_detection import plot_pu_detection_by_ues
from plot_schedulerInputVSOutput import plot_scheduler_input_n_output
from plot_pu_transmission import plot_pu_transmission

import matplotlib.pyplot as plt


def plot_collaborative_sensing_data():
	#Plot figure with 4 subplots sharing the x-axis
    fig, rows = plt.subplots(nrows=4,figsize=(30,10),dpi=150, sharex=True)

    #Plot PU PSD (dBW/Hz) measured by a spectrumAnalyzer
    plot_pu_transmission(ax1=rows[0])

    #Plot PU detection by UEs and Average SINR
    plot_pu_detection_by_ues(ax1=rows[1], ax2=rows[2])

    #Plot eNB scheduler input and output
    # white: unallocated RBG and PU was not detected
    # red  : unallocated RBG, PU was detected previously by one or more UE(s)
    # blue :   allocated RBG, PU was not detected/reported yet    
    plot_scheduler_input_n_output(ax1=rows[3])

    fig.align_labels()
    plt.show()
    pass


if __name__ == "__main__":
    plot_collaborative_sensing_data()
    input()
    pass