#include Cristian Adam cmake modules to increase cmake speed
if(${CMAKE_VERSION} VERSION_LESS "3.11.0")
    message(WARNING "Cristian Adam CMakeChecksCache modules to speed up cmake requires CMake 3.11")
elseif()
    list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/buildsupport/CMakeChecksCache")
endif()


if (WIN32)
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


set(LIB_AS_NEEDED_PRE  )
set(LIB_AS_NEEDED_POST )

if (${NS3_SHARED})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        # using Clang
        if(WIN32)
            set(LINK_FLAGS /WHOLEARCHIVE)
        else()
            set(LIB_AS_NEEDED_PRE -Wl,-all_load)
        endif()
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        # using GCC
        set(LIB_AS_NEEDED_PRE  -Wl,--no-as-needed)
        set(LIB_AS_NEEDED_POST -Wl,--as-needed   )
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
        # using Intel C++
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        # using Visual Studio C++
    endif()
endif()


#process all options passed in main cmakeLists
macro(process_options)

    if (${AUTOINSTALL_DEPENDENCIES})
        include(buildsupport/vcpkg_hunter.cmake)
        setup_vcpkg()
    endif()

    if (WIN32 AND ${NS3_SHARED})
        include(GenerateExportHeader)
        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
        set(BUILD_SHARED_LIBS TRUE)
    endif()

    #Copy all header files to outputfolder/include/
    file(GLOB_RECURSE include_files ${PROJECT_SOURCE_DIR}/src/*.h) #just copying every single header into ns3 include folder
    file(COPY ${include_files} DESTINATION ${CMAKE_HEADER_OUTPUT_DIRECTORY})

    file(GLOB_RECURSE include_files ${PROJECT_SOURCE_DIR}/3rd-party/netanim/*.h) #just copying every single header from netanim into ns3 include folder
    file(COPY ${include_files} DESTINATION ${CMAKE_HEADER_OUTPUT_DIRECTORY})

    #Set common include folder
    include_directories(${CMAKE_OUTPUT_DIRECTORY})

    #Set C++ standard
    set(CMAKE_CXX_STANDARD 17) #c++17 for inline variables in Windows
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    #find required dependencies
    list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/buildsupport/custom_modules")


    set(NOT_FOUND_MSG  "is required and couldn't be found")
    #Libpcre2 for regex
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
        endif()
    else()
        link_directories(${PCRE_LIBRARY})
        include_directories(${PCRE_INCLUDE_DIR})
    endif()

    #BoostC++
    if(${NS3_BOOST})
        find_package(Boost)
        if(NOT ${BOOST_FOUND})
            if (NOT ${AUTOINSTALL_DEPENDENCIES})
                message(FATAL_ERROR "BoostC++ ${NOT_FOUND_MSG}")
            else()
                #If we don't find installed, install
                #add_package(boost) #this install all the boost libraries and was a bad idea
                #todo: add individual boost libraries required

                get_property(boost_dir GLOBAL PROPERTY DIR_boost)
                link_directories(${boost_dir}/lib)
                include_directories(${boost_dir}/include)
            endif()
        else()
            link_directories(${BOOST_LIBRARY_DIRS})
            include_directories( ${BOOST_INCLUDE_DIR})
        endif()
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
                set(LIBXML2_LIBRARIES libxml2)
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

    #removed in favor of C++ threads
    #if(${NS3_PTHREAD})
    #    set(THREADS_PREFER_PTHREAD_FLAG)
    #    find_package(Threads REQUIRED)
    #    if(NOT ${THREADS_FOUND})
    #        message(FATAL_ERROR Thread library not found)
    #    else()
    #        include_directories(${THREADS_PTHREADS_INCLUDE_DIR})
    #        add_definitions(-DHAVE_PTHREAD_H)
    #    endif()
    #endif()
    set(THREADS_FOUND TRUE)

    if(${NS3_PYTHON})
        find_package(Python2 COMPONENTS Interpreter Development)
        if(NOT ${Python2_FOUND})
            message(FATAL_ERROR "PYTHON not found")
        else()
            file(MAKE_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY}/ns)
            link_directories(${Python2_LIBRARY_DIRS})
            include_directories( ${Python2_INCLUDE_DIRS})
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
        else()
            include_directories(${GSL_INCLUDE_DIRS})
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

    #if(${NS3_BRITE})
    #    find_package(Brite)
    #    if(NOT ${BRITE_FOUND})
    #        message(FATAL_ERROR BRITEnot found)
    #    else()
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

	if (${CMAKE_CXX_COMPILER_ID} EQUAL GCC)
    else()
		message(WARNING "Microsoft MSVC and CLang doesn't support 128-bit integer operations. Falling back to double.")
		set(INT64X64 DOUBLE)
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
    #add_definitions(-DPYTHONDIR="/usr/local/lib/python2.7/dist-packages")
    #add_definitions(-DPYTHONARCHDIR="/usr/local/lib/python2.7/dist-packages")
    #add_definitions(-DHAVE_PYEMBED)
    #add_definitions(-DHAVE_PYEXT)
    #add_definitions(-DHAVE_PYTHON_H)


    #Create library names to solve dependency problems with macros that will be called at each lib subdirectory
    set(ns3-libs )
    set(ns3-libs-tests )
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

    #Copy modified headers to output directory before each build
    #May seem stupid, but removing this required to reload the cmake project to copy header files to build/ns3
    #Side effect of using it: forces recompilation of the whole library after copying headers if not using ccache
    #add_custom_command(TARGET ${lib${libname}}
    #        PRE_BUILD
    #        COMMAND ${CMAKE_COMMAND} -E copy ${header_files} ${CMAKE_HEADER_OUTPUT_DIRECTORY}
    #        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/src/${libname}
    #        )

    #Windows dlls require export headers for executables (╯°□°）╯︵ ┻━┻)
    #if(WIN32 AND ${NS3_SHARED})
    #    generate_export_header(${lib${libname}} EXPORT_FILE_NAME lib${libname}_export.h)
    #    file(COPY ${CMAKE_CACHEFILE_DIR}/src/${libname}/lib${libname}_export.h DESTINATION ${CMAKE_HEADER_OUTPUT_DIRECTORY}/)
    #endif()

    #Link the shared library with the libraries passed
    target_link_libraries(${lib${libname}} ${LIB_AS_NEEDED_PRE} ${libraries_to_link} ${LIB_AS_NEEDED_POST})

    #Write a module header that includes all headers from that module
    write_module_header("${libname}" "${header_files}")

    #Build tests if requested
    if(${NS3_TESTS})
        list(LENGTH test_sources test_source_len)
        if (${test_source_len} GREATER 0)
            #Create libname of output library test of module
            set(test${libname} ns${NS3_VER}-${libname}-test-${build_type} CACHE INTERNAL "" FORCE)
            set(ns3-libs-tests ${ns3-libs-tests} ${test${libname}} CACHE INTERNAL "" FORCE)

            #Create shared library containing tests of the module
            add_library(${test${libname}} SHARED "${test_sources}")

            #Link test library to the module library
            target_link_libraries(${test${libname}} ${LIB_AS_NEEDED_PRE} ${ns3-libs} ${LIB_AS_NEEDED_POST})#${lib${libname}} ${LIB_AS_NEEDED_POST})
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