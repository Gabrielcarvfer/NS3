if (WIN32)
    #If using MSYS2
    set(MSYS2_PATH "E:\\msys64\\mingw64")
    set(GTK2_GDKCONFIG_INCLUDE_DIR "${MSYS2_PATH}\\include\\gtk-2.0")
    set(GTK2_GLIBCONFIG_INCLUDE_DIR "${MSYS2_PATH}\\include\\gtk-2.0")
    set(QT_QMAKE_EXECUTABLE "${MSYS2_PATH}\\bin\\qmake.exe")
    set(QT_RCC_EXECUTABLE "${MSYS2_PATH}\\bin\\rcc.exe")
    set(QT_UIC_EXECUTABLE "${MSYS2_PATH}\\bin\\uic.exe")
    set(QT_MOC_EXECUTABLE "${MSYS2_PATH}\\bin\\moc.exe")
    set(QT_MKSPECS_DIR    "${MSYS2_PATH}\\share\\qt4\\mkspecs")
endif()

#Fixed definitions
unset(CMAKE_LINK_LIBRARY_SUFFIX)

#Output folders
set(CMAKE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY}/bin)
set(CMAKE_HEADER_OUTPUT_DIRECTORY  ${CMAKE_OUTPUT_DIRECTORY}/ns3)
add_definitions(-DNS_TEST_SOURCEDIR="${CMAKE_OUTPUT_DIRECTORY}/test")

#fPIC 
set(CMAKE_POSITION_INDEPENDENT_CODE ON) 

#process all options passed in main cmakeLists
macro(process_options)
    #Copy all header files to outputfolder/include/
    FILE(GLOB_RECURSE include_files ${PROJECT_SOURCE_DIR}/*.h) #just copying every single header into ns3 include folder
    file(COPY ${include_files} DESTINATION ${CMAKE_HEADER_OUTPUT_DIRECTORY})

    #Set common include folder
    include_directories(${CMAKE_OUTPUT_DIRECTORY})

    #Set C++ standard
    add_definitions(-std=c++11 -fPIC)

    #find required dependencies

    #BoostC++
    if(${NS3_BOOST})
        find_package(Boost)
        if(NOT ${BOOST_FOUND})
            message(FATAL_ERROR BoostC++ not found)
        else()
            link_directories(${BOOST_LIBRARY_DIRS})
            include_directories( ${BOOST_INCLUDE_DIR})
        endif()
    endif()

    #GTK2
    if(${NS3_GTK2})
        find_package(GTK2)
        if(NOT ${GTK2_FOUND})
            message(FATAL_ERROR LibGTK2 not found)
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
            message(FATAL_ERROR LibXML2 not found)
        else()
            link_directories(${LIBXML2_LIBRARY_DIRS})
            include_directories( ${LIBXML2_INCLUDE_DIR})
            add_definitions(${LIBXML2_DEFINITIONS})
        endif()
    endif()

    #LibRT
    if(${NS3_LIBRT})
        find_library(LIBRT rt)
        if(NOT ${LIBRT_FOUND})
            message(FATAL_ERROR LibRT not found)
        else()
            add_definitions(-lrt)
            add_definitions(-DHAVE_RT)
        endif()
    endif()

    #if(${NS3_PTHREAD})
        set(THREADS_PREFER_PTHREAD_FLAG)
        find_package(Threads REQUIRED)
        if(NOT ${THREADS_FOUND})
            message(FATAL_ERROR Thread library not found)
        else()
            include_directories(${THREADS_PTHREADS_INCLUDE_DIR})
            add_definitions(-DHAVE_PTHREAD_H)
        endif()
    #endif()

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
            message(FATAL_ERROR GSL not found)
        else()
            include_directories( ${GSL_INCLUDE_DIRS})
            link_directories(${GSL_LIBRARY})
        endif()
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
        add_definitions(-g)
        set(build_type "debug")
        set(CMAKE_SKIP_RULE_DEPENDENCY TRUE)
    else()
        add_definitions(-O3)
        set(build_type "release")
        set(CMAKE_SKIP_RULE_DEPENDENCY FALSE)
    endif()

    #Process core-config
    set(INT64X64 128)

    if(INT64X64 EQUAL 128)
        add_definitions(-DHAVE___UINT128_T)
        add_definitions(-DINT64X64_USE_128)
    elseif(INT64X64 EQUAL DOUBLE)
        add_definitions(-DINT64X64_USE_DOUBLE)
    elseif(INT64X64 EQUAL CAIRO)
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
    foreach(libname ${libs_to_build})
        #TODO: add 3rd-party library dependency check
        list(APPEND lib${libname} ns${NS3_VER}-${libname}-${build_type})
        list(APPEND ns3-libs ${lib${libname}})
    endforeach()

	#Dump definitions for later use
    get_directory_property( ADDED_DEFINITIONS COMPILE_DEFINITIONS )
    file(WRITE ${CMAKE_HEADER_OUTPUT_DIRECTORY}/ns3-definitions "${ADDED_DEFINITIONS}")
endmacro()
#----------------------------------------------
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
    #Create shared library with sources and headers
    add_library(${lib${libname}} SHARED "${source_files}" "${header_files}")

    #Link the shared library with the libraries passed
    target_link_libraries(${lib${libname}} ${libraries_to_link})

    #Write a module header that includes all headers from that module
    write_module_header("${libname}" "${header_files}")

    #Build tests if requested
    if(${NS3_TESTS})
        list(LENGTH test_sources test_source_len)
        if (${test_source_len} GREATER 0)
            #Create libname of output library test of module
            list(APPEND test${libname} ns${NS3_VER}-${libname}-test-${build_type})

            #Create shared library containing tests of the module
            add_library(${test${libname}} SHARED "${test_sources}")

            #Link test library to the module library
            target_link_libraries(${test${libname}} ${lib${libname}})
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
        set(arch gcc_ILP32)
        add_custom_command(
                OUTPUT
                ${PROJECT_SOURCE_DIR}/src/${libname}/bindings/modulegen_${arch}.py
                COMMAND
                ${PROJECT_SOURCE_DIR}/bindings/python/ns3modulegen-modular.py
                ${PROJECT_SOURCE_DIR}/src/${libname}/bindings/
                ${PROJECT_SOURCE_DIR}/src/${libname}/
                ${CMAKE_HEADER_OUTPUT_DIRECTORY}/${libname}-module.h
                modulegen_${arch}.py
                ${CMAKE_CXX_FLAGS}
                )
    endif()
endmacro()

macro (build_example name source_files header_files libraries_to_link)
    #Create shared library with sources and headers
    add_executable(${name} "${source_files}" "${header_files}")

    #Link the shared library with the libraries passed
    target_link_libraries(${name} ${libraries_to_link})

    set_target_properties( ${name}
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/examples/${examplename}
            )
endmacro()

macro (build_lib_example name source_files header_files libraries_to_link)
    #Create shared library with sources and headers
    add_executable(${name} "${source_files}" "${header_files}")

    #Link the shared library with the libraries passed
    target_link_libraries(${name} ${libraries_to_link})

    set_target_properties( ${name}
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/examples/${libname}
            )
endmacro()

#Add contributions macros
include(buildsupport/contributions.cmake)