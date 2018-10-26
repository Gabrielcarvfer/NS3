set(name adhoc-aloha-ideal-phy)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libspectrum} ${libmobility} ${libinternet} ${libapplications})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name adhoc-aloha-ideal-phy-matrix-propagation-loss-model)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libspectrum} ${libmobility} ${libinternet} ${libapplications})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name adhoc-aloha-ideal-phy-with-microwave-oven)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libspectrum} ${libmobility} ${libinternet} ${libapplications})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name tv-trans-example)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libspectrum} ${libmobility} ${libcore})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name tv-trans-regional-example)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libspectrum} ${libmobility} ${libcore})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")

