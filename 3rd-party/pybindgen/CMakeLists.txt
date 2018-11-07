#execute_process(COMMAND ${Python2_EXECUTABLE} ./waf configure --prefix ${PROJECT_SOURCE_DIR}/build/python
#        COMMAND ${Python2_EXECUTABLE} ./waf install
#        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/3rd-party/pybindgen/)

file(COPY pybindgen DESTINATION ${CMAKE_OUTPUT_DIRECTORY})
