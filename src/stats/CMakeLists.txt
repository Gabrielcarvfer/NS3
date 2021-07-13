set(name stats)

find_package(SQLite3)
check_include_file_cxx(semaphore.h HAVE_SEMAPHORE_H)
if(${SQLite3_FOUND})
  set(sqlite_sources model/sqlite-data-output.cc)
  set(sqlite_headers model/sqlite-data-output.h )

  include_directories(${SQLite3_INCLUDE_DIRS})
  set(sqlite_libraries ${SQLite3_LIBRARIES})

  if(HAVE_SEMAPHORE_H)
    list(APPEND sqlite_sources model/sqlite-output.cc)
    list(APPEND sqlite_headers model/sqlite-output.h)
  endif()
endif()

set(source_files
    ${sqlite_sources}
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
    model/histogram.cc
)

set(header_files
    ${sqlite_headers}
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
    model/histogram.h
)

set(libraries_to_link ${libcore} ${sqlite_libraries})

set(test_sources test/basic-data-calculators-test-suite.cc test/average-test-suite.cc test/double-probe-test-suite.cc
                 test/histogram-test-suite.cc
)

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")
