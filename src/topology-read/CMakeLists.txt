set(name topology-read)

if(NOT WIN32)
  set(rocketfuel_sources model/rocketfuel-topology-reader.cc)
  set(rocketfuel_headers model/rocketfuel-topology-reader.h)
  set(rocketfuel_tests test/rocketfuel-topology-reader-test-suite.cc)
endif()

set(source_files ${rocketfuel_sources} model/topology-reader.cc model/inet-topology-reader.cc
                 model/orbis-topology-reader.cc helper/topology-reader-helper.cc
)

set(header_files ${rocketfuel_headers} model/topology-reader.h model/inet-topology-reader.h
                 model/orbis-topology-reader.h helper/topology-reader-helper.h
)

set(libraries_to_link ${libnetwork})

set(test_sources ${rocketfuel_tests})

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")
