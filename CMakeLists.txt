#######################################
# Required CMake version#
#######################################
cmake_minimum_required( VERSION 3.11 )

#set(CMAKE_C_COMPILER "clang")
#set(CMAKE_CXX_COMPILER "clang++")

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    SET_PROPERTY(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    SET_PROPERTY(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
    message("CCache is enabled")
endif(CCACHE_FOUND)

#######################################
# Project name                        #
#######################################
project(NS3 CXX C)

include(buildsupport/macros_and_definitions.cmake)

set(NS3_VER -3-dev)

option(NS3_LOG "Enable logging to be built" ON)

option(NS3_TESTS "Enable tests to be built" OFF)

option(NS3_EXAMPLES "Enable examples to be built" OFF)

option(NS3_SANITIZE "Run Google sanitizers" OFF)

option(NS3_PYTHON "Build NS3-lib pybindings" OFF)

option(NS3_BOOST "Build with Boost support" OFF)

option(NS3_OPENFLOW "Build with Openflow support" OFF)

option(NS3_GTK2 "Build with GTK2 support" OFF)

option(NS3_LIBXML2 "Build with LIBXML2 support" OFF)

option(NS3_MPI "Build with MPI support" OFF)

option(NS3_PYTORCH "Build components that rely on PyTorch support" OFF)

option(NS3_GSL "Build with GSL support" OFF)

option(NS3_PLANETLAB "Build with Planetlab support" OFF)

option(NS3_TAP "Build with Tap support" OFF)

option(NS3_EMU "Build with emulation support" OFF)

option(NS3_GNUPLOT "Build with Gnuplot support" OFF)

option(NS3_BRITE "Build with Brite support" OFF)

option (NS3_CLICK "Build with Click support" OFF)

option(NS3_NSC "Build with NSC" OFF)
#TODO: download, build and link sources

option(NS3_NETANIM "Build netanim support" OFF)

option(NS3_PTHREAD "Build with pthread support" ON)

option(NS3_REALTIME "Build with realtime support" OFF)

option(NS3_STATIC "Build static library" OFF)

option(AUTOINSTALL_DEPENDENCIES "Automatically download and compile required dependencies with Vcpkg" OFF)

#Check if optional configuration file (configFile.cmake) exists. It will overlap command line arguments.
if(EXISTS ${CMAKE_SOURCE_DIR}/configFile.cmake)
    include(${CMAKE_SOURCE_DIR}/configFile.cmake)
endif()

#Scan module libraries
SUBDIRLIST(libs_to_build ${CMAKE_SOURCE_DIR}/src)

#Scan contribution libraries
SUBDIRLIST(contribution_libraries_to_build ${CMAKE_SOURCE_DIR}/contrib)

#Hold list of 3rd-party libraries to build
set(3rd_party_libraries_to_build)
#######################################
# Process options                     #
#######################################
process_options()

#######################################
# Add subdirectories                  #
#######################################
foreach(libname ${3rd_party_libraries_to_build})
    add_subdirectory(${PROJECT_SOURCE_DIR}/3rd-party/${libname})
endforeach()

#Build NS3 library core
add_subdirectory(src)

#Build NS library examples
add_subdirectory(examples)

#Build scratch/simulation scripts
add_subdirectory(scratch)

#Build test utils
add_subdirectory(utils)



