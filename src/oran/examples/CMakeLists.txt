build_lib_example(
  NAME TestE2SmRcIndicationMessages
  SOURCE_FILES TestE2SmRcMessages.cc
  LIBRARIES_TO_LINK
    ${libcore}
    ${liboran}
    ${liblte}
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

if(NOT
   (${ARMADILLO}
    STREQUAL
    ARMADILLO-NOTFOUND)
   AND NOT
       (${MLPACK_INCLUDE_DIRS}
        STREQUAL
        MLPACK_INCLUDE_DIRS-NOTFOUND)
)
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
    IGNORE_PCH
    TRUE
  )
  build_lib_example(
    NAME TestHandoverXappMLPACKReinforcedLearning
    SOURCE_FILES TestHandoverXappMLPACKReinforcedLearning.cc
    LIBRARIES_TO_LINK
      ${libcore}
      ${libmobility}
      ${libpoint-to-point}
      ${liblte}
      ${liboran}
      ${libapplications}
    IGNORE_PCH
    TRUE
  )
  build_lib_example(
    NAME HandoverXappsScenario
    SOURCE_FILES HandoverXappsScenario.cc
    LIBRARIES_TO_LINK
      ${libcore}
      ${libmobility}
      ${libpoint-to-point}
      ${liblte}
      ${liboran}
      ${libapplications}
      ${libnetanim}
    IGNORE_PCH
    TRUE
  )
endif()

# find_package(Torch) if(${Torch_FOUND}) # Download libtorch from
# https://pytorch.org/cppdocs/installing.html # Then unzip to ~/.local
# find_library(TORCH torch HINTS ~/.local/lib) find_library(TORCH_LIBRARY
# torch_library HINTS ~/.local/lib) list(REMOVE_ITEM TORCH_LIBRARIES "torch")
# list(REMOVE_ITEM TORCH_LIBRARIES "torch_library") list(INSERT TORCH_LIBRARIES
# 0 ${TORCH_LIBRARY}) list(INSERT TORCH_LIBRARIES 0 ${TORCH})
# include_directories(${TORCH_INCLUDE_DIRS}) build_lib_example( NAME
# TestHandoverXappMLTorch SOURCE_FILES TestHandoverXappMLTorch.cc
# LIBRARIES_TO_LINK ${libcore} ${libmobility} ${libpoint-to-point} ${liblte}
# ${liboran} ${libapplications} ${TORCH_LIBRARIES} )
# target_compile_options(TestHandoverXappMLTorch PUBLIC ${TORCH_CXX_FLAGS})
# endif()
