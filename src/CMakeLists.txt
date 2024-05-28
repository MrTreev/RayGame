set_target_properties(${PROJECT_NAME} PROPERTIES
	CMAKE_CXX_STANDARD 23
	CMAKE_CXX_STANDARD_REQUIRED True
	CXX_EXTENSIONS OFF
)
target_compile_options(${PROJECT_NAME} PRIVATE -Werror ${CMAKE_CXX_LINTER_FLAGS})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(core)
add_subdirectory(system)
add_subdirectory(world)

target_sources(${PROJECT_NAME}
	PUBLIC
	main.h
	main.cpp
)
