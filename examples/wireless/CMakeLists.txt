
set(name mixed-wireless)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libmobility} ${libwifi} ${libapplications} ${libpoint-to-point} ${libinternet} ${libcsma} ${libolsr} ${libnetanim})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-adhoc)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libmobility} ${libwifi} ${libapplications} ${libstats})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-clear-channel-cmu)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libinternet} ${libmobility} ${libwifi} ${libstats})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-ap)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libmobility} ${libwifi} ${libapplications} ${libconfig-store} ${libstats})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name wifi-wired-bridging)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libinternet} ${libmobility} ${libwifi} ${libcsma} ${libbridge} ${libapplications})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name multirate)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libinternet} ${libmobility} ${libwifi} ${libstats} ${libflow-monitor} ${libolsr} ${libapplications} ${libpoint-to-point})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name wifi-simple-adhoc)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libinternet} ${libmobility} ${libwifi} ${libconfig-store} ${libstats})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name wifi-simple-adhoc-grid)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libinternet} ${libmobility} ${libwifi} ${libolsr} ${libconfig-store} ${libstats} ${libpoint-to-point})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name wifi-simple-infra)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libinternet} ${libmobility} ${libwifi} ${libconfig-store})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name wifi-simple-interference)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libinternet} ${libmobility} ${libwifi} ${libconfig-store} ${libstats})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name wifi-blockack)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libinternet} ${libmobility} ${libwifi} ${libapplications})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name ofdm-validation)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libmobility} ${libwifi} ${libconfig-store} ${libstats})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name ofdm-ht-validation)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libmobility} ${libwifi} ${libconfig-store} ${libstats})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name ofdm-vht-validation)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libmobility} ${libwifi} ${libconfig-store} ${libstats})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name wifi-hidden-terminal)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libinternet} ${libmobility} ${libwifi} ${libapplications} ${libpropagation} ${libflow-monitor})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name ht-wifi-network)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libinternet} ${libmobility} ${libwifi} ${libapplications} ${libpropagation})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name vht-wifi-network)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libinternet} ${libmobility} ${libwifi} ${libapplications} ${libpropagation})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name wifi-timing-attributes)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libinternet} ${libmobility} ${libwifi} ${libapplications} ${libpropagation})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name wifi-sleep)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libnetwork} ${libinternet} ${libmobility} ${libwifi} ${libapplications} ${libenergy} ${libconfig-store})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name power-adaptation-distance)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libmobility} ${libwifi} ${libapplications} ${libflow-monitor})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name power-adaptation-interference)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libmobility} ${libwifi} ${libapplications} ${libflow-monitor})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name rate-adaptation-distance)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libmobility} ${libwifi} ${libapplications} ${libflow-monitor})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name wifi-aggregation)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libinternet} ${libmobility} ${libwifi} ${libapplications})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name simple-ht-hidden-stations)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libinternet} ${libmobility} ${libwifi} ${libapplications})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name 80211n-mimo)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libinternet} ${libmobility} ${libwifi} ${libapplications} ${libpropagation})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name mixed-bg-network)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libinternet} ${libmobility} ${libwifi} ${libapplications})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name wifi-tcp)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libinternet} ${libmobility} ${libwifi} ${libapplications} ${libpoint-to-point})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name 80211e-txop)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libinternet} ${libmobility} ${libwifi} ${libapplications})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name wifi-spectrum-per-example)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libinternet} ${libmobility} ${libwifi} ${libapplications} ${libspectrum})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name wifi-spectrum-per-interference)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libinternet} ${libmobility} ${libwifi} ${libapplications} ${libspectrum})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


set(name wifi-spectrum-saturation-example)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libinternet} ${libmobility} ${libwifi} ${libapplications} ${libspectrum})
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")



