cmake_minimum_required(VERSION 3.25...3.29)

project(
    RayGame
    VERSION 0.0.1
    DESCRIPTION "A top-down sprite-based game in C++"
    LANGUAGES CXX
)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME})
include(CompilerFlags)
include(Doxygen)

add_subdirectory(src)

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

# SFML Library
if(NOT RAYGAME_BACKEND)
    set(default_raygame_backend RAYLIB)
    message(
        STATUS
            "Setting build type to '${default_raygame_backend}' as none was specified."
    )
    set(RAYGAME_BACKEND "${default_raygame_backend}"
        CACHE STRING "Choose the graphics backend." FORCE
    )
    set_property(
        CACHE RAYGAME_BACKEND
        PROPERTY STRINGS
                 "RAYLIB"
                 "SFML"
                 "DFPSR"
    )
endif()

if(RAYGAME_BACKEND STREQUAL SFML)
    target_compile_definitions(${PROJECT_NAME} PRIVATE "RAYGAME_BACKEND_SFML")
    include(BuildSfml)
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-audio)
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system)
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-window)
elseif(RAYGAME_BACKEND STREQUAL DFPSR)
    target_compile_definitions(${PROJECT_NAME} PRIVATE "RAYGAME_BACKEND_DFPSR")
    include(BuildDfpsr)
elseif(RAYGAME_BACKEND STREQUAL RAYLIB)
	target_compile_definitions(${PROJECT_NAME} PRIVATE "RAYGAME_BACKEND_RAYLIB")
	include(BuildRaylib)
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
endif()
