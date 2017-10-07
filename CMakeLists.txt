#######################################
# Required CMake version#
#######################################
cmake_minimum_required( VERSION 3.0 )

#######################################
# Project name                        #
#######################################
project(NS3 CXX)

include(buildsupport/macros_and_definitions.cmake)

set(NS3_VER 3.26)


option(NS3_TESTS "Enable tests to be built" OFF)
set(NS3_TESTS OFF)

option(NS3_DEBUG "Build NS3-lib in debug mode" OFF)
set(NS3_DEBUG ON)


set(NS3_PTHREAD ON)
option(NS3_PTHREAD "Build with pthread support" OFF)


set(NS3_MPI ON)
option(NS3_MPI "Build with MPI support" OFF)


set(NS3_GSL ON)
option(NS3_GSL "Build with GSL support" OFF)

#######################################
# Process options                     #
#######################################
process_options()


#######################################
# Add subdirectories                  #
#######################################
NS3_common_includes()

add_subdirectory( src )




