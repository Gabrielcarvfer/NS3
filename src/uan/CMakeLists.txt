set(name uan)

set(source_files
    model/uan-channel.cc
    model/uan-phy-gen.cc
    model/uan-mac.cc
    model/uan-transducer.cc
    model/uan-transducer-hd.cc
    model/uan-net-device.cc
    model/uan-tx-mode.cc
    model/uan-prop-model.cc
    model/uan-prop-model-ideal.cc
    model/uan-mac-aloha.cc
    model/uan-header-common.cc
    model/uan-noise-model-default.cc
    model/uan-mac-cw.cc
    model/uan-prop-model-thorp.cc
    model/uan-phy-dual.cc
    model/uan-header-rc.cc
    model/uan-mac-rc.cc
    model/uan-mac-rc-gw.cc
    model/uan-phy.cc
    model/uan-noise-model.cc
    model/acoustic-modem-energy-model.cc
    helper/uan-helper.cc
    helper/acoustic-modem-energy-model-helper.cc
)

set(header_files
    model/uan-channel.h
    model/uan-phy.h
    model/uan-mac.h
    model/uan-net-device.h
    model/uan-prop-model.h
    model/uan-tx-mode.h
    model/uan-transducer.h
    model/uan-phy-gen.h
    model/uan-transducer-hd.h
    model/uan-prop-model-ideal.h
    model/uan-mac-aloha.h
    model/uan-header-common.h
    model/uan-noise-model.h
    model/uan-noise-model-default.h
    model/uan-mac-cw.h
    model/uan-prop-model-thorp.h
    model/uan-phy-dual.h
    model/uan-header-rc.h
    model/uan-mac-rc.h
    model/acoustic-modem-energy-model.h
    helper/uan-helper.h
    helper/acoustic-modem-energy-model-helper.h
    model/uan-mac-rc-gw.h
)

set(libraries_to_link ${libnetwork} ${libmobility} ${libenergy})

set(test_sources test/uan-test.cc test/uan-energy-model-test.cc)

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")
