
set(name stats)
set(lib${name} ns${NS3_VER}-${name}-${build_type})

if (${SQLITE_ENABLED})
    set(SQLITE_SOURCES
            model/sqlite-data-output.cc
            )
    set(SQLITE_HEADERS
            model/sqlite-data-output.h
            )
else()
    set(SQLITE_SOURCEs )
endif()

set(source_files
        ${SQLITE_SOURCES}
        helper/file-helper.cc
        helper/gnuplot-helper.cc
        model/data-calculator.cc
        model/time-data-calculators.cc
        model/data-output-interface.cc
        model/omnet-data-output.cc
        model/data-collector.cc
        model/gnuplot.cc
        model/data-collection-object.cc
        model/probe.cc
        model/boolean-probe.cc
        model/double-probe.cc
        model/time-probe.cc
        model/uinteger-8-probe.cc
        model/uinteger-16-probe.cc
        model/uinteger-32-probe.cc
        model/time-series-adaptor.cc
        model/file-aggregator.cc
        model/gnuplot-aggregator.cc
        model/get-wildcard-matches.cc
        )

set(header_files
        ${SQLITE_HEADERS}
        model/stats.h
        helper/file-helper.h
        helper/gnuplot-helper.h
        model/data-calculator.h
        model/time-data-calculators.h
        model/basic-data-calculators.h
        model/data-output-interface.h
        model/omnet-data-output.h
        model/data-collector.h
        model/gnuplot.h
        model/average.h
        model/data-collection-object.h
        model/probe.h
        model/boolean-probe.h
        model/double-probe.h
        model/time-probe.h
        model/uinteger-8-probe.h
        model/uinteger-16-probe.h
        model/uinteger-32-probe.h
        model/time-series-adaptor.h
        model/file-aggregator.h
        model/gnuplot-aggregator.h
        model/get-wildcard-matches.h
        )


set(libraries_to_link ${libcore} )

set(test_sources
        test/basic-data-calculators-test-suite.cc
        test/average-test-suite.cc
        test/double-probe-test-suite.cc
        )

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")

