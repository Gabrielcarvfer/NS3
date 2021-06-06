import subprocess
import os
import numpy as np
from concurrent.futures.process import ProcessPoolExecutor
from extract_network_performance_metrics import extract_network_performance_metrics

y = z = 50 * 1000
caseRange = [0, 1]  # udp, tcp
pkt_size = 100
rangeUes = list(range(2, 51, 10))
rangeDistance = [1, 10, 25, 35, 50]
rangeInterval = [1 / frequency for frequency in (1, 10, 50, 100, 200, 500, 1000)]
executor = ProcessPoolExecutor(max_workers=15)
base_dir = "/mnt/dev/tools/source/NS3/build/bin"


def mkdir(path):
    if not os.path.exists(path):
        os.mkdir(path)
    return path


def exec_simulation_n_extract_flowmonitor_data(path, nUes, x, y, z, tcp, interval, pkt_size):
    x *= 1000
    args = "--nUes=%d --x=%d --y=%d --z=%d --tcp=%d --pkt_size=%d --interval=%.6f " % (
    nUes, x, y, z, tcp, pkt_size, interval,)
    if not os.path.exists(path + os.sep + "flow.xml"):
        try:
            if os.sep == "\\":
                cmd = "bash -c "
                cmd += "\""
                cmd += base_dir + os.sep + "5grange_application_test"
                cmd += "\""
                cmd += args
            else:
                cmd = [base_dir + os.sep + "5grange_application_test"]
                cmd.extend(args.split(' '))
                cmd = cmd[:-1]

            simProc = subprocess.run(cmd,
                                     stdout=subprocess.PIPE,
                                     stderr=subprocess.STDOUT,
                                     cwd=path,
                                     env={"OPENBLAS_NUM_THREADS": "1",
                                          },
                                     timeout=8000
                                     )
            if simProc.returncode != 0:
                raise Exception("ProgramFailed")

        except Exception:
            print("Failed to execute simulation. Source path: ",
                  path)
    return extract_network_performance_metrics(path)


outputFolder = mkdir(base_dir + "/output")
simulation_results = {}
for simulationCase in caseRange:
    simCaseFolder = mkdir(outputFolder + "/tcp_%d" % simulationCase)
    for nUes in rangeUes:
        nUesFolder = mkdir(simCaseFolder + "/nUes_%d" % nUes)
        for distance in rangeDistance:
            distanceFolder = mkdir(nUesFolder + "/km_%d" % distance)
            for interval in rangeInterval:
                intervalFolder = mkdir(distanceFolder + "/interval_%.6f" % interval)

                simulation_results[intervalFolder] = executor.submit(exec_simulation_n_extract_flowmonitor_data,
                                                                     intervalFolder,
                                                                     nUes, 50 - distance, y, z, simulationCase, interval, pkt_size)

for simulation in simulation_results:
    simulation_results[simulation] = simulation_results[simulation].result()


def extract_results():
    results = {"tcp": {False: {}, True: {}}}
    for case in caseRange:
        results["tcp"][bool(case)] = {"nUes": {}}
        simCaseFolder = outputFolder + "/tcp_%d" % case
        for nUes in rangeUes:
            results["tcp"][bool(case)]["nUes"][nUes] = {"distance": {}}
            nUesFolder = simCaseFolder + "/nUes_%d" % nUes

            for distance in rangeDistance:
                results["tcp"][bool(case)]["nUes"][nUes]["distance"][distance] = {"interval": {}}
                distanceFolder = nUesFolder + "/km_%d" % distance
                for interval in rangeInterval:
                    results["tcp"][bool(case)]["nUes"][nUes]["distance"][distance]["interval"][interval] = {"throughputrx": 0, "throughputtx": 0, "delay": 0, "lost_packets": 0}

                    result_path = distanceFolder + "/interval_%.6f" % interval
                    appPort = 8000

                    throughput_intervaltx = []
                    throughput_intervalrx = []
                    lost_packets_interval = []
                    delay_interval = []
                    for flow in simulation_results[result_path]['applicationPort'][appPort]['flows'].values():
                        difftime = (float(flow['status']['@timeLastTxPacket'][:-2]) - float(
                            flow['status']['@timeFirstTxPacket'][:-2])) / (10 ** 9)
                        throughputtx = int(flow['status']['@txBytes']) / difftime
                        throughputrx = int(flow['status']['@rxBytes']) / difftime
                        lost_packets = 100*(1-int(flow['status']['@rxPackets'])/int(flow['status']['@txPackets']))

                        delay_list = []
                        for (delay_sample, num_samples) in flow['status']['delayHistogram'].items():
                            delay_list.extend([delay_sample]*num_samples)

                        delay = 0
                        if len(delay_list) > 0:
                            delay = np.average(delay_list)
                            delayDev = np.std(delay_list)
                        throughput_intervaltx.append(throughputtx)
                        throughput_intervalrx.append(throughputrx)
                        lost_packets_interval.append(lost_packets)
                        delay_interval.append(delay)

                    results["tcp"][bool(case)]["nUes"][nUes]["distance"][distance]["interval"][interval]["throughputtx"] = sum(throughput_intervaltx)
                    results["tcp"][bool(case)]["nUes"][nUes]["distance"][distance]["interval"][interval]["throughputrx"] = sum(throughput_intervalrx)
                    results["tcp"][bool(case)]["nUes"][nUes]["distance"][distance]["interval"][interval]["lost_packets"] = np.average(lost_packets_interval)
                    if len(delay_interval) > 0:
                        results["tcp"][bool(case)]["nUes"][nUes]["distance"][distance]["interval"][interval]["delay"] = np.average(delay_interval)
                    del throughput_intervaltx
                    del throughput_intervalrx
                    del lost_packets_interval
                    del delay_interval
    return results


result = extract_results()

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
import numpy as np

for nUes in rangeUes:

    X = rangeDistance
    Y = rangeInterval[1:]
    X, Y = np.meshgrid(X, Y)
    for case in caseRange:
        fig = plt.figure()
        axthrtx = fig.add_subplot(1, 4, 1, projection='3d')
        axthrrx = fig.add_subplot(1, 4, 2, projection='3d')
        axisdel = fig.add_subplot(1, 4, 3, projection='3d')
        axislos = fig.add_subplot(1, 4, 4, projection='3d')

        Z1 = []
        Z2 = []
        Z3 = []
        Z4 = []
        for interval in rangeInterval[1:]:
            Z1_temp = []
            Z2_temp = []
            Z3_temp = []
            Z4_temp = []
            for distance in rangeDistance:
                Z1_temp.append(result["tcp"][bool(case)]["nUes"][nUes]["distance"][distance]["interval"][interval]["throughputtx"]*8/1000)
                Z2_temp.append(result["tcp"][bool(case)]["nUes"][nUes]["distance"][distance]["interval"][interval]["throughputrx"]*8/1000)
                Z3_temp.append(result["tcp"][bool(case)]["nUes"][nUes]["distance"][distance]["interval"][interval]["delay"])
                Z4_temp.append(result["tcp"][bool(case)]["nUes"][nUes]["distance"][distance]["interval"][interval]["lost_packets"])


            Z1.append(Z1_temp)
            Z2.append(Z2_temp)
            Z3.append(Z3_temp)
            Z4.append(Z4_temp)
            del Z1_temp
            del Z2_temp
            del Z3_temp
            del Z4_temp

        axthrtx.scatter(X, Y, np.array(Z1), cmap=cm.viridis)
        axthrrx.scatter(X, Y, np.array(Z2), cmap=cm.viridis)
        axisdel.scatter(X, Y, np.array(Z3), cmap=cm.viridis)
        axislos.scatter(X, Y, np.array(Z4), cmap=cm.viridis)

        axthrtx.set_xlabel("Distance (km)")
        axthrtx.set_ylabel("Interval between packets (s)")
        axthrtx.set_zlabel("Throughput TX (kbps)")
        #axthrtx.set_yscale("logit")

        axthrrx.set_xlabel("Distance (km)")
        axthrrx.set_ylabel("Interval between packets (s)")
        axthrrx.set_zlabel("Throughput RX (kbps)")
        axthrrx.set_title("%d UEs running a %s application with %dB packets" % (nUes, "TCP" if bool(case) else "UDP", pkt_size,))
        #axthrrx.set_yscale("logit")

        axisdel.set_xlabel("Distance (km)")
        axisdel.set_ylabel("Interval between packets (s)")
        axisdel.set_zlabel("Delay (s)")
        axisdel.set_zscale("log")
        axisdel.set_zlim([0.0010, 0.1])

        #axdel.set_title("%d UEs running a %s application with %dB packets" % (nUes, "TCP" if bool(case) else "UDP", pkt_size,))

        axislos.set_xlabel("Distance (km)")
        axislos.set_ylabel("Interval between packets (s)")
        axislos.set_zlabel("Lost Packets (%)")
        #axislos.set_yscale("logit")

        #axlos.set_title("%d UEs running a %s application with %dB packets" % (nUes, "TCP" if bool(case) else "UDP", pkt_size,))
        plt.show()
        print()

    print()
