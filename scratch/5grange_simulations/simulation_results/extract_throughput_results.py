import re


def extract_throughput_results(simulation_path):
    # Open perf.txt and scan for received throughput
    contents = None
    with open(simulation_path + "perf.txt", "r", encoding="utf-8") as file:
        contents = file.readlines()

    phy_dl_received_throughput_regex = re.compile("DL Vazão: (.*)mbps")
    #PHY_DL_injected_throughput_regex = re.compile("Vazão esperada PHY: (.*)mbps")

    regex = None
    throughput = 0.0
    for line in contents:
        regex = phy_dl_received_throughput_regex.match(line)
        if regex is None:
            continue
        throughput = regex.groups()[0]
        throughput = float(throughput)

    return throughput
