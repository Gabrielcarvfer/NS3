#######################################
# Required CMake version#
#######################################
cmake_minimum_required( VERSION 3.0 )

#######################################
# Project name                        #
#######################################
project(NS3 CXX)

set(CMAKE_CXX_COMPILER="ccache g++")
include(buildsupport/macros_and_definitions.cmake)

set(NS3_VER 3.27)

option(NS3_LOG "Enable logging to be built" ON)

option(NS3_TESTS "Enable tests to be built" ON)

option(NS3_EXAMPLES "Enable examples to be built" ON)

option(NS3_DEBUG "Build NS3-lib in debug mode" ON)
set(NS3_DEBUG ON)

option(NS3_PYTHON "Build NS3-lib pybindings" OFF)
set(NS3_PYTHON OFF)

#set(NS3_PTHREAD ON)
#option(NS3_PTHREAD "Build with pthread support" OFF)

option(NS3_BOOST "Build with Boost support" OFF)
set(NS3_BOOST ON)

option(NS3_GTK2 "Build with GTK2 support" OFF)
set(NS3_GTK2 OFF)

option(NS3_LIBXML2 "Build with LIBXML2 support" OFF)
set(NS3_LIBXML2 ON)

option(NS3_LIBRT "Build with RT support" OFF)
set(NS3_LIBRT ON)

option(NS3_MPI "Build with MPI support" OFF)
set(NS3_MPI ON)

option(NS3_GSL "Build with GSL support" OFF)
set(NS3_GSL ON)

option(NS3_PLANETLAB "Build with Planetlab support" OFF)
set(NS3_PLANETLAB OFF)

option(NS3_TAP "Build with Tap support" OFF)
set(NS3_TAP OFF)

option(NS3_EMU "Build with emu support" OFF)
set(NS3_EMU OFF)

option(NS3_GNUPLOT "Build with Gnuplot support" OFF)
set(NS3_GNUPLOT ON)

#Select libs to be built
# libs marked with # on the right are compiling on windows
# libs marked with * on the right, are not compiling correctly yet when using CMake
set(libs_to_build
        antenna #
        aodv
        applications
        bridge #
        #brite
        buildings #
        click
        config-store #
        core #
        csma #
        csma-layout
        dsdv
        dsr
        energy #
        fd-net-device #requires socket implementation
        flow-monitor
        internet #main block, couldnt identify the problem
        internet-apps
        lr-wpan #
        lte
        mesh
        mobility #
        mpi
        netanim
        network #
        nix-vector-routing
        olsr
        #openflow
        point-to-point #
        point-to-point-layout
        propagation #
        sixlowpan
        spectrum #
        stats #
        #tap-bridge *not compiling after update to ns3.27
        test
        topology-read #needs to swap posix regex to c++ regex
        traffic-control #
        uan
        virtual-net-device #
        #visualizer
        wave
        wifi #
        wimax
        )


#######################################
# Process options                     #
#######################################
process_options()


#######################################
# Add subdirectories                  #
#######################################

#Build NS3 3rd-party library support
add_subdirectory(3rd-party)

#Build NS3 library core
add_subdirectory(src)

#Build NS library examples
if(${NS3_EXAMPLES})
    add_subdirectory(examples)
endif()

#Build contribution libraries
add_subdirectory(contrib)

#Build scratch/simulation scripts
add_subdirectory(scratch)




