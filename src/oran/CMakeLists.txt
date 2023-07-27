add_package(Armadillo)
add_package(Mlpack)
find_library(
  ARMADILLO
  armadillo
)
find_path(
  MLPACK_INCLUDE_DIRS
  "mlpack/mlpack.hpp"
)

if((${ARMADILLO}
    STREQUAL
    ARMADILLO-NOTFOUND
   )
   OR (${MLPACK_INCLUDE_DIRS}
       STREQUAL
       MLPACK_INCLUDE_DIRS-NOTFOUND
      )
)
  message(FATAL_ERROR "Missing Armadillo or Mlpack")
endif()

include_directories(${MLPACK_INCLUDE_DIRS})

build_lib(
  LIBNAME oran
  SOURCE_FILES
    model/PubSubInfra.cc
    model/E2AP.cc
    # model/E2SM-KPM.cc  -- these are part of E2AP. separated only for
    # readability. model/E2SM-RC.cc   /
    model/E2SM-KPM-measurements.cc
    model/ORAN-message-types.cc
    model/xAppHandover.cc
    model/xAppHandoverMlpackKmeans.cc
    model/xAppHandoverMaxRsrq.cc
  HEADER_FILES
    model/json.hpp
    model/PubSubInfra.h
    model/E2AP.h
    model/xApp.h
    model/E2SM-KPM-measurements.h
    model/E2SM-RC-control-types.h
    model/E2SM-RC-indication-types.h
    model/ORAN-message-types.h
    model/xAppHandover.h
    model/xAppHandoverMlpackKmeans.h
    model/xAppHandoverMaxRsrq.h
  LIBRARIES_TO_LINK
    ${libcore}
    ${libnetwork}
    ${libinternet}
    ${ARMADILLO}
)
