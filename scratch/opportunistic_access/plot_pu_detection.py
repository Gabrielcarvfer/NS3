#!/usr/bin/python3
import matplotlib.pyplot as plt
import numpy


def plot_pu_detection_by_ues(standalone_plot=False,ax1=None,ax2=None, subchannel=None, col=None, baseFolder="../../build/bin/"):
    bufferFile = ""

    plot_pu_detection_file = "plot_pu.txt"
    if subchannel:
        plot_pu_detection_file = "plot_pu_group.txt"

    with open(baseFolder + plot_pu_detection_file,'r') as file:
        bufferFile = file.readlines()

    plt.ioff()


    ues_dict = {}
    maxSinr = -10000000

    if subchannel is None:
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
    else:
        for ue_str in bufferFile:
            y = ue_str.split(sep=':')
            if y[0] not in ues_dict.keys():
                #Create registry
                ues_dict[y[0]] = {}

                detectionGroups = y[1].split('][')[1:-1]
                # Read detection status
                ues_dict[y[0]]["PU_detected"] = []
                for detectionStatus in detectionGroups:
                    ues_dict[y[0]]["PU_detected"] += [[float(k) for k in detectionStatus.split()]]
                temp = [detectionStatus[col] for detectionStatus in ues_dict[y[0]]["PU_detected"]]

                while len(temp) < 10000:
                    temp += [temp[-1]]

                ues_dict[y[0]]["PU_detected"] = temp
            else:
                sinrGroups = y[1].split('][')[1:-1]
                #Read AvgSinr
                ues_dict[y[0]]["AvgSinr"] = []
                for sinrGroup in sinrGroups:
                    ues_dict[y[0]]["AvgSinr"]    += [[ float(k) for k in sinrGroup.split()]]
                temp = [sinrGroup[col] for sinrGroup in ues_dict[y[0]]["AvgSinr"]]

                while len(temp) < 10000:
                    temp += [temp[-1]]

                ues_dict[y[0]]["AvgSinr"] = temp

                #ue_max_sinr = max(ues_dict[y[0]]["AvgSinr"])
                #if ue_max_sinr > maxSinr:
                #    maxSinr = ue_max_sinr
            pass

    if standalone_plot:
        fig,ax2 = plt.subplots(nrows=1)
    else:
        if ax2 is None:
            exit(-1)

    x = list(range(0,10000,1))

    #print("#UEs=",len(ues_dict))

    for ue in ues_dict:
        #Labels in english
        #ax1.set_xlabel('Time (ms)', )
        #ax1.set_ylabel('PU detected (bool)')
        #ax1.set_yticklabels(["False","True"])
        ax2.set_xlabel('Time (ms)')
        ax2.set_ylabel('Avg. SINR (dB)')

        #Labels in portuguese
        #ax1.set_xlabel('Tempo (ms)', )
        #ax1.set_ylabel('PU detectado')
        #ax1.set_yticklabels(["Não","Sim"])
        #ax2.set_xlabel('Tempo (ms)')
        #ax2.set_ylabel('SINR médio (dB)')


        #ax1.tick_params('y')
        #ax1.minorticks_off()
        #ax1.set_yticks([0.0, 1.0])
        ax2.tick_params('y')

        #ax1.plot(x,ues_dict[ue]['PU_detected'],alpha=0.5)
        ax2.plot(x,ues_dict[ue]["AvgSinr"],alpha=0.5)

        if(standalone_plot):
            plt.show(block=False)
        pass


if __name__ == "__main__":
    plot_pu_detection_by_ues(standalone_plot=True)
    input()
    pass
