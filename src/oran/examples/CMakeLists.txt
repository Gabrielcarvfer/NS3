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
        NAME TestE2Node
        SOURCE_FILES TestE2Node.cc
        LIBRARIES_TO_LINK
        ${libcore}
        ${libmobility}
        ${libpoint-to-point}
        ${liblte}
        ${liboran}
)