target_compile_definitions(${PROJECT_NAME} PUBLIC "RAYGAME_LOG_DEBUG")
target_sources(${PROJECT_NAME}
	PUBLIC
	conditions.h
	conditions.cpp
	logger.h
	logger.cpp
)
