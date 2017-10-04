NS3_common_includes()
set(name aodv)
set(lib${name} ns${NS3_VER}-${name}-${build_type})
add_library(${lib${name}} SHARED
        model/aodv-dpd.cc
        model/aodv-dpd.h
        model/aodv-id-cache.cc
        model/aodv-id-cache.h
        model/aodv-neighbor.cc
        model/aodv-neighbor.h
        model/aodv-packet.cc
        model/aodv-packet.h
        model/aodv-routing-protocol.cc
        model/aodv-routing-protocol.h
        model/aodv-rqueue.cc
        model/aodv-rqueue.h
        model/aodv-rtable.cc
        model/aodv-rtable.h)


#link to dependencies
target_link_libraries(${lib${name}} ${libwifi} ${libinternet})

#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED
#        test/aodv-id-cache-test-suite.cc
#        test/aodv-regression.cc
#        test/aodv-regression.h
#        test/aodv-test-suite.cc)
#
#target_link_libraries(${test${name}} SHARED ${lib${name}})