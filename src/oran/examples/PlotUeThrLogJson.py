import os.path
from statistics import harmonic_mean
from matplotlib import pyplot as plt
import json

fig, axis = plt.subplots(figsize=(5, 3), nrows=1, ncols=1, squeeze=True)
currDir = os.path.abspath(os.path.dirname(__file__))
#with open(f"{currDir}/../ueThrLog.json", "r") as f:
with open(f"{currDir}/../../../ueThrLog.json", "r") as f:
    contents = json.load(f)

maxValues = [max([x['bytes'] for x in contents[label]]) for label in contents]
sortedValues = list(sorted(maxValues, reverse=True))

dlLabel = list(contents.keys())[maxValues.index(sortedValues[0])]
ulLabel = list(contents.keys())[maxValues.index(sortedValues[1])]
for label in [dlLabel, ulLabel]:
    x_axis = [x['ts'] for x in contents[label]]
    y_axis = [x['bytes'] for x in contents[label]]
    x_axis_instantaneous = [0]
    y_axis_instantaneous = [0]
    x_axis_plot = []
    y_axis_plot = []
    for i in range(1, len(y_axis)):
        bytes_transmitted = y_axis[i] - y_axis[i-1]
        timespan = x_axis[i] - x_axis[i-1]
        instant_thr = bytes_transmitted*8/(timespan*1000*1000) # Bytes to Mbps
        if instant_thr > 1:
            x_axis_instantaneous.append(x_axis[i])
            y_axis_instantaneous.append(instant_thr)
        x_axis_plot.append(x_axis[i])
        y_axis_plot.append(harmonic_mean(y_axis_instantaneous))
        if len(y_axis_instantaneous) > 10:
            x_axis_instantaneous.pop(0)
            y_axis_instantaneous.pop(0)
    plt.plot(x_axis_plot, y_axis_plot, label=("DL" if label == dlLabel else "UL"))
    print(f"Vazão média {('DL' if label == dlLabel else 'UL')} [Mbps]: {((y_axis[-1]-y_axis[0])*8)/((x_axis[-1]-x_axis[0])*1000*1000):.1f}")
axis.set_ylabel("Vazão [Mbps]")
axis.set_xlabel("Tempo de simulação [s]")
axis.legend(loc="lower right")
fig.tight_layout()
fig.savefig(f"{currDir}/../../../ueThrLog.png", dpi=300)
