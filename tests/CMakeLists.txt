if(NOT RAYGAME_BUILD_TESTS)
    return()
endif()

raygame_lib(
    RayGameRayTest
    HDRS raytest/raytest.h
    SRCS raytest/raytest.cpp raytest/main.cpp
    NO_INCS
)
target_include_directories(
    RayGameRayTest
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
           $<INSTALL_INTERFACE:include/raytest>
)
raygame_link_testlib(RayGameRayTest)

add_library(RayGame::RayTest ALIAS RayGameRayTest)
add_subdirectory(core)
add_subdirectory(tools)
