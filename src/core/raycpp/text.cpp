#include "core/raycpp/text.h"
#include <utility>

core::raycpp::Text::Text(
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

core::raycpp::Text::Text(
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

void core::raycpp::Text::Draw(const ::Vector2& position) const {
    ::DrawTextEx(font, text.c_str(), position, fontSize, spacing, color);
}

void core::raycpp::Text::Draw(int posX, int posY) const {
    ::DrawTextEx(
        font,
        text.c_str(),
        {static_cast<float>(posX), static_cast<float>(posY)},
        fontSize,
        spacing,
        color
    );
}

void core::raycpp::Text::Draw(
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

int core::raycpp::Text::Measure() const {
    return ::MeasureText(text.c_str(), static_cast<int>(fontSize));
}

Vector2 core::raycpp::Text::MeasureEx() const {
    return ::MeasureTextEx(font, text.c_str(), fontSize, spacing);
}

void core::raycpp::Text::Draw(
    const std::string& text,
    const int          posX,
    const int          posY,
    const int          fontSize,
    const ::Color&     color
) {
    ::DrawText(text.c_str(), posX, posY, fontSize, color);
}

void core::raycpp::Text::Draw(
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

void core::raycpp::Text::Draw(
    const ::Font&      font,
    const std::string& text,
    const ::Vector2&   position,
    const float        fontSize,
    const float        spacing,
    const ::Color&     color
) {
    ::DrawTextEx(font, text.c_str(), position, fontSize, spacing, color);
}

void core::raycpp::Text::Draw(
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

void core::raycpp::Text::SetSpacing(float value) {
    spacing = value;
}

float core::raycpp::Text::GetSpacing() const {
    return spacing;
}

void core::raycpp::Text::SetColor(::Color value) {
    color = value;
}

::Color core::raycpp::Text::GetColor() const {
    return color;
}

void core::raycpp::Text::SetFont(::Font value) {
    font = value;
}

::Font core::raycpp::Text::GetFont() const {
    return font;
}

void core::raycpp::Text::SetFontSize(float value) {
    fontSize = value;
}

float core::raycpp::Text::GetFontSize() const {
    return fontSize;
}

void core::raycpp::Text::SetText(std ::string value) {
    text = std::move(value);
}

std ::string core::raycpp::Text::GetText() const {
    return text;
}
