NS3_common_includes()

set(name mobility)
set(lib${name} ns${NS3_VER}-${name}-${build_type})
add_library(${lib${name}} SHARED
        model/box.cc
        model/constant-acceleration-mobility-model.cc
        model/constant-position-mobility-model.cc
        model/constant-velocity-helper.cc
        model/constant-velocity-mobility-model.cc
        model/gauss-markov-mobility-model.cc
        model/geographic-positions.cc
        model/hierarchical-mobility-model.cc
        model/mobility-model.cc
        model/position-allocator.cc
        model/random-direction-2d-mobility-model.cc
        model/random-walk-2d-mobility-model.cc
        model/random-waypoint-mobility-model.cc
        model/rectangle.cc
        model/steady-state-random-waypoint-mobility-model.cc
        model/waypoint.cc
        model/waypoint-mobility-model.cc
        helper/mobility-helper.cc
        helper/ns2-mobility-helper.cc
        model/box.h
        model/constant-acceleration-mobility-model.h
        model/constant-position-mobility-model.h
        model/constant-velocity-helper.h
        model/constant-velocity-mobility-model.h
        model/gauss-markov-mobility-model.h
        model/geographic-positions.h
        model/hierarchical-mobility-model.h
        model/mobility-model.h
        model/position-allocator.h
        model/rectangle.h
        model/random-direction-2d-mobility-model.h
        model/random-walk-2d-mobility-model.h
        model/random-waypoint-mobility-model.h
        model/steady-state-random-waypoint-mobility-model.h
        model/waypoint.h
        model/waypoint-mobility-model.h
        helper/mobility-helper.h
        helper/ns2-mobility-helper.h
        )

#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED )
