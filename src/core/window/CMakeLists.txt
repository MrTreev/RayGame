rg_core_lib(
    Window
    SOURCES
    window.cpp
    HEADERS
    window.h
    DEPENDS
    Base
    Math
    Drawing
)

if(RG_ENABLE_WAYLAND)
    include(RgWayland)
    target_sources(Window PUBLIC wayland.cpp detail/wayland.cpp)
    rg_target_client_protocol(TARGET Window PROTOCOLS wayland xdg-shell)
    target_link_libraries(Window PUBLIC xkbcommon)
endif()
if(RG_ENABLE_X11)
    target_sources(Window PUBLIC x11.cpp)
    target_link_libraries(Window PRIVATE X11)
endif()
