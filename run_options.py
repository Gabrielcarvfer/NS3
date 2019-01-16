#!/usr/bin/python3 

import multiprocessing
import subprocess, os, json


def run_option(option):
	os.chdir(os.getcwd()+"/build/bin/contrib/gabrielcarvfer/examples")
	subprocess.check_output(["./dynamic_beacon3", "--simOption="+str(option)], shell=False, stderr=subprocess.DEVNULL)
	return


if __name__ == '__main__':
	with multiprocessing.Pool(processes=14) as pool: 
		pool.starmap(run_option, [[x] for x in range(96)])