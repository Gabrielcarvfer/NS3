NS3_common_includes()

set(name dsdv)
set_lib_name(${name})
add_library(lib${name} SHARED
        model/dsdv-packet.cc
        model/dsdv-packet.h
        model/dsdv-packet-queue.cc
        model/dsdv-packet-queue.h
        model/dsdv-routing-protocol.cc
        model/dsdv-routing-protocol.h
        model/dsdv-rtable.cc
        model/dsdv-rtable.h
        helper/dsdv-helper.cc
        helper/dsdv-helper.h
        )

set_test_name(${name})
add_library(test${name}
        test/dsdv-testcase.cc)
