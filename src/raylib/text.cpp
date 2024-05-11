#include "raylib/text.h"
#include <utility>

raylib::Text::Text(
    std::string    _text,
    float          _fontSize,
    const ::Color& _color,
    const ::Font&  _font,
    float          _spacing
)
    : text(std::move(_text))
    , fontSize(_fontSize)
    , color(_color)
    , font(_font)
    , spacing(_spacing) {}

raylib::Text::Text(
    const ::Font&  _font,
    std::string    _text,
    float          _fontSize,
    float          _spacing,
    const ::Color& _color
)
    : text(std::move(_text))
    , fontSize(_fontSize)
    , color(_color)
    , font(_font)
    , spacing(_spacing) {}

void raylib::Text::Draw(const ::Vector2& position) const {
    ::DrawTextEx(font, text.c_str(), position, fontSize, spacing, color);
}

void raylib::Text::Draw(int posX, int posY) const {
    ::DrawTextEx(
        font,
        text.c_str(),
        {static_cast<float>(posX), static_cast<float>(posY)},
        fontSize,
        spacing,
        color
    );
}

void raylib::Text::Draw(
    const ::Vector2& position,
    float            rotation,
    const ::Vector2& origin
) const {
    ::DrawTextPro(
        font,
        text.c_str(),
        position,
        origin,
        rotation,
        fontSize,
        spacing,
        color
    );
}

int raylib::Text::Measure() const {
    return ::MeasureText(text.c_str(), static_cast<int>(fontSize));
}

Vector2 raylib::Text::MeasureEx() const {
    return ::MeasureTextEx(font, text.c_str(), fontSize, spacing);
}

void raylib::Text::Draw(
    const std::string& text,
    const int          posX,
    const int          posY,
    const int          fontSize,
    const ::Color&     color
) {
    ::DrawText(text.c_str(), posX, posY, fontSize, color);
}

void raylib::Text::Draw(
    const std::string& text,
    const ::Vector2&   pos,
    const int          fontSize,
    const ::Color&     color
) {
    ::DrawText(
        text.c_str(),
        static_cast<int>(pos.x),
        static_cast<int>(pos.y),
        fontSize,
        color
    );
}

void raylib::Text::Draw(
    const ::Font&      font,
    const std::string& text,
    const ::Vector2&   position,
    const float        fontSize,
    const float        spacing,
    const ::Color&     color
) {
    ::DrawTextEx(font, text.c_str(), position, fontSize, spacing, color);
}

void raylib::Text::Draw(
    const ::Font&      font,
    const std::string& text,
    const ::Vector2&   position,
    const ::Vector2&   origin,
    const float        rotation,
    const float        fontSize,
    const float        spacing,
    const ::Color&     color
) {
    ::DrawTextPro(
        font,
        text.c_str(),
        position,
        origin,
        rotation,
        fontSize,
        spacing,
        color
    );
}

void raylib::Text::SetSpacing(float value) {
    spacing = value;
}

float raylib::Text::GetSpacing() const {
    return spacing;
}

void raylib::Text::SetColor(::Color value) {
    color = value;
}

::Color raylib::Text::GetColor() const {
    return color;
}

void raylib::Text::SetFont(::Font value) {
    font = value;
}

::Font raylib::Text::GetFont() const {
    return font;
}

void raylib::Text::SetFontSize(float value) {
    fontSize = value;
}

float raylib::Text::GetFontSize() const {
    return fontSize;
}

void raylib::Text::SetText(std ::string value) {
    text = std::move(value);
}

std ::string raylib::Text::GetText() const {
    return text;
}
