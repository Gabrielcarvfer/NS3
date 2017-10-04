NS3_common_includes()

if (${visualizer_python_dependencies})
set(name visualizer)
set(lib${name} ns${NS3_VER}-${name}-${build_type})
add_library(${lib${name}} SHARED
        model/dummy-file-for-static-builds.cc
        )

#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED )
endif()