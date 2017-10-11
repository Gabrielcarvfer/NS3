
if (${visualizer_python_dependencies})
set(name visualizer)

set(source_files
        model/pyviz.cc
        model/visual-simulator-impl.cc
        )

set(header_files
        model/pyviz.h
        )

set(libraries_to_link ${libinternet} ${libwifi} ${libpoint-to-point})

set(test_sources)

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")

endif()