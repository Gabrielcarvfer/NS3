NS3_common_includes()

set(name nix-vector-routing)
set(lib${name} ns${NS3_VER}-${name}-${build_type})
add_library(${lib${name}} SHARED
        model/ipv4-nix-vector-routing.cc
        helper/ipv4-nix-vector-helper.cc
        model/ipv4-nix-vector-routing.h
        helper/ipv4-nix-vector-helper.h
        )

#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED )
