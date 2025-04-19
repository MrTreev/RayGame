################################################################################
# Initial project setup                                                        #
################################################################################

cmake_minimum_required(VERSION 4.0)

project(
    RayGame
    VERSION 0.0.0
    DESCRIPTION "A simple game and engine in C++"
    LANGUAGES CXX C
)

cmake_policy(SET CMP0063 NEW)

function(raygame_assure_out_of_source_builds)
    get_filename_component(srcdir "${CMAKE_SOURCE_DIR}" REALPATH)
    get_filename_component(bindir "${CMAKE_BINARY_DIR}" REALPATH)
    if("${srcdir}" STREQUAL "${bindir}")
        message("######################################################")
        message("Warning: in-source builds are disabled")
        message("Please create a separate build directory and run cmake from there")
        message("######################################################")
        message(FATAL_ERROR "Quitting configuration")
    endif()
endfunction()
raygame_assure_out_of_source_builds()

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo")

################################################################################
# CMake config vars
################################################################################

set(RAYGAME_OS_IS_ANDROID OFF)
set(RAYGAME_OS_IS_BSD OFF)
set(RAYGAME_OS_IS_HURD OFF)
set(RAYGAME_OS_IS_LINUX ON)
set(RAYGAME_OS_IS_MAC OFF)
set(RAYGAME_OS_IS_WINDOWS OFF)

set(RAYGAME_BT_IS_DEBUG ON)
set(RAYGAME_BT_IS_RELEASE OFF)

################################################################################
# Options                                                                      #
################################################################################

# Enable clangd compile_commands.json generation
option(RAYGAME_ENABLE_COMPILE_COMMANDS "Create compile_commands.json file" ON)

option(RAYGAME_BUILD_TESTS "Build tests" ON)
option(RAYGAME_BUILD_DOCS  "Build documentation" ON)
option(RAYGAME_BUILD_GAMES "Build games" ON)

option(RAYGAME_GUI_DISABLE_COCOA "Disable the MacOS Cocoa GUI backend" $<NOT:${RAYGAME_OS_IS_MAC}>)
option(RAYGAME_GUI_DISABLE_DWM "Disable the Windows DWM GUI backend" $<NOT:${RAYGAME_OS_IS_WINDOWS}>)
option(RAYGAME_GUI_DISABLE_WAYLAND "Disable the Linux Wayland GUI backend" $<NOT:${RAYGAME_OS_IS_LINUX}>)
option(RAYGAME_GUI_DISABLE_X11 "Disable the Linux X11 GUI backend" $<NOT:${RAYGAME_OS_IS_LINUX}>)
option(RAYGAME_GUI_DISABLE_IMGUI "Disable the IMGUI GUI backend" $<NOT:${RAYGAME_BT_IS_DEBUG}>)
option(RAYGAME_GUI_DEFAULT_WINDOW_HEIGHT "Default GUI window height" 640)
option(RAYGAME_GUI_DEFAULT_WINDOW_WIDTH "Default GUI window width" 480)
set(RAYGAME_GUI_DEFAULT_WINDOW_TITLE "RayGame" CACHE STRING "Default GUI window width")

option(RAYGAME_MATH_RANDOM_FULL "Non-deterministic random numbers" OFF)
option(RAYGAME_MATH_FORCE_GENERIC "Force generic implementations of maths functions" OFF)

option(RAYGAME_LOG_DISABLE_SOURCE_LOCATION "Disable source_location in logs" OFF)
set(RAYGAME_LOG_LEVEL "DEBUG" CACHE STRING "Minimum log level to be displayed")
set_property(CACHE RAYGAME_LOG_LEVEL PROPERTY STRINGS "TRACE" "DEBUG" "INFO" "NOTE" "PROGRESS" "WARNING" "ERROR" "FATAL")

option(RAYGAME_TIME_FRAMES "Record the average frame time" OFF)

################################################################################
# Main
################################################################################
include(GenerateExportHeader)

set(RAYGAME_PATH_SRC ${PROJECT_SOURCE_DIR})
list(APPEND CMAKE_MODULE_PATH ${RAYGAME_PATH_SRC}/cmake)
include(RayGameWayland)
include(RayGameCompilerArgs)

if(RAYGAME_ENABLE_COMPILE_COMMANDS)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

if(RAYGAME_WARNINGS_AS_ERRORS)
    message(TRACE "Warnings are treated as errors")
    list(APPEND RAYGAME_CLANG_OPTIONS -Werror)
    list(APPEND RAYGAME_GCC_OPTIONS -Werror)
    list(APPEND RAYGAME_MSVC_OPTIONS /WX)
endif()

function(raygame_lib _target)
    add_library(${_target})
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
    target_compile_definitions(${_target} PUBLIC "RAYGAME_LOG_${RAYGAME_LOG_LEVEL}")
    if(RAYGAME_LOG_DISABLE_SOURCE_LOCATION)
        target_compile_definitions(${_target} PUBLIC "RAYGAME_DISABLE_SOURCE_LOCATION")
    elseif(RAYGAME_BT_IS_DEBUG)
        target_compile_definitions(${_target} PUBLIC "RAYGAME_ENABLE_SOURCE_LOCATION")
    endif()
endfunction()

add_subdirectory(raygame)

if(RAYGAME_BUILD_TESTS)
    add_subdirectory(tests)
endif()

if(RAYGAME_BUILD_DOCS)
    add_subdirectory(docs)
endif()

if(RAYGAME_BUILD_GAMES)
    add_subdirectory(games)
endif()
