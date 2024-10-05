add_library(Core)
add_library(RayGame::Core ALIAS Core)
rg_add_args(Core)
target_compile_definitions(Core PUBLIC "RAYGAME_LOG_${RG_LOG_LEVEL}")
if(RG_ENABLE_SOURCE_LOCATION)
    target_compile_definitions(Core PUBLIC "RG_ENABLE_SOURCE_LOC")
endif()
target_compile_definitions(Core PUBLIC "RAYGAME_LOG_${RG_LOG_LEVEL}")

target_sources(
    Core
    PUBLIC colours.h
           condition.h
           config.h
           debug.h
           exception.h
           file.h
           image.h
           logger.h
           math.h
           pixel.h
           spritesheet.h
           texture.h
           types.h
           window.h
           colours.cpp
           condition.cpp
           config.cpp
           debug.cpp
           exception.cpp
           file.cpp
           image.cpp
           logger.cpp
           math.cpp
           pixel.cpp
           spritesheet.cpp
           texture.cpp
           types.cpp
           window.cpp
)
add_subdirectory(math)
add_subdirectory(windowimpl)
