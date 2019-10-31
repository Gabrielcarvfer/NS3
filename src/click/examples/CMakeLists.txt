set(name nsclick-simple-lan)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libclick} ${libcsma} ${libinternet} ${libapplications})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name nsclick-raw-wlan)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libclick} ${libwifi} ${libinternet} ${libapplications})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name nsclick-udp-client-server-csma)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libclick} ${libcsma} ${libinternet} ${libapplications})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name nsclick-udp-client-server-wifi)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libclick} ${libwifi} ${libinternet} ${libapplications})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name nsclick-routing)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libclick} ${libcsma} ${libinternet} ${libapplications})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name nsclick-defines)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libclick})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")

