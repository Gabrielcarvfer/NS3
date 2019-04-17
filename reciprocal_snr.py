#I had a suspicion the probability curves were inverted (main signal being the PU, and not RANGE transmissions)
# so I decided to calculate the reciprocal it to get the "proper" SNR values

# SNR (dB) = 10 log10(Spu/Srange)
# 10^[1/(SNR/10)] = 1/(Spu/Srange) = Srange/Spu
# inverted SNR (dB) = 10 log10 (Srange/Spu)


import json
import math
import os

cwd = os.getcwd()
probability_file = "/src/lte/model/BLER/oulu_pu_probability.json"
file_contents = {}
with open(cwd+probability_file,"r") as file:
    file_contents = json.load(file)

reciprocalSNRs = []
for snr in file_contents["SNR_vs_Pb_tables"]["fig30wiba384"]["SNR_dB"]:
    reciprocalSNR = snr/10.0
    reciprocalSNR = 1/reciprocalSNR
    reciprocalSNR = math.pow(10.0, reciprocalSNR)
    reciprocalSNR = 10.0*math.log10(reciprocalSNR)
    reciprocalSNRs += [reciprocalSNR]

file_contents["SNR_vs_Pb_tables"]["fig30wiba384i"] = {}
file_contents["SNR_vs_Pb_tables"]["fig30wiba384i"]["SNR_dB"] = sorted(reciprocalSNRs)
file_contents["SNR_vs_Pb_tables"]["fig30wiba384i"]["Pd"] = file_contents["SNR_vs_Pb_tables"]["fig30wiba384"]["Pd"]
file_contents["SNR_vs_Pb_tables"]["fig30wiba384i"]["Pfa"]    = file_contents["SNR_vs_Pb_tables"]["fig30wiba384"]["Pfa"]

with open(cwd+probability_file, "w") as file:
    file.write(json.dumps(file_contents, indent=4))

#print(reciprocalSNRs)
