set(name main-callback)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name sample-simulator)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name main-ptr)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name main-random-variable-stream)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libconfig-store} ${libstats})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name sample-random-variable)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name sample-random-variable-stream)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name command-line-example)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name hash-example)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name sample-log-time-format)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")


set(name test-string-value-formatting)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")

set(name sample-show-progress)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore})
set(files_to_copy)
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")



if(${NS3_REALTIME})
    set(name main-test-sync)
    set(source_files ${name}.cc)
    set(header_files)
    set(libraries_to_link ${libnetwork})
    build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${files_to_copy}")
endif()