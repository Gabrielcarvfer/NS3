NS3_common_includes()

set(name netanim)

set(source_files
        model/animation-interface.cc
        )

set(header_files
        model/animation-interface.h
        )

set(libraries_to_link
        ${libinternet}
        ${libmobility}
        ${libwimax}
        ${libwifi}
        ${libcsma}
        ${liblte}
        ${libuan}
        ${libenergy}
        )

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")



#set(test${libname} ns${libNS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED )
