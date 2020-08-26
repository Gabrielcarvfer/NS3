import re
import random


def plot_snr_hist(axis, snr_freq_per_d):
    i = 0
    for d in snr_freq_per_d:
        tripa = []
        for mcs in snr_freq_per_d[d]["snr"]:
            tripa.extend([mcs] * snr_freq_per_d[d]["snr"][mcs])
        axis[i].hist(tripa, bins=27, density=True, label=("%dkm" % d),
                     color=(random.random(), random.random(), random.random()))
        axis[i].legend()
        axis[i].set_xlim((-50.0, 150.0))
        i += 1


def plot_snr_dist(ds=(1, 10, 20, 35, 50,),
                  base_dir="../../build/bin/",
                  cmd=False
                  ):
    snr_freq_per_d = {}
    for d in ds:
        snr_freq_per_d[d] = {"snr": {}}

        contents = None
        with open(base_dir + "out%dkm.txt" % d, "r") as file:
            contents = file.readlines()
        del file

        snr_regex = re.compile("snr (.*[^\n])")
        snr = None
        for line in contents:
            regex = snr_regex.match(line)
            if regex is None:
                continue
            snr = regex.groups()[0]
            snr = float(snr)
            try:
                snr_freq_per_d[d]["snr"][snr] += 1
            except KeyError:
                snr_freq_per_d[d]["snr"][snr] = 1
        del regex, snr, line, contents

    del d, snr_regex
    import matplotlib.pyplot as plt
    fig, axis = plt.subplots(nrows=len(snr_freq_per_d))
    if len(ds) == 1:
        axis = [axis]

    plot_snr_hist(axis, snr_freq_per_d)

    plt.xlabel("SINR")
    if not cmd:
        plt.show()
    plt.savefig(base_dir+"sinr.png")

    # Return results for aggregation
    return snr_freq_per_d

if __name__ == '__main__':
    plot_snr_dist()
