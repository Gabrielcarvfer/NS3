NS3_common_includes()

set(name virtual-net-device)
set_lib_name(${name})
add_library(lib${name} SHARED
        model/virtual-net-device.cc
        model/virtual-net-device.h
        )

#set_test_name(${name})
#add_library(test${name} )
