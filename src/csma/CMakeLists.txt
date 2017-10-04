NS3_common_includes()

set(name csma)
set(lib${name} ns${NS3_VER}-${name}-${build_type})
add_library(${lib${name}} SHARED
        model/backoff.cc
        model/backoff.h
        model/csma-channel.cc
        model/csma-channel.h
        model/csma-net-device.cc
        model/csma-net-device.h
        helper/csma-helper.cc
        helper/csma-helper.h
        )

#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED)