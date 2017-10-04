NS3_common_includes()

set(name point-to-point)
set_lib_name(${name})
add_library(lib${name} SHARED
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

#set_test_name(${name})
#add_library(test${name} )
