if (NS3_BRITE)
    include_directories(${PROJECT_SOURCE_DIR}/3rd-party/brite)

    set(name brite)

    set(source_files
            helper/brite-topology-helper.cc
            )

    set(header_files
            helper/brite-topology-helper.h
            )

    #link to dependencies
    set(libraries_to_link ${libnetwork} ${libcore} ${libinternet} ${libpoint-to-point} brite)

    set(test_sources
            test/brite-test-topology.cc
            )

    build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")
endif()
