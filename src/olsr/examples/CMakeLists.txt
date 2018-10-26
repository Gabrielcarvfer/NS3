set(name olsr-hna)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libmobility} ${libwifi} ${libcsma} ${libolsr})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name simple-point-to-point-olsr)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libpoint-to-point} ${libinternet} ${libolsr} ${libapplications} ${libwifi})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


