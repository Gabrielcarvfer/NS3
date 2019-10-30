
set(name buildings)

set(source_files
        model/building.cc
        model/building-list.cc
        model/mobility-building-info.cc
        model/itu-r-1238-propagation-loss-model.cc
        model/buildings-propagation-loss-model.cc
        model/hybrid-buildings-propagation-loss-model.cc
        model/oh-buildings-propagation-loss-model.cc
        helper/building-container.cc
        helper/building-position-allocator.cc
        helper/building-allocator.cc
        helper/buildings-helper.cc
        )

set(header_files
        model/building.h
        model/building-list.h
        model/mobility-building-info.h
        model/itu-r-1238-propagation-loss-model.h
        model/buildings-propagation-loss-model.h
        model/hybrid-buildings-propagation-loss-model.h
        model/oh-buildings-propagation-loss-model.h
        helper/building-container.h
        helper/building-allocator.h
        helper/building-position-allocator.h
        helper/buildings-helper.h
        )

set(libraries_to_link ${libmobility} ${libpropagation} ${libconfig-store})

set(test_sources
        test/building-position-allocator-test.cc
        test/buildings-helper-test.cc
        test/buildings-pathloss-test.cc
        test/buildings-shadowing-test.cc
        )

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")



