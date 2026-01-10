raygame_lib(
    RayGameCoreBase
    HDRS assert.h
         concepts.h
         condition.h
         config.h
         exception.h
         logger.h
         macros.h
         matrix.h
         types.h
    SRCS assert.cpp
         concepts.cpp
         condition.cpp
         config.cpp
         exception.cpp
         logger.cpp
         macros.cpp
         matrix.cpp
         types.cpp
)
add_library(RayGame::Core::Base ALIAS RayGameCoreBase)

raygame_lib(
    RayGameCoreDrawing
    HDRS drawing/image.h drawing/pixel.h
    SRCS drawing/image.cpp drawing/pixel.cpp
    DEPS RayGame::Core::Base RayGame::Core::Math
)
add_library(RayGame::Core::Drawing ALIAS RayGameCoreDrawing)

raygame_lib(
    RayGameCoreMath
    HDRS math/arithmetic/safe_add.h
         math/arithmetic/safe_div.h
         math/arithmetic/safe_mult.h
         math/arithmetic/safe_sub.h
         math/arithmetic.h
         math/math.h
         math/mathrule.h
         math/numeric_cast.h
         math/random.h
         math/rect.h
         math/ring_average.h
         math/vector.h
    SRCS math/arithmetic/safe_add.cpp
         math/arithmetic/safe_div.cpp
         math/arithmetic/safe_mult.cpp
         math/arithmetic/safe_sub.cpp
         math/arithmetic.cpp
         math/math.cpp
         math/mathrule.cpp
         math/numeric_cast.cpp
         math/random.cpp
         math/rect.cpp
         math/ring_average.cpp
         math/vector.cpp
    DEPS RayGame::Core::Base
)
add_library(RayGame::Core::Math ALIAS RayGameCoreMath)

raygame_lib(
    RayGameCoreApplication
    HDRS application/application.h application/input.h
    SRCS application/application.cpp application/input.cpp application/detail/backends.h application/detail/backends.cpp
    DEPS RayGame::Core::Base RayGame::Core::Drawing
)
add_library(RayGame::Core::Application ALIAS RayGameCoreApplication)
if(RAYGAME_OS_IS_MACOS AND NOT RAYGAME_GUI_DISABLE_COCOA)
    target_sources(RayGameCoreApplication PRIVATE application/detail/cocoa.h application/detail/cocoa.cpp)
    target_link_libraries(RayGameCoreApplication PRIVATE)
endif()
if(RAYGAME_OS_IS_WINDOWS AND NOT RAYGAME_GUI_DISABLE_DWM)
    target_sources(RayGameCoreApplication PRIVATE application/detail/dwm.h application/detail/dwm.cpp)
    target_link_libraries(RayGameCoreApplication PRIVATE)
endif()
if(RAYGAME_OS_IS_LINUX)
    find_package(X11 REQUIRED)
    if(NOT RAYGAME_GUI_DISABLE_WAYLAND)
        raygame_add_wayland_protocols(RayGameApplicationWayland PROTOCOLS wayland xdg-shell)
        target_sources(
            RayGameCoreApplication
            PRIVATE application/detail/wayland/wl_keyboard.cpp
                    application/detail/wayland/wl_pointer.cpp
                    application/detail/wayland/wl_registry.cpp
                    application/detail/wayland/wl_seat.cpp
                    application/detail/wayland/wl_surface.cpp
                    application/detail/wayland/xdg_surface.cpp
                    application/detail/wayland/xdg_toplevel.cpp
                    application/detail/wayland/xdg_wm_base.cpp
                    application/detail/wayland.h
                    application/detail/wayland.cpp
        )
        target_link_libraries(RayGameCoreApplication PRIVATE RayGameApplicationWayland X11::xkbcommon xkbcommon)
    endif()
endif()

raygame_lib(
    RayGameCoreIo
    HDRS io/file.h
    SRCS io/file.cpp
)
add_library(RayGame::Core::Io ALIAS RayGameCoreIo)

raygame_lib(
    RayGameCoreSerialisation
    HDRS serialisation/serialisation.h
    SRCS serialisation/serialisation.cpp
    DEPS RayGame::Core::Base
)
target_link_libraries(RayGameCoreSerialisation PUBLIC RayGame::External::ZppBits)
add_library(RayGame::Core::Serialisation ALIAS RayGameCoreSerialisation)

add_library(RayGameCore)
target_link_libraries(
    RayGameCore PUBLIC RayGame::Core::Base RayGame::Core::Io RayGame::Core::Math RayGame::Core::Application
                       RayGame::Core::Serialisation
)
target_link_libraries(RayGameCore PUBLIC RayGame::External::ZppBits)
add_library(RayGame::Core ALIAS RayGameCore)
