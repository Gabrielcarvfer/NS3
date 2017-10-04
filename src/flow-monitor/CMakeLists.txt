NS3_common_includes()

set(name flow-monitor)
set_lib_name(${name})
add_library(lib${name} SHARED
        model/flow-classifier.cc
        model/flow-classifier.h
        model/flow-monitor.cc
        model/flow-monitor.h
        model/flow-probe.cc
        model/flow-probe.h
        model/histogram.cc
        model/histogram.h
        model/ipv4-flow-classifier.cc
        model/ipv4-flow-classifier.h
        model/ipv4-flow-probe.cc
        model/ipv4-flow-probe.h
        model/ipv6-flow-classifier.cc
        model/ipv6-flow-classifier.h
        model/ipv6-flow-probe.cc
        model/ipv6-flow-probe.h
        helper/flow-monitor-helper.cc
        helper/flow-monitor-helper.h
        )

set_test_name(${name})
add_library(test${name}
        test/histogram-test-suite.cc
        )
