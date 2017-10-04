NS3_common_includes()

set(name click)
set(lib${name} ns${NS3_VER}-${name}-${build_type})
add_library(${lib${name}} SHARED
        model/ipv4-click-routing.cc
        model/ipv4-click-routing.h
        model/ipv4-l3-click-protocol.cc
        model/ipv4-l3-click-protocol.h
        helper/click-internet-stack-helper.cc
        helper/click-internet-stack-helper.h
        )

set(test${name} ns${NS3_VER}-${name}-test-${build_type})
add_library(${test${name}} SHARED
        test/ipv4-click-routing-test.cc
        )

