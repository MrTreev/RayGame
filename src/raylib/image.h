#pragma once

#include "raylib/color.h"
#include "raylib/raylib.h"
#include <string>

namespace raylib {
class Image: public ::Image {
public:
    explicit Image(
        void* _data    = nullptr,
        int   _width   = 0,
        int   _height  = 0,
        int   _mipmaps = 1,
        int   _format  = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    );

    Image(const ::Image& image);

    explicit Image(const std::string& fileName);

    Image(
        const std::string& fileName,
        int                _width,
        int                _height,
        int                _format,
        int                _headerSize = 0
    );

    Image(const std::string& fileName, int* frames);

    Image(
        const std::string&   fileType,
        const unsigned char* fileData,
        int                  dataSize
    );

    explicit Image(const ::Texture2D& texture);

    Image(int _width, int _height, ::Color color = {255, 255, 255, 255});

    Image(
        const std::string& text,
        int                fontSize,
        ::Color            color = {255, 255, 255, 255}
    );

    Image(
        const ::Font&      font,
        const std::string& text,
        float              fontSize,
        float              spacing,
        ::Color            tint = {255, 255, 255, 255}
    );

    Image(const Image& other);

    Image(Image&& other) noexcept;

    static ::Image Text(
        const std::string& text,
        int                fontSize,
        ::Color            color = {255, 255, 255, 255}
    );

    static ::Image Text(
        const ::Font&      font,
        const std::string& text,
        float              fontSize,
        float              spacing,
        ::Color            tint = {255, 255, 255, 255}
    );

    static ::Image LoadFromScreen();

    static ::Image
    Color(int _width, int _height, ::Color color = {255, 255, 255, 255});

    static ::Image GradientLinear(
        int     _width,
        int     _height,
        int     _direction,
        ::Color start,
        ::Color end
    );

    static ::Image GradientRadial(
        int     _width,
        int     _height,
        float   density,
        ::Color inner,
        ::Color outer
    );

    static ::Image Checked(
        int     _width,
        int     _height,
        int     checksX,
        int     checksY,
        ::Color col1 = {255, 255, 255, 255},
        ::Color col2 = {0, 0, 0, 255}
    );

    static ::Image WhiteNoise(int _width, int _height, float factor);

    static ::Image Cellular(int _width, int _height, int tileSize);

    ~Image();

    Image& operator=(const ::Image& image);

    Image& operator=(const Image& other);

    Image& operator=(Image&& other) noexcept;

    void Load(const std::string& fileName);

    void Load(
        const std::string& fileName,
        int                _width,
        int                _height,
        int                _format,
        int                headerSize
    );

    void Load(const std::string& fileName, int* frames);

    void Load(
        const std::string&   fileType,
        const unsigned char* fileData,
        int                  dataSize
    );

    void Load(const ::Texture2D& texture);

    void Unload();

    void Export(const std::string& fileName) const;

    unsigned char* ExportToMemory(const char* fileType, int* fileSize);

    void ExportAsCode(const std::string& fileName) const;

    void SetWidth(
        int     _width,
        int     offsetX = 0,
        int     offsetY = 0,
        ::Color fill    = {255, 255, 255, 255}
    );

    void SetHeight(
        int     _height,
        int     offsetX = 0,
        int     offsetY = 0,
        ::Color fill    = {255, 255, 255, 255}
    );

    ::Vector2 GetSize() const;

    ::Image Copy() const;

    ::Image FromImage(::Rectangle rec) const;

    Image& Format(int newFormat);

    Image& ToPOT(::Color fillColor);

    Image& Crop(::Rectangle crop);

    Image& AlphaCrop(float threshold);

    Image& AlphaClear(::Color color, float threshold);

    Image& AlphaMask(const ::Image& alphaMask);

    Image& AlphaPremultiply();

    Image& Crop(int newWidth, int newHeight);

    Image& Crop(::Vector2 size);

    Image& Crop(int offsetX, int offsetY, int newWidth, int newHeight);

    Image& Resize(int newWidth, int newHeight);

    Image& ResizeNN(int newWidth, int newHeight);

    Image& ResizeCanvas(
        int     newWidth,
        int     newHeight,
        int     offsetX = 0,
        int     offsetY = 0,
        ::Color color   = {255, 255, 255, 255}
    );

    Image& Mipmaps();

    Image& Dither(int rBpp, int gBpp, int bBpp, int aBpp);

    Image& FlipVertical();

    Image& FlipHorizontal();

    Image& Rotate(int degrees);

    Image& RotateCW();

    Image& RotateCCW();

    Image& ColorTint(::Color color = {255, 255, 255, 255});

    Image& ColorInvert();

    Image& ColorGrayscale();

    Image& ColorContrast(float contrast);

    Image& ColorBrightness(int brightness);

    Image& ColorReplace(::Color color, ::Color replace);

    Rectangle GetAlphaBorder(float threshold) const;

    raylib::Color GetColor(int xpos = 0, int ypos = 0) const;

    raylib::Color GetColor(::Vector2 position) const;

    Image& ClearBackground(::Color color = {0, 0, 0, 255});

    void DrawPixel(int posX, int posY, ::Color color = {255, 255, 255, 255});

    void DrawPixel(::Vector2 position, ::Color color = {255, 255, 255, 255});

    void DrawLine(
        int     startPosX,
        int     startPosY,
        int     endPosX,
        int     endPosY,
        ::Color color = {255, 255, 255, 255}
    );

    void DrawLine(
        ::Vector2 start,
        ::Vector2 end,
        ::Color   color = {255, 255, 255, 255}
    );

    void DrawCircle(
        int     centerX,
        int     centerY,
        int     radius,
        ::Color color = {255, 255, 255, 255}
    );

    void DrawCircle(
        ::Vector2 center,
        int       radius,
        ::Color   color = {255, 255, 255, 255}
    );

    void DrawRectangle(
        int     posX,
        int     posY,
        int     _width,
        int     _height,
        ::Color color = {255, 255, 255, 255}
    );

    void DrawRectangle(
        Vector2 position,
        Vector2 size,
        ::Color color = {255, 255, 255, 255}
    );

    void DrawRectangle(::Rectangle rec, ::Color color = {255, 255, 255, 255});

    void DrawRectangleLines(
        ::Rectangle rec,
        int         thick = 1,
        ::Color     color = {255, 255, 255, 255}
    );

    void Draw(
        const ::Image& src,
        ::Rectangle    srcRec,
        ::Rectangle    dstRec,
        ::Color        tint = {255, 255, 255, 255}
    );

    void DrawText(
        const char* text,
        ::Vector2   position,
        int         fontSize,
        ::Color     color = {255, 255, 255, 255}
    );

    void DrawText(
        const std::string& text,
        ::Vector2          position,
        int                fontSize,
        ::Color            color = {255, 255, 255, 255}
    );

    void DrawText(
        const std::string& text,
        int                xpos,
        int                ypos,
        int                fontSize,
        ::Color            color = {255, 255, 255, 255}
    );

    void DrawText(
        const char* text,
        int         xpos,
        int         ypos,
        int         fontSize,
        ::Color     color = {255, 255, 255, 255}
    );

    void DrawText(
        const ::Font&      font,
        const std::string& text,
        ::Vector2          position,
        float              fontSize,
        float              spacing,
        ::Color            tint = {255, 255, 255, 255}
    );

    void DrawText(
        const ::Font& font,
        const char*   text,
        ::Vector2     position,
        float         fontSize,
        float         spacing,
        ::Color       tint = {255, 255, 255, 255}
    );

    ::Color* LoadColors() const;

    ::Color* LoadPalette(int maxPaletteSize, int* colorsCount) const;

    static void UnloadColors(::Color* colors);

    static void UnloadPalette(::Color* colors);

    ::Texture2D LoadTexture() const;

    explicit operator ::Texture2D() const;

    static int GetPixelDataSize(
        int _width,
        int _height,
        int _format = PIXELFORMAT_UNCOMPRESSED_R32G32B32A32
    );

    int GetPixelDataSize() const;

    bool IsReady() const;

    void* GetData() const;

    int GetWidth() const;

    int GetHeight() const;

    int GetMipmaps() const;

    int GetFormat() const;

protected:
    void set(const ::Image& image);
};
} // namespace raylib
