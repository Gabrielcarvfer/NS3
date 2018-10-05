if (${NS3_TESTS})
    add_executable(test-runner test-runner.cc)
    target_link_libraries(test-runner -Wl,--no-as-needed ${ns3-libs} ${ns3-libs-tests} -Wl,--as-needed)

    add_executable(bench-simulator bench-simulator.cc)
    target_link_libraries(bench-simulator ${libcore})

    if (${libnetwork})
        add_executable(bench-packets bench-packets.cc)
        target_link_libraries(bench-packets ${libnetwork})
    endif()

    if (${libcsma}) # weird test, but whatever
        add_executable(print-introspected-doxygen print-introspected-doxygen.cc)
        target_link_libraries(print-introspected-doxygen ${ns3-libs})
    endif()

    add_test(test_core test-runner --test-name=libns3-core-test-debug)
endif()

#todo: fix failing bugs
#   devices-wifi : 2831
#   aggregation-wifi : ampdu
#   wave mac-extension-test-suite : annex_c