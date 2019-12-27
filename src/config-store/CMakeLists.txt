
set(name config-store)

if(${GTK2_FOUND})
    set(GTK2_SOURCE_FILES
            model/gtk-config-store.cc
            model/model-node-creator.cc
            model/model-typeid-creator.cc
            model/display-functions.cc
            )

    set(GTK2_HEADER_FILES
            model/gtk-config-store.h
            )
endif()

if(${LIBXML2_FOUND})
    set(xml2_sources
            model/xml-config.cc
            )
    set(xml2_libraries ${LIBXML2_LIBRARIES})

    if(${CMAKE_BUILD_TYPE} STREQUAL "Release") #Remove some weird stuff Vcpkg does (e.g. libxml2.a;optimized;liblzma.a;debug;liblzmad.a)
        list(REMOVE_AT xml2_libraries 1)
        list(REMOVE_AT xml2_libraries 2)
        list(REMOVE_AT xml2_libraries 2)
    else()
        list(REMOVE_AT xml2_libraries 1)
        list(REMOVE_AT xml2_libraries 1)
        list(REMOVE_AT xml2_libraries 1)
    endif()
    #message(WARNING "${xml2_libraries}")
endif()

set(source_files
        ${GTK2_SOURCE_FILES}
        ${xml2_sources}
        model/attribute-iterator.cc
        model/config-store.cc
        model/attribute-default-iterator.cc
        model/file-config.cc
        model/raw-text-config.cc
        )

set(header_files
        ${GTK2_HEADER_FILES}
        model/file-config.h
        model/config-store.h
        )

set(libraries_to_link
        ${libcore}
        ${libnetwork}
        ${GTK2_LIBRARIES}
        ${xml2_libraries}
        )

set(test_sources)

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")

