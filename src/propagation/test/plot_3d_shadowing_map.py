# Build the shadowing map test redirect the output to this file
# ./shadowing_map_test > shadowing_map_10km_cube.txt

shadowing_map_coordinates = {'z':{}}
shadowing_map_lists = [[], [], []]

file_contents = None

import json
with open("../../../build/bin/shadowing_map_10km_cube.json", "r") as f:
    shadowMap = json.load(f)["shadowMap"]

for entry in shadowMap:
    x = entry['x']
    y = entry['y']
    z = entry['z']
    shadowValue = entry['shadowing']
    if z not in shadowing_map_coordinates['z']:
        shadowing_map_coordinates['z'][z] = {'y': {}}
    if y not in shadowing_map_coordinates['z'][z]['y']:
        shadowing_map_coordinates['z'][z]['y'][y] = {'x': {}}
    if x not in shadowing_map_coordinates['z'][z]['y'][y]['x']:
        shadowing_map_coordinates['z'][z]['y'][y]['x'][x] = float(shadowValue)

import matplotlib.pyplot as plt
plt.ioff()
from mpl_toolkits.mplot3d import Axes3D
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
import numpy as np

X_k = np.array(list(shadowing_map_coordinates['z'][0]['y'][0]['x'].keys())[:-2])
Y_k = np.array(list(shadowing_map_coordinates['z'][0]['y'].keys())[:-2])

X = []
Y = []
Z = []
#for y in list(shadowing_map_coordinates['z'][0]['y'].keys()):
#    X_k = list(shadowing_map_coordinates['z'][0]['y'][y]['x'].keys())
#    X.extend(X_k)
#    Y.extend([y]*len(X_k))
#    Z.extend(list(shadowing_map_coordinates['z'][0]['y'][y]['x'].values()))
Ztest = []
for y in list(shadowing_map_coordinates['z'][0]['y'].keys())[:-2]:
    X.append(X_k)
    Y.append([y]*len(Y_k))
    Z.append(np.array(list(shadowing_map_coordinates['z'][0]['y'][y]['x'].values())[:-2], dtype=float))
    Ztest.extend(list(shadowing_map_coordinates['z'][0]['y'][y]['x'].values())[:-2])

import statistics

print("Mean:", statistics.mean(Ztest), ", StdDev:", statistics.stdev(Ztest))

X = np.array(X)
Y = np.array(Y)
Z = np.array(Z, dtype="float64")
ax.plot_surface(X, Y, Z)
ax.set_xlabel("X cell")
ax.set_ylabel("Y cell")
ax.set_zlabel("Shadowing (dB)")
plt.show()

print()