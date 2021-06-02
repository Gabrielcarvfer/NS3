# Copyright (c) 2017-2021 Universidade de Brasília
#
# This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public
# License version 2 as published by the Free Software Foundation;
#
# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
# warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with this program; if not, write to the Free
# Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
# Author: Gabriel Ferreira <gabrielcarvfer@gmail.com>

# Takes module
# - name (e.g. mmwave)
# - subfolder (e.g. src/mmwave)
# - src_type (e.g. GIT or URL)
# - url (e.g. https://github.com/nyuwireless-unipd/ns3-mmwave.git)
# - tag/hash (e.g. commit/md5)
# - patch (e.g. docsis has patches/ns-3.ver.patch)
# - path_to_apply_patch (e.g. docsis tries to apply their patch on ns-3-dev instead of their own module)

function(fetch_ns3_store_module modulename subfolder src_type url tag_or_hash patch path_to_apply_patch)
    message(STATUS "Fetching contrib/${modulename}")
    set(module_dir ${PROJECT_SOURCE_DIR}/contrib/${modulename})

    # Only fetch archives if store/module doesn't exist, to prevent overwriting modified sources
    if( (NOT (EXISTS ${module_dir})) OR ( (EXISTS ${module_dir}) AND NOT (EXISTS ${module_dir}/.git) ) )
        include(FetchContent)
        if("${src_type}" MATCHES "URL")
            FetchContent_Declare(
                    ${modulename}-module
                    URL ${url}
                    URL_HASH ${tag_or_hash}
                    SOURCE_DIR ${module_dir}
            )
        elseif("${src_type}" MATCHES "GIT")
            FetchContent_Declare(
                    ${modulename}-module
                    GIT_REPOSITORY ${url}
                    GIT_TAG ${tag_or_hash}
                    SOURCE_DIR ${module_dir}
            )
        else()
            message(FATAL_ERROR "Unknown src_type for ${modulename}.")
        endif()

        # Delete CMake temporary folders if user deleted store/modulename to prevent issues when redownloading
        file(GLOB module_leftovers  ${PROJECT_BINARY_DIR}/_deps/${modulename}*)
        list(LENGTH module_leftovers len)
        if(len GREATER "0")
            file(REMOVE_RECURSE ${module_leftovers})
        endif()

        # Redownload sources
        FetchContent_Populate(${modulename}-module)

        file(COPY buildsupport/3rd_party/modules/${modulename}_cmakelists.cmake DESTINATION ${module_dir})
        file(RENAME ${module_dir}/${modulename}_cmakelists.cmake ${module_dir}/CMakeLists.txt)

        set(example_cmakelists ${modulename}_examples_cmakelists.cmake)
        set(store_example_cmakelists buildsupport/3rd_party/modules/${example_cmakelists})
        if(EXISTS ${PROJECT_SOURCE_DIR}/${store_example_cmakelists})
            file(COPY ${store_example_cmakelists} DESTINATION ${module_dir}/examples)
            file(RENAME ${module_dir}/examples/${example_cmakelists} ${module_dir}/examples/CMakeLists.txt)
        endif()

        # Apply a patch if one exists
        string(LENGTH "${patch}" len)
        if( (len GREATER "0") AND (EXISTS ${module_dir}/${patch}) )
            # If no path to apply the patch is specified, assume its the module directory
            string(LENGTH "${path_to_apply_patch}" len)
            if(len EQUAL "0")
                set(path_to_apply_patch ${module_dir})
            endif()
            execute_process(COMMAND patch -p1 -i ${module_dir}/${patch}
                WORKING_DIRECTORY ${path_to_apply_patch}
            )
        endif()
    endif()
endfunction()