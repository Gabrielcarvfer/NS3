NS3_common_includes()

add_executable(scratch-simulator scratch-simulator.cc)

target_link_libraries(scratch-simulator ${ns3-libs})