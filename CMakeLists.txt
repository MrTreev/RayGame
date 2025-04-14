################################################################################
# Initial project setup                                                        #
################################################################################

cmake_minimum_required(VERSION 3.6...3.29)

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


################################################################################
# Options                                                                      #
################################################################################

# Enable clangd compile_commands.json generation
option(RAYGAME_ENABLE_COMPILE_COMMANDS "Create compile_commands.json file" ON)

option(RAYGAME_BUILD_TESTS "Build tests" ON)
option(RAYGAME_BUILD_DOCS  "Build documentation" ON)
option(RAYGAME_BUILD_GAMES "Build games" ON)

option(RAYGAME_GUI_DISABLE_COCOA "Disable the MacOS Cocoa GUI backend" OFF)
option(RAYGAME_GUI_DISABLE_DWM "Disable the Windows DWM GUI backend" OFF)
option(RAYGAME_GUI_DISABLE_WAYLAND "Disable the Linux Wayland GUI backend" OFF)
option(RAYGAME_GUI_DISABLE_X11 "Disable the Linux X11 GUI backend" OFF)
option(RAYGAME_GUI_DISABLE_IMGUI "Disable the IMGUI GUI backend" OFF)
option(RAYGAME_GUI_DEFAULT_WINDOW_HEIGHT "Default GUI window height" 640)
option(RAYGAME_GUI_DEFAULT_WINDOW_WIDTH "Default GUI window width" 480)
option(RAYGAME_GUI_DEFAULT_WINDOW_TITLE "Default GUI window width" "RAYGAME")

option(RAYGAME_MATH_RANDOM_FULL "Non-deterministic random numbers" OFF)
option(RAYGAME_MATH_RANDOM_INIT "Random-number generation seed" 42)
option(RAYGAME_MATH_FORCE_GENERIC "Force generic implementations of maths functions" OFF)

option(RAYGAME_LOG_DISABLE_SOURCE_LOCATION "Disable source_location in logs" OFF)
set(RAYGAME_LOG_LEVEL "DEBUG" CACHE STRING "Minimum log level to be displayed")
set_property(CACHE RAYGAME_LOG_LEVEL PROPERTY STRINGS "TRACE" "DEBUG" "INFO" "NOTE" "PROGRESS" "WARNING" "ERROR" "FATAL")

option(RAYGAME_TIME_FRAMES "Record the average frame time" OFF)

################################################################################
# Main
################################################################################

if(RAYGAME_ENABLE_COMPILE_COMMANDS)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

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
