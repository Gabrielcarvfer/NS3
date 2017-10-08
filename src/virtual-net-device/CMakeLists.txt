NS3_common_includes()

set(name virtual-net-device)

set(source_files
        model/virtual-net-device.cc
        )

set(header_files
        model/virtual-net-device.h
        )

set(libraries_to_link ${libnetwork})

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED )
