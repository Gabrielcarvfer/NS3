if (${NS3_TESTS})
    GET_PROPERTY(local-ns3-libs GLOBAL PROPERTY ns3-libs)
    GET_PROPERTY(local-ns3-libs-tests GLOBAL PROPERTY ns3-libs-tests)

    if(WIN32)
        set(libraries_to_link ${local-ns3-libs})
        list(REMOVE_ITEM libraries_to_link ${libtest})

        add_executable(test-runner test-runner.cc ${local-ns3-libs-tests} $<TARGET_OBJECTS:${libtest}>)
        target_link_libraries(test-runner ${LIB_AS_NEEDED_PRE} ${libraries_to_link}  ${LIB_AS_NEEDED_POST})

        if (MSVC)
            target_link_options(test-runner PUBLIC /OPT:NOREF)
            #Is that so hard not to break people's CI, MSFT?
            #Why would you output the targets to a Debug/Release subfolder? Why?
            foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
                string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
                set_target_properties(test-runner
                PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/
                )
            endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
        endif()
    else()
        add_executable(test-runner test-runner.cc)
        target_link_libraries(test-runner ${LIB_AS_NEEDED_PRE} ${local-ns3-libs} ${local-ns3-libs-tests} ${LIB_AS_NEEDED_POST})
    endif()

    add_executable(bench-simulator bench-simulator.cc)
    target_link_libraries(bench-simulator ${libcore})

    if (${libnetwork})
        add_executable(bench-packets bench-packets.cc)
        target_link_libraries(bench-packets ${libnetwork})
    endif()

    if (${libcsma}) # weird test, but whatever
        add_executable(print-introspected-doxygen print-introspected-doxygen.cc)
        target_link_libraries(print-introspected-doxygen ${local-ns3-libs})
    endif()

endif()

