cmake_minimum_required(VERSION 3.25...3.29)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
    RayGame
    VERSION 0.0.1
    DESCRIPTION "A top-down sprite-based game in C++"
    LANGUAGES CXX
)
add_executable(${PROJECT_NAME})

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES CMAKE_CXX_STANDARD 23
               CMAKE_CXX_STANDARD_REQUIRED True
               CXX_EXTENSIONS OFF
               INTERPROCEDURAL_OPTIMIZATION ${ENABLE_LTO}
)

target_sources(${PROJECT_NAME} PUBLIC main.cpp)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(core)
add_subdirectory(system)
add_subdirectory(world)

option(BUILD_DOC "Build documentation" OFF)
option(ENABLE_ASAN "Enable the Address Sanitiser" OFF)
option(ENABLE_AVX "Enable AVX instructions" ON)
option(ENABLE_LTO "Enable Link-Time Optimisation" OFF)
option(ENABLE_MSAN "Enable the Memory Sanitiser" OFF)
option(ENABLE_UBSAN "Enable the Undefined Behaviour Sanitiser" OFF)
option(RAYGAME_IGNORE_CONDITIONS "Ignore all runtime condition checks" OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(rg_def_type Debug)
    message(
        STATUS "Setting build type to '${rg_def_type}' as none was specified."
    )
    set(CMAKE_BUILD_TYPE "${rg_def_type}"
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
    set(rg_def_back SDL)
    message(
        STATUS "Setting build type to '${rg_def_back}' as none was specified."
    )
    set(RAYGAME_BACKEND "${rg_def_back}"
        CACHE STRING "Choose the graphics backend." FORCE
    )
    set_property(CACHE RAYGAME_BACKEND PROPERTY STRINGS "RAYLIB" "SDL")
endif()

if(RAYGAME_BACKEND STREQUAL RAYLIB)
    add_compile_definitions("RAYGAME_BACKEND_RAYLIB")
    add_subdirectory(../ext/raylib ext/raylib)
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
elseif(RAYGAME_BACKEND STREQUAL SDL)
    add_compile_definitions("RAYGAME_BACKEND_SDL")
    add_subdirectory(../ext/SDL ext/SDL)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
endif()

# Embedding resources into files
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(B_EMBED_SILENCE_DEVMODE_WARNING ON)
else()
    set(B_PRODUCTION_MODE ON)
endif()
add_subdirectory(../ext/battery-embed ext/battery-embed)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    add_compile_definitions("RAYGAME_LOG_DEBUG")
    add_compile_definitions("RAYGAME_LOG_LOCATION")
    add_compile_options(-Og)
    add_compile_options(-ggdb)
else()
    add_compile_definitions("RAYGAME_LOG_INFO")
    target_compile_options(${PROJECT_NAME} PUBLIC -Ofast)
endif()

if(RAYGAME_IGNORE_CONDITIONS)
    target_compile_definitions(
        ${PROJECT_NAME} PUBLIC "RAYGAME_IGNORE_CONDITIONS"
    )
endif()

if(ENABLE_AVX)
    add_compile_options(-mavx)
    add_compile_options(-mavx2)
endif()

if(ENABLE_MSAN AND ENABLE_ASAN)
    message(WARNING "Compiling with both ASAN and MSAN is not recommended")
endif()

if(ENABLE_ASAN)
    add_compile_options(-fno-omit-frame-pointer)
    add_compile_options(-fsanitize=address)
endif()

if(ENABLE_MSAN)
    add_compile_options(-fno-omit-frame-pointer)
    add_compile_options(-fsanitize=memory)
endif()

if(ENABLE_UBSAN)
    add_compile_options(-fno-omit-frame-pointer)
    add_compile_options(-fsanitize=undefined)
endif()

if(BUILD_DOC)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        # set input and output files
        set(DOXYFILE ../Doxyfile)
        message("Doxygen build started")
        add_custom_target(
            doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
        )
    else(DOXYGEN_FOUND)
        message(
            "Doxygen need to be installed to generate the doxygen documentation"
        )
    endif(DOXYGEN_FOUND)
endif(BUILD_DOC)

# Compiler Options
add_compile_options(-std=c++23)

add_compile_options(-fdelete-null-pointer-checks)
add_compile_options(-fsized-deallocation)
add_compile_options(-fstack-protector)
add_compile_options(-fstrict-enums)

add_compile_options(-Werror)
add_compile_options(-Wall)
add_compile_options(-Wextra)
add_compile_options(-Wpedantic)
add_compile_options(-Wabi)
add_compile_options(-Wdeprecated)
add_compile_options(-Wdirect-ivar-access)
add_compile_options(-Weffc++)
add_compile_options(-Wempty-init-stmt)
add_compile_options(-Wempty-translation-unit)
add_compile_options(-Wexplicit-ownership-type)
add_compile_options(-Wformat)
add_compile_options(-Wformat-pedantic)
add_compile_options(-Wformat-type-confusion)
add_compile_options(-Wformat-zero-length)
add_compile_options(-Wfour-char-constants)
add_compile_options(-Wframe-address)
add_compile_options(-Wgcc-compat)
add_compile_options(-Wgnu)
add_compile_options(-Wheader-hygiene)
add_compile_options(-Wimplicit-function-declaration)
add_compile_options(-Wimport-preprocessor-directive-pedantic)
add_compile_options(-Wincompatible-function-pointer-types-strict)
add_compile_options(-Wincomplete-module)
add_compile_options(-Winconsistent-missing-destructor-override)
add_compile_options(-Winfinite-recursion)
add_compile_options(-Wint-in-bool-context)
add_compile_options(-Wmicrosoft)
add_compile_options(-Wmisleading-indentation)
add_compile_options(-Wmissing-braces)
add_compile_options(-Wmove)
add_compile_options(-Wnewline-eof)
add_compile_options(-Wnon-gcc)
add_compile_options(-Wnonportable-cfstrings)
add_compile_options(-Wnonportable-include-path)
add_compile_options(-Wnonportable-system-include-path)
add_compile_options(-Wnonportable-vector-initialization)
add_compile_options(-Wnull-pointer-arithmetic)
add_compile_options(-Wnull-pointer-subtraction)
add_compile_options(-Wold-style-cast)
add_compile_options(-Wpedantic-core-features)
add_compile_options(-Wpointer-arith)
add_compile_options(-Wrange-loop-construct)
add_compile_options(-Wredundant-move)
add_compile_options(-Wreserved-macro-identifier)
add_compile_options(-Wshadow-all)
add_compile_options(-Wsign-compare)
add_compile_options(-Wsign-conversion)
add_compile_options(-Wtautological-compare)
add_compile_options(-Wthread-safety)
add_compile_options(-Wundef)
add_compile_options(-Wundef-prefix)
add_compile_options(-Wunused)
add_compile_options(-Wvariadic-macros)
add_compile_options(-Wvector-conversion)
add_compile_options(-Wvla)
add_compile_options(-Wzero-as-null-pointer-constant)
add_compile_options(-Wzero-length-array)
