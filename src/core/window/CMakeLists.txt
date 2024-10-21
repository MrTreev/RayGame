raygame_core_lib(
    Window
    SOURCES
    window.cpp
    HEADERS
    window.h
    PUBLIC_DEPENDS
    Base
    Math
    Drawing
)

if(RAYGAME_ENABLE_WAYLAND)
    include(RgWayland)
    target_sources(Window PRIVATE wayland.h wayland.cpp detail/wayland.h detail/wayland.cpp)
    raygame_target_client_protocol(TARGET Window PROTOCOLS wayland xdg-shell)
    target_link_libraries(Window PUBLIC xkbcommon)
endif()
if(RAYGAME_ENABLE_X11)
    target_sources(Window PRIVATE x11.cpp x11.h)
    target_link_libraries(Window PRIVATE X11)
endif()
