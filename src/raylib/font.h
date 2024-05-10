#pragma once

#include "raylib/raylib.h"
#include "raylib/textureunmanaged.h"
#include <string>

namespace raylib {

class Font: public ::Font {
public:
    Font(
        int          _baseSize,
        int          _glyphCount,
        int          _glyphPadding,
        ::Texture2D  _texture,
        ::Rectangle* _recs   = nullptr,
        ::GlyphInfo* _glyphs = nullptr
    );

    Font();

    Font(const ::Font& font);

    explicit Font(const std::string& fileName);

    Font(
        const std::string& fileName,
        int                fontSize,
        int*               fontChars = nullptr,
        int                charCount = 0
    );

    Font(const ::Image& image, ::Color key, int firstChar);

    Font(
        const std::string&   fileType,
        const unsigned char* fileData,
        int                  dataSize,
        int                  fontSize,
        int*                 fontChars,
        int                  charsCount
    );

    Font(const Font&) = delete;

    Font(Font&& other) noexcept;

    ~Font();

    void Unload();

    int GetBaseSize() const;

    int GetGlyphCount() const;

    int GetGlyphPadding() const;

    ::Rectangle* GetRecs() const;

    ::GlyphInfo* GetGlyphs() const;

    TextureUnmanaged GetTexture();

    void SetTexture(const ::Texture& newTexture);

    Font& operator=(const ::Font& font);

    Font& operator=(const Font&) = delete;

    Font& operator=(Font&& other) noexcept;

    void Load(const std::string& fileName);

    void Load(
        const std::string& fileName,
        int                fontSize,
        int*               fontChars,
        int                charCount
    );

    void Load(const ::Image& image, ::Color key, int firstChar);

    void Load(
        const std::string&   fileType,
        const unsigned char* fileData,
        int                  dataSize,
        int                  fontSize,
        int*                 fontChars,
        int                  charsCount
    );

    bool IsReady() const;

    void DrawText(
        const char* text,
        ::Vector2   position,
        float       fontSize,
        float       spacing,
        ::Color     tint = WHITE
    ) const;

    void DrawText(
        const std::string& text,
        ::Vector2          position,
        float              fontSize,
        float              spacing,
        ::Color            tint = WHITE
    ) const;

    void DrawText(
        const char* text,
        int         posX,
        int         posY,
        float       fontSize,
        float       spacing,
        ::Color     tint = WHITE
    ) const;

    void DrawText(
        const std::string& text,
        int                posX,
        int                posY,
        float              fontSize,
        float              spacing,
        ::Color            tint = WHITE
    ) const;

    void DrawText(
        const char* text,
        ::Vector2   position,
        ::Vector2   origin,
        float       rotation,
        float       fontSize,
        float       spacing,
        ::Color     tint = WHITE
    ) const;

    void DrawText(
        const std::string& text,
        ::Vector2          position,
        ::Vector2          origin,
        float              rotation,
        float              fontSize,
        float              spacing,
        ::Color            tint = WHITE
    ) const;

    void DrawText(
        int       codepoint,
        ::Vector2 position,
        float     fontSize,
        ::Color   tint = {255, 255, 255, 255}
    ) const;

    void DrawText(
        const int* codepoints,
        int        count,
        ::Vector2  position,
        float      fontSize,
        float      spacing,
        ::Color    tint = {255, 255, 255, 255}
    ) const;

    Vector2 MeasureText(const char* text, float fontSize, float spacing) const;

    Vector2
    MeasureText(const std::string& text, float fontSize, float spacing) const;

    int GetGlyphIndex(int character) const;

    ::Image
    ImageText(const char* text, float fontSize, float spacing, ::Color tint)
        const;

    ::Image ImageText(
        const std::string& text,
        float              fontSize,
        float              spacing,
        ::Color            tint
    ) const;

protected:
    void set(const ::Font& font);
};

} // namespace raylib
