set(name topology-example-sim)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libtopology-read} ${libinternet} ${libnix-vector-routing} ${libpoint-to-point} ${libapplications})
set(files_to_copy Inet_small_toposample.txt)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")

