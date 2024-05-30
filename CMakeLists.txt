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
option(ENABLE_MSAN "Enable the Memory Sanitiser" OFF)
option(ENABLE_UBSAN "Enable the Undefined Behaviour Sanitiser" OFF)
option(ENABLE_LTO "Enable Link-Time Optimisation" OFF)
option(RAYGAME_IGNORE_CONDITIONS "Ignore all runtime condition checks" OFF)

include(CompilerFlags)

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

if (BUILD_DOC)
	find_package(Doxygen)
	if (DOXYGEN_FOUND)
	    # set input and output files
	    set(DOXYFILE ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
	    message("Doxygen build started")
	    add_custom_target( doc_doxygen ALL
	        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
	        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	        COMMENT "Generating API documentation with Doxygen"
	        VERBATIM )
	else (DOXYGEN_FOUND)
	  message("Doxygen need to be installed to generate the doxygen documentation")
	endif (DOXYGEN_FOUND)
endif (BUILD_DOC)

FetchContent_Declare(
  battery-embed
  GIT_REPOSITORY https://github.com/batterycenter/embed.git
  GIT_TAG        v1.2.15
)
FetchContent_Declare(
    RAYLIB GIT_REPOSITORY https://github.com/MrTreev/raylib.git GIT_TAG 5.0
    SYSTEM
)

FetchContent_MakeAvailable(RAYLIB)
FetchContent_MakeAvailable(battery-embed)

set_property(
    DIRECTORY ${raylib_SOURCE_DIR}
    APPEND
    PROPERTY COMPILE_OPTIONS -Wno-error -Wno-zero-as-null-pointer-constant -Wno-implicit-const-int-float-conversion
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
