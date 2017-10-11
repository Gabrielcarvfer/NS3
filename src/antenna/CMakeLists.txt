
set(name antenna)

set(source_files
        model/angles.cc
        model/antenna-model.cc
        model/isotropic-antenna-model.cc
        model/cosine-antenna-model.cc
        model/parabolic-antenna-model.cc
        )

set(header_files
        model/angles.h
        model/antenna-model.h
        model/isotropic-antenna-model.h
        model/cosine-antenna-model.h
        model/parabolic-antenna-model.h
        )

#link to dependencies
set(libraries_to_link ${libcore})

set(test_sources
        test/test-angles.cc
        test/test-cosine-antenna.cc
        test/test-degrees-radians.cc
        test/test-isotropic-antenna.cc
        test/test-parabolic-antenna.cc
        )

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" ${test_sources})




