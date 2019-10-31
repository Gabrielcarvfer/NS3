
set(name topology-read)

if(PCRE_FOUND OR NOT WIN32)
    set(source_files
            model/rocketfuel-topology-reader.cc
            )
    set(header_files
            model/rocketfuel-topology-reader.h
            )
    set(test_sources
            test/rocketfuel-topology-reader-test-suite.cc
            )
endif()

set(source_files
        ${source_files}
        model/topology-reader.cc
        model/inet-topology-reader.cc
        model/orbis-topology-reader.cc
        helper/topology-reader-helper.cc
        )

set(header_files
        ${header_files}
        model/topology-reader.h
        model/inet-topology-reader.h
        model/orbis-topology-reader.h
        helper/topology-reader-helper.h
        )

set(libraries_to_link ${libnetwork} ${PCRE_LIBRARIES})


set(test_sources
        ${test_sources}
        )

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")
