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

# This macro processes a ns-3 module
#
# Arguments: folder = src or contrib/contributor_module libname = core, wifi, contributor_module source_files =
# "cmake;list;of;.cc;files;" header_files = "cmake;list;of;public;.h;files;" libraries_to_link =
# "cmake;list;of;${library_names};" test_sources = "cmake;list;of;.cc;test;files;"
#

macro(
  build_lib_impl
  folder
  libname
  source_files
  header_files
  libraries_to_link
  test_sources
)
  # Create object library with sources and headers, that will be used in lib-ns3-static and the shared library
  add_library(${lib${libname}-obj} OBJECT "${source_files}" "${header_files}")
  if("${folder}" MATCHES "src")
    get_property(local-ns3-libs GLOBAL PROPERTY ns3-libs)
    set_property(GLOBAL PROPERTY ns3-libs "${local-ns3-libs};${lib${libname}}")
  else()
    get_property(local-ns3-contrib-libs GLOBAL PROPERTY ns3-contrib-libs)
    set_property(GLOBAL PROPERTY ns3-contrib-libs "${local-ns3-contrib-libs};${lib${libname}}")
  endif()

  if(${NS3_PRECOMPILE_HEADERS})
    target_precompile_headers(${lib${libname}-obj} REUSE_FROM stdlib_pch)
  endif()

  # Create shared library with previously created object library (saving compilation time for static libraries)
  add_library(${lib${libname}} SHARED $<TARGET_OBJECTS:${lib${libname}-obj}>)

  # Split ns and non-ns libraries to manage their propagation properly
  set(non_ns_libraries_to_link)
  set(ns_libraries_to_link)
  foreach(library ${libraries_to_link})
    if(${library} IN_LIST ns3_all_libs)
      list(APPEND ns_libraries_to_link ${library})
    else()
      list(APPEND non_ns_libraries_to_link ${library})
    endif()
  endforeach()

  # ns-3 libraries are linked publicly, to make sure other modules can find each other without being directly linked
  target_link_libraries(${lib${libname}} PUBLIC ${LIB_AS_NEEDED_PRE} "${ns_libraries_to_link}" ${LIB_AS_NEEDED_POST})

  # non-ns-3 libraries are linked privately, not propagating unnecessary libraries such as pthread, librt, etc
  target_link_libraries(
    ${lib${libname}} PRIVATE ${LIB_AS_NEEDED_PRE} "${non_ns_libraries_to_link}" ${LIB_AS_NEEDED_POST}
  )

  # set output name of library
  set_target_properties(${lib${libname}} PROPERTIES OUTPUT_NAME ns${NS3_VER}-${libname}-${build_type})

  if(${NS3_STATIC})
    get_property(local-ns3-external-libs GLOBAL PROPERTY ns3-external-libs)
    set_property(GLOBAL PROPERTY ns3-external-libs "${local-ns3-external-libs};${non_ns_libraries_to_link}")

    get_property(local-lib-ns3-static-objs GLOBAL PROPERTY lib-ns3-static-objs)
    set_property(
      GLOBAL PROPERTY lib-ns3-static-objs "${local-lib-ns3-static-objs};$<TARGET_OBJECTS:${lib${libname}-obj}>"
    )
  endif()

  # Write a module header that includes all headers from that module
  write_module_header("${libname}" "${header_files}")

  # Copy all header files to outputfolder/include
  file(COPY ${header_files} DESTINATION ${CMAKE_HEADER_OUTPUT_DIRECTORY})

  # Build tests if requested
  if(${NS3_TESTS})
    list(LENGTH test_sources test_source_len)
    if(${test_source_len} GREATER 0)
      # Create libname of output library test of module
      set(test${libname} test-lib${libname}
          CACHE INTERNAL "" FORCE
      )

      get_property(local-ns3-libs-tests GLOBAL PROPERTY ns3-libs-tests)

      set_property(GLOBAL PROPERTY ns3-libs-tests "${local-ns3-libs-tests};${test${libname}}")

      # Create shared library containing tests of the module
      add_library(${test${libname}} SHARED "${test_sources}")

      # Link test library to the module library
      target_link_libraries(
        ${test${libname}} ${LIB_AS_NEEDED_PRE} ${lib${libname}} "${libraries_to_link}" ${LIB_AS_NEEDED_POST}
      )
      set_target_properties(${test${libname}} PROPERTIES OUTPUT_NAME ns${NS3_VER}-${libname}-test-${build_type})

      target_compile_definitions(${test${libname}} PRIVATE NS_TEST_SOURCEDIR="${folder}/${libname}/test")
      if(${NS3_PRECOMPILE_HEADERS})
        target_precompile_headers(${test${libname}} REUSE_FROM stdlib_pch)
      endif()
    endif()
  endif()

  # Build lib examples if requested
  if(${NS3_EXAMPLES})
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/examples)
      add_subdirectory(examples)
    endif()
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/example)
      add_subdirectory(example)
    endif()
  endif()

  # Get architecture pair for python bindings
  set(arch gcc_ILP32)
  set(arch_flag)
  if(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
    set(arch gcc_LP64)
    set(arch_flag -m64)
  endif()

  # Add target to scan python bindings
  if(${NS3_SCAN_PYTHON_BINDINGS} AND EXISTS ${CMAKE_HEADER_OUTPUT_DIRECTORY}/${libname}-module.h)
    set(bindings_output_folder ${PROJECT_SOURCE_DIR}/${folder}/${libname}/bindings)
    file(MAKE_DIRECTORY ${bindings_output_folder})
    set(module_api ${bindings_output_folder}/modulegen__${arch}.py)

    set(modulescan_modular_command ${Python3_EXECUTABLE} ${PROJECT_SOURCE_DIR}/bindings/python/ns3modulescan-modular.py
            )

    # To build the header map for the module, we start by copying the headers and prepending the dictionary start
    set(header_map "{\\\"${header_files};")

    # We then remove model/ helper/ prefixes
    # e.g. {'model/angles.h;model/antenna-model.h;... -> {'angles.h;antenna-model.h;...)
    string(REPLACE "model/" "" header_map "${header_map}")
    string(REPLACE "helper/" "" header_map "${header_map}")

    # Now we replace list entry separators (;) with ending of the string quote ("),
    # followed by the relative module
    # e.g. {"model/angles.h;model/antenna-model.h;... -> {"angles.h" : "antenna", "antenna-model.h": "antenna", "...)
    string(REPLACE ";" "\\\": \\\"${libname}\\\", \\\"" header_map "${header_map}")

    # We now remove the last character ("), which needs to be replaced with a (}), to close the dictionary
    # e.g. "antenna-model.h" : "antenna", " -> "antenna-model.h" : "antenna"
    string(LENGTH "${header_map}" header_map_len)
    math(EXPR header_map_len "${header_map_len}-3")
    string(SUBSTRING "${header_map}" 0 ${header_map_len} header_map)

    # Append end of dictionary (})
    string(APPEND header_map "}")

    add_custom_target(apiscan-${lib${libname}}
            COMMAND ${modulescan_modular_command} ${CMAKE_OUTPUT_DIRECTORY} ${libname} ${header_map} ${module_api} ${arch_flag}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            DEPENDS ${lib${libname}}
    )
    add_dependencies(apiscan-all apiscan-${lib${libname}})
  endif()

  # Build pybindings if requested and if bindings subfolder exists in NS3/src/libname
  if(${NS3_PYTHON_BINDINGS} AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/bindings")
    set(bindings_output_folder ${CMAKE_OUTPUT_DIRECTORY}/${folder}/${libname}/bindings)
    file(MAKE_DIRECTORY ${bindings_output_folder})
    set(module_src ${bindings_output_folder}/ns3module.cc)
    set(module_hdr ${bindings_output_folder}/ns3module.h)

    string(REPLACE "-" "_" libname_sub ${libname}) # '-' causes problems (e.g. csma-layout), replace with '_' (e.g. csma_layout)

    # Set prefix of binding to _ if a ${libname}.py exists, and copy the ${libname}.py to the output folder
    set(prefix)
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bindings/${libname}.py)
      set(prefix _)
      file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/bindings/${libname}.py
              DESTINATION ${CMAKE_OUTPUT_DIRECTORY}/bindings/python/ns
              )
    endif()

    # Run modulegen-modular to generate the bindings sources
    if((NOT EXISTS ${module_hdr}) OR (NOT EXISTS ${module_src})) # OR TRUE) # to force reprocessing
      get_property(local-ns3-libs GLOBAL PROPERTY ns3-libs)
      string(REPLACE ";" "," ENABLED_FEATURES "${local-ns3-libs}")
      set(modulegen_modular_command GCC_RTTI_ABI_COMPLETE=True NS3_ENABLED_FEATURES="${ENABLED_FEATURES}"
                                    ${Python3_EXECUTABLE} ${PROJECT_SOURCE_DIR}/bindings/python/ns3modulegen-modular.py
      )
      execute_process(
        COMMAND ${CMAKE_COMMAND} -E env PYTHONPATH=${CMAKE_OUTPUT_DIRECTORY} ${modulegen_modular_command}
                ${CMAKE_CURRENT_SOURCE_DIR} ${arch} ${prefix}${libname_sub} ${module_src}
        TIMEOUT 60
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_FILE ${module_hdr}
        ERROR_FILE ${bindings_output_folder}/ns3modulegen.log
        RESULT_VARIABLE error_code
      )
      if(${error_code} OR NOT (EXISTS ${module_hdr}))
        message(
          FATAL_ERROR "Something went wrong during processing of the python bindings of module ${libname}."
                      " Make sure the correct versions of Pybindgen and Pygccxml are installed (use the pip ones)."
        )
        if(EXISTS ${module_src})
          file(REMOVE ${module_src})
        endif()
      endif()
    endif()

    # Add core module helper sources
    set(python_module_files ${module_hdr} ${module_src})
    if(${libname} STREQUAL "core")
      list(APPEND python_module_files ${CMAKE_CURRENT_SOURCE_DIR}/bindings/module_helpers.cc
           ${CMAKE_CURRENT_SOURCE_DIR}/bindings/scan-header.h
      )
    endif()
    add_library(${libname}-bindings SHARED "${python_module_files}")
    target_include_directories(${libname}-bindings PUBLIC ${Python3_INCLUDE_DIRS} ${bindings_output_folder})

    # If there is any, remove the "lib" prefix of libraries (search for "set(lib${libname}")
    list(LENGTH ns_libraries_to_link num_libraries)
    if(num_libraries GREATER "0")
      string(REPLACE ";" "-bindings;" bindings_to_link "${ns_libraries_to_link};") # add -bindings suffix to all
                                                                                   # lib${name}
      string(REPLACE "lib" "" bindings_to_link "${bindings_to_link}") # remove lib prefix from all lib${name}-bindings
    endif()
    target_link_libraries(
      ${libname}-bindings PUBLIC ${LIB_AS_NEEDED_PRE} ${lib${libname}} "${bindings_to_link}" "${libraries_to_link}"
                                 ${LIB_AS_NEEDED_POST}
    )
    target_include_directories(${libname}-bindings PRIVATE ${PROJECT_SOURCE_DIR}/src/core/bindings)

    # Set binding library name and output folder
    set_target_properties(
      ${libname}-bindings
      PROPERTIES OUTPUT_NAME ${prefix}${libname_sub}
                 PREFIX ""
                 LIBRARY_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY}/bindings/python/ns
    )

    get_property(local-ns3-python-bindings-modules GLOBAL PROPERTY ns3-python-bindings-modules)
    set_property(GLOBAL PROPERTY ns3-python-bindings-modules "${local-ns3-python-bindings-modules};${libname}-bindings")
  endif()

  # Handle package export
  install(
    TARGETS ${lib${name}}
    EXPORT ns3ExportTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )
endmacro()

# This macro processes a ns-3 module example
#
# Arguments: folder = src or contrib/contributor_module libname = core, wifi, contributor_module (this is implicit, as
# it is called by build_lib_impl)
# name = example name (e.g. command-line-example)
# source_files = "cmake;list;of;.cc;files;"
# header_files = "cmake;list;of;public;.h;files;"
# libraries_to_link = "cmake;list;of;${library_names};"
#
macro(
  build_lib_example_impl
  folder
  name
  source_files
  header_files
  libraries_to_link
)
  # Create shared library with sources and headers
  add_executable(${name} "${source_files}" "${header_files}")

  if(${NS3_STATIC})
    target_link_libraries(${name} ${LIB_AS_NEEDED_PRE_STATIC} ${lib-ns3-static})
  else()
    target_link_libraries(${name} ${LIB_AS_NEEDED_PRE} ${lib${libname}} ${libraries_to_link} ${LIB_AS_NEEDED_POST})
  endif()

  if(${NS3_PRECOMPILE_HEADERS})
    target_precompile_headers(${name} REUSE_FROM stdlib_pch_exec)
  endif()

  set_runtime_outputdirectory(${name} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${folder}/${libname}/examples/)

  if(${NS3_TESTS})
    add_dependencies(all-test-targets ${name})
  endif()
endmacro()

# This macro processes a ns-3 module header file (module_name-module.h)
#
# Arguments: name = module name (e.g. core, wifi) header_files = "cmake;list;of;public;.h;files;"
macro(write_module_header name header_files)
  string(TOUPPER ${name} uppercase_name)
  string(REPLACE "-" "_" final_name ${uppercase_name})
  # Common module_header
  list(APPEND contents "#ifdef NS3_MODULE_COMPILATION ")
  list(
    APPEND
    contents
    "
    error \"Do not include ns3 module aggregator headers from other modules; these are meant only for end user scripts.\" "
  )
  list(APPEND contents "
#endif "
  )
  list(APPEND contents "
#ifndef NS3_MODULE_"
  )
  list(APPEND contents ${final_name})
  list(APPEND contents "
    // Module headers: "
  )

  # Write each header listed to the contents variable
  foreach(header ${header_files})
    get_filename_component(head ${header} NAME)
    list(APPEND contents "
    #include <ns3/${head}>"
    )
    # include \"ns3/${head}\"")
  endforeach()

  # Common module footer
  list(APPEND contents "
#endif "
  )
  file(WRITE ${CMAKE_HEADER_OUTPUT_DIRECTORY}/${name}-module.h ${contents})
endmacro()
