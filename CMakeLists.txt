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
cmake_policy(SET CMP0155 OLD)
set(RAYGAME_PATH_SRC ${PROJECT_SOURCE_DIR})
list(APPEND CMAKE_MODULE_PATH ${RAYGAME_PATH_SRC}/cmake)
cmake_policy(SET CMP0063 NEW)
cmake_policy(SET CMP0128 NEW)

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
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel")


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
if($<NOT:$<OR:RAYGAME_OS_IS_ANDROID,RAYGAME_OS_IS_BSD,RAYGAME_OS_IS_HURD,RAYGAME_OS_IS_LINUX,RAYGAME_OS_IS_MAC,RAYGAME_OS_IS_WINDOWS>>
)
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

set(RAYGAME_GUI_DEFAULT_WINDOW_TITLE
    "RayGame"
    CACHE STRING "Default GUI window title"
)

option(RAYGAME_MATH_RANDOM_FULL "Non-deterministic random numbers" OFF)

set(RAYGAME_SOURCE_LOCATION
    "FULL"
    CACHE STRING "Souce location length"
)
set_property(CACHE RAYGAME_SOURCE_LOCATION PROPERTY STRINGS "FULL" "BASE" "NONE")

set(RAYGAME_LOG_LEVEL
    "DEBUG"
    CACHE STRING "Minimum log level to be displayed"
)
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
    set(CMAKE_EXPORT_COMPILE_COMMANDS
        ON
        CACHE BOOL "Generate compile_commands.json"
    )
endif()

################################################################################
# Main
################################################################################
include(GenerateExportHeader)
include(FetchContent)

if(RAYGAME_ENABLE_COVERAGE)
    # set compiler flags
    set(CMAKE_CXX_FLAGS "-O0 -coverage")

    # find required tools
    find_program(LCOV lcov REQUIRED)
    find_program(GENHTML genhtml REQUIRED)

    # add coverage target
    add_custom_target(
        coverage
        # gather data
        COMMAND ${LCOV} --directory . --capture --output-file coverage.info
        # generate report
        COMMAND ${GENHTML} --demangle-cpp -o coverage coverage.info
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()

function(raygame_bin _target)
    set(options NO_DEFS NO_ARGS)
    set(oneValueArgs)
    set(multiValueArgs SRCS DEPS DEFS)
    cmake_parse_arguments(RAYGAME_TESTARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    add_executable(${_target})
    target_sources(${_target} PRIVATE ${RAYGAME_TESTARGS_SRCS})
    target_link_libraries(${_target} PRIVATE ${RAYGAME_TESTARGS_DEPS})
    target_compile_definitions(${_target} PRIVATE ${RAYGAME_TESTARGS_DEFS})
    set_target_properties(
        ${_target}
        PROPERTIES VERSION ${RayGame_VERSION}
                   CXX_VISIBILITY_PRESET hidden
                   VISIBILITY_INLINES_HIDDEN YES
    )
    set_target_properties(${_target} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
endfunction()

function(raygame_lib _target)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs HDRS SRCS DEPS DEFS)
    cmake_parse_arguments(RAYGAME_TESTARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    add_library(${_target})
    target_include_directories(${_target} PUBLIC $<BUILD_INTERFACE:${RayGame_SOURCE_DIR}> $<INSTALL_INTERFACE:include/raygame>)
    target_sources(${_target} PUBLIC ${RAYGAME_TESTARGS_HDRS})
    target_sources(${_target} PRIVATE ${RAYGAME_TESTARGS_SRCS})
    target_link_libraries(${_target} PRIVATE ${RAYGAME_TESTARGS_DEPS})
    target_compile_definitions(${_target} PUBLIC ${RAYGAME_TESTARGS_DEFS})
    set_target_properties(
        ${_target}
        PROPERTIES VERSION ${RayGame_VERSION}
                   LINKER_LANGUAGE CXX
                   CXX_VISIBILITY_PRESET hidden
                   VISIBILITY_INLINES_HIDDEN YES
    )
    set_target_properties(${_target} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
endfunction()

find_package(PkgConfig)

function(raygame_add_wayland_protocols _full_target)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs PROTOCOLS)
    cmake_parse_arguments(RAYGAME_ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    pkg_check_modules(RAYGAME_WL REQUIRED wayland-client)
    if(NOT RAYGAME_WL_FOUND)
        message(SEND_ERROR "wayland-client module could not be found")
    endif()
    string(REPLACE ":" "" _target ${_full_target})

    find_program(WAYLAND_SCANNER_EXECUTABLE NAMES wayland-scanner)
    set(${_target}_proto_dir "${CMAKE_CURRENT_BINARY_DIR}/wayland")

    add_library(${_target} SHARED)
    set_target_properties(
        ${_target}
        PROPERTIES COMPILER_WARNING_AS_ERROR OFF
                   LANGUAGE C
                   C_EXTENSIONS OFF
                   LINKER_LANGUAGE C
                   SYSTEM ON
    )
    target_compile_options(${_target} PRIVATE -w)

    foreach(protocol IN LISTS RAYGAME_ARGS_PROTOCOLS)
        set(${protocol}_header "${${_target}_proto_dir}/${protocol}-client-protocol.h")
        set(${protocol}_source "${${_target}_proto_dir}/${protocol}-protocol.c")
        set(${protocol}_xml "${RAYGAME_PATH_SRC}/third_party/wayland/${protocol}.xml")
        set_source_files_properties(${${protocol}_source} GENERATED)
        set_source_files_properties(${${protocol}_header} GENERATED)
        set_property(SOURCE ${${protocol}_header} ${${protocol}_source} PROPERTY SKIP_AUTOMOC ON)
        add_custom_command(
            OUTPUT "${${protocol}_source}"
            COMMAND ${WAYLAND_SCANNER_EXECUTABLE} public-code ${${protocol}_xml} ${${protocol}_source}
            DEPENDS ${${protocol}_xml}
            VERBATIM
        )
        add_custom_command(
            OUTPUT "${${protocol}_header}"
            COMMAND ${WAYLAND_SCANNER_EXECUTABLE} client-header ${${protocol}_xml} ${${protocol}_header}
            DEPENDS ${${protocol}_xml}
            VERBATIM
        )
        target_sources(
            ${_target}
            PUBLIC ${${protocol}_header}
            PRIVATE ${${protocol}_source}
        )
    endforeach()

    target_include_directories(
        ${_target}
        PUBLIC ${${_target}_proto_dir}
        PRIVATE ${RAYGAME_WL_INCLUDE_DIRS}
    )
    target_link_libraries(${_target} PUBLIC ${RAYGAME_WL_LINK_LIBRARIES})
    target_link_options(${_target} PRIVATE ${RAYGAME_WL_LDFLAGS})
    target_compile_options(${_target} PRIVATE ${RAYGAME_WL_CFLAGS})
    target_include_directories(${_target} PUBLIC ${${RAYGAME_ARGS_TARGET}_proto_dir})
endfunction()

if(RAYGAME_BUILD_TESTS)
    enable_testing()
    FetchContent_Declare(
        googletest URL https://github.com/google/googletest/releases/download/v1.16.0/googletest-1.16.0.tar.gz
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt
        ON
        CACHE BOOL "" FORCE
    )
    FetchContent_MakeAvailable(googletest)
    include(CTest)
    include(GoogleTest)
endif()

function(raygame_test _target)
    set(options NO_MAIN NO_TESTLIB)
    set(oneValueArgs)
    set(multiValueArgs SRCS DEPS DEFS)
    cmake_parse_arguments(RAYGAME_TESTARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    set(_TARGET "RayGameTest${_target}")
    add_executable(${_TARGET})
    target_include_directories(${_TARGET} PUBLIC ${RayGame_SOURCE_DIR})
    set_target_properties(
        ${_TARGET}
        PROPERTIES VERSION ${RayGame_VERSION}
                   CXX_VISIBILITY_PRESET hidden
                   VISIBILITY_INLINES_HIDDEN YES
    )
    target_link_libraries(${_TARGET} PUBLIC GTest::gtest)
    gtest_discover_tests(${_TARGET})
    if($<NOT:${RAYGAME_TESTARGS_NO_MAIN}>)
        target_compile_definitions(${_TARGET} PUBLIC RAYTEST_NO_MAIN)
    endif()
    if($<NOT:${RAYGAME_TESTARGS_NO_TESTLIB}>)
        target_link_libraries(${_TARGET} PUBLIC GTest::gtest)
    endif()
    target_sources(${_TARGET} PUBLIC ${RAYGAME_TESTARGS_SRCS})
    target_compile_definitions(${_TARGET} PUBLIC RAYGAME_RAYTEST)
    target_compile_definitions(${_TARGET} PUBLIC ${RAYGAME_TESTARGS_DEFS})
    target_link_libraries(${_TARGET} PUBLIC RayGame::RayTest)
    target_link_libraries(${_TARGET} PUBLIC ${RAYGAME_TESTARGS_DEPS})
endfunction()

add_subdirectory(third_party)
add_subdirectory(raygame)

function(raygame_resource _target)
    set(options)
    set(oneValueArgs NAME)
    set(multiValueArgs RESOURCES)
    cmake_parse_arguments(RAYGAME_TESTARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    set(gen_dir "${PROJECT_BINARY_DIR}/generated")
    set(${RAYGAME_TESTARGS_NAME}_header "${gen_dir}/${RAYGAME_TESTARGS_NAME}.h")
    set(${RAYGAME_TESTARGS_NAME}_source "${gen_dir}/${RAYGAME_TESTARGS_NAME}.cpp")
    set_source_files_properties(${${RAYGAME_TESTARGS_NAME}_source} GENERATED)
    set_source_files_properties(${${RAYGAME_TESTARGS_NAME}_header} GENERATED)
    set_property(SOURCE ${${RAYGAME_TESTARGS_NAME}_header} ${${RAYGAME_TESTARGS_NAME}_source} PROPERTY SKIP_AUTOMOC ON)
    get_target_property(RAYGAME_RESMK_DIR
        RayGame::Tools::ResMk
        BINARY_DIR
    )
    file(REAL_PATH ${RAYGAME_TESTARGS_RESOURCES} ${RAYGAME_TESTARGS_NAME}_data)
    add_custom_command(
        OUTPUT ${${RAYGAME_TESTARGS_NAME}_header} ${${RAYGAME_TESTARGS_NAME}_source}
        COMMAND ${RAYGAME_RESMK_DIR}/resmk ${${RAYGAME_TESTARGS_NAME}_header} ${${RAYGAME_TESTARGS_NAME}_data}
        DEPENDS RayGame::Tools::ResMk
        CODEGEN
        VERBATIM
    )
    add_custom_target(${RAYGAME_TESTARGS_NAME}_dep
        DEPENDS
            ${${RAYGAME_TESTARGS_NAME}_header}
            ${${RAYGAME_TESTARGS_NAME}_source}
    )
    add_library(${_target})
    target_sources(${_target} PUBLIC ${${RAYGAME_TESTARGS_NAME}_header})
    target_sources(${_target} PRIVATE ${${RAYGAME_TESTARGS_NAME}_source})
    add_dependencies(${_target} ${RAYGAME_TESTARGS_NAME}_dep)
    target_include_directories(${_target} PUBLIC $<BUILD_INTERFACE:${gen_dir}/../> $<INSTALL_INTERFACE:include/generated>)
    target_include_directories(${_target} PUBLIC $<BUILD_INTERFACE:${RayGame_SOURCE_DIR}> $<INSTALL_INTERFACE:include/raygame>)
endfunction()

add_subdirectory(tests)
add_subdirectory(docs)

find_package(Doxygen REQUIRED COMPONENTS dot)
if(Doxygen_FOUND)
    set(DOXYGEN_WARN_IF_UNDOCUMENTED YES)
    set(DOXYGEN_EXTRACT_ALL YES) # Change to no to generate warnings for all undocumented items
    configure_file(third_party/doxygen/Doxyfile.in Doxyfile)
    doxygen_add_docs(RayGameDocs raygame README.md CONFIG_FILE ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
endif()
add_subdirectory(games)
