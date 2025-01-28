import os.path

from matplotlib import pyplot as plt
import json

currDir = os.path.abspath(os.path.dirname(__file__))
with open(f"{currDir}/../../../build/src/oran/examples/ueThrLog.json", "r") as f:
    contents = json.load(f)

maxValues = [max([x['thr'] for x in contents[label]]) for label in contents]
sortedValues = list(sorted(maxValues, reverse=True))

dlLabel = list(contents.keys())[maxValues.index(sortedValues[0])]
ulLabel = list(contents.keys())[maxValues.index(sortedValues[1])]
from statistics import mean
for label in [dlLabel, ulLabel]:
    x_axis = [x['ts'] for x in contents[label]]
    y_axis = [x['thr'] for x in contents[label]]
    x_axis_instantaneous = [0]
    y_axis_instantaneous = [0]
    x_axis_plot = []
    y_axis_plot = []
    for i in range(1, len(y_axis)):
        bytes_transmitted = y_axis[i]*x_axis[i] - y_axis[i-1]*x_axis[i-1]
        timespan = x_axis[i]-x_axis[i-1]
        instant_thr = bytes_transmitted/timespan
        if instant_thr > 1:
            x_axis_instantaneous.append(x_axis[i])
            y_axis_instantaneous.append(instant_thr)
        x_axis_plot.append(mean(x_axis_instantaneous))
        y_axis_plot.append(mean(y_axis_instantaneous))
        if len(y_axis_instantaneous) > 10:
            x_axis_instantaneous.pop(0)
            y_axis_instantaneous.pop(0)
    plt.plot(x_axis_plot, y_axis_plot, label=("DL" if label == dlLabel else "UL"))
plt.ylabel("Throughput (Mbps)")
plt.xlabel("Time (s)")
plt.legend()
plt.tight_layout()
plt.savefig("ueThrLog.png")