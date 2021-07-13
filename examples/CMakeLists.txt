if(${NS3_EXAMPLES})
  subdirlist(examples_to_build ${CMAKE_CURRENT_SOURCE_DIR})

  # Process subdirectories
  foreach(examplefolder ${examples_to_build})
    add_subdirectory(${examplefolder})

    get_property(local-ns3-example-folders GLOBAL PROPERTY ns3-example-folders)
    set_property(GLOBAL PROPERTY ns3-example-folders "${local-ns3-example-folders};${examplefolder}")
  endforeach()
endif()
