set(name tcp-stream)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libharaldott} ${libwifi} ${libinternet} ${libbuildings} ${libapplications} ${libpoint-to-point})
set(files_to_copy segmentsizes.txt)
build_contrib_example ("${name}" "${contrib_name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}" "${files_to_copy}")

