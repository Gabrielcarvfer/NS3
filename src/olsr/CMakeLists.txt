
set(name olsr)

set(source_files
        model/olsr-header.cc
        model/olsr-state.cc
        model/olsr-routing-protocol.cc
        helper/olsr-helper.cc
        )

set(header_files
        model/olsr-routing-protocol.h
        model/olsr-header.h
        model/olsr-state.h
        model/olsr-repositories.h
        helper/olsr-helper.h
        )

set(libraries_to_link ${libinternet})

set(test_sources
        test/bug780-test.cc
        test/hello-regression-test.cc
        test/olsr-header-test-suite.cc
        test/regression-test-suite.cc
        test/olsr-routing-protocol-test-suite.cc
        test/tc-regression-test.cc
        )

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")


