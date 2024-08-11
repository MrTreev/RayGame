add_subdirectory(windowimpl)

target_sources(
    ${PROJECT_NAME}
    PUBLIC 
           colours.cpp
           condition.cpp
           config.cpp
           exception.cpp
           image.cpp
           logger.cpp
           math.cpp
           pixel.cpp
           spritesheet.cpp
           texture.cpp
           types.cpp
           window.cpp
)
