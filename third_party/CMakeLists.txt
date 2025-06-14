raygame_lib(RayGameExternalZppBits)
add_library(RayGame::External::ZppBits ALIAS RayGameExternalZppBits)
add_custom_command(
    OUTPUT zpp_bits.cpp
    COMMAND echo "#include \"zpp_bits/zpp_bits.h\"" > test
    DEPENDS zpp_bits/zpp_bits.h
    CODEGEN
)
target_sources(
    RayGameCoreSerialisation
    PUBLIC zpp_bits/zpp_bits.h
    PRIVATE zpp_bits/zpp_bits.cpp
)
