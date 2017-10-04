NS3_common_includes()

set(name fd-net-device)
set(lib${name} ns${NS3_VER}-${name}-${build_type})
add_library(${lib${name}} SHARED
       model/fd-net-device.cc
       model/fd-net-device.h
       helper/creator-utils.cc
       helper/creator-utils.h
       #helper/emu-fd-net-device-helper.cc
       #helper/emu-fd-net-device-helper.h
       helper/encode-decode.cc
       helper/encode-decode.h
       helper/fd-net-device-helper.cc
       helper/fd-net-device-helper.h
       #helper/planetlab-fd-net-device-helper.cc
       #helper/planetlab-fd-net-device-helper.h
       #helper/planetlab-tap-creator.cc
       helper/raw-sock-creator.cc
       #helper/tap-device-creator.cc
       #helper/tap-fd-net-device-helper.cc
       #helper/tap-fd-net-device-helper.h
       )

#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED        )

#execute_process(COMMAND bindings/modulegen__gcc_ILP32.py)
#execute_process(COMMAND bindings/modulegen__gcc_LP64.py)