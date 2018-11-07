if(${NS3_PYTHON})

        #if (${visualizer_python_dependencies})
    set(name visualizer)

    set(source_files
            model/pyviz.cc
            model/visual-simulator-impl.cc
            )

    set(header_files
            model/pyviz.h
            )

    set(libraries_to_link ${Python2_LIBRARIES} ${libcore} ${libinternet} ${libwifi} ${libpoint-to-point} )

    set(test_sources)

    build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")

    #change to include visualizer and ns python bindings -> PYTHONPATH=./:./visualizer:./ns
    file(COPY visualizer DESTINATION ${CMAKE_OUTPUT_DIRECTORY})

else()
    message(WARNING "Visualizer will not be built because NS3_PYTHON is missing")
endif()