set(header_files)

set(name application-state-trace-example-netsimulyzer)
set(source_files application-state-trace-example.cc)
set(libraries_to_link ${libnetsimulyzer} ${libcore} ${libapplications})
build_contrib_example("${contribname}" "${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name mobility-buildings-example-netsimulyzer)
set(source_files mobility-buildings-example.cc)
set(libraries_to_link ${libnetsimulyzer} ${libcore} ${libmobility} ${libnetwork} ${libbuildings})
build_contrib_example("${contribname}" "${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name lena-radio-link-failure-netsimulyzer)
set(source_files ${name}.cc)
set(libraries_to_link ${libnetsimulyzer} ${libcore} ${libmobility} ${libnetwork} ${liblte})
build_contrib_example("${contribname}" "${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name outdoor-random-walk-example-netsimulyzer)
set(source_files ${name}.cc)
set(libraries_to_link ${libnetsimulyzer} ${libcore} ${libmobility} ${libnetwork} ${libbuildings})
build_contrib_example("${contribname}" "${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name throughput-sink-example-netsimulyzer)
set(source_files ${name}.cc)
set(libraries_to_link ${libnetsimulyzer} ${libcore} ${libmobility} ${libnetwork} ${libinternet} ${libapplications} ${libpoint-to-point})
build_contrib_example("${contribname}" "${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-bianchi-netsimulyzer)
set(source_files ${name}.cc)
set(libraries_to_link ${libnetsimulyzer} ${libcore} ${libmobility} ${libnetwork} ${libwifi})
build_contrib_example("${contribname}" "${name}" "${source_files}" "${header_files}" "${libraries_to_link}")
