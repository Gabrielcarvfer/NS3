import os
import xmltodict
from enum import Enum
import sys

# Taken from 5g_range_demonstration_json.cc
class ApplicationPorts(Enum):
    voipListenPort      = 8000,
    videoconfListenPort = 8001,
    webListenPort       = 8002,
    streamingListenPort = 8003,
    backhaulListenPort  = 8004,
    iotListenPort       = 8005,

# Taken from D6.3 and previous 5G-RANGE deliverables
application_KPIs = {ApplicationPorts.voipListenPort.value[0]: {"lost_packet_ratio": 0.1,
                                                      "latency": 0.1,
                                                      "jitter": 0.4,
                                                      "dl_throughput_kbps": 500,
                                                      "ul_throughput_kbps": 500},
                    ApplicationPorts.videoconfListenPort.value[0]: {"lost_packet_ratio": 0.01,
                                                           "latency": 0.1,
                                                           "jitter": sys.float_info.max,
                                                           "dl_throughput_kbps": 3000,
                                                           "ul_throughput_kbps": 3000},
                    ApplicationPorts.webListenPort.value[0]: {"lost_packet_ratio": 0.1,
                                                     "latency": 0.1,
                                                     "jitter": 0.1,
                                                     "dl_throughput_kbps": 500,
                                                     "ul_throughput_kbps": 500},
                    ApplicationPorts.streamingListenPort.value[0]: {"lost_packet_ratio": 0,
                                                           "latency": sys.float_info.max,
                                                           "jitter": sys.float_info.max,
                                                           "dl_throughput_kbps": 9000,
                                                           "ul_throughput_kbps":  900},
                    ApplicationPorts.iotListenPort.value[0]: {"lost_packet_ratio": 0.001,
                                                     "latency": 0.05,
                                                     "jitter": sys.float_info.max,
                                                     "dl_throughput_kbps": 500,
                                                     "ul_throughput_kbps": 500},
                    ApplicationPorts.backhaulListenPort.value[0]: {"lost_packet_ratio": 0.005,
                                                          "latency": sys.float_info.max,
                                                          "jitter": sys.float_info.max,
                                                          "dl_throughput_kbps": 100000,  # 50km CDL D/LOS
                                                          "ul_throughput_kbps":  25000},
                    }

def extract_network_performance_metrics(path_to_simulation_folder):
    flow_monitor_contents = None
    # Load XML output from ns-3 flowmonitor
    with open(path_to_simulation_folder+os.sep+'flow.xml', "r") as file:
        flow_monitor_contents = xmltodict.parse(file.read())

    # Identify and group flows with known applications
    application_flows = {"applicationPort": {}}
    for application in list(ApplicationPorts):
        application_flows["applicationPort"][application.value[0]] = {"applicationName": application.name[:-10],
                                                                      "flows": {}}
    flow_port_map = {}
    for flow in flow_monitor_contents['FlowMonitor']['Ipv4FlowClassifier']['Flow']:
        source_port = int(flow["@sourcePort"])
        dest_port = int(flow["@destinationPort"])
        if source_port in application_flows["applicationPort"].keys():
            known_port = source_port
        else:
            known_port = dest_port

        flow_id = int(flow["@flowId"])
        try:
            application_flows["applicationPort"][known_port]["flows"][flow_id] = {"metadata": flow}
            flow_port_map[flow_id] = known_port
        except KeyError:
            pass  # ignore traffics that are not coming from or being sent to an UE
        pass

    # Then collect their statistics
    for flow in flow_monitor_contents['FlowMonitor']['FlowStats']['Flow']:
        flow_id = int(flow["@flowId"])
        if flow_id not in flow_port_map:
            continue
        application_flows["applicationPort"][flow_port_map[flow_id]]["flows"][flow_id]["status"] = flow
        pass

    return application_flows


if __name__ == "__main__":
    test_results = extract_network_performance_metrics(os.path.abspath("./"))
    print()
    pass
