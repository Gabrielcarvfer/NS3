
add_executable(scratch-simulator scratch-simulator.cc)

target_link_libraries(scratch-simulator ${ns3-libs})


add_executable(sim sim.cc)

target_link_libraries(sim ${ns3-libs})