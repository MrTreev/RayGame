target_compile_definitions(${PROJECT_NAME} PUBLIC "RAYGAME_LOG_DEBUG")
target_sources(${PROJECT_NAME}
	PUBLIC
	condition.cpp
	condition.h
	exception.cpp
	exception.h
	logger.cpp
	logger.h
)
