#include "core/raycpp/font.h"
#include "core/raycpp/raylibexception.h"

void core::raycpp::Font::set(const ::Font& font) {
    baseSize     = font.baseSize;
    glyphCount   = font.glyphCount;
    glyphPadding = font.glyphPadding;
    texture      = font.texture;
    recs         = font.recs;
    glyphs       = font.glyphs;
}

core::raycpp::Font::Font(
    int          _baseSize,
    int          _glyphCount,
    int          _glyphPadding,
    ::Texture2D  _texture,
    ::Rectangle* _recs,
    ::GlyphInfo* _glyphs
)
    : ::Font{_baseSize, _glyphCount, _glyphPadding, _texture, _recs, _glyphs} {}

core::raycpp::Font::Font() {
    set(::GetFontDefault());
}

core::raycpp::Font::Font(const ::Font& font) {
    set(font);
}

core::raycpp::Font::Font(const std::string& fileName) {
    Load(fileName);
}

core::raycpp::Font::Font(
    const std::string& fileName,
    int                fontSize,
    int*               fontChars,
    int                charCount
) {
    Load(fileName, fontSize, fontChars, charCount);
}

core::raycpp::Font::Font(const ::Image& image, ::Color key, int firstChar) {
    Load(image, key, firstChar);
}

core::raycpp::Font::Font(
    const std::string&   fileType,
    const unsigned char* fileData,
    int                  dataSize,
    int                  fontSize,
    int*                 fontChars,
    int                  charsCount
) {
    Load(fileType, fileData, dataSize, fontSize, fontChars, charsCount);
}

core::raycpp::Font::Font(Font&& other) noexcept {
    set(other);

    other.baseSize     = 0;
    other.glyphCount   = 0;
    other.glyphPadding = 0;
    other.texture      = {};
    other.recs         = nullptr;
    other.glyphs       = nullptr;
}

core::raycpp::Font::~Font() {
    Unload();
}

void core::raycpp::Font::Unload() {
    if (baseSize != 0) {
        UnloadFont(*this);
        baseSize = 0;
    }
}

int core::raycpp::Font::GetBaseSize() const {
    return baseSize;
}

int core::raycpp::Font::GetGlyphCount() const {
    return glyphCount;
}

int core::raycpp::Font::GetGlyphPadding() const {
    return glyphPadding;
}

::Rectangle* core::raycpp::Font::GetRecs() const {
    return recs;
}

::GlyphInfo* core::raycpp::Font::GetGlyphs() const {
    return glyphs;
}

core::raycpp::TextureUnmanaged core::raycpp::Font::GetTexture() {
    return core::raycpp::TextureUnmanaged(texture);
}

void core::raycpp::Font::SetTexture(const ::Texture& newTexture) {
    texture = newTexture;
}

core::raycpp::Font& core::raycpp::Font::operator=(const ::Font& font) {
    Unload();
    set(font);
    return *this;
}

core::raycpp::Font& core::raycpp::Font::operator=(Font&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    Unload();
    set(other);

    other.baseSize     = 0;
    other.glyphCount   = 0;
    other.glyphPadding = 0;
    other.texture      = {};
    other.recs         = nullptr;
    other.glyphs       = nullptr;

    return *this;
}

void core::raycpp::Font::Load(const std::string& fileName) {
    set(::LoadFont(fileName.c_str()));
    if (!IsReady()) {
        throw RaylibException(
            "Failed to load Font with from file: " + fileName
        );
    }
}

void core::raycpp::Font::Load(
    const std::string& fileName,
    int                fontSize,
    int*               fontChars,
    int                charCount
) {
    set(::LoadFontEx(fileName.c_str(), fontSize, fontChars, charCount));
    if (!IsReady()) {
        throw RaylibException(
            "Failed to load Font with from file with font size: " + fileName
        );
    }
}

void core::raycpp::Font::Load(const ::Image& image, ::Color key, int firstChar) {
    set(::LoadFontFromImage(image, key, firstChar));
    if (!IsReady()) {
        throw RaylibException("Failed to load Font with from image");
    }
}

void core::raycpp::Font::Load(
    const std::string&   fileType,
    const unsigned char* fileData,
    int                  dataSize,
    int                  fontSize,
    int*                 fontChars,
    int                  charsCount
) {
    set(::LoadFontFromMemory(
        fileType.c_str(),
        fileData,
        dataSize,
        fontSize,
        fontChars,
        charsCount
    ));
    if (!IsReady()) {
        throw RaylibException(
            "Failed to load Font " + fileType + " with from file data"
        );
    }
}

bool core::raycpp::Font::IsReady() const {
    return ::IsFontReady(*this);
}

void core::raycpp::Font::DrawText(
    const char* text,
    ::Vector2   position,
    float       fontSize,
    float       spacing,
    ::Color     tint
) const {
    ::DrawTextEx(*this, text, position, fontSize, spacing, tint);
}

void core::raycpp::Font::DrawText(
    const std::string& text,
    ::Vector2          position,
    float              fontSize,
    float              spacing,
    ::Color            tint
) const {
    ::DrawTextEx(*this, text.c_str(), position, fontSize, spacing, tint);
}

void core::raycpp::Font::DrawText(
    const char* text,
    int         posX,
    int         posY,
    float       fontSize,
    float       spacing,
    ::Color     tint
) const {
    ::DrawTextEx(
        *this,
        text,
        {static_cast<float>(posX), static_cast<float>(posY)},
        fontSize,
        spacing,
        tint
    );
}

void core::raycpp::Font::DrawText(
    const std::string& text,
    int                posX,
    int                posY,
    float              fontSize,
    float              spacing,
    ::Color            tint
) const {
    ::DrawTextEx(
        *this,
        text.c_str(),
        {static_cast<float>(posX), static_cast<float>(posY)},
        fontSize,
        spacing,
        tint
    );
}

void core::raycpp::Font::DrawText(
    const char* text,
    ::Vector2   position,
    ::Vector2   origin,
    float       rotation,
    float       fontSize,
    float       spacing,
    ::Color     tint
) const {
    ::DrawTextPro(
        *this,
        text,
        position,
        origin,
        rotation,
        fontSize,
        spacing,
        tint
    );
}

void core::raycpp::Font::DrawText(
    const std::string& text,
    ::Vector2          position,
    ::Vector2          origin,
    float              rotation,
    float              fontSize,
    float              spacing,
    ::Color            tint
) const {
    ::DrawTextPro(
        *this,
        text.c_str(),
        position,
        origin,
        rotation,
        fontSize,
        spacing,
        tint
    );
}

void core::raycpp::Font::DrawText(
    int       codepoint,
    ::Vector2 position,
    float     fontSize,
    ::Color   tint
) const {
    ::DrawTextCodepoint(*this, codepoint, position, fontSize, tint);
}

void core::raycpp::Font::DrawText(
    const int* codepoints,
    int        count,
    ::Vector2  position,
    float      fontSize,
    float      spacing,
    ::Color    tint
) const {
    ::DrawTextCodepoints(
        *this,
        codepoints,
        count,
        position,
        fontSize,
        spacing,
        tint
    );
}

core::raycpp::Vector2 core::raycpp::Font::MeasureText(
    const char* text,
    float       fontSize,
    float       spacing
) const {
    return core::raycpp::Vector2(::MeasureTextEx(*this, text, fontSize, spacing));
}

core::raycpp::Vector2 core::raycpp::Font::MeasureText(
    const std::string& text,
    float              fontSize,
    float              spacing
) const {
    return core::raycpp::Vector2(
        ::MeasureTextEx(*this, text.c_str(), fontSize, spacing)
    );
}

int core::raycpp::Font::GetGlyphIndex(int character) const {
    return ::GetGlyphIndex(*this, character);
}

::Image core::raycpp::Font::ImageText(
    const char* text,
    float       fontSize,
    float       spacing,
    ::Color     tint
) const {
    return ::ImageTextEx(*this, text, fontSize, spacing, tint);
}

::Image core::raycpp::Font::ImageText(
    const std::string& text,
    float              fontSize,
    float              spacing,
    ::Color            tint
) const {
    return ::ImageTextEx(*this, text.c_str(), fontSize, spacing, tint);
}
