NS3_common_includes()

set(name nix-vector-routing)
set_lib_name(${name})
add_library(lib${name} SHARED
        model/ipv4-nix-vector-routing.cc
        helper/ipv4-nix-vector-helper.cc
        model/ipv4-nix-vector-routing.h
        helper/ipv4-nix-vector-helper.h
        )

#set_test_name(${name})
#add_library(test${name} )
