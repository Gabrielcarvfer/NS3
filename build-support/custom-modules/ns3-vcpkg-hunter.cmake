# Copyright (c) 2017-2023 Universidade de Brasília
#
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License version 2 as published by the Free
# Software Foundation;
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
# details.
#
# You should have received a copy of the GNU General Public License along with
# this program; if not, write to the Free Software Foundation, Inc., 59 Temple
# Place, Suite 330, Boston, MA  02111-1307  USA
#
# Author: Gabriel Ferreira <gabrielcarvfer@gmail.com>

if(NOT ${NS3_VCPKG})
  function(add_package package_name)
    message(
            STATUS
            "Vcpkg support is not enabled. Skipping the installation of ${package_name}"
    )
  endfunction()
  return()
endif()

set(VCPKG_DIR "${PROJECT_SOURCE_DIR}/vcpkg")
find_package(Git)

if(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
  set(VCPKG_TARGET_ARCH x64)
else()
  set(VCPKG_TARGET_ARCH x86)
endif()

if(WIN32)
  set(VCPKG_EXEC vcpkg.exe)
  set(VCPKG_TRIPLET ${VCPKG_TARGET_ARCH}-windows)
else()
  set(VCPKG_EXEC vcpkg)
  if(NOT APPLE) # LINUX
    set(VCPKG_TRIPLET ${VCPKG_TARGET_ARCH}-linux)
  else()
    set(VCPKG_TRIPLET ${VCPKG_TARGET_ARCH}-osx)
  endif()
endif()

# https://learn.microsoft.com/en-us/vcpkg/users/buildsystems/cmake-integration
set(VCPKG_TARGET_TRIPLET ${VCPKG_TRIPLET})

function(setup_vcpkg)
  message(STATUS "Setting up Vcpkg support")

  # Check if vcpkg was downloaded previously
  if(EXISTS "${VCPKG_DIR}")
    # Vcpkg already downloaded
    message(STATUS "VcPkg folder already exists, skipping git download")
  else()
    if(NOT ${Git_FOUND})
      message(FATAL_ERROR "Git was not found, but it is required by VcPkg")
    endif()
    get_filename_component(VCPKG_PARENT_DIR ${VCPKG_DIR} DIRECTORY)
    execute_process(
            COMMAND ${GIT_EXECUTABLE} clone --depth 1
            https://github.com/microsoft/vcpkg.git
            WORKING_DIRECTORY "${VCPKG_PARENT_DIR}/"
    )
  endif()

  if(${MSVC})

  else()
    # Check if required packages are installed (unzip curl tar)
    if(WIN32)
      find_program(ZIP_PRESENT zip.exe)
      find_program(UNZIP_PRESENT unzip.exe)
      find_program(CURL_PRESENT curl.exe)
      find_program(TAR_PRESENT tar.exe)
    else()
      find_program(ZIP_PRESENT zip)
      find_program(UNZIP_PRESENT unzip)
      find_program(CURL_PRESENT curl)
      find_program(TAR_PRESENT tar)
    endif()

    if(${ZIP_PRESENT} STREQUAL ZIP_PRESENT-NOTFOUND)
      message(FATAL_ERROR "Zip is required for VcPkg, but is not installed")
    endif()

    if(${UNZIP_PRESENT} STREQUAL UNZIP_PRESENT-NOTFOUND)
      message(FATAL_ERROR "Unzip is required for VcPkg, but is not installed")
    endif()

    if(${CURL_PRESENT} STREQUAL CURL_PRESENT-NOTFOUND)
      message(FATAL_ERROR "Curl is required for VcPkg, but is not installed")
    endif()

    if(${TAR_PRESENT} STREQUAL TAR_PRESENT-NOTFOUND)
      message(FATAL_ERROR "Tar is required for VcPkg, but is not installed")
    endif()
  endif()

  # message(WARNING "Checking VCPKG bootstrapping") Check if vcpkg was
  # bootstrapped previously
  if(EXISTS "${VCPKG_DIR}/${VCPKG_EXEC}")
    message(STATUS "VcPkg already bootstrapped")
  else()
    # message(WARNING "Bootstrapping VCPKG")
    set(COMPILER_ENFORCING)

    if(WIN32)
      set(command bootstrap-vcpkg.bat -disableMetrics)
    else()
      # if(NOT APPLE) #linux/bsd
      set(command bootstrap-vcpkg.sh -disableMetrics)
      # else() set(command bootstrap-vcpkg.sh)# --allowAppleClang) endif()
    endif()

    execute_process(
            COMMAND ${COMPILER_ENFORCING} ${VCPKG_DIR}/${command}
            WORKING_DIRECTORY ${VCPKG_DIR}
    )
    # message(STATUS "VCPKG bootstrapped") include_directories(${VCPKG_DIR})
    set(ENV{VCPKG_ROOT} ${VCPKG_DIR})
  endif()

  if(NOT WIN32)
    execute_process(COMMAND chmod +x ${VCPKG_DIR}/${VCPKG_EXEC})
  endif()

  set(CMAKE_PREFIX_PATH
          "${VCPKG_DIR}/installed/${VCPKG_TRIPLET}/;${CMAKE_PREFIX_PATH}"
          PARENT_SCOPE
  )
endfunction()

function(add_package package_name)
  if(NOT ${NS3_VCPKG})
    message(${HIGHLIGHTED_STATUS}
            "Vcpkg support is disabled. Not installing: ${package_name}"
    )
    return()
  endif()
  message(STATUS "${package_name} will be installed")
  execute_process(
          COMMAND ${VCPKG_DIR}/${VCPKG_EXEC} install ${package_name} --triplet
          ${VCPKG_TRIPLET} # comment for easier debugging
  )
  message(STATUS "${package_name} was installed")
endfunction()

setup_vcpkg()
