NS3_common_includes()


set(name applications)
set(lib${name} ns${NS3_VER}-${name}-${build_type})
add_library(${lib${name}} SHARED
        model/application-packet-probe.cc
        model/application-packet-probe.h
        model/bulk-send-application.cc
        model/bulk-send-application.h
        model/onoff-application.cc
        model/onoff-application.h
        model/packet-loss-counter.cc
        model/packet-loss-counter.h
        model/packet-sink.cc
        model/packet-sink.cc
        model/seq-ts-header.cc
        model/seq-ts-header.h
        model/udp-client.cc
        model/udp-client.h
        model/udp-echo-client.cc
        model/udp-echo-client.h
        model/udp-echo-server.cc
        model/udp-echo-server.h
        model/udp-server.cc
        model/udp-server.h
        model/udp-trace-client.cc
        model/udp-trace-client.h
        helper/bulk-send-helper.cc
        helper/bulk-send-helper.h
        helper/on-off-helper.cc
        helper/on-off-helper.h
        helper/packet-sink-helper.cc
        helper/packet-sink-helper.h
        helper/udp-client-server-helper.cc
        helper/udp-client-server-helper.h
        helper/udp-echo-helper.cc
        helper/udp-echo-helper.h
        )

#link to dependencies
target_link_libraries(${lib${name}} ${libinternet} ${libconfig-store} ${libstats})

set(test${name} ns${NS3_VER}-${name}-test-${build_type})
add_library(${test${name}} SHARED
        test/udp-client-server-test.cc)

target_link_libraries(${test${name}} SHARED ${lib${name}})