NS3_common_includes()

if (${visualizer_python_dependencies})
set(name visualizer)
set_lib_name(${name})
add_library(lib${name} SHARED
        model/dummy-file-for-static-builds.cc
        )

#set_test_name(${name})
#add_library(test${name} )
endif()