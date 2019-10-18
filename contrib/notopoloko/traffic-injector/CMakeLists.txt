
set(name traffic-injector)

set(source_files
        model/json-traffic-injector-application.cc
        helper/loader-traffic-helper.cc
        )

set(header_files
        model/json-traffic-injector-application.h
        helper/loader-traffic-helper.h
        )

set(libraries_to_link ${libinternet} ${libapplication} ${liblte})

set(test_sources)

build_contrib_lib_component("${name}" "${contrib_name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")

