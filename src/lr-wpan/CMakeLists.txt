NS3_common_includes()

set(name lr-wpan)
set_lib_name(${name})
add_library(lib${name} SHARED
        model/lr-wpan-error-model.cc
        model/lr-wpan-interference-helper.cc
        model/lr-wpan-phy.cc
        model/lr-wpan-mac.cc
        model/lr-wpan-mac-header.cc
        model/lr-wpan-mac-trailer.cc
        model/lr-wpan-csmaca.cc
        model/lr-wpan-net-device.cc
        model/lr-wpan-spectrum-value-helper.cc
        model/lr-wpan-spectrum-signal-parameters.cc
        model/lr-wpan-lqi-tag.cc
        helper/lr-wpan-helper.cc
        model/lr-wpan-error-model.h
        model/lr-wpan-interference-helper.h
        model/lr-wpan-phy.h
        model/lr-wpan-mac.h
        model/lr-wpan-mac-header.h
        model/lr-wpan-mac-trailer.h
        model/lr-wpan-csmaca.h
        model/lr-wpan-net-device.h
        model/lr-wpan-spectrum-value-helper.h
        model/lr-wpan-spectrum-signal-parameters.h
        model/lr-wpan-lqi-tag.h
        helper/lr-wpan-helper.h
        )

#set_test_name(${name})
#add_library(test${name} )
