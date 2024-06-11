#include "core/gui/window.h" // IWYU pragma: keep
#include "core/backend.h"
#include "core/condition.h"
#include "core/math.h"
#include <string_view>

namespace {

//! Default window width
#if defined(RAYGAME_GAME_WIDTH)
constexpr std::size_t window_width = RAYGAME_GAME_WIDTH;
#else
constexpr std::size_t window_width = 640;
#endif

//! Default window height
#if defined(RAYGAME_GAME_HEIGHT)
constexpr std::size_t window_height = RAYGAME_GAME_HEIGHT;
#else
constexpr std::size_t window_height = 480;
#endif

//! Default frame rate
#if defined(RAYGAME_GAME_FPS)
constexpr std::size_t frame_rate = RAYGAME_GAME_FPS;
#else
constexpr std::size_t frame_rate = 60;
#endif

//! Game name
#if defined(RAYGAME_GAME_NAME)
constexpr std::string_view game_name = RAYGAME_GAME_NAME;
#else
constexpr std::string_view game_name = "RayGame";
#endif

} // namespace

#if defined(RAYGAME_BACKEND_RAYLIB)

constexpr int rl_win_flags = static_cast<int>(
    static_cast<unsigned int>(FLAG_WINDOW_RESIZABLE)
    | static_cast<unsigned int>(FLAG_WINDOW_ALWAYS_RUN)
    | static_cast<unsigned int>(FLAG_VSYNC_HINT)
);
constexpr int rl_wfs_flags = static_cast<int>(
    static_cast<unsigned int>(FLAG_WINDOW_UNDECORATED)
    | static_cast<unsigned int>(FLAG_WINDOW_ALWAYS_RUN)
    | static_cast<unsigned int>(FLAG_WINDOW_MAXIMIZED)
    | static_cast<unsigned int>(FLAG_BORDERLESS_WINDOWED_MODE)
    | static_cast<unsigned int>(FLAG_VSYNC_HINT)
);
constexpr int rl_fsn_flags = static_cast<int>(
    static_cast<unsigned int>(FLAG_FULLSCREEN_MODE)
    | static_cast<unsigned int>(FLAG_WINDOW_UNDECORATED)
    | static_cast<unsigned int>(FLAG_VSYNC_HINT)
);

core::gui::Window::Window()
    : core::gui::Window(window_width, window_height) {}

core::gui::Window::Window(const size_t& width, const size_t& height)
    : core::gui::Window(width, height, game_name.data()) {}

core::gui::Window::Window(
    const size_t&      width,
    const size_t&      height,
    const std::string& name
)
    : core::gui::Window(width, height, name, WindowStyle::Windowed) {}

core::gui::Window::Window(
    const size_t&      width,
    const size_t&      height,
    const std::string& name,
    const WindowStyle& style
) {
    core::condition::pre_condition(
        ((width > 0) && (height > 0)),
        "Width and height must be greater than zero"
    );
    core::condition::pre_condition(
        (width <= std::numeric_limits<int>::max()),
        "Width is too large for Raylib int type"
    );
    core::condition::pre_condition(
        (height <= std::numeric_limits<int>::max()),
        "Height is too large for Raylib int type"
    );

    ::InitWindow(
        static_cast<int>(width),
        static_cast<int>(height),
        name.c_str()
    );
    core::condition::post_condition(
        ::IsWindowReady(),
        "Failed to create Window"
    );
    set_style(style);
    set_framerate(frame_rate);
}

core::gui::Window::~Window() {
    if (::IsWindowReady()) {
        ::CloseWindow();
    }
}

bool core::gui::Window::should_close() {
    return ::WindowShouldClose();
}

void core::gui::Window::clear() {
    ::BeginDrawing();
    ::ClearBackground(BLACK);
}

void core::gui::Window::display() {
    if (_draw_fps) {
        ::DrawFPS(10, 10);
    }
    ::EndDrawing();
}

void core::gui::Window::draw_fps(bool enable) {
    _draw_fps = enable;
}

bool core::gui::Window::is_windowed() {
    return ::IsWindowState(rl_win_flags);
}

bool core::gui::Window::is_windowed_fullscreen() {
    return ::IsWindowState(rl_wfs_flags);
}

bool core::gui::Window::is_fullscreen() {
    return ::IsWindowFullscreen();
}

void core::gui::Window::set_style(core::gui::WindowStyle style) {
    switch (style) {
    case WindowStyle::Windowed:
        ::SetConfigFlags(rl_win_flags);
        set_fullscreen(false);
        break;
    case WindowStyle::WindowedFullscreen:
        ::SetConfigFlags(rl_wfs_flags);
        set_fullscreen(false);
        break;
    case WindowStyle::Fullscreen:
        ::SetConfigFlags(rl_fsn_flags);
        set_fullscreen(true);
        break;
    }
}

void core::gui::Window::set_framerate(const size_t& framerate) {
    core::condition::pre_condition(
        (framerate <= std::numeric_limits<int>::max()),
        "framerate is too large for Raylib int type"
    );
    ::SetTargetFPS(static_cast<int>(framerate));
}

void core::gui::Window::set_size(const size_t& width, const size_t& height) {
    core::condition::pre_condition(
        ((width > 0) && (height > 0)),
        "Cannot have a width or height of 0"
    );
    core::condition::pre_condition(
        (width <= std::numeric_limits<int>::max()),
        "width is too large for Raylib int type"
    );
    core::condition::pre_condition(
        (height <= std::numeric_limits<int>::max()),
        "height is too large for Raylib int type"
    );
    ::SetWindowSize(static_cast<int>(width), static_cast<int>(height));
}

void core::gui::Window::set_fullscreen(const bool& enable) {
    if (enable) {
        if (!is_fullscreen()) {
            toggle_fullscreen();
        }
    } else {
        if (is_fullscreen()) {
            toggle_fullscreen();
        }
    };
}

void core::gui::Window::toggle_fullscreen() {
    ::ToggleFullscreen();
}

core::gui::WindowStyle core::gui::Window::get_style() {
    if (is_windowed()) {
        return WindowStyle::Windowed;
    }
    if (is_windowed_fullscreen()) {
        return WindowStyle::WindowedFullscreen;
    }
    if (is_fullscreen()) {
        return WindowStyle::Fullscreen;
    }
    core::condition::check_condition(false, "Invalid style");
    return WindowStyle::Windowed; // for static analysis
};

#elif defined(RAYGAME_BACKEND_VULKAN)

namespace {
std::shared_ptr<GLFWwindow> window; // NOLINT
}

core::gui::Window::Window()
    : core::gui::Window(window_width, window_height) {}

core::gui::Window::Window(const size_t& width, const size_t& height)
    : core::gui::Window(width, height, game_name.data()) {}

core::gui::Window::Window(
    const size_t&      width,
    const size_t&      height,
    const std::string& name
)
    : core::gui::Window(width, height, name, WindowStyle::Windowed) {}

core::gui::Window::Window(
    const size_t&      width,
    const size_t&      height,
    const std::string& name,
    const WindowStyle& style
) {
    core::condition::pre_condition(
        ((width > 0) && (height > 0)),
        "Width and height must be greater than zero"
    );
    core::condition::pre_condition(
        (width <= std::numeric_limits<int>::max()),
        "Width is too large for GLFW int type"
    );
    core::condition::pre_condition(
        (height <= std::numeric_limits<int>::max()),
        "Height is too large for GLFW int type"
    );
    core::condition::check_condition(
        glfwInit() != 0,
        "GLFW Initialisation failed"
    );

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(
        window_width,
        window_height,
        name.data(),
        nullptr,
        nullptr
    ));
    condition::check_condition(window != nullptr, "Window creation failed");
}

core::gui::Window::~Window() {
    glfwDestroyWindow(window.get());
    window.reset();
    glfwTerminate();
}

#elif defined(RAYGAME_BACKEND_SDL)

// These need to be raw pointers because of incomplete types
static struct window {
    SDL_Window*  window{nullptr};
    SDL_Surface* surface{nullptr};
} sdl_impl; //NOLINT

core::gui::Window::Window()
    : core::gui::Window(window_width, window_height) {}

core::gui::Window::Window(const size_t& width, const size_t& height)
    : core::gui::Window(width, height, game_name.data()) {}

core::gui::Window::Window(
    const size_t&      width,
    const size_t&      height,
    const std::string& name,
    const WindowStyle& style
) {
    SDL_InitFlags sdl_flags =
        (SDL_INIT_EVENTS | SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    SDL_WindowFlags window_flags{0};
    switch (style) {
    case WindowStyle::Windowed:
        window_flags =
            (window_flags | SDL_WINDOW_RESIZABLE | SDL_WINDOW_INPUT_FOCUS
             | SDL_WINDOW_MOUSE_FOCUS);
        break;
    case WindowStyle::WindowedFullscreen:
        window_flags =
            (window_flags | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE
             | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_INPUT_FOCUS
             | SDL_WINDOW_MOUSE_FOCUS);
        break;
    case WindowStyle::Fullscreen:
        window_flags =
            (window_flags | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_INPUT_FOCUS
             | SDL_WINDOW_MOUSE_FOCUS);
        break;
    }
    const int& init_result = SDL_Init(sdl_flags);
    condition::check_condition(init_result == 0, "SDL Initialisation failed");
    sdl_impl.window = SDL_CreateWindow(
        name.c_str(),
        core::math::numeric_cast<int>(width),
        core::math::numeric_cast<int>(height),
        window_flags
    );
    sdl_impl.surface = SDL_GetWindowSurface(sdl_impl.window);
    size_t fps       = frame_rate;
    fps++;
    std::ignore = fps;
}

core::gui::Window::~Window() {
    SDL_DestroyWindow(sdl_impl.window);
    sdl_impl.window = nullptr;
    SDL_Quit();
}

#endif
