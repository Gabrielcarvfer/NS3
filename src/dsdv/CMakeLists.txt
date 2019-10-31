
set(name dsdv)

set(source_files
        model/dsdv-rtable.cc
        model/dsdv-packet-queue.cc
        model/dsdv-packet.cc
        model/dsdv-routing-protocol.cc
        helper/dsdv-helper.cc
        )

set(header_files
        model/dsdv-rtable.h
        model/dsdv-packet-queue.h
        model/dsdv-packet.h
        model/dsdv-routing-protocol.h
        helper/dsdv-helper.h
        )

set(libraries_to_link ${libinternet})

set(test_sources
        test/dsdv-testcase.cc
        )

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")


