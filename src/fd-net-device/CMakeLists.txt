
set(name fd-net-device)

set(fd-net-device_creators)

if(${NS3_TAP})
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
    if (WIN32)
        set(tap_dev_creator tap-device-creator.exe)
    else()
        set(tap_dev_creator tap-device-creator)
    endif()
    add_definitions(-DTAP_DEV_CREATOR="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${tap_dev_creator}")
    list(APPEND fd-net-device_creators tap-device-creator)
endif()

if(${NS3_EMU})
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
    if(WIN32)
        set(raw_sock_creator raw-sock-creator.exe)
    else()
        set(raw_sock_creator raw-sock-creator)
    endif()
    add_definitions(-DRAW_SOCK_CREATOR="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${raw_sock_creator}")

    list(APPEND fd-net-device_creators raw-sock-creator)
endif()

if(${NS3_PLANETLAB})
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
    if(WIN32)
        set(planet_tap_creator planetlab-tap-creator.exe)
    else()
        set(planet_tap_creator planetlab-tap-creator)
    endif()
    add_definitions(-DPLANETLAB_TAP_CREATOR="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${planet_tap_creator}")
    target_link_libraries(planetlab-tap-creator ${PLANETLAB_LIBRARIES})

    list(APPEND fd-net-device_creators planetlab-tap-creator)
endif()

set(source_files
        "${tap_sources}"
        "${emu_sources}"
        "${planetlab_sources}"
        model/fd-net-device.cc
        helper/fd-net-device-helper.cc
        helper/encode-decode.cc
        helper/creator-utils.cc
       )

set(header_files
        "${tap_headers}"
        "${emu_headers}"
        "${planetlab_headers}"
        model/fd-net-device.h
        helper/fd-net-device-helper.h
        )

set(libraries_to_link ${libnetwork})

set(test_sources)

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")

list(LENGTH fd-net-device_creators num_creators)
if(${num_creators} GREATER 0)
    add_dependencies(${libfd-net-device} ${fd-net-device_creators})
endif()



