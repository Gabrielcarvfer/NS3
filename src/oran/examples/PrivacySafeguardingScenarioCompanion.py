import os
import subprocess
import csv

try:
    import xmltodict
except ImportError:
    print(f"{__file__} requires xmltodict. You can install it via pip install xmltodict")

ns3_dir = os.path.abspath(os.path.join(__file__, "../../../../"))
privacy_dir = os.sep.join([ns3_dir, "build", "src", "oran", "examples"])

if not os.path.exists(privacy_dir):
    # build simulation
    subprocess.call(["ns3", "build", "PrivacySafeguardingScenario"], cwd=ns3_dir)
def get_ground_truth_trajectories():
    trajectories = {}
    ground_truth_file = os.path.join(privacy_dir, "tracking.xml")
    with open(ground_truth_file, "r") as f:
        ground_truth = xmltodict.parse(f.read())

        # For each node
        for node in ground_truth["anim"]["node"]:
            nodeId = node["@id"]
            # Get a list of node updates for said node
            node_trajectory = list(filter(lambda x: x["@id"] == nodeId, ground_truth["anim"]["nu"]))
            # Trim updates with no coordinates
            node_trajectory = list(filter(lambda x: "@x" in list(x.keys()), node_trajectory))
            # Replace dict with tuple
            node_trajectory = list(map(lambda x: (x["@x"], x["@y"]), node_trajectory))
            trajectories[int(nodeId)] = node_trajectory
        for key in list(trajectories.keys()):
            if not trajectories[key]:
                del trajectories[key]
    return trajectories

def get_malicious_tracking_trajectories():
    trajectories = {}
    malicious_tracking_file = os.path.join(privacy_dir, "malicious-tracking.csv")
    with open(malicious_tracking_file, "r") as f:
        malicious_tracking = list(csv.DictReader(f))
        nodeIds = list(map(lambda x: x['nodeId'], malicious_tracking))
        nodeIds = list(set(nodeIds))
        for nodeId in nodeIds:
            # Get a list of node updates for said node
            node_trajectory = list(filter(lambda x: x["nodeId"] == nodeId, malicious_tracking))
            # Replace dict with tuple
            node_trajectory = list(map(lambda x: (x["x"], x["y"]), node_trajectory))
            trajectories[int(nodeId)] = node_trajectory
    return trajectories

ground_truth_node_trajectories = get_ground_truth_trajectories()
malicious_node_trajectories = get_malicious_tracking_trajectories()

from matplotlib import pyplot as plt

for key in malicious_node_trajectories:
    truth = ground_truth_node_trajectories[key]
    approx = malicious_node_trajectories[key]
    xt = list(map(lambda z: float(z[0]), truth))
    yt = list(map(lambda z: float(z[1]), truth))
    xa = list(map(lambda z: float(z[0]), approx))
    ya = list(map(lambda z: float(z[1]), approx))
    plt.cla()
    plt.scatter(xt, yt, label=f"truth for node{key}")
    plt.scatter(xa, ya, label=f"approx for node{key}")
    plt.xlim([600, 2500])
    plt.ylim([600, 2500])
    plt.show()

print()
