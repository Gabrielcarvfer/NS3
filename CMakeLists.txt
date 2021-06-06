# Copyright (c) 2017-2021 Universidade de Brasília
#
# This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public
# License version 2 as published by the Free Software Foundation;
#
# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
# warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with this program; if not, write to the Free
# Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
# Author: Gabriel Ferreira <gabrielcarvfer@gmail.com>

# ######################################################################################################################
# Required CMake version#
# ######################################################################################################################
cmake_minimum_required(VERSION 3.16)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
  message(STATUS "CCache is enabled")

  # Setting CCACHE_SLOPPINES here only works if you call cmake to build instead of using your build system. Just
  # configure ccache directly and it will do the trick. WARNING: ccache settings and version may cause it to may slown
  # down the build when using pch
  set(ENV{CCACHE_SLOPPINESS} "pch_defines,time_macros")
endif(CCACHE_FOUND)

# ######################################################################################################################
# Project name                        #
# ######################################################################################################################
project(NS3 CXX C)

include(buildsupport/macros_and_definitions.cmake)

set(NS3_VER 3-dev)

# common options
option(NS3_ASSERT "Enable assert on failure" OFF)
option(NS3_EXAMPLES "Enable examples to be built" OFF)
option(NS3_LOG "Enable logging to be built" OFF)
option(NS3_TESTS "Enable tests to be built" OFF)

# fd-net-device options
option(NS3_EMU "Build with emulation support" ON)
option(NS3_PLANETLAB "Build with Planetlab support" OFF)
option(NS3_TAP "Build with Tap support" ON)

# maintenance and documentation
option(NS3_COVERAGE "Enable code coverage measurements and report generation" OFF)
option(NS3_CLANG_FORMAT "Enforce cody style with clang-format" OFF)
option(NS3_CLANG_TIDY "Use clang-tidy static analysis" OFF)
option(NS3_DOCS "Generate documentation" OFF)
option(NS3_SANITIZE "Build with sanitizers" OFF)
option(NS3_SCAN_PYTHON_BINDINGS "Scan python bindings" OFF)
option(NS3_LINK_WHAT_YOU_USE "Use LWYU to determine unnecessary linked libraries" OFF)
option(NS3_INCLUDE_WHAT_YOU_USE "Use IWYU to determine unnecessary headers included" OFF)

# 3rd-party libraries/programs
option(NS3_BRITE "Build with brite support" OFF)
option(NS3_CLICK "Build with click support" OFF)
option(NS3_NETANIM "Build netanim support" OFF)
option(NS3_OPENFLOW "Build with Openflow support" OFF)

# other options
option(NS3_ENABLE_BUILD_VERSION "Embed version info into libraries" OFF)
option(NS3_GNUPLOT "Build with Gnuplot support" OFF)
option(NS3_GSL "Build with GSL support" ON)
option(NS3_GTK3 "Build with GTK3 support" ON)
option(NS3_LINK_TIME_OPTIMIZATION "Build with link-time optimization" OFF)
option(NS3_MPI "Build with MPI support" ON)
option(NS3_NATIVE_OPTIMIZATIONS "Build with -march=native -mtune=native" OFF)
option(NS3_NSC "Build with NSC support" OFF) # currently not supported
option(NS3_PRECOMPILE_HEADERS "Precompile module headers to speed up compilation" OFF)
option(NS3_PTHREAD "Build with pthread support" ON)
option(NS3_PYTHON_BINDINGS "Build ns-3 python bindings" OFF)
option(NS3_REALTIME "Build with realtime support" ON)
option(NS3_STACKTRACE "Build with stack-based event tracing" OFF)
option(NS3_STATIC "Build a static ns-3 library and link it against executables" OFF)

# custom options
option(NS3_PYTORCH "Build components that rely on PyTorch support" OFF)
option(AUTOINSTALL_DEPENDENCIES "Automatically download and compile required dependencies with Vcpkg" OFF)

# Check if optional configuration file (configFile.cmake) exists. It will overlap command line arguments.
if(EXISTS ${CMAKE_SOURCE_DIR}/configFile.cmake)
  include(${CMAKE_SOURCE_DIR}/configFile.cmake)
endif()

# Scan module libraries
subdirlist(libs_to_build ${CMAKE_SOURCE_DIR}/src)

# Fetch 3rd-party contrib modules
#fetch_ns3_store_module("lorawan" "" "GIT" "https://github.com/signetlabdei/lorawan.git" "159cc5e8c62430ee2fb15f6ebcda916202004298" "" "")
#fetch_ns3_store_module("netsimulyzer" "" "GIT" "https://github.com/usnistgov/netsimulyzer-ns3-module.git" "e1dbdaa12340f0300d045defc0cfe5808b017076" "" "")
#fetch_ns3_store_module("mmwave" "src/mmwave" "GIT" "https://github.com/nyuwireless-unipd/ns3-mmwave.git" "bb2c452a964785e0be296c85a55d575591d8405f" "" "") # requires ns-3.31
#fetch_ns3_store_module("docsis" "" "GIT" "https://github.com/cablelabs/docsis-ns3.git" "71d8e01c2daa5e180b443b41d7ab920c5ace63c2" "patches/ns-3.33.patch" "${PROJECT_SOURCE_DIR}") # requires an additional patch

# Scan contribution libraries
subdirlist(contribution_libraries_to_build ${CMAKE_SOURCE_DIR}/contrib)

# ######################################################################################################################
# Process options                     #
# ######################################################################################################################
process_options()

# ######################################################################################################################
# Add subdirectories                  #
# ######################################################################################################################
# Build NS3 library core
add_subdirectory(src)

# Build NS library examples
add_subdirectory(examples)

# Build scratch/simulation scripts
add_subdirectory(scratch)

# Build test utils
add_subdirectory(utils)

# Workaround for missing waf files used by test.py
generate_c4che_cachepy()
generate_buildstatus()
generate_fakewaflock()

# Export package targets when installing
ns3_cmake_package()
