import os
cqi_trace_file = []

dir = "../../build/bin/"
tracefile = "CQI_trace.txt"
tracejson = "CQI_trace.json"

CQI_n_MCS_per_rb_per_ue = None


if not os.path.exists(dir+tracejson):
    if not os.path.exists(dir+tracefile):
        exit(-1)

    with open(dir+tracefile, "r") as f:
        cqi_trace_file = f.readlines()

    del f

    CQI_n_MCS_per_rb_per_ue = {"ues": {}}
    for line in cqi_trace_file:
        ue, _, rbId, _, mcs, _, cqi = line.replace("->", " ").split()

        if rbId not in ["0", "10", "16", "20", "30", "40", "60", "80", "86", "90"]:
            continue

        if ue not in CQI_n_MCS_per_rb_per_ue["ues"]:
            CQI_n_MCS_per_rb_per_ue["ues"][ue] = {"rbId": {}}

        if rbId not in CQI_n_MCS_per_rb_per_ue["ues"][ue]["rbId"]:
            CQI_n_MCS_per_rb_per_ue["ues"][ue]["rbId"][rbId] = {"MCS": [], "CQI": []}

        CQI_n_MCS_per_rb_per_ue["ues"][ue]["rbId"][rbId]["MCS"].append(mcs)
        CQI_n_MCS_per_rb_per_ue["ues"][ue]["rbId"][rbId]["CQI"].append(cqi)

    with open(dir+tracejson, "w") as f:
        import json
        json.dump(CQI_n_MCS_per_rb_per_ue, f)

else:
    with open(dir+tracejson, "r") as f:
        import json
        CQI_n_MCS_per_rb_per_ue = json.load(f)


import matplotlib.pyplot as plt
plt.ion()

fig, axis = plt.subplots(1, 4, sharey=True)
i=0
for rbId in ["16", "40", "60", "86"]:
    for ue in CQI_n_MCS_per_rb_per_ue["ues"]:
        axis[i].plot(list(range(len(CQI_n_MCS_per_rb_per_ue["ues"][ue]["rbId"][rbId]["CQI"]))), [int(x) for x in CQI_n_MCS_per_rb_per_ue["ues"][ue]["rbId"][rbId]["CQI"]], label="CQI RB=%s UE=%s" % (rbId, ue))
    #plt.legend()
    axis[i].set_ylim([-1, 16])
    i += 1
plt.show()
input()
pass