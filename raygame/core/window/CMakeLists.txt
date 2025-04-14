raygame_lib(RayGameCoreWindow)
add_library(RayGame::Core::Window ALIAS RayGameCoreWindow)
target_link_libraries(RayGameCoreWindow PUBLIC RayGame::Core::Base)
target_link_libraries(RayGameCoreWindow PUBLIC RayGame::Core::Drawing)
target_sources(
    RayGameCoreWindow
    PUBLIC window.h
    PRIVATE
        window.cpp
        detail/backends.h
        detail/backends.cpp
)

if($<NOT:RAYGAME_GUI_DISABLE_COCOA> AND RAYGAME_OS_IS_MACOS)
    target_sources(
        RayGameCoreWindow
        PRIVATE
            detail/cocoa.h
            detail/cocoa.cpp
    )
endif()

if($<NOT:RAYGAME_GUI_DISABLE_DWM> AND RAYGAME_OS_IS_WINDOWS)
    target_sources(
        RayGameCoreWindow
        PRIVATE
            detail/dwm.h
            detail/dwm.cpp
    )
endif()

if(RAYGAME_OS_IS_LINUX)
    if($<NOT:RAYGAME_GUI_DISABLE_WAYLAND>)
        target_sources(
            RayGameCoreWindow
            PRIVATE
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
        raygame_add_wayland_protocols(
            TARGET RayGameCoreWindow
            PROTOCOLS
                xdg-shell
        )
    endif()
    if($<NOT:RAYGAME_GUI_DISABLE_X11>)
        target_sources(
            RayGameCoreWindow
            PRIVATE
                detail/x11.h
                detail/x11.cpp
        )
    endif()
endif()

target_link_libraries(RayGameCore PUBLIC RayGame::Core::Window)
