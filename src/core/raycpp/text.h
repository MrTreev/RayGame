#pragma once

#include "core/raycpp/raylib.h"
#include <string>

namespace core::raycpp {
class Text {
public:
    std::string text;
    float       fontSize;
    ::Color     color;
    ::Font      font;
    float       spacing;

    explicit Text(
        std::string    _text     = "",
        float          _fontSize = 10,
        const ::Color& _color    = WHITE,
        const ::Font&  _font     = ::GetFontDefault(),
        float          _spacing  = 0
    );
    explicit Text(
        const ::Font&  _font,
        std::string    _text     = "",
        float          _fontSize = 10,
        float          _spacing  = 0,
        const ::Color& _color    = WHITE
    );
    std ::string GetText() const;
    void         SetText(std ::string value);
    float        GetFontSize() const;
    void         SetFontSize(float value);
    ::Font       GetFont() const;
    void         SetFont(::Font value);
    ::Color      GetColor() const;
    void         SetColor(::Color value);
    float        GetSpacing() const;
    void         SetSpacing(float value);
    void         Draw(const ::Vector2& position) const;
    void         Draw(int posX, int posY) const;

    void Draw(
        const ::Vector2& position,
        float            rotation,
        const ::Vector2& origin = {0, 0}
    ) const;

    int         Measure() const;
    Vector2     MeasureEx() const;
    static void Draw(
        const std::string& text,
        int                posX,
        int                posY,
        int                fontSize,
        const ::Color&     color
    );
    static void Draw(
        const std::string& text,
        const ::Vector2&   pos,
        int                fontSize,
        const ::Color&     color
    );
    static void Draw(
        const ::Font&      font,
        const std::string& text,
        const ::Vector2&   position,
        float              fontSize,
        float              spacing,
        const ::Color&     color
    );
    static void Draw(
        const ::Font&      font,
        const std::string& text,
        const ::Vector2&   position,
        const ::Vector2&   origin,
        float              rotation,
        float              fontSize,
        float              spacing,
        const ::Color&     color
    );
};
} // namespace core::raycpp
