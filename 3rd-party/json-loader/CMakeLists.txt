add_library(json-loader SHARED json_loader.cc json_loader.h)
file(COPY json_loader.h DESTINATION ${CMAKE_HEADER_OUTPUT_DIRECTORY})
