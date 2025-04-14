raygame_lib(RayGameCoreBase)
add_library(RayGame::Core::Base ALIAS RayGameCoreBase)
target_sources(
    RayGameCoreBase
    PUBLIC
        concepts.h
        condition.h
        config.h
        debug.h
        exception.h
        logger.h
        matrix.h
        types.h
    PRIVATE
        concepts.cpp
        condition.cpp
        config.cpp
        debug.cpp
        exception.cpp
        logger.cpp
        matrix.cpp
        types.cpp
)

add_subdirectory(drawing)
add_subdirectory(math)
add_subdirectory(window)
