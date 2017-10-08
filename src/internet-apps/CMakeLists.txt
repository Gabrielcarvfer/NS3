NS3_common_includes()

set(name internet-apps)

set(source_files
        model/ping6.cc
        model/radvd-interface.cc
        model/radvd-prefix.cc
        model/radvd.cc
        model/v4ping.cc
        helper/ping6-helper.cc
        helper/radvd-helper.cc
        helper/v4ping-helper.cc
        )

set(header_files
        model/ping6.h
        model/radvd.h
        model/radvd-interface.h
        model/radvd-prefix.h
        model/v4ping.h
        helper/ping6-helper.h
        helper/v4ping-helper.h
        helper/radvd-helper.h
        )

set(libraries_to_link ${libinternet})

set(test_sources)

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")

