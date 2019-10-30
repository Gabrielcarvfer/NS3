
set(name wave)


set(source_files
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
        )

set(header_files
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

set(libraries_to_link ${libcore} ${libpropagation} ${libwifi} ${libinternet})

set(test_sources
        test/mac-extension-test-suite.cc
        test/ocb-test-suite.cc
        )

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")

