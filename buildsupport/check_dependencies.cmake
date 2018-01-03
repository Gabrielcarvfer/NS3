include(CheckIncludeFileCXX)
include(CheckFunctionExists)

#Macro that checks if a required file is present and set the flag passed if found
macro(check_include file flag)
    check_include_file_cxx(${file}.h HAVE_${file}_H)
    if(NOT ${HAVE_${file}_H})
        message(WARNING ${file} not found)
        set(${flag} FALSE)
    else()
        add_definitions(-D${flag})
        set(${flag} TRUE)
    endif()
endmacro()

#Macro that checks if a required function is present and set the flag passed if found
macro(check_function function flag)
    check_function_exists(${function} HAVE_${function}_H)
    if(NOT ${HAVE_${function}_H})
        message(WARNING ${function} not found)
    else()
        add_definitions(-D${flag})
    endif()
endmacro()