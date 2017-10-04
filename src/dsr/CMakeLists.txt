NS3_common_includes()

set(name dsr)
set(lib${name} ns${NS3_VER}-${name}-${build_type})
add_library(${lib${name}} SHARED
        model/dsr-errorbuff.cc
        model/dsr-errorbuff.h
        model/dsr-fs-header.cc
        model/dsr-fs-header.h
        model/dsr-gratuitous-reply-table.cc
        model/dsr-gratuitous-reply-table.h
        model/dsr-maintain-buff.cc
        model/dsr-maintain-buff.h
        model/dsr-network-queue.cc
        model/dsr-network-queue.h
        model/dsr-option-header.cc
        model/dsr-option-header.h
        model/dsr-options.cc
        model/dsr-options.h
        model/dsr-passive-buff.cc
        model/dsr-passive-buff.h
        model/dsr-rcache.cc
        model/dsr-rcache.h
        model/dsr-routing.cc
        model/dsr-routing.h
        model/dsr-rreq-table.cc
        model/dsr-rreq-table.h
        model/dsr-rsendbuff.cc
        model/dsr-rsendbuff.h
        helper/dsr-helper.cc
        helper/dsr-helper.h
        helper/dsr-main-helper.cc
        helper/dsr-main-helper.h
        )

set(test${name} ns${NS3_VER}-${name}-test-${build_type})
add_library(${test${name}} SHARED
            test/dsr-test-suite.cc)
