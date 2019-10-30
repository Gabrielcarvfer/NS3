set(name main-packet-header)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libnetwork})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name main-packet-tag)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libnetwork})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name packet-socket-apps)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libnetwork} ${libcore})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")

