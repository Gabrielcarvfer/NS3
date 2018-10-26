set(name dumbbell-animation)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libnetanim} ${libapplications} ${libpoint-to-point-layout})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name grid-animation)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libnetanim} ${libapplications} ${libpoint-to-point-layout})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")



set(name star-animation)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libnetanim} ${libapplications} ${libpoint-to-point-layout})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name wireless-animation)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libnetanim} ${libapplications} ${libpoint-to-point} ${libcsma} ${libwifi} ${libmobility} ${libnetwork})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name uan-animation)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libnetanim} ${libinternet} ${libmobility} ${libapplications} ${libuan})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name colors-link-description)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libnetanim} ${libapplications} ${libpoint-to-point-layout})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name resources-counters)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libnetanim} ${libapplications} ${libpoint-to-point-layout})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


