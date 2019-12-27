if(${NS3_CLICK})
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

    set(test_sources
            test/ipv4-click-routing-test.cc
            )

    build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")
endif()


