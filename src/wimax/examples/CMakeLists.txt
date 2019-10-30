set(name wimax-ipv4)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwimax} ${libinternet} ${libmobility} ${libcsma} ${libapplications})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name wimax-multicast)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwimax} ${libinternet} ${libcsma} ${libapplications})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name wimax-simple)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwimax} ${libinternet} ${libmobility} ${libapplications})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


