NS3_common_includes()

set(name energy)
set(lib${name} ns${NS3_VER}-${name}-${build_type})
add_library(${lib${name}} SHARED
        model/basic-energy-harvester.cc
        model/basic-energy-harvester.h
        model/basic-energy-source.cc
        model/basic-energy-source.h
        model/device-energy-model.cc
        model/device-energy-model.h
        model/device-energy-model-container.cc
        model/device-energy-model-container.h
        model/energy-harvester.cc
        model/energy-harvester.h
        model/energy-source.cc
        model/energy-source.h
        model/li-ion-energy-source.cc
        model/li-ion-energy-source.h
        model/rv-battery-model.cc
        model/rv-battery-model.h
        model/simple-device-energy-model.cc
        model/simple-device-energy-model.h
        helper/basic-energy-harvester-helper.cc
        helper/basic-energy-harvester-helper.h
        helper/basic-energy-source-helper.cc
        helper/basic-energy-source-helper.h
        helper/energy-harvester-container.cc
        helper/energy-harvester-container.h
        helper/energy-harvester-helper.cc
        helper/energy-harvester-helper.h
        helper/energy-model-helper.cc
        helper/energy-model-helper.h
        helper/energy-source-container.cc
        helper/energy-source-container.h
        helper/li-ion-energy-source-helper.cc
        helper/li-ion-energy-source-helper.h
        helper/rv-battery-model-helper.cc
        helper/rv-battery-model-helper.h
        )

set(test${name} ns${NS3_VER}-${name}-test-${build_type})
add_library(${test${name}} SHARED
            test/basic-energy-harvester-test.cc
            test/li-ion-energy-source-test.cc
        )
