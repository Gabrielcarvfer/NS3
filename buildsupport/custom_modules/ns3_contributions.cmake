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

macro(process_contribution contribution_list)
  # Create handles to reference contrib libraries
  foreach(libname ${contribution_list})
    library_target_name(${libname} targetname)
    set(lib${libname} ${targetname})
    set(lib${libname}-obj ${targetname}-obj)
  endforeach()

  # Add contribution folders to be built
  foreach(contribname ${contribution_list})
    message(STATUS "Processing contrib/${contribname}")
    add_subdirectory("contrib/${contribname}")
  endforeach()
endmacro()

macro(
  build_contrib_example
  contrib
  name
  source_files
  header_files
  libraries_to_link
)
  build_lib_example_impl(
    "contrib/${contrib}" "${contrib}-${name}" "${source_files}" "${header_files}" "${libraries_to_link}")
endmacro()

macro(build_contrib_lib name source_files header_files libraries_to_link test_sources)
  build_lib_impl(
    "contrib/${contrib}" "${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}"
  )
endmacro()
