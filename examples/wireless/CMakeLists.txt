set(examples_to_run)
exemples_to_run_extract_arguments(examples_to_run)
#message(WARNING "${examples_to_run}")

set(name mixed-wired-wireless)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications} ${libolsr} ${libnetanim})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-80211e-txop)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-80211n-mimo)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-adhoc)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-aggregation)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-ap)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-backward-compatibility)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-blockack)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-clear-channel-cmu)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libinternet} ${libwifi})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-dsss-validation)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-he-network)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-hidden-terminal)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications} ${libflow-monitor})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-ht-network)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-mixed-network)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-multi-tos)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-multirate)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libinternet} ${libwifi} ${libolsr} ${libapplications} ${libflow-monitor})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-ofdm-he-validation)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-ofdm-ht-validation)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-ofdm-validation)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-ofdm-vht-validation)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libcore} ${libmobility} ${libwifi} ${libconfig-store} ${libstats})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-pcf)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-power-adaptation-distance)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-power-adaptation-interference)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications} ${libflow-monitor})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-rate-adaptation-distance)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-simple-adhoc)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libinternet} ${libwifi})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-simple-adhoc-grid)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libinternet} ${libwifi} ${libolsr})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-simple-ht-hidden-stations)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-simple-infra)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libinternet} ${libwifi})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-simple-interference)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libinternet} ${libwifi})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-sleep)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-spatial-reuse)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-spectrum-per-example)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-spectrum-per-interference)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-spectrum-saturation-example)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-tcp)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-timing-attributes)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-txop-aggregation)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-vht-network)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libapplications})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name wifi-wired-bridging)
set(source_files ${name}.cc)
set(header_files)
set(libraries_to_link ${libwifi} ${libcsma} ${libbridge} ${libapplications})
examples_to_run_find_examples(${name} "${examples_to_run}" examples)
build_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")



















































