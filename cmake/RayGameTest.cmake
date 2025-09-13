include_guard()
include(RayGameSetup)
include(FetchContent)

macro(raygame_enable_testing)
    if(RAYGAME_BUILD_TESTS)
        enable_testing()
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
    endif()
endmacro()

function(raygame_link_testlib _target)
    target_compile_definitions(${_target} PUBLIC RAYGAME_TESTLIB_GTEST)
    target_link_libraries(${_target} PUBLIC GTest::gtest)
endfunction()

function(raygame_add_test _target)
    raygame_link_testlib(${_target})
    gtest_discover_tests(${_target})
endfunction()

function(raygame_test _target)
    set(options NO_MAIN NO_TESTLIB)
    set(oneValueArgs)
    set(multiValueArgs SRCS DEPS DEFS)
    cmake_parse_arguments(RAYGAME_TESTARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    set(_TARGET "RayGameTest${_target}")
    add_executable(${_TARGET})
    target_compile_features(${_TARGET} PUBLIC cxx_std_23)
    target_include_directories(${_TARGET} PUBLIC ${RayGame_SOURCE_DIR})
    set_target_properties(
        ${_TARGET}
        PROPERTIES VERSION ${RayGame_VERSION}
                   CXX_VISIBILITY_PRESET hidden
                   CXX_STANDARD ${RAYGAME_CXX_STANDARD}
                   CXX_STANDARD_REQUIRED YES
                   VISIBILITY_INLINES_HIDDEN YES
    )
    raygame_add_args(${_TARGET})
    raygame_add_defs(${_TARGET})
    raygame_add_test(${_TARGET})
    target_compile_options(${_TARGET} PRIVATE -coverage)
    target_link_options(${_TARGET} PRIVATE -coverage)
    if($<NOT:${RAYGAME_TESTARGS_NO_MAIN}>)
        target_compile_definitions(${_TARGET} PUBLIC RAYTEST_NO_MAIN)
    endif()
    if($<NOT:${RAYGAME_TESTARGS_NO_TESTLIB}>)
        raygame_link_testlib(${_TARGET})
    endif()
    target_sources(${_TARGET} PUBLIC ${RAYGAME_TESTARGS_SRCS})
    target_compile_definitions(${_TARGET} PUBLIC ${RAYGAME_TESTARGS_DEFS})
    target_link_libraries(${_TARGET} PUBLIC RayGame::RayTest)
    target_link_libraries(${_TARGET} PUBLIC ${RAYGAME_TESTARGS_DEPS})
endfunction()
