#Add contributed libraries to be built

set(contribution_libraries_to_build
        haraldott             # https://github.com/haraldott/dash/commit/f886b5757de277db9c88e442458f20960a70b57a
        )

#All contrib libraries can be linked afterwards linking with ${ns3-contrib-libs}
process_contribution("${contribution_libraries_to_build}")