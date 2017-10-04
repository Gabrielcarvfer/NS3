NS3_common_includes()

set(name sixlowpan)
set(lib${name} ns${NS3_VER}-${name}-${build_type})
add_library(${lib${name}} SHARED
        model/sixlowpan-net-device.cc
        model/sixlowpan-header.cc
        helper/sixlowpan-helper.cc
        model/sixlowpan-net-device.h
        model/sixlowpan-header.h
        helper/sixlowpan-helper.h
        )

#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED )
