#include "raylib/font.h"
#include "raylib/raylibexception.h"

void raylib::Font::set(const ::Font& font) {
    baseSize     = font.baseSize;
    glyphCount   = font.glyphCount;
    glyphPadding = font.glyphPadding;
    texture      = font.texture;
    recs         = font.recs;
    glyphs       = font.glyphs;
}

raylib::Font::Font(
    int          _baseSize,
    int          _glyphCount,
    int          _glyphPadding,
    ::Texture2D  _texture,
    ::Rectangle* _recs,
    ::GlyphInfo* _glyphs
)
    : ::Font{_baseSize, _glyphCount, _glyphPadding, _texture, _recs, _glyphs} {}

raylib::Font::Font() {
    set(::GetFontDefault());
}

raylib::Font::Font(const ::Font& font) {
    set(font);
}

raylib::Font::Font(const std::string& fileName) {
    Load(fileName);
}

raylib::Font::Font(
    const std::string& fileName,
    int                fontSize,
    int*               fontChars,
    int                charCount
) {
    Load(fileName, fontSize, fontChars, charCount);
}

raylib::Font::Font(const ::Image& image, ::Color key, int firstChar) {
    Load(image, key, firstChar);
}

raylib::Font::Font(
    const std::string&   fileType,
    const unsigned char* fileData,
    int                  dataSize,
    int                  fontSize,
    int*                 fontChars,
    int                  charsCount
) {
    Load(fileType, fileData, dataSize, fontSize, fontChars, charsCount);
}

raylib::Font::Font(Font&& other) noexcept {
    set(other);

    other.baseSize     = 0;
    other.glyphCount   = 0;
    other.glyphPadding = 0;
    other.texture      = {};
    other.recs         = nullptr;
    other.glyphs       = nullptr;
}

raylib::Font::~Font() {
    Unload();
}

void raylib::Font::Unload() {
    if (baseSize != 0) {
        UnloadFont(*this);
        baseSize = 0;
    }
}

int raylib::Font::GetBaseSize() const {
    return baseSize;
}

int raylib::Font::GetGlyphCount() const {
    return glyphCount;
}

int raylib::Font::GetGlyphPadding() const {
    return glyphPadding;
}

::Rectangle* raylib::Font::GetRecs() const {
    return recs;
}

::GlyphInfo* raylib::Font::GetGlyphs() const {
    return glyphs;
}

raylib::TextureUnmanaged raylib::Font::GetTexture() {
    return raylib::TextureUnmanaged(texture);
}

void raylib::Font::SetTexture(const ::Texture& newTexture) {
    texture = newTexture;
}

raylib::Font& raylib::Font::operator=(const ::Font& font) {
    Unload();
    set(font);
    return *this;
}

raylib::Font& raylib::Font::operator=(Font&& other) noexcept {
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

void raylib::Font::Load(const std::string& fileName) {
    set(::LoadFont(fileName.c_str()));
    if (!IsReady()) {
        throw RaylibException(
            "Failed to load Font with from file: " + fileName
        );
    }
}

void raylib::Font::Load(
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

void raylib::Font::Load(const ::Image& image, ::Color key, int firstChar) {
    set(::LoadFontFromImage(image, key, firstChar));
    if (!IsReady()) {
        throw RaylibException("Failed to load Font with from image");
    }
}

void raylib::Font::Load(
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

bool raylib::Font::IsReady() const {
    return ::IsFontReady(*this);
}

void raylib::Font::DrawText(
    const char* text,
    ::Vector2   position,
    float       fontSize,
    float       spacing,
    ::Color     tint
) const {
    ::DrawTextEx(*this, text, position, fontSize, spacing, tint);
}

void raylib::Font::DrawText(
    const std::string& text,
    ::Vector2          position,
    float              fontSize,
    float              spacing,
    ::Color            tint
) const {
    ::DrawTextEx(*this, text.c_str(), position, fontSize, spacing, tint);
}

void raylib::Font::DrawText(
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

void raylib::Font::DrawText(
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

void raylib::Font::DrawText(
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

void raylib::Font::DrawText(
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

void raylib::Font::DrawText(
    int       codepoint,
    ::Vector2 position,
    float     fontSize,
    ::Color   tint
) const {
    ::DrawTextCodepoint(*this, codepoint, position, fontSize, tint);
}

void raylib::Font::DrawText(
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

raylib::Vector2 raylib::Font::MeasureText(
    const char* text,
    float       fontSize,
    float       spacing
) const {
    return raylib::Vector2(::MeasureTextEx(*this, text, fontSize, spacing));
}

raylib::Vector2 raylib::Font::MeasureText(
    const std::string& text,
    float              fontSize,
    float              spacing
) const {
    return raylib::Vector2(
        ::MeasureTextEx(*this, text.c_str(), fontSize, spacing)
    );
}

int raylib::Font::GetGlyphIndex(int character) const {
    return ::GetGlyphIndex(*this, character);
}

::Image raylib::Font::ImageText(
    const char* text,
    float       fontSize,
    float       spacing,
    ::Color     tint
) const {
    return ::ImageTextEx(*this, text, fontSize, spacing, tint);
}

::Image raylib::Font::ImageText(
    const std::string& text,
    float              fontSize,
    float              spacing,
    ::Color            tint
) const {
    return ::ImageTextEx(*this, text.c_str(), fontSize, spacing, tint);
}
