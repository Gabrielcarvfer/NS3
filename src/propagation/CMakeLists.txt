NS3_common_includes()

set(name propagation)
set_lib_name(${name})
add_library(lib${name} SHARED
        model/propagation-delay-model.cc
        model/propagation-loss-model.cc
        model/jakes-propagation-loss-model.cc
        model/jakes-process.cc
        model/cost231-propagation-loss-model.cc
        model/okumura-hata-propagation-loss-model.cc
        model/itu-r-1411-los-propagation-loss-model.cc
        model/itu-r-1411-nlos-over-rooftop-propagation-loss-model.cc
        model/kun-2600-mhz-propagation-loss-model.cc
        model/propagation-delay-model.h
        model/propagation-loss-model.h
        model/jakes-propagation-loss-model.h
        model/jakes-process.h
        model/propagation-cache.h
        model/cost231-propagation-loss-model.h
        model/propagation-environment.h
        model/okumura-hata-propagation-loss-model.h
        model/itu-r-1411-los-propagation-loss-model.h
        model/itu-r-1411-nlos-over-rooftop-propagation-loss-model.h
        model/kun-2600-mhz-propagation-loss-model.h
        )

#set_test_name(${name})
#add_library(test${name} )
