NS3_common_includes()

set(name csma)
set_lib_name(${name})
add_library(lib${name} SHARED
        model/backoff.cc
        model/backoff.h
        model/csma-channel.cc
        model/csma-channel.h
        model/csma-net-device.cc
        model/csma-net-device.h
        helper/csma-helper.cc
        helper/csma-helper.h
        )

#set_test_name(${name})
#add_library(test${name})