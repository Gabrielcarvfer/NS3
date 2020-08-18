# To be used with lte-miesm-error-model printing effective SNR of code blocks
import re

ds = [1,50, ]
snr_freq_per_d = {}

for d in ds:
    snr_freq_per_d[d] = {"snr": {}}

    contents = None
    with open("out%dkm_rangeprop2.txt" % d, "r") as file:
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

del d, ds, snr_regex
import random
import matplotlib.pyplot as plt
fig, axis = plt.subplots(ncols=1, nrows=len(snr_freq_per_d))
i = 0
for d in snr_freq_per_d:
    tripa = []
    for mcs in snr_freq_per_d[d]["snr"]:
        tripa.extend([mcs]*snr_freq_per_d[d]["snr"][mcs])
    axis[i].hist(tripa, bins=27, label=("%dkm" % d), color=(random.random(), random.random(), random.random()))
    axis[i].legend()
    axis[i].set_xlim((-50.0, 150.0))
    i += 1
plt.xlabel("SINR")
plt.show()
print()