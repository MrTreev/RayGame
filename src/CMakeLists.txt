add_subdirectory(core)
add_subdirectory(system)
add_subdirectory(world)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(compiler_args)
include(backend)
include(embed)
include(docs)

target_sources(${PROJECT_NAME} PUBLIC main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    target_compile_definitions(${PROJECT_NAME} PUBLIC "RAYGAME_LOG_DEBUG")
    target_compile_definitions(${PROJECT_NAME} PUBLIC "RAYGAME_LOG_LOCATION")
    target_compile_options(${PROJECT_NAME} PUBLIC -Og)
    target_compile_options(${PROJECT_NAME} PUBLIC -ggdb)
else()
    target_compile_definitions(${PROJECT_NAME} PUBLIC "RAYGAME_LOG_INFO")
    target_compile_options(${PROJECT_NAME} PUBLIC -Ofast)
endif()

if(RAYGAME_IGNORE_CONDITIONS)
    target_compile_definitions(
        ${PROJECT_NAME} PUBLIC "RAYGAME_IGNORE_CONDITIONS"
    )
endif()
