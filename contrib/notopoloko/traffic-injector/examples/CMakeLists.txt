set(name traffic-injector-example)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libnotopoloko} ${liblte} ${libinternet} ${libbuildings} ${libapplications} ${libpoint-to-point} json-loader)
set(files_to_copy voip_charge.json)
build_contrib_example ("${name}" "${contrib_name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}" "${files_to_copy}")

