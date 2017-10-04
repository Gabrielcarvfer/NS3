NS3_common_includes()

set(name click)
set_lib_name(${name})
add_library(lib${name} SHARED
        model/ipv4-click-routing.cc
        model/ipv4-click-routing.h
        model/ipv4-l3-click-protocol.cc
        model/ipv4-l3-click-protocol.h
        helper/click-internet-stack-helper.cc
        helper/click-internet-stack-helper.h
        )

set_test_name(${name})
add_library(test${name}
        test/ipv4-click-routing-test.cc
        )

