#include "raylib/rectangle.h"

raylib::Rectangle::Rectangle(const ::Rectangle& rect)
    : ::Rectangle{rect.x, rect.y, rect.width, rect.height} {}

raylib::Rectangle::Rectangle(
    float xpos,
    float ypos,
    float _width,
    float _height
)
    : ::Rectangle{xpos, ypos, _width, _height} {}

raylib::Rectangle::Rectangle(float xpos, float ypos, float _width)
    : ::Rectangle{xpos, ypos, _width, 0} {}

raylib::Rectangle::Rectangle(float xpos, float ypos)
    : ::Rectangle{xpos, ypos, 0, 0} {}

raylib::Rectangle::Rectangle(float xpos)
    : ::Rectangle{xpos, 0, 0, 0} {}

raylib::Rectangle::Rectangle()
    : ::Rectangle{0, 0, 0, 0} {}

raylib::Rectangle::Rectangle(::Vector2 position, ::Vector2 size)
    : ::Rectangle{position.x, position.y, size.x, size.y} {}

raylib::Rectangle::Rectangle(::Vector2 size)
    : ::Rectangle{0, 0, size.x, size.y} {}

raylib::Rectangle::Rectangle(::Vector4 rect)
    : ::Rectangle{rect.x, rect.y, rect.z, rect.w} {}

void raylib::Rectangle::set(const ::Rectangle& rect) {
    x      = rect.x;
    y      = rect.y;
    width  = rect.width;
    height = rect.height;
}

raylib::Rectangle& raylib::Rectangle::SetPosition(const ::Vector2& position) {
    return SetPosition(position.x, position.y);
}

raylib::Rectangle& raylib::Rectangle::SetPosition(float newX, float newY) {
    x = newX;
    y = newY;
    return *this;
}

raylib::Vector2 raylib::Rectangle::GetPosition() const {
    return {x, y};
}

raylib::Rectangle&
raylib::Rectangle::SetShapesTexture(const ::Texture2D& texture) {
    ::SetShapesTexture(texture, *this);
    return *this;
}

raylib::Rectangle& raylib::Rectangle::SetSize(const ::Vector2& size) {
    return SetSize(size.x, size.y);
}

raylib::Rectangle& raylib::Rectangle::SetSize(float newWidth, float newHeight) {
    width  = newWidth;
    height = newHeight;
    return *this;
}

raylib::Vector2 raylib::Rectangle::GetSize() const {
    return {width, height};
}

bool raylib::Rectangle::CheckCollision(::Vector2 center, float radius) const {
    return ::CheckCollisionCircleRec(center, radius, *this);
}

bool raylib::Rectangle::CheckCollision(::Vector2 point) const {
    return ::CheckCollisionPointRec(point, *this);
}

::Rectangle raylib::Rectangle::GetCollision(::Rectangle rec2) const {
    return ::GetCollisionRec(*this, rec2);
}

bool raylib::Rectangle::CheckCollision(::Rectangle rec2) const {
    return ::CheckCollisionRecs(*this, rec2);
}

void raylib::Rectangle::DrawRoundedLines(
    float   roundness,
    int     segments,
    float   lineThick,
    ::Color color
) const {
    ::DrawRectangleRoundedLines(*this, roundness, segments, lineThick, color);
}

void raylib::Rectangle::DrawRounded(
    float   roundness,
    int     segments,
    ::Color color
) const {
    ::DrawRectangleRounded(*this, roundness, segments, color);
}

void raylib::Rectangle::DrawLines(::Color color, float lineThick) const {
    ::DrawRectangleLinesEx(*this, lineThick, color);
}

void raylib::Rectangle::DrawLines(::Color color) const {
    ::DrawRectangleLines(
        static_cast<int>(x),
        static_cast<int>(y),
        static_cast<int>(width),
        static_cast<int>(height),
        color
    );
}

void raylib::Rectangle::DrawGradient(
    ::Color col1,
    ::Color col2,
    ::Color col3,
    ::Color col4
) const {
    ::DrawRectangleGradientEx(*this, col1, col2, col3, col4);
}

void raylib::Rectangle::DrawGradientH(::Color color1, ::Color color2) const {
    ::DrawRectangleGradientH(
        static_cast<int>(x),
        static_cast<int>(y),
        static_cast<int>(width),
        static_cast<int>(height),
        color1,
        color2
    );
}

void raylib::Rectangle::DrawGradientV(::Color color1, ::Color color2) const {
    ::DrawRectangleGradientV(
        static_cast<int>(x),
        static_cast<int>(y),
        static_cast<int>(width),
        static_cast<int>(height),
        color1,
        color2
    );
}

void raylib::Rectangle::Draw(::Vector2 origin, float rotation, ::Color color)
    const {
    ::DrawRectanglePro(*this, origin, rotation, color);
}

void raylib::Rectangle::Draw(::Color color) const {
    ::DrawRectangleRec(*this, color);
}

raylib::Rectangle::operator ::Vector4() const {
    return {x, y, width, height};
}

::Vector4 raylib::Rectangle::ToVector4() {
    return {x, y, width, height};
}

raylib::Rectangle& raylib::Rectangle::operator=(const ::Rectangle& rect) {
    set(rect);
    return *this;
}

void raylib::Rectangle::SetHeight(float value) {
    height = value;
}

float raylib::Rectangle::GetHeight() const {
    return height;
}

void raylib::Rectangle::SetWidth(float value) {
    width = value;
}

float raylib::Rectangle::GetWidth() const {
    return width;
}

void raylib::Rectangle::SetY(float value) {
    y = value;
}

float raylib::Rectangle::GetY() const {
    return y;
}

void raylib::Rectangle::SetX(float value) {
    x = value;
}

float raylib::Rectangle::GetX() const {
    return x;
}
