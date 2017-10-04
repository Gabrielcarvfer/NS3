#Fixed definitions
unset(CMAKE_LINK_LIBRARY_SUFFIX)

#Output folders
set(CMAKE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY}/bin)
set(CMAKE_HEADER_OUTPUT_DIRECTORY  ${CMAKE_OUTPUT_DIRECTORY}/include)
set(CMAKE_HEADER_DIRECTORY  ${PROJECT_SOURCE_DIR}/ns3)



#Copy all header files to outputfolder/include/
FILE(GLOB_RECURSE include_files ${PROJECT_SOURCE_DIR}/*.hpp)
file(COPY ${include_files} DESTINATION ${CMAKE_HEADER_OUTPUT_DIRECTORY})
file(COPY ${include_files} DESTINATION ${CMAKE_HEADER_DIRECTORY})

#macros

#delete ns3 temporary folder
macro(delete_header_temp_folder)
    file (REMOVE_RECURSE ${CMAKE_HEADER_DIRECTORY})
endmacro()

#fetch all .hpp files with full path and set as ${includes}
macro(NS3_common_includes)
    #HEADER_DIRECTORIES(${CMAKE_HEADER_OUTPUT_DIRECTORY})
    include_directories(${CMAKE_OUTPUT_DIRECTORY})

    #workaround for test building without calling process_options
    if(OpENer_DEBUG)
        add_definitions(-std=c++11 -g)
        set(build_type "debug")
    else()
        add_definitions(-std=c++11 -Os)
        set(build_type "release")
    endif()
endmacro()

MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list ${PROJECT_SOURCE_DIR}/*.hpp)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()
#-------------------------------------------------------------

#process all options passed in main cmakeLists
macro(process_options)
    #process test switch
    if( OpENer_EXAMPLES )
        add_subdirectory(examples)
    endif()

    #process debug switch
    if(OpENer_DEBUG)
        add_definitions(-std=c++11 -g)
    else()
        add_definitions(-std=c++11 -O3)
    endif()
endmacro()
#----------------------------------------------

#set library name
macro(set_lib_name name)
    set(lib${name} ns${NS3_VER}-${name}-${build_type})
endmacro()

macro(set_test_name name)
    set(test${name} ns${NS3_VER}-test-${name}-${build_type})
endmacro()