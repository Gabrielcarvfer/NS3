distance_to_power = []
with open("distance.txt", "r") as f:
    contents = f.readlines()
    for line in contents:
        values = line.split(',')
        if len(values) != 2:
            continue
        distance_to_power.append((float(values[1]), float(values[0])))

distance_to_power = list(sorted(distance_to_power, key=lambda x: x[0], reverse=True))

import scipy
import numpy as np

power = list(map(lambda x: x[0], distance_to_power))
distance = list(map(lambda x: x[1], distance_to_power))

def func (x, a, b):
    return a * x + b

popt, perr = scipy.optimize.curve_fit(func, power, distance, method="dogbox")

def bound_func(x):
    return func(x, *popt)

import matplotlib.pyplot as plt
plt.scatter(power, distance)

#def bound_func(x):
#    return 114.285*np.power(-3.5, x)

plt.scatter(power, list(map(bound_func, power)))
plt.show()
print(popt)
pass
