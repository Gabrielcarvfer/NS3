#Add required 3rd-party libraries to build NS3, if dependency is not already installed

add_subdirectory(netanim)    # netanim-3.108
add_subdirectory(pybindgen)  # pybindgen-0.17.0.post58+ngcf00cc0
add_subdirectory(csv-parser) # https://github.com/AriaFallah/csv-parser/commit/41e9cd9b3d50929152c7390de5deb614b885f752
add_subdirectory(picojson)   # https://github.com/kazuho/picojson/commit/8ba7113451b745b6e4bd83db12f73eefbb315d2e