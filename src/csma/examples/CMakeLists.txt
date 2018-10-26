set(name csma-one-subnet)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcsma} ${libinternet} ${libapplications})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name csma-broadcast)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcsma} ${libinternet} ${libapplications})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name csma-packet-socket)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcsma} ${libinternet} ${libapplications})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name csma-multicast)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcsma} ${libinternet} ${libapplications})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name csma-raw-ip-socket)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcsma} ${libinternet} ${libapplications} ${libinternet-apps})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name csma-ping)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcsma} ${libinternet} ${libapplications} ${libinternet-apps})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")

