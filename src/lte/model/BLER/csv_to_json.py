import csv
import json

beta_data = {"channel": {}}
with open('beta_values.csv', 'r') as f:
    reader = csv.DictReader(f)

    for entry in reader:
        numerology = entry["numerology"]
        speed = entry["speed"]
        block_size = entry["block size"]
        mcs = entry['mcs']
        channel = entry['channel']
        beta = entry['beta']

        if channel not in beta_data['channel']:
            beta_data['channel'][channel] = {'numerology': {}}
        if numerology not in beta_data['channel'][channel]['numerology']:
            beta_data['channel'][channel]['numerology'][numerology] = {'block_size': {}}
        if block_size not in beta_data['channel'][channel]['numerology'][numerology]['block_size']:
            beta_data['channel'][channel]['numerology'][numerology]['block_size'][block_size] = {'MCS': {}}
        if mcs not in beta_data['channel'][channel]['numerology'][numerology]['block_size'][block_size]['MCS']:
            beta_data['channel'][channel]['numerology'][numerology]['block_size'][block_size]['MCS'][mcs] = {'speed': {}}
        if speed not in beta_data['channel'][channel]['numerology'][numerology]['block_size'][block_size]['MCS'][mcs]['speed']:
            beta_data['channel'][channel]['numerology'][numerology]['block_size'][block_size]['MCS'][mcs]['speed'][speed] = 0
        beta_data['channel'][channel]['numerology'][numerology]['block_size'][block_size]['MCS'][mcs]['speed'][speed] = beta

with open("beta_values.json", "w") as f:
    json.dump(beta_data, f, indent=3)


tbs_data = {'MCS': {}}
with open('TBSs - Sheet3.csv', 'r') as f:
    reader = csv.DictReader(f)

    for entry in reader:
        num = entry['Numerology']
        mcs = entry['MCS']
        tbs = entry['TBS']
        mcs = "%d" % (int(mcs)-1)  # start from 0
        if mcs not in tbs_data['MCS']:
            tbs_data['MCS'][mcs] = {'#RBs': {}}
        if '1' not in tbs_data['MCS'][mcs]['#RBs']:
            tbs_data['MCS'][mcs]['#RBs']['1'] = {'NUMEROLOGY': {}}
        if num not in tbs_data['MCS'][mcs]['#RBs']['1']["NUMEROLOGY"]:
            tbs_data['MCS'][mcs]['#RBs']['1']['NUMEROLOGY'][num] = float(entry['1'])
        pass
    del num, mcs, tbs, reader

print()

with open("TBS_MCS.json", "w") as f:
    json.dump({"TBS": tbs_data}, f, indent=3)

