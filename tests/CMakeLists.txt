raygame_lib(RayGameRayTest)
set_target_properties(RayGameRayTest PROPERTIES LINKER_LANGUAGE CXX)
add_library(RayGame::RayTest ALIAS RayGameRayTest)
target_sources(RayGameRayTest
    PUBLIC
    raytest/test.h
    raytest/tests_begin.h
)
target_include_directories(RayGameRayTest PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/raytest>
)
target_link_libraries(RayGameRayTest PUBLIC doctest::doctest)
set(RAYGAME_RAYTEST_MAIN ${CMAKE_CURRENT_SOURCE_DIR}/raytest/main.cpp)

function(raygame_test _target)
    set(options NO_MAIN)
    set(oneValueArgs)
    set(multiValueArgs SOURCES DEPENDS DEFINES)
    cmake_parse_arguments(RAYGAME_TESTARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    set(RAYGAME_TEST_USE_MAIN $<NOT:$<BOOL:${RAYGAME_TESTARGS_NO_MAIN}>>)
    add_executable(${_target})
    target_compile_features(${_target} PUBLIC cxx_std_23)
    target_include_directories(${_target} PUBLIC
        $<BUILD_INTERFACE:${RayGame_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include/raygame>
    )
    set_target_properties(
        ${_target}
        PROPERTIES VERSION ${RayGame_VERSION}
                   CXX_VISIBILITY_PRESET hidden
                   CXX_STANDARD 23
                   CXX_STANDARD_REQUIRED YES
                   VISIBILITY_INLINES_HIDDEN YES
    )
    raygame_add_args(${_target})
    raygame_add_defs(${_target})
    target_sources(
        ${_target} PUBLIC
            $<${RAYGAME_TEST_USE_MAIN}:${RAYGAME_RAYTEST_MAIN}>
            ${RAYGAME_TESTARGS_SOURCES}
    )
    target_include_directories(${_target} PUBLIC ${DOCTEST_INCLUDE_DIR})
    target_link_libraries(${_target} PUBLIC RayGame::RayTest)
    doctest_discover_tests(${_target})
endfunction()

add_subdirectory(core)
