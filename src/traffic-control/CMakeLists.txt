set(name traffic-control)
set(source_files
    model/traffic-control-layer.cc
    model/packet-filter.cc
    model/queue-disc.cc
    model/pfifo-fast-queue-disc.cc
    model/red-queue-disc.cc
    model/codel-queue-disc.cc
    model/fq-codel-queue-disc.cc
    model/pie-queue-disc.cc
    helper/traffic-control-helper.cc
    helper/queue-disc-container.cc
    model/mq-queue-disc.cc
    model/fifo-queue-disc.cc
    model/tbf-queue-disc.cc
    model/prio-queue-disc.cc
    model/cobalt-queue-disc.cc
    model/fq-cobalt-queue-disc.cc
    model/fq-pie-queue-disc.cc
)

set(header_files
    model/traffic-control-layer.h
    model/packet-filter.h
    model/queue-disc.h
    model/pfifo-fast-queue-disc.h
    model/red-queue-disc.h
    model/codel-queue-disc.h
    model/fq-codel-queue-disc.h
    model/pie-queue-disc.h
    helper/traffic-control-helper.h
    helper/queue-disc-container.h
    model/mq-queue-disc.h
    model/fifo-queue-disc.h
    model/tbf-queue-disc.h
    model/prio-queue-disc.h
    model/cobalt-queue-disc.h
    model/fq-cobalt-queue-disc.h
    model/fq-pie-queue-disc.h
)

set(libraries_to_link ${libnetwork} ${libcore} ${libconfig-store})

set(test_sources
    test/red-queue-disc-test-suite.cc
    test/codel-queue-disc-test-suite.cc
    test/adaptive-red-queue-disc-test-suite.cc
    test/pie-queue-disc-test-suite.cc
    test/fifo-queue-disc-test-suite.cc
    test/prio-queue-disc-test-suite.cc
    test/queue-disc-traces-test-suite.cc
    test/tbf-queue-disc-test-suite.cc
    test/tc-flow-control-test-suite.cc
    test/cobalt-queue-disc-test-suite.cc
)

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")
