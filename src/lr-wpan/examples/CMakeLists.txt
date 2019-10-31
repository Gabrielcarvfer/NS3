set(name lr-wpan-data)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${liblr-wpan})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name lr-wpan-error-distance-plot)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${liblr-wpan} ${libstats})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name lr-wpan-error-model-plot)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${liblr-wpan} ${libstats})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name lr-wpan-packet-print)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${liblr-wpan})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name lr-wpan-phy-test)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${liblr-wpan})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")

