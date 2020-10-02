add_executable(5grange_cdl_test 5grange_cdl_test.cc)
target_link_libraries(5grange_cdl_test "${ns3-libs}")

add_executable(shadowing_map_test spatially-correlated-shadowing-map-test.cc)
target_link_libraries(shadowing_map_test ${libpropagation})