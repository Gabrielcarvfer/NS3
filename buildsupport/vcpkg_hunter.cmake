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
    if (NOT APPLE) # LINUX
        set(VCPKG_TRIPLET ${VCPKG_TARGET_ARCH}-linux)
    else()
        set(VCPKG_TRIPLET ${VCPKG_TARGET_ARCH}-osx)
    endif()
endif()

function(setup_vcpkg)
    #Check if vcpkg was downloaded previously
    if (EXISTS "${VCPKG_DIR}")
        #Vcpkg already downloaded
        message(STATUS "VcPkg folder already exists, skipping git download")
    else()
        include(${PROJECT_SOURCE_DIR}/buildsupport/GitUtils.cmake)

        git_clone(
                PROJECT_NAME    vcpkg
                GIT_URL         https://github.com/Gabrielcarvfer/vcpkg.git
                GIT_TAG         NS3
                DIRECTORY       ${PROJECT_SOURCE_DIR}/3rd-party/
        )
    endif()

	if(MSVC)

	else()
		#Check if required packages are installed (unzip curl tar)
		if (WIN32)
			find_program(UNZIP_PRESENT unzip.exe)
			find_program(CURL_PRESENT curl.exe)
			find_program(TAR_PRESENT tar.exe)
		else()
			find_program(UNZIP_PRESENT unzip)
			find_program(CURL_PRESENT curl)
			find_program(TAR_PRESENT tar)
		endif()

		if(${UNZIP_PRESENT} STREQUAL UNZIP_PRESENT-NOTFOUND)
			message(FATAL_ERROR "Unzip is required for VcPkg, but is not installed")
		endif()

		if(${CURL_PRESENT} STREQUAL CURL_PRESENT-NOTFOUND)
			message(FATAL_ERROR "Curl is required for VcPkg, but is not installed")
		endif()

		if(${TAR_PRESENT} STREQUAL TAR_PRESENT-NOTFOUND)
			message(FATAL_ERROR "Tar is required for VcPkg, but is not installed")
		endif()
	endif()

    #message(WARNING "Checking VCPKG bootstrapping")
    #Check if vcpkg was bootstrapped previously
    if (EXISTS "${VCPKG_DIR}/${VCPKG_EXEC}")
        message(STATUS "VcPkg already bootstrapped")
    else()
        #message(WARNING "Bootstrapping VCPKG")
        set(COMPILER_ENFORCING)

        if (WIN32)
            set(command bootstrap-vcpkg.bat)
        else()
            #if(NOT APPLE) #linux/bsd
                set(command bootstrap-vcpkg.sh)
            #else()
            #    set(command bootstrap-vcpkg.sh)# --allowAppleClang)
            #endif()
        endif()

        execute_process ( COMMAND ${COMPILER_ENFORCING} ${VCPKG_DIR}/${command}
                WORKING_DIRECTORY ${VCPKG_DIR} )
        #message(STATUS "VCPKG bootstrapped")
		#include_directories(${VCPKG_DIR})
        set(ENV{VCPKG_ROOT} ${VCPKG_DIR})
    endif()

    if(NOT WIN32)
        execute_process(COMMAND chmod +x ${VCPKG_DIR}/${VCPKG_EXEC})
    endif()
endfunction()

function(add_package package_name)
    message(STATUS "${package_name} will be installed")
    execute_process (COMMAND ${VCPKG_DIR}/${VCPKG_EXEC} install ${package_name} --triplet ${VCPKG_TRIPLET}
                     OUTPUT_QUIET #comment for easier debugging
            )
    message(STATUS "${package_name} was installed")
        if (${build_type} STREQUAL "deb")
            set(TRIPLET_APP dbg)
        else()
            set(TRIPLET_APP rel)
        endif()
    set(package_dir ${VCPKG_DIR}/packages/${package_name}_${VCPKG_TRIPLET}/)
    set_property(GLOBAL PROPERTY DIR_${package_name} ${package_dir})
endfunction()