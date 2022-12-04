from csv import DictReader
import re
import shutil
import statistics
import subprocess
import sys
import os

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
    "output3GPPHandover.csv": "--oranSetup=false",
    "outputDistributedHandover.csv": "--distributedHandover",
    "outputKMeansHandover.csv": "",
    }

output_and_type = {
    "output3GPPHandover.csv": "Distribuído",
    "outputDistributedHandover.csv": "Distribuído com O-RAN",
    "outputKMeansHandover.csv": "Centralizado com O-RAN+xApp K-Means",
}

resultingCsv = {}
consolidatedResults = [["", "Handovers", "", "", "", "", "", "", "", "Conexão"],
                       ["", "Disparados", "Cancelados pelo RIC", "Latência para início do handover (ns)", "Iniciados", "Bem sucedidos", "Mal sucedidos", "Duração do handover (ns)", "Média de handovers por UE", "Reconfigurações"]
                       ]
for outputFile in output_and_args.keys():
    if not os.path.exists(os.path.join(curr_dir, outputFile)):
        return_code, stdout, stderr = run_ns3("run HandoverXappsScenario -- %s" % output_and_args[outputFile])
        if return_code != 0:
            exit(return_code)
        shutil.move(os.path.join(ns3_path, "output.csv"),
                    os.path.join(curr_dir, outputFile))
        shutil.move(os.path.join(ns3_path, "anim.xml"),
                    os.path.join(curr_dir, outputFile.replace("output", "anim").replace(".csv", ".xml")) )

    with open(os.path.join(curr_dir, outputFile), "r") as f:
        resultingCsv[outputFile] = DictReader(f.readlines())

    handoversTriggered = 0
    handoversInitiated = 0
    handoversOK = 0
    handoversError = 0
    handoversCancelled = 0
    handoversLatency = []
    cancelledHandoversLatency = []
    handoversPerUE = {}
    handoversTriggeredPerUE = {}
    connectionReconfiguration = 0
    connectionReconfigurationPerUE = {}

    for line in resultingCsv[outputFile]:
        imsi = line["IMSI"]
        if imsi not in handoversPerUE:
            handoversPerUE[imsi] = [[], []]  # start, ok/fail
            handoversTriggeredPerUE[imsi] = [[], []]  # trigger, cancelled/startenb
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
            continue
        if line["Type"] == "CONNECTION_ERROR_ENB":
            continue
        if line["Type"] == "CONNECTION_START_UE":
            continue
        if line["Type"] == "CONNECTION_ESTABLISHED_UE":
            continue
        if line["Type"] == "CONNECTION_ERROR_UE":
            continue
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
    if len(cancelledHandoversLatency) == 0:
        cancelledHandoversLatency.extend([0, 0])
    meanHandovers = handoversInitiated / len(handoversPerUE.keys())
    consolidatedResults.append([output_and_type[outputFile], f"{handoversTriggered}", f"{handoversCancelled}", f"{statistics.mean(cancelledHandoversLatency)}+-{statistics.stdev(cancelledHandoversLatency)}", f"{handoversInitiated}", f"{handoversOK}", f"{handoversError}", f"{statistics.mean(handoversLatency)}+-{statistics.stdev(handoversLatency)}", f"{meanHandovers}", f"{connectionReconfiguration}"])

    pass

with open(os.path.join(curr_dir, "consolidated.csv"), "w") as f:
    for line in consolidatedResults:
        f.write(",".join(line)+"\n")

pass
