import csv
import json
import os
from collections import OrderedDict
print(os.getcwd())
csv_contents = []
keys = []


#Identify BOM
withBOM = False
with open("./TBS_MCS.csv", "r", encoding="utf-8") as f:
    firstLine = f.readline()
    withBOM = firstLine[0] == '\ufeff'
del firstLine

#Read tuples from CSV
with open("./TBS_MCS.csv", "r", encoding="utf-8-sig" if withBOM else "utf-8") as f:
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

json_contents = {"numerology": {}}
for numerology_int in range(6):
    json_contents["numerology"][numerology_int] = {"MCS": {}}
    for mcs_int in range(16):
        json_contents["numerology"][numerology_int]["MCS"][mcs_int] = {"code rate": 0, "bits/symbol": 0, "TBS": 0, "beta": 0, "#RBs": {}}
del mcs_int, numerology_int

#Update tree with values from the CSV
for entry in csv_contents:
    #Skip empty entries
    if (len(entry["TBS"]) == 0):
        continue
    tbs             = int(entry["TBS"])
    mcs             = int(entry["MCS"])
    numerology_char = entry["num"]
    code_rate_char  = entry["code rate"]
    bits_per_symbol = float(entry["bits/symbol"])
    beta_miesm      = float(entry["beta"]) if len(entry["beta"]) > 0 else 0.0

    for numerology_int in numerology_map[numerology_char]:
        json_contents["numerology"][numerology_int]["MCS"][mcs]["code rate"]   = code_rate_map[code_rate_char]
        json_contents["numerology"][numerology_int]["MCS"][mcs]["bits/symbol"] = bits_per_symbol
        json_contents["numerology"][numerology_int]["MCS"][mcs]["TBS"]         = tbs
        json_contents["numerology"][numerology_int]["MCS"][mcs]["beta"]        = beta_miesm
        for rb_int in range(1, 133):
            rb_str = str(rb_int)
            json_contents["numerology"][numerology_int]["MCS"][mcs]["#RBs"][rb_int] = float(entry[rb_str])
    pass

#Dump json file
with open("./TBS_MCS.json", "w") as f:
    json.dump(json_contents, f, indent=2)
print()
