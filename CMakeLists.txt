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
endif(CCACHE_FOUND)

#######################################
# Project name                        #
#######################################
project(NS3 CXX C)

include(buildsupport/macros_and_definitions.cmake)

set(NS3_VER 3.30.1)

option(NS3_LOG "Enable logging to be built" ON)

option(NS3_TESTS "Enable tests to be built" OFF)
set(NS3_TESTS ON)

option(NS3_EXAMPLES "Enable examples to be built" OFF)
set(NS3_EXAMPLES ON)

option(NS3_SANITIZE "Run Google sanitizers" OFF)
#set(NS3_SANITIZE ON)

option(NS3_PYTHON "Build NS3-lib pybindings" OFF)
#set(NS3_PYTHON ON)

option(NS3_BOOST "Build with Boost support" OFF)
#set(NS3_BOOST ON)

option(NS3_OPENFLOW "Build with Openflow support" OFF)
#set(NS3_OPENFLOW ON)

option(NS3_GTK2 "Build with GTK2 support" OFF)
set(NS3_GTK2 OFF)

option(NS3_LIBXML2 "Build with LIBXML2 support" OFF)
set(NS3_LIBXML2 ON)

option(NS3_LIBRT "Build with RT support" OFF)
set(NS3_LIBRT ON) #not working on Windows

option(NS3_MPI "Build with MPI support" OFF)
set(NS3_MPI OFF)

option(NS3_PYTORCH "Build components that rely on PyTorch support" OFF)
set(NS3_PYTORCH ON)

option(NS3_GSL "Build with GSL support" OFF)
set(NS3_GSL ON)

option(NS3_PLANETLAB "Build with Planetlab support" OFF)
set(NS3_PLANETLAB OFF)

option(NS3_TAP "Build with Tap support" OFF)
set(NS3_TAP OFF)

option(NS3_EMU "Build with emu support" OFF)
set(NS3_EMU OFF)

option(NS3_GNUPLOT "Build with Gnuplot support" OFF)
set(NS3_GNUPLOT OFF)

option(NS3_BRITE "Build with Brite support" OFF)
#set(NS3_BRITE ON)

option(NS3_NSC "Build with NSC" OFF)
#TODO: download, build and link sources

option(NS3_NETANIM "Build netanim support" OFF)
#set(NS3_NETANIM ON)

set(USE_QT 5)# Choose between Qt 4 or 5

option(NS3_PTHREAD "Build with pthread support" ON)
set(NS3_PTHREAD ON)

option(NS3_STATIC "Build static library" OFF)

option(AUTOINSTALL_DEPENDENCIES "Automatically download and compile required dependencies with Vcpkg" OFF)
set(AUTOINSTALL_DEPENDENCIES ON)

option(NS3_fd-net-device "Build fd-net-device" ON)
set(NS3_fd-net-device ON)


if(MSVC)
	set(NS3_NETANIM OFF)
endif()

set(build_openflow)
if(${NS3_OPENFLOW})
    set(build_openflow openflow)
endif()

set(build_visualizer)
if(${NS3_PYTHON})
    set(build_bisualizer visualizer)
endif()

set(build_brite)
set(build_fd-net-device)
set(build_tap-bridge)

if (WIN32 OR APPLE)
    if(${NS3_BRITE})
        set(NS3_BRITE OFF)
    endif()
else()
    if(${NS3_BRITE})
        set(build_brite brite)
    endif()
    if(${NS3_fd-net-device})
        set(build_fd-net-device fd-net-device)
    endif()
    if(${NS3_TAP})
        set(build_tap-bridge tap-bridge)
    endif()
endif()




#Select libs to be built
# libs marked with # on the right are compiling on windows
# libs marked with * on the right, are not compiling correctly yet when using CMake
set(libs_to_build
        antenna               #
        aodv                  #
        applications          #
        bridge                #
        ${build_brite}
        buildings             #
        click                 #
        config-store          #
        core                  #
        csma                  #
        csma-layout           #
        dsdv                  #
        dsr                   #
        energy                #
        ${build_fd-net-device}#requires socket implementation
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
        ${build_openflow}     # Only builds openflow if NS3_OPENFLOW is set
        point-to-point        #
        point-to-point-layout
        propagation           #
        sixlowpan
        spectrum              #
        stats                 #
        ${build_tap-bridge}   #
        topology-read         # fixed on Windows with LibPCRE2-posix
        traffic-control       #
        uan                   #
        virtual-net-device    #
        ${build_visualizer}
        wave                  #
        wifi                  #
        wimax                 #
        test                  # beware of naming colisions between macro CHECK in traced-value-callback-typedef-test-suite.cc and torch/script.h (PyTorch)

        )

#Build contribution libraries
set(contribution_libraries_to_build
        haraldott # https://github.com/haraldott/dash/commit/f886b5757de277db9c88e442458f20960a70b57a
        )

#######################################
# Process options                     #
#######################################
process_options()

#######################################
# Add subdirectories                  #
#######################################

#Build NS3 3rd-party library support
#add_subdirectory(3rd-party)

#Build NS3 library core
add_subdirectory(src)

#Build NS library examples
add_subdirectory(examples)

#Build scratch/simulation scripts
add_subdirectory(scratch)

#Build test utils
add_subdirectory(utils)



