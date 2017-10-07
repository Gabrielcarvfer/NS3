NS3_common_includes()

set(name dsdv)
set(lib${name} ns${NS3_VER}-${name}-${build_type})
add_library(${lib${name}} SHARED
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

set(libraries_to_link ${libinternet})


set(test${name} ns${NS3_VER}-${name}-test-${build_type})
add_library(${test${name}} SHARED
        test/dsdv-testcase.cc)
