if(RAYGAME_GUI_USE_WAYLAND)
    target_sources(${PROJECT_NAME} PUBLIC wayland.h wayland.cpp wayland/xdg-shell.h wayland/xdg-shell.c)
endif()
