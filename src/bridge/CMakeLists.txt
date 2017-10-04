NS3_common_includes()

set(libname ns${NS3_VER}-bridge-${build_type})
add_library(lib${name} SHARED
        model/bridge-channel.cc
        model/bridge-channel.h
        model/bridge-net-device.cc
        model/bridge-net-device.h
        helper/bridge-helper.cc
        helper/bridge-helper.h
        )

