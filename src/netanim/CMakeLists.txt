NS3_common_includes()

set(name netanim)
set_lib_name(${name})
add_library(lib${name} SHARED
        model/animation-interface.cc
        model/animation-interface.h
        )

#set_test_name(${name})
#add_library(test${name} )
