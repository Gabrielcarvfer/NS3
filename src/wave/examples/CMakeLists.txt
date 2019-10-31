set(name wave-simple-80211p)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libapplications} ${libmobility} ${libnetwork} ${libwifi} ${libwave})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name wave-simple-device)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libapplications} ${libmobility} ${libnetwork} ${libwifi} ${libwave})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name vanet-routing-compare)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libaodv} ${libapplications} ${libdsr} ${libdsdv} ${libflow-monitor} ${libmobility} ${libnetwork} ${libolsr} ${libpropagation} ${libwifi} ${libwave})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")

