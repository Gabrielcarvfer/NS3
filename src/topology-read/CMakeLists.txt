
set(name topology-read)

set(source_files
        model/topology-reader.cc
        model/inet-topology-reader.cc
        model/orbis-topology-reader.cc
        model/rocketfuel-topology-reader.cc
        helper/topology-reader-helper.cc
        )

set(header_files
        model/topology-reader.h
        model/inet-topology-reader.h
        model/orbis-topology-reader.h
        model/rocketfuel-topology-reader.h
        helper/topology-reader-helper.h
        )

if(WIN32)
    set(pcre_lib_name libpcre2-posix)
else()
    set(pcre_lib_name pcre)
endif()

set(libraries_to_link ${libnetwork} ${pcre_lib_name})

set(test_sources
        test/rocketfuel-topology-reader-test-suite.cc
        )

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")

