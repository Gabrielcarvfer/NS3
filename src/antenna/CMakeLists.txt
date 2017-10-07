NS3_common_includes()

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

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")



#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED
#        test/test-angles.cc
#        test/test-cosine-antenna.cc
#        test/test-degrees-radians.cc
#        test/test-isotropic-antenna.cc
#        test/test-parabolic-antenna.cc)
