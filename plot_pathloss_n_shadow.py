#!/usr/bin/python3
import matplotlib.pyplot as plt
import numpy
bufferFile = ""
with open("./build/bin/loss_n_shadow.txt",'r') as file:
    bufferFile = file.readlines()

plt.ioff()


ues_dict = {}
maxSinr = -10000000
for ue_str in bufferFile:
    y      = ue_str.split(sep=' ')
    ue     = y[0]
    loss   = float(y[1])
    shadow = float(y[2])


    if ue not in ues_dict.keys():
        #Create registry
        ues_dict[ue] = {}
        ues_dict[ue]["pathloss"] = []
        ues_dict[ue]["shadow"] = []

    ues_dict[ue]["pathloss"] += [ loss ]
    ues_dict[ue]["shadow"]   += [ shadow ]

#print(ues_dict)

fig,(ax, ax2, ax3) = plt.subplots(nrows=3)

minLen = 10000
for ue in ues_dict:
    ueLen = len(ues_dict[ue]["pathloss"])
    if ueLen < minLen:
        minLen = ueLen

    ueLen = len(ues_dict[ue]["shadow"])
    if ueLen < minLen:
        minLen = ueLen


x = list(range(0, minLen, 1))
import statistics
for ue in ues_dict:
    ax.set_xlabel('tick', )
    ax.set_ylabel('pathloss (dB)')
    ax.tick_params('y')
    ax2.set_xlabel('tick')
    ax2.set_ylabel('shadow (dB)')
    ax2.tick_params('y')
    ax3.set_xlabel('value')
    ax3.set_ylabel('freq')
    ax3.tick_params('y')
    ax.plot(x,ues_dict[ue]['pathloss'][:minLen],alpha=0.5)
    ax2.plot(x,ues_dict[ue]["shadow"][:minLen],alpha=0.5)
    ax3.hist(ues_dict[ue]["shadow"],alpha=0.5)
    plt.show(block=False)
    #plt.savefig("%s.jpg" % ue)
    print("Ue ", ue, " mean ", statistics.mean(ues_dict[ue]["shadow"]), " stdDev ", statistics.stdev(ues_dict[ue]["shadow"]))
    pass

print("Done")
input()
pass
