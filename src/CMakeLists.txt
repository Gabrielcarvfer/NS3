
#Process subdirectories
foreach(libname ${libs_to_build})
    add_subdirectory(${libname})
endforeach()

#Build the lib-ns3-static (ns3.x-static-buildtype.a/.lib) with all sublibraries
if (${NS3_STATIC})
    add_library(${lib-ns3-static} STATIC empty.cc ${lib-ns3-static-objs})
endif()

if(${NS3_PYTHON})
    add_library(${ns3-python-bindings} SHARED ${ns3-python-bindings-modules})
    target_link_libraries(${ns3-python-bindings} ${LIB_AS_NEEDED_PRE} ${ns3-libs} ${Python2_LIBRARIES} ${LIB_AS_NEEDED_POST})
endif()