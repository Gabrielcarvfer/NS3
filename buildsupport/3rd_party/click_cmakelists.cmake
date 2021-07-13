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

include(ExternalProject)
ExternalProject_Add(
  click
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
  BUILD_IN_SOURCE true
  CONFIGURE_COMMAND ./configure --enable-userlevel --disable-linuxmodule --enable-nsclick --enable-wifi
                    --prefix=${CMAKE_OUTPUT_DIRECTORY} --exec-prefix=${CMAKE_OUTPUT_DIRECTORY}
  BUILD_COMMAND make all -j${NumThreads}
)

# libclick is nsclick + missing symbols, and not the ns-3 click module (accessible with ${libclick})
add_library(click_dep SHARED click_glue.cc)

# make sure libclick is only built after nsclick has been built by the click step
add_dependencies(click_dep click)
target_link_libraries(click_dep PUBLIC nsclick)
set_target_properties(click_dep PROPERTIES OUTPUT_NAME ns${NS3_VER}-click_dep-${build_type})

install(
  TARGETS click_dep
  EXPORT ns3ExportTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
