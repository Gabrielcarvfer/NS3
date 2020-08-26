import re


def plot_mcs_dist(ds=(1, 10, 20, 35, 50,),
                  base_dir="../../build/bin/",
                  cmd=False
                  ):
    mcs_freq_per_d = {}
    for d in ds:
        mcs_freq_per_d[d] = {"mcs": {}}

        contents = None
        with open(base_dir + "out%dkm.txt" % d, "r") as file:
            contents = file.readlines()
        del file

        mcs_regex = re.compile(".*MCS (.*) TBLER .*")
        mcs = None
        for line in contents:
            regex = mcs_regex.match(line)
            if regex is None:
                continue
            mcs = regex.groups()[0]
            mcs = int(mcs)
            try:
                mcs_freq_per_d[d]["mcs"][mcs] += 1
            except KeyError:
                mcs_freq_per_d[d]["mcs"][mcs] = 1
        del regex, mcs, line, contents

    del d, mcs_regex
    import random
    import matplotlib.pyplot as plt
    fig, axis = plt.subplots(ncols=1, nrows=len(mcs_freq_per_d))
    if len(ds) == 1:
        axis = [axis]

    i = 0
    for d in mcs_freq_per_d:
        tripa = []
        for mcs in mcs_freq_per_d[d]["mcs"]:
            tripa.extend([mcs]*mcs_freq_per_d[d]["mcs"][mcs])
        axis[i].hist(tripa, bins=27, density=True, label=("%dkm" % d), color=(random.random(), random.random(), random.random()))

        axis[i].set_xlim((0, 26))
        axis[i].set_xticks(list(range(0, 27)))
        axis[i].legend()
        i += 1

    plt.xlabel("MCS")
    if not cmd:
        plt.show()
    plt.savefig(base_dir+"mcs.png")


if __name__ == '__main__':
    plot_mcs_dist()
