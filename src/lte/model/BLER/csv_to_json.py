import csv
import json

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
