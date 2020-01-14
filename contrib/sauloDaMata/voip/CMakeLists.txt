
set(name voip)

set(source_files
        model/voip-client.cc
        model/voip-server.cc
        helper/voip-client-server-helper.cc
        )

set(header_files
        model/voip-client.h
        model/voip-server.h
        helper/voip-client-server-helper.h
        )

set(libraries_to_link ${libapplications})

set(test_sources)

build_contrib_lib_component("${name}" "${contrib_name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")

