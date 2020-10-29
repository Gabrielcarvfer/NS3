import os
import re

class LteSpectrumPhyResults:
    mcs_distribution = None
    sinr_distribution = None
    tbler_results = None
    latest_simulation_path = None

    def __init__(self, simulation_path):
        # Don't reload results if simulation path is the same
        if LteSpectrumPhyResults.latest_simulation_path == simulation_path:
            return

        # Process if path is different
        simulation_std_error_output = simulation_path + os.path + "out.txt.lzma"
        if not os.path.exists(simulation_std_error_output):
            raise Exception("Failed extracting LteSpectrumPhy results. Skipping to the next simulation. Source path:" + simulation_path)

        file_contents = None
        with lzma.open(simulation_std_error_output, "r") as f:
            file_contents.read_lines(f)
        for line in range(len(file_contents)):
            file_contents[line] = file_contents[line].decode("utf-8")

        mcs_regex = re.compile(".*MCS (.*) TBLER .*")
        snr_regex = re.compile("snr (.*[^\n])")
        corrupted_regex = re.compile(".* corrupted (.*).*")

        mcs_freq = {"mcs": {}}
        snr_freq = {"snr": {}}
        mcs = None
        snr = None
        corrupted = 0
        corrupted_TBs = 0
        total_TBs = 0

        for line in file_contents:
            # Try to match mcs regex
            regex = mcs_regex.match(line)
            if regex is not None:
                mcs = regex.groups()[0]
                mcs = int(mcs)
                try:
                    mcs_freq["mcs"][mcs] += 1
                except KeyError:
                    mcs_freq["mcs"][mcs] = 1
                continue

            # Try to match snr regex
            regex = snr_regex.match(line)
            if regex is not None:
                snr = regex.groups()[0]
                snr = float(snr)
                try:
                    snr_freq["snr"][snr] += 1
                except KeyError:
                    snr_freq["snr"][snr] = 1

            # Try to match tbler regex
            regex = corrupted_regex.match(line)
            if regex is not None:
                total_TBs += 1
                corrupted = regex.groups()[0]
                if "snr" in corrupted:
                    continue
                corrupted = int(corrupted)
                corrupted_TBs += corrupted
        corrupted_freq = corrupted_TBs/total_TBs*100 if corrupted_TBs > 0 else 0
        del regex, mcs, snr, line, total_TBs, corrupted, corrupted_TBs, file_contents

        LteSpectrumPhyResults.sinr_distribution = snr_freq
        LteSpectrumPhyResults.mcs_distribution = mcs_freq
        LteSpectrumPhyResults.tbler_results = corrupted_freq

