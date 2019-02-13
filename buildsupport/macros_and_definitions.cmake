include(buildsupport/vcpkg_hunter.cmake)


if (WIN32 AND NOT MSVC)
    #If using MSYS2
    set(MSYS2_PATH "C:\\tools\\msys64\\mingw64")
    set(GTK2_GDKCONFIG_INCLUDE_DIR "${MSYS2_PATH}\\include\\gtk-2.0")
    set(GTK2_GLIBCONFIG_INCLUDE_DIR "${MSYS2_PATH}\\include\\gtk-2.0")
    set(QT_QMAKE_EXECUTABLE "${MSYS2_PATH}\\bin\\qmake.exe")
    set(QT_RCC_EXECUTABLE   "${MSYS2_PATH}\\bin\\rcc.exe")
    set(QT_UIC_EXECUTABLE   "${MSYS2_PATH}\\bin\\uic.exe")
    set(QT_MOC_EXECUTABLE   "${MSYS2_PATH}\\bin\\moc.exe")
    set(QT_MKSPECS_DIR      "${MSYS2_PATH}\\share\\qt4\\mkspecs")
endif()

#Fixed definitions
#unset(CMAKE_LINK_LIBRARY_SUFFIX)

#Output folders
set(CMAKE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY}/bin)
set(CMAKE_HEADER_OUTPUT_DIRECTORY  ${CMAKE_OUTPUT_DIRECTORY}/ns3)
#add_definitions(-DNS_TEST_SOURCEDIR="${CMAKE_OUTPUT_DIRECTORY}/test")
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
link_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

#fPIC 
set(CMAKE_POSITION_INDEPENDENT_CODE ON) 


set(LIB_AS_NEEDED_PRE  )
set(LIB_AS_NEEDED_POST )


include(ProcessorCount)
ProcessorCount(NumThreads)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # using Clang
    set(LIB_AS_NEEDED_PRE -Wl,-all_load)
    set(LIB_AS_NEEDED_POST             )
    set(CMAKE_MAKE_PROGRAM "${CMAKE_MAKE_PROGRAM} -j${NumThreads}")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # using GCC
    set(LIB_AS_NEEDED_PRE  -Wl,--no-as-needed)
    set(LIB_AS_NEEDED_POST -Wl,--as-needed   )
    set(CMAKE_MAKE_PROGRAM "${CMAKE_MAKE_PROGRAM} -j${NumThreads}")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    # using Intel C++
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # using Visual Studio C++
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
    set(CMake_MSVC_PARALLEL ${NumThreads})
endif()

#Used in build-profile-test-suite
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_definitions(-DNS3_BUILD_PROFILE_DEBUG)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
    add_definitions(-DNS3_BUILD_PROFILE_RELEASE)
else(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_definitions(-DNS3_BUILD_PROFILE_OPTIMIZED)
endif()


#3rd party libraries with sources shipped in 3rd-party folder
set(3rdPartyLibraries
        netanim
        brite
        openflow
        )


#process all options passed in main cmakeLists
macro(process_options)

    #Copy all header files to outputfolder/include/
    file(GLOB_RECURSE include_files ${PROJECT_SOURCE_DIR}/src/*.h) #just copying every single header into ns3 include folder
    file(COPY ${include_files} DESTINATION ${CMAKE_HEADER_OUTPUT_DIRECTORY})


    #Don't build incompatible libraries on Windows
    if (WIN32)
        set(build_lib_brite)
        set(build_lib_openflow)
    else()
        set(build_lib_brite brite)
        set(build_lib_openflow openflow)
    endif()

    #3rd party libraries with sources shipped in 3rd-party folder
    set(3rdPartyLibraries
            netanim
            ${build_lib_brite}
            ${build_lib_openflow}
            )

    #Add 3rd-party library headers to include directories
    foreach(3rdPartyLibrary ${3rdPartyLibraries})
        #file(GLOB_RECURSE include_files ${PROJECT_SOURCE_DIR}/3rd-party/${3rdPartyLibrary}/*.h) #just copying every single header from 3rd party libraries into ns3 include folder
        #file(COPY ${include_files} DESTINATION ${CMAKE_HEADER_OUTPUT_DIRECTORY})
        include_directories(3rd-party/${3rdPartyLibrary})
        include_directories(3rd-party/${3rdPartyLibrary}/include)
    endforeach()

    #BRITE
    set(BRITE_LIBRARIES brite)

    #Set common include folder
    include_directories(${CMAKE_OUTPUT_DIRECTORY})
    #link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    #link_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

    #process debug switch
    if (${AUTOINSTALL_DEPENDENCIES})
        setup_vcpkg()
    endif()

    #Set C++ standard
    if(${NS3_PYTORCH})
        set(CMAKE_CXX_STANDARD 11) #c++17 for inline variables in Windows
        #set(CMAKE_CXX_STANDARD_REQUIRED ON) #ABI requirements for PyTorch affect this
    else()
        set(CMAKE_CXX_STANDARD 17) #c++17 for inline variables in Windows
        set(CMAKE_CXX_STANDARD_REQUIRED ON)
    endif()

    if(${NS3_SANITIZE})
        #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,leak,thread,undefined,memory -g")
    endif()


    #find required dependencies
    list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/buildsupport/custom_modules")


    set(NOT_FOUND_MSG  "is required and couldn't be found")

    #Libpcre2 for regex
    include(FindPCRE)
    find_package(PCRE)
    if (NOT ${PCRE_FOUND})
        if (NOT ${AUTOINSTALL_DEPENDENCIES})
            message(FATAL_ERROR "PCRE2 ${NOT_FOUND_MSG}")
        else()
            #If we don't find installed, install
            add_package(pcre2)
            get_property(pcre2_dir GLOBAL PROPERTY DIR_pcre2)
            link_directories(${pcre2_dir}/lib)
            include_directories(${pcre2_dir}/include)
            #stopped working for whatever reason, hardwired topology-read cmake file
            if(WIN32)
                set(PCRE_LIBRARIES pcre2-posix pcre2-8)
            else()
                set(PCRE_LIBRARIES pcre2-posix pcre2-8)
            endif()

        endif()
    else()
        link_directories(${PCRE_LIBRARY})
        include_directories(${PCRE_INCLUDE_DIR})
    endif()


    set(OPENFLOW_REQUIRED_BOOST_LIBRARIES)

    if(${NS3_OPENFLOW})

        set(OPENFLOW_REQUIRED_BOOST_LIBRARIES
                system
                signals
                filesystem
                static-assert
                config
                )
        include_directories(3rd-party/openflow/include)
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

    #GTK2
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

    #LibXml2
    if(${NS3_LIBXML2})
        find_package(LibXml2)
        if(NOT ${LIBXML2_FOUND})
            if (NOT ${AUTOINSTALL_DEPENDENCIES})
                message(FATAL_ERROR "LibXML2 ${NOT_FOUND_MSG}")
            else()
                #If we don't find installed, install
                add_package (libxml2)
                get_property(libxml2_dir GLOBAL PROPERTY DIR_libxml2)
                link_directories(${libxml2_dir}/lib)
                include_directories(${libxml2_dir}/include)
                #set(LIBXML2_DEFINITIONS)

                if(WIN32)
                    set(LIBXML2_LIBRARIES libxml2)
                else()
                    set(LIBXML2_LIBRARIES libxml2.a)
                endif()
                set(LIBXML2_FOUND TRUE)
            endif()
        else()
            link_directories(${LIBXML2_LIBRARY_DIRS})
            include_directories( ${LIBXML2_INCLUDE_DIR})
            #add_definitions(${LIBXML2_DEFINITIONS})
        endif()
    endif()

    #LibRT
    if(${NS3_LIBRT})
        if(WIN32)
            message(WARNING "Lib RT is not supported on Windows, building without it")
        else()
            find_library(LIBRT rt)
            if(NOT ${LIBRT_FOUND})
                message(FATAL_ERROR LibRT not found)
            else()
                link_libraries(rt)
                add_definitions(-DHAVE_RT)
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
            add_definitions(-DHAVE_PTHREAD_H)
            set(THREADS_FOUND TRUE)
            link_libraries(${CMAKE_THREAD_LIBS_INIT})
        endif()
    endif()


    if(${NS3_PYTHON})
        find_package(Python COMPONENTS Interpreter Development)
        if(NOT ${PYTHON_FOUND})
            message(FATAL_ERROR "PYTHON not found")
        else()
            link_directories(${Python_LIBRARY_DIRS})
            include_directories( ${Python_INCLUDE_DIRS})
        endif()
    endif()

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
        find_package(GSL)
        if(NOT ${GSL_FOUND})
            #message(FATAL_ERROR GSL not found)
            #If we don't find installed, install
            add_package (gsl)
            get_property(gsl_dir GLOBAL PROPERTY DIR_gsl)
            link_directories(${gsl_dir}/lib)
            include_directories(${gsl_dir}/include)
            set(GSL_LIBRARIES gsl gslcblas)
        else()
            include_directories( ${GSL_INCLUDE_DIRS})
            link_directories(${GSL_LIBRARY})
        endif()
    endif()

    if(${NS3_PYTORCH})
        list(APPEND CMAKE_PREFIX_PATH "/usr/local/lib/python3.6/dist-packages/torch")#installed with sudo pip3 install torch torchvision
        find_package(Torch REQUIRED)
        include_directories(${TORCH_INCLUDE_DIRS})
        #link_directories(${TORCH_LIBDIR})
        add_definitions(${TORCH_CXX_FLAGS})
    endif()

    #if(${NS3_GNUPLOT})
    #    find_package(Gnuplot-ios)
    #    if(NOT ${GNUPLOT_FOUND})
    #        message(FATAL_ERROR GNUPLOT not found)
    #    else()
    #        include_directories(${GNUPLOT_INCLUDE_DIRS})
    #        link_directories(${GNUPLOT_LIBRARY})
    #    endif()
    #endif()

    #process debug switch
    if(${NS3_DEBUG})
        set(CMAKE_BUILD_TYPE Debug)
        set(build_type "debug")
        set(CMAKE_SKIP_RULE_DEPENDENCY TRUE)
    else()
        set(CMAKE_BUILD_TYPE Release)
        set(build_type "release")
        set(CMAKE_SKIP_RULE_DEPENDENCY FALSE)
    endif()

    #Process core-config
    set(INT64X64 "128")

	if (${CMAKE_CXX_COMPILER_ID} EQUAL MSVC)
		message(WARNING "Microsoft MSVC doesn't support 128-bit integer operations. Falling back to double.")
		set(INT64X64 "DOUBLE")
	endif()

    if(INT64X64 STREQUAL "128")
        add_definitions(-DHAVE___UINT128_T)
        add_definitions(-DINT64X64_USE_128)
    elseif(INT64X64 STREQUAL "DOUBLE")
        add_definitions(-DINT64X64_USE_DOUBLE)
    elseif(INT64X64 STREQUAL "CAIRO")
        add_definitions(-DINT64X64_USE_CAIRO)
    else()
    endif()

    #Include header and function checker macros
    include(buildsupport/check_dependencies.cmake)

    #Check for required headers and functions, set flags if they're found or warn if they're not found
    check_include("stdint.h"   "HAVE_STDINT_H"   )
    check_include("inttypes.h" "HAVE_INTTYPES_H" )
    check_include("types.h"    "HAVE_SYS_TYPES_H")
    check_include("stat.h"     "HAVE_SYS_STAT_H" )
    check_include("dirent.h"   "HAVE_DIRENT_H"   )
    check_include("stdlib.h"   "HAVE_STDLIB_H"   )
    check_include("signal.h"   "HAVE_SIGNAL_H"   )
    check_function("getenv"    "HAVE_GETENV"     )

    #Enable NS3 logging if requested
    if(${NS3_LOG})
        add_definitions(-DNS3_LOG_ENABLE)
    endif()

    #Process config-store-config
    add_definitions(-DPYTHONDIR="/usr/local/lib/python2.7/dist-packages")
    add_definitions(-DPYTHONARCHDIR="/usr/local/lib/python2.7/dist-packages")
    add_definitions(-DHAVE_PYEMBED)
    add_definitions(-DHAVE_PYEXT)
    add_definitions(-DHAVE_PYTHON_H)


    #Create library names to solve dependency problems with macros that will be called at each lib subdirectory
    set(ns3-libs )
    set(ns3-libs-tests )
    set(ns3-contrib-libs )
    foreach(libname ${libs_to_build})
        #Create libname of output library of module
        set(lib${libname} ns${NS3_VER}-${libname}-${build_type})
        list(APPEND ns3-libs ${lib${libname}})
    endforeach()

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

    #Add libmodule_export.h if on Windows, to import DLLs
    #if (WIN32 AND ${NS3_SHARED})
    #    list(APPEND contents "
    ##include <ns3/lib${name}_export.h>")
    #endif()

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
    #Create shared library with sources and headers
    add_library(${lib${libname}} SHARED "${source_files}" "${header_files}")

    #Windows dlls require export headers for executables (╯°□°）╯︵ ┻━┻)
    #if(WIN32 AND ${NS3_SHARED})
    #    generate_export_header(${lib${libname}} EXPORT_FILE_NAME lib${libname}_export.h)
    #    file(COPY ${CMAKE_CACHEFILE_DIR}/src/${libname}/lib${libname}_export.h DESTINATION ${CMAKE_HEADER_OUTPUT_DIRECTORY}/)
    #endif()
    #Link the shared library with the libraries passed
    target_link_libraries(${lib${libname}} ${LIB_AS_NEEDED_PRE} ${libraries_to_link} ${LIB_AS_NEEDED_POST})
    if(MSVC)
        #set(whole_archive_string)
        #foreach (lib_to_link ${libraries_to_link})
        #    string(REPLACE ".dll" ".lib" lib_to_link_stripped ${lib_to_link})
            #list(APPEND whole_archive_string ${lib_to_link_stripped}.dll)
            #set(whole_archive_string ${whole_archive_string} /WHOLEARCHIVE:${lib_to_link_stripped})
            #set(whole_archive_string ${whole_archive_string} /WHOLEARCHIVE:${lib_to_link})

        #endforeach()
        target_link_options(${lib${libname}} PUBLIC /OPT:NOREF)
        #message(WARNING ${whole_archive_string})
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
                target_link_libraries(${test${libname}} ${LIB_AS_NEEDED_PRE} ${lib${libname}} ${libraries_to_link} ${LIB_AS_NEEDED_POST})
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

    #Build pybindings  if requested
    if(${NS3_PYTHON})
        set(arch gcc_LP64)#ILP32)#
        execute_process(
                COMMAND  PYTHONPATH=${CMAKE_OUTPUT_DIRECTORY} ${Python2_EXEC} ${PROJECT_SOURCE_DIR}/bindings/python/ns3modulegen-modular.py ${PROJECT_SOURCE_DIR}/src/${libname}/bindings/modulegen__${arch}.py > ${CMAKE_OUTPUT_DIRECTORY}/ns/${libname}-module.cc
        )
    endif()
endmacro()

macro (build_example name source_files header_files libraries_to_link)
    #Create shared library with sources and headers
    add_executable(${name} "${source_files}" "${header_files}")

    #Link the shared library with the libraries passed
    target_link_libraries(${name}  ${LIB_AS_NEEDED_PRE} ${libraries_to_link} ${LIB_AS_NEEDED_POST})

    set_target_properties( ${name}
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/examples/${examplename}
            )
endmacro()

macro (build_lib_example name source_files header_files libraries_to_link files_to_copy)
    #Create shared library with sources and headers
    add_executable(${name} "${source_files}" "${header_files}")

    #Link the shared library with the libraries passed
    target_link_libraries(${name} ${LIB_AS_NEEDED_PRE} ${lib${libname}} ${libraries_to_link} ${LIB_AS_NEEDED_POST})

    set_target_properties( ${name}
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/examples/${libname}
            )

    file(COPY ${files_to_copy} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/examples/${libname})
endmacro()

#Add contributions macros
include(buildsupport/contributions.cmake)