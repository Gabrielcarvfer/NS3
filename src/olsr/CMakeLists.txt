NS3_common_includes()

set(name olsr)

set(source_files
        model/olsr-header.cc
        model/olsr-state.cc
        model/olsr-routing-protocol.cc
        helper/olsr-helper.cc
        )

set(header_files
        model/olsr-routing-protocol.h
        model/olsr-header.h
        model/olsr-state.h
        model/olsr-repositories.h
        helper/olsr-helper.h
        )

set(libraries_to_link ${libinternet})

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")


#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED )
