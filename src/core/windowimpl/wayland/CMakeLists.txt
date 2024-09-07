target_sources(
    Core
    PUBLIC wayland_fwd.h util.h
    PRIVATE util.cpp window.cpp window_impl.cpp
)
