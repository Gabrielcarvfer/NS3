
#if(${NS3_MPI})
    set(name mpi)

    set(source_files
            model/distributed-simulator-impl.cc
            model/granted-time-window-mpi-interface.cc
            model/mpi-receiver.cc
            model/null-message-simulator-impl.cc
            model/null-message-mpi-interface.cc
            model/remote-channel-bundle.cc
            model/remote-channel-bundle-manager.cc
            model/mpi-interface.cc
            )

    set(header_files
            model/mpi-receiver.h
            model/mpi-interface.h
            model/parallel-communication-interface.h
            )

    set(libraries_to_link ${libcore} ${libnetwork})

    set(test_sources)

    build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")
#endif()

