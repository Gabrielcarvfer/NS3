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
)