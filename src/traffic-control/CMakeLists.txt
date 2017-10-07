NS3_common_includes()

set(name traffic-control)
set(source_files
        model/traffic-control-layer.cc
        model/packet-filter.cc
        model/queue-disc.cc
        model/pfifo-fast-queue-disc.cc
        model/red-queue-disc.cc
        model/codel-queue-disc.cc
        model/fq-codel-queue-disc.cc
        model/pie-queue-disc.cc
        helper/traffic-control-helper.cc
        helper/queue-disc-container.cc
        )

set(header_files
        model/traffic-control-layer.h
        model/packet-filter.h
        model/queue-disc.h
        model/pfifo-fast-queue-disc.h
        model/red-queue-disc.h
        model/codel-queue-disc.h
        model/fq-codel-queue-disc.h
        model/pie-queue-disc.h
        helper/traffic-control-helper.h
        helper/queue-disc-container.h
        )

set(libraries_to_link
        ${libnetwork}
        ${libcore}
        )

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")



#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED )
