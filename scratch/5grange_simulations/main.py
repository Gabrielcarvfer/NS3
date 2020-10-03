import json
import random
from decimal import Decimal
import os

from simulation_model.simulation_scenario_generation import generateScenarios

if __name__ == "__main__":
    import multiprocessing
    import subprocess
    import shutil
    #Select if you want to generate new simulation scenarios or run manually created ones
    createAndRunScenarios = True

    baseDir = "E:\\tools\\source\\sims\\"
    resultsDict = {"scenario": {}}
    if createAndRunScenarios:
        # 100 batches
        for batch in range(0, 1):#100):
            for numUes in [1, 2, 5, 10]:#, 20, 50, 100]:
                # Prepare the simulationParameter json files for all simulations
                generateScenarios(baseDir,
                                  batch,
                                  numUes,
                                  ueSpeeds=[0,],# 10, 50, 100],
                                  clusteredUes=[False, True],
                                  dynamicSpectrumAccess=[False, True],
                                  markovOptions=[False, True],
                                  harmonicOptions=[False, True],
                                  fusionAlgs=[6,],# 7, 11, 12, 13],
                                  attackerOptions=[0, 1, 2, 5],
                                  frequencyBandOptions=[100, ],# 101, 5, 7],
                                  mimoOptions=[0, 1, 2]
                                  )

        # Easier than trying to figure out all directories for the individual simulations is to use glob
        # to find all json files with simulation parameters and pass the list for parallel execution
        import glob
        simulationParameterFilesList = glob.glob(baseDir+os.sep+"**"+os.sep+"simulationParameters.json", recursive=True)

        for scenarioJson in simulationParameterFilesList:
            # Before executing anything, we check if the outputs file has been processed for that given scenario
            if os.path.exists(os.path.dirname(scenarioJson)+os.sep+"simulationResults.json"):
                # If it does, we skip this simulation until finishing everything else
                continue
            else:
                # Run simulation scenario

                # When it finishes, extract all results and preprocess them to be able
                # to delete simulation traces and save up some disk space
                pass

        # When all simulations have finished, load up their results and apply some statistics/plots
        """
        # Run simulation if the scenario exists
        if (os.path.exists(baseDir+str(i))):

            argList = []
            scenPath = baseDir+str(i)+os.sep
          
            for numUes in [1, 2, 5, 10, 20, 50, 100]:
                path = scenPath+"ues_"+str(numUes)+os.sep+fusionAlgorithms[6]

            # Run simulations in parallel
        with multiprocessing.Pool(processes=14) as pool:
            pool.starmap(runScenario, argList)

        #Extract results
        import re
        regexBitsPerUe = "of (.*?) bits"
        regexBitsPerUeC = re.compile(regexBitsPerUe)
        regexRaw = "From (.*) fusions, (.*) were false positive and (.*) were false negative"
        regexRawC = re.compile(regexRaw)
        regexFalse = ".* of (.*) subframes"
        regexFalseC = re.compile(regexFalse)

        scenPath = baseDir+str(i)+os.sep
        # Run simulation with a few fusion algorithms
        resultsDict["scenario"][i] = {"harmonic":{}}
        for harmonicOption in [False, True]:
            resultsDict["scenario"][i]["harmonic"][harmonicOption] = {"markov":{}}
            for markovOption in [False, True]:
                resultsDict["scenario"][i]["harmonic"][harmonicOption]["markov"][markovOption] = {"attackers":{}}
                harmonicMarkovOptionPath = scenPath+"%sHarmonic_%sMarkov" % ("" if harmonicOption else "no", "" if markovOption else "no")+os.sep
                for attackersOption in ["no", "01", "02", "05", "10"]:
                    resultsDict["scenario"][i]["harmonic"][harmonicOption]["markov"][markovOption]["attackers"][attackersOption] = {"fusion":{}}
                    for fusionAlgorithm in [6, 7, 11, 12]:
                         resultsDict["scenario"][i]["harmonic"][harmonicOption]["markov"][markovOption]["attackers"][attackersOption]["fusion"][fusionAlgorithm] = {"numUes":{}}
                         for numUes in [10, 20, 50, 100]:
                             resultsDict["scenario"][i]["harmonic"][harmonicOption]["markov"][markovOption]["attackers"][attackersOption]["fusion"][fusionAlgorithm]["numUes"][numUes] = {"channel":{}}

                             sensingListFile = harmonicMarkovOptionPath+"ues_"+str(numUes)+"_"+attackersOption+"Attackers"+os.sep+fusionAlgorithms[fusionAlgorithm]+os.sep+"sensing_list.txt"

                             with open(sensingListFile, "r") as f:
                                 lines = f.readlines()
                                 lines = lines[2:] #Skip first two lines

                                 prevLine = 0
                                 for channel in range(4):
                                     channelLines = lines[:4]
                                     lines = lines[4:]

                                     #Extract numbers from e.g. From 9976 fusions, 89 were false positive and 1360 were false negative.
                                     ans = regexBitsPerUeC.search(channelLines[0]).groups()
                                     avgBitsPerUe = float(ans[0])
                                     ans = regexRawC.search(channelLines[1]).groups()
                                     fusions, falsePositives, falseNegatives = int(ans[0]), int(ans[1]), int(ans[2])
                                     framesThatCouldBeFalsePositives = int(regexFalseC.search(channelLines[2]).groups()[0])
                                     framesThatCouldBeFalseNegatives = int(regexFalseC.search(channelLines[3]).groups()[0])

                                     result = {
                                         "avgBitsPerUe"       : avgBitsPerUe,
                                         "totalFusions"       : fusions,
                                         "totalFalsePositives": falsePositives,
                                         "totalFalseNegatives": falseNegatives,
                                         "framesPuWasInactive": framesThatCouldBeFalsePositives,
                                         "framesPuWasActive"  : framesThatCouldBeFalseNegatives
                                     }
                                     resultsDict["scenario"][i]["harmonic"][harmonicOption]["markov"][markovOption]["attackers"][attackersOption]["fusion"][fusionAlgorithm]["numUes"][numUes]["channel"][channel] = result
                                     lines = lines[1:] #Skip empty line between channels

            with open(baseDir+"results.json", "w") as f:
                import json
                json.dump(resultsDict, f, indent=2)
                pass

"""
    pass
