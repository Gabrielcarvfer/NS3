
set(name vasisht2016_chronos)

set(source_files
        model/ap-wifi-mac-chronos.cc
        model/sta-wifi-mac.cc
        )

set(header_files
        model/ap-wifi-mac-chronos.h
        model/sta-wifi-mac.cc

        )

set(libraries_to_link ${libwifi})

set(test_sources)

build_contrib_lib_component("${name}"
        "${contrib_name}"
        "${source_files}"
        "${header_files}"
        "${libraries_to_link}"
        "${test_sources}"
        )


set(name wif-ap2_mod)
set(source_files examples/${name}.cc)
set(header_files)
set(libraries_to_link
        ${lib${contrib_name}}
        #${libwifi}
        ${libinternet}
        ${libinternet-applications}
        ${libnetanim}
        )

build_contrib_example("${name}" "${contrib_name}" "${source_files}" "${header_files}" "${libraries_to_link}")
