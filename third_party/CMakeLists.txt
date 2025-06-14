add_library(RayGameExternalZppBits)
target_sources(
    RayGameExternalZppBits
    PUBLIC include/zppbits.h
    PRIVATE zpp_bits/zpp_bits.h include/zppbits.cpp
)
target_include_directories(
    RayGameExternalZppBits
    PUBLIC $<BUILD_INTERFACE:${RayGame_SOURCE_DIR}/third_party/include>
           $<INSTALL_INTERFACE:include/third_party>
           $<BUILD_INTERFACE:${RayGame_SOURCE_DIR}/third_party/zpp_bits>
           $<INSTALL_INTERFACE:include/zpp_bits>
)
set_target_properties(
    RayGameExternalZppBits
    PROPERTIES CXX_VISIBILITY_PRESET hidden
               CXX_STANDARD 23
               CXX_STANDARD_REQUIRED YES
               VISIBILITY_INLINES_HIDDEN YES
)
add_library(RayGame::External::ZppBits ALIAS RayGameExternalZppBits)
