import pickle
import os
import glob
import subprocess
import lzma

from simulation_results.extract_collaborative_spectrum_sensing_results import extract_collaborative_spectrum_sensing_results
from simulation_results.extract_network_performance_metrics import extract_network_performance_metrics
from simulation_results.extract_rbg_activity_results import extract_rbg_activity_results

cwd = os.path.abspath(os.getcwd())

def execute_simulation_thread(job_queue):
    while not job_queue.empty():
        simulation_path, base_dir = job_queue.get()
        job_queue.task_done()
        execute_simulation(simulation_path, base_dir)

def execute_simulation(simulation_path, base_dir):
    while True:  # Just a big if
        simulation_results_compressed_pickle_path = simulation_path + os.sep + "simulationResults.pickle.lzma"

        # If simulation was already executed and results compiled into a resulting json, skip execution
        if os.path.exists(simulation_results_compressed_pickle_path):
            break

        # Execute simulation
        if not os.path.exists(simulation_path + os.sep + "flow.xml"):
            try:
                if os.sep == "\\":
                    cmd = "bash -c "
                    cmd += "\""
                    cmd += base_dir + os.sep + "5g_range_demonstration_json "
                    cmd += "\""
                else:
                    cmd = [base_dir + os.sep + "5g_range_demonstration_json"]

                simProc = subprocess.run(cmd,
                                         stdout=subprocess.PIPE,
                                         stderr=subprocess.STDOUT,
                                         cwd=simulation_path,
                                         env={"OPENBLAS_NUM_THREADS": "1",
                                              },
                                         timeout=8000
                                         )
                if simProc.returncode != 0:
                    raise Exception("ProgramFailed")
            except Exception:
                print("Failed to execute simulation. Source path: ",
                      simulation_path)
                break


        # When it finishes, extract all results and preprocess them to be able
        # to delete simulation traces and save up some disk space
        simulation_results = {
            "throughput": None,
            "tbler": None,
            "mcs_distribution": None,
            "sinr_distribution": None,
            "rbg_activity":     None,
            "collaborative_spectrum_sensing_results": None,
        }

        # Try to extract flow statistics
        try:
            flow_statistics = extract_network_performance_metrics(simulation_path)
        except Exception as e:
            print("Failed extracting flow statistics. ",
                  "Skipping to next simulation. Source path: ",
                  simulation_path)
            print("Error cause: ", e.__str__())
            break
        simulation_results["flow_statistics"] = flow_statistics
        del flow_statistics

        if "dsa_True" in simulation_path:
            # Try to extract rbg activity (scheduling, PU, etc) distribution
            # Requires scheduler_input.txt and scheduler_output.txt
            #try:
            #    rbg_activity = extract_rbg_activity_results(simulation_path)
            #except Exception:
            #    print("Failed extracting transport block error rate results. ",
            #          "Skipping to next simulation. Source path: ",
            #          simulation_path)
            #    break
            #simulation_results["rbg_activity"] = rbg_activity
            #del rbg_activity

            # Try to extract collaborative spectrum sensing results
            try:
                css_results = extract_collaborative_spectrum_sensing_results(simulation_path)
            except Exception:
                print("Failed extracting collaborative spectrum sensing results. ",
                      "Skipping to next simulation. Source path: ",
                      simulation_path)
                break
            simulation_results["collaborative_spectrum_sensing_results"] = css_results
            del css_results

        # Try dumping results into compressed pickle
        try:
            with lzma.open(simulation_results_compressed_pickle_path, "wb") as f:
                pickle.dump(simulation_results, f)
        except Exception:
            print("Failed dumping results to compressed pickle file. ",
                  "Skipping to next simulation. Source path: ",
                  simulation_path)
            break
        del simulation_results

        # Remove all output files other than simulation parameters and simulation results
        #outputFiles = glob.glob(simulation_path+os.sep+"*.*", recursive=True)
        #todo: remove files other than parameters and results pickle
        print("Finished working on ", simulation_path)
        break  #end of while
    pass