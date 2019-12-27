set(name main-grid-topology)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libmobility} ${libnetwork})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name main-random-topology)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libmobility})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name main-random-walk)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libmobility})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name mobility-trace-example)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libmobility} ${libnetwork})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name ns2-mobility-trace)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libmobility})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name bonnmotion-ns2-example)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libmobility})
set(files_to_copy bonnmotion.ns_movements)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")

