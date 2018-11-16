#######################################
# Required CMake version#
#######################################
cmake_minimum_required( VERSION 3.4 )

#set(CMAKE_C_COMPILER "clang")
#set(CMAKE_CXX_COMPILER "clang++")

#######################################
# Project name                        #
#######################################
project(NS3 CXX)

set(NS3_VER 3.29)

include(buildsupport/macros_and_definitions.cmake)

option(NS3_LOG "Enable logging to be built" ON)

option(NS3_TESTS "Enable tests to be built" OFF)
#set(NS3_TESTS ON)

option(NS3_EXAMPLES "Enable examples to be built" OFF)
#set(NS3_EXAMPLES ON)

option(NS3_DEBUG "Build NS3-lib in debug mode" OFF)
set(NS3_DEBUG ON)

option(NS3_PYTHON "Build NS3-lib pybindings" OFF)
set(NS3_PYTHON OFF)

option(NS3_BOOST "Build with Boost support" OFF)
set(NS3_BOOST ON)

option(NS3_GTK2 "Build with GTK2 support" OFF)
set(NS3_GTK2 OFF)

option(NS3_LIBXML2 "Build with LIBXML2 support" OFF)
set(NS3_LIBXML2 ON)

option(NS3_LIBRT "Build with RT support" OFF)
set(NS3_LIBRT ON) #not working on Windows

option(NS3_MPI "Build with MPI support" OFF)
set(NS3_MPI OFF)

option(NS3_GSL "Build with GSL support" OFF)
set(NS3_GSL OFF)

option(NS3_PLANETLAB "Build with Planetlab support" OFF)
set(NS3_PLANETLAB OFF)

option(NS3_TAP "Build with Tap support" OFF)
set(NS3_TAP OFF)

option(NS3_EMU "Build with emu support" OFF)
set(NS3_EMU OFF)

option(NS3_GNUPLOT "Build with Gnuplot support" OFF)
set(NS3_GNUPLOT OFF)

option(NS3_BRITE "Build with Brite support" OFF)
set(NS3_BRITE OFF)

option(NS3_NETANIM "Build netanim support" OFF)
set(NS3_NETANIM OFF)

option(NS3_SHARED "Build shared libraries" ON)
set(NS3_SHARED ON)

option(AUTOINSTALL_DEPENDENCIES "Automatically download and compile required dependencies with Vcpkg" OFF)
set(AUTOINSTALL_DEPENDENCIES ON)


#Select libs to be built
# libs marked with # on the right are compiling on windows
# libs marked with * on the right, are not compiling correctly yet when using CMake
set(libs_to_build
        antenna               #
        aodv                  #
        applications          #
        bridge                #
        #brite
        buildings             #
        click                 #
        config-store          #
        core                  #
        csma                  #
        csma-layout           #
        dsdv                  #
        dsr                   #
        energy                #
        #fd-net-device        #requires socket implementation
        flow-monitor          #
        internet              #
        internet-apps         #
        lr-wpan               #
        lte                   #
        mesh                  #
        mobility              #
        mpi                   #
        netanim               # Not working with Clang on Windows
        network               #
        nix-vector-routing
        olsr
        #openflow
        point-to-point        #
        point-to-point-layout
        propagation           #
        sixlowpan
        spectrum              #
        stats                 #
        #tap-bridge           #
        test
        topology-read         # fixed on Windows with LibPCRE2-posix
        traffic-control       #
        uan                   #
        virtual-net-device    #
        #visualizer
        wave                  #
        wifi                  #
        wimax                 #
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
add_subdirectory(examples)

#Build contribution libraries
add_subdirectory(contrib)

#Build scratch/simulation scripts
add_subdirectory(scratch)

#Build test utils
add_subdirectory(utils)




