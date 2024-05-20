#pragma once

#include "core/raycpp/raylib.h"
#include "core/raycpp/vector2.h"

namespace core::raycpp {
/**
 * Rectangle type
 */
class Rectangle: public ::Rectangle {
public:
    explicit Rectangle(const ::Rectangle& rect);
    Rectangle(float xpos, float ypos, float _width, float _height);
    Rectangle(float xpos, float ypos, float _width);
    Rectangle(float xpos, float ypos);
    explicit Rectangle(float xpos);
    Rectangle();
    Rectangle(::Vector2 position, ::Vector2 size);
    explicit Rectangle(::Vector2 size);
    explicit Rectangle(::Vector4 rect);
    float      GetX() const;
    void       SetX(float value);
    float      GetY() const;
    void       SetY(float value);
    float      GetWidth() const;
    void       SetWidth(float value);
    float      GetHeight() const;
    void       SetHeight(float value);
    Rectangle& operator=(const ::Rectangle& rect);
    ::Vector4  ToVector4();
    explicit   operator ::Vector4() const;
    void       Draw(::Color color) const;
    void       Draw(::Vector2 origin, float rotation, ::Color color) const;
    void       DrawGradientV(::Color color1, ::Color color2) const;
    void       DrawGradientH(::Color color1, ::Color color2) const;
    void
    DrawGradient(::Color col1, ::Color col2, ::Color col3, ::Color col4) const;
    void DrawLines(::Color color) const;
    void DrawLines(::Color color, float lineThick) const;
    void DrawRounded(float roundness, int segments, ::Color color) const;

    void DrawRoundedLines(
        float   roundness,
        int     segments,
        float   lineThick,
        ::Color color
    ) const;

    bool        CheckCollision(::Rectangle rec2) const;
    ::Rectangle GetCollision(::Rectangle rec2) const;
    bool        CheckCollision(::Vector2 point) const;
    bool        CheckCollision(::Vector2 center, float radius) const;
    Vector2     GetSize() const;
    Rectangle&  SetSize(float newWidth, float newHeight);
    Rectangle&  SetSize(const ::Vector2& size);
    Rectangle&  SetShapesTexture(const ::Texture2D& texture);
    Vector2     GetPosition() const;
    Rectangle&  SetPosition(float newX, float newY);
    Rectangle&  SetPosition(const ::Vector2& position);

protected:
    void set(const ::Rectangle& rect);
};
} // namespace core::raycpp
