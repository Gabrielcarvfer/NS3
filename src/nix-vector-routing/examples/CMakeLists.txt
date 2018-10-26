set(name nix-simple)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libpoint-to-point} ${libinternet} ${libapplications} ${libnix-vector-routing})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name nms-p2p-nix)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libpoint-to-point} ${libinternet} ${libapplications} ${libnix-vector-routing})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


