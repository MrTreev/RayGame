cmake_minimum_required(VERSION 3.6...3.29)

project(
    RayGame
    VERSION 0.0.0
    DESCRIPTION "A simple game and engine in C++"
    LANGUAGES CXX C
)

cmake_policy(SET CMP0063 NEW)
set(RAYGAME_PATH_ETC ${PROJECT_SOURCE_DIR}/etc)
set(RAYGAME_PATH_SRC ${PROJECT_SOURCE_DIR}/src)
set(RAYGAME_PATH_EXT ${CMAKE_CURRENT_BINARY_DIR}/ext)
list(APPEND CMAKE_MODULE_PATH ${RAYGAME_PATH_SRC}/cmake)

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

option(RAYGAME_BUILD_DOC "Build documentation" OFF)
option(RAYGAME_TEST_ENABLE "Build and run tests" ON)
option(RAYGAME_RUN_TESTS "Run tests in build" OFF)
option(RAYGAME_RUN_GAME "Run game in build" OFF)

option(RAYGAME_WARNINGS_AS_ERRORS "Warnings as errors" OFF)

option(RAYGAME_ENABLE_WAYLAND "Enable Wayland Backend" ON)
option(RAYGAME_ENABLE_X11 "Enable X11 Backend" ON)
option(RAYGAME_IGNORE_CONDITIONS "Ignore all runtime condition checks" OFF)

option(RAYGAME_ENABLE_AVX "Enable AVX instructions" ON)

option(RAYGAME_ENABLE_COMPILE_COMMANDS "Create compile_commands.json file" ON)
option(RAYGAME_ENABLE_CLANG_TIDY "Enable Clang Tidy" ON)
option(RAYGAME_ENABLE_SOURCE_LOCATION "Enable source_location in logs" ON)

set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo")
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

if(RAYGAME_ENABLE_COMPILE_COMMANDS)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

if(RAYGAME_TEST_ENABLE)
    include(CTest)
    set(rg_no_dev_warnings_backup "$CACHE{CMAKE_SUPPRESS_DEVELOPER_WARNINGS}")
    set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS
        ON
        CACHE INTERNAL "" FORCE
    )
    add_subdirectory(${RAYGAME_PATH_ETC}/doctest)
    set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS
        ${rg_no_dev_warnings_backup}
        CACHE INTERNAL "" FORCE
    )
endif()

add_subdirectory(src)

if(RAYGAME_BUILD_DOC)
    find_package(Doxygen REQUIRED OPTIONAL_COMPONENTS dot)
    set(DOXYGEN_CALLER_GRAPH YES)
    set(DOXYGEN_CALL_GRAPH YES)
    set(DOXYGEN_CLANG_ASSISTED_PARSING NO)
    set(DOXYGEN_EXAMPLE_RECURSIVE YES)
    set(DOXYGEN_GENERATE_TREEVIEW YES)
    set(DOXYGEN_HAVE_DOT YES)
    set(DOXYGEN_INTERACTIVE_SVG YES)
    set(DOXYGEN_RECURSIVE YES)
    set(DOXYGEN_REFERENCED_BY_RELATION YES)
    set(DOXYGEN_REFERENCES_RELATION YES)
    set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
    set(DOXYGEN_CALLER_GRAPH YES)
    set(DOXYGEN_CALL_GRAPH YES)
    set(DOXYGEN_DOT_IMAGE_FORMAT svg)
    set(DOXYGEN_DOT_TRANSPARENT YES)
    set(DOXYGEN_EXTRACT_ALL YES)
    set(DOXYGEN_EXTRACT_LOCAL_CLASSES NO)
    set(DOXYGEN_GENERATE_TREEVIEW YES)
    set(DOXYGEN_NUM_PROC_THREADS 16)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doxygen)
    set(DOXYGEN_QUIET YES)
    set(DOXYGEN_SORT_BRIEF_DOCS YES)
    set(DOXYGEN_SORT_BY_SCOPE_NAME YES)
    set(DOXYGEN_SORT_GROUP_NAMES YES)
    set(DOXYGEN_SORT_MEMBERS_CTORS_1ST YES)
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${PROJECT_SOURCE_DIR}/README.md")
    message(STATUS "Adding `doxygen-docs` target that builds the documentation.")
    doxygen_add_docs(
        doxygen-docs ALL ${RAYGAME_PATH_SRC}
        COMMENT "Generating documentation - entry file: ${CMAKE_CURRENT_BINARY_DIR}/html/index.html"
    )
endif()
