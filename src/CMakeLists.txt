# Process subdirectories
foreach(libname ${libs_to_build})
  message(STATUS "Processing src/${libname}")
  add_subdirectory(${libname})
endforeach()

# Build the lib-ns3-static (ns3.x-static-buildtype.a/.lib) with all sublibraries
if(${NS3_STATIC})
  add_library(${lib-ns3-static} STATIC ${PROJECT_SOURCE_DIR}/buildsupport/empty.cc "${lib-ns3-static-objs}")
  get_property(local-ns3-external-libs GLOBAL PROPERTY ns3-external-libs)
  target_link_libraries(
    ${lib-ns3-static}
    -static
    -static-libstdc++
    -static-libgcc
    ${LIB_AS_NEEDED_PRE_STATIC}
    ${local-ns3-external-libs}
    ${LIB_AS_NEEDED_POST_STATIC}
  )
endif()
