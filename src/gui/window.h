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
    bool              _draw_fps = true;

public:
    explicit Window(
        const std::string& title,
        const int32_t&     width  = 640,
        const int32_t&     height = 360,
        const uint32_t&    flags  = 0
    )
        : _title(title) {
        if (flags != 0) {
            ::SetConfigFlags(flags);
        }
        ::InitWindow(width, height, title.c_str());
        if (!::IsWindowReady()) {
            utils::log::fatal("Failed to create Window");
            throw std::runtime_error("Failed to create Window");
        }
    }

    ~Window() {
        ::CloseWindow();
    }

    Window(const Window&)            = delete;
    Window(Window&&)                 = delete;
    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&)      = delete;

    void resize(int height, int width) {
        ::SetWindowSize(width, height);
    };

    void start_frame() const {
        ::BeginDrawing();
        clear_background();
    }

    void end_frame() const {
        if (_draw_fps) {
            DrawFPS(0, 0);
        }
        ::EndDrawing();
    }

private:
    static float delta_time() {
        return ::GetFrameTime();
    }

    static bool should_close() {
        return ::WindowShouldClose();
    }

    static void clear_background() {
        ::ClearBackground(gui::colour::black);
    };

    static void SetConfigFlags(config_t flags) {
        ::SetConfigFlags(flags.bits);
    }
};

} // namespace gui
