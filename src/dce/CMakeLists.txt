#Build netlink before DCE
#todo: separate netlink from DCE
#set(name netlink)
#set(lib${libname} ns${NS3_VER}-${libname}-${build_type})
#
set(source_files
        netlink/netlink-socket.cc
        netlink/netlink-socket-address.cc
        netlink/netlink-socket-factory.cc
        netlink/netlink-attribute.cc
        netlink/netlink-message.cc
        netlink/netlink-message-route.cc
        )

set(header_files
        netlink/netlink-socket-factory.h
        netlink/netlink-socket-address.h
        )

#set(libraries_to_link ${libcore} ${libinternet})
#
#set(test_sources
#        test/netlink-socket-test.cc
#        )
#
#build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")


#Now build DCE

set(name dce)

set(kernel_source_files
        model/kernel-socket-fd-factory.cc
        model/kernel-socket-fd.cc
        model/linux-socket-fd-factory.cc
        model/freebsd-socket-fd-factory.cc
        model/linux/linux-socket-impl.cc
        )

set(kernel_header_files
        model/kernel-socket-fd-factory.h
        model/linux-socket-fd-factory.h
        model/freebsd-socket-fd-factory.h
        model/linux/linux-socket-impl.h
        )

set(source_files
        ${source_files}
        model/dce-manager.cc
        model/dce-application.cc
        model/dce.cc
        model/dce-signal.cc
        model/libc-dce.cc
        model/utils.cc
        model/unix-fd.cc
        model/unix-file-fd.cc
        model/unix-socket-fd.cc
        model/unix-datagram-socket-fd.cc
        model/unix-stream-socket-fd.cc
        model/unix-timer-fd.cc
        model/dce-fd.cc
        model/dce-stdio.cc
        model/dce-pthread.cc
        model/dce-stdlib.cc
        model/dce-debug.cc
        model/dce-semaphore.cc
        model/dce-pthread-mutex.cc
        model/dce-cxa.cc
        model/dce-netdb.cc
        model/dce-string.cc
        model/dce-env.cc
        model/dce-pthread-cond.cc
        model/dce-timerfd.cc
        model/dce-time.cc
        model/dce-stat.cc
        model/dce-syslog.cc
        model/dce-dl.cc
        model/dce-global-variables.cc
        model/cmsg.cc
        model/waiter.cc
        model/kingsley-alloc.cc
        model/dce-alloc.cc
        model/fiber-manager.cc
        model/ucontext-fiber-manager.cc
        model/pthread-fiber-manager.cc
        model/task-manager.cc
        model/task-scheduler.cc
        model/rr-task-scheduler.cc
        model/loader-factory.cc
        model/elf-dependencies.cc
        model/elf-cache.cc
        model/cooja-loader-factory.cc
        model/dlm-loader-factory.cc
        model/socket-fd-factory.cc
        model/ns3-socket-fd-factory.cc
        model/local-socket-fd.cc
        model/local-stream-socket-fd.cc
        model/local-datagram-socket-fd.cc
        model/local-socket-fd-factory.cc
        model/dce-umask.cc
        model/dce-misc.cc
        model/dce-node-context.cc
        model/dce-wait.cc
        model/wait-queue.cc
        model/file-usage.cc
        model/dce-poll.cc
        model/ipv4-dce-routing.cc
        model/dce-credentials.cc
        model/dce-pwd.cc
        model/pipe-fd.cc
        model/fifo-buffer.cc
        model/dce-dirent.cc
        model/dce-at.cc
        model/exec-utils.cc
        model/linux/ipv4-linux.cc
        model/linux/ipv6-linux.cc
        model/freebsd/ipv4-freebsd.cc
        model/dce-vfs.cc
        model/elf-ldd.cc
        model/dce-termio.cc
        model/process-delay-model.cc
        model/linux/linux-ipv4-raw-socket-factory.cc
        model/linux/linux-ipv4-raw-socket-factory-impl.cc
        model/linux/linux-ipv6-raw-socket-factory.cc
        model/linux/linux-ipv6-raw-socket-factory-impl.cc
        model/linux/linux-udp-socket-factory.cc
        model/linux/linux-udp-socket-factory-impl.cc
        model/linux/linux-udp6-socket-factory.cc
        model/linux/linux-udp6-socket-factory-impl.cc
        model/linux/linux-tcp-socket-factory.cc
        model/linux/linux-tcp-socket-factory-impl.cc
        model/linux/linux-tcp6-socket-factory.cc
        model/linux/linux-tcp6-socket-factory-impl.cc
        model/linux/linux-dccp-socket-factory.cc
        model/linux/linux-dccp-socket-factory-impl.cc
        model/linux/linux-dccp6-socket-factory.cc
        model/linux/linux-dccp6-socket-factory-impl.cc
        model/linux/linux-sctp-socket-factory.cc
        model/linux/linux-sctp-socket-factory-impl.cc
        model/linux/linux-sctp6-socket-factory.cc
        model/linux/linux-sctp6-socket-factory-impl.cc
        # helper.
        helper/ipv4-dce-routing-helper.cc
        helper/dce-manager-helper.cc
        helper/dce-application-helper.cc
        helper/ccn-client-helper.cc
        helper/linux-stack-helper.cc
        helper/freebsd-stack-helper.cc
        )

set(header_files
        ${header_files}
        model/dce-manager.h
        model/task-scheduler.h
        model/task-manager.h
        model/socket-fd-factory.h
        model/loader-factory.h
        model/dce-application.h
        model/ipv4-dce-routing.h
        model/linux/ipv4-linux.h
        model/linux/ipv6-linux.h
        model/freebsd/ipv4-freebsd.h
        model/process-delay-model.h
        model/exec-utils.h
        model/utils.h
        model/linux/linux-ipv4-raw-socket-factory.h
        model/linux/linux-ipv6-raw-socket-factory.h
        model/linux/linux-udp-socket-factory.h
        model/linux/linux-udp6-socket-factory.h
        model/linux/linux-tcp-socket-factory.h
        model/linux/linux-tcp6-socket-factory.h
        model/linux/linux-dccp-socket-factory.h
        model/linux/linux-dccp6-socket-factory.h
        model/linux/linux-sctp-socket-factory.h
        model/linux/linux-sctp6-socket-factory.h
        helper/dce-manager-helper.h
        helper/dce-application-helper.h
        helper/ccn-client-helper.h
        helper/ipv4-dce-routing-helper.h
        helper/linux-stack-helper.h
        helper/freebsd-stack-helper.h
        )

#check if kernel files should be added to source files
#LIST(APPEND source_files ${kernel_source_files})
#LIST(APPEND header_files ${kernel_header_files})

set(libraries_to_link ${CMAKE_DL_LIBS} ${libcore} ${libnetwork} ${libinternet} )#todo: separate netlink ${libnetlink})

set(test_sources
        )

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")

add_library(c-ns3 SHARED
        model/libc.cc
        model/libc-setup.cc
        model/libc-global-variables.cc
        model/libc.h
        )

set(dce-libs
        pthread
        rt
        m
        dl
        )


foreach (dce-lib ${dce-libs})
    add_library(${dce-lib}-ns3 SHARED
            model/libc.cc
            model/libc-setup.cc
            model/libc.h
            )

    target_compile_definitions(${dce-lib}-ns3
            PUBLIC
            LIBSETUP=lib${dce-lib}_setup)

    target_compile_options(${dce-lib}-ns3 PUBLIC
            -fno-profile-arcs
            -fno-test-coverage
            -Wno-builtin-declaration-mismatch
            )
    target_link_libraries(${dce-lib}-ns3 -nostdlib -fno-profile-arcs)
endforeach()

