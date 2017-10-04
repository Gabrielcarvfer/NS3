NS3_common_includes()

set(name virtual-net-device)
set(lib${name} ns${NS3_VER}-${name}-${build_type})
add_library(${lib${name}} SHARED
        model/virtual-net-device.cc
        model/virtual-net-device.h
        )

#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED )
