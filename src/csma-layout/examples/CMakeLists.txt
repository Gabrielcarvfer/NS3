set(name csma-star)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcsma} ${libcsma-layout} ${libinternet} ${libapplications})
build_lib_example("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")
