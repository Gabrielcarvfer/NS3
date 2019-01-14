
set(name test)

add_library(${lib${name}}
        ${LIB_TYPE}
        csma-system-test-suite.cc
        ns3tc/fq-codel-queue-disc-test-suite.cc
        ns3tc/pfifo-fast-queue-disc-test-suite.cc
        ns3tcp/ns3tcp-cwnd-test-suite.cc
        ns3tcp/ns3tcp-interop-test-suite.cc
        ns3tcp/ns3tcp-loss-test-suite.cc
        ns3tcp/ns3tcp-no-delay-test-suite.cc
        ns3tcp/ns3tcp-socket-test-suite.cc
        ns3tcp/ns3tcp-state-test-suite.cc
        ns3tcp/nsctcp-loss-test-suite.cc
        ns3tcp/ns3tcp-socket-writer.cc
        ns3wifi/wifi-interference-test-suite.cc
        ns3wifi/wifi-msdu-aggregator-test-suite.cc
        ns3wifi/wifi-ac-mapping-test-suite.cc
        traced/traced-callback-typedef-test-suite.cc
        traced/traced-value-callback-typedef-test-suite.cc
        ${ns3-libs-tests} # modules test libraries are built as CMake OBJECT libraries
        )

set(libraries_to_link ${ns3-libs})
list(REMOVE_ITEM libraries_to_link ${lib${name}})

target_link_libraries(${lib${name}} ${LIB_AS_NEEDED_PRE} ${libraries_to_link} ${LIB_AS_NEEDED_PRE} )
