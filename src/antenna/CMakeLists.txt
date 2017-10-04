NS3_common_includes()
set(name antenna)
set_lib_name(${name})
add_library(lib${name} SHARED
        model/angles.cc
        model/angles.h
        model/antenna-model.cc
        model/antenna-model.h
        model/cosine-antenna-model.cc
        model/cosine-antenna-model.h
        model/isotropic-antenna-model.cc
        model/isotropic-antenna-model.h
        model/parabolic-antenna-model.cc
        model/parabolic-antenna-model.h
        )

set_test_name(${name})
add_library(test${name}
        test/test-angles.cc
        test/test-cosine-antenna.cc
        test/test-degrees-radians.cc
        test/test-isotropic-antenna.cc
        test/test-parabolic-antenna.cc)

#link to dependencies
target_link_libraries(lib${name} libcore)