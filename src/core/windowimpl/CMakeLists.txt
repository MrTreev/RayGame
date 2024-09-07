if(RAYGAME_GUI_USE_WAYLAND)
    target_sources(
        Core
        PUBLIC wayland.h
        PRIVATE wayland.cpp
    )
    add_subdirectory(wayland)
    include(RgWayland)
    add_wayland(Core ${RAYGAME_ETC}/wayland-sources)
endif()
