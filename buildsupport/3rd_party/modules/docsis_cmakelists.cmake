if(APPLE OR WSLv1)
    message(FATAL_ERROR "${PLATFORM_UNSUPPORTED_PRE} fd-net-device, which is required by docsis.")
endif()

set(name docsis)

set(source_files
        model/docsis-configuration.cc
        model/docsis-channel.cc
        model/docsis-net-device.cc
        model/cm-net-device.cc
        model/cmts-net-device.cc
        model/docsis-header.cc
        model/docsis-l4s-packet-filter.cc
        model/docsis-queue-disc-item.cc
        model/cmts-upstream-scheduler.cc
        model/dual-queue-coupled-aqm.cc
        model/queue-protection.cc
        helper/docsis-helper.cc
        helper/docsis-scenario-helper.cc
        )

set(header_files
        model/docsis-channel.h
        model/docsis-net-device.h
        model/cm-net-device.h
        model/cmts-net-device.h
        model/docsis-configuration.h
        model/docsis-header.h
        model/docsis-l4s-packet-filter.h
        model/docsis-queue-disc-item.h
        model/cmts-upstream-scheduler.h
        model/dual-queue-coupled-aqm.h
        model/queue-protection.h
        model/microflow-descriptor.h
        helper/docsis-helper.h
        helper/docsis-scenario-helper.h
        )

set(libraries_to_link
        ${libcore}
        ${libnetwork}
        ${libbridge}
        ${libpoint-to-point}
        ${libtraffic-control}
        ${libflow-monitor}
        ${libstats}
        ${libapplications}
        ${libfd-net-device}
        ${libcsma}
        )

set(test_sources
        test/docsis-lld-test-suite.cc
        test/docsis-link-test-class.cc
        test/docsis-link-test-suite.cc
        test/dual-queue-test.cc
        test/dual-queue-coupled-aqm-test-suite.cc
        test/queue-protection-test-suite.cc
        )

build_contrib_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")
