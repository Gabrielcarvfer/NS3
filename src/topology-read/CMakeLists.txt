NS3_common_includes()

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
set(libraries_to_link ${libnetwork})

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED )
