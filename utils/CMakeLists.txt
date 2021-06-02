if(${NS3_TESTS})
  get_property(local-ns3-libs GLOBAL PROPERTY ns3-libs)
  get_property(local-ns3-contrib-libs GLOBAL PROPERTY ns3-contrib-libs)
  get_property(local-ns3-libs-tests GLOBAL PROPERTY ns3-libs-tests)
  set(libraries_to_link ${local-ns3-libs} ${local-ns3-contrib-libs})

  if(WIN32)
    get_property(local-ns3-libs-tests-external GLOBAL PROPERTY ns3-libs-tests-external)

    list(REMOVE_ITEM libraries_to_link ${libtest})

    add_executable(test-runner test-runner.cc ${local-ns3-libs-tests} $<TARGET_OBJECTS:${libtest}>)
    target_link_libraries(test-runner ${LIB_AS_NEEDED_PRE} ${libraries_to_link} ${LIB_AS_NEEDED_POST} ${local-ns3-libs-tests-external})
  else()
    add_executable(test-runner test-runner.cc $<TARGET_OBJECTS:${libtest}>)
    target_link_libraries(
      test-runner ${LIB_AS_NEEDED_PRE} ${local-ns3-libs-tests} ${LIB_AS_NEEDED_POST} ${libraries_to_link}
    )
  endif()
  set_runtime_outputdirectory(test-runner ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/utils/)

  if(WSLv1)
    target_compile_definitions(test-runner PRIVATE -D__WSLv1__)
  endif()

  if(${NS3_TESTS})
    add_dependencies(all-test-targets test-runner)
  endif()

  add_executable(bench-simulator bench-simulator.cc)
  target_link_libraries(bench-simulator ${libcore})
  set_runtime_outputdirectory(bench-simulator ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/utils/)

  add_executable(bench-packets bench-packets.cc)
  target_link_libraries(bench-packets ${libnetwork})
  set_runtime_outputdirectory(bench-packets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/utils/)

  add_executable(print-introspected-doxygen print-introspected-doxygen.cc)
  target_link_libraries(print-introspected-doxygen ${local-ns3-libs})
  set_runtime_outputdirectory(print-introspected-doxygen ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/utils/)

endif()
