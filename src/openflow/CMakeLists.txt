if (${NS3_OPENFLOW})
    if (${BOOST_FOUND})
        set(name openflow)

        set(source_files
                model/openflow-interface.cc
                model/openflow-switch-net-device.cc
                helper/openflow-switch-helper.cc
                )

        set(header_files
                model/openflow-interface.h
                model/openflow-switch-net-device.h
                helper/openflow-switch-helper.h
                )

        set(libraries_to_link ${libinternet} ${BOOST_LIBRARIES} ${OPENFLOW_LIBRARIES})

        set(test_sources
                test/openflow-switch-test-suite.cc
                )

        build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")

        #In case of collisions between one of the dependencies and other modules, add include directories per target
        target_include_directories(${lib${name}} PUBLIC "${BOOST_INCLUDES}")
        target_include_directories(${test${name}} PUBLIC "${BOOST_INCLUDES}")

    endif()
endif()