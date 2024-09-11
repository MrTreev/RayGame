enable_testing()
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_subdirectory(${RG_PATH_ETC}/fuzztest ${CMAKE_CURRENT_BINARY_DIR}/fuzztest)
include(GoogleTest)

enable_testing()
fuzztest_setup_fuzzing_flags()

add_executable(Test)
target_compile_options(Test PRIVATE -Wno-global-constructors -Wno-unsafe-buffer-usage -Wno-shorten-64-to-32 -Wno-sign-conversion)
target_link_libraries(Test PRIVATE GTest::gtest_main)
target_link_libraries(Test PRIVATE Core)
target_sources(Test PUBLIC math.cpp)
gtest_discover_tests(Test)
rg_add_args(Test)

add_executable(TestFuzz)
target_compile_options(TestFuzz PRIVATE -w)
target_link_libraries(TestFuzz PRIVATE GTest::gtest_main)
target_link_libraries(TestFuzz PRIVATE Core)
target_sources(TestFuzz PUBLIC fuzztest.cpp)
gtest_discover_tests(TestFuzz)
link_fuzztest(TestFuzz)
rg_add_args(TestFuzz)


add_custom_target(
    RunTest ALL
    COMMAND Test
    DEPENDS Test
    VERBATIM
)
