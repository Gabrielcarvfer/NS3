macro(process_contribution contribution_list)
    #Create handles to build libraries
    foreach(libname ${contribution_list})
        list(APPEND lib${libname} ns${NS3_VER}-contrib-${libname}-${build_type})
        list(APPEND ns3-contrib-libs ${lib${libname}})
    endforeach()

    #Add contribution folders to be built
    foreach(libname ${contribution_list})
        add_subdirectory("contrib/${libname}")
    endforeach()
endmacro()

macro (build_contrib_lib_component name contrib source_files header_files libraries_to_link test_sources)
    #Create shared library with sources and headers
    add_library("${lib${contrib}-${name}}" OBJECT "${source_files}" "${header_files}")
    set(${contrib}_libraries_to_link "${${contrib}_libraries_to_link}" ${libraries_to_link} PARENT_SCOPE)

    #Build tests if requested
    if(${NS3_TESTS})
        list(LENGTH test_sources test_source_len)
        if (${test_source_len} GREATER 0)
            #Create name of output library test of module
            set(test${name} ns${NS3_VER}-${name}-test-${build_type})

            #Create shared library containing tests of the module
            add_library(${test${name}} SHARED "${test_sources}")

            if (COMMAND cotire)
                cotire(${test${name}})
            endif()

            #Link test library to the module library
            target_link_libraries(${test${name}} ${lib${contrib}})
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

    #set_target_properties( ${lib${name}}
    #        PROPERTIES
    #        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/contrib/${name}/
    #        )
endmacro()

macro (build_contrib_example name contrib source_files header_files libraries_to_link files_to_copy)
    #Create shared library with sources and headers
    add_executable(${name} "${source_files}" "${header_files}")

    if (COMMAND cotire)
        cotire(${name})
    endif()


    #Link the shared library with the libraries passed
    target_link_libraries(${name} "${libraries_to_link}")

    set_target_properties( ${name}
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/contrib/${contrib}/examples
            )

    file(COPY ${files_to_copy} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/contrib/${contrib}/examples/)

endmacro()

macro (build_contrib_lib contrib_name components)
    #Set library handler
    set(lib${contrib_name} ns${NS3_VER}-contrib-${libname}-${build_type})

    #Set sublibraries list
    set(${contrib_name}-contrib-libs)

    #Create a lib handler for each component of the contrib library and add their respective subfolder
    foreach(libname ${components})
        list(APPEND lib${contrib_name}-${libname} "ns${NS3_VER}-contrib-${contrib_name}-${libname}-${build_type}")
        list(APPEND ${contrib_name}-contrib-libs ${lib${contrib_name}-${libname}})
        #Set NS3 or 3rd-party libraries to link
        set(${contrib_name}_libraries_to_link)
        add_subdirectory(${libname})
    endforeach()

    #As we're building a single library from multiple library components,
    #   we need to create a list of target_objects to those components
    set(component_target_objects)
    foreach(component ${${contrib_name}-contrib-libs})
        list(APPEND component_target_objects $<TARGET_OBJECTS:${component}>)
    endforeach()

    #Create the contrib library with their components
    add_library(${lib${contrib_name}} SHARED ${component_target_objects})

    #Windows dlls require export headers for executables (╯°□°）╯︵ ┻━┻)
    #if(WIN32 AND ${NS3_SHARED})
    #    generate_export_header(${lib${contrib_name}} EXPORT_FILE_NAME libcontrib-${contrib_name}_export.h)
    #    file(COPY ${CMAKE_CACHEFILE_DIR}/contrib/${contrib_name}/libcontrib-${contrib_name}_export.h DESTINATION ${CMAKE_HEADER_OUTPUT_DIRECTORY}/)
    #endif()

    if (COMMAND cotire)
        set_target_properties(${lib${contrib_name}} PROPERTIES COTIRE_UNITY_SOURCE_POST_UNDEFS "DEBUG_TYPE")
        cotire(${lib${contrib_name}})
    endif()


    #Link NS3 and/or 3rd-party dependencies
    target_link_libraries(${lib${contrib_name}} PUBLIC ${${contrib_name}_libraries_to_link})

    #Write a module header that includes all headers from that module
    FILE(GLOB_RECURSE header_files ${PROJECT_SOURCE_DIR}/contrib/${contrib_name}/*.h)
    write_module_header("contrib-${contrib_name}" "${header_files}")

    #Copy header files
    file(COPY ${header_files} DESTINATION ${CMAKE_HEADER_OUTPUT_DIRECTORY})

endmacro()

