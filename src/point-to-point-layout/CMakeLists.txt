NS3_common_includes()

set(name point-to-point-layout)
set(lib${name} ns${NS3_VER}-${name}-${build_type})
add_library(${lib${name}} SHARED
        model/point-to-point-dumbbell.cc
        model/point-to-point-grid.cc
        model/point-to-point-star.cc
        model/point-to-point-dumbbell.h
        model/point-to-point-grid.h
        model/point-to-point-star.h
        )

#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED )
