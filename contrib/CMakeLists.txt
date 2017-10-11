#Add contributed libraries to be built

set(contribution_libraries_to_build
        gabrielcarvfer
        )

#All contrib libraries can be linked afterwards linking with ${ns3-contrib-libs}
process_contribution(${contribution_libraries_to_build})