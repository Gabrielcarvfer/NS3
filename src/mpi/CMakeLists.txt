set(name mpi)

include_directories(${MPI_CXX_INCLUDE_DIRS})

set(source_files
    model/distributed-simulator-impl.cc
    model/granted-time-window-mpi-interface.cc
    model/mpi-receiver.cc
    model/null-message-simulator-impl.cc
    model/null-message-mpi-interface.cc
    model/remote-channel-bundle.cc
    model/remote-channel-bundle-manager.cc
    model/mpi-interface.cc
    model/parallel-communication-interface.h
)

set(header_files model/mpi-receiver.h model/mpi-interface.h model/parallel-communication-interface.h)

set(libraries_to_link ${libcore} ${libnetwork} ${MPI_CXX_LIBRARIES})

set(example_as_test_suite)
if(${NS3_EXAMPLES} AND (NOT WIN32))
  set(example_as_test_suite test/mpi-test-suite.cc)
endif()

set(test_sources ${example_as_test_suite})

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")
