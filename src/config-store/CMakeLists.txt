set(name config-store)

if(${GTK3_FOUND})
  set(gtk3_sources model/gtk-config-store.cc model/model-node-creator.cc model/model-typeid-creator.cc
                        model/display-functions.cc
  )

  set(gtk3_headers model/gtk-config-store.h)
  include_directories(${GTK3_INCLUDE_DIRS} ${HarfBuzz_INCLUDE_DIRS})
  link_libraries(${GTK3_LIBRARIES})
endif()

if(${LIBXML2_FOUND})
  set(xml2_sources model/xml-config.cc)
  set(xml2_libraries ${LIBXML2_LIBRARIES})
endif()

set(source_files
    ${gtk3_sources}
    ${xml2_sources}
    model/attribute-iterator.cc
    model/config-store.cc
    model/attribute-default-iterator.cc
    model/file-config.cc
    model/raw-text-config.cc
)

set(header_files ${gtk3_headers} model/file-config.h model/config-store.h)

set(libraries_to_link ${libcore} ${libnetwork} ${xml2_libraries})

set(test_sources)

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")

if(${LIBXML2_FOUND})
  target_include_directories(${libconfig-store-obj} PUBLIC ${LIBXML2_INCLUDE_DIR})
endif()
