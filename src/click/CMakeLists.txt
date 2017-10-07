NS3_common_includes()

set(name click)

set(source_files
        model/ipv4-click-routing.cc
        model/ipv4-l3-click-protocol.cc
        helper/click-internet-stack-helper.cc
        )

set(header_files
        model/ipv4-click-routing.h
        model/ipv4-l3-click-protocol.h
        helper/click-internet-stack-helper.h
        )

set(libraries_to_link
        ${libcore}
        ${libnetwork}
        ${libinternet}
        )

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(test${name}
#        test/ipv4-click-routing-test.cc
#        )

