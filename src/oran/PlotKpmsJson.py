import json
import os
from matplotlib import pyplot as plt

kpms_file = "kpms.json"
currDir = os.path.abspath(os.path.dirname(__file__))

#with open(f"{currDir}/{kpms_file}", "r") as f:
with open(f"{currDir}/../../build/src/oran/examples/{kpms_file}", "r") as f:
    kpms = json.load(f)
    kpms = list(sorted(kpms, key=lambda x: x["KPM"].split(".")[-1]))

fig, axis = plt.subplots(len(kpms), 1, figsize=(6,6), sharex=True, squeeze=False)

suffix_to_axis = {}
for i, kpm in enumerate(kpms):
    kpm_name = kpm["KPM"].replace("/KPM/", "")
    kpm_suffix = kpm_name.split(".")[-1]
    if kpm_suffix not in suffix_to_axis:
        suffix_to_axis[kpm_suffix] = axis[i][0]
    axis[i][0].set_ylabel(kpm_name, rotation="horizontal", loc="center", labelpad=60)
    for endpointMeasurements in kpm["DATA"]:
        # Retrieve E2Node endpoint
        endpointLabel = endpointMeasurements["ENDPOINT"]

        # Find unique RNTIs and separate their data
        rntis = set(map(lambda x: x["measurements"]["RNTI"], endpointMeasurements["MEASUREMENTS"]))

        # Filter RNTI data
        for rnti in rntis:
            rnti_data = list(filter(lambda x: x["measurements"]["RNTI"]==rnti, endpointMeasurements["MEASUREMENTS"]))
            rnti_data_x = list(map(lambda x: int(x["timestamp"])/1e9, rnti_data))
            rnti_data_y = list(map(lambda x: int(x["measurements"]["VALUE"]), rnti_data))
            axis[i][0].plot(rnti_data_x, rnti_data_y, label=f"{endpointLabel}'s RNTI {rnti}")
        axis[i][0].sharey(suffix_to_axis[kpm_suffix])
axis[-1][0].set_xlabel("Tempo de simulação [s]")
#fig.legend(bbox_to_anchor=(0.75, -0.8, 0, 0), ncol=2)
fig.tight_layout()
fig.savefig("kpms.png")
