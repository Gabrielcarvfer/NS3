#Export compile time variable setting the directory to the NS3 root folder
add_definitions(-DPROJECT_SOURCE_PATH="${PROJECT_SOURCE_DIR}")

#Set Linux flag if on Linux
if (UNIX AND NOT APPLE)
    set(LINUX TRUE)
    add_definitions(-D__LINUX__)
endif()

if(APPLE)
    add_definitions(-D__APPLE__)
endif()

if (WIN32)
    add_definitions(-D__WIN32__)
endif()

#Output folders
set(CMAKE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY}/bin)
set(CMAKE_HEADER_OUTPUT_DIRECTORY  ${CMAKE_OUTPUT_DIRECTORY}/ns3)
set(THIRD_PARTY_DIRECTORY ${PROJECT_SOURCE_DIR}/3rd-party)
add_definitions(-DNS_TEST_SOURCEDIR="${CMAKE_OUTPUT_DIRECTORY}/test")
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
link_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

#fPIC and fPIE
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

#When using MinGW, you usually don't want to add your MinGW folder to the path to prevent collisions with other programs
if (WIN32 AND NOT MSVC)
    #If using MSYS2
    set(MSYS2_PATH "E:\\tools\\msys64\\mingw64")
    set(GTK2_GDKCONFIG_INCLUDE_DIR "${MSYS2_PATH}\\include\\gtk-2.0")
    set(GTK2_GLIBCONFIG_INCLUDE_DIR "${MSYS2_PATH}\\include\\gtk-2.0")
    set(QT_QMAKE_EXECUTABLE "${MSYS2_PATH}\\bin\\qmake.exe")
    set(QT_RCC_EXECUTABLE   "${MSYS2_PATH}\\bin\\rcc.exe")
    set(QT_UIC_EXECUTABLE   "${MSYS2_PATH}\\bin\\uic.exe")
    set(QT_MOC_EXECUTABLE   "${MSYS2_PATH}\\bin\\moc.exe")
    set(QT_MKSPECS_DIR      "${MSYS2_PATH}\\share\\qt4\\mkspecs")
    set(ENV{PATH} "$ENV{PATH};${MSYS2_PATH}\\bin;")          #contains std libraries
    set(ENV{PATH} "$ENV{PATH};${MSYS2_PATH}\\..\\usr\\bin;") #contains unzip required for Vcpkg
    #set(ENV{PATH} "$ENV{PATH}${MSYS2_PATH}\\lib;")
    #set(ENV{PATH} "$ENV{PATH}${CMAKE_LIBRARY_OUTPUT_DIRECTORY};")
    #set(ENV{PATH} "$ENV{PATH}${CMAKE_RUNTIME_OUTPUT_DIRECTORY};")
endif()

#Include the cmake file that provides a Hunter-like interface to VcPkg
include(buildsupport/vcpkg_hunter.cmake)



#If on Linux, add cotire for PCH builds. Others were having issues, so I disabled them
if(LINUX)
    #include(buildsupport/cotire.cmake)
	#include(buildsupport/cotire_force_pch.cmake)
endif()


if (COMMAND cotire)
    #If cotire is active and ccache is found, set its flags to prevent issue with pch and unity builds
    if (CCACHE_FOUND)
        set(ENV{CCACHE_SLOPPINESS} "pch_defines,time_macros")
    endif()
else()
    #If cotire is disabled, check if OpenMp is available
    find_package(OpenMP)
    if(OpenMP_CXX_FOUND)
        link_libraries(OpenMP::OpenMP_CXX)
    endif()
endif()

#Check the number of threads
include(ProcessorCount)
ProcessorCount(NumThreads)


#Set compiler options and get command to force unused function linkage (useful for libraries)
set(LIB_AS_NEEDED_PRE  )
set(LIB_AS_NEEDED_POST )
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU" AND NOT APPLE)
    # using GCC
    set(LIB_AS_NEEDED_PRE  -Wl,--no-as-needed)
    set(LIB_AS_NEEDED_POST -Wl,--as-needed   )
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Intel")
    # using Intel C++
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
    # using Visual Studio C++
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
    set(CMAKE_MSVC_PARALLEL ${NumThreads})
endif()

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" AND APPLE)
    # using Clang
    #set(LIB_AS_NEEDED_PRE -all_load)
    set(LIB_AS_NEEDED_POST   )
endif()


macro(fetch_git_submodule submodule_path)
    if(NOT EXISTS "${PROJECT_SOURCE_DIR}/${submodule_path}/.git")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule --init ${PROJECT_SOURCE_DIR}/${submodule_path}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodule ${submodule_path}")
        endif()
    endif()
endmacro()

macro(SUBDIRLIST result curdir)
    file(GLOB children RELATIVE ${curdir} ${curdir}/*)
    set(dirlist "")
    foreach(child ${children})
        if(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
        endif()
    endforeach()
    set(${result} ${dirlist})
endmacro()

#process all options passed in main cmakeLists
macro(process_options)
    #process debug switch
    #Used in build-profile-test-suite
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
        set(build_type "minsizerel")
    endif()

    if(${NS3_TESTS})
        enable_testing()
    endif()

    #Set common include folder
    include_directories(${CMAKE_OUTPUT_DIRECTORY})
    #link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    #link_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

    #Add a hunter-like interface to Vcpkg
    if (${AUTOINSTALL_DEPENDENCIES})
        setup_vcpkg()
        include(${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake)
    endif()

    #Copy all header files to outputfolder/include/
    file(GLOB_RECURSE include_files ${PROJECT_SOURCE_DIR}/src/*.h) #just copying every single header into ns3 include folder
    file(COPY ${include_files} DESTINATION ${CMAKE_HEADER_OUTPUT_DIRECTORY})

    #Load GIT to fetch required submodules
    find_package(Git QUIET)

    #Process Brite 3rd-party submodule and dependencies
    if(${NS3_BRITE})
        if(WIN32 OR APPLE)
            set(${NS3_BRITE} OFF)
            message(WARNING "Not building brite on Windows/Mac")
        else()
            fetch_git_submodule("3rd-party/brite")
            list(APPEND 3rd_party_libraries_to_build brite)
        endif()
    endif()

    if(${NS3_CLICK})
        if(WIN32 OR APPLE)
            set(${NS3_CLICK} OFF)
            message(WARNING "Not building click on Windows/Mac")
        else()
            fetch_git_submodule("3rd-party/click")
            configure_file(${PROJECT_SOURCE_DIR}/3rd-party/ClickCMakeLists.txt ${PROJECT_SOURCE_DIR}/3rd-party/click/CMakeLists.txt COPYONLY)
            list(APPEND 3rd_party_libraries_to_build click)
        endif()
    endif()

    #LibXml2
    if(${NS3_LIBXML2} OR ${NS3_OPENFLOW})
        find_package(LibXml2)
        if(NOT ${LIBXML2_FOUND})
            if (NOT ${AUTOINSTALL_DEPENDENCIES})
                message(FATAL_ERROR "LibXML2 ${NOT_FOUND_MSG}")
            else()
                #If we don't find installed, install
                add_package (libxml2)
                find_package(LibXml2)
            endif()
        endif()
        link_directories(${LIBXML2_LIBRARY_DIRS})
        include_directories(${LIBXML2_INCLUDE_DIR})
        #add_definitions(${LIBXML2_DEFINITIONS})
    endif()
    
    #Process Openflow 3rd-party submodule and dependencies
    if(${NS3_OPENFLOW})
        if(WIN32)
            set(${NS3_OPENFLOW} OFF)
            message(WARNING "Not building brite on Windows")
        else()
            fetch_git_submodule("3rd-party/openflow")
            list(APPEND 3rd_party_libraries_to_build openflow)
        endif()
    endif()

    #Process ns3 Openflow module and dependencies
    set(OPENFLOW_REQUIRED_BOOST_LIBRARIES)

    if(${NS3_OPENFLOW})
        set(OPENFLOW_REQUIRED_BOOST_LIBRARIES
                system
                signals
                filesystem
                static-assert
                config
                )
        include_directories(${PROJECT_SOURCE_DIR}/3rd-party/openflow/include)
        #if (WIN32)
        set(OPENFLOW_LIBRARIES openflow)
        #else()
        #    set(OPENFLOW_LIBRARIES libopenflow.a)
        #endif()
        set(OPENFLOW_FOUND TRUE)
    endif()


    if(${NS3_BOOST})
        #find_package(Boost)
        #if(NOT ${BOOST_FOUND})
        if (NOT ${AUTOINSTALL_DEPENDENCIES})
            message(FATAL_ERROR "BoostC++ ${NOT_FOUND_MSG}")
        else()
            #add_package(boost) #this will install all the boost libraries and was a bad idea

            set(requiredBoostLibraries
                    ${OPENFLOW_REQUIRED_BOOST_LIBRARIES}
                    )

            #Holds libraries to link later
            set(BOOST_LIBRARIES
                    )
            set(BOOST_INCLUDES
                    )

            #For each of the required boost libraries
            foreach(requiredBoostLibrary ${requiredBoostLibraries})
                set(boostLib boost-${requiredBoostLibrary})
                add_package(${boostLib})
                get_property(${boostLib}_dir GLOBAL PROPERTY DIR_${boostLib})
                #include_directories(${boostLib}/include) #damned Boost-assert undefines assert, causing all sorts of problems with Brite
                list(APPEND BOOST_INCLUDES ${${boostLib}_dir}/include) #add BOOST_INCLUDES per target to avoid collisions

                #Some boost libraries (e.g. static-assert) don't have an associated library
                if (EXISTS ${${boostLib}_dir}/lib)
                    link_directories(${${boostLib}_dir}/lib)

                    if (WIN32)
                        list(APPEND BOOST_LIBRARIES libboost_${requiredBoostLibrary})
                    else()
                        list(APPEND BOOST_LIBRARIES libboost_${requiredBoostLibrary}.a)
                    endif()
                endif()
            endforeach()


            set(BOOST_FOUND TRUE)
        endif()
        #else()
        #    link_directories(${BOOST_LIBRARY_DIRS})
        #    include_directories( ${BOOST_INCLUDE_DIR})
        #endif()
    endif()



    #PyTorch still need some fixes on Windows
    if(WIN32 AND ${NS3_PYTORCH})
        message(WARNING "Libtorch linkage on Windows still requires some fixes. The build will continue without it.")
        set(NS3_PYTORCH OFF)
    endif()

    #Set C++ standard
    if(${NS3_PYTORCH})
        set(CMAKE_CXX_STANDARD 11) #c++17 for inline variables in Windows
        set(CMAKE_CXX_STANDARD_REQUIRED OFF) #ABI requirements for PyTorch affect this
        add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0 -Dtorch_EXPORTS -DC10_BUILD_SHARED_LIBS -DNS3_PYTORCH)
    else()
        set(CMAKE_CXX_STANDARD 11) #c++17 for inline variables in Windows
        set(CMAKE_CXX_STANDARD_REQUIRED ON)
    endif()

    if(${NS3_SANITIZE})
        #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,leak,thread,undefined,memory -g")
    endif()


    #find required dependencies
    list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/buildsupport/custom_modules")

    set(NOT_FOUND_MSG  "is required and couldn't be found")

    #Libpcre2 for regex
    include(${PROJECT_SOURCE_DIR}/buildsupport/custom_modules/FindPCRE.cmake)
    find_package(PCRE)
    if (NOT ${AUTOINSTALL_DEPENDENCIES})
        message(WARNING "PCRE2 ${NOT_FOUND_MSG}. Rocketfuel topology reader wont be built")
    else()
        #If we don't find installed, install
        add_package(pcre2)
        find_package(PCRE)
        include_directories(${PCRE_INCLUDE_DIRS})
    endif()





    #GTK2
    # Don't search for it if you don't have it installed, as it take an insane amount of time
    if(${NS3_GTK2})
        find_package(GTK2)
        if(NOT ${GTK2_FOUND})
            if (NOT ${AUTOINSTALL_DEPENDENCIES})
                message(FATAL_ERROR "LibGTK2 ${NOT_FOUND_MSG}")
            else()
                #todo
            endif()
        else()
            link_directories(${GTK2_LIBRARY_DIRS})
            include_directories( ${GTK2_INCLUDE_DIRS})
            add_definitions(${GTK2_CFLAGS_OTHER})
        endif()
    endif()



    #LibRT
    if(${NS3_REALTIME})
        if(WIN32 OR APPLE)
            message(WARNING "Lib RT is not supported on Windows/Mac OS X, building without it")
        else()
            find_library(LIBRT rt)
            if(NOT ${LIBRT_FOUND})
                message(FATAL_ERROR LibRT not found)
            else()
                link_libraries(rt)
                add_definitions(-DHAVE_RT)
                set(HAVE_RT TRUE) # for core-config.h
            endif()
        endif()
    endif()

    #removing pthreads in favor of C++ threads without proper testing was a bad idea
    if(${NS3_PTHREAD})
        set(THREADS_PREFER_PTHREAD_FLAG)
        find_package(Threads REQUIRED)
        if(NOT ${THREADS_FOUND})
            message(FATAL_ERROR Thread library not found)
        else()
            include_directories(${THREADS_PTHREADS_INCLUDE_DIR})
            set(THREADS_FOUND TRUE)
            link_libraries(${CMAKE_THREAD_LIBS_INIT})
            set(HAVE_PTHREAD_H TRUE) # for core-config.h
        endif()
    endif()


    if(${NS3_PYTHON})
         find_package (Python2 COMPONENTS Interpreter Development)


         link_directories(${Python2_LIBRARY_DIRS})
         include_directories( ${Python2_INCLUDE_DIRS})

         if(Python2::Python)
             set(PYTHONDIR TRUE)
             set(PYTHONDIR_STRING Python2_SITELIB)
             set(PYTHONARCHDIR TRUE)
             set(PYTHONARCHDIR_STRING Python2_SITEARCH)
             set(HAVE_PYEMBED  TRUE)
             set(HAVE_PYEXT    TRUE)
             set(HAVE_PYTHON_H TRUE)
         endif()
    endif()
    #Process config-store-config
    configure_file(buildsupport/config-store-config-template.h ${CMAKE_HEADER_OUTPUT_DIRECTORY}/config-store-config.h)


    if(${NS3_MPI})
        find_package(MPI)
        if(NOT ${MPI_FOUND})
            message(FATAL_ERROR "MPI not found")
        else()
            include_directories( ${MPI_CXX_INCLUDE_PATH}) 
            add_definitions(${MPI_CXX_COMPILE_FLAGS} ${MPI_CXX_LINK_FLAGS} -DNS3_MPI) 
            link_libraries(${MPI_CXX_LIBRARIES}) 
            #set(CMAKE_CXX_COMPILER ${MPI_CXX_COMPILER}) 
        endif()
    endif()

    if(${NS3_GSL})
        #message(FATAL_ERROR GSL not found)
        #If we don't find installed, install
        add_package (gsl)
        get_property(gsl_dir GLOBAL PROPERTY DIR_gsl)
        link_directories(${gsl_dir}/lib)
        include_directories(${gsl_dir}/include)
        set(GSL_LIBRARIES gsl gslcblas)
        set(GSL_FOUND)
    endif()

    if (${NS3_NETANIM})
        find_package(Qt4 COMPONENTS QtGui )
        find_package(Qt5 COMPONENTS Core Widgets PrintSupport Gui )

        if((NOT ${Qt4_FOUND}) AND (NOT ${Qt5_FOUND}))
            message(ERROR You need Qt installed to build NetAnim. Continuing without it.)
            set(NS3_NETANIM OFF)
        else()
            if(MSVC)
                set(${NS3_NETANIM} OFF)
                message(WARNING "Not building netanim with MSVC")
            else()
                fetch_git_submodule("3rd-party/netanim")
                list(APPEND 3rd_party_libraries_to_build netanim)
            endif()
        endif()
    endif()

    if(${NS3_PYTORCH})
        #Decide which version of libtorch should be downloaded.
        #If you change the build_type, remember to download both libtorch folder and libtorch.zip to redownload the appropriate version
        if(WIN32)
            if(${build_type} STREQUAL "rel")
                set(libtorch_url https://download.pytorch.org/libtorch/cpu/libtorch-win-shared-with-deps-latest.zip)
            else()
                set(libtorch_url https://download.pytorch.org/libtorch/cpu/libtorch-win-shared-with-deps-debug-latest.zip)
            endif()
        elseif(APPLE)
            set(libtorch_url https://download.pytorch.org/libtorch/cpu/libtorch-macos-latest.zip)
        else()
            set(libtorch_url https://download.pytorch.org/libtorch/cpu/libtorch-shared-with-deps-latest.zip)
        endif()

        #Define executables to download and unzip libtorch archive
        if (WIN32)
            set(CURL_EXE curl.exe)
            if(MSVC)
                set(UNZIP_EXE  powershell expand-archive)
                set(UNZIP_POST .\\)
            else()
                set(UNZIP_EXE unzip.exe)
                set(UNZIP_POST )
            endif()
        else()
            set(CURL_EXE curl)
            set(UNZIP_EXE unzip)
            set(UNZIP_POST )
        endif()

        #Download libtorch archive if not already downloaded
        if (EXISTS ${THIRD_PARTY_DIRECTORY}/libtorch.zip)
            message(STATUS "Libtorch already downloaded")
        else()
            message(STATUS "Downloading libtorch files ${libtorch_url}")
            execute_process(COMMAND ${CURL_EXE} ${libtorch_url} --output libtorch.zip
                WORKING_DIRECTORY ${THIRD_PARTY_DIRECTORY})
        endif()

        #Extract libtorch.zip into the libtorch folder
        if (EXISTS ${THIRD_PARTY_DIRECTORY}/libtorch)
            message(STATUS "Libtorch folder already unzipped")
        else()
            message(STATUS "Unzipping libtorch files")
            execute_process(COMMAND ${UNZIP_EXE} libtorch.zip ${UNZIP_POST}
                WORKING_DIRECTORY ${THIRD_PARTY_DIRECTORY})
        endif()

        #Append the libtorch cmake folder to the CMAKE_PREFIX_PATH (enables FindTorch.cmake)
        list(APPEND CMAKE_PREFIX_PATH "${THIRD_PARTY_DIRECTORY}/libtorch/share/cmake")

        #Torch automatically includes the GNU ABI thing that causes problems (look for PYTORCH references above)
        set(backup_cxx_flags ${CMAKE_CXX_FLAGS})
        find_package(Torch REQUIRED)
        set(CMAKE_CXX_FLAGS ${backup_cxx_flags})

        #Include the libtorch includes and libraries folders
        include_directories(${TORCH_INCLUDE_DIRS})
        link_directories(${THIRD_PARTY_DIRECTORY}/libtorch/lib)

        #Torch flags may cause problems to other libraries, so undo them (TorchConfig.cmake)
        set(TORCH_CXX_FLAGS)
        set_property(TARGET torch PROPERTY INTERFACE_COMPILE_OPTIONS)
    endif()

    if(${NS3_GNUPLOT})
        find_package(Gnuplot-ios)
        if(NOT ${GNUPLOT_FOUND})
            message(FATAL_ERROR GNUPLOT not found)
        else()
            include_directories(${GNUPLOT_INCLUDE_DIRS})
            link_directories(${GNUPLOT_LIBRARY})
        endif()
    endif()

    #add_package(eigen3)
    #get_property(eigen3_dir GLOBAL PROPERTY DIR_eigen3)
    #include_directories(${eigen3_dir}/include)



    #Process core-config
    set(INT64X64 "128")

    if(INT64X64 STREQUAL "128")
        include(buildsupport/custom_modules/FindInt128.cmake)
        FIND_INT128_TYPES()
        if(UINT128_FOUND)
            set(HAVE___UINT128_T TRUE)
            set(INT64X64_USE_128 TRUE)
        else()
            message(WARNING "Int128 not found. Falling back to long double.")
            set(INT64X64 "DOUBLE")
        endif()
    elseif(INT64X64 STREQUAL "DOUBLE")
        #WSLv1 has a long double issue that will result in at least 5 tests crashing https://github.com/microsoft/WSL/issues/830
        include(CheckTypeSize)
        CHECK_TYPE_SIZE("double" SIZEOF_DOUBLE)
        CHECK_TYPE_SIZE("long double" SIZEOF_LONG_DOUBLE)
        if (${SIZEOF_LONG_DOUBLE} EQUAL ${SIZEOF_DOUBLE})
            message(WARNING "Long double has the wrong size: LD ${SIZEOF_LONG_DOUBLE} vs D ${SIZEOF_DOUBLE}. Falling back to CAIRO.")
            set(INT64X64 "CAIRO")
        else()
            set(INT64X64_USE_DOUBLE TRUE)
        endif()
    elseif(INT64X64 STREQUAL "CAIRO")
        set(INT64X64_USE_CAIRO TRUE)
    else()
        message(FATAL_ERROR "Try another int64x64 implementation")
        set(INT64X64)
    endif()

    include(CheckIncludeFileCXX)
    include(CheckFunctionExists)

    #Check for required headers and functions, set flags if they're found or warn if they're not found
    check_include_file_cxx("stdint.h"    "HAVE_STDINT_H"   )
    check_include_file_cxx("inttypes.h"  "HAVE_INTTYPES_H" )
    check_include_file_cxx("sys/types.h" "HAVE_SYS_TYPES_H")
    check_include_file_cxx("stat.h"      "HAVE_SYS_STAT_H" )
    check_include_file_cxx("dirent.h"    "HAVE_DIRENT_H"   )
    check_include_file_cxx("stdlib.h"    "HAVE_STDLIB_H"   )
    check_include_file_cxx("signal.h"    "HAVE_SIGNAL_H"   )
    check_function_exists ("getenv"      "HAVE_GETENV"     )

    configure_file(buildsupport/core-config-template.h ${CMAKE_HEADER_OUTPUT_DIRECTORY}/core-config.h)

    #Enable NS3 logging if requested
    if(${NS3_LOG})
        add_definitions(-DNS3_LOG_ENABLE)
    endif()


    #Remove from libs_to_build all incompatible libraries or the ones that dependencies couldn't be installed
    if(MSVC)
        set(NS3_NETANIM OFF)
        list(REMOVE_ITEM libs_to_build netanim)
    endif()

    if(NOT ${NS3_OPENFLOW})
        list(REMOVE_ITEM libs_to_build openflow)
    endif()

    if(NOT ${NS3_PYTHON})
        list(REMOVE_ITEM libs_to_build visualizer)
    endif()

    if(NOT ${NS3_BRITE})
        list(REMOVE_ITEM libs_to_build brite)
    endif()

    if (WIN32 OR APPLE)
        if(${NS3_BRITE})
            set(NS3_BRITE OFF)
            list(REMOVE_ITEM libs_to_build brite)
        endif()
        list(REMOVE_ITEM libs_to_build fd-net-device)
        list(REMOVE_ITEM libs_to_build tap-bridge)
    endif()

    #Create library names to solve dependency problems with macros that will be called at each lib subdirectory
    set(ns3-libs )
    set(ns3-libs-tests )
    set(ns3-contrib-libs )
    set(lib-ns3-static-objs)
    set(ns3-python-bindings ns${NS3_VER}-pybindings-${build_type})
    set(ns3-python-bindings-modules )

    foreach(libname ${libs_to_build})
        #Create libname of output library of module
        set(lib${libname} ns${NS3_VER}-${libname}-${build_type})
        set(lib${libname}-obj ns${NS3_VER}-${libname}-${build_type}-obj)
        #list(APPEND ns3-libs ${lib${libname}})

        if( NOT (${libname} STREQUAL "test") )
            list(APPEND lib-ns3-static-objs $<TARGET_OBJECTS:${lib${libname}-obj}>)
        endif()

    endforeach()

    #Create new lib for NS3 static builds
    set(lib-ns3-static ns${NS3_VER}-static-${build_type})

    #string (REPLACE ";" " " libs_to_build_txt "${libs_to_build}")
    #add_definitions(-DNS3_MODULES_PATH=${libs_to_build_txt})

    #Dump definitions for later use
    get_directory_property( ADDED_DEFINITIONS COMPILE_DEFINITIONS )
    file(WRITE ${CMAKE_HEADER_OUTPUT_DIRECTORY}/ns3-definitions "${ADDED_DEFINITIONS}")

    #All contrib libraries can be linked afterwards linking with ${ns3-contrib-libs}
    process_contribution("${contribution_libraries_to_build}")
endmacro()

macro (write_module_header name header_files)
    string(TOUPPER ${name} uppercase_name)
    string(REPLACE "-" "_" final_name ${uppercase_name} )
    #Common module_header
    list(APPEND contents "#ifdef NS3_MODULE_COMPILATION ")
    list(APPEND contents  "
    error \"Do not include ns3 module aggregator headers from other modules; these are meant only for end user scripts.\" ")
    list(APPEND contents  "
#endif ")
    list(APPEND contents "
#ifndef NS3_MODULE_")
    list(APPEND contents ${final_name})
    list(APPEND contents "
    // Module headers: ")

    #Write each header listed to the contents variable
    foreach(header ${header_files})
        get_filename_component(head ${header} NAME)
        list(APPEND contents
                "
    #include <ns3/${head}>")
        ##include \"ns3/${head}\"")
    endforeach()

    #Common module footer
    list(APPEND contents "
#endif ")
    file(WRITE ${CMAKE_HEADER_OUTPUT_DIRECTORY}/${name}-module.h ${contents})
endmacro()


macro (build_lib libname source_files header_files libraries_to_link test_sources)

    #Create object library with sources and headers, that will be used in lib-ns3-static and the shared library
    add_library(${lib${libname}-obj} OBJECT "${source_files}" "${header_files}")

    GET_PROPERTY(local-ns3-libs GLOBAL PROPERTY ns3-libs)
    set_property(GLOBAL PROPERTY ns3-libs "${local-ns3-libs};${lib${libname}}")

    if (COMMAND cotire)
        cotire(${lib${libname}-obj})
    endif()

    #Create shared library with previously created object library (saving compilation time)
    add_library(${lib${libname}} SHARED $<TARGET_OBJECTS:${lib${libname}-obj}>)

    #Link the shared library with the libraries passed
    target_link_libraries(${lib${libname}} ${LIB_AS_NEEDED_PRE} "${libraries_to_link}" ${LIB_AS_NEEDED_POST})

    if(MSVC)
        target_link_options(${lib${libname}} PUBLIC /OPT:NOREF)
    endif()

    #Write a module header that includes all headers from that module
    write_module_header("${libname}" "${header_files}")

    #Build tests if requested
    if(${NS3_TESTS})
        list(LENGTH test_sources test_source_len)
        if (${test_source_len} GREATER 0)
            #Create libname of output library test of module
            set(test${libname} ns${NS3_VER}-${libname}-test-${build_type} CACHE INTERNAL "" FORCE)

            if (WIN32)
                set(ns3-libs-tests ${ns3-libs-tests} $<TARGET_OBJECTS:${test${libname}}> CACHE INTERNAL "" FORCE)

                #Create shared library containing tests of the module
                add_library(${test${libname}} OBJECT "${test_sources}")
            else()
                set(ns3-libs-tests ${ns3-libs-tests} ${test${libname}} CACHE INTERNAL "" FORCE)

                #Create shared library containing tests of the module
                add_library(${test${libname}} SHARED "${test_sources}")

                #Link test library to the module library
                target_link_libraries(${test${libname}} ${LIB_AS_NEEDED_PRE} ${lib${libname}} "${libraries_to_link}" ${LIB_AS_NEEDED_POST})
            endif()

            if (COMMAND cotire)
                cotire(${test${libname}})
            endif()

        endif()
    endif()

    #Build lib examples if requested
    if(${NS3_EXAMPLES})
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/examples)
            add_subdirectory(examples)
        endif()
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/example) 
            add_subdirectory(example) 
        endif() 
    endif()

    #Build pybindings if requested and if bindings subfolder exists in NS3/src/libname
    if(${NS3_PYTHON} AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/bindings")
        set(arch gcc_LP64)#ILP32)
        #todo: fix python module names, output folder and missing links
        set(module_src ns3module.cc)
        set(module_hdr ns3module.h)

        string(REPLACE "-" "_" libname_sub input) # - causes problems (e.g. csma-layout) causes problems, rename to _ (e.g. csma_layout)

        set(modulegen_modular_command  python2 ${CMAKE_SOURCE_DIR}/bindings/python/ns3modulegen-modular.py ${CMAKE_CURRENT_SOURCE_DIR} ${arch} ${libname_sub} ${CMAKE_CURRENT_SOURCE_DIR}/bindings/${module_src})
        set(modulegen_arch_command python2 ${CMAKE_CURRENT_SOURCE_DIR}/bindings/modulegen__${arch}.py 2> ${CMAKE_CURRENT_SOURCE_DIR}/bindings/ns3modulegen.log)

        execute_process(
                COMMAND ${CMAKE_COMMAND} -E env PYTHONPATH=${CMAKE_OUTPUT_DIRECTORY} ${modulegen_modular_command}
                COMMAND ${CMAKE_COMMAND} -E env PYTHONPATH=${CMAKE_OUTPUT_DIRECTORY} ${modulegen_arch_command}
                TIMEOUT 60
                #WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                #OUTPUT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/bindings/${module_src}
                RESULT_VARIABLE res
                OUTPUT_QUIET
                ERROR_QUIET
        )

        #message(WARNING ${res})

        set(python_module_files ${CMAKE_CURRENT_SOURCE_DIR}/bindings/${module_hdr} ${CMAKE_CURRENT_SOURCE_DIR}/bindings/${module_src})
        if(${libname} STREQUAL "core")
            list(APPEND python_module_files ${CMAKE_CURRENT_SOURCE_DIR}/bindings/module_helpers.cc ${CMAKE_CURRENT_SOURCE_DIR}/bindings/scan-header.h)
        endif()

        #message(WARNING ${python_module_files})
        add_library(ns3module_${libname} OBJECT "${python_module_files}")
        set(ns3-python-bindings-modules ${ns3-python-bindings-modules} $<TARGET_OBJECTS:ns3module_${libname}> CACHE INTERNAL "" FORCE)
    endif()
endmacro()

macro (build_example name source_files header_files libraries_to_link)
    #Create shared library with sources and headers
    add_executable(${name} "${source_files}" "${header_files}")

    if (COMMAND cotire)
        cotire(${name})
    endif()

    #Link the shared library with the libraries passed
    target_link_libraries(${name}  ${LIB_AS_NEEDED_PRE} ${libraries_to_link} ${LIB_AS_NEEDED_POST})

    set_target_properties( ${name}
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/examples/${examplename}
            )
    if(WIN32)
        #Windows require this workaround to make sure the DLL files are located
        add_test(NAME ctest-${name}
                COMMAND ${CMAKE_COMMAND} -E env "PATH=$ENV{PATH};${CMAKE_RUNTIME_OUTPUT_DIRECTORY};${CMAKE_LIBRARY_OUTPUT_DIRECTORY}" ${name}
                WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/examples/${libname}/)
    else()
        add_test(NAME ctest-${name}
                COMMAND ${name}
                WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/examples/${libname}/)
    endif()
endmacro()

macro (build_lib_example name source_files header_files libraries_to_link files_to_copy)
    #Create shared library with sources and headers
    add_executable(${name} "${source_files}" "${header_files}")

    if (COMMAND cotire)
        cotire(${name})
    endif()

    #Link the shared library with the libraries passed
    target_link_libraries(${name} ${LIB_AS_NEEDED_PRE} ${lib${libname}} ${libraries_to_link} ${LIB_AS_NEEDED_POST})

    set_target_properties( ${name}
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/examples/${libname}
            )

    file(COPY ${files_to_copy} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/examples/${libname})

    if(WIN32)
        #Windows require this workaround to make sure the DLL files are located
        add_test(NAME ctest-${name}
                COMMAND ${CMAKE_COMMAND} -E env "PATH=$ENV{PATH};${CMAKE_RUNTIME_OUTPUT_DIRECTORY};${CMAKE_LIBRARY_OUTPUT_DIRECTORY}" ${name}
                WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/examples/${libname}/)
    else()
        add_test(NAME ctest-${name}
                COMMAND ${name}
                WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/examples/${libname}/)
    endif()
endmacro()

#Add contributions macros
include(buildsupport/contributions.cmake)
