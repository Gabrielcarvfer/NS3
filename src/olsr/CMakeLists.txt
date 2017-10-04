NS3_common_includes()

set(name olsr)
set(lib${name} ns${NS3_VER}-${name}-${build_type})
add_library(${lib${name}} SHARED
        model/olsr-header.cc
        model/olsr-state.cc
        model/olsr-routing-protocol.cc
        helper/olsr-helper.cc
        model/olsr-routing-protocol.h
        model/olsr-header.h
        model/olsr-state.h
        model/olsr-repositories.h
        helper/olsr-helper.h
        )

#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED )
