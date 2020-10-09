import os
import random
import re
from enum import Enum
import pickle
import lzma
import statistics
import matplotlib
import shutil
import matplotlib.pyplot as plt
import multiprocessing as mp
import json
from plot_mcs_distribution import plot_mcs_dist as extract_n_plot_mcs
from plot_mcs_distribution import plot_mcs_hist as plot_mcs
from plot_snr_distribution import plot_snr_hist as plot_snr
from plot_snr_distribution import plot_snr_dist as extract_n_plot_snr

cwd = os.path.abspath(os.getcwd())
base_dir = "../../build/bin/"
output_dir = os.path.abspath(base_dir) + "/range_bench_validation/"
plt.ioff()  # disable interactive plotting

# Spawn processes passing the arguments for each simulation
def exec_sim_parameters(*arg_tuple):
    import subprocess
    forceMaxMcs = arg_tuple[0]
    channel_model = arg_tuple[1]
    distance = arg_tuple[2]
    folder = arg_tuple[3]
    numAntenna = arg_tuple[4]
    mimoMode = arg_tuple[5]
    frequencyBand = arg_tuple[6]

    if not os.path.exists(folder+"sinr.png"):
        try:
            #Execute simulation
            cmd = "bash -c"
            cmd += " \"NS_LOG=LteAmc:LteSpectrumPhy"
            cmd += " ../../../../../../../5grange_cdl_test"
            cmd += " --forceMaxMcsSched=" + ("true" if forceMaxMcs else "false")
            if "CDL" in channel_model:
                cmd += " --useCdlPathLoss=true"
                cmd += " --cdlType=" + channel_model
            else:
                cmd += " --useCdlPathLoss=false"
            cmd += " --numAntennas=%d" % numAntenna
            cmd += " --mimoMode=%d" % mimoMode
            cmd += " --distance=%s" % (distance*1000)
            cmd += " --freqBand=%s" % (frequencyBand)
            cmd += " \""

            if not os.path.exists(folder+"out%dkm.txt.lzma" % distance):
                simProc = subprocess.run(cmd,
                                         stdout=subprocess.PIPE,
                                         stderr=subprocess.STDOUT,
                                         cwd=folder
                                         )

                with lzma.open(folder+"out%dkm.txt.lzma" % distance, "w") as file:
                    file.write(simProc.stdout)

                del_file(folder+"schedulerInput.txt")
                del_file(folder+"schedulerOutput.txt")

            if not os.path.exists(folder+"perf.txt"):
                throughputProc = subprocess.run(["python",
                                                 cwd+os.sep+"get_thr.py"
                                                 ],
                                                stdout=subprocess.PIPE,
                                                stderr=subprocess.STDOUT,
                                                cwd=folder
                                                )

                with open(folder+"perf.txt", "w", encoding="utf-8") as file:
                    file.writelines(throughputProc.stdout.decode("utf-8"))

        except Exception as e:
            return False, None, None
    mcs = None  # extract_n_plot_mcs([distance], base_dir=folder, cmd=True)
    snr = None  # extract_n_plot_snr([distance], base_dir=folder, cmd=True)
    return True, mcs, snr


def del_file(path):
    if os.path.exists(path):
        os.remove(path)


def make_dir(dir):
    try:
        os.mkdir(dir)
    except FileExistsError:
        pass


def randcolor():
    return random.random(), random.random(), random.random()

# look at lte-spectrum-value-helper.h for values
class freqBands(Enum):
    MHz850 = 5
    MHz713 = 12
    MHz525 = 101
    MHz240 = 100

class mimoModes(Enum):
    SISO = 0
    TxDiversity = 1
    SpatialMultiplexing = 2

mimoMarkers = ("o", "p", "*")

def extract_throughput(distanceFolder):
    # Open perf.txt and scan for received throughput
    contents = None
    with open(distanceFolder + "perf.txt", "r", encoding="utf-8") as file:
        contents = file.readlines()

    PHY_DL_received_throughput_regex = re.compile("DL Vazão: (.*)mbps")
    #PHY_DL_injected_throughput_regex = re.compile("Vazão esperada PHY: (.*)mbps")

    regex = None
    throughput = 0.0
    for line in contents:
        regex = PHY_DL_received_throughput_regex.match(line)
        if regex is None:
            continue
        throughput = regex.groups()[0]
        throughput = float(throughput)
    # field trials used 2/3 code rate instead of 5/6,
    #   we compensate for that reducing the throughput here
    #   and increasing the antenna gain on the simulation side
    return throughput#*0.8

def extract_corruption(distanceFolder, distance):
    # Open out__km.txt and scan for corrupted transport blocks to calculate the error rate
    contents = None
    with lzma.open(distanceFolder + "out%dkm.txt.lzma" % distance, "r") as file:
        contents = file.readlines()

    corrupted = 0
    corrupted_regex = re.compile(".* corrupted (.*).*")
    corrupted_TBs = 0
    total_TBs = 0

    regex = None
    for line in contents:
        regex = corrupted_regex.match(line.decode("utf-8"))
        if regex is None:
            continue
        total_TBs += 1
        corrupted = regex.groups()[0]
        if "snr" in corrupted:
            continue
        corrupted = int(corrupted)
        corrupted_TBs += corrupted

    return corrupted_TBs/total_TBs*100 if corrupted_TBs > 0 else 0

def extract_perf(distanceFolder, distance):
    return extract_throughput(distanceFolder), extract_corruption(distanceFolder, distance)

if __name__ == "__main__":
    mp.freeze_support()
    frequencyBands = (freqBands.MHz525, )  # (freqBands.MHz850, freqBands.MHz713, freqBands.MHz525, freqBands.MHz240)
    numAntennas = (1, 2, 4, )
    mimoModes = (mimoModes.SISO, mimoModes.TxDiversity)  # , mimoModes.SpatialMultiplexing)
    channel_models = ("RANGE5G", "CDL_D", "CDL_A",)
    forcedMaxMcs = (False, )  # True,)
    distances = [1, 5, 10, 20, 35, 50, 100, ]
    batches = 20

    thread_parameters = []
    # Create folders to dump simulation results
    make_dir(output_dir)
    for batch in range(batches):
        batch_output_dir = output_dir + str(batch) + os.sep
        make_dir(batch_output_dir)
        for forceMaxMcs in forcedMaxMcs:
            maxMcsFolder = batch_output_dir + "ForceMaxMcs_%s" % str(forceMaxMcs) + os.sep
            make_dir(maxMcsFolder)
            for frequencyBand in frequencyBands:
                frequencyFolder = maxMcsFolder + "freq_%s" % frequencyBand.name + os.sep
                make_dir(frequencyFolder)
                for (numAntenna, mimoMode) in zip(numAntennas, mimoModes):
                    antennaAndMimoFolder = frequencyFolder + "Mimo_%s" % mimoMode.name + os.sep
                    make_dir(antennaAndMimoFolder)
                    for channel_model in channel_models:
                        channelFolder = antennaAndMimoFolder + channel_model + os.sep
                        make_dir(channelFolder)
                        for distance in distances:
                            distanceFolder = channelFolder + str(distance) + "km" + os.sep
                            make_dir(distanceFolder)
                            thread_parameters.append((forceMaxMcs, channel_model, distance, distanceFolder, numAntenna, mimoMode.value, frequencyBand.value))

    del distance, distanceFolder, channel_model, channelFolder, forceMaxMcs, maxMcsFolder, numAntenna, mimoMode

    # Run simulation programs and scripts to process results


    plt.rcParams.update({'figure.max_open_warning': 1000})
    figSize = (4, 3)

    lzma_pickle_results = "resultsDump.pickle.lzma"

    batch_results = {"batch": {}}


    if os.path.exists(lzma_pickle_results):
        with lzma.open(lzma_pickle_results, "rb") as f:
            batch_results = pickle.load(f)
    else:
        results = None
        with mp.Pool(processes=10) as p:
            results = p.starmap(func=exec_sim_parameters, iterable=thread_parameters)

        # Aggregate results in a useful manner
        for batch in range(batches):
            batch_output_dir = output_dir + str(batch) + os.sep
            batch_results["batch"][batch] = {"forceMaxMcs": {}}

            for forceMaxMcs in forcedMaxMcs:
                maxMcsFolder = batch_output_dir +"ForceMaxMcs_%s" % str(forceMaxMcs) + os.sep
                batch_results["batch"][batch]["forceMaxMcs"][forceMaxMcs] = {"frequencyBand": {}}

                for frequencyBand in frequencyBands:
                    frequencyFolder = maxMcsFolder + "freq_%s" % frequencyBand.name + os.sep
                    batch_results["batch"][batch]["forceMaxMcs"][forceMaxMcs]["frequencyBand"][frequencyBand] = {"TBLER": {},
                                                                                                                 "THR": {}}

                    for (numAntenna, mimoMode) in zip(numAntennas, mimoModes):
                        antennaAndMimoFolder = frequencyFolder + "Mimo_%s" % mimoMode.name + os.sep

                        # Create output figure for corruption rate plots
                        fig3, axis3 = plt.subplots(figsize=figSize)
                        axis3 = [axis3]

                        # Create output figure for throughput plots
                        fig4, axis4 = plt.subplots(figsize=figSize)
                        axis4 = [axis4]

                        for channel_model in channel_models:
                            channelFolder = antennaAndMimoFolder + channel_model + os.sep

                            pool_args = []
                            for distance in distances:
                                distanceFolder = channelFolder + str(distance) + "km" + os.sep
                                pool_args.append((distanceFolder, distance))

                            result = p.starmap(func=extract_perf, iterable=pool_args)

                            for distance in distances:
                                batch_results["batch"][batch]["forceMaxMcs"][forceMaxMcs]["frequencyBand"][frequencyBand]["THR"]["%s-%dAnt-%s" %(channel_model, numAntenna, mimoMode.name)] = result[distance][0]
                                batch_results["batch"][batch]["forceMaxMcs"][forceMaxMcs]["frequencyBand"][frequencyBand]["TBLER"]["%s-%dAnt-%s" %(channel_model, numAntenna, mimoMode.name)] = result[distance][1]

                        """
                        # Set axis labels for corruption rate plot
                        axis3[-1].set_xlabel("Distance (km)")
                        axis3[-1].set_ylabel("Corruption rate (%)")
                        axis3[-1].legend()
    
                        # Save results to output files for corruption rate
                        fig3.savefig(antennaAndMimoFolder+"corruption_rate.png", bbox_inches='tight', dpi=300)
    
                        # Set axis labels for corruption rate plot
                        axis4[-1].set_xlabel("Distance (km)")
                        axis4[-1].set_ylabel("Received throughput (Mbps)")
                        axis4[-1].legend()
    
                        # Save results to output files for corruption rate
                        fig4.savefig(antennaAndMimoFolder+"throughput.png", bbox_inches='tight', dpi=300)
                        """
                        pass
                    pass

        with lzma.open(lzma_pickle_results, "wb") as f:
            pickle.dump(batch_results, f)

    with mp.Pool(processes=10) as p:
        for forceMaxMcs in forcedMaxMcs:
            batch_results["batch"][batch]["forceMaxMcs"][forceMaxMcs] = {"frequencyBand": {}}

            for frequencyBand in frequencyBands:
                fig5, axis5 = plt.subplots(figsize=(10, 6))
                axis5 = [axis5]

                fig6, axis6 = plt.subplots(figsize=(10, 6))
                axis6 = [axis6]

                # Calculate statistics between batches
                TBLER = None
                THR = None
                for batch in range(batches-1):
                    if TBLER is None:
                        TBLER = batch_results["batch"][batch]["forceMaxMcs"][forceMaxMcs]["frequencyBand"][frequencyBand]["TBLER"]
                        for key, valueDict in TBLER.items():
                            for distance in valueDict.keys():
                                TBLER[key][distance] = [valueDict[distance]]
                    else:
                        for key, valueDict in batch_results["batch"][batch]["forceMaxMcs"][forceMaxMcs]["frequencyBand"][frequencyBand]["TBLER"].items():
                            for distance in valueDict.keys():
                                TBLER[key][distance].append(valueDict[distance])

                    if THR is None:
                        THR = batch_results["batch"][batch]["forceMaxMcs"][forceMaxMcs]["frequencyBand"][frequencyBand]["THR"]
                        for key, valueDict in THR.items():
                            for distance in valueDict.keys():
                                THR[key][distance] = [valueDict[distance]]
                    else:
                        for key, valueDict in batch_results["batch"][batch]["forceMaxMcs"][forceMaxMcs]["frequencyBand"][frequencyBand]["THR"].items():
                            for distance in valueDict.keys():
                                THR[key][distance].append(valueDict[distance])

                # Calculate statistics and plot
                z_value = 1.96  # for p=0.05
                for lab in sorted(list(THR.keys())):
                    received_throughput_per_d = {}
                    received_throughput_per_d_error = {}
                    for distance in THR[lab].keys():
                        received_throughput_per_d[distance] = statistics.mean(THR[lab][distance])
                        received_throughput_per_d_error[distance] = statistics.stdev(THR[lab][distance])*z_value/((batches)**0.5)
                    axis6[0].errorbar(list(received_throughput_per_d.keys()), list(received_throughput_per_d.values()), yerr=list(received_throughput_per_d_error.values()), label=lab, color=randcolor())

                for lab in sorted(list(TBLER.keys())):
                    corrupted_freq_per_d = {}
                    corrupted_freq_per_d_error = {}
                    for distance in TBLER[lab].keys():
                        corrupted_freq_per_d[distance] = statistics.mean(TBLER[lab][distance])
                        corrupted_freq_per_d_error[distance] = statistics.stdev(TBLER[lab][distance])*z_value/((batches)**0.5)
                    axis5[0].errorbar(list(corrupted_freq_per_d.keys()), list(corrupted_freq_per_d.values()), yerr=list(corrupted_freq_per_d_error.values()), label=lab, color=randcolor())


                # Set axis labels for corruption rate plot
                axis5[-1].set_xlabel("Distance (km)")
                axis5[-1].set_ylabel("Transport Block Corruption Rate (%)")
                axis5[-1].legend(bbox_to_anchor=(0, -0.25, 1, 0.2), loc="lower left",
                                 mode="expand", ncol=3, borderaxespad=0, columnspacing=4.0, fontsize=10)

                # Save results to output files for corruption rate
                fig5.savefig("corruption_rate.png", bbox_inches='tight', dpi=300)

                # Set axis labels for corruption rate plot
                axis6[-1].set_xlabel("Distance (km)")
                axis6[-1].set_ylabel("Received Throughput (Mbps)")
                axis6[-1].legend(bbox_to_anchor=(0, -0.25, 1, 0.2), loc="lower left",
                                 mode="expand", ncol=3, borderaxespad=0, fontsize=10)

                # Save results to output files for corruption rate
                fig6.savefig("throughput.png", bbox_inches='tight', dpi=300)

            pass
        # end main
        pass
