# Copyright (c) 2017-2021 Universidade de Brasília
#
# This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public
# License version 2 as published by the Free Software Foundation;
#
# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
# warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with this program; if not, write to the Free
# Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
# Author: Gabriel Ferreira <gabrielcarvfer@gmail.com>

# Set module name
set(name core)

# Set lib core link dependencies
set(libraries_to_link)

set(gsl_test_sources)
if(${GSL_FOUND})
  include_directories(${GSL_INCLUDE_DIRS})
  set(libraries_to_link ${libraries_to_link} ${GSL_LIBRARIES})
  set(gsl_test_sources test/rng-test-suite.cc test/random-variable-stream-test-suite.cc)
endif()

# Check for dependencies and add sources accordingly
check_include_file_cxx("boost/units/quantity.hpp" HAVE_BOOST_UNITS_QUANTITY)
check_include_file_cxx("boost/units/systems/si.hpp" HAVE_BOOST_UNITS_SI)
if((NOT HAVE_BOOST_UNITS_QUANTITY) OR (NOT HAVE_BOOST_UNITS_SI))
  message(WARNING "Boost Units are an optional feature of length.cc."
                  " Ubuntu ships it within the libboost-dev package."
                  " You may need to clean up the CMake cache after installing it to pass this check."
  )
else()
  add_definitions(-DHAVE_BOOST -DHAVE_BOOST_UNITS)
endif()

set(rt_sources)
set(rt_headers)
if(${ENABLE_REALTIME})
  set(rt_sources model/realtime-simulator-impl.cc model/wall-clock-synchronizer.cc)
  set(rt_headers model/realtime-simulator-impl.h model/wall-clock-synchronizer.h)
  set(libraries_to_link ${libraries_to_link} ${LIBRT})
endif()

set(osclock_sources)
if(WIN32)
  set(osclock_sources model/win32-system-wall-clock-ms.cc)
else()
  set(osclock_sources model/unix-system-wall-clock-ms.cc)
endif()

set(int64x64_sources)
set(int64x64_headers)

if(${INT64X64} MATCHES "INT128")
  set(int64x64_sources model/int64x64-128.cc)
  set(int64x64_headers model/int64x64-128.h)
elseif(${INT64X64} MATCHES "DOUBLE")
  set(int64x64_headers model/int64x64-double.h)
elseif(${INT64X64} MATCHES "CAIRO")
  set(int64x64_sources model/int64x64-cairo.cc)
  set(int64x64_headers model/cairo-wideint-private.h model/int64x64-cairo.h)
endif()

set(thread_sources)
set(thread_headers)
set(thread_test_sources)

if(${THREADS_ENABLED})
  if(WIN32)
      set(thread_sources model/win32-fd-reader.cc)
      set(thread_headers model/win32-fd-reader.h)
    else()
      set(thread_sources model/unix-fd-reader.cc)
      set(thread_headers model/unix-fd-reader.h)
    endif()

    if (${PTHREADS_FOUND})
      if(WIN32)
        set(libraries_to_link ${libraries_to_link} wsock32 ws2_32)
      endif()

      set(libraries_to_link ${libraries_to_link} pthread)
      set(thread_sources
              ${thread_sources}
              model/system-thread.cc
              model/unix-system-mutex.cc
              model/unix-system-condition.cc
              )
    else()
      set(thread_sources
              ${thread_sources}
              model/cpp-system-thread.cc
              model/cpp-system-mutex.cc
              model/cpp-system-condition.cc
              )
    endif()
    set(thread_headers ${thread_headers} model/system-mutex.h model/system-thread.h model/system-condition.h)
    set(thread_test_sources test/threaded-test-suite.cc)
endif()

if(WSLv1)
  set(wslv1_sources ${PROJECT_SOURCE_DIR}/buildsupport/wslv1_workaround.cc)
endif()

if(${NS3_EXAMPLES} AND (NOT WIN32))
  set(example_as_test_sources model/example-as-test.cc)
  set(example_as_test_headers model/example-as-test.h)
  set(example_as_test_suite test/examples-as-tests-test-suite.cc)
endif()

# Embedded version support
set(embedded_version_sources)
set(embedded_version_headers)
if(${NS3_ENABLE_BUILD_VERSION})
  set(embedded_version_sources model/version.cc)
  set(embedded_version_headers model/version.h)
endif()

# Define core lib sources
set(source_files
    ${wslv1_sources}
    ${rt_sources}
    ${osclock_sources}
    ${int64x64_sources}
    ${thread_sources}
    ${valgrind_sources}
    ${example_as_test_sources}
    ${embedded_version_sources}
    model/time.cc
    model/event-id.cc
    model/scheduler.cc
    model/list-scheduler.cc
    model/map-scheduler.cc
    model/heap-scheduler.cc
    model/calendar-scheduler.cc
    model/priority-queue-scheduler.cc
    model/event-impl.cc
    model/simulator.cc
    model/simulator-impl.cc
    model/default-simulator-impl.cc
    model/timer.cc
    model/watchdog.cc
    model/synchronizer.cc
    model/make-event.cc
    model/log.cc
    model/breakpoint.cc
    model/type-id.cc
    model/attribute-construction-list.cc
    model/object-base.cc
    model/ref-count-base.cc
    model/object.cc
    model/test.cc
    model/random-variable-stream.cc
    model/rng-seed-manager.cc
    model/rng-stream.cc
    model/command-line.cc
    model/type-name.cc
    model/attribute.cc
    model/boolean.cc
    model/integer.cc
    model/uinteger.cc
    model/enum.cc
    model/double.cc
    model/int64x64.cc
    model/string.cc
    model/pointer.cc
    model/object-ptr-container.cc
    model/object-factory.cc
    model/global-value.cc
    model/trace-source-accessor.cc
    model/config.cc
    model/callback.cc
    model/names.cc
    model/vector.cc
    model/fatal-impl.cc
    model/system-path.cc
    helper/random-variable-stream-helper.cc
    helper/event-garbage-collector.cc
    model/hash-function.cc
    model/hash-murmur3.cc
    model/hash-fnv.cc
    model/hash.cc
    model/des-metrics.cc
    model/ascii-file.cc
    model/node-printer.cc
    model/show-progress.cc
    model/time-printer.cc
    model/system-wall-clock-timestamp.cc
    model/length.cc
    model/trickle-timer.cc
    helper/csv-reader.cc
)

# Define core lib headers
set(header_files
    ${rt_headers}
    ${int64x64_headers}
    ${thread_headers}
    ${example_as_test_headers}
    ${embedded_version_headers}
    model/valgrind.h
    model/nstime.h
    model/event-id.h
    model/event-impl.h
    model/simulator.h
    model/simulator-impl.h
    model/default-simulator-impl.h
    model/scheduler.h
    model/list-scheduler.h
    model/map-scheduler.h
    model/heap-scheduler.h
    model/calendar-scheduler.h
    model/priority-queue-scheduler.h
    model/simulation-singleton.h
    model/singleton.h
    model/timer.h
    model/timer-impl.h
    model/watchdog.h
    model/synchronizer.h
    model/make-event.h
    model/system-wall-clock-ms.h
    model/system-wall-clock-timestamp.h
    model/empty.h
    model/callback.h
    model/object-base.h
    model/ref-count-base.h
    model/simple-ref-count.h
    model/type-id.h
    model/attribute-construction-list.h
    model/ptr.h
    model/object.h
    model/log.h
    model/log-macros-enabled.h
    model/log-macros-disabled.h
    model/assert.h
    model/breakpoint.h
    model/fatal-error.h
    model/test.h
    model/random-variable-stream.h
    model/rng-seed-manager.h
    model/rng-stream.h
    model/command-line.h
    model/type-name.h
    model/type-traits.h
    model/int-to-type.h
    model/attribute.h
    model/attribute-accessor-helper.h
    model/attribute-container.h
    model/attribute-container-accessor-helper.h
    model/boolean.h
    model/int64x64.h
    model/int64x64-double.h
    model/integer.h
    model/uinteger.h
    model/double.h
    model/enum.h
    model/string.h
    model/pointer.h
    model/object-factory.h
    model/attribute-helper.h
    model/global-value.h
    model/traced-callback.h
    model/traced-value.h
    model/trace-source-accessor.h
    model/config.h
    model/object-ptr-container.h
    model/object-vector.h
    model/object-map.h
    model/deprecated.h
    model/abort.h
    model/names.h
    model/vector.h
    model/default-deleter.h
    model/fatal-impl.h
    model/system-path.h
    model/unused.h
    model/math.h
    helper/event-garbage-collector.h
    helper/random-variable-stream-helper.h
    model/hash-function.h
    model/hash-murmur3.h
    model/hash-fnv.h
    model/hash.h
    model/non-copyable.h
    model/build-profile.h
    model/des-metrics.h
    model/ascii-file.h
    model/ascii-test.h
    model/node-printer.h
    model/show-progress.h
    model/time-printer.h
    model/pair.h
    model/length.h
    model/trickle-timer.h
    helper/csv-reader.h
)

set(test_sources
    ${example_as_test_suite}
    ${gsl_test_sources}
    ${thread_test_sources}
    test/attribute-test-suite.cc
    test/attribute-container-test-suite.cc
    test/build-profile-test-suite.cc
    test/callback-test-suite.cc
    test/command-line-test-suite.cc
    test/config-test-suite.cc
    test/global-value-test-suite.cc
    test/int64x64-test-suite.cc
    test/names-test-suite.cc
    test/object-test-suite.cc
    test/ptr-test-suite.cc
    test/event-garbage-collector-test-suite.cc
    test/many-uniform-random-variables-one-get-value-call-test-suite.cc
    test/one-uniform-random-variable-many-get-value-calls-test-suite.cc
    test/pair-value-test-suite.cc
    test/sample-test-suite.cc
    test/simulator-test-suite.cc
    test/time-test-suite.cc
    test/timer-test-suite.cc
    test/traced-callback-test-suite.cc
    test/type-traits-test-suite.cc
    test/watchdog-test-suite.cc
    test/hash-test-suite.cc
    test/type-id-test-suite.cc
    test/length-test-suite.cc
    test/trickle-timer-test-suite.cc
)

# Build core lib
build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")

if(WSLv1)
  target_compile_definitions(${libcore-obj} PRIVATE -D__WSLv1__)
endif()
