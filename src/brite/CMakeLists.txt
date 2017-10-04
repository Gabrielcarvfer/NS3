NS3_common_includes()

set(name brite)
set_lib_name(${name})
add_library(lib${name} SHARED
        helper/brite-topology-helper.cc
        helper/brite-topology-helper.h
        )

set_test_name(${name})
add_library(test${name}
        test/brite-test-topology.cc
        )

