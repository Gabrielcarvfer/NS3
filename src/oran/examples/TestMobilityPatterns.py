#! /usr/bin/env python3

# Copyright (c) 2024 Centre Tecnologic de Telecomunicacions de Catalunya (CTTC)
#
# SPDX-License-Identifier: GPL-2.0-only

class BoundingBox:
    def __init__(self, xMin, xMax, yMin, yMax):
        self.xMin = xMin
        self.xMax = xMax
        self.yMin = yMin
        self.yMax = yMax

    def x_length(self):
        return self.xMax - self.xMin

    def y_length(self):
        return self.yMax - self.yMin

    def shortest_length(self):
        return min(self.x_length(), self.y_length())


import math

def pattern1_upwards_triangle(steps, boundaries: BoundingBox):
    side = boundaries.shortest_length()

    x = [boundaries.xMin]
    y = [boundaries.yMin]
    cos = math.cos(math.pi / 3)
    sin = math.sin(math.pi / 3)
    step_size = 3 * side / steps
    current_length = 0
    #  0 /\ 1
    #   /  \
    #   ----
    #     2
    for step in range(0, steps):
        if current_length // side == 0:
            x.append(x[-1] + step_size * cos)
            y.append(y[-1] + step_size * sin)
        elif current_length // side == 1:
            x.append(x[-1] + step_size * cos)
            y.append(y[-1] - step_size * sin)
        else:
            x.append(x[-1] - step_size)
            y.append(y[-1])
        current_length += step_size
    return x, y


def pattern2_downwards_triangle(steps, boundaries: BoundingBox):
    #    /\
    #   /  \
    #   ----
    x, y = pattern1_upwards_triangle(steps, boundaries)

    #   ----
    #   \  /
    #    \/
    x = list(reversed(x))
    y = list(map(lambda z: boundaries.yMax + boundaries.yMin - z, reversed(y)))
    return x, y


def pattern3_hourglass(steps, boundaries: BoundingBox):
    cos = math.cos(math.pi / 3)
    sin = math.sin(math.pi / 3)
    side = boundaries.shortest_length() * (1/sin) / 2

    x = [boundaries.xMin + (boundaries.x_length()-side)/2]
    y = [boundaries.yMin]
    step_size = 6 * side / steps
    steps_per_side = steps / 6
    #     3
    #   ----
    # 2 \  / 4
    #    \/
    #    /\
    # 5 /  \ 1
    #   ----
    #     0
    for step in range(0, steps):
        if step // steps_per_side == 0:
            x.append(x[-1] + step_size)
            y.append(y[-1])
        elif step // steps_per_side in [1, 2]:
            x.append(x[-1] - step_size * cos)
            y.append(y[-1] + step_size * sin)
        elif step // steps_per_side == 3:
            x.append(x[-1] + step_size)
            y.append(y[-1])
        elif step // steps_per_side in [4, 5]:
            x.append(x[-1] - step_size * cos)
            y.append(y[-1] - step_size * sin)
    return x, y


def pattern4_square(steps, boundaries: BoundingBox):
    side = boundaries.shortest_length()

    x = [boundaries.xMin]
    y = [boundaries.yMin]
    step_size = 4 * side / steps
    steps_per_side = steps / 4
    #      1
    #   +-----+
    #   |     |
    # 0 |     | 2
    #   +-----+
    #     3
    for step in range(1, steps):
        if step // steps_per_side == 0:
            x.append(x[-1])
            y.append(y[-1] + step_size)
        elif step // steps_per_side == 1:
            x.append(x[-1] + step_size)
            y.append(y[-1])
        elif step // steps_per_side == 2:
            x.append(x[-1])
            y.append(y[-1] - step_size)
        else:
            x.append(x[-1] - step_size)
            y.append(y[-1])
    return x, y


def pattern5_diamond(steps, boundaries: BoundingBox):
    cos = math.cos(math.pi / 3)
    sin = math.sin(math.pi / 3)
    side = boundaries.shortest_length() * (1/sin) / 2

    x = [(boundaries.xMax + boundaries.xMin) / 2]
    y = [boundaries.yMin]
    step_size = 4 * side / steps
    steps_per_side = steps / 4
    # 1  /\  2
    #   /  \
    #   \  /
    # 0  \/  3
    for step in range(0, steps):
        if step // steps_per_side == 0:
            x.append(x[-1] - step_size * cos)
            y.append(y[-1] + step_size * sin)
        elif step // steps_per_side == 1:
            x.append(x[-1] + step_size * cos)
            y.append(y[-1] + step_size * sin)
        elif step // steps_per_side == 2:
            x.append(x[-1] + step_size * cos)
            y.append(y[-1] - step_size * sin)
        else:
            x.append(x[-1] - step_size * cos)
            y.append(y[-1] - step_size * sin)
    return x, y


def pattern_n_periods(steps, boundaries: BoundingBox, periods=2):
    x = [0]
    y = [0]

    period_per_trip = periods / 2
    steps_per_trip = steps // 2
    angle_per_step = period_per_trip*2*math.pi/steps_per_trip
    # ==================>
    for step in range(0, steps_per_trip):
        x.append(x[-1] + abs(math.sin(step*angle_per_step)))
        y.append(y[-1] + math.cos(step*angle_per_step))
    # <==================
    for step in range(steps_per_trip, steps_per_trip*2):
        x.append(x[-1] - abs(math.sin(step * angle_per_step)))
        y.append(y[-1] + math.cos(step * angle_per_step))

    # Figure out maximum dimensions of the figure and rescale to fit the bounding box
    xMax = max(x)
    xMin = min(x)
    if xMin < 0:
        xMax -= xMin
        x = list(map(lambda z: z - xMin, x))
        xMin = 0
    yMax = max(y)
    yMin = min(y)
    if yMin < 0:
        yMax -= yMin
        y = list(map(lambda z: z-yMin, y))
        yMin = 0
    x = list(map(lambda z: boundaries.xMin+z*(boundaries.xMax-boundaries.xMin)/(xMax-xMin), x))
    y = list(map(lambda z: boundaries.yMin+z*(boundaries.yMax-boundaries.yMin)/(yMax-yMin), y))
    return x, y


def pattern6_1period(steps, boundaries: BoundingBox):
    return pattern_n_periods(steps, boundaries, 1)


def pattern7_2period(steps, boundaries: BoundingBox):
    return pattern_n_periods(steps, boundaries, 2)


def pattern8_3period(steps, boundaries: BoundingBox):
    return pattern_n_periods(steps, boundaries, 3)


movement_patterns = [
    pattern1_upwards_triangle,
    pattern2_downwards_triangle,
    pattern3_hourglass,
    pattern4_square,
    pattern5_diamond,
    pattern6_1period,
    pattern7_2period,
    pattern8_3period,
]

import matplotlib
matplotlib.use('TkAgg')

import matplotlib.pyplot as plt
steps = 120
boundaries = BoundingBox(800, 2400, 800, 2400)#0, 100, 0, 100)
fig, axes = plt.subplots(nrows=2, ncols=4, squeeze=False, sharex=True, sharey=True)
#axes[0][0].set_xticks([0, 10])
#axes[0][0].set_yticks([0, 10])
for i, pattern in enumerate(movement_patterns):
    axes[i//4][i%4].plot(*pattern(steps, boundaries), label="Python")

import json, os
ns3_directory = os.path.dirname(os.path.abspath(__file__))
while "ns3" not in os.listdir(ns3_directory):
    ns3_directory = os.path.dirname(ns3_directory)

filename = f"{ns3_directory}/build/src/oran/examples/mobility_patterns.json"
if not os.path.exists(filename):
    raise Exception("Run TestMobilityPatterns first!")

with open(filename, "r") as f:
    movement_patterns = json.load(f)['mobilityPatterns']
for i, pattern in enumerate(movement_patterns):
    axes[i//4][i%4].plot(pattern['x'], pattern['y'], label="C++")
plt.legend()
plt.show(block=True)
