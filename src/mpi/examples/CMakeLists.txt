if(${NS3_MPI})
    set(name simple-distributed)
    set(source_files ${name}.cc)
    set(header_files)
    set(libraries_to_link ${libpoint-to-point} ${libinternet} ${libnix-vector-routing} ${libapplications})
    set(files_to_copy)
    build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


    set(name third-distributed)
    set(source_files ${name}.cc)
    set(header_files)
    set(libraries_to_link ${libpoint-to-point} ${libinternet} ${libmobility} ${libwifi} ${libcsma} ${libapplications})
    set(files_to_copy)
    build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


    set(name nms-p2p-nix-distributed)
    set(source_files ${name}.cc)
    set(header_files)
    set(libraries_to_link ${libpoint-to-point} ${libinternet} ${libnix-vector-routing} ${libapplications})
    set(files_to_copy)
    build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


    set(name simple-distributed-empty-node)
    set(source_files ${name}.cc)
    set(header_files)
    set(libraries_to_link ${libpoint-to-point} ${libinternet} ${libnix-vector-routing} ${libapplications})
    set(files_to_copy)
    build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")

endif()