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
    maxMcsSched = arg_tuple[1]
    channel_model = arg_tuple[2]
    distance = arg_tuple[3]
    folder = arg_tuple[4]
    numAntenna = arg_tuple[5]
    mimoMode = arg_tuple[6]
    frequencyBand = arg_tuple[7]

    if not os.path.exists(folder+"sinr.png"):
        try:
            if os.sep == "\\":
                #Execute simulation
                cmd = "bash -c"
                cmd += " \"NS_LOG=LteAmc:LteSpectrumPhy"
                cmd += " ../../../../../../../5grange_cdl_test"
                cmd += " --forceMaxMcsSched=" + ("true" if forceMaxMcs else "false")
                cmd += " --maxMcsSched=" + maxMcsSched
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
            else:
                cmd = [os.getcwd() + os.sep + ".." + os.sep + ".." + os.sep + "build/bin/5grange_cdl_test", "\""]
                cmd += ["--forceMaxMcsSched=%s" % ("true" if forceMaxMcs else "false")]
                cmd += ["--maxMcsSched=%d" % maxMcsSched]
                if "CDL" in channel_model:
                    cmd += ["--useCdlPathLoss=true"]
                    cmd += ["--cdlType=%s" % channel_model]
                else:
                    cmd += ["--useCdlPathLoss=false"]
                cmd += ["--numAntennas=%d" % numAntenna]
                cmd += ["--mimoMode=%d" % mimoMode]
                cmd += ["--distance=%s" % (distance*1000)]
                cmd += ["--freqBand=%s" % (frequencyBand)]
                cmd += ["\""]

            if not os.path.exists(folder+"out%dkm.txt.lzma" % distance):
                simProc = subprocess.run(cmd,
                                         stdout=subprocess.PIPE,
                                         stderr=subprocess.STDOUT,
                                         cwd=folder,
                                         env={"NS_LOG": "LteAmc:LteSpectrumPhy"}
                                         )

                with lzma.open(folder+"out%dkm.txt.lzma" % distance, "w") as file:
                    file.write(simProc.stdout)

                del_file(folder+"schedulerInput.txt")
                del_file(folder+"schedulerOutput.txt")

            if not os.path.exists(folder+"perf.txt"):
                throughputProc = subprocess.run(["python3",
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
    mcs = None # extract_n_plot_mcs([distance], base_dir=folder, cmd=True)
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

    return throughput

def extract_corruption_and_mcs(distanceFolder, distance):
    # Open out__km.txt and scan for corrupted transport blocks to calculate the error rate
    contents = None
    with lzma.open(distanceFolder + "out%dkm.txt.lzma" % distance, "r") as file:
        contents = file.readlines()

    corrupted = 0
    corrupted_regex = re.compile(".* corrupted (.*).*")
    corrupted_TBs = 0
    total_TBs = 0

    mcs_regex = re.compile(".*MCS (.*) TBLER .*")
    mcs_freq = {}
    for mcs in range(28):
        mcs_freq[mcs] = 0

    mcs = None
    regex = None
    for line in contents:
        regex = corrupted_regex.match(line.decode("utf-8"))
        if regex is not None:
            total_TBs += 1
            corrupted = regex.groups()[0]
            if "snr" in corrupted:
                continue
            corrupted = int(corrupted)
            corrupted_TBs += corrupted
            continue

        regex = mcs_regex.match(line.decode("utf-8"))
        if regex is None:
            continue
        mcs = regex.groups()[0]
        mcs = int(mcs)
        mcs_freq[mcs] += 1

    return (corrupted_TBs/total_TBs*100 if corrupted_TBs > 0 else 0, mcs_freq)


def extract_perf(distanceFolder, distance):
    return extract_throughput(distanceFolder), *extract_corruption_and_mcs(distanceFolder, distance)


# Results for 713MHz carrier with 6MHz channel bandwidth
fieldTrialResults = {"LOS": {
                                10:{"d_km": 10,
                                 "thr_Mbps": 22,
                                 "ber": 0,
                                 "mcs_trial": "QAM64 3/4 trial A",
                                 "nearest_mcs_to_simulate": 19,
                                 "gain_adj_mult": 1,
                                 "throughtput_adj_mult": 1
                                 },
                                20:{"d_km": 20,
                                 "thr_Mbps": 22,
                                 "ber": 0,
                                 "mcs_trial": "QAM64 3/4 trial A",
                                 "nearest_mcs_to_simulate": 19,
                                 "gain_adj_mult": 1,
                                 "throughtput_adj_mult": 1
                                 },
                                20:{
                                    "d_km": 20,
                                    "thr_Mbps": 22,
                                    "ber": 0,
                                    "mcs_trial": "QAM64 3/4 trial B",
                                    "nearest_mcs_to_simulate": 15,
                                    "gain_adj_mult": 1,
                                    "throughtput_adj_mult": 1
                                },
                                50:{"d_km": 50,
                                 "thr_Mbps": 22,
                                 "ber": 0,
                                 "mcs_trial": "QAM64 3/4",
                                 "nearest_mcs_to_simulate": 19,
                                 "gain_adj_mult": 1,
                                 "throughtput_adj_mult": 1
                                 }
                            },
                     "NLOS": {

                                30:{"d_km": 30,
                                 "thr_Mbps": 13,
                                 "ber": 0,
                                 "mcs_trial": "QAM16 2/3 trial A",
                                 "nearest_mcs_to_simulate": 14,
                                 "gain_adj_mult": 1,
                                 "throughtput_adj_mult": 1
                                 },
                                30:{"d_km": 30,
                                    "thr_Mbps": 13,
                                    "ber": 0,
                                    "mcs_trial": "QAM16 2/3 trial B",
                                    "nearest_mcs_to_simulate": 14,
                                    "gain_adj_mult": 1,
                                    "throughtput_adj_mult": 1
                                    },
                                30:{"d_km": 30,
                                    "thr_Mbps": 13,
                                    "ber": 0,
                                    "mcs_trial": "QAM16 2/3 trial C",
                                    "nearest_mcs_to_simulate": 14,
                                    "gain_adj_mult": 1,
                                    "throughtput_adj_mult": 1
                                    },
                                40:{"d_km": 40,
                                 "thr_Mbps": 13,
                                 "ber": 0.5,
                                 "mcs_trial": "QAM16 2/3 trial A",
                                 "nearest_mcs_to_simulate": 14,
                                 "gain_adj_mult": 1,
                                 "throughtput_adj_mult": 1
                                 },
                                 40:{"d_km": 40,
                                  "thr_Mbps": 13,
                                  "ber": 0.5,
                                  "mcs_trial": "QAM16 2/3 trial B",
                                  "nearest_mcs_to_simulate": 14,
                                  "gain_adj_mult": 1,
                                  "throughtput_adj_mult": 1
                                  },
                             }
                     }

# Results for 525MHz carrier with 24MHz channel bandwidth
fieldTrialResults = {"LOS": {
                            50: {"d_km": 50.5,
                                 "thr_Mbps": 102,
                                 "ber": 0,
                                 # QAM256 2/3 isn't available in latest MCS scheme, so we approximate by adding gain and reducing throughput
                                 "mcs_trial": "QAM256 2/3",
                                 "nearest_mcs_to_simulate": 24,  # QAM256 5/6
                                 "gain_adj_add": 3,  # link gain, can be added to eNB or UE
                                 "throughtput_adj_mult": 0.8
                                },
                        }
                    }

if __name__ == "__main__":
    mp.freeze_support()
    import numpy
    import pandas
    frequencyBands = (freqBands.MHz525, )  # (freqBands.MHz850, freqBands.MHz713, freqBands.MHz525, freqBands.MHz240)
    numAntennas = (2, )  # 1, 4
    mimoModes = (mimoModes.TxDiversity, )  # mimoModes.SISO, mimoModes.SpatialMultiplexing)
    channel_models = ("CDL_D", "CDL_A",)  # "RANGE5G",
    forcedMaxMcs = (False, )  # False, True,)
    distances = [ 1, 5, 10, 20, 35, 50, 100, ]  # 10, 20, 30, 40,
    batches = 3

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

                            if distance in fieldTrialResults["LOS" if channel_model == "CDL_D" else "NLOS"]:
                                # Get trial parameters and forward to simulation
                                sample = fieldTrialResults["LOS" if channel_model == "CDL_D" else "NLOS"][distance]
                            #else:
                            #    # If field trial doesn't have the sample for LOS/NLOS, use the NLOS/LOS MCS for consistency
                            #    sample = fieldTrialResults["LOS" if channel_model != "CDL_D" else "NLOS"][distance]

                            maxMcsSched = sample["nearest_mcs_to_simulate"]
                            sample = None
                            try:
                                if distance in fieldTrialResults["LOS" if channel_model == "CDL_D" else "NLOS"]:
                                    # Get trial parameters and forward to simulation
                                    sample = fieldTrialResults["LOS" if channel_model == "CDL_D" else "NLOS"][distance]
                                else:
                                    # If field trial doesn't have the sample for LOS/NLOS, use the NLOS/LOS MCS for consistency
                                    sample = fieldTrialResults["LOS" if channel_model != "CDL_D" else "NLOS"][distance]
                                maxMcsSched = sample["nearest_mcs_to_simulate"]
                            except:
                                maxMcsSched = 1
                            thread_parameters.append((forceMaxMcs, maxMcsSched-1, channel_model, distance, distanceFolder, numAntenna, mimoMode.value, frequencyBand.value))
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
                                                                                                                     "THR": {},
                                                                                                                     "MCS_DIST": {}}

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

                                i = 0
                                label = "%s-%dAnt-%s" % (channel_model, numAntenna, mimoMode.name)
                                batch_results["batch"][batch]["forceMaxMcs"][forceMaxMcs]["frequencyBand"][frequencyBand]["THR"][label] = {}
                                batch_results["batch"][batch]["forceMaxMcs"][forceMaxMcs]["frequencyBand"][frequencyBand]["TBLER"][label] = {}
                                batch_results["batch"][batch]["forceMaxMcs"][forceMaxMcs]["frequencyBand"][frequencyBand]["MCS_DIST"][label] = {}
                                for folder, distance in pool_args:
                                    batch_results["batch"][batch]["forceMaxMcs"][forceMaxMcs]["frequencyBand"][frequencyBand]["THR"][label][distance] = result[i][0]
                                    batch_results["batch"][batch]["forceMaxMcs"][forceMaxMcs]["frequencyBand"][frequencyBand]["TBLER"][label][distance] = result[i][1]
                                    batch_results["batch"][batch]["forceMaxMcs"][forceMaxMcs]["frequencyBand"][frequencyBand]["MCS_DIST"][label][distance] = result[i][2]
                                    i += 1
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

    #with lzma.open("/media/gabri/dev/tools/source/NS3/build/bin/range_bench_validation/0/ForceMaxMcs_True/freq_MHz713/Mimo_TxDiversity/CDL_A/50km/out50km.txt.lzma", "rb") as f:
    #    contents = [line.decode('utf-8') for line in f.readlines()]
    #endrxlines = []
    #for line in contents:
    #    if "corrupted" in line:
    #        endrxlines.append(line);

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
            MCS_DIST = None
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

                if MCS_DIST is None:
                    temp_mcs_dist = batch_results["batch"][batch]["forceMaxMcs"][forceMaxMcs]["frequencyBand"][frequencyBand]["MCS_DIST"]
                    MCS_DIST = {}
                    for key, valueDict in temp_mcs_dist.items():
                        MCS_DIST[key] = {}
                        for distance in valueDict.keys():
                            MCS_DIST[key][distance] = {}
                            for mcs in valueDict[distance].keys():
                                MCS_DIST[key][distance][mcs] = [valueDict[distance][mcs]]
                else:
                    for key, valueDict in batch_results["batch"][batch]["forceMaxMcs"][forceMaxMcs]["frequencyBand"][frequencyBand]["MCS_DIST"].items():
                        for distance in valueDict.keys():
                            for mcs in valueDict[distance].keys():
                                MCS_DIST[key][distance][mcs].append(valueDict[distance][mcs])

            # Calculate statistics and plot
            from collections import OrderedDict
            plot_dataset = OrderedDict({"THR": {},
                            "TBLER": {}
                            })
            error_dataset = OrderedDict({"THR": {},
                             "TBLER": {}
                             })
            z_value = 4.303  # p=0.05 requires 1.96 with #samples=infty, 2.0 with #samples=40, 2.262 with #samples=10, 4.303 with #samples=3
            for lab in sorted(list(THR.keys())):
                received_throughput_per_d = {}
                received_throughput_per_d_error = {}
                for distance in distances:
                    if distance in THR[lab].keys():
                        received_throughput_per_d[distance] = statistics.mean(THR[lab][distance]) # trial samples are for 6MHz wide channels instead of 24MHz wide like ours
                        received_throughput_per_d_error[distance] = statistics.stdev(THR[lab][distance])*z_value/((batches)**0.5)
                    else:
                        received_throughput_per_d[distance] = 0
                        received_throughput_per_d_error[distance] = 0
                #axis6[0].bar(list(received_throughput_per_d.keys()), list(received_throughput_per_d.values()), yerr=list(received_throughput_per_d_error.values()), label=lab, color=randcolor())
                lab = "Simulation %s" % lab[:5].replace("CDL_D", "LOS").replace("CDL_A", "NLOS")
                plot_dataset["THR"][lab] = list(received_throughput_per_d.values())
                error_dataset["THR"][lab] = list(received_throughput_per_d_error.values())
            del lab, sample, received_throughput_per_d, received_throughput_per_d_error

            for lab in sorted(list(TBLER.keys())):
                corrupted_freq_per_d = {}
                corrupted_freq_per_d_error = {}
                for distance in distances:
                    if distance in TBLER[lab].keys():
                        corrupted_freq_per_d[distance] = statistics.mean(TBLER[lab][distance])
                        corrupted_freq_per_d_error[distance] = statistics.stdev(TBLER[lab][distance])*z_value/((batches)**0.5)
                    else:
                        corrupted_freq_per_d[distance] = 0
                        corrupted_freq_per_d_error[distance] = 0
                #axis5[0].bar(list(corrupted_freq_per_d.keys()), list(corrupted_freq_per_d.values()), yerr=list(corrupted_freq_per_d_error.values()), label=lab, color=randcolor())
                lab = "Simulation %s" % lab[:5].replace("CDL_D", "LOS").replace("CDL_A", "NLOS")
                plot_dataset["TBLER"][lab] = list(corrupted_freq_per_d.values())
                error_dataset["TBLER"][lab] = list(corrupted_freq_per_d_error.values())
            del lab, corrupted_freq_per_d, corrupted_freq_per_d_error

            for lab in sorted(list(MCS_DIST.keys())):
                mcs_dist_per_d = {}
                mcs_dist_per_d_error = {}
                for distance in distances:
                    if distance in MCS_DIST[lab].keys():
                        mcs_dist_per_d[distance] = {}
                        mcs_dist_per_d_error[distance] = {}
                        for mcs in MCS_DIST[lab][distance].keys():
                            mcs_dist_per_d[distance][mcs] = statistics.mean(MCS_DIST[lab][distance][mcs])
                            mcs_dist_per_d_error[distance][mcs] = statistics.stdev(MCS_DIST[lab][distance][mcs])*z_value/((batches)**0.5)
                #axis5[0].bar(list(corrupted_freq_per_d.keys()), list(corrupted_freq_per_d.values()), yerr=list(corrupted_freq_per_d_error.values()), label=lab, color=randcolor())
                lab = "%s Simulation" % lab[:5].replace('_', ' ')

                fig, axis = plt.subplots(nrows=len(mcs_dist_per_d), sharex=True, sharey=True, figsize=(5, 8))
                if len(distances) == 1:
                    axis = [axis]

                i = 0
                for d in mcs_dist_per_d:
                    tripa = []
                    tripa_err = []
                    total_freq = 0
                    temp = 0
                    for mcs in mcs_dist_per_d[d]:
                        total_freq += mcs_dist_per_d[d][mcs]
                    for mcs in mcs_dist_per_d[d]:
                        tripa.append(mcs_dist_per_d[d][mcs]/total_freq)
                        tripa_err.append(mcs_dist_per_d_error[d][mcs]/total_freq)
                    label = "%d km" % d
                    axis[i].bar(x=list(range(1, 29)), height=tripa, yerr=tripa_err, label=label)
                    axis[i].set_ylim((0, 1.01))
                    axis[i].set_xlim((0, 28))
                    if i == 3:
                        axis[i].set_ylabel("Distribution of MCSs")
                    axis[i].set_xticks(list(range(1, 29, 2)))
                    axis[i].legend(loc='upper left')
                    i += 1
                plt.xlabel("MCS")
                plt.savefig("mcs_%s.png" % lab)

            del lab, tripa, tripa_err, total_freq, mcs, d, mcs_dist_per_d, mcs_dist_per_d_error, fig, axis

            # Plot field trial results
            #for channel_model in channel_models:
            #    corrupted_freq_per_d = {}
            #    received_throughput_per_d = {}
#
            #    for distance in distances:
            #        if distance not in fieldTrialResults["LOS" if channel_model == "CDL_D" else "NLOS"]:
            #            received_throughput_per_d[distance] = 0
            #            corrupted_freq_per_d[distance] = 0
            #            continue
#
            #        # Get trial parameters and forward to simulation
            #        sample = fieldTrialResults["LOS" if channel_model == "CDL_D" else "NLOS"][distance]
            #        received_throughput_per_d[distance] = sample["thr_Mbps"]
            #        corrupted_freq_per_d[distance] = sample["ber"]*100  # convert to tbler? how?
#
            #    lab = "%s Field trial" % channel_model.replace('_', ' ')
            #    plot_dataset["THR"][lab] = list(received_throughput_per_d.values())
            #    error_dataset["THR"][lab] = [0]*len(distances)
#
            #    plot_dataset["TBLER"][lab] = list(corrupted_freq_per_d.values())
            #    error_dataset["TBLER"][lab] = [0]*len(distances)
            #    #axis5[0].bar(list(corrupted_freq_per_d.keys()), list(corrupted_freq_per_d.values()), label=("Field trial %s" % channel_model), color=randcolor())
            #    #axis6[0].bar(list(received_throughput_per_d.keys()), list(received_throughput_per_d.values()), label=("Field trial %s" % channel_model), color=randcolor())
            #    del lab, sample, received_throughput_per_d, corrupted_freq_per_d

            tbler = OrderedDict()
            for key in sorted(plot_dataset["TBLER"], key=lambda x: x[1]+x[-4:]):
                tbler[key] = plot_dataset["TBLER"][key]
            del plot_dataset["TBLER"]

            for i in range(0, 4, 2):
                key_i = list(tbler.keys())[i]
                key_ipp = list(tbler.keys())[i+1]
                for j in range(len(tbler[key_i])):
                    tbler[key_i][j] = 0 if tbler[key_ipp][j] == 0 else tbler[key_i][j]
                    error_dataset["TBLER"][key_i][j] = 0 if tbler[key_i][j] == 0 else error_dataset["TBLER"][key_i][j]

            pandas.DataFrame(tbler, index=distances).plot(kind='bar', yerr=error_dataset["TBLER"], ax=axis5[-1])

            #patches = axis5[-1].patches
            #x_list = distances*4
            #j = 0
            #for i in axis5[-1].patches:
            #    # get_x pulls left or right; get_height pushes up or down
            #    x = x_list.pop(0)
            #    asterisk = False
            #    notMeasured = False
            #    list_labels =list(tbler.keys())
            #    key = j//5
            #    try:
            #        mcs = fieldTrialResults["LOS" if list_labels[key][:5] == "CDL D" else "NLOS"][x]
            #    except:
            #        mcs = fieldTrialResults["LOS" if list_labels[key][:5] != "CDL D" else "NLOS"][x]
            #        asterisk = True
            #        if "trial" in list_labels[key]:
            #            notMeasured = True
            #        pass
            #    if not notMeasured:
            #        label = "MCS %d %s" % (mcs['nearest_mcs_to_simulate']+1, "*" if asterisk else "")
            #    else:
            #        label = "Not measured"
            #    axis5[-1].text(i.get_x()+0.02, 1, label, fontsize=12, color='black', rotation=90)

            #    j += 1
            #axis5[-1].text(0.0, 0.00, "*: MCS values were taken from field trial samples with same distance but different LOS conditions",
            #               ha="center", fontsize=7, bbox={"facecolor": "white", "alpha": 0.5, "pad": 5})

            # Set axis labels for corruption rate plot
            axis5[-1].set_yticks(list(range(0, 101, 10)))
            axis5[-1].set_xlabel("Distance (km)")
            axis5[-1].set_ylabel("Transport Block Error Rate - TBLER (%)")
            axis5[-1].set_ylim([0,100])
            axis5[-1].legend(bbox_to_anchor=(0, -0.2, 1, 0.2), loc="lower left",
                             mode="expand", ncol=4, borderaxespad=0, columnspacing=4.0, fontsize=10)

            # Save results to output files for corruption rate
            fig5.savefig("corruption_rate.png", bbox_inches='tight', dpi=300)

            thr = OrderedDict()

            for key in sorted(plot_dataset["THR"], key=lambda x: x[1]+x[-4:]):
                thr[key] = plot_dataset["THR"][key]
            del plot_dataset["THR"]

            for i in range(0, 4, 2):
                key_i = list(thr.keys())[i]
                key_ipp = list(thr.keys())[i+1]
                for j in range(len(thr[key_i])):
                    thr[key_i][j] = 0 if thr[key_ipp][j] == 0 else thr[key_i][j]
                    error_dataset["THR"][key_i][j] = 0 if thr[key_i][j] == 0 else error_dataset["THR"][key_i][j]
            pandas.DataFrame(thr, index=distances).plot(kind='bar', yerr=error_dataset["THR"], ax=axis6[-1])

            patches = axis6[-1].patches
            x_list = distances*4
            notMeasured = False

            #j = 0
            #for i in axis6[-1].patches:
            #    # get_x pulls left or right; get_height pushes up or down
            #    x = x_list.pop(0)
            #    asterisk = False
            #    notMeasured = False
            #    list_labels =list(tbler.keys())
            #    key = j//5
            #    try:
            #        mcs = fieldTrialResults["LOS" if list_labels[key][:5] == "CDL D" else "NLOS"][x]
            #    except:
            #        mcs = fieldTrialResults["LOS" if list_labels[key][:5] != "CDL D" else "NLOS"][x]
            #        asterisk = True
            #        if "trial" in list_labels[key]:
            #            notMeasured = True
            #        pass
            #    if not notMeasured:
            #        label = "MCS %d %s" % (mcs['nearest_mcs_to_simulate']+1, "*" if asterisk else "")
            #    else:
            #        label = "Not measured"
            #    axis6[-1].text(i.get_x()+0.02, 1, label, fontsize=12, color='black', rotation=90)
            #    j += 1
            axis6[-1].set_yticks(list(range(0, 170, 10)))
            #axis6[-1].text(0.0, -1.50, "*: MCS values were taken from field trial samples with same distance but different LOS conditions",
            #               ha="center", fontsize=7, bbox={"facecolor": "white", "alpha": 0.5, "pad": 5})
            # Set axis labels for corruption rate plot
            axis6[-1].set_xlabel("Distance (km)")
            axis6[-1].set_ylabel("Received Throughput (Mbps)")
            axis6[-1].legend(bbox_to_anchor=(0, -0.2, 1, 0.2), loc="lower left",
                             mode="expand", ncol=4, borderaxespad=0, fontsize=10)

            # Save results to output files for corruption rate
            fig6.savefig("throughput.png", bbox_inches='tight', dpi=300)

        pass
    # end main
    pass
