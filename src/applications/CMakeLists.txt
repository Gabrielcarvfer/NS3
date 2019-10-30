

set(name applications)

set(source_files
        model/bulk-send-application.cc
        model/onoff-application.cc
        model/packet-sink.cc
        model/udp-client.cc
        model/udp-server.cc
        model/seq-ts-header.cc
        model/udp-trace-client.cc
        model/packet-loss-counter.cc
        model/udp-echo-client.cc
        model/udp-echo-server.cc
        model/application-packet-probe.cc
        model/three-gpp-http-client.cc
        model/three-gpp-http-header.cc
        model/three-gpp-http-server.cc
        model/three-gpp-http-variables.cc
        helper/bulk-send-helper.cc
        helper/on-off-helper.cc
        helper/packet-sink-helper.cc
        helper/udp-client-server-helper.cc
        helper/udp-echo-helper.cc
        helper/three-gpp-http-helper.cc
        )

set(header_files
        model/bulk-send-application.h
        model/onoff-application.h
        model/packet-sink.h
        model/udp-client.h
        model/udp-server.h
        model/seq-ts-header.h
        model/udp-trace-client.h
        model/packet-loss-counter.h
        model/udp-echo-client.h
        model/udp-echo-server.h
        model/application-packet-probe.h
        model/three-gpp-http-client.h
        model/three-gpp-http-header.h
        model/three-gpp-http-server.h
        model/three-gpp-http-variables.h
        helper/bulk-send-helper.h
        helper/on-off-helper.h
        helper/packet-sink-helper.h
        helper/udp-client-server-helper.h
        helper/udp-echo-helper.h
        helper/three-gpp-http-helper.h
        )

#link to dependencies
set(libraries_to_link
        ${libinternet}
        ${libconfig-store}
        ${libstats}
        )

set(test_sources
        test/udp-client-server-test.cc
        test/three-gpp-http-client-server-test.cc
        )

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")

