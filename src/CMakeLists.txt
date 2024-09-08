cmake_minimum_required(VERSION 3.25...3.29)

project(
    RayGame
    VERSION 0.0.0
    DESCRIPTION "A simple game and engine in C++"
    LANGUAGES CXX C
)

cmake_path(GET PROJECT_SOURCE_DIR PARENT_PATH MAIN_PATH)
list(APPEND CMAKE_MODULE_PATH ${MAIN_PATH}/cmake)
include(RgPaths)
include(RgProjectArgs)
include(RgProjectOptions)
include(RgPreventInSourceBuilds)
add_subdirectory(core)
add_subdirectory(game)
add_subdirectory(system)
add_subdirectory(world)
add_subdirectory(test)
