
#Process subdirectories
foreach(libname ${libs_to_build})
    add_subdirectory(${libname})
endforeach()

#Build the lib-ns3-static (ns3.x-static-buildtype.a/.lib) with all sublibraries
if (${NS3_STATIC})
    add_library(${lib-ns3-static} STATIC empty.cc ${lib-ns3-static-objs})
endif()