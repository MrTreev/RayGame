add_library(Core)
rg_add_args(Core)

target_compile_definitions(Core PUBLIC "RAYGAME_LOG_${RG_LOG_LEVEL}")

if(RG_ENABLE_SOURCE_LOCATION)
    target_compile_definitions(Core PUBLIC "RG_ENABLE_SOURCE_LOC")
endif()

target_compile_definitions(Core PUBLIC "RAYGAME_LOG_${RG_LOG_LEVEL}")

target_include_directories(Core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(
    Core
    PUBLIC colours.cpp
           condition.cpp
           config.cpp
           debug.cpp
           exception.cpp
           file.cpp
           image.cpp
           logger.cpp
           math.cpp
           pixel.cpp
           rect.cpp
           spritesheet.cpp
           texture.cpp
           types.cpp
           vector.cpp
           window.cpp
)
add_subdirectory(math)
add_subdirectory(windowimpl)

add_library(RayGame::Core ALIAS Core)
