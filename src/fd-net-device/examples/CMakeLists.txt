if(${NS3_EMU})
    set(name dummy-network)
    set(source_files ${name}.cc)
    set(header_files)
    set(libraries_to_link ${libfd-net-device} ${libinternet} ${libinternet-apps})
    set(files_to_copy)
    build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")

    set(name fd2fd-onoff)
    set(source_files ${name}.cc)
    set(header_files)
    set(libraries_to_link ${libfd-net-device} ${libinternet} ${libapplications})
    set(files_to_copy)
    build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")

    set(name fd-emu-ping)
    set(source_files ${name}.cc)
    set(header_files)
    set(libraries_to_link ${libfd-net-device} ${libinternet} ${libinternet-apps})
    build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


    set(name fd-emu-udp-echo)
    set(source_files ${name}.cc)
    set(header_files)
    set(libraries_to_link ${libfd-net-device} ${libinternet} ${libapplications})
    build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


    set(name fd-emu-onoff)
    set(source_files ${name}.cc)
    set(header_files)
    set(libraries_to_link ${libfd-net-device} ${libinternet} ${libapplications})
    build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")

    if(${NS3_REALTIME})
        set(name realtime-dummy-network)
        set(source_files ${name}.cc)
        set(header_files)
        set(libraries_to_link ${libfd-net-device} ${libinternet} ${libinternet-apps})
        build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


        set(name realtime-fd2fd-onoff)
        set(source_files ${name}.cc)
        set(header_files)
        set(libraries_to_link ${libfd-net-device} ${libinternet} ${libapplications})
        build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")
    endif()

    if(${NS3_TAP})
        set(name fd-tap-ping)
        set(source_files ${name}.cc)
        set(header_files)
        set(libraries_to_link ${libfd-net-device} ${libinternet} ${libinternet-apps})
        build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


        set(name fd-tap-ping6)
        set(source_files ${name}.cc)
        set(header_files)
        set(libraries_to_link ${libfd-net-device} ${libinternet} ${libinternet-apps} ${libcsma})
        build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")
    endif()

    if(${NS3_PLANETLAB})
        set(name fd-planetlab-ping)
        set(source_files ${name}.cc)
        set(header_files)
        set(libraries_to_link ${libfd-net-device} ${libinternet} ${libinternet-apps})
        build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")
    endif()

endif()
