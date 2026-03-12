if(NOT RAYGAME_BUILD_GAMES)
    return()
endif()

add_subdirectory(generated_image)
add_subdirectory(init_only)
add_subdirectory(image)
