NS3_common_includes()

set(name olsr)
set_lib_name(${name})
add_library(lib${name} SHARED
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

#set_test_name(${name})
#add_library(test${name} )
