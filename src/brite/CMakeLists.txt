NS3_common_includes()

set(name brite)
set(lib${name} ns${NS3_VER}-${name}-${build_type})
add_library(${lib${name}} SHARED
        helper/brite-topology-helper.cc
        helper/brite-topology-helper.h
        )

set(test${name} ns${NS3_VER}-${name}-test-${build_type})
add_library(${test${name}} SHARED
        test/brite-test-topology.cc
        )

