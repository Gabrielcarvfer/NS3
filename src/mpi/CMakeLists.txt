NS3_common_includes()


if (${mpi_dependencies})

set(name mpi)
set(lib${name} ns${NS3_VER}-${name}-${build_type})
add_library(${lib${name}} SHARED
        model/distributed-simulator-impl.cc
        model/granted-time-window-mpi-interface.cc
        model/mpi-receiver.cc
        model/null-message-simulator-impl.cc
        model/null-message-mpi-interface.cc
        model/remote-channel-bundle.cc
        model/remote-channel-bundle-manager.cc
        model/mpi-interface.cc
        model/mpi-receiver.h
        model/mpi-interface.h
        model/parallel-communication-interface.h
        )

#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED )

endif()