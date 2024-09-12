include(RgTest)

if(RG_TEST_ENABLE)
    add_executable(Test)
    target_compile_options(Test PRIVATE -Wno-unsafe-buffer-usage)
    target_link_libraries(Test PUBLIC Core)
    target_link_libraries(Test PUBLIC doctest)
    target_sources(Test PUBLIC main.cpp math.cpp)
    rg_add_args(Test)
endif()

add_custom_target(
    RunTest ALL
    COMMAND Test
    DEPENDS Test
    VERBATIM
)
