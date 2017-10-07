NS3_common_includes()


set(libs_to_build
        antenna
        aodv
        applications
        bridge
        #brite
        buildings
        click
        config-store
        core
        csma
        csma-layout
        dsdv
        dsr
        energy
        fd-net-device
        flow-monitor
        internet
        internet-apps
        lr-wpan
        lte
        mesh
        mobility
        mpi
        netanim
        network
        nix-vector-routing
        olsr
        #openflow
        point-to-point
        point-to-point-layout
        propagation
        sixlowpan
        spectrum
        stats
        #tap-bridge
        #test
        topology-read
        traffic-control
        uan
        virtual-net-device
        #visualizer
        wave
        wifi
        wimax
        )

#Create library names to solve dependency problems with macros that will be called at each lib subdirectory
set(ns3-libs )
foreach(libname ${libs_to_build})
    set(lib${libname} ns${NS3_VER}-${libname}-${build_type})
    set(ns3-libs "${ns3-libs}" ${lib${libname}})
endforeach()

#Process subdirectories
foreach(libname ${libs_to_build})
    add_subdirectory(${libname})
endforeach()

#Process simulation folder
add_subdirectory(sim)
