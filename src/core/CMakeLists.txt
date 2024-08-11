add_library(
    ${PROJECT_NAME}_core
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

add_subdirectory(windowimpl)

add_library(${PROJECT_NAME}::core ALIAS ${PROJECT_NAME}_core)
