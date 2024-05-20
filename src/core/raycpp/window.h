#pragma once

#include "core/raycpp/raylib.h"
#include "core/raycpp/vector2.h"
#include <string>
#include "config.h"

namespace core::raycpp {
class Window {
public:
    explicit Window(const std::string& title = config::game_name.data());
    explicit Window(
        int                width  = config::default_window_width,
        int                height = config::default_window_height,
        const std::string& title  = config::game_name.data(),
        unsigned int       flags  = 0
    );

    Window();
    Window(const Window&)            = delete;
    Window(Window&&)                 = delete;
    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&)      = delete;
    ~Window();

    static void Init(
        int                width  = config::default_window_height,
        int                height = config::default_window_width,
        const std::string& title  = "RayGame",
        unsigned int       flags  = 0
    );
    static void Init(const std::string& title);

    static void BeginDrawing();
    static void Close();
    static void EndDrawing();
    static void Maximize();
    static void Minimize();
    static void Restore();
    static void SetFocused();
    static void ToggleBorderless();
    static void ToggleFullscreen();

    static void ClearBackground(const ::Color& color = BLACK);
    static void ClearState(unsigned int flag);
    static void DrawFPS(int posX = 10, int posY = 10);
    static void SetClipboardText(const std::string& text);
    static void SetConfigFlags(unsigned int flags);
    static void SetExitKey(int key);
    static void SetFullscreen(bool fullscreen);
    static void SetIcon(const ::Image& image);
    static void SetIcons(Image* images, int count);
    static void SetMinSize(const ::Vector2& size);
    static void SetMinSize(int width, int height);
    static void SetMonitor(int monitor);
    static void SetOpacity(float opacity);
    static void SetPosition(const ::Vector2& position);
    static void SetPosition(int xpos, int ypos);
    static void SetSize(const ::Vector2& size);
    static void SetSize(int width, int height);
    static void SetState(unsigned int flag);
    static void SetTargetFPS(int fps);
    static void SetTitle(const std::string& title);

    static bool IsState(unsigned int flag);

    static bool   ShouldClose();
    static bool   IsCursorOnScreen();
    static bool   IsFullscreen();
    static bool   IsHidden();
    static bool   IsMinimized();
    static bool   IsMaximized();
    static bool   IsFocused();
    static bool   IsResized();
    static int    GetWidth();
    static int    GetHeight();
    static int    GetRenderWidth();
    static int    GetRenderHeight();
    static int    GetFPS();
    static float  GetFrameTime();
    static double GetTime();
    static bool   IsReady();

    static void*           GetHandle();
    static std::string     GetClipboardText();
    static core::raycpp::Vector2 GetSize();
    static core::raycpp::Vector2 GetPosition();
    static core::raycpp::Vector2 GetScaleDPI();
};
} // namespace core::raycpp
