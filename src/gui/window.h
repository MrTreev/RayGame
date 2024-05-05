#pragma once
#include "gui/colour.h"
#include "utils/logger.h"
#include <cstdint>
#include <string>

namespace gui {

using config_t = union {
    struct ConfigField {
        uint32_t                         : 1;
        uint32_t fullscreen              : 1;
        uint32_t window_resizable        : 1;
        uint32_t window_undecorated      : 1;
        uint32_t window_transparent      : 1;
        uint32_t msaa_4x_hint            : 1;
        uint32_t vsync_hint              : 1;
        uint32_t window_hidden           : 1;
        uint32_t window_always_run       : 1;
        uint32_t window_minimised        : 1;
        uint32_t window_maximised        : 1;
        uint32_t window_unfocused        : 1;
        uint32_t window_topmost          : 1;
        uint32_t window_highdpi          : 1;
        uint32_t window_mouse_passthrough: 1;
        uint32_t borderless_windowed_mode: 1;
        uint32_t interlaced              : 1;
    };

    unsigned int bits;
};

// clang-format on

class Window {
private:
    const std::string _title;

public:
    explicit Window(
        const std::string& title,
        const int32_t&     width  = 640,
        const int32_t&     height = 360,
        const uint32_t&    flags  = 0
    );
    ~Window();

    Window(const Window&)            = delete;
    Window(Window&&)                 = delete;
    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&)      = delete;

    static void resize(int height, int width);
    static void start_frame();
    static void end_frame();
    static bool should_close();
    static bool next();

private:
    static float delta_time();
    static void  clear_background();
    static void  SetConfigFlags(config_t flags);
};

} // namespace gui
