build_lib(
  LIBNAME oran
  SOURCE_FILES
    model/PubSubInfra.cc
    model/E2AP.cc
    #model/E2SM-KPM.cc  -- these are part of E2AP. separated only for readability.
    #model/E2SM-RC.cc   /
    model/E2SM-KPM-measurements.cc
    model/xApp.cc
    model/dynamicSpectrumAllocationxApp.cc
    model/ORAN-message-types.cc
  HEADER_FILES
    model/json.hpp
    model/PubSubInfra.h
    model/E2AP.h
    model/xApp.h
    model/dynamicSpectrumAllocationxApp.h
    model/E2SM-KPM-measurements.h
    model/E2SM-RC-control-types.h
    model/E2SM-RC-indication-types.h
    model/ORAN-message-types.h
  LIBRARIES_TO_LINK
    ${libcore}
    ${libnetwork}
    ${libinternet}
)
