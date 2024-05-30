
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    target_compile_definitions(${PROJECT_NAME} PUBLIC "RAYGAME_LOG_DEBUG")
    target_compile_definitions(${PROJECT_NAME} PUBLIC "RAYGAME_LOG_LOCATION")
    target_compile_options(${PROJECT_NAME} PUBLIC -Og)
    target_compile_options(${PROJECT_NAME} PUBLIC -ggdb)
else()
    target_compile_definitions(${PROJECT_NAME} PUBLIC "RAYGAME_LOG_INFO")
    target_compile_options(${PROJECT_NAME} PUBLIC -Ofast)
endif()

if(RAYGAME_IGNORE_CONDITIONS)
    target_compile_definitions(${PROJECT_NAME} PUBLIC "RAYGAME_IGNORE_CONDITIONS")
endif()

if(ENABLE_LTO)
    set_target_properties(${PROJECT_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

if(ENABLE_MSAN AND ENABLE_ASAN)
    message(WARNING "Compiling with both AddressSanitizer and MemorySanitizer is not recommended")
endif()

if(ENABLE_ASAN)
    target_compile_options(${PROJECT_NAME} PUBLIC -fno-omit-frame-pointer)
    target_compile_options(${PROJECT_NAME} PUBLIC -fsanitize=address)
endif()

if(ENABLE_MSAN)
    target_compile_options(${PROJECT_NAME} PUBLIC -fno-omit-frame-pointer)
    target_compile_options(${PROJECT_NAME} PUBLIC -fsanitize=memory)
endif()

if(ENABLE_UBSAN)
    target_compile_options(${PROJECT_NAME} PUBLIC -fno-omit-frame-pointer)
    target_compile_options(${PROJECT_NAME} PUBLIC -fsanitize=undefined)
endif()


