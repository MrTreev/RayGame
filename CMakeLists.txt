cmake_minimum_required(VERSION 3.29)

project(RayGame
	VERSION 0.0.1
	DESCRIPTION "A top-down sprite-based game in C++"
	LANGUAGES CXX
)

add_executable(${PROJECT_NAME})
target_compile_options(${PROJECT_NAME} PRIVATE -Werror)

set_target_properties(${PROJECT_NAME} PROPERTIES
	CMAKE_CXX_STANDARD 23
	CMAKE_CXX_STANDARD_REQUIRED True
	CXX_EXTENSIONS OFF
)

# Utility
set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE include-what-you-use)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(CompilerFlags)
include(BuildSfml)

if(NOT CMAKE_BUILD_TYPE)
    set(default_build_type Debug)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-audio)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-window)
