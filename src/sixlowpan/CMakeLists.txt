set(name sixlowpan)

set(source_files model/sixlowpan-net-device.cc model/sixlowpan-header.cc helper/sixlowpan-helper.cc)

set(header_files model/sixlowpan-net-device.h model/sixlowpan-header.h helper/sixlowpan-helper.h)

set(libraries_to_link ${libinternet} ${libinternet} ${libcore})

set(example_as_test_suite)
if(${NS3_EXAMPLES} AND (NOT WIN32))
  set(example_as_test_suite test/sixlowpan-examples-test-suite.cc)
endif()

set(test_sources ${example_as_test_suite} test/mock-net-device.cc test/sixlowpan-hc1-test.cc
                 test/sixlowpan-iphc-test.cc test/sixlowpan-iphc-stateful-test.cc test/sixlowpan-fragmentation-test.cc
)

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")
