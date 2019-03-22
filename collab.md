---
layout: page
title: ns-3-COLAB
permalink: /COLAB/
---

## What is it?
ns-3-COLAB is a set of modifications to the standard LTE implementation of the ns-3 simulator. These modifications implement a simple collaborative sensing cycle and allow the development of new schedulers, collaborative sensing fusion algorithms and dynamic spectrum access research.

## How to cite?
Check the paper in the link: [https://ieeexplore.ieee.org/document/8877232](https://ieeexplore.ieee.org/document/8877232)

## How to install?
The first step is cloning the [NS3.29-cognitive repo](https://github.com/Gabrielcarvfer/NS3/tree/NS3.29-cognitive).

As in the installation instructions for the [ns-3 with CMake](/NS3/installation), before proceeding you will need at least g++, make, cmake, unzip, curl and tar.

After downloading and installing these tools, you can either run cmake manually, as follows
```
mkdir cmake
cd cmake
cmake ..
```
or you can use an IDE that supports CMake projects (Jetbrains CLion is the best one), that will load and run CMake automatically after opening the project folder.

During the `cmake ..` command, [VcPkg](https://github.com/Microsoft/vcpkg) will be compiled and then will download and build required dependencies.

After it finishes, you will have multiple targets (for libraries and executables).

You can change the configuration in the editing the main CMakeLists.txt or pass the arguments throught the command line. Every flag change will require to re-run the cmake command.

You can build your target with make. 

## How to use?
An example is provided in the scratch folder (test-scratch.cc), that can be built with `make test-scratch`.

This example has 10 UEs and 1 eNB, sharing the same channel with a microwave oven and a spectrum analyzer (trace power in the channel). The UEs are transmiting consistently only to generate traffic and provide a workload for the scheduler.

To include new spectrum sensing probability curves/tables, you currently need to include it in the src/lte/model/BLER/oulu_pu_probability.json file. The X-axis (SNR_dB) is the SNR level in dB, the Y-axis (Pd_tot) is the probability of detection [0,1]. The false alarm probability (Pfa) is also required. Current curves were taken from the [5G-RANGE technical report](http://5g-range.eu/wp-content/uploads/2018/04/D4.2-Spectrum-Sensing-to-Complement-Databases.pdf).

To choose between the spectrum sensing probability curves/tables, you currently need to edit the parameter of the JSON function at the beginning of the sensingProcedure function, located in the /src/lte/model/lte-spectrum-phy.cc source file.

To change the UE sensing behavior (e.g. selecting how many and which RBGs to use for the sensing, or only sense on unallocated spots based on the DCI), you currently need to edit the sensingProcedure function.

If your sensing probability curves are for the whole channel, you should mark set the senseRBs option as false in the Sense function, located in /src/lte/model/lte-spectrum-phy.cc source file.

To choose a different collaborative sensing fusion algorithm, you currently need to edit the parameter of the mergeSensingReports() call in the DoSubframeIndication function, located in the src/lte/model/lte-enb-mac.cc source file.

# Be aware that your probability curves are usually based on spectrum sensing techniques dependant on the bandwidth sensed by the UEs. You will need to adjust the amount of RBs/RBGs sensed in your simulations to match this bandwidth.

## How to plot the results?
If you sucessfully ran the test-scratch without modifications, run the `main.py` python script to plot the results.

The script will plot 4 images:
1. The received power on the channel, measured by the spectrum analyzer node (the output is in the build/bin/spectrum-analyzer-x.tr).
2. The detection or not of the PU by the UEs.
3. The average SINR perceived by the UEs.
4. The channel schedule per RBG, as seen by the eNB. White means free RBG. Blue means that the RBG was scheduled for use by the eNB. Red means the eNB detected the PU presence, based on the collaborative sensing fusion.

![sensing_result](/NS3/img/sensing_result.png)

## What to expect?
If you are not experienced with simulations, be aware of incredible results, as they may be wrong. 

## To-Do
1. Collect the number and duration of collisions with the PU

## Bonus: modified/included functions of the LTE stack for the collaborative sensing
![modified/included functions for sensing](/NS3/img/sensing_cyc.jpg)
