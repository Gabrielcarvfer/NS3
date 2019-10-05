import pyshark
import os
import pickle
import hurst

output_file = "results.pickle"
flows = None
if not os.path.exists(output_file):
    #Mount relative path to notopoloko example build folder

    bin_folder = ".." + os.sep
    bin_folder = bin_folder*4
    bin_folder += os.sep.join(["build", "bin", "contrib", "notopoloko", "examples"])

    #Scan for pcap files there
    files = {}
    for (dirpath, dirnames, filenames) in os.walk(bin_folder):
        #Iterate files while ignoring files without extension or with extensions other than pcap
        for filename in filenames:
            sep = filename.split(".")
            if len(sep) < 2 or sep[1] not in ["pcap"]:
                continue
            #Store relative path to a given file
            files[filename] = True
            pass
        pass

    #Open a pcap
    pcapFile = pyshark.FileCapture(bin_folder+os.sep+list(files.keys())[0], keep_packets=False)

    #Load all packets to a dictionary
    packets = []
    while True:
        try:
            currPacket = pcapFile.next()
        except:
            break
        packets.append(currPacket)

    flows = {}

    #Fetch tcp data if available
    for packet in packets:
        #By skipping packets without TCP layers
        if "tcp" not in [_.layer_name for _ in packet.layers]:
            continue

        #Compute flow tuple
        flow_tuple = (packet.ip.src_host, packet.tcp.srcport, packet.ip.dst_host, packet.tcp.dstport)

        #Check if flow exists
        if flow_tuple not in flows:
            flows[flow_tuple] = {"packets": []}

        #Add packet to flow
        flows[flow_tuple]["packets"] += [packet]

    import statistics

    #Now compute statistics for each flow
    for flow in flows.values():
        packetSizes = []
        windowSizes = []
        seqNumbers  = []
        timestamps  = []
        rtt         = [0]

        #Collect info from all packets from the flow
        prevPacket = None
        for packet in flow["packets"]:
            packetSizes += [int(packet.tcp.len)]
            windowSizes += [int(packet.tcp.window_size)]
            seqNumbers  += [int(packet.tcp.seq)]
            timestamps  += [float(packet.sniff_timestamp)]
            if prevPacket is not None:
                rtt += [float(packet.sniff_timestamp) - float(prevPacket.sniff_timestamp)]
            prevPacket = packet

        #Create fields to store flow related statistics
        flow["numPackets"]      = len(flow["packets"])
        flow["totalBytes"]      = sum(packetSizes)
        flow["avgSizeBytes"]    = flow["totalBytes"]/flow["numPackets"]
        flow["stdDevSizeBytes"] = statistics.stdev(packetSizes)
        flow["avgRtt"]          = sum(rtt)/flow["numPackets"]
        flow["stdDevRtt"]       = statistics.stdev(rtt)
        flow["totalDuration"]   = float(flow["packets"][-1].sniff_timestamp)-float(flow["packets"][0].sniff_timestamp)
        H, c, data = hurst.compute_Hc(timestamps, kind='random_walk', simplified=True)
        flow["hurst"] = (H, c)
        flow["retransmissions"] = 0.0

        #Remove items from memory
        del packetSizes
        del windowSizes
        del seqNumbers
        del timestamps
        del H, c, data
        del prevPacket
        del rtt

    #dump results for later use
    with open(output_file, "wb") as fd:
        pickle.dump(flows, fd) #tuples can't be dumped into json, then use a pickle
        pass

#if output file exists, load results
if flows is None and os.path.exists(output_file):
    with open(output_file, "rb") as fd:
        flows = pickle.load(fd) #tuples can't be dumped into json, then use a pickle
        pass

print("pew pew")