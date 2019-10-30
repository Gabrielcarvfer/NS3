
set(name bridge)

set(source_files
        model/bridge-channel.cc
        model/bridge-net-device.cc
        helper/bridge-helper.cc
        )

set(header_files
        model/bridge-channel.h
        model/bridge-net-device.h
        helper/bridge-helper.h
        )


#link to dependencies
set(libraries_to_link ${libnetwork})

set(test_sources
        )

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")
