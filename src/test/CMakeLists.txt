include(RgTest)
add_executable(Tests)
rg_make_test(Tests LIBS Core)
rg_add_args(Tests)
target_sources(Tests PUBLIC main.cpp math.cpp)
target_compile_definitions(Tests PUBLIC "RAYGAME_LOG_${RG_LOG_LEVEL}")

add_custom_target(
    RunTest ALL
    COMMAND Tests
    DEPENDS Tests
    VERBATIM
)
