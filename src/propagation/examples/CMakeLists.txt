set(name main-propagation-loss)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libpropagation} ${libconfig-store} ${libstats} ${libmobility})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name jakes-propagation-model-example)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libpropagation})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")

