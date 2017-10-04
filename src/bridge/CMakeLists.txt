NS3_common_includes()

set(name bridge)
set(lib${name} ns${NS3_VER}-${name}-${build_type})
add_library(${lib${name}} SHARED
        model/bridge-channel.cc
        model/bridge-channel.h
        model/bridge-net-device.cc
        model/bridge-net-device.h
        helper/bridge-helper.cc
        helper/bridge-helper.h
        )


#link to dependencies
target_link_libraries(${lib${name}} ${libnetwork})