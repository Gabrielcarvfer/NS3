import os
import re
import matplotlib
import shutil
import matplotlib.pyplot as plt
import multiprocessing as mp
from plot_mcs_distribution import plot_mcs_dist as extract_n_plot_mcs
from plot_mcs_distribution import plot_mcs_hist as plot_mcs
from plot_snr_distribution import plot_snr_hist as plot_snr
from plot_snr_distribution import plot_snr_dist as extract_n_plot_snr

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

    if not os.path.exists(folder+"sinr.png"):
        try:
            #Execute simulation
            cmd = "bash -c"
            cmd += " \"NS_LOG=LteAmc:LteSpectrumPhy"
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
        except Exception:
            return False, None, None
    mcs = extract_n_plot_mcs([distance], base_dir=folder, cmd=True)
    snr = extract_n_plot_snr([distance], base_dir=folder, cmd=True)
    return True, mcs, snr


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

    # Create folders to dump simulation results
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

    # Run simulation programs and scripts to process results
    results = None
    with mp.Pool(processes=10) as p:
        results = p.starmap(func=exec_sim_parameters, iterable=thread_parameters)

    # Aggregate results in a useful manner
    for forceMaxMcs in [False, True]:
        maxMcsFolder = output_dir+"ForceMaxMcs_%s" % str(forceMaxMcs) + os.sep
        for channel_model in channel_models:
            channelFolder = maxMcsFolder + channel_model + os.sep
            mcs_freq_per_d = {}
            snr_freq_per_d = {}

            # Aggregate MCS and SNR results for different distances
            for distance in distances:
                # Pop MCS and SNR distribution results
                finished, mcs_freq, snr_freq = results.pop(0)
                mcs_freq_per_d.update(mcs_freq)
                snr_freq_per_d.update(snr_freq)

            # Create output figures for MCS and SNR
            fig, axis = plt.subplots(nrows=len(mcs_freq_per_d))
            if len(distances) == 1:
                axis = [axis]

            fig2, axis2 = plt.subplots(nrows=len(snr_freq_per_d))
            if len(distances) == 1:
                axis2 = [axis2]

            # Plot aggregated results for MCS and SNR
            axis[-1].set_xlabel("MCS")
            axis2[-1].set_xlabel("SNR")
            plot_mcs(axis, mcs_freq_per_d)
            plot_snr(axis2, snr_freq_per_d)

            # Save results to output files for MCS and SNR
            fig.savefig(channelFolder+"mcs.png")
            fig2.savefig(channelFolder+"snr.png")

            # Clean environment of MCS and SNR variables
            del fig, fig2, axis, axis2, mcs_freq_per_d, snr_freq_per_d, distance, finished, mcs_freq, snr_freq


            # Aggregate results for different distances
            corrupted_freq_per_d = {}
            for distance in distances:
                distanceFolder = channelFolder + str(distance) + "km" + os.sep

                # Open out__km.txt and scan for corrupted transport blocks to calculate the error rate
                contents = None
                with open("out%dkm.txt" % distance, "r") as file:
                    contents = file.readlines()

                corrupted_regex = re.compile(".* corrupted (.*).*")
                corrupted_TBs = 0
                total_TBs = 0

                for line in contents:
                    regex = corrupted_regex.match(line)
                    if regex is None:
                        continue
                    total_TBs += 1
                    corrupted = regex.groups()[0]
                    corrupted = int(corrupted)
                    corrupted_TBs += corrupted
                corrupted_freq_per_d[distance] = (corrupted_TBs, total_TBs)
                del regex, line, contents, corrupted, file
            del corrupted_TBs, total_TBs, contents




