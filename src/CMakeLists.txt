
#Process subdirectories
foreach(libname ${libs_to_build})
    add_subdirectory(${libname})
endforeach()


