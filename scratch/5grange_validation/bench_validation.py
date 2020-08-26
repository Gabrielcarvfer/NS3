import os
import matplotlib
import shutil
import multiprocessing as mp
from plot_mcs_distribution import plot_mcs_dist as plot_mcs
from plot_snr_distribution import plot_snr_dist as plot_snr

cwd = os.path.abspath(os.getcwd())
base_dir = "../../build/bin/"
output_dir = os.path.abspath(base_dir) + "/range_bench_validation/"


# Spawn processes passing the arguments for each simulation
def exec_sim_parameters(*arg_tuple):
    import subprocess
    forceMaxMcs = arg_tuple[0]
    channel_model = arg_tuple[1]
    distance = arg_tuple[2]
    folder = arg_tuple[3]
    if os.path.exists(folder+"sinr.png"):
        return True

    try:
        #Execute simulation
        cmd = "bash -c"
        cmd += " \"NS_LOG=LteAmc"
        cmd += " ../../../../5grange_cdl_test"
        cmd += " --forceMaxMcsSched=" + ("true" if forceMaxMcs else "false")
        cmd += " --useCdlPathLoss=" + ("true" if channel_model == "CDL" else "false")
        cmd += " --distance=%s" % (distance*1000)
        cmd += " \""
        simProc = subprocess.run(cmd,
                                 stdout=subprocess.PIPE,
                                 stderr=subprocess.STDOUT,
                                 cwd=folder
                                 )

        with open(folder+"out%dkm.txt" % distance, "w") as file:
            file.write(simProc.stdout.decode("utf-8"))

        throughputProc = subprocess.run(["python",
                                         cwd+os.sep+"get_thr.py"
                                         ],
                                        stdout=subprocess.PIPE,
                                        stderr=subprocess.STDOUT,
                                        cwd=folder
                                        )

        with open(folder+"perf.txt", "w") as file:
            file.write(throughputProc.stdout.decode("utf-8"))

        plot_mcs([distance], base_dir=folder, cmd=True)
        plot_snr([distance], base_dir=folder, cmd=True)

    except Exception:
        return False
    finally:
        return True


def make_dir(dir):
    try:
        os.mkdir(dir)
    except FileExistsError:
        pass


if __name__ == "__main__":
    mp.freeze_support()
    channel_models = ("CDL", "RANGE5G")
    distances = [1, 5, 10, 20, 35, 50, 100, ]

    thread_parameters = []

    make_dir(output_dir)
    for forceMaxMcs in [False, True]:
        maxMcsFolder = output_dir+"ForceMaxMcs_%s" % str(forceMaxMcs) + os.sep
        make_dir(maxMcsFolder)
        for channel_model in channel_models:
            channelFolder = maxMcsFolder + channel_model + os.sep
            make_dir(channelFolder)
            for distance in distances:
                distanceFolder = channelFolder + str(distance) + "km" + os.sep
                make_dir(distanceFolder)
                thread_parameters.append((forceMaxMcs, channel_model, distance, distanceFolder))


    del distance, distanceFolder, channel_model, channelFolder, forceMaxMcs, maxMcsFolder

    with mp.Pool(processes=10) as p:
        p.starmap(func=exec_sim_parameters, iterable=thread_parameters)






