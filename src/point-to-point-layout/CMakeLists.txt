NS3_common_includes()

set(name point-to-point-layout)
set_lib_name(${name})
add_library(lib${name} SHARED
        model/point-to-point-dumbbell.cc
        model/point-to-point-grid.cc
        model/point-to-point-star.cc
        model/point-to-point-dumbbell.h
        model/point-to-point-grid.h
        model/point-to-point-star.h
        )

#set_test_name(${name})
#add_library(test${name} )
