import subprocess, os, json


#Run a test case and return output + error 
def run_test(test_name):

	output = None
	error = None
	try:
		output = subprocess.check_output(["./test-runner", "--test-name="+test_name], shell=False, cwd="../build/bin/", stderr=subprocess.DEVNULL).decode()
		output = output.split("\n")[-2]
		output = output.split(" ")[0]
	except Exception:
		error = True

	return test_name, output, error


#Dispatch tests to run
def dispatch_tests(tests_to_run):
	# Create a pool of worker processes and run tests in parallel
	import multiprocessing

	results = []
	#Lazy work ahead: dispatch all test processes (>200x2) at the same time
	with multiprocessing.Pool(processes=len(tests)) as pool: 
		results = pool.starmap(run_test, [[x] for x in tests_to_run])

	# Compile failed tests in a single dictionary
	failed_tests = {}
	for result in results:
		if result[2]:
			failed_tests[result[0]] = (result[1:])

	return results, failed_tests


#Print failed tests
def print_results(failed_tests, num_tests):
	# Print number and name of failed tests
	print("Failed tests: %d of %d" % (len(failed_tests), num_tests))
	print("", list(failed_tests.keys()))


#Dump failed tests
def dump_results(failed_tests, output_file):

	with open(output_file, "w") as file:
		json.dump(failed_tests, file)


#Load previous results
def load_previous(input_file):
	if os.path.exists(input_file):
		#Load results
		with open(input_file, "r") as file:
			previous_results = json.load(file)

		#Check failed tests
		failed_tests = {}
		for result in previous_results:
			if result[2]:
				failed_tests[result[0]] = (result[1:])

		return True, previous_results, failed_tests
	else:
		return False, {}, {}


if __name__ == '__main__':
	dumpfile = "failed_tests.json"

	#Fetch test names from test-runner
	tmp = subprocess.check_output(["./test-runner", "--list"], shell=False, cwd="../build/bin/", stderr=None).decode()
	tests = tmp.split("\n")[:-1]

	#If there is a failed tests file, load
	have_previous, previous_results, previously_failed_tests = load_previous(dumpfile)

	#If you want to run only tests that failed previously
	rerunFailed = True

	#Choose whether to rerun previously failed tests or run all the tests
	if rerunFailed and have_previous:
		tests = list(previously_failed_tests.keys())

	results, failed_tests = dispatch_tests(tests)

	#Print results
	print_results(failed_tests, len(tests))

	#Dump failed tests for future tests
	dump_results(results, dumpfile)

	pass


