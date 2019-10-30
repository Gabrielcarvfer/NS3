set(name csma-bridge)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libbridge} ${libcsma} ${libinternet} ${libapplications})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")



set(name csma-bridge-one-hop)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libbridge} ${libcsma} ${libinternet} ${libapplications})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")

