set(docsis_single_source_examples
        residential-example
        docsis-configuration-example
        )

set(header_files)
set(libraries_to_link ${libdocsis})

foreach (example ${docsis_single_source_examples})
    set(name ${example})
    set(source_files ${name}.cc)
    build_contrib_example("${contribname}" "${name}" "${source_files}" "${header_files}" "${libraries_to_link}")
endforeach ()


