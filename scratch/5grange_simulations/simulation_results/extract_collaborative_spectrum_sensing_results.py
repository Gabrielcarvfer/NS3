import re
import os


def extract_collaborative_spectrum_sensing_results(path_to_simulation_folder):
    regex_bits_per_ue = "of (.*?) bits"
    regex_bits_per_ue_c = re.compile(regex_bits_per_ue)
    regex_raw = "From (.*) fusions, (.*) were false positive and (.*) were false negative"
    regex_raw_c = re.compile(regex_raw)
    regex_false = ".* of (.*) subframes"
    regex_false_c = re.compile(regex_false)

    sensingListFile = path_to_simulation_folder + os.sep + "sensing_list.txt"

    if os.path.exists(sensingListFile):
        lines = []
        with open(sensingListFile, "r") as f:
            lines = f.readlines()
            lines = lines[2:]  # Skip first two lines

        result_dict = {"channel": {}}
        for channel in range(4):
            channel_lines = lines[:4]
            lines = lines[4:]

            # Extract numbers from e.g. From 9976 fusions, 89 were false positive and 1360 were false negative.
            ans = regex_bits_per_ue_c.search(channel_lines[0]).groups()
            avg_bits_per_ue = float(ans[0])
            ans = regex_raw_c.search(channel_lines[1]).groups()
            fusions, false_positives, false_negatives = int(ans[0]), int(ans[1]), int(ans[2])
            frames_that_could_be_false_positives = int(regex_false_c.search(channel_lines[2]).groups()[0])
            frames_that_could_be_false_negatives = int(regex_false_c.search(channel_lines[3]).groups()[0])

            channel_results = {
                "avg_bits_per_ue"       : avg_bits_per_ue,
                "total_fusions"         : fusions,
                "total_false_positives" : false_positives,
                "total_false_negatives" : false_negatives,
                "frames_pu_was_inactive": frames_that_could_be_false_positives,
                "frames_pu_was_active"  : frames_that_could_be_false_negatives
            }
            result_dict["channel"][channel] = channel_results
            lines = lines[1:]  # Skip empty line between channels
        return result_dict

    raise Exception("sensing_lists.txt file doesn't exist")
