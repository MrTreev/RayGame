target_compile_definitions(${PROJECT_NAME} PUBLIC "RAYGAME_LOG_DEBUG")
target_sources(
    ${PROJECT_NAME}
    PUBLIC condition.h
           condition.cpp
		   config.h
		   config.cpp
           exception.cpp
           exception.h
           logger.cpp
           logger.h
		   spritesheet.cpp
		   spritesheet.h
           types.cpp
           types.h
)
add_subdirectory(gui)
