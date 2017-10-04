NS3_common_includes()

set(name csma-layout)
set_lib_name(${name})
add_library(lib${name} SHARED
        model/csma-star-helper.cc
        model/csma-star-helper.h
        )

#set_test_name(${name})
#add_library(test${name})
