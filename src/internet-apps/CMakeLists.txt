NS3_common_includes()

set(name internet-apps)
set(lib${name} ns${NS3_VER}-${name}-${build_type})
add_library(${lib${name}} SHARED
        model/ping6.cc
        model/ping6.h
        model/radvd-interface.cc
        model/radvd-interface.h
        model/radvd-prefix.cc
        model/radvd-prefix.h
        model/radvd.cc
        model/radvd.h
        model/v4ping.cc
        model/v4ping.h
        helper/ping6-helper.cc
        helper/radvd-helper.cc
        helper/radvd-helper.h
        helper/v4ping-helper.cc
        helper/ping6-helper.h
        helper/v4ping-helper.h

        )

#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED )
