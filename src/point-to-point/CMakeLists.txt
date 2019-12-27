
set(name point-to-point)


set(mpi_sources)
set(mpi_headers)
set(mpi_libraries)

#if (${NS3_MPI})
    set(mpi_sources
            model/point-to-point-remote-channel.cc
            )
    set(mpi_headers
            model/point-to-point-remote-channel.h
            )
    set(mpi_libraries
            ${libmpi}
            )
#endif()

set(source_files
        ${mpi_sources}
        model/point-to-point-net-device.cc
        model/point-to-point-channel.cc
        model/ppp-header.cc
        helper/point-to-point-helper.cc
        )

set(header_files
        ${mpi_headers}
        model/point-to-point-net-device.h
        model/point-to-point-channel.h
        model/ppp-header.h
        helper/point-to-point-helper.h
        )

set(libraries_to_link
        ${libnetwork}
        ${mpi_libraries}
        )

set(test_sources
        test/point-to-point-test.cc
        )

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")


