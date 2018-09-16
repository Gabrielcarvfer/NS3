
if (NS3_BRITE)
    if (BRITE_FOUND)
        set(name brite)

        set(source_files
                helper/brite-topology-helper.cc
                )

        set(header_files
                helper/brite-topology-helper.h
                )

        #link to dependencies
        set(libraries_to_link ${libnetwork} ${libcore} ${libinternet} ${libpoint-to-point} ${LIBBRITE})

        set(test_sources
                test/brite-test-topology.cc
                )

        build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")
    else()
        message(WARNING "Brite library not found")
    endif()
endif() # NS3 brite
