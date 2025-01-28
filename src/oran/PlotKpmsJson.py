import json

kpms_file = "kpms.json"

with open(kpms_file, "r") as f:
    kpms = json.load(f)

from matplotlib import pyplot as plt
fig, axis = plt.subplots(len(kpms), 1, sharex=True, squeeze=False)

for i, kpm in enumerate(kpms):
    axis[i][0].set_ylabel(kpm["KPM"].replace("/KPM/", ""), rotation="horizontal", loc="center", labelpad=60)
    for endpointMeasurements in kpm["DATA"]:
        # Retrieve E2Node endpoint
        endpointLabel = endpointMeasurements["ENDPOINT"]

        # Find unique RNTIs and separate their data
        rntis = set(map(lambda x: x["measurements"]["RNTI"], endpointMeasurements["MEASUREMENTS"]))

        # Filter RNTI data
        for rnti in rntis:
            rnti_data = list(filter(lambda x: x["measurements"]["RNTI"]==rnti, endpointMeasurements["MEASUREMENTS"]))
            rnti_data_x = list(map(lambda x: int(x["timestamp"]), rnti_data))
            rnti_data_y = list(map(lambda x: int(x["measurements"]["VALUE"]), rnti_data))
            axis[i][0].plot(rnti_data_x, rnti_data_y, label=f"{endpointLabel}'s RNTI {rnti}")
plt.legend(bbox_to_anchor=(0.75, -0.4, 0, 0))
plt.tight_layout()
plt.show()
