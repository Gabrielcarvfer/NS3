
set(name dash)

set(source_files
        model/tcp-stream-adaptation-algorithm.cc
        model/tcp-stream-client.cc
        model/tcp-stream-server.cc
        model/tobasco2.cc
        model/festive.cc
        model/panda.cc
        helper/tcp-stream-helper.cc
        )

set(header_files
        model/tcp-stream-adaptation-algorithm.h
        model/tcp-stream-client.h
        model/tcp-stream-server.h
        model/tobasco2.h
        model/festive.h
        model/panda.h
        model/tcp-stream-interface.h
        helper/tcp-stream-helper.h
        )

set(libraries_to_link ${libinternet})

set(test_sources)

build_contrib_lib_component("${name}" "${contrib_name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")

