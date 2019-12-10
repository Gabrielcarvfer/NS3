import sys
import os

sys.path.append("E:\\tools\\source\\NS3")

from plot_network_topology import plot_network_topology

baseDir = "E:\\results_collaborative_sensing\\report_scenarios\\"

simulationScenarios = os.listdir(baseDir)

for scenario in simulationScenarios:

	scenarioVariations = os.listdir(baseDir+scenario)

	for scenarioVariation in scenarioVariations:
		plot_network_topology(baseDir+scenario+"\\"+scenarioVariation+"\\")