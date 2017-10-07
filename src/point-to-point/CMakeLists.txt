NS3_common_includes()

set(name point-to-point)

set(source_files
        model/point-to-point-net-device.cc
        model/point-to-point-channel.cc
        model/point-to-point-remote-channel.cc
        model/ppp-header.cc
        helper/point-to-point-helper.cc
        )

set(header_files
        model/point-to-point-net-device.h
        model/point-to-point-channel.h
        model/point-to-point-remote-channel.h
        model/ppp-header.h
        helper/point-to-point-helper.h
        )

set(libraries_to_link
        ${libnetwork}
        ${libmpi}
        )

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED )
