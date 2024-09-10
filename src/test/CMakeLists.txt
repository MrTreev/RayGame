enable_testing()
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_subdirectory(${RG_PATH_ETC}/fuzztest ${CMAKE_CURRENT_BINARY_DIR}/fuzztest)
include(GoogleTest)
add_executable(Testing)
target_link_libraries(Testing PRIVATE GTest::gtest_main)
target_compile_options(Testing PRIVATE -Wno-global-constructors -Wno-unsafe-buffer-usage -Wno-shorten-64-to-32)
include(GoogleTest)

rg_add_args(Testing)
target_link_libraries(Testing PRIVATE Core)
target_sources(Testing PUBLIC math.cpp)
link_fuzztest(Testing)
gtest_discover_tests(Testing)

add_custom_target(
    RunTesting ALL
    COMMAND Testing
    DEPENDS Testing
    VERBATIM
)
