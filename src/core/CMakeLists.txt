target_compile_definitions(${PROJECT_NAME} PUBLIC "RAYGAME_LOG_DEBUG")
target_sources(
    ${PROJECT_NAME}
    PUBLIC condition.cpp
           condition.h
           config.cpp
           config.h
           exception.cpp
           exception.h
           image.cpp
           image.h
           logger.cpp
           logger.h
           math.cpp
           math.h
           spritesheet.cpp
           spritesheet.h
           texture.cpp
           texture.h
           types.cpp
           types.h
           window.cpp
           window.h
)
