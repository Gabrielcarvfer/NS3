import os
import xmltodict
from enum import Enum

class ApplicationPorts(Enum):
    UDP  = 8000,
    TCP  = 8001,


def extract_network_performance_metrics(path_to_simulation_folder):
    return extract_network_performance_metrics_impl(path_to_simulation_folder)

def extract_network_performance_metrics_impl(path_to_simulation_folder):
    flow_monitor_contents = None
    # Load XML output from ns-3 flowmonitor
    with open(path_to_simulation_folder+os.sep+'flow.xml', "r") as file:
        flow_monitor_contents = xmltodict.parse(file.read())

    # Identify and group flows with known applications
    application_flows = {"applicationPort": {}}
    for application in list(ApplicationPorts):
        appValue = application.value if type(application.value) == int else application.value[0]
        application_flows["applicationPort"][appValue] = {"applicationName": application.name,
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

    def read_histogram(flow_monitor_histogram):
        histogram = {}
        skip = False
        if 'bin' in flow_monitor_histogram:
            for bin in flow_monitor_histogram['bin']:
                if type(bin) is str:
                    bin = flow_monitor_histogram['bin']
                    skip = True
                histogram[float(bin['@start'])] = int(bin['@count'])
                if skip:
                    break
        return histogram

    # Then collect their statistics
    for flow in flow_monitor_contents['FlowMonitor']['FlowStats']['Flow']:
        flow_id = int(flow["@flowId"])
        if flow_id not in flow_port_map:
            continue

        # Replace histograms with dictionaries
        flow['delayHistogram'] = read_histogram(flow['delayHistogram'])
        flow['jitterHistogram'] = read_histogram(flow['jitterHistogram'])
        flow['packetSizeHistogram'] = read_histogram(flow['packetSizeHistogram'])

        application_flows["applicationPort"][flow_port_map[flow_id]]["flows"][flow_id]["status"] = flow
        pass

    return application_flows


if __name__ == "__main__":
    test_results = extract_network_performance_metrics(os.path.abspath("./"))
    print()
    pass
