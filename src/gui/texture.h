#pragma once
#include "gui/colour.h"
#include "gui/rectangle.h"
#include "gui/vector.h"

namespace gui {

class Tex2d {
private:
    const ::Texture _texture;

public:
    explicit Tex2d(const std::string& fileName);
    ~Tex2d();
    Tex2d(const Tex2d&&)            = delete;
    Tex2d& operator=(const Tex2d&)  = delete;
    Tex2d(const Tex2d&)             = delete;
    Tex2d& operator=(const Tex2d&&) = delete;

    [[nodiscard]]
    int width() const {
        return _texture.width;
    }

    [[nodiscard]]
    int height() const {
        return _texture.height;
    }

    void Draw(int posX = 0, int posY = 0, gui::Colour tint = gui::colour::black)
        const;

    void Draw(
        gui::Rect    sourceRec,
        const Vec2d& position = {0, 0},
        gui::Colour  tint     = colour::black
    ) const;
};

} // namespace gui
