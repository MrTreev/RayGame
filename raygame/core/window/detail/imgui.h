#pragma once
#include "raygame/core/window/window.h"

struct ImGuiIO;
struct GLFWwindow;

namespace core::window::detail {
class ImguiWindowImpl final: public WindowImpl {
public:
    explicit ImguiWindowImpl(
        Vec2<size_t> size  = DEFAULT_WINDOW_SIZE,
        std::string  title = DEFAULT_WINDOW_TITLE,
        WindowStyle  style = DEFAULT_WINDOW_STYLE
    );
    ImguiWindowImpl(const ImguiWindowImpl&)           = delete;
    ImguiWindowImpl operator=(const ImguiWindowImpl&) = delete;
    ImguiWindowImpl(ImguiWindowImpl&&)                = default;
    ImguiWindowImpl& operator=(ImguiWindowImpl&&)     = default;
    ~ImguiWindowImpl() final;

    void draw(const drawing::ImageView& image) final;

    void restyle(WindowStyle style) final;

    void render_frame() final;

    [[nodiscard]]
    bool next_frame() final;

    [[nodiscard]]
    bool should_close() const final;

private:
    void pre_frame();
    void post_frame();

    GLFWwindow* m_window{nullptr};
    ImGuiIO*    m_io{nullptr};
    int         m_window_flags{0};
};
} // namespace core::window::detail
