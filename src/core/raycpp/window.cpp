#include "core/raycpp/window.h"
#include "core/raycpp/raylibexception.h"

core::raycpp::Window::Window() {
    Init();
}

core::raycpp::Window::Window(const std::string& title) {
    Init(title);
}

core::raycpp::Window::Window(
    int                width,
    int                height,
    const std::string& title,
    unsigned int       flags
) {
    Init(width, height, title, flags);
}

core::raycpp::Window::~Window() {
    Close();
}

void core::raycpp::Window::Init(const std::string& title) {
    ::InitWindow(config::default_window_height, config::default_window_width, title.c_str());
    if (!::IsWindowReady()) {
        throw RaylibException("Failed to create Window");
    }
}

void core::raycpp::Window::Init(
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

bool core::raycpp::Window::ShouldClose() {
    return ::WindowShouldClose();
}

void core::raycpp::Window::SetExitKey(int key) {
    ::SetExitKey(key);
}

void core::raycpp::Window::Close() {
    if (::IsWindowReady()) {
        ::CloseWindow();
    }
}

bool core::raycpp::Window::IsCursorOnScreen() {
    return ::IsCursorOnScreen();
}

bool core::raycpp::Window::IsFullscreen() {
    return ::IsWindowFullscreen();
}

bool core::raycpp::Window::IsHidden() {
    return ::IsWindowHidden();
}

bool core::raycpp::Window::IsMinimized() {
    return ::IsWindowMinimized();
}

bool core::raycpp::Window::IsMaximized() {
    return ::IsWindowMaximized();
}

bool core::raycpp::Window::IsFocused() {
    return ::IsWindowFocused();
}

bool core::raycpp::Window::IsResized() {
    return ::IsWindowResized();
}

bool core::raycpp::Window::IsState(unsigned int flag) {
    return ::IsWindowState(flag);
}

void core::raycpp::Window::SetState(unsigned int flag) {
    ::SetWindowState(flag);
}

void core::raycpp::Window::ClearState(unsigned int flag) {
    ::ClearWindowState(flag);
}

void core::raycpp::Window::ClearBackground(const ::Color& color) {
    ::ClearBackground(color);
}

void core::raycpp::Window::ToggleFullscreen() {
    ::ToggleFullscreen();
}

void core::raycpp::Window::SetFullscreen(bool fullscreen) {
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

void core::raycpp::Window::ToggleBorderless() {
    ::ToggleBorderlessWindowed();
}

void core::raycpp::Window::Maximize() {
    ::MaximizeWindow();
}

void core::raycpp::Window::Minimize() {
    ::MinimizeWindow();
}

void core::raycpp::Window::Restore() {
    ::RestoreWindow();
}

void core::raycpp::Window::SetIcon(const ::Image& image) {
    ::SetWindowIcon(image);
}

void core::raycpp::Window::SetIcons(Image* images, int count) {
    ::SetWindowIcons(images, count);
}

void core::raycpp::Window::SetTitle(const std::string& title) {
    ::SetWindowTitle(title.c_str());
}

void core::raycpp::Window::SetPosition(int xpos, int ypos) {
    ::SetWindowPosition(xpos, ypos);
}

void core::raycpp::Window::SetPosition(const ::Vector2& position) {
    return SetPosition(
        static_cast<int>(position.x),
        static_cast<int>(position.y)
    );
}

void core::raycpp::Window::SetMonitor(int monitor) {
    ::SetWindowMonitor(monitor);
}

void core::raycpp::Window::SetMinSize(int width, int height) {
    ::SetWindowMinSize(width, height);
}

void core::raycpp::Window::SetMinSize(const ::Vector2& size) {
    ::SetWindowMinSize(static_cast<int>(size.x), static_cast<int>(size.y));
}

void core::raycpp::Window::SetSize(int width, int height) {
    ::SetWindowSize(width, height);
}

void core::raycpp::Window::SetOpacity(float opacity) {
    ::SetWindowOpacity(opacity);
}

void core::raycpp::Window::SetFocused() {
    ::SetWindowFocused();
}

void core::raycpp::Window::SetSize(const ::Vector2& size) {
    return SetSize(static_cast<int>(size.x), static_cast<int>(size.y));
}

core::raycpp::Vector2 core::raycpp::Window::GetSize() {
    return {static_cast<float>(GetWidth()), static_cast<float>(GetHeight())};
}

void* core::raycpp::Window::GetHandle() {
    return ::GetWindowHandle();
}

void core::raycpp::Window::BeginDrawing() {
    ::BeginDrawing();
}

void core::raycpp::Window::EndDrawing() {
    ::EndDrawing();
}

int core::raycpp::Window::GetWidth() {
    return ::GetScreenWidth();
}

int core::raycpp::Window::GetHeight() {
    return ::GetScreenHeight();
}

int core::raycpp::Window::GetRenderWidth() {
    return ::GetRenderWidth();
}

int core::raycpp::Window::GetRenderHeight() {
    return ::GetRenderHeight();
}

core::raycpp::Vector2 core::raycpp::Window::GetPosition() {
    return Vector2(::GetWindowPosition());
}

core::raycpp::Vector2 core::raycpp::Window::GetScaleDPI() {
    return Vector2(::GetWindowScaleDPI());
}

void core::raycpp::Window::SetClipboardText(const std::string& text) {
    ::SetClipboardText(text.c_str());
}

std::string core::raycpp::Window::GetClipboardText() {
    return ::GetClipboardText();
}

void core::raycpp::Window::SetTargetFPS(int fps) {
    ::SetTargetFPS(fps);
}

int core::raycpp::Window::GetFPS() {
    return ::GetFPS();
}

void core::raycpp::Window::DrawFPS(int posX, int posY) {
    ::DrawFPS(posX, posY);
}

float core::raycpp::Window::GetFrameTime() {
    return ::GetFrameTime();
}

double core::raycpp::Window::GetTime() {
    return ::GetTime();
}

bool core::raycpp::Window::IsReady() {
    return ::IsWindowReady();
}

void core::raycpp::Window::SetConfigFlags(unsigned int flags) {
    ::SetConfigFlags(flags);
}
