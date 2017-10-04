NS3_common_includes()

set(name tap-bridge)
set(lib${name} ns${NS3_VER}-${name}-${build_type})
add_library(${lib${name}} SHARED
        model/tap-bridge.cc
        model/tap-encode-decode.cc
        helper/tap-bridge-helper.cc
        model/tap-bridge.h
        model/tap-encode-decode.h
        helper/tap-bridge-helper.h
        )

#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED )
