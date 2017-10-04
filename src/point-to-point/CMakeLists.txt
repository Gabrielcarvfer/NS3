NS3_common_includes()

set(name point-to-point)
set(lib${name} ns${NS3_VER}-${name}-${build_type})
add_library(${lib${name}} SHARED
        model/point-to-point-net-device.cc
        model/point-to-point-channel.cc
        model/point-to-point-remote-channel.cc
        model/ppp-header.cc
        helper/point-to-point-helper.cc
        model/point-to-point-net-device.h
        model/point-to-point-channel.h
        model/point-to-point-remote-channel.h
        model/ppp-header.h
        helper/point-to-point-helper.h
        )

#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED )
