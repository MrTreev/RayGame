raygame_lib(
    RayGameRayTest
    HDRS raytest/raytest.h
    SRCS raytest/main.cpp
)
target_include_directories(
    RayGameRayTest PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:include/raytest>
)
raygame_link_testlib(RayGameRayTest)

function(raygame_test _target)
    set(options NO_MAIN)
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
                   CXX_STANDARD 23
                   CXX_STANDARD_REQUIRED YES
                   VISIBILITY_INLINES_HIDDEN YES
    )
    raygame_add_args(${_TARGET})
    raygame_add_defs(${_TARGET})
    raygame_add_test(${_TARGET})
    target_sources(${_TARGET} PUBLIC ${RAYGAME_TESTARGS_SRCS})
    target_compile_definitions(${_TARGET} PUBLIC ${RAYGAME_TESTARGS_DEFS})
    target_link_libraries(${_TARGET} PUBLIC RayGame::RayTest)
    target_link_libraries(${_TARGET} PUBLIC ${RAYGAME_TESTARGS_DEPS})
endfunction()

add_subdirectory(core)
