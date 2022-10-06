build_lib(
  LIBNAME oran
  SOURCE_FILES
    model/PubSubInfra.cc
    model/E2AP.cc
    model/xApp.cc
    model/dynamicSpectrumAllocationxApp.cc
  HEADER_FILES
    model/json.hpp
    model/PubSubInfra.h
    model/E2AP.h
    model/xApp.h
    model/dynamicSpectrumAllocationxApp.h
  LIBRARIES_TO_LINK
        ${libcore}
        ${libnetwork}
        ${libinternet}
)
