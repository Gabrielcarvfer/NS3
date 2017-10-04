NS3_common_includes()

set(name buildings)
set(lib${name} ns${NS3_VER}-${name}-${build_type})
add_library(${lib${name}} SHARED
        model/building.cc
        model/building.h
        model/building-list.cc
        model/building-list.h
        model/buildings-propagation-loss-model.cc
        model/buildings-propagation-loss-model.h
        model/hybrid-buildings-propagation-loss-model.cc
        model/hybrid-buildings-propagation-loss-model.h
        model/itu-r-1238-propagation-loss-model.cc
        model/itu-r-1238-propagation-loss-model.h
        model/mobility-building-info.cc
        model/mobility-building-info.h
        model/oh-buildings-propagation-loss-model.cc
        model/oh-buildings-propagation-loss-model.h
        helper/building-allocator.cc
        helper/building-allocator.h
        helper/building-container.cc
        helper/building-container.h
        helper/building-position-allocator.cc
        helper/building-position-allocator.h
        helper/buildings-helper.cc
        helper/buildings-helper.h
        )

set(test${name} ns${NS3_VER}-${name}-test-${build_type})
add_library(${test${name}} SHARED
        test/building-position-allocator-test.cc
        test/buildings-helper-test.cc
        test/buildings-pathloss-test.cc
        test/buildings-pathloss-test.h
        test/buildings-shadowing-test.cc
        test/buildings-shadowing-test.h
        )

