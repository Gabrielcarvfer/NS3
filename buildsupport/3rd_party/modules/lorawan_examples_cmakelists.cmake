set(lorawan_single_source_examples
    simple-network-example
    network-server-example
    complete-network-example
    adr-example
    energy-model-example
    aloha-throughput
    parallel-reception-example
    frame-counter-update
)

set(header_files)
set(libraries_to_link ${liblorawan})

foreach (example ${lorawan_single_source_examples})
    set(name ${example})
    set(source_files ${name}.cc)
    build_contrib_example("${contribname}" "${name}" "${source_files}" "${header_files}" "${libraries_to_link}")
endforeach ()


