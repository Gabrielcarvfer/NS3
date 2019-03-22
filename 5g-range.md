---
layout: page
title: 5G-RANGE
permalink: /5G-RANGE/
---

The goal of the [5G-RANGE](http://5g-range.eu/) project is to design, develop, 
implement and validate the mechanisms to enable the 5G network to provide an 
economically effective solution for Internet access for remote areas.

In terms of simulations, our goal was to implement the channel model of the 5G-RANGE project, 
validate the results based on the field trials measurements, provide dynamic spectrum access capabilities
that enable opportunistic use of the spectrum underutilized by TV white spaces.


## How do you get it?
Following instructions in [COLAB-5G](https://gabrielcarvfer.github.io/NS3/COLAB_5G/).

An example of a setup using it is available [here](https://github.com/Gabrielcarvfer/NS3/blob/NS3.30.1-colab5g/scratch/5grange_cdl_test.cc).

## What have we done so far in terms of system-level simulations?

We used the [LTE/LENA](http://networks.cttc.es/mobile-networks/software-tools/lena/) model 
of the [ns-3](https://www.nsnam.org/) simulator as the basis for our project. 
The original code follows the 3GPP LTE specifications really closely, 
providing a solid foundation for mobile networks development.

[x] = complete
[ ] = pending

### List of changes associated with the channel model changes
- [x] Implement a simple propagation model for 5G-RANGE large scale path loss (named RANGE5G in the propagation module,
 following the path loss equation described in 
 [D3.1](http://5g-range.eu/wp-content/uploads/2018/04/D3.1-Physical-layer-of-the-5G-RANGE-Part-I.zip))
- [x] Implement the detailed propagation model with fast fading for large and small scale path loss (CDL D/LOS and CDL A/NLOS)

### List of changes associated with the physical layer
- [x] Implement spectrum sensing on the UEs (using probability of detection tables)
- [x] Implement hooks to notify the MAC layer of the detection
- [x] Widen channels to workaround the lack of cross-carrier aggregation
- [x] Implement a new error model for 5G-RANGE CDL D and A channels
- [x] - Implement numerology support and feed speed between nodes into the TBLER calculation
- [x] - Load and interpolate new BLER curves according to the channel type (CDL D/LOS or A/NLOS)
- [x] - Take into account CBs SINR to fetch the proper error rates and assemble the correct TBLER
- [x] Load and interpolate new MCS scheme and spectral efficiency curves

### List of changes associated with the MAC layer
- [x] Adapt the existing code to behave properly with new MCS values
- [x] Adapt the existing code to support higher granularity scheduling 
- [x] Implement a simple cognitive MAC protocol
- [x] Implement sensing messages and proper transmission time
- [x] Implement sensing messages reception on the eNB
- [x] Implement collaborative sensing algorithm to merge received information
- [x] Implement translation from the compiled sensing information into a mask of occupied RBs/channels
- [x] Implement changes to mark the free slots list as occupied based on the mask of occupied RBs
- [x] Implement changes to the resource schedulers to take into account the quality of aggregated carriers (be it cross-carrier or LAA)
- [x] Implement collaborative spectrum sensing and performance metrics collection

### List of changes associated with the network layer
- [x] Increase buffer sizes to improve 5G-RANGE performance

### List of changes associated with the application layer
- [x] Custom application to inject traffic with known distributions to analyze the impact of changes to lower layers
- [x] Custom traffic generator [EROS](https://github.com/notopoloko/Eros) 

## What is in progress?
[x] = testing
[ ] = actively working

- [x] Implementation of spatially correlated shadowing for the 5G-RANGE channel models
- [ ] Validation of channel model and physical layer implementations

## Remanining tasks
[x] = started
[ ] = not started
- [ ] Reproduce proof-of-concept field trial results
- [ ] Prepare realistic simulation scenarios
- [ ] Prepare stress-testing simulation scenarios
- [ ] Analytical model extrapolating the simulation results
- [ ] Split up the 5G-RANGE modified components from the LTE model and contribute back to the upstream project

## How about some results and nice pictures?
Working on it. We should have more to share by the end of October/2020.

## Acknowledgments
I want to thank every ns-3 developer, especially the CTTC people for the LTE/LENA model. 
It was essential for our project.

I'm also very grateful to all of our partners that enabled us to deliver an amazing simulation tool, 
that produces realistic results for our scenarios. 

I'm very optimistic that our work will end up in the wild, providing network connectivity for remote areas in Brazil,
Europe and others.

P.S.: This is not an official page for the project. 
Please look at the official [5G-RANGE](http://5g-range.eu/) page for more information.