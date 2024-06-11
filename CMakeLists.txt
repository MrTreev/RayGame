cmake_minimum_required(VERSION 3.25...3.29)
include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
    RayGame
    VERSION 0.0.1
    DESCRIPTION "A top-down sprite-based game in C++"
    LANGUAGES CXX
)
add_executable(${PROJECT_NAME})

option(BUILD_DOC "Build documentation" OFF)
option(ENABLE_ASAN "Enable the Address Sanitiser" OFF)
option(ENABLE_AVX "Enable AVX instructions" ON)
option(ENABLE_LTO "Enable Link-Time Optimisation" OFF)
option(ENABLE_MSAN "Enable the Memory Sanitiser" OFF)
option(ENABLE_UBSAN "Enable the Undefined Behaviour Sanitiser" OFF)
option(RAYGAME_IGNORE_CONDITIONS "Ignore all runtime condition checks" OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(default_build_type Debug)
    message(
        STATUS
            "Setting build type to '${default_build_type}' as none was specified."
    )
    set(CMAKE_BUILD_TYPE "${default_build_type}"
        CACHE STRING "Choose the type of build." FORCE
    )
    set_property(
        CACHE CMAKE_BUILD_TYPE
        PROPERTY STRINGS
                 "Debug"
                 "Release"
                 "MinSizeRel"
                 "RelWithDebInfo"
    )
endif()

if(NOT RAYGAME_BACKEND)
    set(default_raygame_backend RAYLIB)
    message(
        STATUS
            "Setting build type to '${default_raygame_backend}' as none was specified."
    )
    set(RAYGAME_BACKEND "${default_raygame_backend}"
        CACHE STRING "Choose the graphics backend." FORCE
    )
    set_property(CACHE RAYGAME_BACKEND PROPERTY STRINGS "RAYLIB" "VULKAN" "SDL")
endif()

add_subdirectory(src)
