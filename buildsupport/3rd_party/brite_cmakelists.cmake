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

set(source_files
    Brite.cc
    BriteNode.cc
    Edge.cc
    Graph.cc
    Parser.cc
    Topology.cc
    Util.cc
    Models/ASBarabasiAlbertModel.cc
    Models/ASModel.cc
    Models/ASWaxmanModel.cc
    Models/BottomUpHierModel.cc
    Models/ImportedFileModel.cc
    Models/Model.cc
    Models/RouterBarabasiAlbertModel.cc
    Models/RouterModel.cc
    Models/RouterWaxmanModel.cc
    Models/TopDownHierModel.cc
)

set(header_files
    Brite.h
    BriteNode.h
    Edge.h
    Graph.h
    Parser.h
    Topology.h
    Util.h
    Models/ASBarabasiAlbertModel.h
    Models/ASModel.h
    Models/ASWaxmanModel.h
    Models/BottomUpHierModel.h
    Models/ImportedFileModel.h
    Models/Model.h
    Models/RouterBarabasiAlbertModel.h
    Models/RouterModel.h
    Models/RouterWaxmanModel.h
    Models/TopDownHierModel.h
)

add_library(brite_dep SHARED ${source_files} ${header_files})
target_compile_options(brite_dep PRIVATE -g -O0)
set_target_properties(brite_dep PROPERTIES OUTPUT_NAME ns${NS3_VER}-brite_dep-${build_type})

install(
  TARGETS brite_dep
  EXPORT ns3ExportTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
