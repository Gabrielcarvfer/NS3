
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

if(${XML2_FOUND})
    set(XML2_SOURCE_FILES
            model/xml-config.cc
            )
endif()

set(source_files
        ${GTK2_SOURCE_FILES}
        ${XML2_SOURCE_FILES}
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
        ${LIBXML2_LIBRARIES}
        )

set(test_sources)

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")

#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED)

