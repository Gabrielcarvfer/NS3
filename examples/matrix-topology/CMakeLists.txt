set(name matrix-topology)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libnetwork} ${libnetanim} ${libmobility} ${libpoint-to-point} ${libinternet}
                      ${libapplications}
)
build_example("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")
