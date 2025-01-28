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

for label in [dlLabel, ulLabel]:
    x_axis = [x['ts'] for x in contents[label]]
    y_axis = [x['thr'] for x in contents[label]]
    plt.plot(x_axis, y_axis, label=("DL" if label == dlLabel else "UL"))
plt.ylabel("Throughput (Mbps)")
plt.xlabel("Time (ns)")
plt.legend()
plt.tight_layout()
plt.show()