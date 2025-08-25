#pragma once
#include "raygame/core/window/detail/backends.h" // IWYU pragma: keep
#include "raygame/core/window/window.h"
#include <map>

namespace core::window::detail {
class RaylibWindowImpl final: public WindowImpl {
    std::map<const void*, unsigned int> m_imgs;

public:
    RAYGAME_RETURN_RAYLIB
    RaylibWindowImpl(Vec2<size_t> size, std::string title, WindowStyle style);
    RaylibWindowImpl(const RaylibWindowImpl&)           = delete;
    RaylibWindowImpl operator=(const RaylibWindowImpl&) = delete;
    RaylibWindowImpl(RaylibWindowImpl&&)                = default;
    RaylibWindowImpl& operator=(RaylibWindowImpl&&)     = default;
    ~RaylibWindowImpl() final;

    void draw(const drawing::ImageView& image) final;

    void restyle(WindowStyle style) final;

    void render_frame() final;

    [[nodiscard]]
    bool next_frame() final;

    [[nodiscard]]
    bool should_close() const final;

private:
};
} // namespace core::window::detail
