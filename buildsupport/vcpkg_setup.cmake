set(VCPKG_DIR ${PROJECT_SOURCE_DIR}/3rd-party/vcpkg)

set(DEFAULT_CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH})

MACRO(SUBDIRLIST result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
            LIST(APPEND dirlist ${child}/lib)
            LIST(APPEND dirlist ${child}/include)
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()


if(NOT EXISTS ${VCPKG_DIR})
    execute_process(COMMAND "git clone https://github.com/Microsoft/vcpkg.git"
          WORKING_DIRECTORY "${VCPKG_DIR}/../")
endif()

if(NOT EXISTS ${VCPKG_DIR}/vcpkg)
    execute_process(COMMAND "./scripts/bootstrap.sh"
          WORKING_DIRECTORY "${VCPKG_DIR}/")
endif()

macro(vcpkg_install package)
    message(STATUS "Trying to install ${package} with Vcpkg")
    execute_process(COMMAND ./vcpkg install ${package}
            WORKING_DIRECTORY "${VCPKG_DIR}/"
            )
    #After each install, update the prefix path to all vcpkg/package/<library_name>/ + /lib + /include folders
    set(CMAKE_PREFIX_PATH ${DEFAULT_CMAKE_PREFIX_PATH})
    list(APPEND CMAKE_PREFIX_PATH ${VCPKG_DIR}/packages/)
    SUBDIRLIST(packages_subdir ${VCPKG_DIR}/packages)
    list(APPEND CMAKE_PREFIX_PATH ${packages_subdir})
endmacro()