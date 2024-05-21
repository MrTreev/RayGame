target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(core)
add_subdirectory(system)
add_subdirectory(world)

target_sources(${PROJECT_NAME}
	PUBLIC
	config.h
	config.cpp
	main.cpp
)
