import os
import shutil
import multiprocessing
from enum import Enum

from simulation_model.simulation_scenario_generation import generate_scenarios
from simulation_execution.execute_simulation import execute_simulation

class freqBands(Enum):
    MHz850 = 5
    MHz713 = 12
    MHz525 = 101
    MHz240 = 100

class mimoModes(Enum):
    SISO = 0
    TxDiversity = 1
    SpatialMultiplexing = 2


if __name__ == "__main__":
    multiprocessing.freeze_support()

    # Select if you want to generate new simulation scenarios or run manually created ones
    createAndRunScenarios = True

    # Output folder
    baseDir = os.path.abspath("../../build/bin/")

    # You're supposed to run this script inside the scratch/5grange_simulations folder
    cwd = os.path.abspath(os.getcwd())  # do not touch this

    # Copy injected traffic files to baseDir (where the 5g_range_demonstration_json executable is)
    shutil.copy("voip_charge0_10s.json", baseDir)
    shutil.copy("voip_charge0_100s.json", baseDir)
    shutil.copy("web_charge0_10s.json", baseDir)
    shutil.copy("web_charge0_100s.json", baseDir)


    resultsDict = {"scenario": {}}
    numBatches = 10
    numUEs = [1, 3, 20, 50, 100, ] # 2, 5, 10, 20, 50, 100
    numerology_and_numUEs_threshold = [(0, 0), (2, 20), (3, 50)]
    dynamic_spectrum_access = [False, True,]
    if createAndRunScenarios:
        for batch in range(numBatches):
            for numUes in numUEs:
                for use_dsa in dynamic_spectrum_access:
                    for numerology, numUesThreshold in numerology_and_numUEs_threshold:
                        if numUes >= numUesThreshold:
                            # Prepare the simulationParameter json files for all simulations
                            generate_scenarios(baseDir,
                                          batch,
                                          numUes,
                                          numerologies=[numerology, ],
                                          ueSpeeds=[0, ],  # 10, 50, 100],
                                          clusteredUes=[False, ],  # True],
                                          dynamicSpectrumAccess=[use_dsa, ],  # True],
                                          markovOptions=[use_dsa, ],  # True],
                                          harmonicOptions=[False, ],  # True], # not working with attackers
                                          fusionAlgs=[6, ],  # 7, 11, 12, 13],
                                          attackerOptions=[0, ],  # 1, 2, 5],
                                          frequencyBandOptions=[freqBands.MHz713, ],  # 101, 5, 7],
                                          mimoOptions=[mimoModes.TxDiversity, ],  # 0, 1, 2]
                                          )

        # Easier than trying to figure out all directories for the individual simulations is to use glob
        # to find all json files with simulation parameters and pass the list for parallel execution
        import glob
        simulationParameterFilesList = glob.glob(baseDir+os.sep+"**"+os.sep+"simulationParameters.json", recursive=True)

        for scenarioJson in simulationParameterFilesList:
            # Before executing anything, we check if the outputs file has been processed for that given scenario
            simulation_path = os.path.dirname(scenarioJson)

            # Run simulation if necessary and try to extract results into a single output file
            execute_simulation(simulation_path, baseDir)


        # When all simulations have finished, load up their results and apply some statistics/plots
        # Result files were pickled and compressed

    pass
