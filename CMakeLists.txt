cmake_minimum_required(VERSION 3.29)

project(RayGame
	VERSION 0.0.1
	DESCRIPTION "A top-down sprite-based game in C++"
	LANGUAGES CXX
)

add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
	CMAKE_CXX_STANDARD 23
	CMAKE_CXX_STANDARD_REQUIRED True
	CXX_EXTENSIONS OFF
)

# Utility
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(CompilerFlags)
target_compile_options(${PROJECT_NAME} PRIVATE -Werror ${CMAKE_CXX_LINTER_FLAGS})

# Docs
option(BUILD_DOC "Build documentation" ON)
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
