NS3_common_includes()

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

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED )
