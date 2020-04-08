import csv
import json
import os
from collections import OrderedDict
print(os.getcwd())
csv_contents = []
keys = []

#Read tuples from CSV
with open("./TBS_MCS.csv", "r", encoding="utf-8") as f:
    reader = csv.DictReader(f)
    for row in reader:
        csv_contents += [row]
    keys = row.keys()
del row, reader, f

#Build JSON tree
json_contents = {"TBS": {}}
numerology_map = OrderedDict({"A": [0],
                              "B": [1, 2, 3, 4],
                              "C": [5]
                              })

code_rate_map = OrderedDict({"1/3": 1/3,
                             "1/2": 1/2,
                             "2/3": 2/3,
                             "3/4": 3/4,
                             "5/6": 5/6,
                             "7/8": 7/8
                             })

for tbs_int in range(48):
    json_contents["TBS"][tbs_int] = {"MCS": {}}
    for mcs_int in range(16):
        json_contents["TBS"][tbs_int]["MCS"][mcs_int] = {"code rate": 0, "bits/symbol": 0, "numerology": {}}
        for numerology_int in range(6):
            json_contents["TBS"][tbs_int]["MCS"][mcs_int]["numerology"][numerology_int] = {"#RBs": {}}
            for num_rbs in range(1, 133):
                json_contents["TBS"][tbs_int]["MCS"][mcs_int]["numerology"][numerology_int]["#RBs"][num_rbs] = 0
del tbs_int, mcs_int, numerology_int, num_rbs

#Update tree with values from the CSV
for entry in csv_contents:
    tbs             = int(entry["TBS"])
    mcs             = int(entry["MCS"])
    numerology_char = entry["num"]
    code_rate_char  = entry["code rate"]
    bits_per_symbol = float(entry["bits/symbol"])

    json_contents["TBS"][tbs]["MCS"][mcs]["code rate"] = code_rate_map[code_rate_char]
    json_contents["TBS"][tbs]["MCS"][mcs]["bits/symbol"] = bits_per_symbol
    for numerology_int in numerology_map[numerology_char]:
        for rb_int in range(1, 133):
            json_contents["TBS"][tbs]["MCS"][mcs]["numerology"][numerology_int]["#RBs"][rb_int] = entry[str(rb_int)]
    pass

#Dump json file
with open("./TBS_MCS.json", "w") as f:
    json.dump(json_contents, f, indent=4)
print()
