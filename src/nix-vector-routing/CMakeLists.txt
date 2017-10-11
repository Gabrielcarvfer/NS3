
set(name nix-vector-routing)

set(source_files
        model/ipv4-nix-vector-routing.cc
        helper/ipv4-nix-vector-helper.cc
        )

set(header_files
        model/ipv4-nix-vector-routing.h
        helper/ipv4-nix-vector-helper.h
        )

set(libraries_to_link ${libinternet})

set(test_sources
        )

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")

