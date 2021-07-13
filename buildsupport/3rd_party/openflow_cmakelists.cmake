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

if(NOT ${LIBXML2_FOUND})
  message(FATAL_ERROR "LibXml2 is required by openflow.")
endif()

check_include_file_cxx(boost/static_assert.hpp BOOST_STATIC_ASSERT)
if(NOT BOOST_STATIC_ASSERT)
  message(
    FATAL_ERROR "Boost static_assert.hpp is required by openflow." "Ubuntu ships it within the libboost-dev package."
                "You may need to clean up the CMake cache and configure again."
  )
endif()

set(private_header_files
    lib/csum.h
    lib/poll-loop.h
    lib/rconn.h
    lib/queue.h
    lib/stp.h
    lib/compiler.h
    lib/util.h
    lib/vconn.h
    lib/xtoxll.h
    lib/ofpbuf.h
    lib/red-black-tree.h
    lib/misc.h
    lib/stack.h
    lib/flow.h
    lib/list.h
    lib/packets.h
    lib/random.h
    lib/timeval.h
    lib/type-props.h
    switch/chain.h
    switch/table.h
    switch/datapath.h
    switch/switch-port.h
    switch/dp_act.h
    switch/switch-flow.h
    switch/pt_act.h
)

set(source_files
    lib/command-line.c
    lib/csum.c
    lib/daemon.c
    lib/dhcp.c
    lib/dhcp-client.c
    lib/dirs.c
    lib/dpif.c
    lib/dynamic-string.c
    lib/fatal-signal.c
    lib/fault.c
    lib/flow.c
    lib/freelist.c
    lib/hash.c
    lib/hmap.c
    lib/learning-switch.c
    lib/list.c
    lib/mac-learning.c
    lib/misc.c
    lib/mpls-fib.c
    lib/mpls-switch.c
    lib/netdev.c
    lib/netlink.c
    lib/ofpbuf.c
    lib/ofp-print.c
    lib/poll-loop.c
    lib/port-array.c
    lib/queue.c
    lib/random.c
    lib/rconn.c
    lib/read-mpls-fib.c
    lib/red-black-tree.c
    lib/signals.c
    lib/socket-util.c
    lib/stack.c
    lib/stp.c
    lib/timeval.c
    lib/util.c
    lib/vconn.c
    lib/vconn-mpls.c
    lib/vconn-netlink.c
    lib/vconn-stream.c
    lib/vconn-tcp.c
    lib/vconn-unix.c
    lib/vlog.c
    lib/vlog-socket.c
    switch/chain.c
    switch/crc32.c
    switch/datapath.c
    switch/dp_act.c
    switch/er_act.c
    switch/nx_act.c
    switch/pt_act.c
    switch/switch.c
    switch/switch-flow.c
    switch/switch-port.c
    switch/table-hash.c
    switch/table-linear.c
)

# Copy private header files
file(COPY ${private_header_files} DESTINATION ${CMAKE_OUTPUT_DIRECTORY}/include/openflow/private)
file(COPY config.h DESTINATION ${CMAKE_OUTPUT_DIRECTORY}/include/openflow)

file(GLOB_RECURSE public_header_files ${CMAKE_CURRENT_SOURCE_DIR}/include/openflow/*.h)
file(COPY ${public_header_files} DESTINATION ${CMAKE_OUTPUT_DIRECTORY}/include/openflow)

add_library(openflow_dep STATIC ${private_header_files} config.h "${source_files}")
target_compile_definitions(openflow_dep PRIVATE -DNS3)
target_include_directories(openflow_dep PRIVATE ./ ./include ./lib ./switch ${LIBXML2_INCLUDE_DIR})
target_link_libraries(openflow_dep ${LIBXML2_LIBRARIES})
set_target_properties(openflow_dep PROPERTIES OUTPUT_NAME ns${NS3_VER}-openflow_dep-${build_type})

install(
  TARGETS openflow_dep
  EXPORT ns3ExportTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
