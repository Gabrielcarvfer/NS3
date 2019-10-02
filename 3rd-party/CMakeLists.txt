#Add required 3rd-party libraries to build NS3, if dependency is not already installed

if(NOT WIN32)
    add_subdirectory(brite)      # http://code.nsnam.org/BRITE/file/73badd18f5cd
    add_subdirectory(openflow)   # http://code.nsnam.org/jpelkey3/openflow
    if(${NS3_NSC})
        add_subdirectory(nsc)        # https://code.nsnam.org/index.cgi/nsc/file/08c391d0660a
    endif()
endif()

add_subdirectory(netanim)    # http://code.nsnam.org/netanim/rev/2ce82d2b8afd 3.108
add_subdirectory(pybindgen)  # pybindgen-0.17.0.post58+ngcf00cc0
add_subdirectory(csv-parser) # https://github.com/AriaFallah/csv-parser/commit/41e9cd9b3d50929152c7390de5deb614b885f752
add_subdirectory(picojson)   # https://github.com/kazuho/picojson/commit/8ba7113451b745b6e4bd83db12f73eefbb315d2e

#add_subdirectory(slowness) # https://github.com/jpakkane/slowness/commit/3669baff5da70a4c0e90b2cc026b0492fd9530ba
#add_subdirectory(ninjatracing) # https://github.com/nico/ninjatracing/commit/3bb34bbb0657b2b7dbbe8c42720a9d91f576b341
#add_subdirectory(cpp-std-fwd) # https://github.com/Philip-Trettner/cpp-std-fwd/commit/ea132558e70051a1e49cf2a805ebf5bc2eacef4e
