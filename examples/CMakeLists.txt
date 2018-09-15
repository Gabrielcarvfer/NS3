
if (${NS3_EXAMPLES})
    set(examples_to_build
            energy
            error-model
            ipv6
            matrix-topology
            naming
            realtime
            routing
            socket
            stats
            tcp
            traffic-control
            tutorial
            udp
            udp-client-server
            wireless
            )
    #Process subdirectories
    foreach(examplename ${examples_to_build})
        add_subdirectory(${examplename})
    endforeach()
endif()





