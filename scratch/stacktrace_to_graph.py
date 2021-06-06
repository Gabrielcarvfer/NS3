# Copyright (c) 2017-2021 Universidade de Brasília
#
# This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public
# License version 2 as published by the Free Software Foundation;
#
# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
# warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with this program; if not, write to the Free
# Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
# Author: Gabriel Ferreira <gabrielcarvfer@gmail.com>

# Parse trace file
def get_graph(trace_file):
    with open(trace_file, "r") as file:
        trace_log = file.readlines()

    from collections import deque
    trace_log = deque(trace_log)

    # Discard lines until trace starts
    while "SimulationTime" not in trace_log[0]:
        trace_log.popleft()

    # Create structure for execution graph
    # (dictionary has events as keys and edges are a tuple of timestamp + scheduled id + stack)
    graph = {"nodes": {}}

    trace_log_len = len(trace_log)
    while trace_log_len > 0:
        trace_log_len -= 2

        # Now we read the first line with simulation timestamp (ns), current event id and scheduled event id
        temp = trace_log.popleft().split(" ")
        timestamp_ns, currentId, scheduledId, scheduled_timestamp_ns, context = [int(temp[i]) for i in range(1, 10, 2)]

        # Then we read the reversed stack
        stack = []
        while len(trace_log[0]) > 1:
            line = trace_log.popleft()
            stack.append(line.split("#")[1])
            trace_log_len -= 1

        # Remove the empty line separator
        trace_log.popleft()

        # Put the stack in the right order
        stack.reverse()
        stack = deque(stack)

        # Create entry for current ID
        if currentId not in graph["nodes"]:
            graph["nodes"][currentId] = {"edges": {}, "timestamp_s": 0, "context": -1}

        # Store scheduled ID, timestamp and stack
        graph["nodes"][currentId]["edges"][scheduledId] = (timestamp_ns, stack)

        # Create entry for scheduled ID
        if scheduledId not in graph["nodes"]:
            graph["nodes"][scheduledId] = {"edges": {},
                                           "timestamp_s": scheduled_timestamp_ns/(10**9),
                                           "context": context if context != 4294967295 else -1
                                           }

    return graph


def get_shared_stack(graph):
    for node in graph["nodes"]:
        shared_stack = []
        commonStack = "trash"
        while commonStack:
            commonStack = None
            for edge in graph["nodes"][node]["edges"]:
                if len(graph["nodes"][node]["edges"][edge][1]) == 0:
                    commonStack = None
                    break
                edge_stack = graph["nodes"][node]["edges"][edge][1][0]
                if not commonStack:
                    commonStack = edge_stack
                if commonStack != edge_stack:
                    commonStack = None
                    break  # stop trying to get a shared stack
            if commonStack:
                for edge in graph["nodes"][node]["edges"]:
                    graph["nodes"][node]["edges"][edge][1].popleft()
                shared_stack.append(commonStack)
            graph["nodes"][node]["shared_stack"] = shared_stack

        smallestTimestamp = None
        for edge in graph["nodes"][node]["edges"]:
            edge_timestamp = graph["nodes"][node]["edges"][edge][0]
            if not smallestTimestamp:
                smallestTimestamp = edge_timestamp
            if smallestTimestamp > edge_timestamp:
                smallestTimestamp = edge_timestamp
        if smallestTimestamp is not None:
            graph["nodes"][node]["timestamp_s"] = smallestTimestamp/(10**9)
    return graph


def get_flow_chart(graph):
    flow_chart_nodes = []
    flow_chart_edges = []

    # We are going to to this in two passes, first creating all necessary nodes with comments and timestamps
    for node in graph["nodes"]:
        shared_stack = graph["nodes"][node]["shared_stack"]
        if len(shared_stack) > 0:
            for i in [len(shared_stack)-i-1 for i in range(len(shared_stack))]:
                if "Schedule" in shared_stack[i]:
                    continue
                shared_stack = shared_stack[i]
                break
        node_text = "%d [label=\" Timestamp=%fs, Context=%d, Shared Stack=%s\"];" %\
                    (node,
                     graph["nodes"][node]['timestamp_s'],
                     graph["nodes"][node]['context'],
                     "".join(shared_stack).replace("\n", ";"),
                     )
        flow_chart_nodes.append(node_text)

    # In the second pass, we create the edges with the delays between the events
    for node in graph["nodes"]:
        timestamp_origin = graph["nodes"][node]["timestamp_s"]
        for edge in graph["nodes"][node]["edges"]:
            timestamp_destination = graph["nodes"][edge]["timestamp_s"]
            private_stack = graph["nodes"][node]["edges"][edge][1]
            for i in [len(private_stack)-i-1 for i in range(len(private_stack))]:
                if "Schedule" in private_stack[i]:
                    continue
                private_stack = private_stack[i]
                break
            edge_text = "%d -> %d [label=\"Delay=%f, Stack=%s\"];" % (node, edge, timestamp_destination-timestamp_origin, "".join(private_stack).replace("\n", ";"))
            flow_chart_edges.append(edge_text)

    return "digraph sim {\n" + "\n".join(flow_chart_nodes) + "\n" + "\n".join(flow_chart_edges) + "\n}\n"

# Read stacktrace file and build basic graph
stack_graph = get_graph("stacktrace.txt")

# Now we can get shared stack portions of all edges
shared_stack_graph = get_shared_stack(stack_graph)

# Now we can build the actual graph or flow chart
flow_chart = get_flow_chart(shared_stack_graph)

# Dump flowchart
with open("flowchart.dot", "w") as file:
    file.write(flow_chart)

print()
