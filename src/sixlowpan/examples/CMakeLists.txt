set(name example-ping-lr-wpan)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libnetwork} ${libsixlowpan} ${libinternet} ${liblr-wpan} ${libinternet-apps})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name example-sixlowpan)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libnetwork} ${libsixlowpan} ${libinternet} ${libcsma} ${libinternet-apps})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")

