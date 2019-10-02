SOURCE_PATH = "/mnt/dev/tools/source/NS3/"

import os
import re


REGEX_MATCH_STRING = "#include*.*[<\"](?!sys|net|linux|netinet|unistd|errno)(.*.h)[>\"]"
"""
Test cases for regex matching of header files finishing with .h 
Resulting header file without <> or "" is stored in re.search(REGEX_MATCH_STRING, string_to_match).group(1)

#include <ns3/test.h>
#include <ns3/openflow/openflow.h>
#include <3rd-Party-Library/openflow/openflow.h>
#include <3rd-Party-Library/openflow.h>
#include "ns3/test.h"
#include "ns3/openflow/openflow.h"
#include "3rd-Party-Library/openflow/openflow.h"
#include "3rd-Party-Library/openflow.h"
#include <cstdio>
#include <unistd.h>
asdasd
<asdoaskdo.h>
//<--
#include <netinet/in.h>
#include <sys/socket.h>

"""

os.chdir(SOURCE_PATH)

#Search for all .cc and .h files and their relative paths to the root folder (SOURCE_PATH)
file_paths = {} #{file_name : { relative_path : path} }
for (dirpath, dirnames, filenames) in os.walk("./"):
    #Ignore files in build folder
    sep = dirpath.split("/")

    ignore_folder = False
    for ignored_folder in ["build", "vcpkg", "cmake-build-debug", "cmake-build-release", "cmake-build-relwithdebinfo", "ninja_cmake", "3rd-party"]:
        if "cpp-std-fwd" in sep:
            break
        if ignored_folder in sep:
            ignore_folder = True
            break

    if ignore_folder:
        continue

    #Iterate files while ignoring files without extension or with extensions other than .cc and .h
    for filename in filenames:
        sep = filename.split(".")
        if len(sep) < 2 or sep[1] not in ["h", "cc"]:
            continue
        #Store relative path to a given file
        file_paths[filename] = {"relative_path": dirpath+os.sep+filename}
        pass
    pass

def parse_and_fix_headers(relative_path):
    modified = False
    file_contents = []
    with open(relative_path, "r", encoding="UTF-8") as fd:
        #Read file contents
        file_contents = fd.readlines()
        #Close file handle

    #Process each line for includes
    for line in range(len(file_contents)):

        #Ignore lines that do not contain header paths
        search = re.search(REGEX_MATCH_STRING, file_contents[line])
        if search is None:
            continue

        #Ignore modules
        pos_m = file_contents[line].find("-module.h")
        if pos_m is not -1:
            continue

        # Get the header file name
        header_file = search.group(1).split("/")[-1]

        #Ignore headers that are not from ns-3 or are generated during build ("core-config.h", "mpi.h", "longlong.h", "fnv.h", "ns3module.h", "Brite.h", "config-store-config.h")
        if header_file not in file_paths:
            continue

        #Copy line contents
        contents = file_contents[line]

        # Replace <> with "" for ns3 headers
        contents = contents.replace("<", "\"")
        contents = contents.replace(">", "\"")

        #Get current file path
        curr_file_path = file_paths[file]["relative_path"]
        header_file_path = file_paths[header_file]["relative_path"]

        #Check commonalities between relative paths and reduce path if possible
        curr_file_path_components = curr_file_path.split("/")
        header_file_path_components = header_file_path.split("/")

        join_point = 0
        while (curr_file_path_components[join_point] == header_file_path_components[join_point]):
            join_point += 1

        #Compute relative path to header
        relative_path = "../" * (len(curr_file_path_components)-join_point-1)
        relative_path += "/".join(header_file_path_components[join_point:])

        #Replace path to header with relative path
        contents = contents.replace(search.group(1), relative_path)

        #If content changed, write to disk
        file_contents[line] = contents

        #Mark file to be overwritten with header modifications
        modified = True

        #Remove temporary variables
        del header_file
        del header_file_path, header_file_path_components
        del curr_file_path, curr_file_path_components
        del join_point
        del relative_path
        pass
    pass
    return file_contents, modified


def write_modified_file (path, contents):
    # Write modified contents
    with open(path, "w", encoding="UTF-8") as fd:
        fd.writelines(contents)
        fd.flush()
        fd.close()
        # Close file handle
        pass
    pass

modified_files = []

#Open all .cc and .h files looking for "ns3/.h" includes and replace with relative path to the included header
for file in file_paths:
    file_contents = ""
    modified = False

    file_contents, modified = parse_and_fix_headers(file_paths[file]["relative_path"])

    if modified:
        write_modified_file(file_paths[file]["relative_path"], file_contents)
        modified_files += [file]
        pass
    pass

print("%d files had their include header paths relativized. " % len(modified_files))
print("%s" % ("Here's the list: " + ", ".join(modified_files) + ".") if len(modified_files) > 0 else "")
pass

