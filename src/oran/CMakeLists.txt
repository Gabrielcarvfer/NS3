#add_package(Armadillo)
#add_package(Mlpack)

include_directories("/usr/include")
link_directories("/lib/aarch64-linux-gnu")

find_library(
  ARMADILLO
  armadillo
)

find_path(MLPACK_INCLUDE_DIRS "mlpack/methods/kmeans/allow_empty_clusters.hpp" "mlpack/methods/kmeans/kmeans.hpp" "mlpack/prereqs.hpp" "mlpack.hpp" PATHS /usr/include)
#find_path(
#  MLPACK_INCLUDE_DIRS
#  PATHS /lib/aarch64-linux-gnu
#  )

if(${ARMADILLO}
    STREQUAL
    ARMADILLO-NOTFOUND
   
)
  message(FATAL_ERROR "Missing Armadillo")
endif()
if(${MLPACK_INCLUDE_DIRS}
       STREQUAL
       MLPACK_INCLUDE_DIRS-NOTFOUND
       )

  message(FATAL_ERROR "Missing Mlpack")
endif()

include_directories(${MLPACK_INCLUDE_DIRS})

check_deps(
        reinforced_handover_xapp
        PYTHON_PACKAGES
        pybind11
)

set(source_files)
set(header_files)
set(libraries)
if(${reinforced_handover_xapp})
    message(
            FATAL_ERROR
            "Missing reinforced handover xapp"
    )
else()
    #cmake_policy(SET CMP0148 NEW)
    find_package(
            pybind11
            REQUIRED
    )
    list(
            APPEND
            source_files
            model/xAppHandoverReinforcedLearning.cc
    )
    list(
            APPEND
            header_files
            model/xAppHandoverReinforcedLearning.h
    )
    list(APPEND link_libraries pybind11::headers
            pybind11::embed
            ${CMAKE_DL_LIBS})
endif()

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
    #model/xAppHandoverMlpackKmeans.cc
    model/xAppHandoverMaxRsrq.cc
    model/xAppHandoverMaliciousPositioning.cc
    ${source_files}
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
    #model/xAppHandoverMlpackKmeans.h
    model/xAppHandoverMaxRsrq.h
    model/xAppHandoverMaliciousPositioning.h
    ${header_files}
  LIBRARIES_TO_LINK
    ${libcore}
    ${libnetwork}
    ${libinternet}
    ${ARMADILLO}
    ${link_libraries}
    )
