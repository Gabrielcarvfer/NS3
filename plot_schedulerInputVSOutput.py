#!/usr/bin/python3
import matplotlib.pyplot as plt
import numpy

def plot_scheduler_input_n_output(standalone_plot=False, ax1=None, subchannel=False, col=None, baseFolder="./build/bin/"):
    bufferFileIn = ""
    bufferFileOut = ""

    with open(baseFolder + "schedulerInput.txt", 'r') as file:
        bufferFileIn = file.readlines()

    with open(baseFolder + "schedulerOutput.txt", 'r') as file:
        bufferFileOut = file.readlines()

    plt.ioff()

    #Discard first lines
    bufferFileIn = bufferFileIn[1:]
    bufferFileOut = bufferFileOut[1:]

    bufferFileIn = bufferFileIn[:-3]
    bufferFileOut = bufferFileOut[:-3]


    inputAndOutputBitmapPerInterval = {}

    for intervalBitmap in bufferFileIn:
        y = intervalBitmap.split(sep=':')

        interval = y[0] #"+350000000.0ns"
        interval = interval.split(sep=".")#["+350000000", "0ns"]
        interval = interval[0]#"+350000000"
        interval = int(interval)#350000000
        interval /= 1000000 #350

        inputAndOutputBitmapPerInterval[interval] = [int(y[1],2), 0]

    for intervalBitmap in bufferFileOut:
        y = intervalBitmap.split(sep=':')

        interval = y[0] #"+350000000.0ns"
        interval = interval.split(sep=".")#["+350000000", "0ns"]
        interval = interval[0]#"+350000000"
        interval = int(interval)#350000000
        interval /= 1000000 #350

        if interval not in inputAndOutputBitmapPerInterval:
            inputAndOutputBitmapPerInterval[interval] = [0, int(y[1],2)]
        else:
            inputAndOutputBitmapPerInterval[interval][1] = int(y[1],2)

    ax = None
    ax_1 = None
    if standalone_plot:
        fig, ax = plt.subplots()
    else:
        if ax1 is None:
            exit(-1)
        else:
            ax = ax1

    sortedInputOutputBitmapKeys = list(sorted(inputAndOutputBitmapPerInterval.keys()))

    #Labels in english
    ax.set_xlabel('Time (ms)', )
    ax.set_ylabel('RBG status')

    #Labels in portuguese
    #ax.set_xlabel('Tempo (ms)', )
    #ax.set_ylabel('Estado do RBG')

    #ax.grid(True)
    #ax.tick_params('y')
    #yticks = [x for x in list(range(0, 60, 10))]
    xticks = [float(x) for x in range(20000)]

    base = 0
    top  = 50
    #separate channel into subchannels for plotting
    ncol = col - 3
    ncol = -ncol
    if subchannel:
        base = 11+(ncol-1)*13 if ncol>0 else 0
        top  = (11+(ncol)*13) % 51 if ncol>0 else 11
        #print("base ", base, " top ", top)

    for i in range(base, top):

        input_barh = []
        output_barh = []

        for interval in sortedInputOutputBitmapKeys:

            bitmaps = inputAndOutputBitmapPerInterval[interval]
            marked = False
            if ( (bitmaps[0]>>i) & 0x01):
                    input_barh += [(float(interval),1.0)] #Blocks occupied before scheduling (unexpected access reported by UEs, may be a PU,SU,whatever)
                    marked = True
            if ( (bitmaps[1]>>i) & 0x01) and not marked:
                    output_barh += [(float(interval),1.0)] #Blocks occupied by transmissions scheduled by the eNB

        ax.broken_barh(input_barh,(i,1.0), facecolors="red", alpha=0.7) #Blocks occupied before scheduling (unexpected access reported by UEs, may be a PU,SU,whatever)
        ax.broken_barh(output_barh,(i,1.0), facecolors="blue", alpha=0.5) #Blocks occupied before scheduling (unexpected access reported by UEs, may be a PU,SU,whatever)
        #ax.set_yticks(yticks)
        #ax.set_xticks(xticks)

        if(standalone_plot):
            plt.show(block=False)
        pass
    pass


    return

if __name__ == "__main__":
    plot_scheduler_input_n_output(standalone_plot=True)
    input()
    pass