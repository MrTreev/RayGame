#pragma once
#include "raygame/core/window/detail/backends.h"
#include "raygame/core/window/window.h"

#if defined(RAYGAME_GUI_BACKEND_IMGUI)
#endif

namespace core::window::detail {
class ImguiWindowImpl final: public WindowImpl {
    consteval bool enabled() { return config::EnabledBackends::imgui(); }

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
#if defined(RAYGAME_GUI_BACKEND_IMGUI)
#endif
};
} // namespace core::window::detail
