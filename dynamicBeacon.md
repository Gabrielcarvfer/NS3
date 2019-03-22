---
layout: page
title: 802.11 dynamic beacon
permalink: /dynamicBeacon/
---

## What is it?
dynamicBeacon is a set of modifications to the 802.11 standards implemented in the ns-3 simulator. These modifications implement a beacon backoff technique to reduce/increase the transmission of beacon frames when network nodes are mostly static/moving, while trying to keep association/dissociation times low.

## How to cite?
Check the paper in the link: [https://link.springer.com/chapter/10.1007%2F978-3-030-15032-7_55](https://link.springer.com/chapter/10.1007%2F978-3-030-15032-7_55)

## How to install?
The first step is cloning the [NS3.27-wifiDynamicBeacon](https://github.com/Gabrielcarvfer/NS3/tree/NS3.27-wifiDynamicBeacon).

As in the installation instructions for the [ns-3 with CMake](/NS3/installation), before proceeding you will need at least g++, make and cmake.

After downloading and installing these tools, you can either run cmake manually, as follows
```
mkdir cmake
cd cmake
cmake ..
```
or you can use an IDE that supports CMake projects (Jetbrains CLion is the best one), that will load and run CMake automatically after opening the project folder.

After it finishes, you will have multiple targets (for libraries and executables).

You can change the configuration in the editing the main CMakeLists.txt or pass the arguments throught the command line. Every flag change will require to re-run the cmake command.

You can build your target with make. 

## How to use?
An example is provided in the scratch folder (/contrib/gabrielcarvfer/wifi/examples/dynamic_beacon3.cc), that can be built with `make dynamic_beacon3`. Pcap files with the outputs will be generated in /build/bin folder.

## To-Do
1. Update to the latest ns-3 build
