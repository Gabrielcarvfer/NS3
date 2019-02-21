#!/usr/bin/python3
import matplotlib.pyplot as plt
import numpy
bufferFile = ""
with open("./build/bin/plot_pu.txt",'r') as file:
    bufferFile = file.readlines()

plt.ioff()


ues_dict = {}
maxSinr = -10000000
for ue_str in bufferFile:
    y = ue_str.split(sep=':')
    if y[0] not in ues_dict.keys():
        #Create registry
        ues_dict[y[0]] = {}

        # Read PU_detected
        ues_dict[y[0]]["PU_detected"] = [ float(k) for k in y[1].split()]
    else:
        #Read AvgSinr
        ues_dict[y[0]]["AvgSinr"]    = [ float(k) for k in y[1].split()]
        ue_max_sinr = max(ues_dict[y[0]]["AvgSinr"])
        if ue_max_sinr > maxSinr:
            maxSinr = ue_max_sinr
    pass

fig,(ax, ax2) = plt.subplots(nrows=2)

x = list(range(0,4999,1))

print("#UEs=",len(ues_dict))

for ue in ues_dict:
    #ax.cla()
    #ax2.cla()
    ax.set_xlabel('time (ms)', )
    ax.set_ylabel('PU detected (bool)')
    ax.tick_params('y')
    ax2.set_xlabel('time (ms)')
    ax2.set_ylabel('avg sinr (dB)')
    ax2.tick_params('y')
    ax.plot(x,ues_dict[ue]['PU_detected'],alpha=0.5)
    #normalizedSinr = [k/maxSinr for k in ues_dict[ue]['AvgSinr']]
    #ax2.plot(x,normalizedSinr,alpha=0.5)
    ax2.plot(x,ues_dict[ue]["AvgSinr"],alpha=0.5)
    plt.show(block=False)
    #plt.savefig("%s.jpg" % ue)
    pass

print("Done")
input()
pass