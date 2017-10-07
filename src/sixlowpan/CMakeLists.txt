NS3_common_includes()

set(name sixlowpan)

set(source_files
        model/sixlowpan-net-device.cc
        model/sixlowpan-header.cc
        helper/sixlowpan-helper.cc
        )

set(header_files
        model/sixlowpan-net-device.h
        model/sixlowpan-header.h
        helper/sixlowpan-helper.h
        )

set(libraries_to_link ${libinternet} ${libinternet} ${libcore})

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED )
