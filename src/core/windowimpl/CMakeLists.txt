if(RAYGAME_GUI_USE_WAYLAND)
    target_sources(${PROJECT_NAME} PUBLIC wayland.cpp)
endif()
