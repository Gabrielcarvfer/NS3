import os
import shutil
import time

baseFolder = "F:\\sims\\"
currentFolder = os.getcwd()

if os.path.exists("latest_results"):
	timestamp = time.strftime('%Y_%m_%d_%H_%M', time.gmtime(os.path.getmtime("latest_results")))
	shutil.move("latest_results", timestamp +"_old_results")

simulationScenarios = os.listdir(baseFolder)
for sim in simulationScenarios:
	for fusionAlgorithm in ["MRG_MULTIFRAME_OR",
							"MRG_MULTIFRAME_2_OF_N",
							"MRG_MULTIFRAME_3_OF_N",
							"MRG_MULTIFRAME_4_OF_N",
							"MRG_1_OF_N",
							"MRG_2_OF_N",
							"MRG_3_OF_N",
							"MRG_4_OF_N"]:

		sourceFolder = baseFolder+sim+"\\"+fusionAlgorithm

		if os.path.exists(sourceFolder):
			os.chdir(sourceFolder)
			
			if os.path.exists("sensing.png"):
				targetFolder = currentFolder+"\\latest_results\\"+sim+"\\"+fusionAlgorithm

				if not os.path.exists(targetFolder):
					os.makedirs(targetFolder)
					
				shutil.copy2("sensing.png", targetFolder)
				shutil.copy2("sensing_list.txt", targetFolder)
				shutil.copy2("simulationParameters.json", targetFolder)

			os.chdir(currentFolder)

