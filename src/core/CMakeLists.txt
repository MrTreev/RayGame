target_compile_definitions(${PROJECT_NAME} PUBLIC "RAYGAME_LOG_DEBUG")
target_sources(${PROJECT_NAME}
	PUBLIC
	utils/logger.h
	PRIVATE
	utils/logger.cpp
)
