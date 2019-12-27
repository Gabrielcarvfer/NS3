if (${NS3_TAP})
    set(name tap-csma)
    set(source_files ${name}.cc)
    set(header_files)
    set(libraries_to_link ${libcsma} ${libtap-bridge} ${libinternet} ${libwifi})
    set(files_to_copy)
    build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")

    set(name tap-csma-virtual-machine)
    set(source_files ${name}.cc)
    set(header_files)
    set(libraries_to_link ${libcsma} ${libtap-bridge} ${libinternet})
    set(files_to_copy)
    build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


    set(name tap-wifi-virtual-machine)
    set(source_files ${name}.cc)
    set(header_files)
    set(libraries_to_link ${libcsma} ${libtap-bridge} ${libinternet} ${libwifi} ${libmobility})
    set(files_to_copy)
    build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


    set(name tap-wifi-dumbbell)
    set(source_files ${name}.cc)
    set(header_files)
    set(libraries_to_link ${libwifi} ${libcsma} ${libpoint-to-point} ${libtap-bridge} ${libinternet} ${libapplications})
    set(files_to_copy)
    build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")

endif()