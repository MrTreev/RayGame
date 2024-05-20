#include "core/raycpp/rectangle.h"

core::raycpp::Rectangle::Rectangle(const ::Rectangle& rect)
    : ::Rectangle{rect.x, rect.y, rect.width, rect.height} {}

core::raycpp::Rectangle::Rectangle(
    float xpos,
    float ypos,
    float _width,
    float _height
)
    : ::Rectangle{xpos, ypos, _width, _height} {}

core::raycpp::Rectangle::Rectangle(float xpos, float ypos, float _width)
    : ::Rectangle{xpos, ypos, _width, 0} {}

core::raycpp::Rectangle::Rectangle(float xpos, float ypos)
    : ::Rectangle{xpos, ypos, 0, 0} {}

core::raycpp::Rectangle::Rectangle(float xpos)
    : ::Rectangle{xpos, 0, 0, 0} {}

core::raycpp::Rectangle::Rectangle()
    : ::Rectangle{0, 0, 0, 0} {}

core::raycpp::Rectangle::Rectangle(::Vector2 position, ::Vector2 size)
    : ::Rectangle{position.x, position.y, size.x, size.y} {}

core::raycpp::Rectangle::Rectangle(::Vector2 size)
    : ::Rectangle{0, 0, size.x, size.y} {}

core::raycpp::Rectangle::Rectangle(::Vector4 rect)
    : ::Rectangle{rect.x, rect.y, rect.z, rect.w} {}

void core::raycpp::Rectangle::set(const ::Rectangle& rect) {
    x      = rect.x;
    y      = rect.y;
    width  = rect.width;
    height = rect.height;
}

core::raycpp::Rectangle& core::raycpp::Rectangle::SetPosition(const ::Vector2& position) {
    return SetPosition(position.x, position.y);
}

core::raycpp::Rectangle& core::raycpp::Rectangle::SetPosition(float newX, float newY) {
    x = newX;
    y = newY;
    return *this;
}

core::raycpp::Vector2 core::raycpp::Rectangle::GetPosition() const {
    return {x, y};
}

core::raycpp::Rectangle&
core::raycpp::Rectangle::SetShapesTexture(const ::Texture2D& texture) {
    ::SetShapesTexture(texture, *this);
    return *this;
}

core::raycpp::Rectangle& core::raycpp::Rectangle::SetSize(const ::Vector2& size) {
    return SetSize(size.x, size.y);
}

core::raycpp::Rectangle& core::raycpp::Rectangle::SetSize(float newWidth, float newHeight) {
    width  = newWidth;
    height = newHeight;
    return *this;
}

core::raycpp::Vector2 core::raycpp::Rectangle::GetSize() const {
    return {width, height};
}

bool core::raycpp::Rectangle::CheckCollision(::Vector2 center, float radius) const {
    return ::CheckCollisionCircleRec(center, radius, *this);
}

bool core::raycpp::Rectangle::CheckCollision(::Vector2 point) const {
    return ::CheckCollisionPointRec(point, *this);
}

::Rectangle core::raycpp::Rectangle::GetCollision(::Rectangle rec2) const {
    return ::GetCollisionRec(*this, rec2);
}

bool core::raycpp::Rectangle::CheckCollision(::Rectangle rec2) const {
    return ::CheckCollisionRecs(*this, rec2);
}

void core::raycpp::Rectangle::DrawRoundedLines(
    float   roundness,
    int     segments,
    float   lineThick,
    ::Color color
) const {
    ::DrawRectangleRoundedLines(*this, roundness, segments, lineThick, color);
}

void core::raycpp::Rectangle::DrawRounded(
    float   roundness,
    int     segments,
    ::Color color
) const {
    ::DrawRectangleRounded(*this, roundness, segments, color);
}

void core::raycpp::Rectangle::DrawLines(::Color color, float lineThick) const {
    ::DrawRectangleLinesEx(*this, lineThick, color);
}

void core::raycpp::Rectangle::DrawLines(::Color color) const {
    ::DrawRectangleLines(
        static_cast<int>(x),
        static_cast<int>(y),
        static_cast<int>(width),
        static_cast<int>(height),
        color
    );
}

void core::raycpp::Rectangle::DrawGradient(
    ::Color col1,
    ::Color col2,
    ::Color col3,
    ::Color col4
) const {
    ::DrawRectangleGradientEx(*this, col1, col2, col3, col4);
}

void core::raycpp::Rectangle::DrawGradientH(::Color color1, ::Color color2) const {
    ::DrawRectangleGradientH(
        static_cast<int>(x),
        static_cast<int>(y),
        static_cast<int>(width),
        static_cast<int>(height),
        color1,
        color2
    );
}

void core::raycpp::Rectangle::DrawGradientV(::Color color1, ::Color color2) const {
    ::DrawRectangleGradientV(
        static_cast<int>(x),
        static_cast<int>(y),
        static_cast<int>(width),
        static_cast<int>(height),
        color1,
        color2
    );
}

void core::raycpp::Rectangle::Draw(::Vector2 origin, float rotation, ::Color color)
    const {
    ::DrawRectanglePro(*this, origin, rotation, color);
}

void core::raycpp::Rectangle::Draw(::Color color) const {
    ::DrawRectangleRec(*this, color);
}

core::raycpp::Rectangle::operator ::Vector4() const {
    return {x, y, width, height};
}

::Vector4 core::raycpp::Rectangle::ToVector4() {
    return {x, y, width, height};
}

core::raycpp::Rectangle& core::raycpp::Rectangle::operator=(const ::Rectangle& rect) {
    set(rect);
    return *this;
}

void core::raycpp::Rectangle::SetHeight(float value) {
    height = value;
}

float core::raycpp::Rectangle::GetHeight() const {
    return height;
}

void core::raycpp::Rectangle::SetWidth(float value) {
    width = value;
}

float core::raycpp::Rectangle::GetWidth() const {
    return width;
}

void core::raycpp::Rectangle::SetY(float value) {
    y = value;
}

float core::raycpp::Rectangle::GetY() const {
    return y;
}

void core::raycpp::Rectangle::SetX(float value) {
    x = value;
}

float core::raycpp::Rectangle::GetX() const {
    return x;
}
