macro(raygame_enable_testing)
    enable_testing()
    include(FetchContent)
    FetchContent_Declare(
        googletest URL https://github.com/google/googletest/releases/download/v1.16.0/googletest-1.16.0.tar.gz
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt
        ON
        CACHE BOOL "" FORCE
    )
    FetchContent_MakeAvailable(googletest)
    include(CTest)
    include(GoogleTest)
endmacro()

function(raygame_link_testlib _target)
    target_compile_definitions(${_target} PUBLIC RAYGAME_TESTLIB_GTEST)
    target_link_libraries(${_target} PUBLIC GTest::gtest)
endfunction()

function(raygame_add_test _target)
    target_compile_definitions(${_target} PUBLIC RAYGAME_TESTLIB_GTEST)
    target_include_directories(${_target} PUBLIC ${GTEST_INCLUDE_DIR})
    target_link_libraries(${_target} PUBLIC GTest::gtest)
    gtest_discover_tests(${_target})
endfunction()
