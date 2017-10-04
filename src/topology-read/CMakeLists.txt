NS3_common_includes()

set(name topology-read)
set(lib${name} ns${NS3_VER}-${name}-${build_type})
add_library(${lib${name}} SHARED
        model/topology-reader.cc
        model/inet-topology-reader.cc
        model/orbis-topology-reader.cc
        model/rocketfuel-topology-reader.cc
        helper/topology-reader-helper.cc
        model/topology-reader.h
        model/inet-topology-reader.h
        model/orbis-topology-reader.h
        model/rocketfuel-topology-reader.h
        helper/topology-reader-helper.h
        )

#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED )
