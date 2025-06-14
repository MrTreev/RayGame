raygame_lib(
    RayGameCoreWindow
    HDRS window.h
    SRCS window.cpp
        detail/backends.h
        detail/backends.cpp
    DEPS RayGame::Core::Base
         RayGame::Core::Drawing
)
add_library(RayGame::Core::Window ALIAS RayGameCoreWindow)

if(RAYGAME_OS_IS_MACOS AND NOT RAYGAME_GUI_DISABLE_COCOA)
    target_sources(RayGameCoreWindow PRIVATE detail/cocoa.h detail/cocoa.cpp)
    target_link_libraries(RayGameCoreWindow PRIVATE )
endif()
if(RAYGAME_OS_IS_WINDOWS AND NOT RAYGAME_GUI_DISABLE_DWM)
    target_sources(RayGameCoreWindow PRIVATE detail/dwm.h detail/dwm.cpp)
    target_link_libraries(RayGameCoreWindow PRIVATE )
endif()
if(RAYGAME_OS_IS_LINUX)
    find_package(X11 REQUIRED)
    if(NOT RAYGAME_GUI_DISABLE_WAYLAND)
        raygame_add_wayland_protocols(RayGameWindowWayland PROTOCOLS wayland xdg-shell)
        target_sources(RayGameCoreWindow PRIVATE
                detail/wayland/wayland_fwd.h
                detail/wayland/wl_keyboard.cpp
                detail/wayland/wl_pointer.cpp
                detail/wayland/wl_registry.cpp
                detail/wayland/wl_seat.cpp
                detail/wayland/wl_surface.cpp
                detail/wayland/xdg_surface.cpp
                detail/wayland/xdg_toplevel.cpp
                detail/wayland/xdg_wm_base.cpp
                detail/wayland.h
                detail/wayland.cpp
        )
        target_link_libraries(RayGameCoreWindow PRIVATE RayGameWindowWayland X11::xkbcommon xkbcommon)
    endif()
    if(NOT RAYGAME_GUI_DISABLE_X11)
        target_sources(RayGameCoreWindow PRIVATE detail/x11.h detail/x11.cpp)
        target_link_libraries(RayGameCoreWindow PRIVATE X11::X11 X11::xkbcommon xkbcommon)
    endif()
endif()
