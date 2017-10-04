NS3_common_includes()

set(name tap-bridge)
set_lib_name(${name})
add_library(lib${name} SHARED
        model/tap-bridge.cc
        model/tap-encode-decode.cc
        helper/tap-bridge-helper.cc
        model/tap-bridge.h
        model/tap-encode-decode.h
        helper/tap-bridge-helper.h
        )

#set_test_name(${name})
#add_library(test${name} )
