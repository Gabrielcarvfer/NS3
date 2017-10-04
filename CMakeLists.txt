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

set(NS3_TESTS ON)
option(NS3_TESTS "Enable tests to be built" OFF)

set(NS3_DEBUG ON)
option( NS3_DEBUG "Build NS3-lib in debug mode" OFF)


#######################################
# Process options                     #
#######################################
process_options()


#######################################
# Add subdirectories                  #
#######################################
NS3_common_includes()

add_subdirectory( src )

delete_header_temp_folder()



