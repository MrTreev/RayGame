if(RG_ENABLE_WAYLAND)
    include(RgWayland)
    target_sources(
        Core
        PUBLIC wayland.h
               wayland.cpp
               wayland/util.cpp
               wayland/window.cpp
               wayland/window_impl.cpp
               wayland/util.h
    )
    rg_target_client_protocol(TARGET Core PROTOCOLS wayland xdg-shell)
endif()
