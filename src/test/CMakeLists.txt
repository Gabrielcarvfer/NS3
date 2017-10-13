
set(name test)

set(test${name} ns${NS3_VER}-${name}-${build_type})
add_library(${test${name}} SHARED
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
        )

target_link_libraries(${test${name}}
        ${libapplications}
        ${libbridge}
        ${libconfig-store}
        ${libcsma}
        ${libcsma-layout}
        ${libdsr}
        ${libflow-monitor}
        ${libinternet}
        ${liblr-wpan}
        ${liblte}
        ${libmesh}
        ${libmobility}
        ${libolsr}
        ${libpoint-to-point}
        ${libsixlowpan}
        ${libstats}
        ${libuan}
        ${libwifi}
        ${libinternet-apps}
        ${libpoint-to-point-layout}
        ${libtraffic-control}
        )
