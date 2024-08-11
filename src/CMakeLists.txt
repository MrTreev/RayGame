cmake_minimum_required(VERSION 3.25...3.29)
cmake_path(
    GET
    CMAKE_CURRENT_SOURCE_DIR
    PARENT_PATH
    RAYGAME_SUPER_DIR
)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(RAYGAME_ETC ${RAYGAME_SUPER_DIR}/etc)
include(CompilerArgs)
include(CompilerWarnings)
include(Linker)

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
option(ENABLE_STATIC_ANALYSIS "Do a bunch of extra checking" OFF)
option(RAYGAME_IGNORE_CONDITIONS "Ignore all runtime condition checks" OFF)
option(RAYGAME_GUI_USE_WAYLAND "Use Wayland for GUI backend" ON)
option(RAYGAME_EMBED_BATTERY "Use Battery for file embedding" ON)
option(RAYGAME_WARNINGS_AS_ERRORS "Warnings as errors" ON)

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
    link_libraries(asan)
endif()

if(ENABLE_MSAN)
    add_compile_options(-fno-omit-frame-pointer)
    add_compile_options(-fsanitize=memory)
    link_libraries(msan)
endif()

if(ENABLE_UBSAN)
    add_compile_options(-fno-omit-frame-pointer)
    add_compile_options(-fsanitize=undefined)
    link_libraries(ubsan)
endif()

if(BUILD_DOC)
    include(Doxygen)
    rg_enable_doxygen(YES)
endif(BUILD_DOC)

rg_set_project_warnings(${PROJECT_NAME} ${RAYGAME_WARNINGS_AS_ERRORS})
rg_configure_linker(${PROJECT_NAME})
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    target_compile_definitions(${PROJECT_NAME} PUBLIC RAYGAME_LOG_DEBUG)
    target_compile_definitions(${PROJECT_NAME} PUBLIC RAYGAME_LOG_LOCATION)
else()
    target_compile_definitions(${PROJECT_NAME} PUBLIC RAYGAME_LOG_INFO)
endif()

if(RAYGAME_GUI_USE_WAYLAND)
    target_compile_definitions(${PROJECT_NAME} PUBLIC "RAYGAME_GUI_USE_WAYLAND")
endif()

if(RAYGAME_EMBED_BATTERY)
    include(FindBattery)
    add_battery_embed(${PROJECT_NAME})
endif()

if(ENABLE_STATIC_ANALYSIS)
    include(StaticAnalysis)
    rg_enable_clang_tidy(${PROJECT_NAME})
    rg_enable_include_what_you_use(${PROJECT_NAME})
endif()

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++23)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(core)
add_subdirectory(system)
add_subdirectory(world)
target_sources(${PROJECT_NAME} PUBLIC main.cpp)

# Compiler Options
add_compile_options(-std=c++23)

add_compile_options(-fdelete-null-pointer-checks)
add_compile_options(-fsized-deallocation)
add_compile_options(-fstack-protector)
add_compile_options(-fstrict-enums)
add_compile_options(-pedantic)
