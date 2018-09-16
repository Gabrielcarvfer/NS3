#! /usr/bin/env python
## -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

# A list of C++ examples to run in order to ensure that they remain
# buildable and runnable over time.  Each tuple in the list contains
#
#     (example_name, do_run, do_valgrind_run).
#
# See test.py for more information.
cpp_examples = [
    ("mixed-wired-wireless", "True", "True"),
    ("multirate --totalTime=0.3s --rateManager=ns3::AarfcdWifiManager", "True", "True"), 
    ("multirate --totalTime=0.3s --rateManager=ns3::AmrrWifiManager", "True", "False"), 
    ("multirate --totalTime=0.3s --rateManager=ns3::CaraWifiManager", "True", "False"), 
    ("multirate --totalTime=0.3s --rateManager=ns3::IdealWifiManager", "True", "False"), 
    ("multirate --totalTime=0.3s --rateManager=ns3::MinstrelWifiManager", "True", "False"), 
    ("multirate --totalTime=0.3s --rateManager=ns3::OnoeWifiManager", "True", "False"), 
    ("multirate --totalTime=0.3s --rateManager=ns3::RraaWifiManager", "True", "False"), 
    ("wifi-adhoc", "False", "True"), # Takes too long to run
    ("wifi-ap --verbose=0", "True", "True"), # Don't let it spew to stdout
    ("wifi-clear-channel-cmu", "False", "True"), # Requires specific hardware
    ("wifi-simple-adhoc", "True", "True"),
    ("wifi-simple-adhoc-grid", "True", "True"),
    ("wifi-simple-infra", "True", "True"),
    ("wifi-simple-interference", "True", "True"),
    ("wifi-wired-bridging", "True", "True"),
    ("wifi-sleep", "True", "True"),
    ("wifi-blockack", "True", "True"),
    ("wifi-timing-attributes --simulationTime=1", "True", "True"),
    ("power-adaptation-distance --manager=ns3::ParfWifiManager --outputFileName=parf --steps=5 --stepsSize=10", "True", "True"),
    ("power-adaptation-distance --manager=ns3::AparfWifiManager --outputFileName=aparf --steps=5 --stepsSize=10", "True", "False"),
    ("power-adaptation-distance --manager=ns3::RrpaaWifiManager --outputFileName=rrpaa --steps=5 --stepsSize=10", "True", "False"),
    ("power-adaptation-interference --simuTime=5", "True", "False"),
    ("dsss-validation", "True", "True"),
    ("ofdm-validation", "True", "True"),
    ("ofdm-ht-validation", "True", "True"),
    ("ofdm-vht-validation", "True", "True"),
    ("ofdm-he-validation", "True", "True"),
    ("80211n-mimo --simulationTime=0.1 --step=10", "True", "True"),
    ("ht-wifi-network --simulationTime=0.1 --frequency=5 --useRts=0 --minExpectedThroughput=5 --maxExpectedThroughput=134", "True", "True"),
    ("ht-wifi-network --simulationTime=0.1 --frequency=5 --useRts=1 --minExpectedThroughput=5 --maxExpectedThroughput=130", "True", "True"),
    ("ht-wifi-network --simulationTime=0.1 --frequency=2.4 --useRts=0 --minExpectedThroughput=5 --maxExpectedThroughput=132", "True", "True"),
    ("ht-wifi-network --simulationTime=0.1 --frequency=2.4 --useRts=1 --minExpectedThroughput=4.5 --maxExpectedThroughput=128", "True", "True"),
    ("vht-wifi-network --simulationTime=0.1 --useRts=0  --minExpectedThroughput=5 --maxExpectedThroughput=555", "True", "True"),
    ("vht-wifi-network --simulationTime=0.2 --useRts=1", "True", "True"),
    ("he-wifi-network --simulationTime=0.25 --frequency=5 --useRts=0  --minExpectedThroughput=6 --maxExpectedThroughput=754", "True", "True"),
    ("he-wifi-network --simulationTime=0.3 --frequency=5 --useRts=1 --minExpectedThroughput=6 --maxExpectedThroughput=639", "True", "True"),
    ("he-wifi-network --simulationTime=0.25 --frequency=2.4 --useRts=0 --minExpectedThroughput=6 --maxExpectedThroughput=238", "True", "True"),
    ("he-wifi-network --simulationTime=0.3 --frequency=2.4 --useRts=1 --minExpectedThroughput=6 --maxExpectedThroughput=224", "True", "True"),
    ("simple-ht-hidden-stations --simulationTime=1 --enableRts=0 --nMpdus=32 --minExpectedThroughput=59 --maxExpectedThroughput=60", "True", "True"),
    ("simple-ht-hidden-stations --simulationTime=1 --enableRts=1 --nMpdus=32 --minExpectedThroughput=57 --maxExpectedThroughput=58", "True", "True"),
    ("mixed-network --simulationTime=1", "True", "True"),
    ("wifi-aggregation --simulationTime=1 --verifyResults=1", "True", "True"),
    ("80211e-txop --simulationTime=1 --verifyResults=1", "True", "True"),
    ("wifi-multi-tos --simulationTime=1 --nWifi=16 --useRts=1 --useShortGuardInterval=1", "True", "True"),
    ("wifi-tcp", "True", "True"),
    ("wifi-pcf --simulationTime=1 --withData=0", "True", "True"),
    ("wifi-pcf --simulationTime=1 --withData=1 --trafficDirection=upstream", "True", "True"),
    ("wifi-pcf --simulationTime=1 --withData=1 --trafficDirection=downstream", "True", "True"),
    ("wifi-hidden-terminal --wifiManager=Arf", "True", "True"),
    ("wifi-hidden-terminal --wifiManager=Aarf", "True", "True"),
    ("wifi-hidden-terminal --wifiManager=Aarfcd", "True", "True"),
    ("wifi-hidden-terminal --wifiManager=Onoe", "True", "True"),
    ("wifi-hidden-terminal --wifiManager=Amrr", "True", "True"),
    ("wifi-hidden-terminal --wifiManager=Minstrel", "True", "True"),
    ("wifi-hidden-terminal --wifiManager=Cara", "True", "True"),
    ("wifi-hidden-terminal --wifiManager=Rraa", "True", "True"),
    ("wifi-hidden-terminal --wifiManager=Rrpaa", "True", "True"),
    ("wifi-spectrum-per-example --distance=52 --index=3 --wifiType=ns3::SpectrumWifiPhy --simulationTime=1", "True", "True"),
    ("wifi-spectrum-per-example --distance=24 --index=31 --wifiType=ns3::YansWifiPhy --simulationTime=1", "True", "False"),
    ("wifi-spectrum-per-interference --distance=24 --index=31 --simulationTime=1 --waveformPower=0.1", "True", "True"),
    ("wifi-spectrum-saturation-example --simulationTime=1 --index=63", "True", "True"),
    ("wifi-backward-compatibility --apVersion=80211a --staVersion=80211n_5GHZ --simulationTime=1", "True", "True"),
    ("wifi-backward-compatibility --apVersion=80211a --staVersion=80211n_5GHZ --apRaa=Ideal --staRaa=Ideal --simulationTime=1", "True", "False"),
    ("wifi-backward-compatibility --apVersion=80211a --staVersion=80211ac --simulationTime=1", "True", "False"),
    ("wifi-backward-compatibility --apVersion=80211a --staVersion=80211ac --apRaa=Ideal --staRaa=Ideal --simulationTime=1", "True", "False"),
]

# A list of Python examples to run in order to ensure that they remain
# runnable over time.  Each tuple in the list contains
#
#     (example_name, do_run).
#
# See test.py for more information.
python_examples = [
    ("wifi-ap.py", "True"),
    ("mixed-wired-wireless.py", "True"),
]
