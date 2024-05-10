#include "raylib/window.h"
#include "raylib/raylibexception.h"

raylib::Window::Window() {
    Init();
}

raylib::Window::Window(const std::string& title) {
    Init(title);
}

raylib::Window::Window(
    int                width,
    int                height,
    const std::string& title,
    unsigned int       flags
) {
    Init(width, height, title, flags);
}

raylib::Window::~Window() {
    Close();
}

void raylib::Window::Init(const std::string& title) {
    ::InitWindow(config::default_window_height, config::default_window_width, title.c_str());
    if (!::IsWindowReady()) {
        throw RaylibException("Failed to create Window");
    }
}

void raylib::Window::Init(
    int                width,
    int                height,
    const std::string& title,
    unsigned int       flags
) {
    if (flags != 0) {
        ::SetConfigFlags(flags);
    }
    ::InitWindow(width, height, title.c_str());
    if (!::IsWindowReady()) {
        throw RaylibException("Failed to create Window");
    }
}

bool raylib::Window::ShouldClose() {
    return ::WindowShouldClose();
}

void raylib::Window::SetExitKey(int key) {
    ::SetExitKey(key);
}

void raylib::Window::Close() {
    if (::IsWindowReady()) {
        ::CloseWindow();
    }
}

bool raylib::Window::IsCursorOnScreen() {
    return ::IsCursorOnScreen();
}

bool raylib::Window::IsFullscreen() {
    return ::IsWindowFullscreen();
}

bool raylib::Window::IsHidden() {
    return ::IsWindowHidden();
}

bool raylib::Window::IsMinimized() {
    return ::IsWindowMinimized();
}

bool raylib::Window::IsMaximized() {
    return ::IsWindowMaximized();
}

bool raylib::Window::IsFocused() {
    return ::IsWindowFocused();
}

bool raylib::Window::IsResized() {
    return ::IsWindowResized();
}

bool raylib::Window::IsState(unsigned int flag) {
    return ::IsWindowState(flag);
}

void raylib::Window::SetState(unsigned int flag) {
    ::SetWindowState(flag);
}

void raylib::Window::ClearState(unsigned int flag) {
    ::ClearWindowState(flag);
}

void raylib::Window::ClearBackground(const ::Color& color) {
    ::ClearBackground(color);
}

void raylib::Window::ToggleFullscreen() {
    ::ToggleFullscreen();
}

void raylib::Window::SetFullscreen(bool fullscreen) {
    if (fullscreen) {
        if (!IsFullscreen()) {
            ToggleFullscreen();
        }
    } else {
        if (IsFullscreen()) {
            ToggleFullscreen();
        }
    }
}

void raylib::Window::ToggleBorderless() {
    ::ToggleBorderlessWindowed();
}

void raylib::Window::Maximize() {
    ::MaximizeWindow();
}

void raylib::Window::Minimize() {
    ::MinimizeWindow();
}

void raylib::Window::Restore() {
    ::RestoreWindow();
}

void raylib::Window::SetIcon(const ::Image& image) {
    ::SetWindowIcon(image);
}

void raylib::Window::SetIcons(Image* images, int count) {
    ::SetWindowIcons(images, count);
}

void raylib::Window::SetTitle(const std::string& title) {
    ::SetWindowTitle(title.c_str());
}

void raylib::Window::SetPosition(int xpos, int ypos) {
    ::SetWindowPosition(xpos, ypos);
}

void raylib::Window::SetPosition(const ::Vector2& position) {
    return SetPosition(
        static_cast<int>(position.x),
        static_cast<int>(position.y)
    );
}

void raylib::Window::SetMonitor(int monitor) {
    ::SetWindowMonitor(monitor);
}

void raylib::Window::SetMinSize(int width, int height) {
    ::SetWindowMinSize(width, height);
}

void raylib::Window::SetMinSize(const ::Vector2& size) {
    ::SetWindowMinSize(static_cast<int>(size.x), static_cast<int>(size.y));
}

void raylib::Window::SetSize(int width, int height) {
    ::SetWindowSize(width, height);
}

void raylib::Window::SetOpacity(float opacity) {
    ::SetWindowOpacity(opacity);
}

void raylib::Window::SetFocused() {
    ::SetWindowFocused();
}

void raylib::Window::SetSize(const ::Vector2& size) {
    return SetSize(static_cast<int>(size.x), static_cast<int>(size.y));
}

raylib::Vector2 raylib::Window::GetSize() {
    return {static_cast<float>(GetWidth()), static_cast<float>(GetHeight())};
}

void* raylib::Window::GetHandle() {
    return ::GetWindowHandle();
}

void raylib::Window::BeginDrawing() {
    ::BeginDrawing();
}

void raylib::Window::EndDrawing() {
    ::EndDrawing();
}

int raylib::Window::GetWidth() {
    return ::GetScreenWidth();
}

int raylib::Window::GetHeight() {
    return ::GetScreenHeight();
}

int raylib::Window::GetRenderWidth() {
    return ::GetRenderWidth();
}

int raylib::Window::GetRenderHeight() {
    return ::GetRenderHeight();
}

raylib::Vector2 raylib::Window::GetPosition() {
    return ::GetWindowPosition();
}

raylib::Vector2 raylib::Window::GetScaleDPI() {
    return ::GetWindowScaleDPI();
}

void raylib::Window::SetClipboardText(const std::string& text) {
    ::SetClipboardText(text.c_str());
}

std::string raylib::Window::GetClipboardText() {
    return ::GetClipboardText();
}

void raylib::Window::SetTargetFPS(int fps) {
    ::SetTargetFPS(fps);
}

int raylib::Window::GetFPS() {
    return ::GetFPS();
}

void raylib::Window::DrawFPS(int posX, int posY) {
    ::DrawFPS(posX, posY);
}

float raylib::Window::GetFrameTime() {
    return ::GetFrameTime();
}

double raylib::Window::GetTime() {
    return ::GetTime();
}

bool raylib::Window::IsReady() {
    return ::IsWindowReady();
}

void raylib::Window::SetConfigFlags(unsigned int flags) {
    ::SetConfigFlags(flags);
}
