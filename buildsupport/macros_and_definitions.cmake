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

# Export compile time variable setting the directory to the NS3 root folder
add_definitions(-DPROJECT_SOURCE_PATH="${PROJECT_SOURCE_DIR}")

# Cache options for INT64X64
set(INT64X64 "INT128" CACHE STRING "Int64x64 implementation")
set(INT64X64 "CAIRO"  CACHE STRING "Int64x64 implementation")
set(INT64X64 "DOUBLE" CACHE STRING "Int64x64 implementation")
set_property(CACHE INT64X64 PROPERTY STRINGS INT128 CAIRO DOUBLE)

# WSLv1 doesn't support tap features
if(EXISTS "/proc/version")
  file(READ "/proc/version" CMAKE_LINUX_DISTRO)
  string(FIND ${CMAKE_LINUX_DISTRO} "Microsoft" res)
  if(res EQUAL -1)
    set(WSLv1 False)
  else()
    set(WSLv1 True)
  endif()
endif()

# Set Linux flag if on Linux
if(UNIX AND NOT APPLE)
  set(LINUX TRUE)
  add_definitions(-D__LINUX__)
endif()

if(APPLE)
  add_definitions(-D__APPLE__)
endif()

set(cat_command cat)

if(CMAKE_XCODE_BUILD_SYSTEM)
  set(XCODE True)
else()
  set(XCODE False)
endif()

# Check the number of threads
include(ProcessorCount)
ProcessorCount(NumThreads)

# Output folders
set(CMAKE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY})
set(CMAKE_HEADER_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY}/include/ns3)
set(THIRD_PARTY_DIRECTORY ${PROJECT_SOURCE_DIR}/3rd-party)
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
link_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Get installation folder default values for each platform and include package configuration macro
include(GNUInstallDirs)
include(buildsupport/custom_modules/ns3_cmake_package.cmake)

if(${XCODE})
  # Is that so hard not to break people's CI, AAPL? Why would you output the targets to a Debug/Release
  # subfolder? Why?
  foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
  endforeach()
endif()

# fPIC (position-independent code) and fPIE (position-independent executable)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Set compiler options and get command to force unused function linkage (useful for libraries)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(LIB_AS_NEEDED_PRE)
set(LIB_AS_NEEDED_POST)
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU" AND NOT APPLE)
  # using GCC
  set(LIB_AS_NEEDED_PRE -Wl,--no-as-needed)
  set(LIB_AS_NEEDED_POST -Wl,--as-needed)
  set(LIB_AS_NEEDED_PRE_STATIC -Wl,--whole-archive,-Bstatic)
  set(LIB_AS_NEEDED_POST_STATIC -Wl,--no-whole-archive)
  set(LIB_AS_NEEDED_POST_STATIC_DYN -Wl,-Bdynamic,--no-whole-archive)
endif()

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" AND APPLE)
  # using Clang set(LIB_AS_NEEDED_PRE -all_load)
  set(LIB_AS_NEEDED_POST)
endif()

macro(SUBDIRLIST result curdir)
  file(
    GLOB children
    RELATIVE ${curdir}
    ${curdir}/*
  )
  set(dirlist "")
  foreach(child ${children})
    if(IS_DIRECTORY ${curdir}/${child})
      list(APPEND dirlist ${child})
    endif()
  endforeach()
  set(${result} ${dirlist})
endmacro()

macro(library_target_name libname targetname)
  set(${targetname} lib${libname})
endmacro()

# process all options passed in main cmakeLists
macro(process_options)
  # process debug switch Used in build-profile-test-suite
  string(TOUPPER ${CMAKE_BUILD_TYPE} cmakeBuildType)
  if(${cmakeBuildType} STREQUAL "DEBUG")
    add_definitions(-DNS3_BUILD_PROFILE_DEBUG)
    set(build_type "deb")
  elseif(${cmakeBuildType} STREQUAL "RELWITHDEBINFO")
    add_definitions(-DNS3_BUILD_PROFILE_RELEASE)
    set(build_type "reldeb")
  elseif(${cmakeBuildType} STREQUAL "RELEASE")
    add_definitions(-DNS3_BUILD_PROFILE_OPTIMIZED)
    set(build_type "rel")
  else()
    add_definitions(-DNS3_BUILD_PROFILE_OPTIMIZED)
    set(build_type "minsizerel")
  endif()

  if(${NS3_ENABLE_BUILD_VERSION})
    include(buildsupport/custom_modules/ns3_versioning.cmake)
    add_definitions(-DENABLE_BUILD_VERSION=1)

    find_program(GIT git)
    if(NOT GIT)
      message(FATAL_ERROR "Baking build version into libraries require Git.")
    endif()

    check_git_repo_has_ns3_tags(HAS_NS3_TAGS NS3_VERSION_TAG)

    if(NOT ${HAS_NS3_TAGS})
      message(FATAL_ERROR "This repository doesn't contain ns-3 git tags to bake into the libraries.")
    endif()

    check_ns3_closest_tags(NS3_VERSION_CLOSEST_TAG NS3_VERSION_TAG_DISTANCE NS3_VERSION_COMMIT_HASH NS3_VERSION_DIRTY_FLAG)

    # Split commit tag (ns-3.<minor>[.patch][-RC<digit>]) into (ns;3.<minor>[.patch];[-RC<digit>]):
    string(REPLACE "-" ";" NS3_VER_LIST ${NS3_VERSION_TAG})
    list(LENGTH NS3_VER_LIST NS3_VER_LIST_LEN)

    # Get last version tag fragment (RC<digit>)
    set(NS3_VERSION_RELEASE_CANDIDATE )
    if(${NS3_VER_LIST_LEN} GREATER 2)
      list(GET NS3_VER_LIST 2 RELEASE_CANDIDATE)
      set(NS3_VERSION_RELEASE_CANDIDATE "${RELEASE_CANDIDATE}")
    endif()

    # Get 3.<minor>[.patch]
    list(GET NS3_VER_LIST 1 VERSION_STRING)
    # Split into a list 3;<minor>[;patch]
    string(REPLACE "." ";" VERSION_LIST ${VERSION_STRING})
    list(LENGTH VERSION_LIST VER_LIST_LEN)

    list(GET VERSION_LIST 0 NS3_VERSION_MAJOR)
    if(${VER_LIST_LEN} GREATER 1)
      list(GET VERSION_LIST 1 NS3_VERSION_MINOR)
      if(${VER_LIST_LEN} GREATER 2)
        list(GET VERSION_LIST 2 NS3_VERSION_PATCH)
      endif()
    endif()

    # Transform list with 1 entry into strings
    set(NS3_VERSION_MAJOR "${NS3_VERSION_MAJOR}")
    set(NS3_VERSION_MINOR "${NS3_VERSION_MINOR}")
    set(NS3_VERSION_PATCH "${NS3_VERSION_PATCH}")
    set(NS3_VERSION_TAG   "${NS3_VERSION_TAG}")

    # Set
    set(NS3_VERSION_BUILD_PROFILE ${cmakeBuildType})
    configure_file(buildsupport/version-defines-template.h ${CMAKE_HEADER_OUTPUT_DIRECTORY}/version-defines.h)
  endif()

  if(${NS3_CLANG_TIDY})
    find_program(CLANG_TIDY clang-tidy)
    if(CLANG_TIDY)
      set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
    else()
      message(STATUS "Proceeding without clang-tidy static analysis")
    endif()
  endif()

  if(${NS3_CLANG_FORMAT})
    find_program(CLANG_FORMAT clang-format)
    if(CLANG_FORMAT)
      file(
        GLOB_RECURSE
        ALL_CXX_SOURCE_FILES
        src/*.cc
        src/*.h
        examples/*.cc
        examples/*.h
        utils/*.cc
        utils/*.h
        scratch/*.cc
        scratch/*.h
      )
      add_custom_target(clang-format COMMAND clang-format -style=file -i ${ALL_CXX_SOURCE_FILES})
      unset(ALL_CXX_SOURCE_FILES)
    else()
      message(STATUS "Proceeding without clang-format target")
    endif()
  endif()

  find_program(CMAKE_FORMAT_PROGRAM cmake-format HINTS ~/.local/bin)
  if(CMAKE_FORMAT_PROGRAM)
    file(GLOB_RECURSE ALL_CMAKE_FILES CMakeLists.txt buildsupport/*.cmake)
    add_custom_target(
      cmake-format COMMAND ${CMAKE_FORMAT_PROGRAM} -c ${PROJECT_SOURCE_DIR}/buildsupport/.cmake-format.txt -i
                           ${ALL_CMAKE_FILES}
    )
    unset(ALL_CMAKE_FILES)
  endif()

  if(${NS3_SANITIZE})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,leak,thread,undefined,memory -g")
  endif()

  if( ${NS3_NATIVE_OPTIMIZATIONS} AND ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU"))
    add_compile_options(-march=native -mtune=native)
  endif()

  if(${NS3_LINK_TIME_OPTIMIZATION})
    # Link-time optimization (LTO) if available
    include(CheckIPOSupported)
    check_ipo_supported(RESULT LTO_AVAILABLE OUTPUT output)
    if(LTO_AVAILABLE)
      set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    else()
      message(WARNING "Link-time optimization (LTO) is not supported: ${output}")
    endif()
  endif()

  if(${NS3_LINK_WHAT_YOU_USE})
    set(CMAKE_LINK_WHAT_YOU_USE TRUE)
  else()
    set(CMAKE_LINK_WHAT_YOU_USE FALSE)
  endif()

  if(${NS3_INCLUDE_WHAT_YOU_USE})
    # beware, it can throw errors for not finding stdc++ headers you may either need to include the system headers path
    # with -I or install clang https://github.com/include-what-you-use/include-what-you-use/issues/679
    find_program(INCLUDE_WHAT_YOU_USE_PROG iwyu)
    if(NOT INCLUDE_WHAT_YOU_USE_PROG)
      message(FATAL_ERROR "iwyu (include-what-you-use) was not found.")
    endif()
    set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${INCLUDE_WHAT_YOU_USE_PROG}) # ;--transitive_includes_only)
  else()
    unset(CMAKE_CXX_INCLUDE_WHAT_YOU_USE)
  endif()

  # Set common include folder (./build/include, where we find ns3/core-module.h)
  include_directories(${CMAKE_OUTPUT_DIRECTORY}/include)

  # find required dependencies
  list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/buildsupport/custom_modules")
  list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/buildsupport/3rd_party")


  # GTK3 Don't search for it if you don't have it installed, as it take an insane amount of time
  if(${NS3_GTK3})
    find_package(GTK3)
    if(NOT ${GTK3_FOUND})
      message(WARNING "GTK3 was not found. Continuing without it.")
    endif()

    find_package(HarfBuzz)
    if(NOT ${HarfBuzz_FOUND})
      message(WARNING "Harfbuzz is required by GTK")
      set(GTK3_FOUND FALSE)
    endif()
  endif()

  if(${NS3_STATIC})
    # This block should either find static versions of libxml2, librt and others or just make sure the dynamic versions
    # don't get used
    set(ENABLE_REALTIME FALSE)
    set(HAVE_RT FALSE)

    # Didn't extensively test these, so I'm disabling them by default
    if(${NS3_BRITE}
       OR ${NS3_CLICK}
       OR ${NS3_OPENFLOW}
       OR ${NS3_MPI}
    )
      message(FATAL_ERROR "Statically linking 3rd party libraries have not been tested."
                          " We are crashing your script to make sure you are aware of that."
      )
    endif()
  else()
    find_package(LibXml2 QUIET)
    if(NOT ${LIBXML2_FOUND})
      message(WARNING "LibXML2 was not found. Continuing without it.")
    else()
      add_definitions(-DHAVE_LIBXML2)
    endif()

    # LibRT
    if(${NS3_REALTIME})
      if(APPLE)
        message(WARNING "Lib RT is not supported on Mac OS X. Continuing without it.")
      else()
        find_library(LIBRT rt QUIET)
        if(NOT ${LIBRT_FOUND})
          message(FATAL_ERROR "LibRT was not found")
          set(ENABLE_REALTIME FALSE)
        else()
          set(ENABLE_REALTIME TRUE)
          set(HAVE_RT TRUE) # for core-config.h
        endif()
      endif()
    endif()
  endif()

  # removing pthreads in favor of C++ threads without proper testing was a bad idea
  if(${NS3_PTHREAD})
    set(THREADS_PREFER_PTHREAD_FLAG)
    find_package(Threads QUIET)
    if(${CMAKE_USE_PTHREADS_INIT})
      include_directories(${THREADS_PTHREADS_INCLUDE_DIR})
      set(NS3_PTHREAD TRUE)
      set(PTHREADS_FOUND TRUE)
      set(HAVE_PTHREAD_H TRUE) # for core-config.h
    else()
      set(NS3_PTHREAD FALSE)
      set(PTHREADS_FOUND FALSE)
    endif()
  endif()

  find_package(Python3 COMPONENTS Interpreter Development)
  if(${NS3_PYTHON_BINDINGS} AND ${Python3_FOUND})
    link_directories(${Python3_LIBRARY_DIRS})
    include_directories(${Python3_INCLUDE_DIRS})
    set(PYTHONDIR ${Python3_SITELIB})
    set(PYTHONARCHDIR ${Python3_SITEARCH})
    set(HAVE_PYEMBED TRUE)
    set(HAVE_PYEXT TRUE)
    set(HAVE_PYTHON_H TRUE)
    set(destination_dir ${CMAKE_OUTPUT_DIRECTORY}/bindings/python/ns)
    file(COPY bindings/python/ns__init__.py DESTINATION ${destination_dir})
    file(RENAME ${destination_dir}/ns__init__.py ${destination_dir}/__init__.py)
  endif()

  if(${NS3_SCAN_PYTHON_BINDINGS})
    # empty scan target that will depend on other module scan targets to scan all of them
    add_custom_target(apiscan-all)
  endif()

  if(${NS3_TESTS})
    add_custom_target(all-test-targets)

    # Create a custom target to run test.py --nowaf
    # Target is also used to produce code coverage output
    add_custom_target(
            run_test_py
            COMMAND ${Python3_EXECUTABLE} test.py --nowaf
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            DEPENDS all-test-targets
    )
    if(${NS3_EXAMPLES})
      include(buildsupport/custom_modules/ns3_coverage.cmake)
    endif()
  endif()

  # Process config-store-config
  configure_file(buildsupport/config-store-config-template.h ${CMAKE_HEADER_OUTPUT_DIRECTORY}/config-store-config.h)

  set(ENABLE_MPI FALSE)
  if(${NS3_MPI})
    find_package(MPI)
    if(NOT ${MPI_FOUND})
      message(WARNING "MPI was not found. Continuing without it.")
    else()
      add_definitions(-DNS3_MPI)
      set(ENABLE_MPI TRUE)
    endif()
  endif()

  if(${NS3_GSL})
    find_package(GSL QUIET)
    if(NOT ${GSL_FOUND})
      message(WARNING "GSL was not found. Continuing without it.")
    endif()
  endif()

  if(${NS3_GNUPLOT})
    find_package(Gnuplot-ios) # Not sure what package would contain the correct header/library
    if(NOT ${GNUPLOT_FOUND})
      message(WARNING "GNUPLOT was not found. Continuing without it.")
    else()
      include_directories(${GNUPLOT_INCLUDE_DIRS})
      link_directories(${GNUPLOT_LIBRARY})
    endif()
  endif()

  if(${NS3_DOCS})
    find_package(Doxygen REQUIRED)
    find_program(DOT dot)
    find_program(DIA dia)
    if((NOT DOT) OR (NOT DIA))
      message(FATAL_ERROR "Dot and Dia are required by Doxygen docs."
                          "They're shipped within the graphviz and dia packages on Ubuntu"
      )
    endif()
    # Get introspected doxygen
    add_custom_target(
      run-print-introspected-doxygen
      COMMAND ${CMAKE_COMMAND} -E env ${CMAKE_OUTPUT_DIRECTORY}/utils/print-introspected-doxygen >
              ${PROJECT_SOURCE_DIR}/doc/introspected-doxygen.h
      DEPENDS print-introspected-doxygen
    )
    add_custom_target(
      run-introspected-command-line
      COMMAND ${CMAKE_COMMAND} -E env NS_COMMANDLINE_INTROSPECTION=".." ${Python3_EXECUTABLE} ./test.py --nowaf
              --constrain=example
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
      DEPENDS all-test-targets # all-test-targets only exists if NS3_TESTS is set to ON
    )

    file(
      WRITE ${PROJECT_SOURCE_DIR}/doc/introspected-command-line.h
      "/* This file is automatically generated by
CommandLine::PrintDoxygenUsage() from the CommandLine configuration
in various example programs.  Do not edit this file!  Edit the
CommandLine configuration in those files instead.
*/
\n"
    )
    add_custom_target(
      assemble-introspected-command-line
      # works on CMake 3.18 or newer > COMMAND ${CMAKE_COMMAND} -E cat
      # ${PROJECT_SOURCE_DIR}/testpy-output/*.command-line >
      # ${PROJECT_SOURCE_DIR}/doc/introspected-command-line.h
      COMMAND ${cat_command} ${PROJECT_SOURCE_DIR}/testpy-output/*.command-line >
              ${PROJECT_SOURCE_DIR}/doc/introspected-command-line.h 2> NULL
      DEPENDS run-introspected-command-line
    )

    add_custom_target(
      doxygen
      COMMAND Doxygen::doxygen ${PROJECT_SOURCE_DIR}/doc/doxygen.conf
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
      DEPENDS run-print-introspected-doxygen assemble-introspected-command-line
    )

    find_package(Sphinx REQUIRED)
    find_program(EPSTOPDF epstopdf)
    find_program(PDFLATEX pdflatex)
    find_program(LATEXMK latexmk)
    find_program(CONVERT convert)
    find_program(DVIPNG dvipng)
    if((NOT EPSTOPDF)
       OR (NOT PDFLATEX)
       OR (NOT LATEXMK)
       OR (NOT CONVERT)
       OR (NOT DVIPNG)
    )
      message(
        FATAL_ERROR
          "Convert, Dvipng, Epstopdf, Pdflatex, Latexmk and fncychap.sty are required by Sphinx docs."
          " They're shipped within the dvipng, imagemagick, texlive, texlive-font-utils and latexmk packages on Ubuntu."
          " Imagemagick may fail due to a security policy issue."
          " https://gitlab.com/nsnam/ns-3-dev/-/blob/master/utils/tests/gitlab-ci-doc.yml#L10-11"
      )
    endif()
    add_custom_target(sphinx COMMENT "Building sphinx documents")

    function(sphinx_target targetname)
      add_custom_target(
        sphinx_${targetname}
        COMMAND make SPHINXOPTS=-N -k html singlehtml latexpdf
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/doc/${targetname}
      )
      add_dependencies(sphinx sphinx_${targetname})
    endfunction()
    sphinx_target(manual)
    sphinx_target(models)
    sphinx_target(tutorial)
  endif()

  # Process core-config
  if(${INT64X64} MATCHES "INT128")
    include(buildsupport/3rd_party/FindInt128.cmake)
    find_int128_types()
    if(UINT128_FOUND)
      set(HAVE___UINT128_T TRUE)
      set(INT64X64_USE_128 TRUE)
    else()
      message(WARNING "Int128 was not found. Falling back to Cairo.")
      set(INT64X64 "CAIRO")
    endif()
  endif()

  if(${INT64X64} MATCHES "CAIRO")
    set(INT64X64_USE_CAIRO TRUE)
  endif()

  if(${INT64X64} MATCHES "DOUBLE")
    # WSLv1 has a long double issue that will result in a few tests failing https://github.com/microsoft/WSL/issues/830
    include(CheckTypeSize)
    check_type_size("double" SIZEOF_DOUBLE)
    check_type_size("long double" SIZEOF_LONG_DOUBLE)

    if(${SIZEOF_LONG_DOUBLE} EQUAL ${SIZEOF_DOUBLE})
      message(
        WARNING
          "Long double has the wrong size: LD ${SIZEOF_LONG_DOUBLE} vs D ${SIZEOF_DOUBLE}. Falling back to CAIRO."
      )
      set(INT64X64 "CAIRO")
    else()
      set(INT64X64_USE_DOUBLE TRUE)
    endif()
  endif()

  include(CheckIncludeFileCXX)
  include(CheckFunctionExists)

  # Check for required headers and functions, set flags if they're found or warn if they're not found
  check_include_file_cxx("stdint.h" "HAVE_STDINT_H")
  check_include_file_cxx("inttypes.h" "HAVE_INTTYPES_H")
  check_include_file_cxx("sys/types.h" "HAVE_SYS_TYPES_H")
  check_include_file_cxx("stat.h" "HAVE_SYS_STAT_H")
  check_include_file_cxx("dirent.h" "HAVE_DIRENT_H")
  check_include_file_cxx("stdlib.h" "HAVE_STDLIB_H")
  check_include_file_cxx("signal.h" "HAVE_SIGNAL_H")
  check_include_file_cxx("netpacket/packet.h" "HAVE_PACKETH")
  check_function_exists("getenv" "HAVE_GETENV")

  configure_file(buildsupport/core-config-template.h ${CMAKE_HEADER_OUTPUT_DIRECTORY}/core-config.h)

  # Enable NS3 logging if requested
  if(${NS3_LOG})
    add_definitions(-DNS3_LOG_ENABLE)
  endif()

  if(${NS3_ASSERT})
    add_definitions(-DNS3_ASSERT_ENABLE)
  endif()

  # Enable examples as tests suites
  if(${NS3_EXAMPLES})
    set(NS3_ENABLE_EXAMPLES "1")
    add_definitions(-DNS3_ENABLE_EXAMPLES -DCMAKE_EXAMPLE_AS_TEST)
  endif()

  set(PLATFORM_UNSUPPORTED_PRE "Platform doesn't support")
  set(PLATFORM_UNSUPPORTED_POST "features. Continuing without them.")
  # Remove from libs_to_build all incompatible libraries or the ones that dependencies couldn't be installed
  if(APPLE
     OR WSLv1
  )
    set(NS3_TAP OFF)
    set(NS3_EMU OFF)
    list(REMOVE_ITEM libs_to_build fd-net-device)
    message(WARNING "${PLATFORM_UNSUPPORTED_PRE} TAP and EMU ${PLATFORM_UNSUPPORTED_POST}")
  endif()

  if(NOT ${NS3_BRITE})
    list(REMOVE_ITEM libs_to_build brite)
  endif()

  if(NOT ${NS3_CLICK})
    list(REMOVE_ITEM libs_to_build click)
  endif()

  if(NOT ${ENABLE_MPI})
    list(REMOVE_ITEM libs_to_build mpi)
  endif()

  if(NOT ${NS3_OPENFLOW})
    list(REMOVE_ITEM libs_to_build openflow)
  endif()

  if(NOT ${NS3_PYTHON_BINDINGS})
    list(REMOVE_ITEM libs_to_build visualizer)
  endif()

  if(NOT ${NS3_TAP})
    list(REMOVE_ITEM libs_to_build tap-bridge)
  endif()

  # Fetch 3rd-party libraries
  if(${NS3_CLICK})
    include(FetchContent)
    FetchContent_Declare(
      click
      GIT_REPOSITORY https://github.com/kohler/click.git
      GIT_TAG 593d10826cf5f945a78307d095ffb0897de515de
    )
    FetchContent_Populate(click)
    file(COPY buildsupport/3rd_party/click_cmakelists.cmake DESTINATION ${click_SOURCE_DIR})
    file(RENAME ${click_SOURCE_DIR}/click_cmakelists.cmake ${click_SOURCE_DIR}/CMakeLists.txt)
    file(COPY buildsupport/3rd_party/click_glue.cc DESTINATION ${click_SOURCE_DIR})
    add_subdirectory(${click_SOURCE_DIR})
    add_definitions(-DNS3_CLICK)
  endif()

  if(${NS3_BRITE})
    include(FetchContent)
    FetchContent_Declare(
      brite
      URL https://code.nsnam.org/index.cgi/BRITE/archive/73badd18f5cd.zip
      URL_HASH MD5=2dbcdd96a99b333a04870d228851db23
    )
    FetchContent_Populate(brite)
    file(COPY buildsupport/3rd_party/brite_cmakelists.cmake DESTINATION ${brite_SOURCE_DIR})
    file(RENAME ${brite_SOURCE_DIR}/brite_cmakelists.cmake ${brite_SOURCE_DIR}/CMakeLists.txt)
    add_subdirectory(${brite_SOURCE_DIR})
    add_definitions(-DENABLE_BRITE)
  endif()

  if(${NS3_OPENFLOW})
    include(FetchContent)
    FetchContent_Declare(
      openflow
      URL https://code.nsnam.org/index.cgi/openflow/archive/4db95a8ea718.zip
      URL_HASH MD5=1b55a0339c3f1f99bd7cbf0ee497d756
    )
    FetchContent_Populate(openflow)
    file(COPY buildsupport/3rd_party/openflow_cmakelists.cmake DESTINATION ${openflow_SOURCE_DIR})
    file(RENAME ${openflow_SOURCE_DIR}/openflow_cmakelists.cmake ${openflow_SOURCE_DIR}/CMakeLists.txt)
    add_subdirectory(${openflow_SOURCE_DIR})
    add_definitions(-DNS3_OPENFLOW -DENABLE_OPENFLOW)
  endif()

  # Create library names to solve dependency problems with macros that will be called at each lib subdirectory
  set(ns3-libs)
  set(ns3-all-libs)
  set(ns3-libs-tests)
  set(ns3-contrib-libs)
  set(lib-ns3-static-objs)
  set(ns3-external-libs)
  set(ns3-python-bindings ns${NS3_VER}-pybindings-${build_type})
  set(ns3-python-bindings-modules)

  foreach(libname ${libs_to_build})
    # Create libname of output library of module
    library_target_name(${libname} targetname)
    set(lib${libname} ${targetname})
    set(lib${libname}-obj ${targetname}-obj)
    list(APPEND ns3_all_libs ${lib${libname}})

    if(NOT (${libname} STREQUAL "test"))
      list(APPEND lib-ns3-static-objs $<TARGET_OBJECTS:${lib${libname}-obj}>)
    endif()
  endforeach()

  if(${NS3_PRECOMPILE_HEADERS})
    set(precompiled_header_libraries
        <iostream>
        <stdlib.h>
        <map>
        <unordered_map>
        <vector>
        <list>
        <algorithm>
        <string>
        <sstream>
        <fstream>
        <cstdlib>
    )
    add_library(stdlib_pch OBJECT ${PROJECT_SOURCE_DIR}/buildsupport/empty.cc)

    set_target_properties(stdlib_pch PROPERTIES POSITION_INDEPENDENT_CODE True)
    target_precompile_headers(stdlib_pch PUBLIC "${precompiled_header_libraries}")

    add_library(stdlib_pch_exec OBJECT ${PROJECT_SOURCE_DIR}/buildsupport/empty_main.cc)
    set_target_properties(stdlib_pch_exec PROPERTIES POSITION_INDEPENDENT_CODE False)
    target_precompile_headers(stdlib_pch_exec PUBLIC "${precompiled_header_libraries}")
  endif()

  # Create new lib for NS3 static builds
  set(lib-ns3-static ns${NS3_VER}-static-${build_type})

  # All contrib libraries can be linked afterwards linking with ${ns3-contrib-libs}
  process_contribution("${contribution_libraries_to_build}")

  # Netanim depends on ns-3 core, so we built it later
  if(${NS3_NETANIM})
    include(FetchContent)
    FetchContent_Declare(
      netanim
      GIT_REPOSITORY https://gitlab.com/nsnam/netanim.git
      GIT_TAG netanim-3.108
    )
    FetchContent_Populate(netanim)
    file(COPY buildsupport/3rd_party/netanim_cmakelists.cmake DESTINATION ${netanim_SOURCE_DIR})
    file(RENAME ${netanim_SOURCE_DIR}/netanim_cmakelists.cmake ${netanim_SOURCE_DIR}/CMakeLists.txt)
    add_subdirectory(${netanim_SOURCE_DIR})
  endif()
endmacro()

function(set_runtime_outputdirectory target_name output_directory)
  get_property(local-ns3-executables GLOBAL PROPERTY ns3-execs)
  set_property(GLOBAL PROPERTY ns3-execs "${local-ns3-executables};${output_directory}${target_name}")

  set_target_properties(${target_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${output_directory})
  if(${XCODE})
    # Is that so hard not to break people's CI, AAPL?? Why would you output the targets to a Debug/Release
    # subfolder? Why?
    foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
      string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
      set_target_properties(${target_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${output_directory})
    endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)
  endif()
endfunction(set_runtime_outputdirectory)


# Import macros used for modules and define specialized versions for src modules
include(buildsupport/custom_modules/ns3_module_macros.cmake)

macro(build_lib libname source_files header_files libraries_to_link test_sources)
  build_lib_impl("src" "${libname}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")
endmacro()

macro(build_lib_example name source_files header_files libraries_to_link)
  build_lib_example_impl("src" "${name}" "${source_files}" "${header_files}" "${libraries_to_link}")
endmacro()

# Contrib modules counterparts of macros above
include(buildsupport/custom_modules/ns3_contributions.cmake)

# Function to fetch 3rd-party contrib modules
include(buildsupport/custom_modules/ns3_store.cmake)

# Macro to build examples in ns-3-dev/examples/
macro(build_example name source_files header_files libraries_to_link)
  # Create shared library with sources and headers
  add_executable(${name} "${source_files}" "${header_files}")

  if(${NS3_STATIC})
    target_link_libraries(${name} ${LIB_AS_NEEDED_PRE_STATIC} ${lib-ns3-static})
  else()
    # Link the shared library with the libraries passed
    target_link_libraries(${name} ${LIB_AS_NEEDED_PRE} ${libraries_to_link} ${LIB_AS_NEEDED_POST})
  endif()

  if(${NS3_PRECOMPILE_HEADERS})
    target_precompile_headers(${name} REUSE_FROM stdlib_pch_exec)
  endif()

  set_runtime_outputdirectory(${name} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/examples/${examplefolder}/)

  if(${NS3_TESTS})
    add_dependencies(all-test-targets ${name})
  endif()
endmacro()

# Waf workaround scripts
include(buildsupport/custom_modules/waf_workaround_c4cache.cmake)
include(buildsupport/custom_modules/waf_workaround_buildstatus.cmake)
include(buildsupport/custom_modules/waf_workaround_lock.cmake)
