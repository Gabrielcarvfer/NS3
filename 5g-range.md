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

![](/NS3/img/5g-range/scenario.jpg)

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
- [x] Implementation of spatially correlated shadowing for the 5G-RANGE channel models
- [x] Validation of the channel model implementation

### List of changes associated with the physical layer
- [x] Implement spectrum sensing on the UEs (using probability of detection tables)
- [x] Implement hooks to notify the MAC layer of the detection
- [x] Widen channels to workaround the lack of cross-carrier aggregation
- [x] Implement a new error model for 5G-RANGE CDL D and A channels
- [x] - Implement numerology support and feed speed between nodes into the TBLER calculation
- [x] - Load and interpolate new BLER curves according to the channel type (CDL D/LOS or A/NLOS)
- [x] - Take into account CBs SINR to fetch the proper error rates and assemble the correct TBLER
- [x] Load and interpolate new MCS scheme and spectral efficiency curves
- [x] Validation of the physical layer implementation

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

## How about some results and nice pictures?
Sure. Here are some of them.

### Field trial measurements

The field trial was executed by the Inatel and the Federal University of Ceará (UFC) teams, and findings were published in 
[5G-RANGE Project Field Trial](https://ieeexplore.ieee.org/document/8802021)

![](/NS3/img/5g-range/area-medidas.png)

The following images are from the field trial paper mentioned above.

![](/NS3/img/5g-range/medidas.png)

![](/NS3/img/5g-range/medidas_2.png)


### Channel validation

There were two channel models proposed based on CDL D and A, for LOS and NLOS scenarios, respectively.

The models were proposed by the UFC team and published 
in [CDL-based Channel Model for 5G MIMO Systems in Remote Rural Areas](https://ieeexplore.ieee.org/document/8877334).

Our implementation (5G-RANGE in the figures below) matches the expected results for both CDL D and CDL A.

![](/NS3/img/5g-range/cdl-d-validation.png)

![](/NS3/img/5g-range/cdl-a-validation.png)

### PHY and MAC validation

The PHY and MAC were validated comparing to the proof-of-concept measurements made in the field trials.

The simulated performance matched the real-life results from the trials.

![](/NS3/img/5g-range/5g-rcolab-validation-part1.png)

The results for TBLER on the other hand, were a lot higher on the field trial measurements for NLOS at 40km.

![](/NS3/img/5g-range/5g-rcolab-validation-part2.png)


### Dynamic Spectrum Access with Collaborative Spectrum Sensing

This is my main contribution, and it was done in collaboration from our friends from the University of Oulu.

How can we detect a primary user (channel licensee)? There are many ways, but the one that doesn't have to rely on
a central entity giving out temporary licenses is basically some form of spectrum sensing.

Since a single point sensing the spectrum in a 50km-wide cell isn't very effective since the sensing
element can be far enough of the licensee to perceive it is transmitting. If both transmit simultaneously,
we cause interference, which is not desirable nor allowed. 

Using collaborative spectrum sensing (CSS) is a lot more logical in this case.
CSS allow multiple sensing elements to perform their sensing independently
and merge/fuse their sensing results later.

![](/NS3/img/5g-range/spectrum-sensing.png)

In our case, the individual sensing technique used is based on the technique proposed on 
[Spectrum window based signal detection at low SNR](https://ieeexplore.ieee.org/document/8398726),
known as WIBA.

The sensing results are then fused according to a fusion scheme/policy on the LTE's eNodeB
(which is very logical, since we are using a centralized network as the base for 5G-RANGE).

We have shown in [MHM: A Novel Collaborative Spectrum Sensing Method based on Markov-chains and Harmonic Mean for 5G Networks](https://ieeexplore.ieee.org/document/9142763),
a particular combination of techniques to have an effective fusion scheme.

We used the BLER as a source of trust of the reported CQI by the UEs.

The trusted CQI can then be correlated with the sensing data: when a primary user starts transmitting, 
it is expected that nearby UEs have a drop in CQI. We can filter the others out by filtering by the
harmonic mean of reported CQIs.

Building that trust makes us less exposed to Byzantine attackers (either malicious sensing reports or faulty ones).

We also employed a Markov Chain to make the individual sensing reports (sent on channel condition change) 
more stable temporally, saving up some control channel bandwidth at the cost of detection range.

![](/NS3/img/5g-range/MHM_topology_random_attackers_05_fusion_12.png)

The images below show how false positives (a.k.a. unused spectrum), 
false negatives (a.k.a. interference with the primary user PU)
and reported frames per UE (a.k.a. control channel overhead) 
scale with the number of UEs during different simulations.

#### With 20 UEs
![](/NS3/img/5g-range/sensing_per_scenario_ues_20_simulationCase_11.png)

#### With 50 UEs
![](/NS3/img/5g-range/sensing_per_scenario_ues_50_simulationCase_11.png)

#### With 100 UEs
![](/NS3/img/5g-range/sensing_per_scenario_ues_100_simulationCase_11.png)

Of course, we simulated all of these in both scenarios with randomly dispersed UEs (less realistic)
and scenarios with randomly dispersed clusters of UEs (e.g. rural businesses, small city, rural school, etc).

#### Randomly dispersed UEs
![](/NS3/img/5g-range/mac-ver-sce1.png)

#### Randomly dispersed clusters of UEs
![](/NS3/img/5g-range/mac-ver-sce2.png)

## Acknowledgments
I want to thank every ns-3 developer, especially the CTTC people for the LTE/LENA model. 
It was essential for our project.

I'm also very grateful to all of our partners that enabled us to deliver an amazing simulation tool, 
that produces realistic results for our scenarios. 

I'm very optimistic that our work will end up in the wild, providing network connectivity for remote areas in Brazil,
Europe and others.

P.S.: This is not an official page for the project. 
Please look at the official [5G-RANGE](http://5g-range.eu/) page for more information.