set(VCPKG_DIR ${PROJECT_SOURCE_DIR}/3rd-party/vcpkg)

if (${CMAKE_SIZEOF_VOID_P} EQUAL 8)
    set(VCPKG_TARGET_ARCH x64)
else()
    set(VCPKG_TARGET_ARCH x86)
endif()

if (WIN32)
    set(VCPKG_EXEC vcpkg.exe)
    set(VCPKG_TRIPLET ${VCPKG_TARGET_ARCH}-windows)
else()
    set(VCPKG_EXEC vcpkg)
    if (LINUX)
        set(VCPKG_TRIPLET ${VCPKG_TARGET_ARCH}-linux)
    else()
        set(VCPKG_TRIPLET ${VCPKG_TARGET_ARCH}-osx)
    endif()
endif()

function(setup_vcpkg)
    #Check if vcpkg was downloaded previously
    if (EXISTS "${VCPKG_DIR}")
        #Vcpkg already downloaded
    else()
        include(${PROJECT_SOURCE_DIR}/buildsupport/GitUtils.cmake)

        git_clone(
                PROJECT_NAME    vcpkg
                GIT_URL         https://github.com/Microsoft/vcpkg.git
                GIT_BRANCH      master
                DIRECTORY       ${PROJECT_SOURCE_DIR}/3rd-party/
        )
    endif()

    #message(WARNING "Checking VCPKG bootstrapping")

    #Check if vcpkg was bootstrapped previously
    if (EXISTS "${VCPKG_DIR}/${VCPKG_EXEC}")
        #Vcpkg already bootstrapped
    else()
        #message(WARNING "Bootstrapping VCPKG")
        if (WIN32)
            set(command bootstrap-vcpkg.bat)
        else()
            set(command bootstrap-vcpkg.sh)
        endif()

        execute_process ( COMMAND "${VCPKG_DIR}/${command}"
                WORKING_DIRECTORY ${VCPKG_DIR} )
        #message(WARNING "VCPKG bootstrapped")
		include_directories(${VCPKG_DIR})
    endif()
endfunction()

function(add_package package_name)
    message(WARNING "${package_name} will be installed")
    execute_process (COMMAND ${VCPKG_DIR}/${VCPKG_EXEC} install ${package_name} --triplet ${VCPKG_TRIPLET})
    message(WARNING "${package_name} was installed")
        if (${NS3_DEBUG})
            set(TRIPLET_APP dbg)
        else()
            set(TRIPLET_APP rel)
        endif()
    set(package_dir ${VCPKG_DIR}/packages/${package_name}_${VCPKG_TRIPLET}/)
    set_property(GLOBAL PROPERTY DIR_${package_name} ${package_dir})
endfunction()