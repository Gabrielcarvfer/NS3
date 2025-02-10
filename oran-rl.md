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

Start by cloning the [NS3's branch NS3.40-ns3-o-rl](https://github.com/Gabrielcarvfer/NS3/tree/NS3.40-ns3-o-rl) branch.
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
    git
git clone -b NS3.40-ns3-o-rl https://github.com/Gabrielcarvfer/NS3
cd NS3
```

Then, fetch the RL model and install it from the repo
[Handover_ORAN's multiple_ue branch](https://github.com/MatheusOCruz/Handover_ORAN/tree/multiple_ue)

```
git clone -b multiple_ue https://github.com/MatheusOCruz/Handover_ORAN.git
cd Handover_ORAN
pip install ./Handover_ORAN/HandoverRL
```

After downloading and installing these tools, 
configure ns-3 normally, then run the example

```
./ns3 configure --enable-examples -d release
./ns3 run "HandoverXappsScenario --scenario=5 --outputFile=0_outputRLRicInitiated.csv --useThreeGppChannel=1
```

# Trying the model itself

The repo with the model comes with synthetic data scenarios the enable initial training and
ploting the results obtained, the explanation can be found in the README.md of the
[repo](https://github.com/MatheusOCruz/Handover_ORAN/tree/multiple_ue).

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

The simulation program supports 3 different topologies and movement patterns, as shown in
the figure below

![](/NS3/img/ns3-o-rl/patterns.png)

To select them, use choose one of the available strides:
`ns3 run 'HandoverXappsScenario --stride=(triangle|opposite_senoids|offset_senoids)'`

Use `ns3 run 'HandoverXappsScenario --useThreeGppChannel=1` to 
enables the 3GPP channel, instead of the default Friis channel used by LTE.
This channel is more realistic, accounting for different ray clusters,
fading and shadowing effects additionally to pathloss.
These effects make handover triggering and target cell selection
a lot more challenging, especially due to large short-term fluctuations,
that induce ping-pongs using traditional techniques.

An easier way to run the model without worring about dependencies, is using
the docker-compose in the repo, simply run `docker compose up --build`, 
and `docker compose up` om subsequent runs

## How it works?

PyTorch model is loaded by C++ via Pybind11, starts a new process that runs
the model and has its own memory keeping track of previous decisions, rewards, etc.

The ns3-O-RL integrates into ns3-ORAN as follows:

[![](https://mermaid.ink/img/pako:eNqVVV9vmzAQ_yonXps8tHtDUyRK2BapJRlN91DlxbUvwRrY7GyiRFW_-2wIDYRM6nhJ7ON-f-7s4y3gWmAQBgb_1Kg4ziXbESs3Ctzzqg_wIHe5_U6ICr4hszWhAVlWBZaoLAqQCmwuDTCykhfYJlbNSlZMWThEVTXeXR3vpRK3t9ciNtcqKx6dsKINoxIXgu6LGiE5SGOl2sH2Q5gCZb5Ml1mUjoGzRTzexPT-9oKk0LqCFZLUQnLgOfLfsNUEOVNC75FAV5UmWytpJZo2p3sYt3LPLPZcd08DG3s0L9nmCApd_YbIW2DwnAwTPdR0NusqFkKiXNNOIF9faeYypoQF8-3QrwbJKZBaNSGprHaYaV1WR7CojKZPK-4YG_JeU0KIdXXsXPShG8ot6bKJxDc37peQCbC6CfndFuoUGBIO9Fw5B0NxvfBY4UJtkfyBBldbsMSkcoI_A9NVue9RIJfGlRT2yO2lzYGh1qa-8D_mFfgZo70O-PaEMMeL1rfVb2V5Xsc5hOgRjTt8OlotdnJAXtuR5ZIJPGexoruhUHq9zXvCHTybM3s-yG4gKORoDKPjVUp3GUNYk9ztkMw5by8ZJHfRyl9WWKTzRRytF8sUuFa2bWHjOrl7epxmMfyI0vnyV5JBvEzX2fIBsuTnc_K0_o8SOCInx4-BECLOsbKmYSNdAPmhaKxXdaI9Kfsn3ccQub4IJkGJVDIp3Mh988FN4Ipd4iYI3d_Cj7ZNMGkDpSTSFPnOGh_fssK4Trw7EFZb_XRUPAgt1TgJSNe7PAibNyZBXQnn9TTJP3bduHvR-rxGIR3yYzv-m6_A-1_7ZOtq?type=png)](https://mermaid.ink/img/pako:eNqVVV9vmzAQ_yonXps8tHtDUyRK2BapJRlN91DlxbUvwRrY7GyiRFW_-2wIDYRM6nhJ7ON-f-7s4y3gWmAQBgb_1Kg4ziXbESs3Ctzzqg_wIHe5_U6ICr4hszWhAVlWBZaoLAqQCmwuDTCykhfYJlbNSlZMWThEVTXeXR3vpRK3t9ciNtcqKx6dsKINoxIXgu6LGiE5SGOl2sH2Q5gCZb5Ml1mUjoGzRTzexPT-9oKk0LqCFZLUQnLgOfLfsNUEOVNC75FAV5UmWytpJZo2p3sYt3LPLPZcd08DG3s0L9nmCApd_YbIW2DwnAwTPdR0NusqFkKiXNNOIF9faeYypoQF8-3QrwbJKZBaNSGprHaYaV1WR7CojKZPK-4YG_JeU0KIdXXsXPShG8ot6bKJxDc37peQCbC6CfndFuoUGBIO9Fw5B0NxvfBY4UJtkfyBBldbsMSkcoI_A9NVue9RIJfGlRT2yO2lzYGh1qa-8D_mFfgZo70O-PaEMMeL1rfVb2V5Xsc5hOgRjTt8OlotdnJAXtuR5ZIJPGexoruhUHq9zXvCHTybM3s-yG4gKORoDKPjVUp3GUNYk9ztkMw5by8ZJHfRyl9WWKTzRRytF8sUuFa2bWHjOrl7epxmMfyI0vnyV5JBvEzX2fIBsuTnc_K0_o8SOCInx4-BECLOsbKmYSNdAPmhaKxXdaI9Kfsn3ccQub4IJkGJVDIp3Mh988FN4Ipd4iYI3d_Cj7ZNMGkDpSTSFPnOGh_fssK4Trw7EFZb_XRUPAgt1TgJSNe7PAibNyZBXQnn9TTJP3bduHvR-rxGIR3yYzv-m6_A-1_7ZOtq?type=png)


## What is the current model?

- Inputs: the RSRP metric of the 2 gNBs available, the ID of the connected gnb and the RNTI of the UE
- Neural network: The network is a Deep Recurrent Q-Network, meaning we have a LSTM layer that leads to a 
deep Q-learning network
- Outputs: boolean representing the decision to do the handover
- Reward: The reward is based on the the difference of RSRP on the connected gNB and the other available, in case of 
handover, the reward is based on the cumulative gain of RSRP over the last time steps

![model](/NS3/img/ns3-o-rl/model.png)

## I’ve run the example, now what?

We collect KPMs reported over time into a JSON file `kpms.json`,
which can be plotted with the help of the `src/oran/PlotKpmsJson.py` script,
which will produce something like the following figures, where we can observe
the RNTI and E2Node of a single UE changing over time as it is handed over or
reconnects to the other cell.

- Using the bypass xApp (`--scenario=1`)

![](/NS3/img/ns3-o-rl/by3a.jpg)

- Using the RL xApp (`--scenario=5`)

![](/NS3/img/ns3-o-rl/rl3a.png)
 
Another auxiliary script, `src/oran/examples/PlotUeThrLogJson.py` plots the
average UE throughput logged into `ueThrLog.json` over a sliding window, to
help visualize the side-effects of the handover and disconnections into the
application, like shown below.

![](/NS3/img/ns3-o-rl/ueThrLog.png)


Note: these scripts assume the resulting json files will be along the built
binary `HandoverXappsScenario` located in the `build/src/oran/examples`.
They need to be manually edited to point to files in different locations.

To plot these for the different strides, use `PlotAllScenarios.sh`.

We can also aggregate these results from a bunch of different simulations using
the same strategies, and get some statistical confidence and margins of
errors. After that, we can consolidate all of these results using different
scripts to show different aspects of the data. This is all done by the 
`src/oran/examples/HandoverXappsScenarioCompanion.py` script. You should get a
`consolidated.csv` file for simulation campaign (using different xApps for a 
same setting combination). To run for all different strides, call 
`src/oran/examples/CompanionCompanion.sh`.

For the triangle stride, we get the following:

![](/NS3/img/ns3-o-rl/results.png)
