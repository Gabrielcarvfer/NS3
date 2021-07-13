set(name openflow)

set(source_files model/openflow-interface.cc model/openflow-switch-net-device.cc helper/openflow-switch-helper.cc)

set(header_files model/openflow-interface.h model/openflow-switch-net-device.h helper/openflow-switch-helper.h)

set(libraries_to_link ${libinternet} openflow_dep)

set(test_sources test/openflow-switch-test-suite.cc)

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")
