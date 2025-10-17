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

set(RAYGAME_PATH_SRC ${PROJECT_SOURCE_DIR})
list(APPEND CMAKE_MODULE_PATH ${RAYGAME_PATH_SRC}/cmake)
include(RayGameSetup)

################################################################################
# CMake config vars
################################################################################

set(RAYGAME_IS_TOPLEVEL ${PROJECT_IS_TOP_LEVEL})

set(RAYGAME_OS_IS_ANDROID $<PLATFORM_ID:Android>)
set(RAYGAME_OS_IS_BSD $<PLATFORM_ID:FreeBSD,kFreeBSD,MirBSD,NetBSD,OpenBSD>)
set(RAYGAME_OS_IS_HURD $<PLATFORM_ID:GNU>)
set(RAYGAME_OS_IS_LINUX $<PLATFORM_ID:Linux>)
set(RAYGAME_OS_IS_MAC $<PLATFORM_ID:Darwin>)
set(RAYGAME_OS_IS_WINDOWS $<PLATFORM_ID:Windows>)
if($<NOT:$<OR:RAYGAME_OS_IS_ANDROID,RAYGAME_OS_IS_BSD,RAYGAME_OS_IS_HURD,RAYGAME_OS_IS_LINUX,RAYGAME_OS_IS_MAC,RAYGAME_OS_IS_WINDOWS>>)
    message(FATAL_ERROR "Unknown OS")
endif()

set(RAYGAME_BT_IS_DEBUG $<CONFIG:Debug>)
set(RAYGAME_BT_IS_RELEASE $<OR:$<CONFIG:Release,RelWithDebInfo,MinSizeRel>>)
if($<NOT:$<OR:RAYGAME_BT_IS_DEBUG,RAYGAME_BT_IS_RELEASE>>)
    message(FATAL_ERROR "Unknown Build Type")
endif()

################################################################################
# Options                                                                      #
################################################################################

# Enable clangd compile_commands.json generation
option(RAYGAME_ENABLE_COMPILE_COMMANDS "Create compile_commands.json file" ${RAYGAME_IS_TOPLEVEL})

option(RAYGAME_BUILD_TESTS "Build tests" ${RAYGAME_IS_TOPLEVEL})
option(RAYGAME_BUILD_DOCS "Build documentation" ${RAYGAME_IS_TOPLEVEL})
option(RAYGAME_BUILD_GAMES "Build games" ${RAYGAME_IS_TOPLEVEL})

option(RAYGAME_GUI_DISABLE_COCOA "Disable the MacOS Cocoa GUI backend" $<NOT:RAYGAME_OS_IS_MAC>)
option(RAYGAME_GUI_DISABLE_DWM "Disable the Windows DWM GUI backend" $<NOT:RAYGAME_OS_IS_WINDOWS>)
option(RAYGAME_GUI_DISABLE_WAYLAND "Disable the Linux Wayland GUI backend" $<NOT:RAYGAME_OS_IS_LINUX>)
option(RAYGAME_GUI_DISABLE_X11 "Disable the Linux X11 GUI backend" ON)

option(RAYGAME_ENABLE_COVERAGE "Enable code coverage" OFF)

set(RAYGAME_GUI_DEFAULT_WINDOW_TITLE "RayGame" CACHE STRING "Default GUI window title")

option(RAYGAME_MATH_RANDOM_FULL "Non-deterministic random numbers" OFF)

option(RAYGAME_LOG_DISABLE_SOURCE_LOCATION "Disable source_location in logs" OFF)
set(RAYGAME_LOG_LEVEL "DEBUG" CACHE STRING "Minimum log level to be displayed")
set_property(
    CACHE RAYGAME_LOG_LEVEL
    PROPERTY STRINGS
             "TRACE"
             "DEBUG"
             "INFO"
             "NOTE"
             "PROGRESS"
             "WARNING"
             "ERROR"
             "FATAL"
)

option(RAYGAME_TIME_FRAMES "Record the average frame time" OFF)

if(RAYGAME_ENABLE_COMPILE_COMMANDS)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Generate compile_commands.json")
endif()

################################################################################
# Main
################################################################################
include(GenerateExportHeader)

if(RAYGAME_ENABLE_COVERAGE)
  # set compiler flags
  set(CMAKE_CXX_FLAGS "-O0 -coverage")

  # find required tools
  find_program(LCOV lcov REQUIRED)
  find_program(GENHTML genhtml REQUIRED)

  # add coverage target
  add_custom_target(coverage
    # gather data
    COMMAND ${LCOV} --directory . --capture --output-file coverage.info
    # generate report
    COMMAND ${GENHTML} --demangle-cpp -o coverage coverage.info
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

include(RayGameBin)
include(RayGameLib)
include(RayGameWayland)
include(RayGameTest)
raygame_enable_testing()

add_subdirectory(third_party)
add_subdirectory(raygame)
add_subdirectory(tests)
add_subdirectory(docs)

find_package(Doxygen REQUIRED COMPONENTS dot)
if(Doxygen_FOUND)
    set(DOXYGEN_WARN_IF_UNDOCUMENTED YES)
    set(DOXYGEN_EXTRACT_ALL YES) # Change to no to generate warnings for all undocumented items
    configure_file(third_party/doxygen/Doxyfile.in Doxyfile)
    doxygen_add_docs(
        RayGameDocs
        raygame README.md
        CONFIG_FILE ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    )
endif()
add_subdirectory(games)
