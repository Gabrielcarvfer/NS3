NS3_common_includes()

set(name netanim)
set(lib${name} ns${NS3_VER}-${name}-${build_type})
add_library(${lib${name}} SHARED
        model/animation-interface.cc
        model/animation-interface.h
        )

#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED )
