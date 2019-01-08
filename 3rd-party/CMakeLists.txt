#Add required 3rd-party libraries to build NS3, if dependency is not already installed

add_subdirectory(brite)      # http://code.nsnam.org/BRITE/file/73badd18f5cd
add_subdirectory(netanim)    # http://code.nsnam.org/netanim/rev/2ce82d2b8afd 3.108
#add_subdirectory(openflow)   # http://code.nsnam.org/jpelkey3/openflow #todo: create a CMakeLists.txt for openflow
add_subdirectory(pybindgen)  # pybindgen-0.17.0.post58+ngcf00cc0
add_subdirectory(csv-parser) # https://github.com/AriaFallah/csv-parser/commit/41e9cd9b3d50929152c7390de5deb614b885f752
add_subdirectory(picojson)   # https://github.com/kazuho/picojson/commit/8ba7113451b745b6e4bd83db12f73eefbb315d2e