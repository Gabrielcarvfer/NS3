NS3_common_includes()

set(name sixlowpan)
set_lib_name(${name})
add_library(lib${name} SHARED
        model/sixlowpan-net-device.cc
        model/sixlowpan-header.cc
        helper/sixlowpan-helper.cc
        model/sixlowpan-net-device.h
        model/sixlowpan-header.h
        helper/sixlowpan-helper.h
        )

#set_test_name(${name})
#add_library(test${name} )
