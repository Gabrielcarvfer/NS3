set(name li-ion-energy-source)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libenergy})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name rv-battery-model-test)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libenergy} ${libwifi})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name basic-energy-model-test)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libenergy} ${libwifi})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")

