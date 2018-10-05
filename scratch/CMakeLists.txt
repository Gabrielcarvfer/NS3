file(GLOB_RECURSE scratches  ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

foreach(scratch_src ${scratches})
    get_filename_component(scratch_name ${scratch_src} NAME)
    string(REGEX REPLACE "\\.[^.]*$" "" scratch_name ${scratch_name})
    add_executable(${scratch_name} "${scratch_src}")
    target_link_libraries(${scratch_name} "${ns3-libs}")
endforeach()

