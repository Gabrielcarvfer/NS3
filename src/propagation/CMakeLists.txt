
set(name propagation)

set(source_files
        model/propagation-delay-model.cc
        model/propagation-loss-model.cc
        model/jakes-propagation-loss-model.cc
        model/jakes-process.cc
        model/cost231-propagation-loss-model.cc
        model/okumura-hata-propagation-loss-model.cc
        model/itu-r-1411-los-propagation-loss-model.cc
        model/itu-r-1411-nlos-over-rooftop-propagation-loss-model.cc
        model/kun-2600-mhz-propagation-loss-model.cc
        )

set(header_files
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

set(libraries_to_link ${libnetwork} ${libmobility} )

set(test_sources
        test/propagation-loss-model-test-suite.cc
        test/okumura-hata-test-suite.cc
        test/itu-r-1411-los-test-suite.cc
        test/kun-2600-mhz-test-suite.cc
        test/itu-r-1411-nlos-over-rooftop-test-suite.cc
        )

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")

