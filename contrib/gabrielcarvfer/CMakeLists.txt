
set(contrib_name gabrielcarvfer)
set(contribution_lib_components
        wifi
        )

#build_contrib_lib("${contrib_name}" "${contribution_lib_components}")

set(examples
        dynamic_beacon_10static_1moving
        dynamic_beacon_10static_2moving
        dynamic_beacon_10static_3moving
        dynamic_beacon_2ap_10static_1moving

        )

foreach(example ${examples})
    set(name ${example})
    set(source_files wifi/examples/${name}.cc wifi/examples/shared.cc)
    set(header_files wifi/examples/shared.h)
    set(libraries_to_link
            #${lib${contrib_name}}
            ${libwifi}
            ${libinternet}
            ${libinternet-applications}
            ${libnetanim}
            )

    build_contrib_example("${name}" "${contrib_name}" "${source_files}" "${header_files}" "${libraries_to_link}")
endforeach()