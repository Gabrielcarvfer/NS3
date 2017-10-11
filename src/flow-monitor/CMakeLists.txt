
set(name flow-monitor)

set(source_files
        model/flow-monitor.cc
        model/flow-classifier.cc
        model/flow-probe.cc
        model/ipv4-flow-classifier.cc
        model/ipv4-flow-probe.cc
        model/ipv6-flow-classifier.cc
        model/ipv6-flow-probe.cc
        model/histogram.cc
        helper/flow-monitor-helper.cc
        )

set(header_files
        model/flow-monitor.h
        model/flow-probe.h
        model/flow-classifier.h
        model/ipv4-flow-classifier.h
        model/ipv4-flow-probe.h
        model/ipv6-flow-classifier.h
        model/ipv6-flow-probe.h
        model/histogram.h
        helper/flow-monitor-helper.h
        )

set(libraries_to_link ${libinternet} ${libconfigstore})

set(test_sources
        test/histogram-test-suite.cc
        )

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")

