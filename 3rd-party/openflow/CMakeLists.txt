if(${LIBXML2_FOUND} AND ${NS3_OPENFLOW})
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


    #Copy all header files to outputfolder/include/
    file(GLOB_RECURSE switch_source_files ${CMAKE_CURRENT_SOURCE_DIR}/switch/*.c)
    file(GLOB_RECURSE lib_source_files    ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.c)

    set(source_files
            ${switch_source_files}
            ${lib_source_files}
            )



    #Copy private header files
    file(COPY ${private_header_files} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/openflow/private)
    file(COPY config.h                DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/openflow)

    add_library(openflow STATIC ${private_header_files} config.h "${source_files}")
    target_include_directories(openflow PUBLIC ./ ./include ./lib ./switch)
    target_link_libraries(openflow ${LIBXML2_LIBRARIES})
endif()