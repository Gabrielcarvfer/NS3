build_lib_example(
        NAME TestE2SmRcIndicationMessages
        SOURCE_FILES TestE2SmRcMessages.cc
        LIBRARIES_TO_LINK
        ${libcore}
        ${liboran}
)

build_lib_example(
  NAME TestPubSubInfra
  SOURCE_FILES TestPubSubInfra.cc
  LIBRARIES_TO_LINK
    ${libcore}
    ${libmobility}
    ${libpoint-to-point}
    ${liblte}
    ${liboran}
)

build_lib_example(
        NAME TestE2AP
        SOURCE_FILES TestE2AP.cc
        LIBRARIES_TO_LINK
        ${libcore}
        ${libmobility}
        ${libpoint-to-point}
        ${liblte}
        ${liboran}
        ${libapplications}
)

build_lib_example(
        NAME TestHandover
        SOURCE_FILES TestHandover.cc
        LIBRARIES_TO_LINK
        ${libcore}
        ${libmobility}
        ${libpoint-to-point}
        ${liblte}
        ${liboran}
        ${libapplications}
)

build_lib_example(
        NAME TestHandoverXapp
        SOURCE_FILES TestHandoverXapp.cc
        LIBRARIES_TO_LINK
        ${libcore}
        ${libmobility}
        ${libpoint-to-point}
        ${liblte}
        ${liboran}
        ${libapplications}
)

find_library(ARMADILLO armadillo)
find_library(MLPACK mlpack)
if(NOT(${ARMADILLO} STREQUAL ARMADILLO-NOTFOUND) AND NOT(${MLPACK} STREQUAL MLPACK-NOTFOUND))
    build_lib_example(
            NAME TestHandoverXappMLPACK
            SOURCE_FILES TestHandoverXappMLPACK.cc
            LIBRARIES_TO_LINK
            ${libcore}
            ${libmobility}
            ${libpoint-to-point}
            ${liblte}
            ${liboran}
            ${libapplications}
            ${ARMADILLO}
            ${MLPACK}
    )
endif()