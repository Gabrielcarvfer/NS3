if (${NS3_TESTS})
    GET_PROPERTY(local-ns3-libs GLOBAL PROPERTY ns3-libs)

    if(WIN32)
        set(libraries_to_link ${local-ns3-libs})
        list(REMOVE_ITEM libraries_to_link ${libtest})

        add_executable(test-runner test-runner.cc ${ns3-libs-tests} $<TARGET_OBJECTS:${libtest}>)
        target_link_libraries(test-runner ${LIB_AS_NEEDED_PRE} ${libraries_to_link}  ${LIB_AS_NEEDED_POST})
    else()
        add_executable(test-runner test-runner.cc)
        target_link_libraries(test-runner ${LIB_AS_NEEDED_PRE} ${ns3-libs} ${ns3-libs-tests} ${LIB_AS_NEEDED_POST})
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

    add_test(test_core test-runner --test-name=libns3-core-test-debug)
endif()

