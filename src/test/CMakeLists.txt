
set(name test)

set(nsc_sources )
if (${NS3_NSC})
    set(nsc_sources
            ns3tcp/nsctcp-loss-test-suite.cc
            ns3tcp/ns3tcp-interop-test-suite.cc
            ns3tcp/ns3tcp-cwnd-test-suite.cc
            )
endif()

add_library(${lib${name}}
        OBJECT
        ${nsc_sources}
        csma-system-test-suite.cc
        ns3tc/fq-codel-queue-disc-test-suite.cc
        ns3tc/pfifo-fast-queue-disc-test-suite.cc
        ns3tcp/ns3tcp-loss-test-suite.cc
        ns3tcp/ns3tcp-no-delay-test-suite.cc
        ns3tcp/ns3tcp-socket-test-suite.cc
        ns3tcp/ns3tcp-state-test-suite.cc
        ns3tcp/ns3tcp-socket-writer.cc
        ns3wifi/wifi-interference-test-suite.cc
        ns3wifi/wifi-msdu-aggregator-test-suite.cc
        ns3wifi/wifi-ac-mapping-test-suite.cc
        traced/traced-callback-typedef-test-suite.cc
        traced/traced-value-callback-typedef-test-suite.cc
        )
