import itertools
from csv import DictReader
import re
import shutil
import statistics
import subprocess
import sys
import os
import numpy as np
import scipy.stats as st

curr_dir = os.path.dirname(os.path.abspath(__file__))
ns3_path = curr_dir
while "ns3" not in os.listdir(ns3_path):
    ns3_path = os.path.dirname(ns3_path)
ns3_script = os.path.join(ns3_path, "ns3")

def run_ns3(args, env=None, generator="Ninja"):
    """!
    Runs the ns3 wrapper script with arguments
    @param args: string containing arguments that will get split before calling ns3
    @param env: environment variables dictionary
    @param generator: CMake generator
    @return tuple containing (error code, stdout and stderr)
    """
    if "clean" in args:
        possible_leftovers = ["contrib/borked", "contrib/calibre"]
        for leftover in possible_leftovers:
            if os.path.exists(leftover):
                shutil.rmtree(leftover, ignore_errors=True)
    if " -G " in args:
        args = args.format(generator=generator)
    return run_program(ns3_script, args, python=True, env=env)


# Adapted from https://github.com/metabrainz/picard/blob/master/picard/util/__init__.py
def run_program(program, args, python=False, cwd=ns3_path, env=None):
    """!
    Runs a program with the given arguments and returns a tuple containing (error code, stdout and stderr)
    @param program: program to execute (or python script)
    @param args: string containing arguments that will get split before calling the program
    @param python: flag indicating whether the program is a python script
    @param cwd: the working directory used that will be the root folder for the execution
    @param env: environment variables dictionary
    @return tuple containing (error code, stdout and stderr)
    """
    if type(args) != str:
        raise Exception("args should be a string")

    # Include python interpreter if running a python script
    if python:
        arguments = [sys.executable, program]
    else:
        arguments = [program]

    if args != "":
        arguments.extend(re.findall("(?:\".*?\"|\S)+", args))  # noqa

    for i in range(len(arguments)):
        arguments[i] = arguments[i].replace("\"", "")

    # Forward environment variables used by the ns3 script
    current_env = os.environ.copy()

    # Add different environment variables
    if env:
        current_env.update(env)

    # Call program with arguments
    ret = subprocess.run(
        arguments,
        stdin=subprocess.DEVNULL,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        cwd=cwd,  # run process from the ns-3-dev path
        env=current_env
    )
    # Return (error code, stdout and stderr)
    return ret.returncode, ret.stdout.decode(sys.stdout.encoding), ret.stderr.decode(sys.stderr.encoding)


output_and_args = {
    "output3GPPHandover.csv": "--scenario=0",
    "outputDistributedHandover.csv": "--scenario=1",
    "outputKMeansHandover.csv": "--scenario=2",
    "outputKMeansHandoverRicInitiated.csv": "--scenario=3",
    "outputMaxRsRp.csv": "--scenario=4",
    "outputMaxRsRpRicInitiated.csv": "--scenario=5"
}

output_and_type = {
    "output3GPPHandover.csv": "Iniciado por eNB",
    "outputDistributedHandover.csv": "Iniciado por eNB e confirmado por O-RAN",
    "outputKMeansHandover.csv": "Iniciado por eNB e confirmado por O-RAN+xApp K-Means",
    "outputKMeansHandoverRicInitiated.csv": "Iniciado por O-RAN+xApp K-Means",
    "outputMaxRsRp.csv": "Iniciado por eNB e confirmado por O-RAN+xApp MaxRsrp",
    "outputMaxRsRpRicInitiated.csv": "Iniciado por O-RAN+xApp MaxRsrp",
}

resultingCsv = {}
consolidatedResults = [["", "Handovers", "", "", "", "", "", "", "", "Conexão"],
                       ["",
                        "Disparados",
                        "Cancelados pelo RIC",
                        "Latência para início do handover (ns)",
                        "Iniciados",
                        "Bem sucedidos",
                        "Mal sucedidos",
                        "Duração do handover (ns)",
                        "Média de handovers por UE",
                        "Conexões estabelecidas",
                        "Conexões Reestabelecidas"]
                       ]

def run_simulation(arguments, outputFile):
    if not os.path.exists(os.path.join(curr_dir, outputFile)):
        return_code, stdout, stderr = run_ns3(f"run HandoverXappsScenario -- {arguments} --outputFile={outputFile}")
        if return_code != 0:
            exit(return_code)
        shutil.move(os.path.join(ns3_path, outputFile),
                    os.path.join(curr_dir, outputFile))
        #shutil.move(os.path.join(ns3_path, "anim.xml"),
        #            os.path.join(curr_dir, outputFile.replace("output", "anim").replace(".csv", ".xml")) )

from concurrent.futures import ThreadPoolExecutor

for outputFile in output_and_args.keys():
    # Run simulations
    num_runs = 20
    with ThreadPoolExecutor(max_workers=os.cpu_count()-1) as pool:
        res = pool.map(run_simulation,
                       [output_and_args[outputFile]]*num_runs,
                       [f"{run}_{outputFile}" for run in range(num_runs)]
                       )
        for resp in res:
            pass
    del pool, res, resp

    # Create containers to collect run results
    handoversLatency = []
    cancelledHandoversLatency = []
    handoversTriggeredList = []
    handoversInitiatedList = []
    handoversOKList = []
    handoversErrorList = []
    handoversCancelledList = []
    connectionEstablishedList = []
    connectionReconfigurationList = []
    meanHandoversList = []

    # Process each run
    for run in range(num_runs):
        with open(os.path.join(curr_dir, f"{run}_{outputFile}"), "r") as f:
            resultingCsv = DictReader(f.readlines())
        del f

        handoversTriggered = 0
        handoversInitiated = 0
        handoversOK = 0
        handoversError = 0
        handoversCancelled = 0
        handoversPerUE = {}
        handoversTriggeredPerUE = {}
        connectionEstablished = 0
        connectionEstablishedPerUE = {}
        connectionReconfiguration = 0
        connectionReconfigurationPerUE = {}

        for line in resultingCsv:
            imsi = line["IMSI"]
            if imsi not in handoversPerUE:
                handoversPerUE[imsi] = [[], []]  # start, ok/fail
                handoversTriggeredPerUE[imsi] = [[], []]  # trigger, cancelled/startenb
            if imsi not in connectionEstablishedPerUE:
                connectionEstablishedPerUE[imsi] = []
            if imsi not in connectionReconfigurationPerUE:
                connectionReconfigurationPerUE[imsi] = []
            if line["Type"] == "HANDOVER_TRIGGERED_ENB":
                handoversTriggered += 1
                handoversTriggeredPerUE[imsi][0].append(line)
                continue
            if line["Type"] == "HANDOVER_CANCELLED_RIC":
                handoversCancelled += 1
                handoversTriggeredPerUE[imsi][1].append(line)
                continue
            if line["Type"] == "HANDOVER_START_ENB":
                handoversInitiated += 1
                handoversPerUE[imsi][0].append(line)
                handoversTriggeredPerUE[imsi][1].append(line)
                continue
            if line["Type"] == "HANDOVER_OK_ENB":
                continue
            if line["Type"] == "HANDOVER_START_UE":
                #handoversInitiated += 1
                #handoversPerUE[imsi][0].append(line)
                continue
            if line["Type"] == "HANDOVER_OK_UE":
                handoversOK += 1
                handoversPerUE[imsi][1].append(line)
                continue
            if line["Type"] == "HANDOVER_ERROR_UE":
                handoversError += 1
                handoversPerUE[imsi][1].append(line)
                continue
            if line["Type"] == "CONNECTION_RECONFIGURATION_ENB":
                connectionReconfiguration += 1
                connectionReconfigurationPerUE[imsi].append(line)
                continue
            if line["Type"] == "CONNECTION_ESTABLISHED_ENB":
                connectionEstablished += 1
                connectionEstablishedPerUE[imsi].append(line)
                continue
            if line["Type"] == "CONNECTION_ERROR_ENB":
                continue
            if line["Type"] == "CONNECTION_START_UE":
                continue
            if line["Type"] == "CONNECTION_ESTABLISHED_UE":
                continue
            if line["Type"] == "CONNECTION_ERROR_UE":
                continue

        del line, imsi, resultingCsv

        def zip_to_nearest(list1, list2):
            zipped_list = []
            for list1_item in list1:
                filtered = list(filter(lambda x: int(x["Time (ns)"])-int(list1_item["Time (ns)"]) >= 0, list2))
                if filtered:
                    zipped_list.append((list1_item, filtered[0]))
            return zipped_list
        for imsi in handoversPerUE:
            for (handoverStart, handoverEnd) in zip_to_nearest(*handoversPerUE[imsi]):
                if handoverEnd["Type"] != "HANDOVER_CANCELLED_RIC":
                    handoversLatency.append(int(handoverEnd["Time (ns)"]) - int(handoverStart["Time (ns)"]))
            for (handoverStart, handoverEnd) in zip_to_nearest(*handoversTriggeredPerUE[imsi]):
                    cancelledHandoversLatency.append(int(handoverEnd["Time (ns)"]) - int(handoverStart["Time (ns)"]))
        del imsi, handoverStart, handoverEnd
        if len(cancelledHandoversLatency) == 0:
            cancelledHandoversLatency.extend([0, 0])
        meanHandovers = handoversInitiated / len(handoversPerUE.keys())

        handoversTriggeredList.append(handoversTriggered)
        handoversInitiatedList.append(handoversInitiated)
        handoversOKList.append(handoversOK)
        handoversErrorList.append(handoversError)
        handoversCancelledList.append(handoversCancelled)
        connectionEstablishedList.append(connectionEstablished)
        connectionReconfigurationList.append(connectionReconfiguration)
        meanHandoversList.append(meanHandovers)
        del handoversTriggered, handoversInitiated, handoversOK, handoversError, handoversCancelled, meanHandovers
        del connectionEstablished, connectionReconfiguration, run
    def calcMeanPlusMargin(data):
        lower_bound, upper_bound = st.t.interval(alpha=0.95, df=len(data)-1, loc=np.mean(data), scale=st.sem(data, nan_policy='omit'))
        mean = np.mean(data)
        margin = (upper_bound-lower_bound)/2
        if np.isnan(margin):
            margin = 0
        return f"{mean:.0f}+-{margin:.0f}"

    consolidatedResults.append([output_and_type[outputFile],
                                calcMeanPlusMargin(handoversTriggeredList),
                                calcMeanPlusMargin(handoversCancelledList),
                                calcMeanPlusMargin(cancelledHandoversLatency),
                                calcMeanPlusMargin(handoversInitiatedList),
                                calcMeanPlusMargin(handoversOKList),
                                calcMeanPlusMargin(handoversErrorList),
                                calcMeanPlusMargin(handoversLatency),
                                calcMeanPlusMargin(meanHandoversList),
                                calcMeanPlusMargin(connectionEstablishedList),
                                calcMeanPlusMargin(connectionReconfigurationList)
                                ])
    pass

with open(os.path.join(curr_dir, "consolidated.csv"), "w") as f:
    for line in consolidatedResults:
        f.write(",".join(line)+"\n")

pass
