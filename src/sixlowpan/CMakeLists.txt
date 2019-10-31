
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

set(test_sources
        test/sixlowpan-hc1-test.cc
        test/sixlowpan-iphc-test.cc
        test/sixlowpan-fragmentation-test.cc
        )

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")


