
set(name dsr)
set(source_files
        model/dsr-routing.cc
        model/dsr-options.cc
        model/dsr-fs-header.cc
        model/dsr-option-header.cc
        model/dsr-maintain-buff.cc
        model/dsr-passive-buff.cc
        model/dsr-rsendbuff.cc
        model/dsr-rcache.cc
        model/dsr-rreq-table.cc
        model/dsr-gratuitous-reply-table.cc
        model/dsr-errorbuff.cc
        model/dsr-network-queue.cc
        helper/dsr-helper.cc
        helper/dsr-main-helper.cc
        )

set(header_files
        model/dsr-routing.h
        model/dsr-options.h
        model/dsr-fs-header.h
        model/dsr-option-header.h
        model/dsr-maintain-buff.h
        model/dsr-passive-buff.h
        model/dsr-rsendbuff.h
        model/dsr-rcache.h
        model/dsr-rreq-table.h
        model/dsr-gratuitous-reply-table.h
        model/dsr-errorbuff.h
        model/dsr-network-queue.h
        helper/dsr-helper.h
        helper/dsr-main-helper.h
        )

set(libraries_to_link ${libinternet} ${libwifi})

set(test_sources
        test/dsr-test-suite.cc
        )

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")


