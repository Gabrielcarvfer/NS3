---
layout: page
title: ns3-O-RL
permalink: /ns3_ORAN_RL/
---


# What is it?

The project is based on the [ns3-ORAN](/NS3/ns3_ORAN/) 

# How to cite?

TBD

# How to install? 

Start by cloning the [we need a better name for the branch](https://github.com/Gabrielcarvfer/ns3_oran/tree/teste-matias)
As in the installation instructions for the 
[Quick-Start section of the ns-3 documentation](https://www.nsnam.org/docs/release/3.40/tutorial/html/quick-start.html#prerequisites), 
before proceeding, you will need at least g++, ninja, cmake.


Install the dependencies
```
apt-get update && apt-get install -y \
    g++ \
    ninja-build \
    python3 \
    cmake \
    libarmadillo-dev \
    libmlpack-dev \
    pybind11-dev \
    python3-dev \
    ca-certificates \
    python3-pip \
    git \
```
Clone the Model repo and change to the `multiple_ue` branch

```

git clone https://github.com/MatheusOCruz/Handover_ORAN.git
cd Handover_ORAN
git switch multiple_ue
cd ../ns3_oran
pip install ../Handover_ORAN/HandoverRL

```



After downloading and installing these tools, 
configure ns-3 normally, then run the example

```

./ns3 configure --enable-examples -d release
./ns3 run "HandoverXappsScenario --scenario=5 --outputFile=0_outputRLRicInitiated.csv --useThreeGppChannel=1

```


# How to use?

The RL model uses the `HandoverXappsScenario.cc` provided in src/oran/example.

This example runs a simulation with different strategies of handover triggering (when to evaluate a handover decision)
and handover decision (to which cell the UE should be handed-over).

You can specify which simulation scenario you want to run:
- Scenario 0: 3GPP standard handover (triggering + decision)
- O-RAN handovers:
  - Scenario 0: standard 3GPP handover 
  - Scenario 1: standard 3GPP triggering + RIC bypass (forwarding the eNB decision back to itself)
  - Scenario 4: standard 3GPP triggering + RIC xApp using the RL for handover decision
  - Scenario 5: RIC xApp using the RL model for handover triggering and decision

In scenario 5, the handover xApp periodically checks for the 
reported KPMs and decide by itself when to trigger a handover from one 
cell to another. When that happens, the control request is sent by the RIC 
to the source cell, for it to initiate the handover process. For that to 
work, we need to disable the handover triggering algorithm in the eNB,
making it completely clueless regarding the handover necessity.

`--useThreeGppChannel=1` enables the 3GPP channel, instead of the
default Friis channel used by LTE.
This channel is more realistic, accounting for different ray clusters,
fading and shadowing effects additionally to pathloss.
These effects make handover triggering and target cell selection
a lot more challenging, especially due to large short-term fluctuations,
that induce ping-pongs using traditional techniques.

These cases are shown in the following sequence diagram.

[![](https://mermaid.ink/img/pako:eNqtkkFP8zAMhv-KlfM4sGMFk_ptlagEHXQdp0oo
pF4b0cbFSfmYEP-dJNVAAokTySFObb9-3PhNKGpQJMLi84RG4UbLluVQG_CrJxphNsN6TcfxbLU
KRwK3yJoarWTfH0F1qJ7gQHzxyCvopGnoBRloHIndZLTTaH_olPk6gYp12yJbuDol_deuAwmKjG
PqgQOYdaBNKOY0GRjQWtkihGLZMr0FrwR5scnXaZVvi_A5ZEtttGnBdfgpki13N2flOkSURZVf7
rOHcIb7VVpstvdZCettUZXbayizu322q76wfRVPjcW_8wRSpXB0Nor_Qvp4BIv-6jFkxP7J_a3c
38DHGC--QaWtB7mceb96CV3MzSwT2DnJLpb6fLmRSWEzMcYHpUP07rOIHh_oOwEcmIYYFaTB0cl
ezkX9X6jNvMVCDMiD1I2fu7fgroUPHrAWiTd73XauFovZMWhm4lQ5Yhv8B9lbrM27F5GTo93RKJ
E4nnAhprGR7jTAIomRC4GN9rk385THYX__AGMR-Jo?type=png)](https://mermaid.live/e
dit#pako:eNqtkkFP8zAMhv-KlfM4sGMFk_ptlagEHXQdp0oopF4b0cbFSfmYEP-dJNVAAokTyS
FObb9-3PhNKGpQJMLi84RG4UbLluVQG_CrJxphNsN6TcfxbLUKRwK3yJoarWTfH0F1qJ7gQHzxy
CvopGnoBRloHIndZLTTaH_olPk6gYp12yJbuDol_deuAwmKjGPqgQOYdaBNKOY0GRjQWtkihGLZ
Mr0FrwR5scnXaZVvi_A5ZEtttGnBdfgpki13N2flOkSURZVf7rOHcIb7VVpstvdZCettUZXbayi
zu322q76wfRVPjcW_8wRSpXB0Nor_Qvp4BIv-6jFkxP7J_a3c38DHGC--QaWtB7mceb96CV3MzS
wT2DnJLpb6fLmRSWEzMcYHpUP07rOIHh_oOwEcmIYYFaTB0clezkX9X6jNvMVCDMiD1I2fu7fgr
oUPHrAWiTd73XauFovZMWhm4lQ5Yhv8B9lbrM27F5GTo93RKJE4nnAhprGR7jTAIomRC4GN9rk3
85THYX__AGMR-Jo)

## Dockerfile

An easier way to run the model without worring about dependencies, is using
the docker-compose in the repo, simply run `docker compose up --build`, 
and `docker compose up` om subsequent runs

## How it works?

PyTorch model is loaded by C++ via Pybind11, starts a new process that runs
the model and has its own memory keeping track of previous decisions, rewards, etc.

## What is the current model?

- Inputs: the RSRP metric of the 2 gNBs available, the ID of the connected gnb and the RNTI of the UE
- Neural network: The network is a Deep Recurrent Q-Network, meaning we have a LSTM layer that leads to a 
deep Q-learning network
- Outputs: boolean representing the decision to do the handover
- Reward: The reward is based on the the difference of RSRP on the connected gNB and the other available, in case of 
handover, the reward is based on the cumulative gain of RSRP over the last time steps 


## I’ve run the example, now what?


We can aggregate these results from a bunch of different simulations using 
the same strategies, and get some statistical confidence and margins of 
errors.

After that, we can consolidate all of these results using different scripts to 
show different aspects of the data.

First, we have a single spreadsheet comparing the handover performance 
in the different scenarios.


![resultados comparados]()


The auxiliary script `.py`, can plot the collected KPMs by the near-RT RIC,
We can also generate two plots, one showing the RSRP and RSRQ metrics 
over time, and another one showing the throughput obtained by the UE 
in the simulation.

![metric]()
![throughput]()
