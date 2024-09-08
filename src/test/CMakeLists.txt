include(RgTest)
add_executable(Tests)
rg_make_test(Tests LIBS Core)
target_sources(Tests PUBLIC main.cpp math.cpp)
add_custom_target(
    RunTest ALL
    COMMAND Tests
    DEPENDS Tests
    VERBATIM
)
