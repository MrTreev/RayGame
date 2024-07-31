if(RAYGAME_GUI_USE_WAYLAND)
    add_subdirectory(wayland)
    target_sources(${PROJECT_NAME} PUBLIC wayland.cpp)
endif()
