NS3_common_includes()

set(name wave)
set(lib${name} ns${NS3_VER}-${name}-${build_type})
add_library(${lib${name}} SHARED
        model/wave-mac-low.cc
        model/ocb-wifi-mac.cc
        model/vendor-specific-action.cc
        model/channel-coordinator.cc
        model/channel-scheduler.cc
        model/default-channel-scheduler.cc
        model/channel-manager.cc
        model/vsa-manager.cc
        model/bsm-application.cc
        model/higher-tx-tag.cc
        model/wave-net-device.cc
        helper/wave-bsm-stats.cc
        helper/wave-mac-helper.cc
        helper/wave-helper.cc
        helper/wifi-80211p-helper.cc
        helper/wave-bsm-helper.cc
        model/wave-mac-low.h
        model/ocb-wifi-mac.h
        model/vendor-specific-action.h
        model/channel-coordinator.h
        model/channel-manager.h
        model/channel-scheduler.h
        model/default-channel-scheduler.h
        model/vsa-manager.h
        model/higher-tx-tag.h
        model/wave-net-device.h
        model/bsm-application.h
        helper/wave-bsm-stats.h
        helper/wave-mac-helper.h
        helper/wave-helper.h
        helper/wifi-80211p-helper.h
        helper/wave-bsm-helper.h
        )

#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED )
