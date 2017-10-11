
set(name fd-net-device)

if(${TAP_FOUND})
    set(tap_sources
            helper/tap-fd-net-device-helper.cc
            )
    set(tap_headers
            helper/tap-fd-net-device-helper.h
            )
    add_executable(tap-device-creator
            helper/tap-device-creator.cc
            helper/encode-decode.cc
            helper/creator-utils.cc
            )
    target_link_libraries(tap-device-creator ${TAP_LIBRARIES})
endif()

if(${EMU_FOUND})
    set(emu_sources
            helper/emu-fd-net-device-helper.cc
            )
    set(emu_headers
            helper/emu-fd-net-device-helper.h
            )
    add_executable(raw-sock-creator
            helper/raw-sock-creator.cc
            helper/encode-decode.cc
            helper/creator-utils.cc
            )
    target_link_libraries(raw-sock-creator ${EMU_LIBRARIES})
endif()

if(${PLANETLAB_FOUND})
    set(planetlab_sources
            helper/planetlab-fd-net-device-helper.cc
            )
    set(planetlab_headers
            helper/planetlab-fd-net-device-helper.h
            )
    add_executable(planetlab-tap-creator
            helper/planetlab-tap-creator.cc
            helper/encode-decode.cc
            helper/creator-utils.cc
            )
    target_link_libraries(planetlab-tap-creator ${PLANETLAB_LIBRARIES})
endif()

set(source_files
        ${tap_sources}
        ${emu_sources}
        ${planetlab_sources}
        model/fd-net-device.cc
        helper/fd-net-device-helper.cc
        helper/encode-decode.cc
        helper/creator-utils.cc
       )

set(header_files
        ${tap_headers}
        ${emu_sources}
        ${planetlab_sources}
        model/fd-net-device.h
        helper/fd-net-device-helper.h
        )

set(libraries_to_link ${libnetwork})

set(test_sources)

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")


