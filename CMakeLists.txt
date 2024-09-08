cmake_minimum_required(VERSION 3.25...3.29)

project(
    RayGame
    VERSION 0.0.0
    DESCRIPTION "A simple game and engine in C++"
	LANGUAGES CXX C
)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(RgPaths)
include(RgProjectOptions)
include(RgPreventInSourceBuilds)
add_subdirectory(src)
